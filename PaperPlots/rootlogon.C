{
    gROOT->SetStyle("Plain");

    // use plain black on white colors
    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetStatColor(0);
    // margins
    gStyle->SetPaperSize(20,26);
    gStyle->SetPadBottomMargin(0.0);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadTopMargin(0.0);
    gStyle->SetPadRightMargin(0.05);

    // fonts
    gStyle->SetTextSize(0.06);
    gStyle->SetLabelSize(25,"x");
    gStyle->SetTitleSize(25,"x");
    gStyle->SetLabelSize(25,"y");
    gStyle->SetTitleSize(25,"y");
    gStyle->SetLabelSize(25,"z");
    gStyle->SetTitleSize(25,"z");
    gStyle->SetLabelFont(43,"x");
    gStyle->SetLabelFont(43,"y");
    gStyle->SetTitleFont(43,"x");
    gStyle->SetTitleFont(43,"y");

    // use bold lines and markers
    gStyle->SetMarkerStyle(21);
    gStyle->SetMarkerSize(0.7);
    gStyle->SetHistLineWidth(1.8);
    gStyle->SetHistLineColor(kBlack);
    gStyle->SetFuncColor(kRed);
    gStyle->SetLineStyleString(2,"[12 12]");

    // do not display any of the standard histogram decorations
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit(0);

    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(11111);
    gStyle->SetOptFit(111111);
    gStyle->SetOptFile(2);
    gROOT->ForceStyle();

  }
