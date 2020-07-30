void FilterBinAvg()
{
	static const int nbins = 9;
        const double binEdges[10] = {13.0, 17.0, 19.0, 23.0, 28.0, 34.0, 41.0, 58.0, 82.0, 120.0};
	static const int Nsides = 3;
        const char *side[Nsides] = {"", "EEWW", "EW"};
	static const int numNNPDF = 101;
	
	// Declare histograms to save info from histogram file
	TProfile *hCorrMassAsymmDetBin_Filter[numNNPDF][Nsides];
	TProfile *hCorrMassAsymmDetBin_Filter_4pct[numNNPDF][Nsides];

	// Declare Histograms to add runs together	
	TProfile *CorrMassAsymmDetBin_Filter[Nsides];
	TProfile *CorrMassAsymmDetBin_Filter_4pct[Nsides];
	
	TH1F *InvariantMass[Nsides];

                for(int j = 0; j < Nsides; j++)
                {
                        CorrMassAsymmDetBin_Filter[j] = new TProfile(Form("hCorrMassAsymmDetBinFilter%s",side[j]), Form("hCorrMassAsymmDetBinFilter%s",side[j]), 125, 0, 125);
                        CorrMassAsymmDetBin_Filter_4pct[j] = new TProfile(Form("hCorrMassAsymmDetBinFilter_4pct%s",side[j]), Form("hCorrMassAsymmDetBinFilter_4pct%s",side[j]), 125, 0, 125);
               			InvariantMass[j] = new TH1F(Form("hInvMas_%s", side[j]) , Form("Invariant Mass - %s", side[j]), 120, 0, 120);
		 }

	TFile *file_filter = new TFile("/Users/Nick/Run15/DijetAsymmetryAnalysis/Histograms/PartonAsym/PartonAsymm_Filter.root");
	//TFile *file_filter_4pct = new TFile("/home/Nick/Analysis/Working_A_LL/Histograms/Dijet/PartonAsym/PartonAsymm_Filter4pct.root");

	for(int i = 0; i < numNNPDF; i++)
	{
		for(int j = 0; j < Nsides; j++)
		{
			hCorrMassAsymmDetBin_Filter[i][j] = (TProfile*)file_filter->Get(Form("hCorrMassAsymm1GeVBin%s_%d",side[j],i));
			//hCorrMassAsymmDetBin_Filter_4pct[i][j] = (TProfile*)file_filter_4pct->Get(Form("hCorrMassAsymm1GeVBin%s_%d",side[j],i));
		
			CorrMassAsymmDetBin_Filter[j]->Add(hCorrMassAsymmDetBin_Filter[i][j]);
			//CorrMassAsymmDetBin_Filter_4pct[j]->Add(hCorrMassAsymmDetBin_Filter_4pct[i][j]);
		}
	}
	

	for (int j = 0; j < Nsides; j++)
	{
		cout << "Invariant Mass " << side[j] << " : {" ;
		for (int i = 0; i < 121; i ++)
		{
		//Bin 0 corresponds to 0-1 GeV so bin to GeV conversion is n -> n-0.5 GeV
			InvariantMass[j]->Fill( i-0.5,  CorrMassAsymmDetBin_Filter[j]->GetBinEntries(i));	
		}
	      for(Int_t iii = 0; iii<nbins; iii++){
              	//New way - more precise
              	Int_t BinL = InvariantMass[j]->GetXaxis()->FindBin(binEdges[iii]);
              	Int_t BinH = InvariantMass[j]->GetXaxis()->FindBin(binEdges[iii+1]);
              	InvariantMass[j]->GetXaxis()->SetRange(BinL,BinH); 
               
              	cout <<  Form("% .2f",InvariantMass[j]->GetMean());
              	if(iii==nbins-1) cout << "};"<< endl; 
              	else cout << ",";
              	InvariantMass[j]->GetXaxis()->SetRange();
              }
	}



} // end void
