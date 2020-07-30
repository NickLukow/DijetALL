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



TPad* upPad(string name, int isLog=0) {
  
  TPad *pad = new TPad(name.c_str(),name.c_str(), 0.0,0.53,1.0,1.0);
  if(isLog==1) pad->SetLogy();
  pad->SetBottomMargin(0.11); //0
  pad->SetTopMargin(0.059);
  pad->Draw();
  
  return pad;
}

TPad* dPad(string name, int isLog=0) {
  
  TPad *pad = new TPad(name.c_str(),name.c_str(), 0,0.0,1.0,0.53);
  if(isLog==1) pad->SetLogy();
  pad->SetTopMargin(0.105);
  pad->SetBottomMargin(0.158);
  pad->Draw();
  
  return pad;
}

void SetHistogramOptions( TH1D *EmbHistogram, TH1D *DataHistogram, int trigger)
{
  int colors[3] = {2,4,8};
  int markers[3] = {22,21,20};
  int markersr[3] = {26,25,24};

  double dataInt = DataHistogram->Integral();
  double embInt = EmbHistogram->Integral();
  EmbHistogram->Scale(dataInt/embInt);
  
  DataHistogram->SetLineWidth(2);
  EmbHistogram->SetLineWidth(3);
  DataHistogram->SetLineColor(colors[trigger]);
  EmbHistogram->SetLineColor(colors[trigger]);
  DataHistogram->SetMarkerStyle(markers[trigger]);
  DataHistogram->SetMarkerColor(colors[trigger]);
  DataHistogram->SetMarkerSize(1.5);    
  EmbHistogram->GetYaxis()->SetTitle("Counts");
  EmbHistogram->SetTitle("");

  return;
}




void AngleEmbComp(){
  
  gStyle->SetOptDate(0);                                                                                                                                                                                  
  gStyle->SetOptStat(0);
  gStyle->SetTitleOffset(2.,"y");
  gStyle->SetTitleOffset(2,"x");
  
  //-------> Inserted Code
  TFile *fRData = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Data/Data.root"); 
  TFile *fREmb = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Embedding/Embedding.root");

  /////END Read files <--1--

  Int_t trig = 2;    // JP1=0, JP2=1, All=2
  Int_t ijet = 0;    // High jet = 0, low jet = 1
  Int_t topol = 2;   //0 = EW, 1 = EEWW, 2 = Full

  Float_t JP1PS = 9.92;  

  ////Define Histograms --2-->
  const int Ntriggers = 3;
  const char *trigger[Ntriggers] = {"JP1","JP2","All"};

  const int Ntopol = 3;
  const char *topology[Ntopol] = {"EW", "EEWW", "Full"};


  TH1D *hR15DataMass[Ntriggers]; TH1D *hR15DataDeltaPhi[Ntriggers]; TH1D *hR15DataDeltaEta[Ntriggers];
  TH1D *hR15EmbMass[Ntriggers];  TH1D *hR15EmbDeltaPhi[Ntriggers];  TH1D *hR15EmbDeltaEta[Ntriggers];

  for(int i = 0; i < Ntriggers; i++){ 
      //hR15DataMass[i][j] = (TH1D*)fRData->Get(Form("hDiJetMass_%s_%s",trigger[i],topology[topol]));
      hR15DataMass[i] = (TH1D*)fRData->Get(Form("hDiJetMass_DetBin_%s_%s",trigger[i],topology[topol]));
      hR15DataDeltaPhi[i] = (TH1D*)fRData->Get(Form("hDiJetDeltaPhi_%s_%s",trigger[i],topology[topol]));
      hR15DataDeltaEta[i] = (TH1D*)fRData->Get(Form("hDiJetDeltaEta_%s_%s",trigger[i],topology[topol]));
      if(i==2){

      hR15EmbMass[i] = (TH1D*)hR15EmbMass[1]->Clone();
      hR15EmbDeltaPhi[i] = (TH1D*)hR15EmbDeltaPhi[1]->Clone();
      hR15EmbDeltaEta[i] = (TH1D*)hR15EmbDeltaEta[1]->Clone();

      hR15EmbMass[i]->Add(hR15EmbMass[0], 1/JP1PS);
      hR15EmbDeltaPhi[i]->Add(hR15EmbDeltaPhi[0], 1/JP1PS);
      hR15EmbDeltaEta[i]->Add(hR15EmbDeltaEta[0], 1/JP1PS);

      }
      else{
        //hR15EmbMass[i][j] = (TH1D*)fREmb->Get(Form("hDiJetMass_%s_%s",trigger[i],topology[topol]));
        hR15EmbMass[i] = (TH1D*)fREmb->Get(Form("hDiJetMass_DetBin_%s_%s",trigger[i],topology[topol]));
        hR15EmbDeltaPhi[i] = (TH1D*)fREmb->Get(Form("hDiJetDeltaPhi_%s_%s",trigger[i],topology[topol]));
        hR15EmbDeltaEta[i] = (TH1D*)fREmb->Get(Form("hDiJetDeltaEta_%s_%s",trigger[i],topology[topol]));
      }
  }

//Setting histogram options
  for (int i = 0; i < Ntriggers; i++)
  {
      SetHistogramOptions( hR15EmbMass[i], hR15DataMass[i], i);
      SetHistogramOptions( hR15EmbDeltaPhi[i], hR15DataDeltaPhi[i], i);
      SetHistogramOptions( hR15EmbDeltaEta[i], hR15DataDeltaEta[i], i);

      hR15EmbDeltaEta[i]->GetXaxis()->SetRangeUser(-2, 2);
      hR15EmbDeltaEta[i]->GetXaxis()->SetTitle("d#eta");
      hR15DataDeltaEta[i]->GetXaxis()->SetRangeUser(-2, 2);
      hR15DataDeltaEta[i]->Rebin(4);
      hR15EmbDeltaEta[i]->Rebin(4);

      hR15EmbDeltaPhi[i]->GetXaxis()->SetRangeUser(1.8, 3.4);
      hR15EmbDeltaPhi[i]->GetXaxis()->SetTitle("d#phi");
      hR15DataDeltaPhi[i]->GetXaxis()->SetRangeUser(1.8, 3.4);

      hR15EmbMass[i]->GetXaxis()->SetRangeUser(0 , 79);
      hR15EmbMass[i]->GetXaxis()->SetTitle("M_{inv}");
      hR15DataMass[i]->GetXaxis()->SetRangeUser(0, 79);
  }


//<-------Inserted Code

  // Make Legend
  TLegend *leg0 = new TLegend(0.4,0.18,0.78,0.31);
  leg0->SetTextSize(25);
  leg0->SetTextFont(43);
  leg0->SetBorderSize(0);  leg0->SetFillStyle(0);

  TLatex text0;
  text0.SetTextAlign(12);
  text0.SetTextFont(43);
  text0.SetTextSize(25);


  TCanvas *cDelta = new TCanvas("cDelta","JetPt",0,0,800,1.26*800);
  cDelta->cd();
  upPad("uRt",1)->cd();
  hR15EmbDeltaPhi[0]->GetYaxis()->SetRangeUser(1.1, 6000000);
  hR15EmbDeltaPhi[0]->Draw("hist");
  hR15EmbDeltaPhi[1]->Draw("hist same");
  hR15DataDeltaPhi[1]->Draw("PE same");
  hR15DataDeltaPhi[0]->Draw("PE same");
  leg0->AddEntry(hR15DataDeltaPhi[0],"JP1","LP");
  leg0->AddEntry(hR15DataDeltaPhi[1],"JP2","LP");
  leg0->Draw("same");
  //text0.DrawLatex(0.5,10," #LT p_{T} #GT = 6.54 GeV/c");
  cDelta->cd();
  
  dPad("dRt",1)->cd();
  hR15EmbDeltaEta[0]->GetYaxis()->SetRangeUser(1.2, 6000000);
  hR15EmbDeltaEta[0]->Draw("hist");
  hR15EmbDeltaEta[1]->Draw("hist same");
  hR15DataDeltaEta[0]->Draw("PE same");
  hR15DataDeltaEta[1]->Draw("PE same");
  //text0.DrawLatex(0.5,10," #LT p_{T} #GT = 28.7 GeV/c");
  
  cDelta->Draw(); 

  cDelta->Print("./Figures/Run15Dijet_AngleComparison.pdf");
 
}
