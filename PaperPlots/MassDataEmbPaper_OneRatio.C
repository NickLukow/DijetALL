/**
 * Comparring Rt for data and embedding samples
 *
 * @author Maria Zurek
 */


//Still original... Make sever edits to turn this into the angle comparison code (copy chunks from that code and use the plot formatted here...)

#include <string>
#include "Riostream.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TString.h"
#include "TDatime.h"
#include "TMath.h"
#include "TStyle.h"
#include "TF1.h"
#include "TLatex.h"

int chosenEta = 2; // Choose eta region: 0 - forward, 1 - mid, 2 - full
int chosenTrig = 2; // Choose trigger: 0 - JP1, 1 - JP2, 2 - JP1+JP2
bool printHisto = true; // Do you want to print histograms?
string nameHisto = "Sl16d_data_emb"; // Set name tag for all histograms  
  
  int colors[3] = {2,4,8};
  int markers[3] = {22,21,20};
  int markersr[3] = {26,25,24};

  const int Ntriggers = 3;
  const char *trigger[Ntriggers] = {"JP1","JP2","All"};

  const int Ntopol = 3;
  const char *topology[Ntopol] = {"EW", "EEWW", "Full"};

TH1D* hRatio(TH1D* hdata, TH1D* hemb, int mar, int col) {

  TH1D *ratio= (TH1D*) hdata->Clone();
  ratio->SetDirectory(0);
  ratio->Add(hemb,-1);
  ratio->Divide(hdata);
 
  ratio->SetBit(TH1::kNoTitle);
  ratio->SetLineWidth(2);
  ratio->GetYaxis()->SetTitle("#frac{data-simu}{data}");
  ratio->GetXaxis()->SetTitle("Dijet M_{inv} (GeV/c^{2})");
  ratio->GetYaxis()->CenterTitle();
  ratio->GetYaxis()->SetRangeUser(-0.3,0.3);
 
  ratio->GetYaxis()->SetNdivisions(5);
  ratio->SetMarkerStyle(mar);
  ratio->SetMarkerColor(col);
  ratio->SetLineColor(col);

  return ratio;
}

TPad* upPad(string name, int isLog=0) {
  
  TPad *pad = new TPad(name.c_str(),name.c_str(), 0.0,0.298,1.0,1.0);
  if(isLog==1) pad->SetLogy();
  pad->SetBottomMargin(0);
  pad->SetTopMargin(0.1); //0.2
  pad->Draw();
  
  return pad;
}
TPad* upPadCopy(string name, int isLog=0) {
  
  TPad *pad = new TPad(name.c_str(),name.c_str(), 0.0,0.298,1.0,1.0);
  if(isLog==1) pad->SetLogy();
  pad->SetBottomMargin(0);
  pad->SetTopMargin(0.1); //0.2
  pad->SetFillColor(0);
  pad->SetFillStyle(0);
  pad->SetFrameFillStyle(0);

  pad->Draw();
  
  return pad;
}


TPad* dPad(string name) {
  
  TPad *pad = new TPad(name.c_str(),name.c_str(), 0,0.0,1.0,0.298);
  pad->SetTopMargin(0);
  pad->SetBottomMargin(0.3);
  pad->Draw();
  
  return pad;
}



void SetHistogramOptions( TH1D *EmbHistogram, TH1D *DataHistogram, int triggerID)
{
  //clearing overflowbin and unused first bin for proper integral
  EmbHistogram->SetBinContent(1,0);
  DataHistogram->SetBinContent(1,0);
  EmbHistogram->SetBinContent(0,0);
  DataHistogram->SetBinContent(0,0);
  


  double dataInt = DataHistogram->Integral();
  double embInt = EmbHistogram->Integral();
  EmbHistogram->Scale(dataInt/embInt);
  
  DataHistogram->SetLineWidth(2);
  EmbHistogram->SetLineWidth(3);
  DataHistogram->SetLineColor(colors[triggerID]);
  EmbHistogram->SetLineColor(colors[triggerID]);
  DataHistogram->SetMarkerStyle(markers[triggerID]);
  DataHistogram->SetMarkerColor(colors[triggerID]);
  DataHistogram->SetMarkerSize(1.5);    
  EmbHistogram->GetYaxis()->SetTitle("Counts");
  EmbHistogram->SetTitle("");

  return;
}




void MassDataEmbPaper_OneRatio(){
  
  gStyle->SetOptDate(0);                                                                                                                                                                                  
  gStyle->SetOptStat(0);
  gStyle->SetTitleOffset(1.4,"y");
  gStyle->SetTitleOffset(3.5,"x");
  
  //-------> Inserted Code
  TFile *fRData = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Data/Data.root"); 
  TFile *fREmb = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Embedding/Embedding.root");

  /////END Read files <--1--

  Int_t trig = 2;    // JP1=0, JP2=1, All=2
  Int_t ijet = 0;    // High jet = 0, low jet = 1
  Int_t topol = 2;   //0 = EW, 1 = EEWW, 2 = Full

  Float_t JP1PS = 9.92;  

  ////Define Histograms --2-->
  


  TH1D *hR15DataMass[Ntriggers];
  TH1D *hR15EmbMass[Ntriggers]; 

  for(int i = 0; i < Ntriggers; i++){ 
      //hR15DataMass[i][j] = (TH1D*)fRData->Get(Form("hDiJetMass_%s_%s",trigger[i],topology[topol]));
      hR15DataMass[i] = (TH1D*)fRData->Get(Form("hDiJetMass_DetBin_%s_%s",trigger[i],topology[topol]));
      if(i==2){

      hR15EmbMass[i] = (TH1D*)hR15EmbMass[1]->Clone();

      hR15EmbMass[i]->Add(hR15EmbMass[0], 1/JP1PS);

      }
      else{
        //hR15EmbMass[i][j] = (TH1D*)fREmb->Get(Form("hDiJetMass_%s_%s",trigger[i],topology[topol]));
        hR15EmbMass[i] = (TH1D*)fREmb->Get(Form("hDiJetMass_DetBin_%s_%s",trigger[i],topology[topol]));
      }
  }

//Setting histogram options
  for (int i = 0; i < Ntriggers; i++)
  {
      SetHistogramOptions( hR15EmbMass[i], hR15DataMass[i], i);

      hR15EmbMass[i]->GetXaxis()->SetRangeUser(17 , 79);
      hR15EmbMass[i]->GetXaxis()->SetTitle("M_{inv}");
      hR15DataMass[i]->GetXaxis()->SetRangeUser(17, 79);
  }


//<-------Inserted Code

// Second axis with labels
  const char *ParMass[7]  = {"18.2", "22.0", "26.8", "32.7", "39.6", "49.5", "68.0"};
  TH1D *hEmbDijetMassCopy = (TH1D*)hR15EmbMass[1]->Clone("hEmbDijetMassCopy");
  hEmbDijetMassCopy->Reset();
  hEmbDijetMassCopy->SetLineColor(kBlack);
  for(int bin=0; bin<7; bin++){
    hEmbDijetMassCopy->GetXaxis()->SetBinLabel(bin+2,ParMass[bin]);
  }
  hEmbDijetMassCopy->LabelsOption("v");
  hEmbDijetMassCopy->GetXaxis()->SetLabelOffset(-0.005); //0.037
  hEmbDijetMassCopy->GetXaxis()->SetTitleOffset(0.7); //3.0
  hEmbDijetMassCopy->GetXaxis()->SetTitle("Parton dijet M_{inv} (GeV/c^{2})");

  

  // Make Legend
  TLegend *leg0 = new TLegend(0.16,0.08,0.54,0.21);
  leg0->SetTextSize(25);
  leg0->SetTextFont(43);
  leg0->SetBorderSize(0);  leg0->SetFillStyle(0);
  
  TLegend *leg1 = new TLegend(0.14,0.11,0.25,0.28);
  leg1->SetTextSize(25);
  leg1->SetTextFont(43);
  leg1->SetBorderSize(0);  leg1->SetFillStyle(0);
  
  TLegend *leg2 = new TLegend(0.14,0.35,0.25,0.52);
  leg2->SetTextSize(25);
  leg2->SetTextFont(43);
  leg2->SetBorderSize(0);  leg2->SetFillStyle(0);

  TLatex text0;
  text0.SetTextAlign(12);
  text0.SetTextFont(43);
  text0.SetTextSize(25);


  TCanvas *cMass = new TCanvas("cMass","DijetMass",0,0,800,0.887*800);
  cMass->cd();

  


  // Pad with yields
  upPad("uMass",1)->cd();
  hR15EmbMass[1]->GetYaxis()->SetRangeUser(1.1, 100000000);


  //Draw Shorter Axis
  TGaxis *axis = new TGaxis(17,1.1,17,10000000,1.1,10000000,50510,"G");
  axis->SetName("axis");
  axis->SetLabelFont(43);
  axis->SetLabelSize(25);
  hR15EmbMass[1]->GetYaxis()->SetLabelSize(0);
  hR15EmbMass[1]->GetYaxis()->SetTickLength(0);


  hR15EmbMass[1]->Draw("hist");
  axis->Draw();
  hR15EmbMass[0]->Draw("hist same");
  hR15DataMass[1]->Draw("same");
  hR15DataMass[0]->Draw("same");


  cMass->cd();
  // Pad with top axis
  upPadCopy("uPtCopy",1)->cd();
  hEmbDijetMassCopy->GetYaxis()->SetLabelSize(0.);
  hEmbDijetMassCopy->GetYaxis()->SetTickSize(0.);
  hEmbDijetMassCopy->GetXaxis()->SetTickSize(0.);
  hEmbDijetMassCopy->Draw("X+");
  leg0->AddEntry(hR15DataMass[0],"JP1","LP");
  leg0->AddEntry(hR15DataMass[1],"JP2","LP");
  leg0->Draw("same");
  cMass->cd();

  
  // Pad with simu-data for JP2
  dPad("dMass")->cd();
  hRatio(hR15DataMass[0],hR15EmbMass[0],markersr[0],colors[0])->Draw("");
  hRatio(hR15DataMass[1],hR15EmbMass[1],markersr[1],colors[1])->Draw("Same");
  
  cMass->Draw();
  

  
  cMass->Draw(); 

  cMass->Print("./Figures/Run15Dijet_MassComparison_OneRatio.pdf");
 
}
