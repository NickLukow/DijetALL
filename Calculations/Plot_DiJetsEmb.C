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


//--->START MAIN PROGRAM
//________________________________________________________________________________

void Plot_DiJetsEmb(const Char_t *eachfile= "/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Embedding/Embedding.root"){
//void Plot_DiJetsEmb(const Char_t *eachfile= "/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Embedding/Embedding4pct.root"){
  
  TDatime now;                                          //Set time in Root
  now.Print();
  
  //gStyle->SetOptDate(0);
  gStyle->SetOptStat(1);
  
  TFile f(eachfile); if (f.IsZombie()) {cout << "File failed!" << endl; return;}
  //cout << "Input file: " << eachfile << endl;

  //High/Low Jet Selection
  const int iJet = 0;  //0 = High, 1 = low

  //Topology Selection
  const int topol = 0; //0 = EW, 1 = EEWW, 2 = Full

  
  
  ////////////Plot Vertex --1-->
  /*TH1D *hVertexZ = (TH1D*)f.Get("hVertexZ");
  TCanvas *cV = new TCanvas("cV","Vertex Z",0,0,700,500);
  cV->cd();
  hVertexZ->GetXaxis()->SetTitle("Vertex Z (cm)");
  //hVertexZ->SetMarkerStyle(20);
  hVertexZ->Draw();
  hVertexZ->SetDirectory(gROOT);
  cV->Draw();*/
  ////////////<--1-- END Plot Vertex

  gStyle->SetOptDate(0);
  gStyle->SetOptStat(0);

  ////// Plots Relative Luminosity --2-->
  //////END Plot Relative Luminosity<--2--
  ////// Plot Polarization--3-->
  //////END Plot Average Polarization<--11--


  ///////////A_LL calculation --3-->
  const int nbins = 15;    
  const double binEdges[nbins+1] = {5,6,7.1,8.4,9.9,11.7,13.8,16.3,19.2,22.7,26.8,31.6,37.3,44,51.9,61.2};

  const Int_t Ntriggers = 3;
  const char *trigger[Ntriggers] = {"JP1","JP2","All"};
  
  const int Ntop = 3;
  const char *Topology[Ntop] = {"EW", "EEWW", "Full"};

  const int nbins_Mass = 9;
  const double binEdges_Mass[nbins+1] = {13.0, 17.0, 19.0, 23.0, 28.0, 34.0, 41.0, 58.0, 82.0, 120.0}; 

  ////////<--4-- END False Asymmetries

  
  //////Get QA histograms --5-->
   
  //Partons
  TH2D *h2PtParton[Ntriggers]; 
  TH2D *h2MassParton[Ntriggers];  
  //Particles
  TH2D *h2PtPartic[Ntriggers];
  TH2D *h2MassPartic[Ntriggers];
  //DiJet
  TH1D *hDiJetMass[Ntriggers]; 
  TH1D *hDiJetdPhi[Ntriggers];
  TH1D *hDiJetUE[Ntriggers]; TH2D *h2DiJetMassUE[Ntriggers];
  //Jets
  TH1D *hJetIdx[Ntriggers]; TH1D *hJetPt[Ntriggers]; TH1D *hJetRt[Ntriggers];
  TH1D *hJetEta[Ntriggers]; TH1D *hJetPhi[Ntriggers]; TH1D *hJetDet[Ntriggers];
  //TH1D *hJetUE[Ntriggers]; TH2D *h2JetPtRt[Ntriggers]; TH2D *h2JetPtUE[Ntriggers]; 
  //Tracks
  TH1D *hTrackIdx[Ntriggers]; TH1D *hTrackPt[Ntriggers]; TH1D *hTrackDcaXY[Ntriggers];
  TH1D *hTrackEta[Ntriggers]; TH1D *hTrackPhi[Ntriggers]; TH1D *hTrackDcaZ[Ntriggers];
  //Towers
  TH1D *hTowerIdx[Ntriggers]; TH1D *hTowerPt[Ntriggers]; TH1D *hTowerE[Ntriggers];   //Tower Pt does not exist is Tower ET
  TH1D *hTowerEta[Ntriggers]; TH1D *hTowerPhi[Ntriggers]; TH1D *hTowerAdc[Ntriggers]; 

  for(int i = 0; i < Ntriggers; i++){ 
    h2PtParton[i] = (TH2D*)f.Get(Form("h2PtParton_%s_%s_%d",trigger[i],Topology[topol], iJet));
    h2PtPartic[i] = (TH2D*)f.Get(Form("h2PtPartic_%s_%s_%d",trigger[i],Topology[topol], iJet));
    h2MassParton[i] = (TH2D*)f.Get(Form("h2MassParton_%s_%s",trigger[i],Topology[topol]));
    h2MassPartic[i] = (TH2D*)f.Get(Form("h2MassPartic_%s_%s",trigger[i],Topology[topol]));
    //DiJet
    hDiJetMass[i]  =(TH1D*)f.Get(Form("hDiJetMass_%s_%s",trigger[i],Topology[topol]));
    hDiJetdPhi[i]  =(TH1D*)f.Get(Form("hDiJetdPhi_%s_%s",trigger[i],Topology[topol]));
    hDiJetUE[i]  =(TH1D*)f.Get(Form("hDiJetUE_%s_%s",trigger[i],Topology[topol]));
    h2DiJetMassUE[i]  =(TH2D*)f.Get(Form("h2DiJetMassUE_%s_%s",trigger[i],Topology[topol]));
    //Jets
    hJetIdx[i]  =(TH1D*)f.Get(Form("hJetIdx_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hJetPt[i]   =(TH1D*)f.Get(Form("hJetPt_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hJetRt[i]   =(TH1D*)f.Get(Form("hJetRt_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hJetEta[i]  =(TH1D*)f.Get(Form("hJetEta_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hJetPhi[i]  =(TH1D*)f.Get(Form("hJetPhi_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hJetDet[i]  =(TH1D*)f.Get(Form("hJetDet_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //hJetUE[i]     =(TH1D*)f.Get(Form("hJetUE_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //h2JetPtRt[i]  =(TH2D*)f.Get(Form("h2JetPtRt_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //h2JetPtUE[i]  =(TH2D*)f.Get(Form("h2JetPtUE_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //h2ZDCJetUE[i]  =(TH2D*)f.Get(Form("h2ZDCJetUE_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //h2JetPtrUE[i]  =(TH2D*)f.Get(Form("h2JetPtrUE_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //Tracks
    hTrackIdx[i]   =(TH1D*)f.Get(Form("hTrackIdx_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTrackPt[i]    =(TH1D*)f.Get(Form("hTrackPt_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTrackDcaXY[i] =(TH1D*)f.Get(Form("hTrackDcaXY_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTrackEta[i]   =(TH1D*)f.Get(Form("hTrackEta_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTrackPhi[i]   =(TH1D*)f.Get(Form("hTrackPhi_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTrackDcaZ[i]  =(TH1D*)f.Get(Form("hTrackDcaZ_%s_%s_%d",trigger[i],Topology[topol], iJet));
    //Towers
    hTowerIdx[i]  =(TH1D*)f.Get(Form("hTowerIdx_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTowerPt[i]   =(TH1D*)f.Get(Form("hTowerPt_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTowerE[i]    =(TH1D*)f.Get(Form("hTowerE_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTowerEta[i]  =(TH1D*)f.Get(Form("hTowerEta_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTowerPhi[i]  =(TH1D*)f.Get(Form("hTowerPhi_%s_%s_%d",trigger[i],Topology[topol], iJet));
    hTowerAdc[i]  =(TH1D*)f.Get(Form("hTowerAdc_%s_%s_%d",trigger[i],Topology[topol], iJet));
  }
  //END Get QA histograms <--5--
  

  //////Jets Plots --6-->
  TCanvas *c0 = new TCanvas("c0","Jets",0,0,1300,700);
  c0->cd();
  c0->Divide(3,2);
  
  c0->cd(1);
  c0->cd(1)->SetLogy();
  hJetIdx[2]->SetTitle("Jets per event");
  //hJetIdx[2]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hJetIdx[2]->SetLineWidth(2); hJetIdx[2]->SetLineColor(1);
  hJetIdx[2]->SetMinimum(0.1);
  hJetIdx[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetIdx[i]->SetLineColor(i+2);
    hJetIdx[i]->Draw("same");
  }

  /*
  hDiJetMass[2]->SetTitle("DiJets invariant Mass");
  hDiJetMass[2]->GetXaxis()->SetTitle("M_{inv} (GeV/c^{2})");
  hDiJetMass[2]->SetLineWidth(2); hDiJetMass[2]->SetLineColor(1);
  hDiJetMass[2]->SetMinimum(0.1);
  hDiJetMass[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hDiJetMass[i]->SetLineColor(i+2);
    hDiJetMass[i]->Draw("same");
  }*/

  c0->cd(2);
  c0->cd(2)->SetLogy();
  hJetPt[2]->SetTitle("Jets Transverse Momentum");
  hJetPt[2]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hJetPt[2]->SetLineWidth(2); hJetPt[2]->SetLineColor(1);
  hJetPt[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  TLegend *legend0 = new TLegend(0.5,0.6,0.85,0.85);
  legend0->AddEntry(hJetPt[2], Form("%s Triggers",trigger[2]), "l");
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetPt[i]->SetLineColor(i+2);
    hJetPt[i]->Draw("same");
    legend0->AddEntry(hJetPt[i], Form("%s",trigger[i]), "l");
  } 
  legend0->SetTextSize(0.05);
  legend0->SetBorderSize(0);
  legend0->SetFillStyle(0);
  legend0->Draw();

  c0->cd(3);
  c0->cd(3)->SetLogy();
  hJetRt[2]->SetTitle("Jets R_{T}");
  //hJetPt[2]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hJetRt[2]->SetLineWidth(2); hJetRt[2]->SetLineColor(1);
  hJetRt[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetRt[i]->SetLineColor(i+2);
    hJetRt[i]->Draw("same");
  }

  c0->cd(4);
  //c0->SetLogy();
  hJetEta[2]->SetTitle("Jets #eta");
  hJetEta[2]->GetXaxis()->SetTitle("#eta");
  hJetEta[2]->SetLineWidth(2); hJetEta[2]->SetLineColor(1);
  hJetEta[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetEta[i]->SetLineColor(i+2);
    hJetEta[i]->Draw("same");
  }

  c0->cd(5);
  //c0->SetLogy();
  hJetPhi[2]->SetTitle("Jets #phi");
  hJetPhi[2]->GetXaxis()->SetTitle("#phi");
  hJetPhi[2]->SetLineWidth(2); hJetPhi[2]->SetLineColor(1);
  hJetPhi[2]->SetMinimum(0);
  hJetPhi[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    //if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetPhi[i]->SetLineColor(i+2);
    hJetPhi[i]->Draw("same");
  }

  c0->cd(6);
  //c0->SetLogy();
  hJetDet[2]->SetTitle("Jets detector #eta");
  hJetDet[2]->GetXaxis()->SetTitle("#eta_{det}");
  hJetDet[2]->SetLineWidth(2); hJetDet[2]->SetLineColor(1);
  hJetDet[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetDet[i]->SetLineColor(i+2);
    hJetDet[i]->Draw("same");
  }

  //c0->SaveAs("/star/u/aquinter/Run13/InclusiveJets/PlotHisto/JetPt.png");

  c0->Draw();
  //////END Jets Plots <--6--
  
 
  //////Track Plots --7-->
  TCanvas *c1 = new TCanvas("c1","Tracks",0,0,1300,700);
  c1->cd();
  c1->Divide(3,2);
  
  c1->cd(1);
  c1->cd(1)->SetLogy();
  hTrackIdx[2]->SetTitle("Tracks per jet");
  //hTrackIdx[2]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hTrackIdx[2]->SetLineWidth(2); hTrackIdx[2]->SetLineColor(1);
  hTrackIdx[2]->SetMinimum(0.1);
  hTrackIdx[2]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackIdx[i]->SetLineColor(i+2);
    hTrackIdx[i]->Draw("same");
  }

  c1->cd(2);
  c1->cd(2)->SetLogy();
  hTrackPt[2]->SetTitle("Tracks Transverse Momentum");
  hTrackPt[2]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hTrackPt[2]->SetLineWidth(2); hTrackPt[2]->SetLineColor(1);
  hTrackPt[2]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  //TLegend *legend0 = new TLegend(0.6,0.70,0.85,0.85);
  //legend0->AddEntry(hTrackPt[2], Form("%s Triggers",trigger[2]), "l");
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackPt[i]->SetLineColor(i+2);
    hTrackPt[i]->Draw("same");
    //legend0->AddEntry(hTrackPt[i], Form("%s",trigger[i]), "l");
  } 
  //legend0->SetTextSize(0.05);
  //legend0->SetBorderSize(0);
  //legend0->SetFillStyle(0);
  legend0->Draw();

  c1->cd(3);
  //c1->cd(3)->SetLogy();
  hTrackDcaXY[2]->SetTitle("Tracks DCA_{XY}");
  hTrackDcaXY[2]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
  hTrackDcaXY[2]->SetLineWidth(2); hTrackDcaXY[2]->SetLineColor(1);
  hTrackDcaXY[2]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackDcaXY[i]->SetLineColor(i+2);
    hTrackDcaXY[i]->Draw("same");
  }

  c1->cd(4);
  //c1->SetLogy();
  hTrackEta[2]->SetTitle("Tracks #eta");
  hTrackEta[2]->GetXaxis()->SetTitle("#eta");
  hTrackEta[2]->SetLineWidth(2); hTrackEta[2]->SetLineColor(1);
  hTrackEta[2]->SetMinimum(0);
  hTrackEta[2]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackEta[i]->SetLineColor(i+2);
    hTrackEta[i]->Draw("same");
  }

  c1->cd(5);
  //c1->SetLogy();
  hTrackPhi[2]->SetTitle("Tracks #phi");
  hTrackPhi[2]->GetXaxis()->SetTitle("#phi");
  hTrackPhi[2]->SetLineWidth(2); hTrackPhi[2]->SetLineColor(1);
  hTrackPhi[2]->SetMinimum(0);
  hTrackPhi[2]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    //if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackPhi[i]->SetLineColor(i+2);
    hTrackPhi[i]->Draw("same");
  }

  c1->cd(6);
  //c1->SetLogy();
  hTrackDcaZ[2]->SetTitle("Tracks DCA_{Z}");
  hTrackDcaZ[2]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
  hTrackDcaZ[2]->SetLineWidth(2); hTrackDcaZ[2]->SetLineColor(1);
  hTrackDcaZ[2]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackDcaZ[i]->SetLineColor(i+2);
    hTrackDcaZ[i]->Draw("same");
  }

  //c1->SaveAs("/star/u/aquinter/Run13/InclusiveTracks/PlotHisto/TrackPt.png");

  c1->Draw();
  //END Plot Tracks<--7--


  //////Tower Plots --8-->
  TCanvas *c2 = new TCanvas("c2","Towers",0,0,1300,700);
  c2->cd();
  c2->Divide(3,2);
  
  c2->cd(1);
  c2->cd(1)->SetLogy();
  hTowerIdx[2]->SetTitle("Towers per jet");
  //hTowerIdx[2]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hTowerIdx[2]->SetLineWidth(2); hTowerIdx[2]->SetLineColor(1);
  hTowerIdx[2]->SetMinimum(0.1);
  hTowerIdx[2]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerIdx[i]->SetLineColor(i+2);
    hTowerIdx[i]->Draw("same");
  }

  c2->cd(2);
  c2->cd(2)->SetLogy();
  hTowerPt[2]->SetTitle("Towers Transverse Energy");        //Tower Pt does not exist is Tower ET
  hTowerPt[2]->GetXaxis()->SetTitle("E_{T} (GeV)");
  hTowerPt[2]->SetLineWidth(2); hTowerPt[2]->SetLineColor(1);
  hTowerPt[2]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  //TLegend *legend0 = new TLegend(0.6,0.70,0.85,0.85);
  //legend0->AddEntry(hTowerPt[2], Form("%s Triggers",trigger[2]), "l");
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerPt[i]->SetLineColor(i+2);
    hTowerPt[i]->Draw("same");
    //legend0->AddEntry(hTowerPt[i], Form("%s",trigger[i]), "l");
  } 
  //legend0->SetTextSize(0.05);
  //legend0->SetBorderSize(0);
  //legend0->SetFillStyle(0);
  legend0->Draw();
  
  c2->cd(3);
  c2->cd(3)->SetLogy();
  hTowerE[2]->SetTitle("Towers Energy");
  hTowerE[2]->GetXaxis()->SetTitle("E (GeV)");
  hTowerE[2]->SetLineWidth(2); hTowerE[2]->SetLineColor(1);
  hTowerE[2]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerE[i]->SetLineColor(i+2);
    hTowerE[i]->Draw("same");
  }

  c2->cd(4);
  //c1->SetLogy();
  hTowerEta[2]->SetTitle("Towers #eta");
  hTowerEta[2]->GetXaxis()->SetTitle("#eta");
  hTowerEta[2]->SetLineWidth(2); hTowerEta[2]->SetLineColor(1);
  hTowerEta[2]->SetMinimum(0);
  hTowerEta[2]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerEta[i]->SetLineColor(i+2);
    hTowerEta[i]->Draw("same");
  }

  c2->cd(5);
  //c1->SetLogy();
  hTowerPhi[2]->SetTitle("Towers #phi");
  hTowerPhi[2]->GetXaxis()->SetTitle("#phi");
  hTowerPhi[2]->SetLineWidth(2); hTowerPhi[2]->SetLineColor(1);
  hTowerPhi[2]->SetMinimum(0);
  hTowerPhi[2]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    //if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerPhi[i]->SetLineColor(i+2);
    hTowerPhi[i]->Draw("same");
  }
  
  c2->cd(6);
  //c1->SetLogy();
  hTowerAdc[2]->SetTitle("Towers Adc");
  //hTowerAdc[2]->GetXaxis()->SetTitle("");
  hTowerAdc[2]->SetLineWidth(2); hTowerAdc[2]->SetLineColor(1);
  hTowerAdc[2]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerAdc[i]->SetLineColor(i+2);
    hTowerAdc[i]->Draw("same");
  }

  //c1->SaveAs("/star/u/aquinter/Run13/InclusiveTowers/PlotHisto/TowerPt.png");

  c2->Draw();
  //END Plot Towers<--8--


 //////DiJets Plots --9-->
  TCanvas *cM = new TCanvas("cM","DiJets",0,0,1300,700);
  cM->cd();
  cM->Divide(3,2);
  
  cM->cd(1);
  cM->cd(1)->SetLogy();
  hDiJetMass[2]->SetTitle("DiJets invariant Mass");
  hDiJetMass[2]->GetXaxis()->SetTitle("M_{inv} (GeV/c^{2})");
  hDiJetMass[2]->SetLineWidth(2); hDiJetMass[2]->SetLineColor(1);
  hDiJetMass[2]->SetMinimum(0.1);
  hDiJetMass[2]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[2]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hDiJetMass[i]->SetLineColor(i+2);
    hDiJetMass[i]->Draw("same");
  }

  cM->cd(2);
  //cM->cd(2)->SetLogy();
  hDiJetdPhi[2]->SetTitle("DiJets #Delta cos(#Phi)");
  hDiJetdPhi[2]->GetXaxis()->SetTitle("DiJets #Delta cos(#Phi)");
  hDiJetdPhi[2]->SetLineWidth(2); hDiJetdPhi[Ntriggers-1]->SetLineColor(1);
  hDiJetdPhi[2]->Draw("");
  legend0->Draw();

  cM->cd(4);
  //cM->cd(2)->SetLogy();
  hDiJetUE[2]->SetTitle("DiJets UE Mass_{inv}");
  hDiJetUE[2]->GetXaxis()->SetTitle("UE M_{inv} (GeV/c^{2})");
  hDiJetUE[2]->SetLineWidth(2); hDiJetUE[Ntriggers-1]->SetLineColor(1);
  hDiJetUE[2]->Draw("");

  cM->cd(5);
  cM->cd(5)->SetLogz();
  h2DiJetMassUE[2]->SetTitle("DiJets UE Mass_{inv}");
  h2DiJetMassUE[2]->GetXaxis()->SetTitle("UE M_{inv} (GeV/c^{2})");
  h2DiJetMassUE[2]->SetLineWidth(2); h2DiJetMassUE[Ntriggers-1]->SetLineColor(1);
  h2DiJetMassUE[2]->Draw("colz");

  cM->cd(3);
  cM->cd(3)->SetLogz();
  h2MassParton[2]->SetTitle("Jets Mass, Parton vs Detector");
  h2MassParton[2]->GetXaxis()->SetTitle("(detector) M_{inv} (GeV/c^{2})");
  h2MassParton[2]->GetYaxis()->SetTitle("(parton) M_{inv} (GeV/c^{2})");
  h2MassParton[2]->GetXaxis()->SetRangeUser(10,82);
  h2MassParton[2]->GetYaxis()->SetRangeUser(0,100);
  h2MassParton[2]->Draw("colz");
  TProfile * h2MassParton_pfX = h2MassParton[2]->ProfileX(); 
  h2MassParton_pfX->Draw("same");
  TF1 *fshift = new TF1("fshift","pol1",16,82.0);
  h2MassParton_pfX->Fit(fshift,"+R");
  h2MassParton_pfX->SetDirectory(gROOT);

  cM->cd(6);
  cM->cd(6)->SetLogz();
  h2MassPartic[2]->SetTitle("DiJets Mass, Particle vs Detector");
  h2MassPartic[2]->GetXaxis()->SetTitle("Mass_{inv} (GeV/c^{2})");
  h2MassPartic[2]->GetYaxis()->SetTitle("M_{inv} (GeV/c^{2})");
  h2MassPartic[2]->Draw("colz");
  TProfile * h2MassPartic_pfX = h2MassPartic[2]->ProfileX();
  h2MassPartic_pfX->Draw("same");
  h2MassPartic_pfX->SetDirectory(gROOT);

  //////END DiJets Plots <--9--
  

  for(int i = 0; i < Ntriggers; i++){  //NEED THIS TO PLOT EACH HISTOGRAM
    h2PtParton[i]->SetDirectory(gROOT); h2PtPartic[i]->SetDirectory(gROOT);
    h2MassParton[i]->SetDirectory(gROOT); h2MassPartic[i]->SetDirectory(gROOT);
    //DiJet
    hDiJetMass[i]->SetDirectory(gROOT);
    hDiJetdPhi[i]->SetDirectory(gROOT);
    hDiJetUE[i]->SetDirectory(gROOT);
    h2DiJetMassUE[i]->SetDirectory(gROOT);
    //Jet
    hJetIdx[i]->SetDirectory(gROOT); hJetPt[i]->SetDirectory(gROOT); hJetRt[i]->SetDirectory(gROOT);
    hJetEta[i]->SetDirectory(gROOT); hJetPhi[i]->SetDirectory(gROOT); hJetDet[i]->SetDirectory(gROOT);
    //hJetUE[i]->SetDirectory(gROOT); h2JetPtRt[i]->SetDirectory(gROOT); h2JetPtUE[i]->SetDirectory(gROOT);
    //Track
    hTrackIdx[i]->SetDirectory(gROOT); hTrackPt[i]->SetDirectory(gROOT); hTrackDcaXY[i]->SetDirectory(gROOT);
    hTrackEta[i]->SetDirectory(gROOT); hTrackPhi[i]->SetDirectory(gROOT); hTrackDcaZ[i]->SetDirectory(gROOT);
    //Tower
    hTowerIdx[i]->SetDirectory(gROOT); hTowerPt[i]->SetDirectory(gROOT); hTowerE[i]->SetDirectory(gROOT);
    hTowerEta[i]->SetDirectory(gROOT); hTowerPhi[i]->SetDirectory(gROOT); hTowerAdc[i]->SetDirectory(gROOT);
  }

  /*cout << "Pt average per bin: " << endl;
  cout << "Float_t cpt_13[N]={";
  for(Int_t iii = 0; iii<nbins-2; iii++){
    hJetPt[2]->GetXaxis()->SetRange(binEdges[iii]*10,binEdges[iii+1]*10);   //Might need to multiply by 10 due the binning
    //cout << Form("% .1f - % .1f:   avg: % .2f",binEdges[iii],binEdges[iii+1],hJetPt[2]->GetMean()) << endl;
    cout <<  Form("% .2f",hJetPt[2]->GetMean());
    if(iii==nbins-3) cout << "};"<< endl; 
    else cout << ",";
    hJetPt[2]->GetXaxis()->SetRange();
    }*/
 
  cout << "Average Parton InvMass per bin: " << endl;
  for(Int_t iii = 2; iii<=nbins_Mass-1; iii++) cout << h2MassParton_pfX->GetBinContent(iii) << endl; 

  cout << "Average Detector InvMass per bin: " << endl;
  for(Int_t iii = 1; iii<nbins_Mass-1; iii++){
    Int_t BinL = hDiJetMass[2]->GetXaxis()->FindBin(binEdges_Mass[iii]);
    Int_t BinH = hDiJetMass[2]->GetXaxis()->FindBin(binEdges_Mass[iii+1]);
    hDiJetMass[2]->GetXaxis()->SetRange(BinL,BinH);   
    //hDiJetMass[2]->GetXaxis()->SetRange(binEdges[iii],binEdges[iii+1]);   
    //cout << binEdges[iii] << "-" << binEdges[iii+1] << ": " << Form("% .2f",hDiJetMass[2]->GetMean()) << endl;;
    cout <<  Form("%.2f",hDiJetMass[2]->GetMean()) << endl;;
    
    hDiJetMass[2]->GetXaxis()->SetRange();
  }
/*
  cout << "Mass shift (Parton) per bin: " << endl;
  for(Int_t iii = 1; iii<=nbins_Mass; iii++) {
    //cout << h2PtParton_pfX->GetBinContent(iii) << " - " << h2PtParton_pfX->GetBinCenter(iii) << " = " << 
    cout << h2MassParton_pfX->GetBinContent(iii) - h2MassParton_pfX->GetBinCenter(iii) << endl;
  } 
*/
  //cout << "Pt shift (Particle) per bin: " << endl;
  //for(Int_t iii = 1; iii<=nbins; iii++) cout << h2PtPartic_pfX->GetBinContent(iii) << endl;
      
 cout << "Mass shift (Parton) ERROR per bin: " << endl;
  for(Int_t iii = 2; iii<=nbins_Mass-1; iii++) cout << h2MassParton_pfX->GetBinError(iii) << endl; 

  TDatime now1;
  now1.Print();
}
  

