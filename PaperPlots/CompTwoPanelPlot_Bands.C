/**
 * Plotting of ALL for |eta| < 0.5 and 0.5 < |eta| < 1.0
 *
 * This script plots the ALL plot with all the uncertainties for 2 eta regions.
 * @author Maria Zurek
 */

//Edited to plot Dijet results
//Noting all changes so that it can be updated to "Final" version
//I changed the names of the arrays and the plots
//I changed the x axis limits
// Adding brief section on the math to get to the proper text placements

//To change axes, change these values only
double XMIN = 0.05; //0.05
double XMAX = 0.35;
double YMIN = -0.04;  //with 9 -0.04   without -0.021
double YMAX = 0.105;  // with 9 0.125   without 0.105

//These are fractions calculated from Maria's original code
double XFRAC = 0.071428;
double YFRAC1 = 0.111111;
double YFRAC2 = 0.188888;
double YFRAC3 = 0.266666;
double YFRAC4 = 0.344444;
double YFRAC5 = 0.916666;

double XPOS = XFRAC*(XMAX-XMIN) + XMIN;
double YPOS1 = YMAX - YFRAC1*(YMAX-YMIN);
double YPOS2 = YMAX - YFRAC2*(YMAX-YMIN);
double YPOS3 = YMAX - YFRAC3*(YMAX-YMIN);
double YPOS4 = YMAX - YFRAC4*(YMAX-YMIN);
double YPOS5 = YMAX - YFRAC5*(YMAX-YMIN);

Int_t PLOT9 = 1;
Int_t PLOTGLOBAL = 1;
Int_t DSSVERR = 1;


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
#include "TBox.h"

#include "./DijetData.h"

TPad* upPad(string name, int isLog=0) {

  TPad *pad = new TPad(name.c_str(),name.c_str(), 0.0,0.53,1.0,1.0);
  if(isLog==1) pad->SetLogy();
  pad->SetBottomMargin(0);
  pad->SetTopMargin(0.059);
  pad->Draw();

  return pad;
}

TPad* dPad(string name, int isLog=0) {

  TPad *pad = new TPad(name.c_str(),name.c_str(), 0,0.0,1.0,0.53);
  if(isLog==1) pad->SetLogy();
  pad->SetTopMargin(0);
  pad->SetBottomMargin(0.158);
  pad->Draw();

  return pad;
}

void CompTwoPanelPlot_Bands(){
  gROOT->Reset();
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetTitleOffset(2,"y");
  gStyle->SetTitleOffset(2.5,"x");
  
double LEGLOWY = 0.68 - 3*0.06*PLOT9 - 2*0.06*PLOTGLOBAL; //Using PLOT9 adds three entries to legend. Using PLOTGLOBAL adds 2
if (PLOT9 == 1 && PLOTGLOBAL==1) LEGLOWY = 0.5;

/*
  double EEWWrun9x[7] = {17.70,21.34,26.02,31.66,38.25,48.28,66.65};
	double EEWWrun9xerror[7] = {0,0,0,0,0,0,0};
	double EEWWrun9y[7] = {0.0067,0.0088,0.0162,0.0024,0.0130,0.0336,0.0755};
	double EEWWrun9yerror[7] = {0.0034,0.0032,0.0039,0.0056,0.0089,0.0133,0.0460};
	double EEWWrun9sysx[7] = {0.56,1.07,1.33,1.39,1.79,2.17,2.56};
	double EEWWrun9sysy[7] = {0.0004,0.0005,0.0006,0.0010,0.0015,0.0024,0.0041};

	double EWrun9x[7] = {17.99,21.58,26.29,31.72,38.38,48.79,67.32};
  double EWrun9xerror[7] = {0,0,0,0,0,0,0};
  double EWrun9y[7] = {0.0059,0.0096,0.0068,0.0151,0.0083,0.0092,-0.0282};
  double EWrun9yerror[7] = {0.0039,0.0032,0.0037,0.0050,0.0077,0.0109,0.0340};
  double EWrun9sysx[7] = {0.56,0.96,1.32,1.72,1.70,2.07,3.35};
  double EWrun9sysy[7] = {0.0005,0.0006,0.0007,0.0009,0.0013,0.0022,0.0036};




	double EWrun15x[7] = {18.28, 22.01, 26.90, 32.77, 39.78, 49.69, 68.23};
  double EWrun15y[7] = {6.1378E-03, 1.7369E-03, 4.3123E-03, 9.8534E-03, 1.8615E-02, 2.2233E-02, 9.1493E-02};
  double EWrun15yerror[7] = {4.03E-03, 2.74E-03, 3.17E-03, 4.43E-03, 6.84E-03, 9.70E-03, 3.04E-02};
  double EWrun15sysx[7] = {0.60, 0.61, 0.69, 0.80, 0.92, 1.08, 1.28};
  double EWrun15sysy[7] = {4.25E-04, 3.86E-04, 4.62E-04, 5.85E-04, 9.21E-04, 8.52E-04, 1.68E-03};
    
	double EEWWrun15x[7] = {18.18, 21.97, 26.78, 32.68, 39.52, 49.34, 67.63};
	double EEWWrun15y[7] ={6.47E-03, 4.00E-03, 5.38E-04, 1.21E-02, 2.96E-02, 2.06E-02, 1.95E-02};
	double EEWWrun15yerror[7] = {3.57E-03, 2.77E-03, 3.46E-03, 5.06E-03, 8.11E-03, 1.21E-02, 4.18E-02};
	double EEWWrun15sysx[7] = {0.54, 0.61, 0.67, 0.78, 0.89, 1.02, 1.30};
	double EEWWrun15sysy[7] = {8.41E-04, 6.85E-04, 7.25E-04, 7.83E-04, 9.92E-04, 1.10E-03, 2.17E-03};
	*/
  for (int i = 0; i < 7; i++)
  {
    EEWWrun15x[i] = EEWWrun15x[i]/200;
    EEWWrun15sysx[i] = EEWWrun15sysx[i]/200;
    EWrun15x[i] = EWrun15x[i]/200;
    EWrun15sysx[i] = EWrun15sysx[i]/200;
    EEWWrun9x[i] = EEWWrun9x[i]/200;
    EEWWrun9sysx[i] = EEWWrun9sysx[i]/200;
    EWrun9x[i] = EWrun9x[i]/200;
    EWrun9sysx[i] = EWrun9sysx[i]/200;
  }


//---------------> Theory


  TGraphAsymmErrors *ALLdssvEEWW = new TGraphAsymmErrors("./Theory/DSSV_MC/EEWW_x.DSSV.txt", "%lg %lg %lg %lg");
  ALLdssvEEWW->SetLineColor(kRed);
  ALLdssvEEWW->SetLineStyle(7);
  ALLdssvEEWW->SetFillColor(kMagenta-4);
  ALLdssvEEWW->SetFillStyle(3354);
  ALLdssvEEWW->SetLineWidth(3);

  TGraphAsymmErrors *ALLdssvEW = new TGraphAsymmErrors("./Theory/DSSV_MC/EW_x.DSSV.txt", "%lg %lg %lg %lg");
  ALLdssvEW->SetLineColor(kRed);
  ALLdssvEW->SetLineStyle(7);
  ALLdssvEW->SetFillColor(kMagenta-4);
  ALLdssvEW->SetFillStyle(3354);
  ALLdssvEW->SetLineWidth(3);

  TGraphAsymmErrors *ALLnnpdfEEWW = new TGraphAsymmErrors("Theory/NNPDF/Coarse_Trunc/EEWW_x_Asym.NNPDF.txt", "%lg %lg %lg %lg");
  ALLnnpdfEEWW->SetLineColor(kMagenta+1);
  ALLnnpdfEEWW->SetFillColor(kCyan+1);
  ALLnnpdfEEWW->SetFillStyle(3345);
  ALLnnpdfEEWW->SetLineWidth(3);

  TGraphAsymmErrors *ALLnnpdfEW = new TGraphAsymmErrors("Theory/NNPDF/Coarse_Trunc/EW_x_Asym.NNPDF.txt", "%lg %lg %lg %lg");
  ALLnnpdfEW->SetLineColor(kMagenta+1);
  ALLnnpdfEW->SetFillColor(kCyan+1);
  ALLnnpdfEW->SetFillStyle(3345);
  ALLnnpdfEW->SetLineWidth(3);


//Plus and Minus Lines
TGraph *dssv_EEWW_p = new TGraph("./Theory/DSSV_MC/EEWW_x_P.DSSV.txt", "%lg %lg");
dssv_EEWW_p->SetLineColor(kMagenta-4);
dssv_EEWW_p->SetLineWidth(1);
TGraph *dssv_EEWW_m = new TGraph("./Theory/DSSV_MC/EEWW_x_M.DSSV.txt", "%lg %lg");
dssv_EEWW_m->SetLineColor(kMagenta-4);
dssv_EEWW_m->SetLineWidth(1);

TGraph *dssv_EW_p = new TGraph("./Theory/DSSV_MC/EW_x_P.DSSV.txt", "%lg %lg");
dssv_EW_p->SetLineColor(kMagenta-4);
dssv_EW_p->SetLineWidth(1);
TGraph *dssv_EW_m = new TGraph("./Theory/DSSV_MC/EW_x_M.DSSV.txt", "%lg %lg");
dssv_EW_m->SetLineColor(kMagenta-4);
dssv_EW_m->SetLineWidth(1);

TGraph *nnpdf_EEWW_p = new TGraph("./Theory/NNPDF/Coarse_Trunc/EEWW_x_P.NNPDF.txt", "%lg %lg");
nnpdf_EEWW_p->SetLineColor(kCyan+1);
nnpdf_EEWW_p->SetLineWidth(1);
TGraph *nnpdf_EEWW_m = new TGraph("./Theory/NNPDF/Coarse_Trunc/EEWW_x_M.NNPDF.txt", "%lg %lg");
nnpdf_EEWW_m->SetLineColor(kCyan+1);
nnpdf_EEWW_m->SetLineWidth(1);

TGraph *nnpdf_EW_p = new TGraph("./Theory/NNPDF/Coarse_Trunc/EW_x_P.NNPDF.txt", "%lg %lg");
nnpdf_EW_p->SetLineColor(kCyan+1);
nnpdf_EW_p->SetLineWidth(1);
TGraph *nnpdf_EW_m = new TGraph("./Theory/NNPDF/Coarse_Trunc/EW_x_M.NNPDF.txt", "%lg %lg");
nnpdf_EW_m->SetLineColor(kCyan+1);
nnpdf_EW_m->SetLineWidth(1);





//<--------------- Theory



        

        




/*
  // Luminosity 2015
  TBox *bxLumi15 = new TBox(18,-0.0007,XMAX,0.0007); //change to M_inv limits
  bxLumi15->SetFillColor(kYellow-6);
  //TBox *bxLumi15 = new TBox(0.21,-0.0007,0.245,0.0007);
  //bxLumi15->SetFillColor(kYellow-6);

  // Luminosity 2009
  TBox *bxLumi09 = new TBox(0.245,0.000,0.28,0.0005);  //change to M_inv limits
  bxLumi09->SetFillColor(kRed-8);
  */

 // Luminosity 2015
  double Lumi15_lowx = 18.0/200.0;
  double Lumi15_highx = XMAX;

 if (PLOT9)
 {
   Lumi15_lowx= 53.0/200.0;
   Lumi15_highx= 58.0/200.0;

 }
  //TBox *bxLumi15 = new TBox(53,-0.0007,58,0.0007);
  TBox *bxLumi15 = new TBox(Lumi15_lowx,-0.0007,Lumi15_highx,0.0007);
  bxLumi15->SetFillColor(kYellow-6);

  // Luminosity 2009
  TBox *bxLumi09 = new TBox(58.0/200,-0.0005,63.0/200,0.0005);
  bxLumi09->SetFillColor(kRed-8);

  TCanvas *cALL = new TCanvas("cALL"," ALL",800,800*1.26);  //800,800*1.26

  //TLegend *leglumi9 = new TLegend(0.632,0.268,0.833,0.349);
  double lumiypos = 0.39;
  TLegend *leglumi9 = new TLegend(0.67,lumiypos,0.871,lumiypos+0.081);
  leglumi9->SetTextSize(19);
  leglumi9->SetTextFont(43);
  leglumi9->AddEntry("","Lumi. Syst.","");
  leglumi9->AddEntry("","2015     2009","");
  leglumi9->SetBorderSize(0);  leglumi9->SetFillStyle(0);



  TLatex text0;
  text0.SetTextAlign(12);
  text0.SetTextFont(43);
  text0.SetTextSize(25);

  TLatex text1;
  text1.SetTextAlign(12);
  text1.SetTextFont(43);
  text1.SetTextSize(25);

  TLegend *legeta1 = new TLegend(0.15,0.81,0.35,0.99);
  legeta1->SetTextSize(25);
  legeta1->SetTextFont(43);
  legeta1->AddEntry("","0.5 < |#eta| < 1.0","");
  legeta1->SetBorderSize(0);  legeta1->SetFillStyle(0);

  TLegend *legeta2 = new TLegend(0.15,0.43,0.35,0.61);
  legeta2->SetTextSize(25);
  legeta2->SetTextFont(43);
  legeta2->AddEntry("","|#eta| < 0.5","");
  legeta2->SetBorderSize(0);  legeta2->SetFillStyle(0);
  TLegend *leg2 = new TLegend(0.170,LEGLOWY,0.27,0.86);
  leg2->SetTextSize(25);  leg2->SetBorderSize(0);  leg2->SetFillStyle(0);
  leg2->SetTextFont(43);

  TLatex textP;
  textP.SetTextAlign(12);
  textP.SetTextFont(43);
  textP.SetTextSize(19); //25  20
  
  TLegend *legP = new TLegend(0.12,0.04,0.40,0.1);
  legP->SetTextSize(24);
  //legP->AddEntry("","#pm 6.1% (2015) and 6.5% (2009) scale uncertainty from polarization not shown","");
  legP->SetBorderSize(0); legP->SetFillStyle(0);
  legP->SetTextFont(43);
  
  TLine *line = new TLine(XMIN,0,XMAX,0); //Changed
  line->SetLineColor(1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  /*
  TLegend *leglumi9 = new TLegend(0.573498,0.22961,0.773948,0.365092);
  leglumi9->SetTextSize(25);
  leglumi9->SetTextFont(43);
  leglumi9->AddEntry("","Lumi. Syst.","");
  leglumi9->SetBorderSize(0);  leglumi9->SetFillStyle(0);
  */

  cALL->cd();
  upPad("uRt",0)->cd();
   
  TGraphErrors *gALL09_EW    = new TGraphErrors(7,EWrun9x,EWrun9y,0,EWrun9yerror);
  gALL09_EW->SetMarkerColor(4);
  gALL09_EW->SetLineColor(4);
  gALL09_EW->SetMarkerStyle(24);   gALL09_EW->SetMarkerSize(1.2);  
  gALL09_EW->SetLineWidth(3);

  TGraphErrors *gSystALL09_EW = new TGraphErrors(7, EWrun9x, EWrun9y, EWrun9sysx, EWrun9sysy);
  gSystALL09_EW->SetMarkerColor(1);
  gSystALL09_EW->SetFillColorAlpha(18,0.80);

  TGraphErrors *gSystALL15_EW = new TGraphErrors(7, EWrun15x, EWrun15y, EWrun15sysx, EWrun15sysy);
  gSystALL15_EW->SetMarkerColor(1);
  gSystALL15_EW->SetFillColorAlpha(29,0.80);

  TGraphErrors *gALL15_EW = new TGraphErrors(7,EWrun15x,EWrun15y,0,EWrun15yerror);
  gALL15_EW->SetTitle("A_LL ADC+3 UE ; x_{T} = 2p_{T}/#sqrt{s};A_{LL}");
  gALL15_EW->GetYaxis()->SetDecimals(2);
  gALL15_EW->GetXaxis()->SetDecimals(2);
  gALL15_EW->GetYaxis()->SetNdivisions(6,5,0);
  gALL15_EW->SetMarkerColor(kGreen+3);
  gALL15_EW->SetLineColor(kGreen+3);
  gALL15_EW->SetMarkerStyle(21);   gALL15_EW->SetMarkerSize(1.2);
  gALL15_EW->GetXaxis()->SetLimits(XMIN,XMAX); //Changed
  gALL15_EW->GetHistogram()->SetMinimum(YMIN);  //Changed
  gALL15_EW->GetHistogram()->SetMaximum(YMAX);  //0.105 //Changed
  gALL15_EW->SetLineWidth(3);
   
  gALL15_EW->Draw("AP"); 

  
  if(PLOTGLOBAL) ALLdssvEW->Draw("cXsame");
  if(PLOTGLOBAL && DSSVERR) ALLdssvEW->Draw("3same");
  if(PLOTGLOBAL) ALLnnpdfEW->Draw("3same");
  if(PLOTGLOBAL) ALLnnpdfEW->Draw("cXsame");
  
  dssv_EW_m->Draw("csame");
  dssv_EW_p->Draw("csame");
  nnpdf_EW_p->Draw("csame");
  nnpdf_EW_m->Draw("csame");


  //bxLumi15->Draw();
  line->Draw();


 
  if(PLOT9) gSystALL09_EW->Draw("2same");
  if(PLOT9) gALL09_EW->Draw("Psame");
  gSystALL15_EW->Draw("2same");
  gALL15_EW->Draw("P"); 

  if(PLOT9) leg2->AddEntry(gALL09_EW, "2009 Data, PRL 115 (2015) 92002", "p");
  if(PLOT9) leg2->AddEntry(gSystALL09_EW, "2009 Syst.", "f");
  //if(PLOT9) leg2->AddEntry(bxLumi09, "2009 Lumi. Syst.", "f");    
  leg2->AddEntry(gALL15_EW, "STAR 2015", "p");
  leg2->AddEntry(gSystALL15_EW, "2015 Syst.", "f");    
  //leg2->AddEntry(bxLumi15, "Lumi. Syst.", "f");    
	if(PLOTGLOBAL && DSSVERR) leg2->AddEntry(ALLdssvEW, "DSSV'14", "lf");
  else leg2->AddEntry(ALLdssvEW, "DSSV'14", "l");
  if(PLOTGLOBAL) leg2->AddEntry(ALLnnpdfEW, "NNPDFpol1.1", "lf");

  text0.DrawLatex(XPOS,YPOS1,"#font[72]{#color[4]{STAR}} #font[62]{2015, #sqrt{s} = 200 GeV}");
  text0.DrawLatex(XPOS,YPOS2,"p+p #rightarrow Jet + Jet + X");
  text0.DrawLatex(XPOS,YPOS3,"Anti-k_{T} R=0.6");
  text0.DrawLatex(XPOS,YPOS4,"sign(#eta_{1}) #neq sign(#eta_{2})"); //Changed

  //textP.DrawLatex(XPOS,YPOS5,"#pm 6.1% (2015) and 6.5% (2009) scale uncertainty from polarization not shown");

  cALL->cd();
  dPad("dRt",0)->cd();

  TGraphErrors *gALL09_EEWW    = new TGraphErrors(7,EEWWrun9x,EEWWrun9y,0,EEWWrun9yerror);
  gALL09_EEWW->SetMarkerColor(4);
  gALL09_EEWW->SetLineColor(4);
  gALL09_EEWW->SetMarkerStyle(24);   gALL09_EEWW->SetMarkerSize(1.2);  
  gALL09_EEWW->SetLineWidth(3);

  TGraphErrors *gSystALL09_EEWW = new TGraphErrors(7, EEWWrun9x, EEWWrun9y, EEWWrun9sysx, EEWWrun9sysy);
  gSystALL09_EEWW->SetMarkerColor(1);
  gSystALL09_EEWW->SetFillColorAlpha(18,0.80);

  TGraphErrors *gSystALL15_EEWW = new TGraphErrors(7, EEWWrun15x, EEWWrun15y, EEWWrun15sysx, EEWWrun15sysy);
  gSystALL15_EEWW->SetMarkerColor(1);
  gSystALL15_EEWW->SetFillColorAlpha(29,0.80);

  TGraphErrors *gALL15_EEWW = new TGraphErrors(7,EEWWrun15x,EEWWrun15y,0,EEWWrun15yerror);
  gALL15_EEWW->SetTitle("A_LL; M_{inv}/#sqrt{s} ;A_{LL}");
  gALL15_EEWW->GetYaxis()->SetDecimals(2);
  gALL15_EEWW->GetXaxis()->SetDecimals(2);
  gALL15_EEWW->GetYaxis()->SetNdivisions(6,5,0);
  gALL15_EEWW->GetXaxis()->SetTitleSize(25);
  gALL15_EEWW->SetMarkerColor(kGreen+3);
  gALL15_EEWW->SetLineColor(kGreen+3);
  gALL15_EEWW->SetMarkerStyle(21);   gALL15_EEWW->SetMarkerSize(1.2);
  gALL15_EEWW->GetXaxis()->SetLimits(XMIN,XMAX);  //Changed
  gALL15_EEWW->GetHistogram()->SetMinimum(YMIN); //Changed
  gALL15_EEWW->GetHistogram()->SetMaximum(YMAX);  //Changed
  gALL15_EEWW->SetLineWidth(3);
  gALL15_EEWW->Draw("AP"); 

  if(PLOTGLOBAL) ALLdssvEEWW->Draw("cXsame");
  if(PLOTGLOBAL && DSSVERR) ALLdssvEEWW->Draw("3same");
  if(PLOTGLOBAL) ALLnnpdfEEWW->Draw("3same");
  if(PLOTGLOBAL) ALLnnpdfEEWW->Draw("cXsame");
  
  dssv_EEWW_m->Draw("csame");
  dssv_EEWW_p->Draw("csame");
  nnpdf_EEWW_p->Draw("csame");
  nnpdf_EEWW_m->Draw("csame");

  if(PLOT9)bxLumi09->Draw();
  bxLumi15->Draw();
  if(PLOT9)leglumi9->Draw();
  line->Draw();
 
  if(PLOT9) gSystALL09_EEWW->Draw("2same");
  if(PLOT9) gALL09_EEWW->Draw("Psame");
  gSystALL15_EEWW->Draw("2same");
  gALL15_EEWW->Draw("P"); 
  text0.DrawLatex(XPOS,YPOS1,"sign(#eta_{1}) = sign(#eta_{2})"); //Changed 
  leg2->Draw();

  textP.DrawLatex(XPOS - XPOS*0.15,YPOS5,"#pm 6.1% (2015) and 6.5% (2009) scale uncertainty from polarization not shown");


  //cALL->Draw();

  cALL->Print("./Figures/Run15DijetALL_TwoPanel.pdf");
  //cALL->Print("./Figures/Run15DijetALL_TwoPanel_Print.pdf");
  //cALL->SaveAs("./Figures/Run15DijetALL_TwoPanel_SaveAs.pdf");
  
}
  

