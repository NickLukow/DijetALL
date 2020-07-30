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

//Author Nick Lukow
//--->START MAIN PROGRAM
void PlotTune(){
  
  TDatime now;                                          //Set time in Root
  now.Print();
  const int iTop = 1;  // 0 = EW, 1 = EEWW, 2 = Full
  //gStyle->SetOptDate(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  



  TFile f_370("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_370.root"); if (f_370.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_371("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_371.root"); if (f_371.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_372("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_372.root"); if (f_372.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_374("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_374.root"); if (f_374.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_376("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_376.root"); if (f_376.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_377("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_377.root"); if (f_377.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_378("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_378.root"); if (f_378.IsZombie()) {cout << "File failed!" << endl; return;}
  TFile f_383("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PythiaTune/Tune_383.root"); if (f_383.IsZombie()) {cout << "File failed!" << endl; return;}
  //cout << "Input file: " << eachfile << endl;

  

  ////////////A_LL calculation --3-->
  const Int_t Ntopol = 3;
  const char *topology[Ntopol]= {"EW", "EEWW", "Full"};
  
  const int nbins_Mass = 9;     
  const double binEdges_Mass[nbins_Mass+1] = { 13.0, 17.0, 19.0, 23.0, 28.0, 34.0, 41.0, 58.0, 82.0, 120.0};


  TProfile *t370 = (TProfile*)f_370.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t371 = (TProfile*)f_371.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t372 = (TProfile*)f_372.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t374 = (TProfile*)f_374.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t376 = (TProfile*)f_376.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t377 = (TProfile*)f_377.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t378 = (TProfile*)f_378.Get(Form("MassShift_%s", topology[iTop]));
  TProfile *t383 = (TProfile*)f_383.Get(Form("MassShift_%s", topology[iTop]));

  TProfile *td370 = (TProfile*)t370->Clone();
  td370->Add(t370, -1);
  TProfile *td371 = (TProfile*)t371->Clone();
  td371->Add(t370, -1);
  TProfile *td372 = (TProfile*)t372->Clone();
  td372->Add(t370, -1);
  TProfile *td374 = (TProfile*)t374->Clone();
  td374->Add(t370, -1);
  TProfile *td376 = (TProfile*)t376->Clone();
  td376->Add(t370, -1);
  TProfile *td377 = (TProfile*)t377->Clone();
  td377->Add(t370, -1);
  TProfile *td378 = (TProfile*)t378->Clone();
  td378->Add(t370, -1);
  TProfile *td383 = (TProfile*)t383->Clone();
  td383->Add(t370, -1);


  TProfile *tSysSum = new TProfile("tSysSum", "Sum", 9, binEdges_Mass );
  TProfile *tSys371_372 = new TProfile("tSys371_372", "371/372", 9, binEdges_Mass );
  TProfile *tSys374 = (TProfile*)td374->Clone();
  TProfile *tSys376_377 = new TProfile("tSys376_377", "376/377", 9, binEdges_Mass );
  TProfile *tSys378 = (TProfile*)td378->Clone();
  TProfile *tSys383 = (TProfile*)td383->Clone();


  TCanvas *c0 = new TCanvas("c0","Tune Shifts",0,0,1000,700);
  c0->cd();
  Int_t colorCount = 1;
  t370->SetLineColor(colorCount);
  t370->Draw("hist");
  t370->GetXaxis()->SetRangeUser(17.0,82.0);
  t370->GetYaxis()->SetRangeUser(0,1.5);
  t370->SetTitle(Form("Mass Shifts for %s", topology[iTop]));
  colorCount++;

  t371->SetLineColor(colorCount);
  t371->Draw("hist same");
  colorCount++;
  
  t372->SetLineColor(colorCount);
  t372->Draw("hist same");
  colorCount++;

  t374->SetLineColor(colorCount);
  t374->Draw("hist same");
  colorCount++;

  t376->SetLineColor(colorCount);
  t376->Draw("hist same");
  colorCount++;

  t377->SetLineColor(colorCount);
  t377->Draw("hist same");
  colorCount++;

  t378->SetLineColor(colorCount);
  t378->Draw("hist same");
  colorCount++;

  t383->SetLineColor(colorCount);
  t383->Draw("hist same");
  colorCount++;


  TLegend *legend0 = new TLegend(0.42,0.60,0.75,0.875);
  
    legend0->AddEntry(t370, "Tune 370", "l");
    legend0->AddEntry(t371, "Tune 371", "l");
    legend0->AddEntry(t372, "Tune 372", "l");
    legend0->AddEntry(t374, "Tune 374", "l");
    legend0->AddEntry(t376, "Tune 376", "l");
    legend0->AddEntry(t377, "Tune 377", "l");
    legend0->AddEntry(t378, "Tune 378", "l");
    legend0->AddEntry(t383, "Tune 383", "l");
  
  legend0->SetTextSize(0.03);
  legend0->SetBorderSize(0);
  legend0->SetFillStyle(0);
  legend0->Draw();

  //c0->SaveAs("/star/u/aquinter/Run13/InclusiveJets/PlotHisto/JetPt.png");

  c0->Draw();


TCanvas *c1 = new TCanvas("c1","Tune Shifts Difference From 370",0,0,1000,700);
  c1->cd();
  

  
  
  
  
  colorCount = 1;
  td370->SetLineColor(colorCount);
  td370->Draw("hist");
  td370->GetXaxis()->SetRangeUser(17.0,82.0);
  td370->GetYaxis()->SetRangeUser(-0.3,0.3);
  td370->SetTitle(Form("Mass Shift Difference From Tune 370 for %s", topology[iTop]));
  colorCount++;

  td371->SetLineColor(colorCount);
  td371->Draw("hist same");
  colorCount++;
  
  td372->SetLineColor(colorCount);
  td372->Draw("hist same");
  colorCount++;

  td374->SetLineColor(colorCount);
  td374->Draw("hist same");
  colorCount++;

  td376->SetLineColor(colorCount);
  td376->Draw("hist same");
  colorCount++;

  td377->SetLineColor(colorCount);
  td377->Draw("hist same");
  colorCount++;

  td378->SetLineColor(colorCount);
  td378->Draw("hist same");
  colorCount++;

  td383->SetLineColor(colorCount);
  td383->Draw("hist same");
  colorCount++;

  legend0->Draw();

  //c0->SaveAs("/star/u/aquinter/Run13/InclusiveJets/PlotHisto/JetPt.png");

  c1->Draw();

TCanvas *c2 = new TCanvas("c2","Tune Systematics",0,0,1000,700);
  c2->cd();
  colorCount = 1;
  for (int ibin = 0; ibin<9; ibin++)
  {
    Float_t temp371, temp372, temp374, temp376, temp377, temp378, temp383;
    temp371 = td371->GetBinContent(ibin);
    temp372 = td372->GetBinContent(ibin);
    temp374 = td374->GetBinContent(ibin);
    temp376 = td376->GetBinContent(ibin);
    temp377 = td377->GetBinContent(ibin);
    temp378 = td378->GetBinContent(ibin);
    temp383 = td383->GetBinContent(ibin);


    Float_t temp371_372, temp376_377;
    if (TMath::Abs(temp371) > TMath::Abs(temp372)) temp371_372 = temp371;
    else temp371_372 = temp372;

    if (TMath::Abs(temp376) > TMath::Abs(temp377)) temp376_377 = temp376;
    else temp376_377 = temp377;


    tSys376_377->Fill(binEdges_Mass[ibin]+0.1, temp376_377);
    tSys371_372->Fill(binEdges_Mass[ibin]+0.1, temp371_372);

    Float_t QuadratureSum = 0;
    QuadratureSum = temp371_372*temp371_372 + temp374*temp374 + temp376_377*temp376_377 + temp378*temp378 + temp383*temp383;
    QuadratureSum = TMath::Sqrt(QuadratureSum);


    tSysSum->Fill(binEdges_Mass[ibin]+0.1, QuadratureSum);
    
  }
  tSysSum->SetLineColor(colorCount);
  tSysSum->Draw("hist");
  tSysSum->GetXaxis()->SetRangeUser(17.0,82.0);
  tSysSum->GetYaxis()->SetRangeUser(-0.3,0.8);
  tSysSum->SetTitle(Form("Tune Systematics for %s", topology[iTop]));
  colorCount++;

  tSys371_372->SetLineColor(colorCount);
  tSys371_372->Draw("hist same");
  colorCount++;
  

  tSys374->SetLineColor(colorCount);
  tSys374->Draw("hist same");
  colorCount++;

  tSys376_377->SetLineColor(colorCount);
  tSys376_377->Draw("hist same");
  colorCount++;

  tSys378->SetLineColor(colorCount);
  tSys378->Draw("hist same");
  colorCount++;

  tSys383->SetLineColor(colorCount);
  tSys383->Draw("hist same");
  colorCount++;
  


  TLegend *legend1 = new TLegend(0.42,0.60,0.75,0.875);
  
    legend1->AddEntry(tSysSum, "Sum", "l");
    legend1->AddEntry(tSys371_372, "Tune 371/372", "l");
    legend1->AddEntry(tSys374, "Tune 374", "l");
    legend1->AddEntry(tSys376_377, "Tune 376/377", "l");
    legend1->AddEntry(tSys378, "Tune 378", "l");
    legend1->AddEntry(tSys383, "Tune 383", "l");
  
  legend1->SetTextSize(0.03);
  legend1->SetBorderSize(0);
  legend1->SetFillStyle(0);
  legend1->Draw();

  //c0->SaveAs("/star/u/aquinter/Run13/InclusiveJets/PlotHisto/JetPt.png");

  c2->Draw();





  //NEED THIS TO PLOT EACH HISTOGRAM
  t370->SetDirectory(gROOT);
  t371->SetDirectory(gROOT);
  t372->SetDirectory(gROOT);
  t374->SetDirectory(gROOT);
  t376->SetDirectory(gROOT);
  t377->SetDirectory(gROOT);
  t378->SetDirectory(gROOT);
  t383->SetDirectory(gROOT);

  td370->SetDirectory(gROOT);
  td371->SetDirectory(gROOT);
  td372->SetDirectory(gROOT);
  td374->SetDirectory(gROOT);
  td376->SetDirectory(gROOT);
  td377->SetDirectory(gROOT);
  td378->SetDirectory(gROOT);
  td383->SetDirectory(gROOT);
  
  tSysSum->SetDirectory(gROOT);
  tSys371_372->SetDirectory(gROOT);
  tSys374->SetDirectory(gROOT);
  tSys376_377->SetDirectory(gROOT);
  tSys378->SetDirectory(gROOT);
  tSys383->SetDirectory(gROOT);



  cout << "Tune Systematic per bin - " << topology[iTop] << ": " << endl;
  for(Int_t iii = 2; iii<nbins_Mass; iii++){
    cout << tSysSum->GetBinContent(iii) << endl;
  }


 
  TDatime now1;
  now1.Print();
}
  

