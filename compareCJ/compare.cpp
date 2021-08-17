#include "getCJ.cpp"
#include "getF1f2.cpp"

void compare(){

  TGraph *gcj=getCJ("21");
  TGraph *gm=getF1f2();

  gm->SetLineColor(kBlue);
  gcj->SetLineColor(kRed);

  gm->GetYaxis()->SetRangeUser(0.55,1.1);
  gm->GetXaxis()->SetRangeUser(0.2,1);
  gm->GetXaxis()->SetTitle("Bjorken x");
  gm->GetYaxis()->SetTitle("F2d / F2p");

  gm->Draw("al");
  gcj->Draw("sl");

  TLegend *l=new TLegend(.4,.7,.6,.9);
  l->AddEntry(gm,"f1f220 f2d/f2p","l");
  l->AddEntry(gcj,"CJ15   f2d/f2p","l");
  return;
}
