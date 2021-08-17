#include "getGraph.cpp"

void ex1(double angle=21, string target="h"){
  //TGraph* getGraph(string title="nameMe", double angle=21,  string target="h", Int_t choice=1){
  /*
      if(choice==1)yy=born;
      if(choice==2)yy=bornInc;
      if(choice==3)yy=bornQe;
      if(choice==4)yy=rad;
      if(choice==5)yy=radEl;
      if(choice==6)yy=radQe;
      if(choice==7)yy=radDis;
  */
  TGraph* gBorn=getGraph("born", angle, target, 1);
  TGraph* gBornInc=getGraph("bornInc", angle, target, 2);
  TGraph* gBornQe=getGraph("bornQe", angle, target, 3);
  TGraph* gRad=getGraph("rad", angle, target, 4);
  TGraph* gRadEl=getGraph("radEl", angle, target, 5);
  TGraph* gRadQe=getGraph("radQe", angle, target, 6);
  TGraph* gRadDis=getGraph("radDis", angle, target, 7);
  TGraph* gRadElp2=getGraph("radElp2", angle, target, 8);
  TGraph* gRadElm2=getGraph("radElm2", angle, target, 9);
  TGraph* gRadp2=getGraph("radp2", angle, target, 10);
  TGraph* gRadm2=getGraph("radm2", angle, target, 11);
  TGraph* gRad0=getGraph("rad0", angle, target, 12);

  gBorn->SetLineColor(kBlack);
  gBornInc->SetLineColor(kGreen+3);
  gBornQe->SetLineColor(kRed);
  gRad->SetLineColor(kBlack);
  gRadEl->SetLineColor(kGreen+3);
  gRadQe->SetLineColor(kRed);
  gRadDis->SetLineColor(kMagenta);
  gRadElp2->SetLineColor(kGreen+3);
  gRadElm2->SetLineColor(kGreen+3);
  gRadp2->SetLineColor(kRed);
  gRadm2->SetLineColor(kBlack);
  gRad0->SetLineColor(kBlue);

  gRadElp2->SetLineStyle(9);
  gRadElm2->SetLineStyle(9);
  gRadp2->SetLineStyle(9);
  gRadm2->SetLineStyle(9);
  gRad0->SetLineStyle(9);
  
  TLegend *leg1=new TLegend(.4,.6,.6,.85);
  leg1->AddEntry(gBorn, "Born","l");
  leg1->AddEntry(gBornInc, "BornInc","l");
  leg1->AddEntry(gBornQe, "BornQE","l");
  TLegend *leg2=new TLegend(.4,.6,.6,.85);
  leg2->AddEntry(gRad, "Rad","l");
  leg2->AddEntry(gRadEl, "RadEl","l");
  leg2->AddEntry(gRadQe, "RadQE","l");
  leg2->AddEntry(gRadDis, "RadDIS","l");
  TLegend *leg3=new TLegend(.4,.6,.6,.85);
  leg3->AddEntry(gRadp2, "Rad (with RadEl/RadQE scaled up 2%)","l");
  leg3->AddEntry(gRadm2, "Rad (with RadEl/RadQE scaled down 2%)","l");


  TCanvas *c1=new TCanvas();
  c1->Divide(1,2);
  c1->cd(1);
  gPad->Divide(2,1);
  c1->cd(1);gPad->cd(1);
  gBorn->Draw("al");
  gBornInc->Draw("sl");
  gBornQe->Draw("sl");
  leg1->Draw("same");
  c1->cd(1);gPad->cd(2);
  leg2->Draw("same");
  gRad->Draw("al");
  gRadEl->Draw("sl");
  gRadQe->Draw("sl");
  gRadDis->Draw("sl");
  gRadElp2->Draw("sl");
  gRadElm2->Draw("sl");
  leg2->Draw("same");

  c1->cd(2);
  gRadp2->GetYaxis()->SetRangeUser(.98,1.02);
  gRadp2->SetTitle("Ratio  (Rad with Scaling)/(Rad)");
  gRadp2->Draw("al");
  gRadm2->Draw("sl");
  gRad0->Draw("sl");
  leg3->Draw("same");

  TPaveText *tb=new TPaveText(.35,.13,.65,.25,"NDC");
  tb->AddText(Form("Target: %s  Angle:%2.0f",target.c_str(),angle));
  tb->Draw();
  c1->SaveAs(Form("%s%2.0f.pdf",target.c_str(),angle));
  return;
}
