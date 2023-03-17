{
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  TFile *_file0 = TFile::Open("drawMe.root");
  heff->Draw("LEGO2");
  gPad->SetPhi(120);
  gStyle->SetPalette(kRainBow);
  heff->GetXaxis()->SetRangeUser(-35,35);
  heff->GetXaxis()->CenterTitle(1);
  heff->GetYaxis()->CenterTitle(1);
  heff->GetZaxis()->CenterTitle(1);
  heff->GetZaxis()->SetTitle("Effective Solid Angle (msr)");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  heff->GetXaxis()->SetTitleSize(.048);
  heff->GetYaxis()->SetTitleSize(.048);
  heff->GetZaxis()->SetTitleSize(.048);


  heff->GetXaxis()->SetTitleOffset(1.7);
  heff->GetYaxis()->SetTitleOffset(1.5);
  heff->GetZaxis()->SetTitleOffset(1.04);

  gPad->SetRightMargin(.04);
  gPad->SetTopMargin(.1);
  gPad->SetLeftMargin(.1);

  heff->Scale(1000.);
  heff->Draw("LEGO2");
 
}
