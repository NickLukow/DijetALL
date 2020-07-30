#include <string>
#include "Riostream.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TString.h"
#include "TDatime.h"
#include "TMath.h"
#include "TStyle.h"


//--->START MAIN PROGRAM
//________________________________________________________________________________
void Plot_UE(const Char_t *dirname= "/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Data/Runs/", const Char_t *ext=".root") {
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();



  gStyle->SetOptDate(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  //Topology Selection
  const int topol = 0; // 0 = EW, 1 = EEWW, 2 = Full

  const int yscalebool = 1;

  static const double yaxisscale = 0.08;
  static const double xaxismax = 82; 

  //gROOT->cd();
  TDatime now;                                          //Set time in Root
  now.Print();
  
  static const int nbins = 9;         
  const double binEdges[nbins+1] = { 13.0, 17.0, 19.0, 23.0, 28.0, 34.0, 41.0, 58.0, 82.0, 120.0};

  static const int nTops = 3;
  const char* Topology[nTops] = {"EW", "EEWW", "Full"};

  Float_t JP1PS = 9.92;

  /*
  //Make array of TgraphErrors? 
  TGraphErrors *UEvsRun[7];

  for (int ibin = 0; ibin < 7; ibin++)
  {
    UEvsRun[ibin] = new TGraphErrors();
  }
*/

TGraphErrors *Bin1 = new TGraphErrors();
TGraphErrors *Bin2 = new TGraphErrors();
TGraphErrors *Bin3 = new TGraphErrors();
TGraphErrors *Bin4 = new TGraphErrors();
TGraphErrors *Bin5 = new TGraphErrors();
TGraphErrors *Bin6 = new TGraphErrors();
TGraphErrors *Bin7 = new TGraphErrors();




Double_t CentralValues[7][557];
Double_t ErrorValues[7][557];
Double_t XValue[557];
Double_t XWidths[557];
for (int itemp = 0; itemp < 557; itemp++){
  XWidths[itemp] = 0.1;
  XValue[itemp]=itemp;
}
  //////////Read all files --2-->
  Int_t count=0;
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  if (files) {
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      fname = file->GetName();
      if (!file->IsDirectory() && fname.EndsWith(ext)) {
	      Char_t eachfile[100];
	      sprintf(eachfile,"%s%s",dirname,fname.Data());
  
	      TFile f(eachfile); if (f.IsZombie()) {cout<< "Problems with file: " << fname.Data() << endl; continue;}

	      TString runnumberfile(&eachfile[28]);//
	      //TString runnumberfile(&eachfile[26]);
	      TString runnumber(runnumberfile(0,8));

        //starting with bin 16-19 and ending with the bin 58-82
	      for(Int_t i=2; i<=nbins-1; i++ ){ 

	        Float_t Value = ((TProfile*)f.Get(Form("hUEAsymmetry_All_%s",Topology[topol])))->GetBinContent(i);
	        Float_t Error = ((TProfile*)f.Get(Form("hUEAsymmetry_All_%s",Topology[topol])))->GetBinError(i);

          //cout << "Bin " << i << "  Value: " << Value << "     -Error: " << Error << endl;
          CentralValues[i-2][count] = Value;
          ErrorValues[i-2][count] = Error;

          //checking events
          Int_t ppCount = ((TH1D*)f.Get(Form("hUECounter_pp_All_%s",Topology[topol])))->GetBinContent(i);
          Int_t mmCount = ((TH1D*)f.Get(Form("hUECounter_mm_All_%s",Topology[topol])))->GetBinContent(i);
          Int_t mpCount = ((TH1D*)f.Get(Form("hUECounter_mp_All_%s",Topology[topol])))->GetBinContent(i);
          Int_t pmCount = ((TH1D*)f.Get(Form("hUECounter_pm_All_%s",Topology[topol])))->GetBinContent(i);

          //cout << "ppCount for bin " << i-1 << " : " << ppCount << endl;
          //cout << "mmCount for bin " << i-1 << " : " << mmCount << endl;
          //cout << "mpCount for bin " << i-1 << " : " << mpCount << endl;
          //cout << "pmCount for bin " << i-1 << " : " << pmCount << endl;

          Int_t CutThreshold = 3; //3
          bool NoCut = true;
          if ( ppCount < CutThreshold || mmCount < CutThreshold || mpCount < CutThreshold || pmCount < CutThreshold ) NoCut = false;

          //Change how the points are added to the TGraphErrors... Do it manually point by point so that I can skip points without assigning a dummy value...
          if (i == 2 && NoCut){ Bin1->SetPoint(count, count, Value ); Bin1->SetPointError(count, 0.1, Error);}
          if (i == 3 && NoCut){ Bin2->SetPoint(count, count, Value ); Bin2->SetPointError(count, 0.1, Error);}
          if (i == 4 && NoCut){ Bin3->SetPoint(count, count, Value ); Bin3->SetPointError(count, 0.1, Error);}
          if (i == 5 && NoCut){ Bin4->SetPoint(count, count, Value ); Bin4->SetPointError(count, 0.1, Error);}
          if (i == 6 && NoCut){ Bin5->SetPoint(count, count, Value ); Bin5->SetPointError(count, 0.1, Error);}
          if (i == 7 && NoCut){ Bin6->SetPoint(count, count, Value ); Bin6->SetPointError(count, 0.1, Error);}
          if (i == 8 && NoCut){ Bin7->SetPoint(count, count, Value ); Bin7->SetPointError(count, 0.1, Error);}// cout << "setting point for Bin 7 at : " << count << "Counts pp/mm/mp/pm : " << ppCount << "/" << mmCount << "/" << mpCount << "/" << pmCount << endl;}

        }
	      

	      count++;
	      if (count%100==0) {cout << "Files: " << count << endl;}
	      //if (count==10) break;
      }
    }
  }


  
  
  cout << "Total number of files: " << count << endl;
  //////////END Reading all files <--2--



  TCanvas *cUE = new TCanvas("cUE","UE Asymetries",0,0,1200,900);
  cUE->cd();
  cUE->Divide(2,4);
  
  TF1 *Fit1 = new TF1 ("Fit1", "pol0");
  TF1 *Fit2 = new TF1 ("Fit2", "pol0");
  TF1 *Fit3 = new TF1 ("Fit3", "pol0");
  TF1 *Fit4 = new TF1 ("Fit4", "pol0");
  TF1 *Fit5 = new TF1 ("Fit5", "pol0");
  TF1 *Fit6 = new TF1 ("Fit6", "pol0");
  TF1 *Fit7 = new TF1 ("Fit7", "pol0");


  cUE->cd(1);
  Bin1->SetTitle("Bin 1");
  if (yscalebool == 1) Bin1->GetYaxis()->SetRangeUser(-5,5);
  Bin1->Draw("AP");
  Bin1->Fit("Fit1");

  cUE->cd(2);
  Bin2->SetTitle("Bin 2");
  if (yscalebool == 1) Bin2->GetYaxis()->SetRangeUser(-5,5);
  Bin2->Draw("AP");
  Bin2->Fit("Fit2");

  cUE->cd(3);
  Bin3->SetTitle("Bin 3");
  if (yscalebool == 1) Bin3->GetYaxis()->SetRangeUser(-5,5);
  Bin3->Draw("AP");
  Bin3->Fit("Fit3");

  cUE->cd(4);
  Bin4->SetTitle("Bin 4");
  if (yscalebool == 1) Bin4->GetYaxis()->SetRangeUser(-5,5);
  Bin4->Draw("AP");
  Bin4->Fit("Fit4");

  cUE->cd(5);
  Bin5->SetTitle("Bin 5");
  if (yscalebool == 1) Bin5->GetYaxis()->SetRangeUser(-5,5);
  Bin5->Draw("AP");
  Bin5->Fit("Fit5");

  cUE->cd(6);
  Bin6->SetTitle("Bin 6");
  if (yscalebool == 1) Bin6->GetYaxis()->SetRangeUser(-5,5);
  Bin6->Draw("AP");
  Bin6->Fit("Fit6");

  cUE->cd(7);
  Bin7->SetTitle("Bin 7");
  if (yscalebool == 1) Bin7->GetYaxis()->SetRangeUser(-5,5);
  Bin7->Draw("AP");
  Bin7->Fit("Fit7");
  
//cUE->SaveAs(Form("/home/nick/Documents/AnalysisFolder/Figures/DiJetUEWithCut_%s.pdf", Topology[topol]));


// tacked on Code
  

 
  //TFile fdata("/home/nick/Documents/AnalysisFolder/Working_A_LL/Histograms/Dijet/Data/testData.root");
  TFile fdata("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Data/Data.root");
  TFile fembe("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/Embedding/Embedding.root");

  //new code
  TH2D *hDijetMassUEJP2   =(TH2D*)fembe.Get(Form("h2DiJetMassUE_JP2_%s",Topology[topol]));
  TH2D *hDijetMassUEJP1   =(TH2D*)fembe.Get(Form("h2DiJetMassUE_JP1_%s",Topology[topol]));
  TH2D *hDijetMassUEEmbe     =(TH2D*)hDijetMassUEJP2->Clone();
  hDijetMassUEEmbe->Add(hDijetMassUEJP1,1/JP1PS); 
  TProfile *pDijetMassUEEmbe = hDijetMassUEEmbe->ProfileX(Form("pDijetMassUEEmb_All_%s", Topology[topol]));
 

  

  TH1D* hUEALL; // histogram for ALL uncertainty
  TString histname="";
  
  
    //Defining Histogram
    histname=Form("hUnderlyingEventAsymmetry_All_%s", Topology[topol]);
    hUEALL = new TH1D(histname, histname, nbins, binEdges); 
    //double check and make sure bins are plotted at the right places!!!!
      hUEALL->SetBinContent(2, Fit1->GetParameter(0));
      hUEALL->SetBinError(2, Fit1->GetParError(0));           
      hUEALL->SetBinContent(3, Fit2->GetParameter(0));
      hUEALL->SetBinError(3, Fit2->GetParError(0)); 
      hUEALL->SetBinContent(4, Fit3->GetParameter(0));
      hUEALL->SetBinError(4, Fit3->GetParError(0)); 
      hUEALL->SetBinContent(5, Fit4->GetParameter(0));
      hUEALL->SetBinError(5, Fit4->GetParError(0)); 
      hUEALL->SetBinContent(6, Fit5->GetParameter(0));
      hUEALL->SetBinError(6, Fit5->GetParError(0)); 
      hUEALL->SetBinContent(7, Fit6->GetParameter(0));
      hUEALL->SetBinError(7, Fit6->GetParError(0)); 
      hUEALL->SetBinContent(8, Fit7->GetParameter(0));
      hUEALL->SetBinError(8, Fit7->GetParError(0)); 
 
 
 
  TGraph *gCS[3]; // cross-section graphs
  /*
  gCS[2] = new TGraph("TheoryCurves/TEST/NewTest/FULL.RES", "%lg %lg"); //Full
  gCS[0] = new TGraph("TheoryCurves/TEST/NewTest/EW.RES", "%lg %lg"); //EW
  gCS[1] = new TGraph("TheoryCurves/TEST/NewTest/EEWW.RES", "%lg %lg"); //EEWW
*/

  gCS[2] = new TGraph("TheoryCurves/FULL.RES", "%lg %lg"); //Full
  gCS[0] = new TGraph("TheoryCurves/EW.RES", "%lg %lg"); //EW
  gCS[1] = new TGraph("TheoryCurves/EEWW.RES", "%lg %lg"); //EEWW

/*
  gCS[2] = new TGraph("TheoryCurves/Pythia_fromDmitry/FULL.RES", "%lg %lg"); //Full
  gCS[0] = new TGraph("TheoryCurves/Pythia_fromDmitry/EW.RES", "%lg %lg"); //EW
  gCS[1] = new TGraph("TheoryCurves/Pythia_fromDmitry/EEWW.RES", "%lg %lg"); //EEWW

  gCS[2] = new TGraph("TheoryCurves/NewTest/FULL.RES", "%lg %lg"); //Full
  gCS[0] = new TGraph("TheoryCurves/NewTest/EW.RES", "%lg %lg"); //EW
  gCS[1] = new TGraph("TheoryCurves/NewTest/EEWW.RES", "%lg %lg"); //EEWW


  gCS[2] = new TGraph("TheoryCurves/CT10/FULL.RES", "%lg %lg"); //Full
  gCS[0] = new TGraph("TheoryCurves/CT10/EW.RES", "%lg %lg"); //EW
  gCS[1] = new TGraph("TheoryCurves/CT10/EEWW.RES", "%lg %lg"); //EEWW
*/

  TH2D *hDijetMassUE[3][3]; // 2D histos UE dpT vs jet pT
  TProfile *pDijetMassUE[3][3]; // profile with mean UE dpT per pT bin
  TF1 *fcs[3][14]; // function to fit cross section
  TH1D *hUEAsym[3]; // histo with final ALL uncertainties
  

cout << "UE ALL FITTING" << endl;
TF1 *pol0Fit;
TF1 *pol0Draw;
pol0Fit = new TF1("pol0Fit","pol0",17,82);
pol0Draw = new TF1("pol0Draw","pol0",17,82);
if(topol==2)hUEALL->Fit("pol0Fit","","",17,82.);
else hUEALL->Fit("pol0Fit","","",17,82);
pol0Draw->SetParameter(0,pol0Fit->GetParameter(0));
double dMALLMean = pol0Fit->GetParameter(0);

  gStyle->SetOptFit(1);
cout << "END UE ALL FITTING" << endl;


  
    //for(int t=0; t<3; t++) {
      int t = 0;
      hDijetMassUE[t][topol] = (TH2D*)fdata.Get(Form("h2DiJetMassUE_All_%s",  Topology[topol]));
      pDijetMassUE[t][topol] = hDijetMassUE[t][topol]->ProfileX(Form("pDijetMassUE_All_%s", Topology[topol]));
    //}

    histname=Form("hUEAsym_%s", Topology[topol]);
    hUEAsym[topol] = new TH1D(histname, histname, nbins, binEdges); 
    
    for(int b=1; b<9; b++) { // loop over bins starting from 6GeV (bin #2)
      double all = dMALLMean; //hUEALL->GetBinContent(b+1); // dpT ALL
      double dpt = pDijetMassUE[0][topol]->GetBinContent(b+1); // average dpT per bin
      double egdelow = binEdges[b]; // low pT bin edge
      double egdehigh = binEdges[b+1]; // high pT bin edge
      double down = egdelow-0.25*3; // low fit range
      double up = egdehigh+0.25*3; // high fit range
      // fit cross-section, one has to play for a while with a function with fits all ranged of the cross section well. 
      // Try changing ranges and different function, e.g., expo, pol
      // Be sure the function fits well within the ranges: (egdelow-all*dpt, egdelow+all*dpt)
      if (b == 1 && topol == 1){
        fcs[topol][b-1] = new TF1(Form("fcs_%d_%d",topol, b),"pol5",down,up);
        //fcs[topol][b-1]->SetParameter(1, 7.62);
        //fcs[topol][b-1]->SetParameter(2, 0.333);
        //fcs[topol][b-1] = new TF1(Form("fcs_%d_%d",topol, b),"gaus(0) + pol4(3)",down,up);
        //fcs[topol][b-1]->SetParameter(1, 15.95);
        //fcs[topol][b-1]->SetParameter(2, 0.33);
      }

      else fcs[topol][b-1] = new TF1(Form("fcs_%d_%d",topol, b),"pol4",down,up);

      gCS[topol]->Fit(Form("fcs_%d_%d",topol, b),"r");
      fcs[topol][b-1]->SetLineColor(b);
      double integp = fcs[topol][b-1]->Integral(egdelow+all*dpt,egdehigh+all*dpt); // integrate cross section within the bin + ALL*<dpT>
      double integm = fcs[topol][b-1]->Integral(egdelow-all*dpt,egdehigh-all*dpt); // integrate cross section within the bin - ALL*<dpT>
      cout<<"all: "<<all<<" dMinv: "<<dpt<<" egdelow: "<<egdelow-all*dpt<<" egdehigh: "<<egdehigh+all*dpt<<" integp: "<<integp<<" integm: "<<integm<<endl;
      double UEasym = (integm-integp)/(integp+integm);
      hUEAsym[topol]->SetBinContent(b+1,UEasym);
      hUEAsym[topol]->SetBinError(b+1, 0.0000000001); //artificially set to draw bars in histogram instead of points
    }
  
 
  
  cout<< "UE Contribution to A_LL Systematic Uncertainties for Topology " << Topology[topol]<<endl;
  for(int b=1; b<8; b++) {
    cout<< hUEAsym[topol]->GetBinContent(b+1)<<endl; 
    //cout<< "Bin " << binEdges[b] << "-" << binEdges[b+1] << ": " << hUEAsym[topol]->GetBinContent(b+1)<<endl; 
  }
  
hUEAsym[topol]->SetDirectory(gROOT);
hDijetMassUE[0][topol]->SetDirectory(gROOT);  
pDijetMassUE[0][topol]->SetDirectory(gROOT);
hDijetMassUEEmbe->SetDirectory(gROOT);
pDijetMassUEEmbe->SetDirectory(gROOT);
hUEALL->SetDirectory(gROOT);

  cout << " -------- " << Topology[topol] << "------------" << endl;
  cout << "Difference Data - Embedding: " << endl; 
  for(Int_t iii = 2; iii<=8; iii++) cout << pDijetMassUE[0][topol]->GetBinContent(iii) -  pDijetMassUEEmbe->GetBinContent(iii) << endl;




TCanvas *cTest = new TCanvas("cTest", "Test Canvas", 1800, 1200 );
cTest->Divide(3,2);

cTest->cd(1);
gPad->SetLogz();
hDijetMassUE[0][topol]->SetTitle("");
hDijetMassUE[0][topol]->GetXaxis()->SetRangeUser(17,xaxismax);
hDijetMassUE[0][topol]->GetYaxis()->SetRangeUser(0,10);
hDijetMassUE[0][topol]->GetXaxis()->SetTitle("Dijet M_{inv} [GeV]");
hDijetMassUE[0][topol]->GetYaxis()->SetTitle("dM_{inv} UE");
hDijetMassUE[0][topol]->SetTitle(Form("Data Underlying Event <dM_{inv}> - %s Topology", Topology[topol]));
hDijetMassUE[0][topol]->Draw("colz");
pDijetMassUE[0][topol]->SetLineColor(4);
pDijetMassUE[0][topol]->Draw("same");

cTest->cd(2);
gPad->SetLogz();
hDijetMassUEEmbe->SetTitle("");
hDijetMassUEEmbe->GetXaxis()->SetRangeUser(17,xaxismax);
hDijetMassUEEmbe->GetYaxis()->SetRangeUser(0,10);
hDijetMassUEEmbe->GetXaxis()->SetTitle("Dijet M_{inv} [GeV]");
hDijetMassUEEmbe->GetYaxis()->SetTitle("dM_{inv} UE");
hDijetMassUEEmbe->SetTitle(Form("Embedding Underlying Event <dM_{inv}> - %s Topology", Topology[topol]));
hDijetMassUEEmbe->Draw("colz");
pDijetMassUEEmbe->SetLineColor(2);
pDijetMassUEEmbe->Draw("same");

cTest->cd(3);
pDijetMassUE[0][topol]->SetLineColor(4);
pDijetMassUE[0][topol]->GetXaxis()->SetRangeUser(17,82);  
pDijetMassUE[0][topol]->GetYaxis()->SetRangeUser(1,2);  
pDijetMassUE[0][topol]->SetTitle(Form("Dijets <dM_{inv}> profile vs M_{inv} - %s Topology", Topology[topol]));
pDijetMassUE[0][topol]->Draw("E");
pDijetMassUEEmbe->SetLineColor(2);  
pDijetMassUEEmbe->Draw("same E");


cTest->cd(4);
hUEALL->GetXaxis()->SetRangeUser(17,xaxismax);
hUEALL->GetYaxis()->SetRangeUser(-1*yaxisscale,yaxisscale);
hUEALL->SetTitle(Form("Underlying Event A_{LL} - %s Topology", Topology[topol]));
hUEALL->GetXaxis()->SetTitle("Dijet M_{inv} [GeV]");
hUEALL->GetYaxis()->SetTitle("A_{LL}^{<dM_{inv}>}");
hUEALL->GetYaxis()->SetTitleOffset(1.4);
hUEALL->Draw();
pol0Draw->SetLineColor(kRed);
pol0Draw->Draw("same");

cTest->cd(5);
gPad->SetLogy();
gStyle->SetOptFit(0);

gCS[topol]->GetXaxis()->SetTitle("M_{inv} [GeV]");
gCS[topol]->GetYaxis()->SetTitle("d#sigma/dM_{inv}");
gCS[topol]->SetTitle(Form("d#sigma/dM_{inv} - %s Topology",Topology[topol])); 
gCS[topol]->SetMarkerStyle(8);
gCS[topol]->SetMarkerSize(0.5);
gCS[topol]->Draw("AP");
for(int b=1; b<9; b++) {
  fcs[topol][b-1]->Draw("same");
}
gCS[topol]->GetXaxis()->SetRangeUser(17,xaxismax);
gCS[topol]->GetYaxis()->SetRangeUser(1,1000000000);
//gCS[topol]->GetYaxis()->SetRangeUser(100000,10000000);

cTest->cd(6);
hUEAsym[topol]->SetTitle("");
hUEAsym[topol]->GetXaxis()->SetRangeUser(17,xaxismax);
//hUEAsym[topol]->GetYaxis()->SetRangeUser(-0.001,0.001);
hUEAsym[topol]->GetXaxis()->SetTitle("Dijet M_{inv} [GeV]");
hUEAsym[topol]->GetYaxis()->SetTitle("#deltaA_{LL}");
hUEAsym[topol]->SetTitle(Form("#deltaA_{LL} - %s Topology", Topology[topol]) );
//hUEAsym[topol]->SetMarkerStyle(8);
hUEAsym[topol]->GetYaxis()->SetTitleOffset(1.4);
hUEAsym[topol]->Draw("Hist");

//hUEAsym[topol]->Fit("pol0");

cout << "UE A_LL Mean: " << dMALLMean << endl;
//cTest->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/UEMassScale.png");


  TDatime now1;
  now1.Print();
}
  

