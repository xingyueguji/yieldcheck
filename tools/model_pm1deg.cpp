#include"plotModelNew.cpp"

void model_pm1deg(int bin=10){
  gStyle->SetTitleX(.1);
  gStyle->SetTitleW(.8);

  double min=5.1*(1+0.01*bin);
  bin++;
  double max=5.1*(1+0.01*bin);

  TString tit=Form("    %lf < #delta < %lf", min,max);
  auto g=plotModelNew("r","v0.995",21.0);
  g->SetName("g");
  auto gp=plotModelNew("r","v0.995",22.0);
  gp->SetName("gp");
  auto gm=plotModelNew("r","v0.995",20.0);
  gm->SetName("gm");

  g->SetMarkerStyle(33);
  gp->SetMarkerStyle(33);
  gm->SetMarkerStyle(33);

  g->SetMarkerColor(kBlack);
  gp->SetMarkerColor(kRed);
  gm->SetMarkerColor(kBlue);

  g->SetMarkerSize(1);
  gp->SetMarkerSize(1);
  gm->SetMarkerSize(1);

  g->GetYaxis()->SetRangeUser(0.5,1.1);

  g->GetYaxis()->SetTitle("#sigma_{Rad}");
  g->GetXaxis()->SetTitle("x_{B}");
  g->GetXaxis()->SetTitle("E' (GeV)");
  g->SetTitle("#sigma_{Rad} (ff1f221 v0.995)"+tit);
  g->Draw("ap");
  gPad->Update();
  //  g->GetXaxis()->SetRangeUser(5.508,5.559);
  //  g->GetXaxis()->SetRangeUser(5.559,5.61);
  g->GetXaxis()->SetRangeUser(min,max);

  g->Draw("ap");
  gp->Draw("sp");
  gm->Draw("sp");

  TLegend *t=new TLegend(.8,.7,1.,.85);

  t->AddEntry(gm,"model @ 20#circ","lp");
  t->AddEntry(g,"model @ 21#circ","lp");
  t->AddEntry(gp,"model @ 22#circ","lp");
  t->Draw("same");
  gPad->SaveAs(Form("bin%d.pdf",bin));
  return;
}
