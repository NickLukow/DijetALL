double CalcAsymm(double mass, double a3, double a2, double a1, double a0)
{
        double asymm = a3*TMath::Power(mass,3) + a2*TMath::Power(mass,2) + a1*mass + a0;

        return asymm;
}

void PlotsPartonAsymmNNPDF()
{

	static const int nbins = 9;
        //const double binEdges[nbins+2] = {12.0,14.0,17.0,20.0,24.0,29.0,34.0,41.0,49.0,59.0,70.0,84.0,101.0,121.0};
        const double binEdges[10] = {13.0, 17.0, 19.0, 23.0, 28.0, 34.0, 41.0, 58.0, 82.0, 120.0};
	static const int Nsides = 3;
        const char *side[Nsides] = {"", "EEWW", "EW"};
	static const int numNNPDF = 101;
	
		double Mass[nbins] = { 15.90, 18.45, 21.23, 25.53, 30.85, 37.16, 46.42, 64.48, 89.05};
        double Mass_EEWW[nbins] = { 15.81, 18.44, 21.18, 25.49, 30.82, 37.12, 46.27, 64.20, 88.88};
        double Mass_EW[nbins] = { 16.01, 18.46, 21.27, 25.56, 30.88, 37.19, 46.53, 64.62, 89.10};

	// Declare histograms to save info from histogram file
	TProfile *hCorrMassAsymmDetBin_Filter[numNNPDF][Nsides];
	TProfile *hCorrMassAsymmDetBin_Filter_4pct[numNNPDF][Nsides];
        TProfile *hAsymm2GeVBin_NoFilter[numNNPDF][Nsides];

	// Declare Histograms to add runs together	
	TProfile *CorrMassAsymmDetBin_Filter[numNNPDF][Nsides];
	TProfile *CorrMassAsymmDetBin_Filter_4pct[numNNPDF][Nsides];
        TProfile *Asymm2GeVBin_NoFilter[numNNPDF][Nsides];
	
	//TEST
	TGraph *DiffPlot[Nsides];
        for (int iTop = 0 ; iTop < Nsides; iTop++)
        {
                DiffPlot[iTop] = new TGraph();
                DiffPlot[iTop]->SetName(Form("DiffPlot_%s", side[iTop]));
        }
        int counter[Nsides] = {0,0,0};
	//TEST

	for(int i = 0; i < numNNPDF; i++)
        {
                for(int j = 0; j < Nsides; j++)
                {
                        CorrMassAsymmDetBin_Filter[i][j] = new TProfile(Form("hCorrMassAsymmDetBinFilter%s_%d",side[j],i), Form("hCorrMassAsymmDetBinFilter%s_%d",side[j],i), nbins,binEdges);
                        CorrMassAsymmDetBin_Filter_4pct[i][j] = new TProfile(Form("hCorrMassAsymmDetBinFilter_4pct%s_%d",side[j],i), Form("hCorrMassAsymmDetBinFilter_4pct%s_%d",side[j],i), nbins,binEdges);
                }
        }

	//TFile *file_filter = new TFile("/home/nick/Documents/AnalysisFolder/Working_A_LL/Histograms/Dijet/PartonAsym/PartonAsymm_Filter_NoUECut.root");
	//TFile *file_filter_4pct = new TFile("/home/nick/Documents/AnalysisFolder/Working_A_LL/Histograms/Dijet/PartonAsym/PartonAsymm_Filter4pct_NoUECut.root");
	TFile *file_filter = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PartonAsym/PartonAsymm_Filter.root");
	TFile *file_filter_4pct = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PartonAsym/PartonAsymm_Filter4pct.root");
	TFile *file_nofilter = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PartonAsym/PartonAsymm_NoFilter.root");
	//TFile *file_nofilter = new TFile("/home/nick/Documents/AnalysisFolder/Working_A_LL/Histograms/Dijet/PartonAsym/PartonAsymm_NoFilter_NoCut.root");
	//TFile *file_nofilter = new TFile("/home/nick/Documents/AnalysisFolder/Working_A_LL/Histograms/Dijet/PartonAsym/BAD_DO_NOT_USE_PartonAsymm_NoFilter.root");

	TProfile *hasymm_Filter[Nsides];
	TProfile *hasymm_Filter_4pct[Nsides];
	TProfile *hasymm_NoFilter[Nsides];
	TProfile *hasymm_diff[Nsides];

	for(int i = 0; i < Nsides; i++)
	{
		hasymm_Filter[i] = new TProfile(Form("hasymm_Filter_%s",side[i]), Form("hasymm_Filter_%s",side[i]), nbins,0,nbins);
		hasymm_Filter_4pct[i] = new TProfile(Form("hasymm_Filter_4pct_%s",side[i]), Form("hasymm_Filter_4pct_%s",side[i]), nbins,0,nbins);
		hasymm_NoFilter[i] = new TProfile(Form("hasymm_NoFilter_%s",side[i]), Form("hasymm_NoFilter_%s",side[i]), nbins,0,nbins);
		hasymm_diff[i] = new TProfile(Form("hasymm_diff_%s",side[i]), Form("hasymm_diff_%s",side[i]), nbins,0,nbins);
	}



	for(int i = 0; i < numNNPDF; i++)
	{
		for(int j = 0; j < Nsides; j++)
		{
			hCorrMassAsymmDetBin_Filter[i][j] = (TProfile*)file_filter->Get(Form("hCorrMassAsymmDetBin%s_%d",side[j],i));
			hCorrMassAsymmDetBin_Filter_4pct[i][j] = (TProfile*)file_filter_4pct->Get(Form("hCorrMassAsymmDetBin%s_%d",side[j],i));
		
			CorrMassAsymmDetBin_Filter[i][j]->Add(hCorrMassAsymmDetBin_Filter[i][j]);
			CorrMassAsymmDetBin_Filter_4pct[i][j]->Add(hCorrMassAsymmDetBin_Filter_4pct[i][j]);
			
			hAsymm2GeVBin_NoFilter[i][j] = (TProfile*)file_nofilter->Get(Form("hAsymm2GeVBin%s_%d",side[j],i));
			if (!hAsymm2GeVBin_NoFilter[i][j]) cout << "Missing Topology (" << side[j] << ") and Replicate " << i << endl;
		}
	}
		
	
	TF1 *f3 = new TF1("f3","pol3",13,82);

	double a3[numNNPDF][Nsides];
	double a2[numNNPDF][Nsides];
	double a1[numNNPDF][Nsides];
	double a0[numNNPDF][Nsides];

	double asymm_NoFilter[numNNPDF][Nsides][nbins];
	double asymm_Filter[numNNPDF][Nsides][nbins];
	double asymm_diff[numNNPDF][Nsides][nbins];

	for(int i = 1; i < numNNPDF; i++)
	{
		for(int j = 0; j < Nsides; j++)
		{
			hAsymm2GeVBin_NoFilter[i][j]->Fit(f3,"RQ");	

			a3[i][j] = f3->GetParameter(3);
			a2[i][j] = f3->GetParameter(2);
			a1[i][j] = f3->GetParameter(1);
			a0[i][j] = f3->GetParameter(0);

			//printf("i: %d, j: %d, a3: %e\n",i,j,a3[i][j]);
			for(int k = 1; k < nbins-1; k++)
			{
				if(j == 0) asymm_NoFilter[i][j][k] = CalcAsymm(Mass[k]      ,a3[i][j],a2[i][j],a1[i][j],a0[i][j]);
				if(j == 1) asymm_NoFilter[i][j][k] = CalcAsymm(Mass_EEWW[k] ,a3[i][j],a2[i][j],a1[i][j],a0[i][j]);
				if(j == 2) asymm_NoFilter[i][j][k] = CalcAsymm(Mass_EW[k]   ,a3[i][j],a2[i][j],a1[i][j],a0[i][j]);
				hasymm_NoFilter[j]->Fill(k,CalcAsymm(Mass[k],a3[i][j],a2[i][j],a1[i][j],a0[i][j]));
				asymm_Filter[i][j][k] = CorrMassAsymmDetBin_Filter[i][j]->GetBinContent(k+1);
				hasymm_Filter[j]->Fill(k,CorrMassAsymmDetBin_Filter[i][j]->GetBinContent(k+1));
				hasymm_Filter_4pct[j]->Fill(k,CorrMassAsymmDetBin_Filter_4pct[i][j]->GetBinContent(k+1));
				hasymm_diff[j]->Fill(k,asymm_Filter[i][j][k]-asymm_NoFilter[i][j][k]);
				
				//TEST
				double binwidth = binEdges[k+1] - binEdges[k];
                                double frac = i;
                                frac = frac/100;
                                double xplot = binEdges[k] + binwidth*frac;
                                DiffPlot[j]->SetPoint(counter[j], xplot, asymm_Filter[i][j][k]-asymm_NoFilter[i][j][k]);
                                counter[j]++;
				//TEST			


			} // end nbins
		} //end Nsides
	} // end numNNPDF

//Getting Corection Values
TH1D *CorrectionPlot[Nsides];
for(int i = 0; i < Nsides; i++)
{
        CorrectionPlot[i] = new TH1D(Form("hCorr_%s",side[i]), Form("Correction - %s", side[i]), nbins, binEdges);
        for(int j = 1; j < nbins-1; j++)
        {
                CorrectionPlot[i]->SetBinContent(j+1,hasymm_diff[i]->GetBinContent(j+1));
                CorrectionPlot[i]->SetBinError(j+1,hasymm_diff[i]->GetBinError(j+1));
        }
}


	for(int i = 0; i < Nsides; i++)
	{
		for(int j = 1; j < nbins-1; j++)
		{
			if(i == 0) printf("NNPDF Best Fit bin#: %d  Asymm: %f, AsymmErr: %f\n",j,CorrMassAsymmDetBin_Filter[0][i]->GetBinContent(j+1),CorrMassAsymmDetBin_Filter[0][i]->GetBinError(j+1));
			if(i == 1) printf("EEWW NNPDF Best Fit bin#: %d  Asymm: %f, AsymmErr: %f\n",j,CorrMassAsymmDetBin_Filter[0][i]->GetBinContent(j+1),CorrMassAsymmDetBin_Filter[0][i]->GetBinError(j+1));
			if(i == 2) printf("EW NNPDF Best Fit bin#: %d  Asymm: %f, AsymmErr: %f\n",j,CorrMassAsymmDetBin_Filter[0][i]->GetBinContent(j+1),CorrMassAsymmDetBin_Filter[0][i]->GetBinError(j+1));
		}
	}

	for(int i = 0; i < Nsides; i++)
	{
		for(int j = 1; j < nbins-1; j++)
		{
			if(i == 0) printf("bin#: %d  asymmCorr: %f, CorrRMS: %f\n",j,hasymm_diff[0]->GetBinContent(j+1),hasymm_diff[0]->GetBinError(j+1));
			if(i == 1) printf("EEWW bin#: %d  asymmCorr: %f, CorrRMS: %f\n",j,hasymm_diff[1]->GetBinContent(j+1),hasymm_diff[1]->GetBinError(j+1));
			if(i == 2) printf("EW bin#: %d  asymmCorr: %f, CorrRMS: %f\n",j,hasymm_diff[2]->GetBinContent(j+1),hasymm_diff[2]->GetBinError(j+1));
		}
	}

	for(int i = 0; i < Nsides; i++)
	{
		for(int j = 1; j < nbins-1; j++)
		{
			if(i == 0) printf("bin#: %d  NominalAsymm: %f, 4pctAsymm: %f\n",j,hasymm_Filter[0]->GetBinContent(j+1),hasymm_Filter_4pct[0]->GetBinContent(j+1));
			if(i == 1) printf("EEWW bin#: %d  NominalAsymm: %f, 4pctAsymm: %f\n",j,hasymm_Filter[1]->GetBinContent(j+1),hasymm_Filter_4pct[1]->GetBinContent(j+1));
			if(i == 2) printf("EW bin#: %d  NominalAsymm: %f, 4pctAsymm: %f\n",j,hasymm_Filter[2]->GetBinContent(j+1),hasymm_Filter_4pct[2]->GetBinContent(j+1));
		}
	}

	for(int i = 0; i < Nsides; i++)
	{
		cout << "---- Best Fit RMS - " << side[i] << "-----" << endl;
		for(int j = 1; j < nbins-1; j++)
		{
			cout << CorrMassAsymmDetBin_Filter[0][i]->GetBinError(j+1) << endl;
		}
	}

	for(int i = 0; i < Nsides; i++)
	{
		cout << "----- Asymmetry Correction - " << side[i] << " -----" << endl;
		for(int j = 1; j < nbins-1; j++)
		{
			cout << hasymm_diff[i]->GetBinContent(j+1) << endl;
		}
	}
	
	for(int i = 0; i < Nsides; i++)
	{
		cout << "----- Asymmetry Correction RMS - " << side[i] << " -----" << endl;
		for(int j = 1; j < nbins-1; j++)
		{
			cout << hasymm_diff[i]->GetBinError(j+1) << endl;
		}
	}
	
	for(int i = 0; i < Nsides; i++)
	{
		cout << "----- 4pct Track Loss - " << side[i] << " -----" << endl;
		for(int j = 1; j < nbins-1; j++)
		{
			cout << hasymm_Filter[i]->GetBinContent(j+1) - hasymm_Filter_4pct[i]->GetBinContent(j+1) << endl;
		}
	}

	gStyle->SetOptDate(0);
	gStyle->SetOptStat(0);
/*
	TCanvas *canvas1 = new TCanvas();
	hasymm_diff[0]->SetTitle();
	hasymm_diff[0]->GetXaxis()->SetTitle("Mass Bin #");
	hasymm_diff[0]->GetYaxis()->SetTitle("Detector-Parton A_{LL} Average");
	hasymm_diff[0]->GetYaxis()->CenterTitle();
	hasymm_diff[0]->GetYaxis()->SetTitleOffset(1.40);
	hasymm_diff[0]->Draw("e");
	canvas1->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/DetectorPartonAvg.png");

	TCanvas *canvas2 = new TCanvas();
	hasymm_diff[1]->SetTitle();
	hasymm_diff[1]->GetXaxis()->SetTitle("Mass Bin #");
	hasymm_diff[1]->GetYaxis()->SetTitle("Detector-Parton EEWW A_{LL} Average");
	hasymm_diff[1]->GetYaxis()->CenterTitle();
	hasymm_diff[1]->GetYaxis()->SetTitleOffset(1.40);
	hasymm_diff[1]->Draw("e");
	canvas2->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/DetectorPartonAvg_EEWW.png");

	TCanvas *canvas3 = new TCanvas();
	hasymm_diff[2]->SetTitle();
	hasymm_diff[2]->GetXaxis()->SetTitle("Mass Bin #");
	hasymm_diff[2]->GetYaxis()->SetTitle("Detector-Parton A_{LL} Average");
	hasymm_diff[2]->GetYaxis()->CenterTitle();
	hasymm_diff[2]->GetYaxis()->SetTitleOffset(1.40);
	hasymm_diff[2]->Draw("e");
	canvas3->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/DetectorPartonAvg_EW.png");

	TCanvas *canvas4 = new TCanvas();
	CorrMassAsymmDetBin_Filter[0][0]->SetTitle();
	CorrMassAsymmDetBin_Filter[0][0]->GetXaxis()->SetTitle("Invariant Mass");
	CorrMassAsymmDetBin_Filter[0][0]->GetYaxis()->SetTitle("NNPDF Best Fit A_{LL}");
	CorrMassAsymmDetBin_Filter[0][0]->GetYaxis()->CenterTitle();
	CorrMassAsymmDetBin_Filter[0][0]->GetYaxis()->SetTitleOffset(1.35);
	CorrMassAsymmDetBin_Filter[0][0]->Draw("e");
	canvas4->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/NNPDF_BestFit.png");

	TCanvas *canvas5 = new TCanvas();
	CorrMassAsymmDetBin_Filter[0][1]->SetTitle();
	CorrMassAsymmDetBin_Filter[0][1]->GetXaxis()->SetTitle("Invariant Mass");
	CorrMassAsymmDetBin_Filter[0][1]->GetYaxis()->SetTitle("NNPDF Best Fit EEWW A_{LL}");
	CorrMassAsymmDetBin_Filter[0][1]->GetYaxis()->CenterTitle();
	CorrMassAsymmDetBin_Filter[0][1]->GetYaxis()->SetTitleOffset(1.35);
	CorrMassAsymmDetBin_Filter[0][1]->Draw("e");
	canvas5->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/NNPDF_BestFit_EEWW.png");

	TCanvas *canvas6 = new TCanvas();
	CorrMassAsymmDetBin_Filter[0][2]->SetTitle();
	CorrMassAsymmDetBin_Filter[0][2]->GetXaxis()->SetTitle("Invariant Mass");
	CorrMassAsymmDetBin_Filter[0][2]->GetYaxis()->SetTitle("NNPDF Best Fit EW A_{LL}");
	CorrMassAsymmDetBin_Filter[0][2]->GetYaxis()->CenterTitle();
	CorrMassAsymmDetBin_Filter[0][2]->GetYaxis()->SetTitleOffset(1.35);
	CorrMassAsymmDetBin_Filter[0][2]->Draw("e");
	canvas6->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/NNPDF_BestFit_EW.png");
*/
	TCanvas *canvasDiff1 = new TCanvas();
        canvasDiff1->cd();
        DiffPlot[0]->SetTitle("Detector - Parton Full Sample - 100 Replicates per bin");
        DiffPlot[0]->GetXaxis()->SetTitle("Invariant Mass");
        DiffPlot[0]->GetYaxis()->SetTitle("Detector-Parton A_{LL} Average");
        DiffPlot[0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
        DiffPlot[0]->SetMarkerSize(0.2);
        DiffPlot[0]->SetMarkerStyle(3);
        DiffPlot[0]->Draw("AP");
        CorrectionPlot[0]->SetMarkerColor(2);
        CorrectionPlot[0]->SetLineColor(2);
        CorrectionPlot[0]->SetLineWidth(2);
        CorrectionPlot[0]->Draw("same");
	//canvasDiff1->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/NEWCorrection_Full.pdf");

        TCanvas *canvasDiff2 = new TCanvas();
        canvasDiff2->cd();
        DiffPlot[1]->SetTitle("Detector - Parton EEWW Sample - 100 Replicates per bin");
        DiffPlot[1]->GetXaxis()->SetTitle("Invariant Mass");
        DiffPlot[1]->GetYaxis()->SetTitle("Detector-Parton EEWW A_{LL} Average");
	DiffPlot[1]->GetYaxis()->SetRangeUser(-0.05, 0.05);
        DiffPlot[1]->SetMarkerSize(0.2);
        DiffPlot[1]->SetMarkerStyle(3);
        DiffPlot[1]->Draw("AP");
        CorrectionPlot[1]->SetMarkerColor(2);
        CorrectionPlot[1]->SetLineColor(2);
        CorrectionPlot[1]->SetLineWidth(2);
        CorrectionPlot[1]->Draw("same");
	//canvasDiff2->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/NEWCorrection_EEWW.pdf");

        TCanvas *canvasDiff3 = new TCanvas();
        canvasDiff3->cd();
        DiffPlot[2]->SetTitle("Detector - Parton EW Sample - 100 Replicates per bin");
        DiffPlot[2]->GetXaxis()->SetTitle("Invariant Mass");
        DiffPlot[2]->GetYaxis()->SetTitle("Detector-Parton EW A_{LL} Average");
	DiffPlot[2]->GetYaxis()->SetRangeUser(-0.05, 0.05);
        DiffPlot[2]->SetMarkerSize(0.2);
        DiffPlot[2]->SetMarkerStyle(3);
        DiffPlot[2]->Draw("AP");
        CorrectionPlot[2]->SetMarkerColor(2);
        CorrectionPlot[2]->SetLineColor(2);
        CorrectionPlot[2]->SetLineWidth(2);
        CorrectionPlot[2]->Draw("same");
	//canvasDiff3->SaveAs("/home/nick/Documents/AnalysisFolder/Figures/DiJetTriggerBias/NEWCorrection_EW.pdf");

} // end void
