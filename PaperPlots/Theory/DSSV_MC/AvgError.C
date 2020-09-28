#define POINTS 66

void AvgError() { 

  //gStyle->SetOptLogy(1);

//-----
//-----
  Double_t Xvals[3][POINTS];
  Double_t Yvals[3][3][POINTS];

  ifstream EEWWin; 
  ifstream EWin; 

  ofstream EEWWout("./EEWW.Avg.txt");
  ofstream EWout("./EW.Avg.txt");

  EEWWin.open("./EEWW.txt");
  EWin.open("./EW.txt");

  for(int i=0; i<POINTS; i++) { 
    EEWWin>>Xvals[0][i]>>Yvals[0][0][i]>>Yvals[0][1][i]>>Yvals[0][2][i];
    EWin>>Xvals[1][i]>>Yvals[1][0][i]>>Yvals[1][1][i]>>Yvals[1][2][i];
  
    for(int iTop =0; iTop < 3; iTop++)
    {
      //Xvals[iTop][i] = Xvals[iTop][i]/200;
      Yvals[iTop][1][i] = Yvals[iTop][1][i]/2 + Yvals[iTop][2][i]/2;
    }

    EEWWout << Xvals[0][i] << " " << Yvals[0][0][i] << " " << Yvals[0][1][i]  << endl;
    EWout << Xvals[1][i] << " " << Yvals[1][0][i] << " " << Yvals[1][1][i] << endl;


  }

  


}

