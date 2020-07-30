#define POINTS 65

void xConv() { 

  //gStyle->SetOptLogy(1);

//-----
//-----
  Double_t Xvals[3][POINTS];
  Double_t Yvals[3][3][POINTS];

  ifstream EEWWin; 
  ifstream EWin; 
  ifstream FULLin; 

  ofstream EEWWout("./EEWW_x.NNPDF.txt");
  ofstream EWout("./EW_x.NNPDF.txt");
  ofstream FULLout("./FULL_x.NNPDF.txt");

  EEWWin.open("./EEWW.NNPDF.txt");
  EWin.open("./EW.NNPDF.txt");
  FULLin.open("./FULL.NNPDF.txt");
  

  for(int i=0; i<POINTS; i++) { 
    EEWWin>>Xvals[0][i]>>Yvals[0][0][i]>>Yvals[0][1][i]>>Yvals[0][2][i];
    EWin>>Xvals[1][i]>>Yvals[1][0][i]>>Yvals[1][1][i]>>Yvals[1][2][i];
    FULLin>>Xvals[2][i]>>Yvals[2][0][i]>>Yvals[2][1][i]>>Yvals[2][2][i];
  
    for(int iTop =0; iTop < 3; iTop++)
    {
      Xvals[iTop][i] = Xvals[iTop][i]/200;
    }

    EEWWout << Xvals[0][i] << " " << Yvals[0][0][i] << Yvals[0][1][i] << Yvals[0][2][i] << endl;
    EWout << Xvals[1][i] << " " << Yvals[1][0][i] << Yvals[1][1][i] << Yvals[1][2][i] << endl;
    FULLout << Xvals[2][i] << " " << Yvals[2][0][i] << Yvals[2][1][i] << Yvals[2][2][i] << endl;


  }

  


}

