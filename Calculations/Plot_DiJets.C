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
void Plot_DiJets(const Char_t *eachfile= "/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms//Data/Data.root"){
  
  TDatime now;                                          //Set time in Root
  now.Print();
  const int iJet = 0;  // 0=high, 1=low
  const int iTop = 0;  // 0 = EW, 1 = EEWW, 2 = Full
  //gStyle->SetOptDate(0);
  //gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);
  
  TFile f(eachfile); if (f.IsZombie()) {cout << "File failed!" << endl; return;}
  //cout << "Input file: " << eachfile << endl;

  
  ////////////Plot Vertex --1-->
  /* TH1D *hVertexZ = (TH1D*)f.Get("hVertexZ");
  TCanvas *cV = new TCanvas("cV","Vertex Z",0,0,800,400);
  cV->Divide(2,1);
  cV->cd(1);
  hVertexZ->GetXaxis()->SetTitle("Vertex Z (cm)");
  //hVertexZ->SetMarkerStyle(20);
  hVertexZ->Draw();
  hVertexZ->SetDirectory(gROOT);

  cV->cd(2);
  TH1D *hBX = (TH1D*)f.Get("hBX");
  //hBX->GetXaxis()->SetTitle("Vertex Z (cm)");
  //hVertexZ->SetMarkerStyle(20);
  hBX->Draw();
  hBX->SetDirectory(gROOT);

  cV->Draw();
*/
  ////////////<--1-- END Plot Vertex

  //gStyle->SetOptDate(0);
  //gStyle->SetOptStat(0);
  //gStyle->SetOptFit(1);

  ////// Plots Relative Luminosity --2-->
  /* TCanvas *cR = new TCanvas("cR","Relative Luminosity",0,0,1300,700);
  cR->cd();
  cR->Divide(3,2);
  
  cR->cd(1);
  TH1D *hR1 = (TH1D*)f.Get("hR1");
  hR1->SetTitle("R1");
  //h2R1->GetXaxis()->SetTitle("ZDC rate (kHz)");
  //h2R1->GetYaxis()->SetTitle("");
  hR1->Draw();

  cR->cd(2);
  TH1D *hR2 = (TH1D*)f.Get("hR2");
  hR2->SetTitle("R2");
  hR2->Draw();

  cR->cd(3);
  TH1D *hR3 = (TH1D*)f.Get("hR3");
  hR3->SetTitle("R3");
  hR3->Draw();

  cR->cd(4);
  TH1D *hR4 = (TH1D*)f.Get("hR4");
  hR4->SetTitle("R4");
  hR4->Draw();

  cR->cd(5);
  TH1D *hR5 = (TH1D*)f.Get("hR5");
  hR5->SetTitle("R5");
  hR5->Draw();

  cR->cd(6);
  TH1D *hR6 = (TH1D*)f.Get("hR6");
  hR6->SetTitle("R6");
  hR6->Draw();

  hR1->SetDirectory(gROOT); hR2->SetDirectory(gROOT); hR3->SetDirectory(gROOT);
  hR4->SetDirectory(gROOT); hR5->SetDirectory(gROOT); hR6->SetDirectory(gROOT);

  cR->Draw();
  */
  //////END Plot Relative Luminosity<--2--


  ////// Plot Polarization--3-->
  /* TCanvas *cPol = new TCanvas("cPol","Polarization",0,0,800,400);
  cPol->cd(); 
  cPol->Divide(2,1);
 
  cPol->cd(1);
  TH1D *hPolB = (TH1D*)f.Get("hPolB");
  hPolB->SetTitle("Blue beam Polarization");
  hPolB->Draw();
  
  cPol->cd(2);
  TH1D *hPolY = (TH1D*)f.Get("hPolY");
  hPolY->SetTitle("Yellow beam Polarization");
  hPolY->Draw();

  cPol->Draw();

  hPolB->SetDirectory(gROOT);  hPolY->SetDirectory(gROOT);
  */
  //////END Plot Average Polarization<--11--


  ////////////A_LL calculation --3-->
  const Int_t Ntopol = 3;
  const char *topology[Ntopol]= {"EW", "EEWW", "Full"};
  
  const Int_t Ntriggers = 3;
  const char *trigger[Ntriggers] = {"JP1","JP2","All"};
  
  const int nbins_Mass = 9;         //Amilkar
  const double binEdges_Mass[nbins_Mass+1] = { 13.0, 17.0, 19.0, 23.0, 28.0, 34.0, 41.0, 58.0, 82.0, 120.0};


  TH1D *hALL         = new TH1D("hALL","Longitudinal Double Spin Asymmetry",nbins_Mass,binEdges_Mass);

  TH1D *hNumerator = (TH1D*)f.Get(Form("hNumerator_All_%s", topology[iTop]));
  TH1D *hNumeratorErr = (TH1D*)f.Get(Form("hNumeratorErr_All_%s", topology[iTop]));
  TH1D *hDenominator = (TH1D*)f.Get(Form("hDenominator_All_%s", topology[iTop]));
  if (!hNumerator || !hDenominator) {cout<< "Problems with file: " << eachfile << endl; return;}
  
  //hALL->SetDirectory(gDirectory);
  //hNumerator->Sumw2(kFALSE);  hDenominator->Sumw2(kFALSE);
  //hALL->Sumw2();
  hALL->Divide(hNumerator,hDenominator,1.,1.,"b");
  for(Int_t i=1; i<=hALL->GetNbinsX(); i++ ) 
    hALL->SetBinError(i,sqrt(hNumeratorErr->GetBinContent(i))/(hDenominator->GetBinContent(i)));
  TCanvas *cALL = new TCanvas("cALL","A_{LL}",0,0,700,500);
  cALL->cd();
  hALL->GetXaxis()->SetTitle("(UE corr.)   p_{T} (GeV/c)");
  hALL->GetYaxis()->SetTitle("A_{LL}");
  //hALL->SetMarkerStyle(20);
  //hALL->GetXaxis()->SetRangeUser(0,75);
  //hALL->GetYaxis()->SetRangeUser(-0.01,0.16);
  hALL->Draw("E");
  hALL->SetDirectory(gROOT);           //NEED THIS TO PLOT THE FIGURE
  
  Int_t n = hALL->GetNbinsX();
  cout << "Bin Center: " << endl;
  cout << "Bin Center Mass: " << endl;
  for(int i=2; i<=n-1;i++) {
    cout << hALL->GetBinCenter(i) << endl;
    //if(i==n) cout << "};"<< endl;
    //else cout << ",";
    }
  
  cout << "Asymmetry - " << topology[iTop] << ": " << endl;
  for(int i=2; i<=n-1;i++) {
    cout <<  Form("%0.6lf",hALL->GetBinContent(i)) << endl;
    //if(i==n) cout << "};"<< endl;
    //else cout << ",";
    }
  //for(int i=1; i<n+1;i++) cout << Form("%1.6e",hALL->GetBinContent(i)) << endl;  

  cout << "Asymmetry Statistical Error - " << topology[iTop] << ": " << endl;
  for(int i=2; i<=n-1;i++) {
    cout <<  Form("%0.6lf",sqrt(hNumeratorErr->GetBinContent(i))/(hDenominator->GetBinContent(i))) << endl;
    //if(i==n) cout << "};"<< endl; 
    //else cout << ",";
    }
  cout << endl;
  //for(int i=1; i<n+1;i++) cout <<  Form("% .6e",sqrt(hNumeratorErr->GetBinContent(i))/(hDenominator->GetBinContent(i))) << endl;
  
  //cout << "e[n]={";
  //for(int i=1; i<n+1;i++) cout << hALL->GetBinError(i) << ",";
  //cout << "};"<< endl;
  //////////A_LL calculation --3-->
  
  //return;


  TH1D *hALL1[3];

  TH1D *hNumerator1[3];
  TH1D *hNumeratorErr1[3];
  TH1D *hDenominator1[3];

  TCanvas *cALL1 = new TCanvas("cALL1","A_{LL} Jet Patch",0,0,700,500);
  cALL1->cd();
  TLegend *legendX = new TLegend(0.6,0.70,0.85,0.85);
  
  for(int ii = 0; ii < Ntriggers-1; ii++){
    hALL1[ii]         = new TH1D("hALL","Longitudinal Double Spin Asymmetry",nbins_Mass,binEdges_Mass);
    
    hNumerator1[ii] = (TH1D*)f.Get(Form("hNumerator_%s_%s",trigger[ii],topology[iTop]));
    hNumeratorErr1[ii] = (TH1D*)f.Get(Form("hNumeratorErr_%s_%s",trigger[ii],topology[iTop]));
    hDenominator1[ii] = (TH1D*)f.Get(Form("hDenominator_%s_%s",trigger[ii],topology[iTop]));
    
    hALL1[ii]->Divide(hNumerator1[ii],hDenominator1[ii],1.,1.,"b");
    for(Int_t jj=1; jj<=hALL1[ii]->GetNbinsX(); jj++ ){ 
      if( hNumerator1[ii]->GetBinContent(jj)==0){
	hNumerator1[ii]->SetBinContent(jj,0);
	hNumeratorErr1[ii]->SetBinContent(jj,0);
	hDenominator1[ii]->SetBinContent(jj,0);
      } else  hALL1[ii]->SetBinError(jj,sqrt(hNumeratorErr1[ii]->GetBinContent(jj))/(hDenominator1[ii]->GetBinContent(jj)));
    }
    hALL1[ii]->SetLineColor(ii+2);
    if(ii==0) {
      hALL1[ii]->Draw("E");
      hALL1[ii]->GetXaxis()->SetTitle("(UE corr.)   p_{T} (GeV/c)");
      hALL1[ii]->GetYaxis()->SetTitle("A_{LL}");
      //hALL1[ii]->GetXaxis()->SetRangeUser(0,75);
      //hALL1[ii]->GetYaxis()->SetRangeUser(-0.01,0.16);
    } else  hALL1[ii]->Draw("same E");
    
    legendX->AddEntry(hALL1[ii], Form("%s Triggers",trigger[ii]), "l");
    hALL1[ii]->SetDirectory(gROOT);
    
  }
  legendX->Draw();
  

  ////////--4--> False Asymmetries
  TH1D *hbAL          = new TH1D("hbAL","Longitudinal Single Spin Asymmetry Blue beam",nbins_Mass,binEdges_Mass);
  TH1D *hbNumerator   = (TH1D*)f.Get(Form("hbNumerator_All_%s", topology[iTop])); TH1D *hbNumeratorErr   = (TH1D*)f.Get(Form("hbNumeratorErr_All_%s", topology[iTop]));
  TH1D *hbDenominator = (TH1D*)f.Get(Form("hbDenominator_All_%s", topology[iTop]));

  TH1D *hyAL          = new TH1D("hyAL","Longitudinal Single Spin Asymmetry Yellow beam",nbins_Mass,binEdges_Mass);
  TH1D *hyNumerator   = (TH1D*)f.Get(Form("hyNumerator_All_%s", topology[iTop])); TH1D *hyNumeratorErr   = (TH1D*)f.Get(Form("hyNumeratorErr_All_%s", topology[iTop]));
  TH1D *hyDenominator = (TH1D*)f.Get(Form("hyDenominator_All_%s", topology[iTop]));

  TH1D *hlALL         = new TH1D("hlALL","Longitudinal Double Spin Asymmetry like sign",nbins_Mass,binEdges_Mass);
  TH1D *hlNumerator   = (TH1D*)f.Get(Form("hlNumerator_All_%s", topology[iTop])); TH1D *hlNumeratorErr   = (TH1D*)f.Get(Form("hlNumeratorErr_All_%s", topology[iTop]));
  TH1D *hlDenominator = (TH1D*)f.Get(Form("hlDenominator_All_%s", topology[iTop]));

  TH1D *huALL          = new TH1D("huALL","Longitudinal Double Spin Asymmetry unlike sign",nbins_Mass,binEdges_Mass);
  TH1D *huNumerator   = (TH1D*)f.Get(Form("huNumerator_All_%s", topology[iTop])); TH1D *huNumeratorErr   = (TH1D*)f.Get(Form("huNumeratorErr_All_%s", topology[iTop]));
  TH1D *huDenominator = (TH1D*)f.Get(Form("huDenominator_All_%s", topology[iTop]));
  
  //Plot Asymmetries
  TCanvas *cAfl = new TCanvas("cAfl","False Asymetries",0,0,900,600);
  cAfl->cd();
  cAfl->Divide(2,2);

  cAfl->cd(1);
  hbAL ->Divide(hbNumerator,hbDenominator,1.,1.,"b");
  for(Int_t i=1; i<=hbAL->GetNbinsX(); i++ ) 
    hbAL->SetBinError(i,sqrt(hbNumeratorErr->GetBinContent(i))/(hbDenominator->GetBinContent(i)));
  hbAL->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hbAL->GetYaxis()->SetTitle("A_{L} blue beam");
  //hbAL->SetMarkerStyle(20);
  hbAL->GetXaxis()->SetRangeUser(0,76);
  hbAL->GetYaxis()->SetRangeUser(-0.0575,0.0575);
  hbAL->Draw("E");
  TF1 *fbAL = new TF1("fbAL","pol0",16,76.9);
  hbAL->Fit("fbAL","+R");

  cAfl->cd(2);
  hyAL ->Divide(hyNumerator,hyDenominator,1.,1.,"b");
  for(Int_t i=1; i<=hyAL->GetNbinsX(); i++ ) 
    hyAL->SetBinError(i,sqrt(hyNumeratorErr->GetBinContent(i))/(hyDenominator->GetBinContent(i)));
  hyAL->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hyAL->GetYaxis()->SetTitle("A_{L} yellow beam");
  //hyAL->SetMarkerStyle(20);
  hyAL->GetXaxis()->SetRangeUser(0,76);
  hyAL->GetYaxis()->SetRangeUser(-0.0575,0.0575);
  hyAL->Draw("E");
  TF1 *fyAL = new TF1("fyAL","pol0",16,76.9);
  hyAL->Fit("fyAL","+R");
  
  cAfl->cd(3);
  hlALL->Divide(hlNumerator,hlDenominator,1.,1.,"b");
  for(Int_t i=1; i<=hlALL->GetNbinsX(); i++ ) 
    hlALL->SetBinError(i,sqrt(hlNumeratorErr->GetBinContent(i))/(hlDenominator->GetBinContent(i)));
  hlALL->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hlALL->GetYaxis()->SetTitle("A_{LL} like sign");
  //hlALL->SetMarkerStyle(20);
  hlALL->GetXaxis()->SetRangeUser(0,76);
  hlALL->GetYaxis()->SetRangeUser(-0.0675,0.0675);
  hlALL->Draw("E");
  TF1 *flALL = new TF1("flALL","pol0",16,76.9);
  hlALL->Fit("flALL","+R");

  cAfl->cd(4);
  huALL->Divide(huNumerator,huDenominator,1.,1.,"b");
  for(Int_t i=1; i<=huALL->GetNbinsX(); i++ ) 
    huALL->SetBinError(i,sqrt(huNumeratorErr->GetBinContent(i))/(huDenominator->GetBinContent(i)));
  huALL->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  huALL->GetYaxis()->SetTitle("A_{LL} unlike sign");
  //huALL->SetMarkerStyle(20);
  huALL->GetXaxis()->SetRangeUser(0,76);
  huALL->GetYaxis()->SetRangeUser(-0.0975,0.0975);
  huALL->Draw("E");
  TF1 *fuALL = new TF1("fuALL","pol0",16,76.9);
  huALL->Fit("fuALL","+R");

  hyAL->SetDirectory(gROOT);           //NEED THIS TO PLOT THE FIGURE
  hbAL->SetDirectory(gROOT);           //NEED THIS TO PLOT THE FIGURE
  hlALL->SetDirectory(gROOT);           //NEED THIS TO PLOT THE FIGURE
  huALL->SetDirectory(gROOT);           //NEED THIS TO PLOT THE FIGURE

  cAfl->Draw();

  cAfl->SaveAs("/home/Nick/Analysis/Figures/FalseAsymmetries_Dijet.png");
  ////////<--4-- END False Asymmetries

  //return;
  //////Get QA histograms --5-->
    
  //DiJets
  TH1D *hDiJetMass[Ntriggers];
  TH1D *hDiJetdPhi[Ntriggers];
  TH1D *hDiJetUE[Ntriggers]; TH2D *h2DiJetMassUE[Ntriggers];
  TH2D *h2DiJetMassRt[Ntriggers];
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
    //DiJets
    hDiJetMass[i]  =(TH1D*)f.Get(Form("hDiJetMass_%s_%s",trigger[i],topology[iTop]));
    hDiJetdPhi[i]  =(TH1D*)f.Get(Form("hDiJetdPhi_%s_%s",trigger[i],topology[iTop]));
    hDiJetUE[i]  =(TH1D*)f.Get(Form("hDiJetUE_%s_%s",trigger[i],topology[iTop]));
    h2DiJetMassUE[i]  =(TH2D*)f.Get(Form("h2DiJetMassUE_%s_%s",trigger[i],topology[iTop]));
    h2DiJetMassRt[i]  =(TH2D*)f.Get(Form("h2DiJetMassRt_%s_%s",trigger[i],topology[iTop]));
    //Jets
    hJetIdx[i]  =(TH1D*)f.Get(Form("hJetIdx_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hJetPt[i]   =(TH1D*)f.Get(Form("hJetPt_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hJetRt[i]   =(TH1D*)f.Get(Form("hJetRt_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hJetEta[i]  =(TH1D*)f.Get(Form("hJetEta_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hJetPhi[i]  =(TH1D*)f.Get(Form("hJetPhi_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hJetDet[i]  =(TH1D*)f.Get(Form("hJetDet_%s_%s_%d",trigger[i],topology[iTop],iJet));
    // hJetUE[i]     =(TH1D*)f.Get(Form("hJetUE_%s_%s_%d",trigger[i],topology[iTop],iJet));
    // h2JetPtRt[i]  =(TH2D*)f.Get(Form("h2JetPtRt_%s_%s_%d",trigger[i],topology[iTop],iJet));
    //h2JetPtUE[i]  =(TH2D*)f.Get(Form("h2JetPtUE_%s_%s_%d",trigger[i],topology[iTop],iJet));
    //h2ZDCJetUE[i]  =(TH2D*)f.Get(Form("h2ZDCJetUE_%s_%s_%d",trigger[i],topology[iTop],iJet));
    //h2JetPtrUE[i]  =(TH2D*)f.Get(Form("h2JetPtrUE_%s_%s_%d",trigger[i],topology[iTop],iJet));
    //Tracks
    hTrackIdx[i]   =(TH1D*)f.Get(Form("hTrackIdx_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTrackPt[i]    =(TH1D*)f.Get(Form("hTrackPt_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTrackDcaXY[i] =(TH1D*)f.Get(Form("hTrackDcaXY_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTrackEta[i]   =(TH1D*)f.Get(Form("hTrackEta_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTrackPhi[i]   =(TH1D*)f.Get(Form("hTrackPhi_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTrackDcaZ[i]  =(TH1D*)f.Get(Form("hTrackDcaZ_%s_%s_%d",trigger[i],topology[iTop],iJet));
    //Towers
    hTowerIdx[i]  =(TH1D*)f.Get(Form("hTowerIdx_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTowerPt[i]   =(TH1D*)f.Get(Form("hTowerPt_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTowerE[i]    =(TH1D*)f.Get(Form("hTowerE_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTowerEta[i]  =(TH1D*)f.Get(Form("hTowerEta_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTowerPhi[i]  =(TH1D*)f.Get(Form("hTowerPhi_%s_%s_%d",trigger[i],topology[iTop],iJet));
    hTowerAdc[i]  =(TH1D*)f.Get(Form("hTowerAdc_%s_%s_%d",trigger[i],topology[iTop],iJet));
  }
  //END Get QA histograms <--5--


  //////Jets Plots --6-->
  TCanvas *c0 = new TCanvas("c0","Jets",0,0,1300,700);
  c0->cd();
  c0->Divide(3,2);
  
  c0->cd(1);
  c0->cd(1)->SetLogy();
   hJetIdx[Ntriggers-1]->SetTitle("Jets per event");
  //hJetIdx[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hJetIdx[Ntriggers-1]->SetLineWidth(2); hJetIdx[Ntriggers-1]->SetLineColor(1);
  hJetIdx[Ntriggers-1]->SetMinimum(0.1);
  hJetIdx[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetIdx[i]->SetLineColor(i+2);
    hJetIdx[i]->Draw("same");
  }

  c0->cd(2);
  c0->cd(2)->SetLogy();
  hJetPt[Ntriggers-1]->SetTitle("Jets Transverse Momentum");
  hJetPt[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hJetPt[Ntriggers-1]->SetLineWidth(2); hJetPt[Ntriggers-1]->SetLineColor(1);
  hJetPt[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  TLegend *legend0 = new TLegend(0.45,0.60,0.75,0.85);
  legend0->AddEntry(hJetPt[Ntriggers-1], Form("%s Triggers",trigger[Ntriggers-1]), "l");
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
  hJetRt[Ntriggers-1]->SetTitle("Jets R_{T}");
  //hJetPt[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hJetRt[Ntriggers-1]->SetLineWidth(2); hJetRt[Ntriggers-1]->SetLineColor(1);
  hJetRt[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetRt[i]->SetLineColor(i+2);
    hJetRt[i]->Draw("same");
  }

  c0->cd(4);
  //c0->SetLogy();
  hJetEta[Ntriggers-1]->SetTitle("Jets #eta");
  hJetEta[Ntriggers-1]->GetXaxis()->SetTitle("#eta");
  hJetEta[Ntriggers-1]->SetLineWidth(2); hJetEta[Ntriggers-1]->SetLineColor(1);
  hJetEta[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetEta[i]->SetLineColor(i+2);
    hJetEta[i]->Draw("same");
  }

  c0->cd(5);
  //c0->SetLogy();
  hJetPhi[Ntriggers-1]->SetTitle("Jets #phi");
  hJetPhi[Ntriggers-1]->GetXaxis()->SetTitle("#phi");
  hJetPhi[Ntriggers-1]->SetLineWidth(2); hJetPhi[Ntriggers-1]->SetLineColor(1);
  hJetPhi[Ntriggers-1]->SetMinimum(0);
  hJetPhi[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    //if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetPhi[i]->SetLineColor(i+2);
    hJetPhi[i]->Draw("same");
  }

  c0->cd(6);
  //c0->SetLogy();
  hJetDet[Ntriggers-1]->SetTitle("Jets detector #eta");
  hJetDet[Ntriggers-1]->GetXaxis()->SetTitle("#eta_{det}");
  hJetDet[Ntriggers-1]->SetLineWidth(2); hJetDet[Ntriggers-1]->SetLineColor(1);
  hJetDet[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetDet[i]->SetLineColor(i+2);
    hJetDet[i]->Draw("same");
  }

  //c0->SaveAs("/star/u/aquinter/Run13/InclusiveJets/PlotHisto/JetPt.png");

  c0->Draw();


  /* TCanvas *cUE = new TCanvas("cUE","Jets UE",0,0,1300,700);
  cUE->cd();
  cUE->Divide(3,2);
  
  cUE->cd(1);
  cUE->cd(1)->SetLogy();
  hJetUE[Ntriggers-1]->SetTitle("Underlying event per jet");
  hJetUE[Ntriggers-1]->GetXaxis()->SetTitle("dp_{T} (GeV/c)");
  hJetUE[Ntriggers-1]->SetLineWidth(2); hJetUE[Ntriggers-1]->SetLineColor(1);
  //hJetUE[Ntriggers-1]->SetMinimum(1);
  hJetUE[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hJetUE[i]->SetLineColor(i+2);
    hJetUE[i]->Draw("same");
  }

  cUE->cd(2);
  cUE->cd(2)->SetLogz();
  h2JetPtUE[Ntriggers-1]->SetTitle("Jets UE vs p_{T}");
  h2JetPtUE[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h2JetPtUE[Ntriggers-1]->GetYaxis()->SetTitle("dp_{T} (GeV/c)");
  //h2JetPtUE[Ntriggers-1]->SetLineWidth(2); h2JetPtUE[Ntriggers-1]->SetLineColor(1);
  h2JetPtUE[Ntriggers-1]->Draw("colz");
  //h2JetPtUE[Ntriggers-1]->GetXaxis()->SetRangeUser(0,120);
  TProfile * h2JetPtUE_pfX = h2JetPtUE[Ntriggers-1]->ProfileX();
  h2JetPtUE_pfX->Draw("same");
  h2JetPtUE_pfX->SetDirectory(gROOT);
  
  cUE->cd(3);
  cUE->cd(3)->SetLogz();
  h2JetPtRt[Ntriggers-1]->SetTitle("Jets R_{T} vs p_{T}");
  h2JetPtRt[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  //h2JetPtRt[Ntriggers-1]->SetLineWidth(2); hJetRt[Ntriggers-1]->SetLineColor(1);
  h2JetPtRt[Ntriggers-1]->Draw("colz");
  //h2JetPtRt[Ntriggers-1]->GetXaxis()->SetRangeUser(0,120);
  TProfile * h2JetPtRt_pfX = h2JetPtRt[Ntriggers-1]->ProfileX();
  h2JetPtRt_pfX->Draw("same");
  h2JetPtRt_pfX->SetDirectory(gROOT);

  cUE->cd(4);
  //cUE->cd(3)->SetLogz();
  h2ZDCJetUE[Ntriggers-1]->SetTitle("Jets UE vs ZDC");
  h2ZDCJetUE[Ntriggers-1]->GetXaxis()->SetTitle("ZDC kHz");
  h2ZDCJetUE[Ntriggers-1]->GetYaxis()->SetTitle("dp_{T} (GeV/c)");
  h2ZDCJetUE[Ntriggers-1]->Draw("colz");

  cUE->cd(5);
  TH1D *hUEALL         = new TH1D("hUEALL","Longitudinal Double Spin Asymmetry",nbins_Mass,binEdges_Mass);

  TH1D *hUENumerator = (TH1D*)f.Get("hUENumerator_All");
  TH1D *hUENumeratorErr = (TH1D*)f.Get("hUENumeratorErr_All");
  TH1D *hUEDenominator = (TH1D*)f.Get("hUEDenominator_All");
 
  hUEALL->Divide(hUENumerator,hUEDenominator,1.,1.,"b");
  for(Int_t i=1; i<=hUEALL->GetNbinsX(); i++ ) 
  hUEALL->SetBinError(i,sqrt(hUENumeratorErr->GetBinContent(i))/(hUEDenominator->GetBinContent(i)));
  hUEALL->GetXaxis()->SetTitle("(UE corr.)   p_{T} (GeV/c)");
  hUEALL->GetYaxis()->SetTitle("A_{LL}");
  //hUEALL->SetMarkerStyle(20);
  hUEALL->GetXaxis()->SetRangeUser(0,76.3);
  hUEALL->GetYaxis()->SetRangeUser(-0.0275,0.0275);
  hUEALL->Draw("E");
  hUEALL->SetDirectory(gROOT);

  //cUE->cd(6);
 
  cUE->Draw();
  */
  //////END Jets Plots <--6--
  
 
  //////Track Plots --7-->
  TCanvas *c1 = new TCanvas("c1","Tracks",0,0,1300,700);
  c1->cd();
  c1->Divide(3,2);
  
  c1->cd(1);
  c1->cd(1)->SetLogy();
  hTrackIdx[Ntriggers-1]->SetTitle("Tracks per jet");
  //hTrackIdx[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hTrackIdx[Ntriggers-1]->SetLineWidth(2); hTrackIdx[Ntriggers-1]->SetLineColor(1);
  hTrackIdx[Ntriggers-1]->SetMinimum(0.1);
  hTrackIdx[Ntriggers-1]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackIdx[i]->SetLineColor(i+2);
    hTrackIdx[i]->Draw("same");
  }

  c1->cd(2);
  c1->cd(2)->SetLogy();
  hTrackPt[Ntriggers-1]->SetTitle("Tracks Transverse Momentum");
  hTrackPt[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hTrackPt[Ntriggers-1]->SetLineWidth(2); hTrackPt[Ntriggers-1]->SetLineColor(1);
  hTrackPt[Ntriggers-1]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  //TLegend *legend0 = new TLegend(0.6,0.70,0.85,0.85);
  //legend0->AddEntry(hTrackPt[Ntriggers-1], Form("%s Triggers",trigger[Ntriggers-1]), "l");
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
  hTrackDcaXY[Ntriggers-1]->SetTitle("Tracks DCA_{XY}");
  hTrackDcaXY[Ntriggers-1]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
  hTrackDcaXY[Ntriggers-1]->SetLineWidth(2); hTrackDcaXY[Ntriggers-1]->SetLineColor(1);
  hTrackDcaXY[Ntriggers-1]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackDcaXY[i]->SetLineColor(i+2);
    hTrackDcaXY[i]->Draw("same");
  }

  c1->cd(4);
  //c1->SetLogy();
  hTrackEta[Ntriggers-1]->SetTitle("Tracks #eta");
  hTrackEta[Ntriggers-1]->GetXaxis()->SetTitle("#eta");
  hTrackEta[Ntriggers-1]->SetLineWidth(2); hTrackEta[Ntriggers-1]->SetLineColor(1);
  hTrackEta[Ntriggers-1]->SetMinimum(0);
  hTrackEta[Ntriggers-1]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackEta[i]->SetLineColor(i+2);
    hTrackEta[i]->Draw("same");
  }

  c1->cd(5);
  //c1->SetLogy();
  hTrackPhi[Ntriggers-1]->SetTitle("Tracks #phi");
  hTrackPhi[Ntriggers-1]->GetXaxis()->SetTitle("#phi");
  hTrackPhi[Ntriggers-1]->SetLineWidth(2); hTrackPhi[Ntriggers-1]->SetLineColor(1);
  hTrackPhi[Ntriggers-1]->SetMinimum(0);
  hTrackPhi[Ntriggers-1]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    //if(hTrackPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTrackPhi[i]->SetLineColor(i+2);
    hTrackPhi[i]->Draw("same");
  }

  c1->cd(6);
  //c1->SetLogy();
  hTrackDcaZ[Ntriggers-1]->SetTitle("Tracks DCA_{Z}");
  hTrackDcaZ[Ntriggers-1]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
  hTrackDcaZ[Ntriggers-1]->SetLineWidth(2); hTrackDcaZ[Ntriggers-1]->SetLineColor(1);
  hTrackDcaZ[Ntriggers-1]->Draw("");
  //hTrackPt->GetXaxis()->SetRangeUser(0,100);
  //TrackPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
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
  hTowerIdx[Ntriggers-1]->SetTitle("Towers per jet");
  //hTowerIdx[Ntriggers-1]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hTowerIdx[Ntriggers-1]->SetLineWidth(2); hTowerIdx[Ntriggers-1]->SetLineColor(1);
  hTowerIdx[Ntriggers-1]->SetMinimum(0.1);
  hTowerIdx[Ntriggers-1]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerIdx[i]->SetLineColor(i+2);
    hTowerIdx[i]->Draw("same");
  }

  c2->cd(2);
  c2->cd(2)->SetLogy();
  hTowerPt[Ntriggers-1]->SetTitle("Towers Transverse Energy");        //Tower Pt does not exist is Tower ET
  hTowerPt[Ntriggers-1]->GetXaxis()->SetTitle("E_{T} (GeV)");
  hTowerPt[Ntriggers-1]->SetLineWidth(2); hTowerPt[Ntriggers-1]->SetLineColor(1);
  hTowerPt[Ntriggers-1]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  //TLegend *legend0 = new TLegend(0.6,0.70,0.85,0.85);
  //legend0->AddEntry(hTowerPt[Ntriggers-1], Form("%s Triggers",trigger[Ntriggers-1]), "l");
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
  hTowerE[Ntriggers-1]->SetTitle("Towers Energy");
  hTowerE[Ntriggers-1]->GetXaxis()->SetTitle("E (GeV)");
  hTowerE[Ntriggers-1]->SetLineWidth(2); hTowerE[Ntriggers-1]->SetLineColor(1);
  hTowerE[Ntriggers-1]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerE[i]->SetLineColor(i+2);
    hTowerE[i]->Draw("same");
  }

  c2->cd(4);
  //c1->SetLogy();
  hTowerEta[Ntriggers-1]->SetTitle("Towers #eta");
  hTowerEta[Ntriggers-1]->GetXaxis()->SetTitle("#eta");
  hTowerEta[Ntriggers-1]->SetLineWidth(2); hTowerEta[Ntriggers-1]->SetLineColor(1);
  hTowerEta[Ntriggers-1]->SetMinimum(0);
  hTowerEta[Ntriggers-1]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerEta[i]->SetLineColor(i+2);
    hTowerEta[i]->Draw("same");
  }

  c2->cd(5);
  //c1->SetLogy();
  hTowerPhi[Ntriggers-1]->SetTitle("Towers #phi");
  hTowerPhi[Ntriggers-1]->GetXaxis()->SetTitle("#phi");
  hTowerPhi[Ntriggers-1]->SetLineWidth(2); hTowerPhi[Ntriggers-1]->SetLineColor(1);
  hTowerPhi[Ntriggers-1]->SetMinimum(0);
  hTowerPhi[Ntriggers-1]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    //if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerPhi[i]->SetLineColor(i+2);
    hTowerPhi[i]->Draw("same");
  }
  
  c2->cd(6);
  //c1->SetLogy();
  hTowerAdc[Ntriggers-1]->SetTitle("Towers Adc");
  //hTowerAdc[Ntriggers-1]->GetXaxis()->SetTitle("");
  hTowerAdc[Ntriggers-1]->SetLineWidth(2); hTowerAdc[Ntriggers-1]->SetLineColor(1);
  hTowerAdc[Ntriggers-1]->Draw("");
  //hTowerPt->GetXaxis()->SetRangeUser(0,100);
  //TowerPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hTowerPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hTowerAdc[i]->SetLineColor(i+2);
    hTowerAdc[i]->Draw("same");
  }

  //c1->SaveAs("/star/u/aquinter/Run13/InclusiveTowers/PlotHisto/TowerPt.png");

  c2->Draw();
  //////END Plot Towers<--8--


  //////DiJets Plots --9-->
  TCanvas *cM = new TCanvas("cM","DiJets",0,0,900,600);
  cM->cd();
  cM->Divide(2,2);
  
  cM->cd(1);
  cM->cd(1)->SetLogy();
  hDiJetMass[Ntriggers-1]->SetTitle("DiJets invariant Mass");
  hDiJetMass[Ntriggers-1]->GetXaxis()->SetTitle("M_{inv} (GeV/c^{2})");
  hDiJetMass[Ntriggers-1]->SetLineWidth(2); hDiJetMass[Ntriggers-1]->SetLineColor(1);
  hDiJetMass[Ntriggers-1]->SetMinimum(0.1);
  hDiJetMass[Ntriggers-1]->Draw("");
  //hJetPt->GetXaxis()->SetRangeUser(0,100);
  //JetPt[Ntriggers-1]->GetYaxis()->SetRangeUser(1e-4,5e-1);
  for(int i = 0; i < Ntriggers-1; i++){  //Skip the first histogram
    // if(hJetPt[i]->GetEntries()==0) {cout << Form("No entries for %s trigger",trigger[i]) << endl; continue;}
    hDiJetMass[i]->SetLineColor(i+2);
    hDiJetMass[i]->Draw("same");
  }

  cM->cd(2);
  //cM->cd(2)->SetLogy();
  //hDiJetdPhi[Ntriggers-1]->SetTitle("DiJets #Delta cos(#Phi)");
  hDiJetdPhi[Ntriggers-1]->GetXaxis()->SetTitle("DiJets #Delta cos(#Phi)");
  hDiJetdPhi[Ntriggers-1]->SetLineWidth(2); hDiJetdPhi[Ntriggers-1]->SetLineColor(1);
  hDiJetdPhi[Ntriggers-1]->Draw("");
  legend0->Draw();

  cM->cd(3);
  //cM->cd(2)->SetLogy();
  hDiJetUE[Ntriggers-1]->SetTitle("DiJets UE Mass_{inv}");
  hDiJetUE[Ntriggers-1]->GetXaxis()->SetTitle("UE M_{inv} (GeV/c^{2})");
  hDiJetUE[Ntriggers-1]->SetLineWidth(2); hDiJetUE[Ntriggers-1]->SetLineColor(1);
  hDiJetUE[Ntriggers-1]->Draw("");

  cM->cd(4);
  cM->cd(4)->SetLogz();
  h2DiJetMassUE[Ntriggers-1]->SetTitle("DiJets UE Mass_{inv}");
  h2DiJetMassUE[Ntriggers-1]->GetXaxis()->SetTitle("UE M_{inv} (GeV/c^{2})");
  h2DiJetMassUE[Ntriggers-1]->SetLineWidth(2); h2DiJetMassUE[Ntriggers-1]->SetLineColor(1);
  h2DiJetMassUE[Ntriggers-1]->Draw("colz");


  TProfile * h2DiJetMassRt_pfX = h2DiJetMassRt[2]->ProfileX();



  //////END DiJets Plots <--9--
  

  for(int i = 0; i < Ntriggers; i++){  //NEED THIS TO PLOT EACH HISTOGRAM
    //DiJet
    hDiJetMass[i]->SetDirectory(gROOT);
    hDiJetdPhi[i]->SetDirectory(gROOT);
    hDiJetUE[i]->SetDirectory(gROOT);
    h2DiJetMassUE[i]->SetDirectory(gROOT);
    h2DiJetMassRt[i]->SetDirectory(gROOT);
    //Jet
    hJetIdx[i]->SetDirectory(gROOT); hJetPt[i]->SetDirectory(gROOT); hJetRt[i]->SetDirectory(gROOT);
    hJetEta[i]->SetDirectory(gROOT); hJetPhi[i]->SetDirectory(gROOT); hJetDet[i]->SetDirectory(gROOT);
    // hJetUE[i]->SetDirectory(gROOT); h2JetPtRt[i]->SetDirectory(gROOT); h2JetPtUE[i]->SetDirectory(gROOT);
    //h2ZDCJetUE[i]->SetDirectory(gROOT);  h2JetPtrUE[i]->SetDirectory(gROOT);
    //Track
    hTrackIdx[i]->SetDirectory(gROOT); hTrackPt[i]->SetDirectory(gROOT); hTrackDcaXY[i]->SetDirectory(gROOT);
    hTrackEta[i]->SetDirectory(gROOT); hTrackPhi[i]->SetDirectory(gROOT); hTrackDcaZ[i]->SetDirectory(gROOT);
    //Tower
    hTowerIdx[i]->SetDirectory(gROOT); hTowerPt[i]->SetDirectory(gROOT); hTowerE[i]->SetDirectory(gROOT);
    hTowerEta[i]->SetDirectory(gROOT); hTowerPhi[i]->SetDirectory(gROOT); hTowerAdc[i]->SetDirectory(gROOT);
  }


  cout << "Rt average per bin - " << topology[iTop] << ": " << endl;
  for(Int_t iii = 2; iii<=nbins_Mass-1; iii++){
    cout << h2DiJetMassRt_pfX->GetBinContent(iii) << endl;
  }



  cout << "Mass average per bin: " << endl;
  cout << "Average Mass - " << topology[iTop] << ": " << endl;
  for(Int_t iii = 1; iii<nbins_Mass-1; iii++){
    Int_t BinL = hDiJetMass[Ntriggers-1]->GetXaxis()->FindBin(binEdges_Mass[iii]);
    Int_t BinH = hDiJetMass[Ntriggers-1]->GetXaxis()->FindBin(binEdges_Mass[iii+1]);
    hDiJetMass[Ntriggers-1]->GetXaxis()->SetRange(BinL,BinH);  
    
    //hDiJetMass[Ntriggers-1]->GetXaxis()->SetRange(binEdges_Mass[iii]*10,binEdges_Mass[iii+1]*10);   //Might need to multiply by 10 due the binning
    //cout << Form("% .1f - % .1f:   avg: % .2f",binEdges_Mass[iii],binEdges_Mass[iii+1],hJetPt[Ntriggers-1]->GetMean()) << endl;
    cout <<  Form("%.2f",hDiJetMass[Ntriggers-1]->GetMean()) << endl;
    //if(iii==nbins_Mass-1) cout << "};"<< endl; 
    //else cout << ",";
    hDiJetMass[Ntriggers-1]->GetXaxis()->SetRange();
  }
 
  /* cout << "Rt average per bin: " << endl;
  for(Int_t iii = 1; iii<=nbins_Mass; iii++){
    cout << h2JetPtRt_pfX->GetBinContent(iii) << endl;
    }*/
      
  TDatime now1;
  now1.Print();
}
  

