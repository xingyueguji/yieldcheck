 {
TStyle* cStyle = new TStyle("mcStyle","Manuel's Root Styles");
// gROOT->SetStyle("Plain");
// cStyle->SetTitleX(0.2);
// cStyle->SetTitleW(.6);
 cStyle->SetOptStat(1111);
//mcStyle->SetPalette(1,0); // avoid horrible default color schem
//mcStyle->SetOptStat(0);
//mcStyle->SetOptTitle(0);
 cStyle->SetOptDate(0);
 // cStyle->SetOptTitle(0);
 cStyle->SetLabelSize(0.04,"xyz");// size of axis value font
 cStyle->SetTitleSize(0.04,"xyz");// size of axis title font
 cStyle->SetTitleFont(22,"xyz");// font option
 cStyle->SetLabelFont(22,"xyz");
 cStyle->SetTitleOffset(.8,"y");// from .8
//mcStyle->SetTitleAlign(23);
// default canvas options
 cStyle->SetCanvasDefW(800);
cStyle->SetCanvasDefH(500);
//mcStyle->SetCanvasColor(0);
// canvas... mcStyle->SetCanvasBorderMode(0);
//mcStyle->SetCanvasBorderSize(0);

//margins... mcStyle->SetPadTopMargin(0.1);

// mcStyle->SetPadBottomMargin(0.1);
// mcStyle->SetPadLeftMargin(0.1);
// mcStyle->SetPadRightMargin(0.1);
 cStyle->SetPadGridX(1);
 // grids, tickmarks
 cStyle->SetPadGridY(1);
 cStyle->SetPadTickX(1);
 cStyle->SetPadTickY(1);
 //mcStyle->SetFrameBorderMode(0);
 cStyle->SetPaperSize(20,24); // US letter size
 gROOT->SetStyle("mcStyle");
 cout << "Styles are Set!" << endl;
 return; }
