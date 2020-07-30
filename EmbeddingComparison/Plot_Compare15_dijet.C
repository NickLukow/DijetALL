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

//--->START MAIN PROGRAM
//________________________________________________________________________________
void Plot_Compare15_dijet() {
  
  gROOT->cd();
  TDatime now;                                          //Set time in Root
  now.Print();
  
  /////Read files --1-->
  
  TFile *fR13 = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Data/Data.root"); 
  TFile *fREmb = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Embedding/Embedding.root");
  
  /////END Read files <--1--

  Int_t trig = 1;    // JP1=0, JP2=1, All=2
  Int_t ijet = 0;    // High jet = 0, low jet = 1
  Int_t topol = 2;   //0 = EW, 1 = EEWW, 2 = Full

  Bool_t REBIN = 1;
  Int_t binXX = 10;

  //Period 1
  //Float_t JP1PS = 18.88;  //Modify 21.82 --> 18.88
  //Float_t JP0PS = 133.34;
  //Period 2
  Float_t JP1PS = 9.92;    //Modify 56.731 --> 48.88 
  //Float_t JP0PS = 361.32;

  ////Define Histograms --2-->
  const int Ntriggers = 3;
  const char *trigger[Ntriggers] = {"JP1","JP2","All"};

  const int Ntopol = 3;
  const char *topology[Ntopol] = {"EW", "EEWW", "Full"};

  //Jets
  TH1D *hR13JetIdx[Ntriggers][2]; TH1D *hR13JetPt[Ntriggers][2]; TH1D *hR13JetRt[Ntriggers][2];
  TH1D *hR13JetEta[Ntriggers][2]; TH1D *hR13JetPhi[Ntriggers][2]; TH1D *hR13JetDet[Ntriggers][2];
  TH1D *hREmbJetIdx[Ntriggers][2]; TH1D *hREmbJetPt[Ntriggers][2]; TH1D *hREmbJetRt[Ntriggers][2];
  TH1D *hREmbJetEta[Ntriggers][2]; TH1D *hREmbJetPhi[Ntriggers][2]; TH1D *hREmbJetDet[Ntriggers][2];
  //Tracks
  TH1D *hR13TrackIdx[Ntriggers][2]; TH1D *hR13TrackPt[Ntriggers][2]; TH1D *hR13TrackDcaXY[Ntriggers][2];
  TH1D *hR13TrackEta[Ntriggers][2]; TH1D *hR13TrackPhi[Ntriggers][2]; TH1D *hR13TrackDcaZ[Ntriggers][2];
  TH1D *hREmbTrackIdx[Ntriggers][2]; TH1D *hREmbTrackPt[Ntriggers][2]; TH1D *hREmbTrackDcaXY[Ntriggers][2];
  TH1D *hREmbTrackEta[Ntriggers][2]; TH1D *hREmbTrackPhi[Ntriggers][2]; TH1D *hREmbTrackDcaZ[Ntriggers][2]; 
  //Towers
  TH1D *hR13TowerIdx[Ntriggers][2]; TH1D *hR13TowerPt[Ntriggers][2]; TH1D *hR13TowerE[Ntriggers][2];   //Tower Pt does not exist is Tower ET
  TH1D *hR13TowerEta[Ntriggers][2]; TH1D *hR13TowerPhi[Ntriggers][2]; TH1D *hR13TowerAdc[Ntriggers][2]; 
  TH1D *hREmbTowerIdx[Ntriggers][2]; TH1D *hREmbTowerPt[Ntriggers][2]; TH1D *hREmbTowerE[Ntriggers][2];   //Tower Pt does not exist is Tower ET
  TH1D *hREmbTowerEta[Ntriggers][2]; TH1D *hREmbTowerPhi[Ntriggers][2]; TH1D *hREmbTowerAdc[Ntriggers][2]; 
    
  for(int i = 0; i < Ntriggers; i++){ 
  for(int j = 0; j < 2; j++){
    //Jets
    
    hR13JetIdx[i][j] = (TH1D*)fR13->Get(Form("hDiJetMass_%s_%s",trigger[i],topology[topol]));
    //hR13JetIdx[i][j] = (TH1D*)fR13->Get(Form("hJetIdx_%s_%s_%d",trigger[i], topology[topol],j));
    hR13JetPt[i][j]  = (TH1D*)fR13->Get(Form("hJetPt_%s_%s_%d",trigger[i],topology[topol],j));
    hR13JetRt[i][j]  = (TH1D*)fR13->Get(Form("hJetRt_%s_%s_%d",trigger[i],topology[topol],j));
    hR13JetEta[i][j] = (TH1D*)fR13->Get(Form("hJetEta_%s_%s_%d",trigger[i],topology[topol],j));
    hR13JetPhi[i][j] = (TH1D*)fR13->Get(Form("hJetPhi_%s_%s_%d",trigger[i],topology[topol],j));
    hR13JetDet[i][j] = (TH1D*)fR13->Get(Form("hJetDet_%s_%s_%d",trigger[i],topology[topol],j));
    
    if(i==2){
    hREmbJetIdx[i][j] = (TH1D*)hREmbJetIdx[1][j]->Clone();
    hREmbJetPt[i][j]  = (TH1D*)hREmbJetPt[1][j]->Clone();
    hREmbJetRt[i][j]  = (TH1D*)hREmbJetRt[1][j]->Clone();
    hREmbJetEta[i][j] = (TH1D*)hREmbJetEta[1][j]->Clone();
    hREmbJetPhi[i][j] = (TH1D*)hREmbJetPhi[1][j]->Clone();
    hREmbJetDet[i][j] = (TH1D*)hREmbJetDet[1][j]->Clone();

    hREmbJetIdx[i][j]->Add(hREmbJetIdx[0][j] , 1/JP1PS);
    hREmbJetPt[i][j]->Add(hREmbJetPt[0][j] , 1/JP1PS); 
    hREmbJetRt[i][j]->Add(hREmbJetRt[0][j] , 1/JP1PS); 
    hREmbJetEta[i][j]->Add(hREmbJetEta[0][j] , 1/JP1PS);
    hREmbJetPhi[i][j]->Add(hREmbJetPhi[0][j] , 1/JP1PS);
    hREmbJetDet[i][j]->Add(hREmbJetDet[0][j] , 1/JP1PS);
    
    }
    else{
    hREmbJetIdx[i][j] = (TH1D*)fREmb->Get(Form("hDiJetMass_%s_%s",trigger[i],topology[topol]));
    //hREmbJetIdx[i][j] = (TH1D*)fREmb->Get(Form("hJetIdx_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbJetPt[i][j]  = (TH1D*)fREmb->Get(Form("hJetPt_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbJetRt[i][j]  = (TH1D*)fREmb->Get(Form("hJetRt_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbJetEta[i][j] = (TH1D*)fREmb->Get(Form("hJetEta_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbJetPhi[i][j] = (TH1D*)fREmb->Get(Form("hJetPhi_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbJetDet[i][j] = (TH1D*)fREmb->Get(Form("hJetDet_%s_%s_%d",trigger[i], topology[topol],j));
    }
    
    //Tracks
    hR13TrackIdx[i][j]    = (TH1D*)fR13->Get(Form("hTrackIdx_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TrackPt[i][j]     = (TH1D*)fR13->Get(Form("hTrackPt_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TrackDcaXY[i][j]  = (TH1D*)fR13->Get(Form("hTrackDcaXY_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TrackEta[i][j]    = (TH1D*)fR13->Get(Form("hTrackEta_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TrackPhi[i][j]    = (TH1D*)fR13->Get(Form("hTrackPhi_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TrackDcaZ[i][j]   = (TH1D*)fR13->Get(Form("hTrackDcaZ_%s_%s_%d",trigger[i],topology[topol],j));
    if(i==2){
    hREmbTrackIdx[i][j]    = (TH1D*)hREmbTrackIdx[1][j]->Clone();
    hREmbTrackPt[i][j]     = (TH1D*)hREmbTrackPt[1][j]->Clone();
    hREmbTrackDcaXY[i][j]  = (TH1D*)hREmbTrackDcaXY[1][j]->Clone();
    hREmbTrackEta[i][j]    = (TH1D*)hREmbTrackEta[1][j]->Clone();
    hREmbTrackPhi[i][j]    = (TH1D*)hREmbTrackPhi[1][j]->Clone();
    hREmbTrackDcaZ[i][j]   = (TH1D*)hREmbTrackDcaZ[1][j]->Clone();

    hREmbTrackIdx[i][j]->Add(hREmbTrackIdx[0][j], 1/JP1PS);  
    hREmbTrackPt[i][j]->Add(hREmbTrackPt[0][j], 1/JP1PS);   
    hREmbTrackDcaXY[i][j]->Add(hREmbTrackDcaXY[0][j], 1/JP1PS);
    hREmbTrackEta[i][j]->Add(hREmbTrackEta[0][j], 1/JP1PS);  
    hREmbTrackPhi[i][j]->Add(hREmbTrackPhi[0][j], 1/JP1PS);  
    hREmbTrackDcaZ[i][j]->Add(hREmbTrackDcaZ[0][j], 1/JP1PS); 
    }
    else {
    hREmbTrackIdx[i][j]    = (TH1D*)fREmb->Get(Form("hTrackIdx_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTrackPt[i][j]     = (TH1D*)fREmb->Get(Form("hTrackPt_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTrackDcaXY[i][j]  = (TH1D*)fREmb->Get(Form("hTrackDcaXY_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTrackEta[i][j]    = (TH1D*)fREmb->Get(Form("hTrackEta_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTrackPhi[i][j]    = (TH1D*)fREmb->Get(Form("hTrackPhi_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTrackDcaZ[i][j]   = (TH1D*)fREmb->Get(Form("hTrackDcaZ_%s_%s_%d",trigger[i], topology[topol],j));

    }
    
    //Towers
    hR13TowerIdx[i][j] = (TH1D*)fR13->Get(Form("hTowerIdx_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TowerPt[i][j]  = (TH1D*)fR13->Get(Form("hTowerPt_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TowerE[i][j]   = (TH1D*)fR13->Get(Form("hTowerE_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TowerEta[i][j] = (TH1D*)fR13->Get(Form("hTowerEta_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TowerPhi[i][j] = (TH1D*)fR13->Get(Form("hTowerPhi_%s_%s_%d",trigger[i],topology[topol],j));
    hR13TowerAdc[i][j] = (TH1D*)fR13->Get(Form("hTowerAdc_%s_%s_%d",trigger[i],topology[topol],j));
    if(i==2){
    hREmbTowerIdx[i][j] = (TH1D*)hREmbTowerIdx[1][j]->Clone();
    hREmbTowerPt[i][j]  = (TH1D*)hREmbTowerPt[1][j]->Clone();
    hREmbTowerE[i][j]   = (TH1D*)hREmbTowerE[1][j]->Clone();
    hREmbTowerEta[i][j] = (TH1D*)hREmbTowerEta[1][j]->Clone();
    hREmbTowerPhi[i][j] = (TH1D*)hREmbTowerPhi[1][j]->Clone();
    hREmbTowerAdc[i][j] = (TH1D*)hREmbTowerAdc[1][j]->Clone();

    hREmbTowerIdx[i][j]->Add(hREmbTowerIdx[0][j], 1/JP1PS); 
    hREmbTowerPt[i][j]->Add(hREmbTowerPt[0][j], 1/JP1PS);  
    hREmbTowerE[i][j]->Add(hREmbTowerE[0][j], 1/JP1PS);   
    hREmbTowerEta[i][j]->Add(hREmbTowerEta[0][j], 1/JP1PS); 
    hREmbTowerPhi[i][j]->Add(hREmbTowerPhi[0][j], 1/JP1PS); 
    hREmbTowerAdc[i][j]->Add(hREmbTowerAdc[0][j], 1/JP1PS); 
    }
    else {
    hREmbTowerIdx[i][j] = (TH1D*)fREmb->Get(Form("hTowerIdx_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTowerPt[i][j]  = (TH1D*)fREmb->Get(Form("hTowerPt_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTowerE[i][j]   = (TH1D*)fREmb->Get(Form("hTowerE_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTowerEta[i][j] = (TH1D*)fREmb->Get(Form("hTowerEta_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTowerPhi[i][j] = (TH1D*)fREmb->Get(Form("hTowerPhi_%s_%s_%d",trigger[i], topology[topol],j));
    hREmbTowerAdc[i][j] = (TH1D*)fREmb->Get(Form("hTowerAdc_%s_%s_%d",trigger[i], topology[topol],j));
    }
  } 
  }
  ////End Define Histograms <--2--

gStyle->SetOptStat(0);

  //////Jets Plots --5-->
  TCanvas *c0 = new TCanvas("c0","Jets",0,0,1300,900);
  c0->cd();
  c0->Divide(3,2);
  
  c0->cd(1);
  //c0->cd(1)->SetLogy();
  TPad *pad010 = new TPad("pad010","pad010", 0.0,0.3,1.0,1.0);
  pad010->SetLogy();
  pad010->SetBottomMargin(0);
  pad010->Draw();
  pad010->cd();
  //////////
  if(REBIN) hR13JetIdx[trig][ijet]->Rebin(10);
  //hR13JetIdx[trig][ijet]->SetTitle("Jets per event");
  hR13JetIdx[trig][ijet]->SetTitle("Di-Jet Invariant Mass");
  hR13JetIdx[trig][ijet]->SetLineWidth(2); hR13JetIdx[trig][ijet]->SetLineColor(4);
  hR13JetIdx[trig][ijet]->SetMinimum(0.1);
  hR13JetIdx[trig][ijet]->Scale(1/hR13JetIdx[trig][ijet]->Integral());
  hR13JetIdx[trig][ijet]->GetXaxis()->SetRangeUser(0,120);
  hR13JetIdx[trig][ijet]->Draw();
  
  hREmbJetIdx[trig][ijet]->SetLineColor(2);
  hREmbJetIdx[trig][ijet]->Scale(1/hREmbJetIdx[trig][ijet]->Integral());
  hREmbJetIdx[trig][ijet]->Draw("same");
  //////////
  c0->cd(1);
  TPad *pad011 = new TPad("pad011","pad011", 0,0.05,1.0,0.3);
  pad011->SetTopMargin(0);
  pad011->SetBottomMargin(0.2);
  pad011->Draw();
  pad011->cd();
  //hR13JetIdx[trig][ijet]->Sumw2(kFALSE);  hR13JetIdx[trig][ijet]->Sumw2(kFALSE);
  TH1D *hR13JetIdx_R= (TH1D*) hR13JetIdx[trig][ijet]->Clone();
  //hR13JetIdx_R->Sumw2();
  hR13JetIdx_R->Add(hREmbJetIdx[trig][ijet],-1);
  hR13JetIdx_R->Divide(hR13JetIdx[trig][ijet]);
  hR13JetIdx_R->SetBit(TH1::kNoTitle);
  hR13JetIdx_R->SetLineColor(1); 
  hR13JetIdx_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13JetIdx_R->GetYaxis()->CenterTitle();
  hR13JetIdx_R->GetYaxis()->SetTitleSize(0.07);
  hR13JetIdx_R->GetYaxis()->SetTitleOffset(0.38);
  hR13JetIdx_R->GetYaxis()->SetRangeUser(-1,1);
  hR13JetIdx_R->GetXaxis()->SetRangeUser(0,120);
  //hR13JetIdx_R->SetLineWidth(2);
  hR13JetIdx_R->GetYaxis()->SetLabelSize(0.09);
  hR13JetIdx_R->GetXaxis()->SetLabelSize(0.09);
  hR13JetIdx_R->GetYaxis()->SetNdivisions(5); 
  //hR13JetIdx_R->SetMarkerStyle(2); 
  hR13JetIdx_R->Draw(" ");
  /*
  double Highmass;
  if (trig == 2 || trig == 1) Highmass = 90;
  else Highmass = 50;
  TF1 *MassRatioFit = new TF1("MassRatioFit", "pol0", 13, Highmass);
  hR13JetIdx_R->Fit("MassRatioFit", "RW");
  MassRatioFit->Draw("same");
*/

  c0->cd(2);
  //c0->cd(2)->SetLogy();
  TPad *pad020 = new TPad("pad020","pad020", 0.0,0.3,1.0,1.0);
  pad020->SetLogy();
  pad020->SetBottomMargin(0);
  pad020->Draw();
  pad020->cd();
  if(REBIN) hR13JetPt[trig][ijet]->Rebin(10);
  hR13JetPt[trig][ijet]->SetTitle("Jets Transverse Momentum");
  hR13JetPt[trig][ijet]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hR13JetPt[trig][ijet]->SetLineWidth(2); hR13JetPt[trig][ijet]->SetLineColor(4);

  //cout << "Data -  Integral: " << hR13JetPt[trig][ijet]->Integral() << " --- Entries: " << hR13JetPt[trig][ijet]->GetEntries() << endl;

  hR13JetPt[trig][ijet]->Scale(1/hR13JetPt[trig][ijet]->Integral());

  //cout << "Data Integral: " << hR13JetPt[trig][ijet]->Integral() << endl;

  



  hR13JetPt[trig][ijet]->Draw("H");
  TLegend *legend0 = new TLegend(0.6,0.70,0.85,0.85);
  legend0->AddEntry(hR13JetPt[trig][ijet], "Run 15", "l");
  //
  hREmbJetPt[trig][ijet]->SetLineColor(2);

  //cout << "Embd -  Integral: " << hREmbJetPt[trig][ijet]->Integral() << " --- Entries: " << hREmbJetPt[trig][ijet]->GetEntries() << endl;

  hREmbJetPt[trig][ijet]->Scale(1/hREmbJetPt[trig][ijet]->Integral());

  //cout << "Embd Integral: " << hREmbJetPt[trig][ijet]->Integral() << endl;

  hREmbJetPt[trig][ijet]->Draw("same");
  legend0->AddEntry(hREmbJetPt[trig][ijet],"Run 15 Emb", "l");
  legend0->SetTextSize(0.05);
  legend0->SetBorderSize(0);
  legend0->SetFillStyle(0);
  legend0->Draw("hist p");

  TLatex* latex1 = new TLatex();
  latex1->SetTextFont(22);
  latex1->SetTextSize(0.1);
  latex1->DrawLatexNDC(0.6,0.5,trigger[trig]);
  latex1->DrawLatexNDC(0.6,0.6,topology[topol]);

  //Uncommnet this for the jet label on Jets plot
  if(ijet==0)  latex1->DrawLatexNDC(0.6,0.40,"High jet");
  else  latex1->DrawLatexNDC(0.6,0.40,"Low jet");
  //
  //////////
  c0->cd(2);
  TPad *pad021 = new TPad("pad021","pad021", 0,0.05,1.0,0.3);
  pad021->SetTopMargin(0);
  pad021->SetBottomMargin(0.2);
  pad021->Draw();
  pad021->cd();
  TH1D *hR13JetPt_R= (TH1D*) hR13JetPt[trig][ijet]->Clone();
  hR13JetPt_R->Add(hREmbJetPt[trig][ijet],-1);
  hR13JetPt_R->Divide(hR13JetPt[trig][ijet]);
  //hR13JetPt_R->Rebin(5); 
  hR13JetPt_R->SetBit(TH1::kNoTitle);
  hR13JetPt_R->SetLineColor(1); 
  hR13JetPt_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13JetPt_R->GetYaxis()->CenterTitle();
  hR13JetPt_R->GetYaxis()->SetTitleSize(0.07);
  hR13JetPt_R->GetYaxis()->SetTitleOffset(0.38);
  //hR13JetPt_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  hR13JetPt_R->GetYaxis()->SetRangeUser(-1,1);
  //hR13JetPt_R->SetLineWidth(2);
  hR13JetPt_R->GetYaxis()->SetLabelSize(0.09);
  hR13JetPt_R->GetXaxis()->SetLabelSize(0.09);
  hR13JetPt_R->GetXaxis()->SetTitleSize(0.07);
  hR13JetPt_R->GetYaxis()->SetNdivisions(5); 
  //hR13JetPt_R->SetMarkerStyle(2);
  hR13JetPt_R->Draw(" ");
  

  c0->cd(3);
  //c0->cd(3)->SetLogy();
  TPad *pad030 = new TPad("pad030","pad030", 0.0,0.3,1.0,1.0);
  pad030->SetLogy();
  pad030->SetBottomMargin(0);
  pad030->Draw();
  pad030->cd();
  hR13JetRt[trig][ijet]->SetTitle("Jets Neutral Energy (R_{T})");
  hR13JetRt[trig][ijet]->SetLineWidth(2); hR13JetRt[trig][ijet]->SetLineColor(4);
  hR13JetRt[trig][ijet]->Scale(1/hR13JetRt[trig][ijet]->Integral());
  hR13JetRt[trig][ijet]->Draw("H");
  //
  hREmbJetRt[trig][ijet]->SetLineColor(2);
  hREmbJetRt[trig][ijet]->Scale(1/hREmbJetRt[trig][ijet]->Integral());
  hREmbJetRt[trig][ijet]->Draw("same");
  //////////
  c0->cd(3);
  TPad *pad031 = new TPad("pad031","pad031", 0,0.05,1.0,0.3);
  pad031->SetTopMargin(0);
  pad031->SetBottomMargin(0.2);
  pad031->Draw();
  pad031->cd();
  TH1D *hR13JetRt_R= (TH1D*) hR13JetRt[trig][ijet]->Clone();
  hR13JetRt_R->Add(hREmbJetRt[trig][ijet],-1);
  hR13JetRt_R->Divide(hR13JetRt[trig][ijet]);
  //hR13JetRt_R->Rebin(5);
  hR13JetRt_R->SetBit(TH1::kNoTitle);
  hR13JetRt_R->SetLineColor(1); 
  hR13JetRt_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13JetRt_R->GetYaxis()->CenterTitle();
  hR13JetRt_R->GetYaxis()->SetTitleSize(0.07);
  hR13JetRt_R->GetYaxis()->SetTitleOffset(0.38);
  hR13JetRt_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13JetRt_R->SetLineWidth(2);
  hR13JetRt_R->GetYaxis()->SetLabelSize(0.09);
  hR13JetRt_R->GetXaxis()->SetLabelSize(0.09);
  hR13JetRt_R->GetYaxis()->SetNdivisions(5); 
  //hR13JetRt_R->SetMarkerStyle(2);
  hR13JetRt_R->Draw(" ");
  
  c0->cd(4);
  //c0->SetLogy();
  TPad *pad040 = new TPad("pad040","pad040", 0.0,0.3,1.0,1.0);
  //pad020->SetLogy();
  pad040->SetBottomMargin(0);
  pad040->Draw();
  pad040->cd();
  hR13JetEta[trig][ijet]->SetTitle("Jets #eta");
  hR13JetEta[trig][ijet]->GetXaxis()->SetTitle("#eta");
  hR13JetEta[trig][ijet]->SetLineWidth(2); hR13JetEta[trig][ijet]->SetLineColor(4);
  hR13JetEta[trig][ijet]->Scale(1/hR13JetEta[trig][ijet]->Integral());
  hR13JetEta[trig][ijet]->SetMaximum(0.035);
  hR13JetEta[trig][ijet]->Draw("H");
  //
  hREmbJetEta[trig][ijet]->SetLineColor(2);
  hREmbJetEta[trig][ijet]->Scale(1/hREmbJetEta[trig][ijet]->Integral());
  hREmbJetEta[trig][ijet]->Draw("same");
  //////////
  c0->cd(4);
  TPad *pad041 = new TPad("pad041","pad041", 0,0.05,1.0,0.3);
  pad041->SetTopMargin(0);
  pad041->SetBottomMargin(0.2);
  pad041->Draw();
  pad041->cd();
  TH1D *hR13JetEta_R= (TH1D*) hR13JetEta[trig][ijet]->Clone();
  hR13JetEta_R->Add(hREmbJetEta[trig][ijet],-1);
  hR13JetEta_R->Divide(hR13JetEta[trig][ijet]);
  //hR13JetEta_R->Rebin(2);
  hR13JetEta_R->SetBit(TH1::kNoTitle);
  hR13JetEta_R->SetLineColor(1); 
  hR13JetEta_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13JetEta_R->GetYaxis()->CenterTitle();
  hR13JetEta_R->GetYaxis()->SetTitleSize(0.07);
  hR13JetEta_R->GetYaxis()->SetTitleOffset(0.38);
  hR13JetEta_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13JetEta_R->SetLineWidth(2);
  hR13JetEta_R->GetYaxis()->SetLabelSize(0.09);
  hR13JetEta_R->GetXaxis()->SetLabelSize(0.09);
  hR13JetEta_R->GetYaxis()->SetNdivisions(5); 
  //hR13JetEta_R->SetMarkerStyle(2);
  hR13JetEta_R->Draw(" ");

  c0->cd(5);
  //c0->SetLogy();
  TPad *pad050 = new TPad("pad050","pad050", 0.0,0.3,1.0,1.0);
  //pad050->SetLogy();
  pad050->SetBottomMargin(0);
  pad050->Draw();
  pad050->cd();
  hR13JetPhi[trig][ijet]->SetTitle("Jets #phi");
  hR13JetPhi[trig][ijet]->GetXaxis()->SetTitle("#phi");
  hR13JetPhi[trig][ijet]->SetLineWidth(2); hR13JetPhi[trig][ijet]->SetLineColor(4);
  hR13JetPhi[trig][ijet]->Scale(1/hR13JetPhi[trig][ijet]->Integral());
  hR13JetPhi[trig][ijet]->SetMinimum(0.001);
  hR13JetPhi[trig][ijet]->SetMaximum(0.07);
  hR13JetPhi[trig][ijet]->Draw("H");
  //
  hREmbJetPhi[trig][ijet]->SetLineColor(2);
  hREmbJetPhi[trig][ijet]->Scale(1/hREmbJetPhi[trig][ijet]->Integral());
  hREmbJetPhi[trig][ijet]->Draw("same");
  //////////
  c0->cd(5);
  TPad *pad051 = new TPad("pad051","pad051", 0,0.05,1.0,0.3);
  pad051->SetTopMargin(0);
  pad051->SetBottomMargin(0.2);
  pad051->Draw();
  pad051->cd();
  TH1D *hR13JetPhi_R= (TH1D*) hR13JetPhi[trig][ijet]->Clone();
  hR13JetPhi_R->Add(hREmbJetPhi[trig][ijet],-1);
  hR13JetPhi_R->Divide(hR13JetPhi[trig][ijet]);
  //hR13JetPhi_R->Rebin(2);
  hR13JetPhi_R->SetBit(TH1::kNoTitle);
  hR13JetPhi_R->SetLineColor(1); 
  hR13JetPhi_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13JetPhi_R->GetYaxis()->CenterTitle();
  hR13JetPhi_R->GetYaxis()->SetTitleSize(0.07);
  hR13JetPhi_R->GetYaxis()->SetTitleOffset(0.38);
  hR13JetPhi_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13JetPhi_R->SetLineWidth(2);
  hR13JetPhi_R->GetYaxis()->SetLabelSize(0.09);
  hR13JetPhi_R->GetXaxis()->SetLabelSize(0.09);
  hR13JetPhi_R->GetYaxis()->SetNdivisions(5); 
  //hR13JetPhi_R->SetMarkerStyle(2);
  hR13JetPhi_R->Draw(" ");

  c0->cd(6);
  //c0->SetLogy();
  TPad *pad060 = new TPad("pad060","pad060", 0.0,0.3,1.0,1.0);
  //pad020->SetLogy();
  pad060->SetBottomMargin(0);
  pad060->Draw();
  pad060->cd();
  hR13JetDet[trig][ijet]->SetTitle("Jets detector #eta");
  hR13JetDet[trig][ijet]->GetXaxis()->SetTitle("#eta_{det}");
  hR13JetDet[trig][ijet]->SetLineWidth(2); hR13JetDet[trig][ijet]->SetLineColor(4);
  hR13JetDet[trig][ijet]->Scale(1/hR13JetDet[trig][ijet]->Integral());
  hR13JetDet[trig][ijet]->SetMaximum(0.04);
  hR13JetDet[trig][ijet]->Draw("H");
  //
  hREmbJetDet[trig][ijet]->SetLineColor(2);
  hREmbJetDet[trig][ijet]->Scale(1/hREmbJetDet[trig][ijet]->Integral());
  hREmbJetDet[trig][ijet]->Draw("same");
  //////////
  c0->cd(6);
  TPad *pad061 = new TPad("pad061","pad061", 0,0.05,1.0,0.3);
  pad061->SetTopMargin(0);
  pad061->SetBottomMargin(0.2);
  pad061->Draw();
  pad061->cd();
  TH1D *hR13JetDet_R= (TH1D*) hR13JetDet[trig][ijet]->Clone();
  hR13JetDet_R->Add(hREmbJetDet[trig][ijet],-1);
  hR13JetDet_R->Divide(hR13JetDet[trig][ijet]);
  //hR13JetDet_R->Rebin(2);
  hR13JetDet_R->SetBit(TH1::kNoTitle);
  hR13JetDet_R->SetLineColor(1); 
  hR13JetDet_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13JetDet_R->GetYaxis()->CenterTitle();
  hR13JetDet_R->GetYaxis()->SetTitleSize(0.07);
  hR13JetDet_R->GetYaxis()->SetTitleOffset(0.38);
  hR13JetDet_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13JetDet_R->SetLineWidth(2);
  hR13JetDet_R->GetYaxis()->SetLabelSize(0.09);
  hR13JetDet_R->GetXaxis()->SetLabelSize(0.09);
  hR13JetDet_R->GetYaxis()->SetNdivisions(5); 
  //hR13JetDet_R->SetMarkerStyle(2);
  hR13JetDet_R->Draw(" ");

  //c0->SaveAs("/star/u/aquinter/Run15/InclusiveJets/Compare/JetPt_compare.png");

  c0->Draw();
  //////ENDJets Plots <--3--
 

  //////Track Plots --4-->
  TCanvas *c1 = new TCanvas("c1","Tracks",0,0,1300,900);
  c1->cd();
  c1->Divide(3,2);
  
  c1->cd(1);
  //c1->cd(1)->SetLogy();
  TPad *pad110 = new TPad("pad110","pad110", 0.0,0.3,1.0,1.0);
  pad110->SetLogy();
  pad110->SetBottomMargin(0);
  pad110->Draw();
  pad110->cd();
  hR13TrackIdx[trig][ijet]->SetTitle("Tracks per jet");
  hR13TrackIdx[trig][ijet]->SetLineWidth(2); hR13TrackIdx[trig][ijet]->SetLineColor(4);
  hR13TrackIdx[trig][ijet]->SetMinimum(0.1);
  hR13TrackIdx[trig][ijet]->Scale(1/hR13TrackIdx[trig][ijet]->Integral());
  hR13TrackIdx[trig][ijet]->Draw("H");
  //TLatex* latex1 = new TLatex();
  //latex1->SetTextFont(22);
  //latex1->SetTextSize(0.1);
  latex1->DrawLatexNDC(0.6,0.6,trigger[trig]);
  latex1->DrawLatexNDC(0.6,0.7,topology[topol]);
 if(ijet==0)  latex1->DrawLatexNDC(0.6,0.50,"High jet");
  else  latex1->DrawLatexNDC(0.6,0.50,"Low jet");
  //
  hREmbTrackIdx[trig][ijet]->SetLineColor(2);
  hREmbTrackIdx[trig][ijet]->Scale(1/hREmbTrackIdx[trig][ijet]->Integral());
  hREmbTrackIdx[trig][ijet]->Draw("same");
  //////////
  c1->cd(1);
  TPad *pad111 = new TPad("pad111","pad111", 0,0.05,1.0,0.3);
  pad111->SetTopMargin(0);
  pad111->SetBottomMargin(0.2);
  pad111->Draw();
  pad111->cd();
  TH1D *hR13TrackIdx_R= (TH1D*) hR13TrackIdx[trig][ijet]->Clone();
  hR13TrackIdx_R->Add(hREmbTrackIdx[trig][ijet],-1);
  hR13TrackIdx_R->Divide(hR13TrackIdx[trig][ijet]);
  //hR13TrackIdx_R->Add(hREmbTrackIdx[trig][ijet],-1);
  //hR13TrackIdx_R->Divide(hR13TrackIdx[trig][ijet]);
  hR13TrackIdx_R->SetBit(TH1::kNoTitle);
  hR13TrackIdx_R->SetLineColor(1); 
  hR13TrackIdx_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TrackIdx_R->GetYaxis()->CenterTitle();
  hR13TrackIdx_R->GetYaxis()->SetTitleSize(0.07);
  hR13TrackIdx_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TrackIdx_R->GetYaxis()->SetRangeUser(-1,1);
  //hR13TrackIdx_R->SetLineWidth(2);
  hR13TrackIdx_R->GetYaxis()->SetLabelSize(0.09);
  hR13TrackIdx_R->GetXaxis()->SetLabelSize(0.09);
  hR13TrackIdx_R->GetYaxis()->SetNdivisions(5); 
  //hR13TrackIdx_R->SetMarkerStyle(2);
  hR13TrackIdx_R->Draw(" ");

  c1->cd(2);
  //c1->cd(2)->SetLogy();
  TPad *pad120 = new TPad("pad120","pad120", 0.0,0.3,1.0,1.0);
  pad120->SetLogy();
  pad120->SetBottomMargin(0);
  pad120->Draw();
  pad120->cd();
  hR13TrackPt[trig][ijet]->Rebin(5);                   /////////////////////REBIN
  hR13TrackPt[trig][ijet]->SetTitle("Tracks Transverse Momentum");
  hR13TrackPt[trig][ijet]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hR13TrackPt[trig][ijet]->SetLineWidth(2); hR13TrackPt[trig][ijet]->SetLineColor(4);
  hR13TrackPt[trig][ijet]->Scale(1/hR13TrackPt[trig][ijet]->Integral());
  hR13TrackPt[trig][ijet]->Draw("H");
  //TLegend *legend1 = new TLegend(0.6,0.70,0.85,0.85);
  //legend1->AddEntry(hR13TrackPt[trig][ijet], "Run 15", "l");
  // 
  hREmbTrackPt[trig][ijet]->Rebin(5);                   /////////////////////REBIN
  hREmbTrackPt[trig][ijet]->SetLineColor(2);
  hREmbTrackPt[trig][ijet]->Scale(1/hREmbTrackPt[trig][ijet]->Integral());
  hREmbTrackPt[trig][ijet]->Draw("same");
  legend0->Draw();
  //////////
  c1->cd(2);
  TPad *pad121 = new TPad("pad121","pad121", 0,0.05,1.0,0.3);
  pad121->SetTopMargin(0);
  pad121->SetBottomMargin(0.2);
  pad121->Draw();
  pad121->cd();
  TH1D *hR13TrackPt_R= (TH1D*) hR13TrackPt[trig][ijet]->Clone();
  hR13TrackPt_R->Add(hREmbTrackPt[trig][ijet],-1);
  hR13TrackPt_R->Divide(hR13TrackPt[trig][ijet]);
  //hR13TrackPt_R->Rebin(10);
  hR13TrackPt_R->SetBit(TH1::kNoTitle);
  hR13TrackPt_R->SetLineColor(1); 
  hR13TrackPt_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TrackPt_R->GetYaxis()->CenterTitle();
  hR13TrackPt_R->GetYaxis()->SetTitleSize(0.07);
  hR13TrackPt_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TrackPt_R->GetYaxis()->SetRangeUser(-1,1);
  //hR13TrackPt_R->SetLineWidth(2);
  hR13TrackPt_R->GetYaxis()->SetLabelSize(0.09);
  hR13TrackPt_R->GetXaxis()->SetLabelSize(0.09);
  hR13TrackPt_R->GetYaxis()->SetNdivisions(5);
  hR13TrackPt_R->GetXaxis()->SetTitleSize(0.07); 
  //hR13TrackPt_R->SetMarkerStyle(2);
  hR13TrackPt_R->Draw(" ");

  c1->cd(3);
  //c1->cd(3)->SetLogy();
  TPad *pad130 = new TPad("pad130","pad130", 0.0,0.3,1.0,1.0);
  //pad130->SetLogy();
  pad130->SetBottomMargin(0);
  pad130->Draw();
  pad130->cd();
  hR13TrackDcaXY[trig][ijet]->SetTitle("Tracks DCA_{XY}");
  hR13TrackDcaXY[trig][ijet]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
  hR13TrackDcaXY[trig][ijet]->SetLineWidth(2); hR13TrackDcaXY[trig][ijet]->SetLineColor(4);
  hR13TrackDcaXY[trig][ijet]->Scale(1/hR13TrackDcaXY[trig][ijet]->Integral());
  hR13TrackDcaXY[trig][ijet]->SetMaximum(0.05);
  hR13TrackDcaXY[trig][ijet]->GetXaxis()->SetRangeUser(-2,2);
  hR13TrackDcaXY[trig][ijet]->Draw("H");
  //
  hREmbTrackDcaXY[trig][ijet]->SetLineColor(2);
  hREmbTrackDcaXY[trig][ijet]->Scale(1/hREmbTrackDcaXY[trig][ijet]->Integral());
  hREmbTrackDcaXY[trig][ijet]->Draw("same");
  //////////
  c1->cd(3);
  TPad *pad131 = new TPad("pad131","pad131", 0,0.05,1.0,0.3);
  pad131->SetTopMargin(0);
  pad131->SetBottomMargin(0.2);
  pad131->Draw();
  pad131->cd();
  TH1D *hR13TrackDcaXY_R= (TH1D*) hR13TrackDcaXY[trig][ijet]->Clone();
  hR13TrackDcaXY_R->Add(hREmbTrackDcaXY[trig][ijet],-1);
  hR13TrackDcaXY_R->Divide(hR13TrackDcaXY[trig][ijet]);
  //hR13TrackDcaXY_R->Rebin(10);
  hR13TrackDcaXY_R->SetBit(TH1::kNoTitle);
  hR13TrackDcaXY_R->SetLineColor(1); 
  hR13TrackDcaXY_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TrackDcaXY_R->GetYaxis()->CenterTitle();
  hR13TrackDcaXY_R->GetYaxis()->SetTitleSize(0.07);
  hR13TrackDcaXY_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TrackDcaXY_R->GetXaxis()->SetRangeUser(-2,2);
  hR13TrackDcaXY_R->GetYaxis()->SetRangeUser(-1,1);
  //hR13TrackDcaXY_R->SetLineWidth(2);
  hR13TrackDcaXY_R->GetYaxis()->SetLabelSize(0.09);
  hR13TrackDcaXY_R->GetXaxis()->SetLabelSize(0.09);
  hR13TrackDcaXY_R->GetYaxis()->SetNdivisions(5); 
  hR13TrackDcaXY_R->GetXaxis()->SetTitleSize(0.07); 
  //hR13TrackDcaXY_R->SetMarkerStyle(2);
  hR13TrackDcaXY_R->Draw(" ");

  c1->cd(4);
  //c1->SetLogy();
  TPad *pad140 = new TPad("pad140","pad140", 0.0,0.3,1.0,1.0);
  //pad140->SetLogy();
  pad140->SetBottomMargin(0);
  pad140->Draw();
  pad140->cd();
  hR13TrackEta[trig][ijet]->SetTitle("Tracks #eta");
  hR13TrackEta[trig][ijet]->GetXaxis()->SetTitle("#eta");
  hR13TrackEta[trig][ijet]->SetLineWidth(2); hR13TrackEta[trig][ijet]->SetLineColor(4);
  hR13TrackEta[trig][ijet]->Scale(1/hR13TrackEta[trig][ijet]->Integral());
  hR13TrackEta[trig][ijet]->SetMaximum(0.035);
  hR13TrackEta[trig][ijet]->Draw("H");
  //
  hREmbTrackEta[trig][ijet]->SetLineColor(2);
  hREmbTrackEta[trig][ijet]->Scale(1/hREmbTrackEta[trig][ijet]->Integral());
  hREmbTrackEta[trig][ijet]->Draw("same");
  //////////
  c1->cd(4);
  TPad *pad141 = new TPad("pad141","pad141", 0,0.05,1.0,0.3);
  pad141->SetTopMargin(0);
  pad141->SetBottomMargin(0.2);
  pad141->Draw();
  pad141->cd();
  TH1D *hR13TrackEta_R= (TH1D*) hR13TrackEta[trig][ijet]->Clone();
  hR13TrackEta_R->Add(hREmbTrackEta[trig][ijet],-1);
  hR13TrackEta_R->Divide(hR13TrackEta[trig][ijet]);
  //hR13TrackEta_R->Rebin(2);
  hR13TrackEta_R->SetBit(TH1::kNoTitle);
  hR13TrackEta_R->SetLineColor(1); 
  hR13TrackEta_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TrackEta_R->GetYaxis()->CenterTitle();
  hR13TrackEta_R->GetYaxis()->SetTitleSize(0.07);
  hR13TrackEta_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TrackEta_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13TrackEta_R->SetLineWidth(2);
  hR13TrackEta_R->GetYaxis()->SetLabelSize(0.09);
  hR13TrackEta_R->GetXaxis()->SetLabelSize(0.09);
  hR13TrackEta_R->GetYaxis()->SetNdivisions(5); 
  //hR13TrackEta_R->SetMarkerStyle(2);
  hR13TrackEta_R->Draw(" ");

  c1->cd(5);
  //c1->SetLogy();
  TPad *pad150 = new TPad("pad150","pad150", 0.0,0.3,1.0,1.0);
  //pad150->SetLogy();
  pad150->SetBottomMargin(0);
  pad150->Draw();
  pad150->cd();
  hR13TrackPhi[trig][ijet]->SetTitle("Tracks #phi");
  hR13TrackPhi[trig][ijet]->GetXaxis()->SetTitle("#phi");
  hR13TrackPhi[trig][ijet]->SetLineWidth(2); hR13TrackPhi[trig][ijet]->SetLineColor(4);
  hR13TrackPhi[trig][ijet]->SetMinimum(0.1);
  hR13TrackPhi[trig][ijet]->Scale(1/hR13TrackPhi[trig][ijet]->Integral());
  hR13TrackPhi[trig][ijet]->SetMinimum(0.001);
  hR13TrackPhi[trig][ijet]->SetMaximum(0.06);
  hR13TrackPhi[trig][ijet]->Draw("H");
  //
  hREmbTrackPhi[trig][ijet]->SetLineColor(2);
  hREmbTrackPhi[trig][ijet]->Scale(1/hREmbTrackPhi[trig][ijet]->Integral());
  hREmbTrackPhi[trig][ijet]->Draw("same");
  //////////
  c1->cd(5);
  TPad *pad151 = new TPad("pad151","pad151", 0,0.05,1.0,0.3);
  pad151->SetTopMargin(0);
  pad151->SetBottomMargin(0.2);
  pad151->Draw();
  pad151->cd();
  TH1D *hR13TrackPhi_R= (TH1D*) hR13TrackPhi[trig][ijet]->Clone();
  hR13TrackPhi_R->Add(hREmbTrackPhi[trig][ijet],-1);
  hR13TrackPhi_R->Divide(hR13TrackPhi[trig][ijet]);
  //hR13TrackPhi_R->Rebin(2);
  hR13TrackPhi_R->SetBit(TH1::kNoTitle);
  hR13TrackPhi_R->SetLineColor(1); 
  hR13TrackPhi_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TrackPhi_R->GetYaxis()->CenterTitle();
  hR13TrackPhi_R->GetYaxis()->SetTitleSize(0.07);
  hR13TrackPhi_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TrackPhi_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13TrackPhi_R->SetLineWidth(2);
  hR13TrackPhi_R->GetYaxis()->SetLabelSize(0.09);
  hR13TrackPhi_R->GetXaxis()->SetLabelSize(0.09);
  hR13TrackPhi_R->GetYaxis()->SetNdivisions(5); 
  //hR13TrackPhi_R->SetMarkerStyle(2);
  hR13TrackPhi_R->Draw(" ");

  c1->cd(6);
  //c1->SetLogy();
  TPad *pad160 = new TPad("pad160","pad160", 0.0,0.3,1.0,1.0);
  //pad160->SetLogy();
  pad160->SetBottomMargin(0);
  pad160->Draw();
  pad160->cd();
  hR13TrackDcaZ[trig][ijet]->SetTitle("Tracks DCA_{Z}");
  hR13TrackDcaZ[trig][ijet]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
  hR13TrackDcaZ[trig][ijet]->SetLineWidth(2); hR13TrackDcaZ[trig][ijet]->SetLineColor(4);
  hR13TrackDcaZ[trig][ijet]->Scale(1/hR13TrackDcaZ[trig][ijet]->Integral());
  hR13TrackDcaZ[trig][ijet]->SetMaximum(0.06);
  hR13TrackDcaZ[trig][ijet]->Draw("H");
  //
  hREmbTrackDcaZ[trig][ijet]->SetLineColor(2);
  hREmbTrackDcaZ[trig][ijet]->Scale(1/hREmbTrackDcaZ[trig][ijet]->Integral());
  hREmbTrackDcaZ[trig][ijet]->Draw("same");
  //////////
  c1->cd(6);
  TPad *pad161 = new TPad("pad161","pad161", 0,0.05,1.0,0.3);
  pad161->SetTopMargin(0);
  pad161->SetBottomMargin(0.2);
  pad161->Draw();
  pad161->cd();
  TH1D *hR13TrackDcaZ_R= (TH1D*) hR13TrackDcaZ[trig][ijet]->Clone();
  hR13TrackDcaZ_R->Add(hREmbTrackDcaZ[trig][ijet],-1);
  hR13TrackDcaZ_R->Divide(hR13TrackDcaZ[trig][ijet]);
  //hR13TrackDcaZ_R->Rebin(10);
  hR13TrackDcaZ_R->SetBit(TH1::kNoTitle);
  hR13TrackDcaZ_R->SetLineColor(1); 
  hR13TrackDcaZ_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TrackDcaZ_R->GetYaxis()->CenterTitle();
  hR13TrackDcaZ_R->GetYaxis()->SetTitleSize(0.07);
  hR13TrackDcaZ_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TrackDcaZ_R->GetYaxis()->SetRangeUser(-1,1);
  //hR13TrackDcaZ_R->SetLineWidth(2);
  hR13TrackDcaZ_R->GetYaxis()->SetLabelSize(0.09);
  hR13TrackDcaZ_R->GetXaxis()->SetLabelSize(0.09);
  hR13TrackDcaZ_R->GetYaxis()->SetNdivisions(5);
  hR13TrackDcaZ_R->GetXaxis()->SetTitleSize(0.07);  
  //hR13TrackDcaZ_R->SetMarkerStyle(2);
  hR13TrackDcaZ_R->Draw(" ");

  //c1->SaveAs("/star/u/aquinter/Run15/InclusiveJets/Compare/TrackPt_compare.png");

  c1->Draw();
  ///////END Plot Tracks<--4--
  
  
  //////Tower Plots --5-->
  TCanvas *c2 = new TCanvas("c2","Towers",0,0,1300,900);
  c2->cd();
  c2->Divide(3,2);
  
  c2->cd(1);
  //c2->cd(1)->SetLogy();
  TPad *pad210 = new TPad("pad210","pad210", 0.0,0.3,1.0,1.0);
  pad210->SetLogy();
  pad210->SetBottomMargin(0);
  pad210->Draw();
  pad210->cd();
  hR13TowerIdx[trig][ijet]->SetTitle("Towers per jet");
  //hTowerIdx[trig][ijet]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hR13TowerIdx[trig][ijet]->SetLineWidth(2); hR13TowerIdx[trig][ijet]->SetLineColor(4);
  hR13TowerIdx[trig][ijet]->SetMinimum(0.1);
  hR13TowerIdx[trig][ijet]->Scale(1/hR13TowerIdx[trig][ijet]->Integral());
  hR13TowerIdx[trig][ijet]->Draw("H");
  latex1->DrawLatexNDC(0.6,0.6,trigger[trig]);
  latex1->DrawLatexNDC(0.6,0.7,topology[topol]);
 if(ijet==0)  latex1->DrawLatexNDC(0.6,0.50,"High jet");
  else  latex1->DrawLatexNDC(0.6,0.50,"Low jet");
  //
  hREmbTowerIdx[trig][ijet]->SetLineColor(2);
  hREmbTowerIdx[trig][ijet]->Scale(1/hREmbTowerIdx[trig][ijet]->Integral());
  hREmbTowerIdx[trig][ijet]->Draw("same");
  //////////
  c2->cd(1);
  TPad *pad211 = new TPad("pad211","pad211", 0,0.05,1.0,0.3);
  pad211->SetTopMargin(0);
  pad211->SetBottomMargin(0.2);
  pad211->Draw();
  pad211->cd();
  TH1D *hR13TowerIdx_R= (TH1D*) hR13TowerIdx[trig][ijet]->Clone();
  hR13TowerIdx_R->Add(hREmbTowerIdx[trig][ijet],-1);
  hR13TowerIdx_R->Divide(hR13TowerIdx[trig][ijet]);
  hR13TowerIdx_R->SetBit(TH1::kNoTitle);
  hR13TowerIdx_R->SetLineColor(1); 
  hR13TowerIdx_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TowerIdx_R->GetYaxis()->CenterTitle();
  hR13TowerIdx_R->GetYaxis()->SetTitleSize(0.07);
  hR13TowerIdx_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TowerIdx_R->GetYaxis()->SetRangeUser(-2,2);
  //hR13TowerIdx_R->SetLineWidth(2);
  hR13TowerIdx_R->GetYaxis()->SetLabelSize(0.09);
  hR13TowerIdx_R->GetXaxis()->SetLabelSize(0.09);
  hR13TowerIdx_R->GetYaxis()->SetNdivisions(5); 
  //hR13TowerIdx_R->SetMarkerStyle(2);
  hR13TowerIdx_R->Draw(" ");


  c2->cd(2);
  //c2->cd(2)->SetLogy();
  TPad *pad220 = new TPad("pad220","pad220", 0.0,0.3,1.0,1.0);
  pad220->SetLogy();
  pad220->SetBottomMargin(0);
  pad220->Draw();
  pad220->cd();  
  hR13TowerPt[trig][ijet]->SetTitle("Towers Transverse Energy");        //Tower Pt does not exist is Tower ET
  hR13TowerPt[trig][ijet]->GetXaxis()->SetTitle("E_{T} (GeV)");
  hR13TowerPt[trig][ijet]->SetLineWidth(2); hR13TowerPt[trig][ijet]->SetLineColor(4);
  hR13TowerPt[trig][ijet]->Scale(1/hR13TowerPt[trig][ijet]->Integral());
  hR13TowerPt[trig][ijet]->Draw("H");
  //TLegend *legend0 = new TLegend(0.6,0.70,0.85,0.85);
  //legend0->AddEntry(hR13TowerPt[trig][ijet], "Run 15", "l");
  //
  hREmbTowerPt[trig][ijet]->SetLineColor(2);
  hREmbTowerPt[trig][ijet]->Scale(1/hREmbTowerPt[trig][ijet]->Integral());
  hREmbTowerPt[trig][ijet]->Draw("same");
  legend0->Draw();
  //////////
  c2->cd(2);
  TPad *pad221 = new TPad("pad221","pad221", 0,0.05,1.0,0.3);
  pad221->SetTopMargin(0);
  pad221->SetBottomMargin(0.2);
  pad221->Draw();
  pad221->cd();
  TH1D *hR13TowerPt_R= (TH1D*) hR13TowerPt[trig][ijet]->Clone();
  hR13TowerPt_R->Add(hREmbTowerPt[trig][ijet],-1);
  hR13TowerPt_R->Divide(hR13TowerPt[trig][ijet]);
  //hR13TowerPt_R->Rebin(2);
  hR13TowerPt_R->SetBit(TH1::kNoTitle);
  hR13TowerPt_R->SetLineColor(1); 
  hR13TowerPt_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TowerPt_R->GetYaxis()->CenterTitle();
  hR13TowerPt_R->GetYaxis()->SetTitleSize(0.07);
  hR13TowerPt_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TowerPt_R->GetYaxis()->SetRangeUser(-2,2);
  //hR13TowerPt_R->SetLineWidth(2);
  hR13TowerPt_R->GetYaxis()->SetLabelSize(0.09);
  hR13TowerPt_R->GetXaxis()->SetLabelSize(0.09);
  hR13TowerPt_R->GetXaxis()->SetTitleSize(0.07);
  hR13TowerPt_R->GetYaxis()->SetNdivisions(5); 
  //hR13TowerPt_R->SetMarkerStyle(2);
  hR13TowerPt_R->Draw(" ");
 
  c2->cd(3);
  //c2->cd(3)->SetLogy();
  TPad *pad230 = new TPad("pad230","pad230", 0.0,0.3,1.0,1.0);
  pad230->SetLogy();
  pad230->SetBottomMargin(0);
  pad230->Draw();
  pad230->cd();
  hR13TowerE[trig][ijet]->SetTitle("Towers Energy");
  hR13TowerE[trig][ijet]->GetXaxis()->SetTitle("E (GeV)");
  hR13TowerE[trig][ijet]->SetLineWidth(2); hR13TowerE[trig][ijet]->SetLineColor(4);
  hR13TowerE[trig][ijet]->Scale(1/hR13TowerE[trig][ijet]->Integral());
  hR13TowerE[trig][ijet]->Draw("H");
  //
  hREmbTowerE[trig][ijet]->SetLineColor(2);
  hREmbTowerE[trig][ijet]->Scale(1/hREmbTowerE[trig][ijet]->Integral());
  hREmbTowerE[trig][ijet]->Draw("same");
  //////////
  c2->cd(3);
  TPad *pad231 = new TPad("pad231","pad231", 0,0.05,1.0,0.3);
  pad231->SetTopMargin(0);
  pad231->SetBottomMargin(0.2);
  pad231->Draw();
  pad231->cd();
  TH1D *hR13TowerE_R= (TH1D*) hR13TowerE[trig][ijet]->Clone();
  hR13TowerE_R->Add(hREmbTowerE[trig][ijet],-1);
  hR13TowerE_R->Divide(hR13TowerE[trig][ijet]);
  //hR13TowerE_R->Rebin(2);
  hR13TowerE_R->SetBit(TH1::kNoTitle);
  hR13TowerE_R->SetLineColor(1); 
  hR13TowerE_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TowerE_R->GetYaxis()->CenterTitle();
  hR13TowerE_R->GetYaxis()->SetTitleSize(0.07);
  hR13TowerE_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TowerE_R->GetYaxis()->SetRangeUser(-1,1);
  //hR13TowerE_R->SetLineWidth(2);
  hR13TowerE_R->GetYaxis()->SetLabelSize(0.09);
  hR13TowerE_R->GetXaxis()->SetLabelSize(0.09);
  hR13TowerE_R->GetXaxis()->SetTitleSize(0.07);
  hR13TowerE_R->GetYaxis()->SetNdivisions(5); 
  //hR13TowerE_R->SetMarkerStyle(2);
  hR13TowerE_R->Draw(" ");

  c2->cd(4);
  //c1->SetLogy();
  TPad *pad240 = new TPad("pad240","pad240", 0.0,0.3,1.0,1.0);
  //pad240->SetLogy();
  pad240->SetBottomMargin(0);
  pad240->Draw();
  pad240->cd();
  hR13TowerEta[trig][ijet]->SetTitle("Towers #eta");
  hR13TowerEta[trig][ijet]->GetXaxis()->SetTitle("#eta");
  hR13TowerEta[trig][ijet]->SetLineWidth(2); hR13TowerEta[trig][ijet]->SetLineColor(4);
  hR13TowerEta[trig][ijet]->Scale(1/hR13TowerEta[trig][ijet]->Integral());
  hR13TowerEta[trig][ijet]->SetMaximum(0.035);
  hR13TowerEta[trig][ijet]->Draw("H");
  //
  hREmbTowerEta[trig][ijet]->SetLineColor(2);
  hREmbTowerEta[trig][ijet]->Scale(1/hREmbTowerEta[trig][ijet]->Integral());
  hREmbTowerEta[trig][ijet]->Draw("same");
  //////////
  c2->cd(4);
  TPad *pad241 = new TPad("pad241","pad241", 0,0.05,1.0,0.3);
  pad241->SetTopMargin(0);
  pad241->SetBottomMargin(0.2);
  pad241->Draw();
  pad241->cd();
  TH1D *hR13TowerEta_R= (TH1D*) hR13TowerEta[trig][ijet]->Clone();
  hR13TowerEta_R->Add(hREmbTowerEta[trig][ijet],-1);
  hR13TowerEta_R->Divide(hR13TowerEta[trig][ijet]);
  //hR13TowerEta_R->Rebin(2);
  hR13TowerEta_R->SetBit(TH1::kNoTitle);
  hR13TowerEta_R->SetLineColor(1); 
  hR13TowerEta_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TowerEta_R->GetYaxis()->CenterTitle();
  hR13TowerEta_R->GetYaxis()->SetTitleSize(0.07);
  hR13TowerEta_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TowerEta_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13TowerEta_R->SetLineWidth(2);
  hR13TowerEta_R->GetYaxis()->SetLabelSize(0.09);
  hR13TowerEta_R->GetXaxis()->SetLabelSize(0.09);
  hR13TowerEta_R->GetYaxis()->SetNdivisions(5); 
  //hR13TowerEta_R->SetMarkerStyle(2);
  hR13TowerEta_R->Draw(" ");

  c2->cd(5);
  //c1->SetLogy();
  TPad *pad250 = new TPad("pad250","pad250", 0.0,0.3,1.0,1.0);
  //pad250->SetLogy();
  pad250->SetBottomMargin(0);
  pad250->Draw();
  pad250->cd();
  hR13TowerPhi[trig][ijet]->SetTitle("Towers #phi");
  hR13TowerPhi[trig][ijet]->GetXaxis()->SetTitle("#phi");
  hR13TowerPhi[trig][ijet]->SetLineWidth(2); hR13TowerPhi[trig][ijet]->SetLineColor(4);
  hR13TowerPhi[trig][ijet]->SetMinimum(0.1);
  hR13TowerPhi[trig][ijet]->Scale(1/hR13TowerPhi[trig][ijet]->Integral());
  hR13TowerPhi[trig][ijet]->SetMinimum(0.001);
  hR13TowerPhi[trig][ijet]->SetMaximum(0.06);
  hR13TowerPhi[trig][ijet]->Draw("H");
  //
  hREmbTowerPhi[trig][ijet]->SetLineColor(2);
  hREmbTowerPhi[trig][ijet]->Scale(1/hREmbTowerPhi[trig][ijet]->Integral());
  hREmbTowerPhi[trig][ijet]->Draw("same");
  //////////
  c2->cd(5);
  TPad *pad251 = new TPad("pad251","pad251", 0,0.05,1.0,0.3);
  pad251->SetTopMargin(0);
  pad251->SetBottomMargin(0.2);
  pad251->Draw();
  pad251->cd();
  TH1D *hR13TowerPhi_R= (TH1D*) hR13TowerPhi[trig][ijet]->Clone();
  hR13TowerPhi_R->Add(hREmbTowerPhi[trig][ijet],-1);
  hR13TowerPhi_R->Divide(hR13TowerPhi[trig][ijet]);
  hR13TowerPhi_R->SetBit(TH1::kNoTitle);
  hR13TowerPhi_R->SetLineColor(1); 
  hR13TowerPhi_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TowerPhi_R->GetYaxis()->CenterTitle();
  hR13TowerPhi_R->GetYaxis()->SetTitleSize(0.07);
  hR13TowerPhi_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TowerPhi_R->GetYaxis()->SetRangeUser(-0.5,0.5);
  //hR13TowerPhi_R->SetLineWidth(2);
  hR13TowerPhi_R->GetYaxis()->SetLabelSize(0.09);
  hR13TowerPhi_R->GetXaxis()->SetLabelSize(0.09);
  hR13TowerPhi_R->GetYaxis()->SetNdivisions(5); 
  //hR13TowerPhi_R->SetMarkerStyle(2);
  hR13TowerPhi_R->Draw(" ");
  
  c2->cd(6);
  //c1->SetLogy();
  TPad *pad260 = new TPad("pad260","pad260", 0.0,0.3,1.0,1.0);
  //pad260->SetLogy();
  pad260->SetBottomMargin(0);
  pad260->Draw();
  pad260->cd();
  hR13TowerAdc[trig][ijet]->SetTitle("Towers Adc");
  hR13TowerAdc[trig][ijet]->SetLineWidth(2); hR13TowerAdc[trig][ijet]->SetLineColor(4);
  hR13TowerAdc[trig][ijet]->Scale(1/hR13TowerAdc[trig][ijet]->Integral());
  hR13TowerAdc[trig][ijet]->Draw("H");
  //
  hREmbTowerAdc[trig][ijet]->SetLineColor(2);
  hREmbTowerAdc[trig][ijet]->Scale(1/hREmbTowerAdc[trig][ijet]->Integral());
  hREmbTowerAdc[trig][ijet]->Draw("same");
  /////////
  c2->cd(6);
  TPad *pad261 = new TPad("pad261","pad261", 0,0.05,1.0,0.3);
  pad261->SetTopMargin(0);
  pad261->SetBottomMargin(0.2);
  pad261->Draw();
  pad261->cd();
  TH1D *hR13TowerAdc_R= (TH1D*) hR13TowerAdc[trig][ijet]->Clone();
  hR13TowerAdc_R->Add(hREmbTowerAdc[trig][ijet],-1);
  hR13TowerAdc_R->Divide(hR13TowerAdc[trig][ijet]);
  //hR13TowerAdc_R->Rebin(5);
  hR13TowerAdc_R->SetBit(TH1::kNoTitle);
  hR13TowerAdc_R->SetLineColor(1); 
  hR13TowerAdc_R->GetYaxis()->SetTitle("(Run15-Run15E)/Run15");
  hR13TowerAdc_R->GetYaxis()->CenterTitle();
  hR13TowerAdc_R->GetYaxis()->SetTitleSize(0.07);
  hR13TowerAdc_R->GetYaxis()->SetTitleOffset(0.38);
  hR13TowerAdc_R->GetYaxis()->SetRangeUser(-2,2);
  //hR13TowerAdc_R->SetLineWidth(2);
  hR13TowerAdc_R->GetYaxis()->SetLabelSize(0.09);
  hR13TowerAdc_R->GetXaxis()->SetLabelSize(0.09);
  hR13TowerAdc_R->GetYaxis()->SetNdivisions(5); 
  //hR13TowerAdc_R->SetMarkerStyle(2);
  hR13TowerAdc_R->Draw(" ");

  c2->Draw();
  //END Plot Towers<--6--
  
  //cout << "Number of entries: " << hR13JetPt[trig]->GetEntries() << endl;

  TDatime now1;
  now1.Print();
  //file->Clear(); 
  //files->Clear();
}
  

