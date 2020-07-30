

void xConv() { 

  //gStyle->SetOptLogy(1);

//-----
//-----
  Double_t Xvals[3][136];
  Double_t Yvals[3][136];

  ifstream EEWWin; 
  ifstream EWin; 
  ifstream FULLin; 

  ofstream EEWWout("./EEWW_x.DSSV.txt");
  ofstream EWout("./EW_x.DSSV.txt");
  ofstream FULLout("./FULL_x.DSSV.txt");

  EEWWin.open("./EEWW.DSSV.txt");
  EWin.open("./EW.DSSV.txt");
  FULLin.open("./FULL.DSSV.txt");
  

  for(int i=0; i<36; i++) { 
    EEWWin>>Xvals[0][i]>>Yvals[0][i];
    EWin>>Xvals[1][i]>>Yvals[1][i];
    FULLin>>Xvals[2][i]>>Yvals[2][i];
  
    for(int iTop =0; iTop < 3; iTop++)
    {
      Xvals[iTop][i] = Xvals[iTop][i]/200;
    }

    EEWWout << Xvals[0][i] << " " << Yvals[0][i] << endl;
    EWout << Xvals[1][i] << " " << Yvals[1][i] << endl;
    FULLout << Xvals[2][i] << " " << Yvals[2][i] << endl;


  }

  


}

