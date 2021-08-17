#include "getGraph.cpp"

TGraph* plotrat(double angle=21, string target="h"){
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

  TGraph* gRadp2h=getGraph("radp2h", angle, "h", 10);
  TGraph* gRadm2h=getGraph("radm2h", angle, "h", 11);
  gRadp2h->SetLineColor(kRed);
  gRadm2h->SetLineColor(kBlack);
  gRadp2h->SetLineStyle(9);
  gRadm2h->SetLineStyle(9);

  TGraph* gRadp2d=getGraph("radp2d", angle, "d", 10);
  TGraph* gRadm2d=getGraph("radm2d", angle, "d", 11);
  gRadp2d->SetLineColor(kGreen+3);
  gRadm2d->SetLineColor(kBlue);
  gRadp2d->SetLineStyle(9);
  gRadm2d->SetLineStyle(9);

    TLegend *leg3=new TLegend(.2,.6,.8,.85);
  leg3->AddEntry(gRadp2h, "Rad (with RadEl/RadQE scaled up 2%)","l");
  leg3->AddEntry(gRadm2h, "Rad (with RadEl/RadQE scaled down 2%)","l");
  leg3->AddEntry(gRadp2d, "Rad (with RadEl/RadQE scaled up 2%)","l");
  leg3->AddEntry(gRadm2d, "Rad (with RadEl/RadQE scaled down 2%)","l");


  TCanvas *c1=new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  gRadp2h->GetYaxis()->SetRangeUser(.98,1.02);
  gRadp2h->GetXaxis()->SetRangeUser(.2,0.95);
  gRadp2h->SetTitle("Ratio  (Rad with Scaling)/(Rad)");
  gRadp2h->Draw("al");
  gRadm2h->Draw("sl");
  gRadp2d->Draw("sl");
  gRadm2d->Draw("sl");
  leg3->Draw("same");

  TPaveText *tb=new TPaveText(.35,.13,.65,.25,"NDC");
  tb->AddText(Form("Angle:%2.0f",angle));
  tb->Draw();


  double x1,y1,x2,y2;
  vector <double> sx;
  vector <double> sy;
  int npts=gRadp2h->GetN();
  for(int i=0; i<npts; i++){

    gRadp2h->GetPoint(i,x1,y1);
    gRadp2d->GetPoint(i,x2,y2);
    double val1=abs(1.0 - y1);
    double val2=abs(1.0 - y2);
    double total=sqrt(val1*val1+val2*val2+0.01*0.01);
    cout << y1 <<"\t"<<  y2 <<"\t"<< total << endl;
    sx.push_back(x1);
    sy.push_back(total*100);
  } 
  c1->cd(2);
  TGraph *g=new TGraph(npts, &sx[0], &sy[0]);
  g->GetYaxis()->SetRangeUser(0,2);
  g->GetXaxis()->SetRangeUser(.2,0.95);
  g->SetTitle("Uncertainty in D/H ratio");
  g->GetYaxis()->SetTitle("%");
  g->GetXaxis()->SetTitle("X");
  g->Draw();
  g->Fit("pol6");
  c1->SaveAs(Form("rat%2.0f.pdf",angle));
  return g;
}
