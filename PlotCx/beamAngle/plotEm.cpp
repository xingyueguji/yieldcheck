#include "makeGr2.cpp"

void plotEm(){
  gStyle->SetTitleX(.1);
  gStyle->SetTitleW(.8);
  TCanvas *c1=new TCanvas();
c1->Divide
  TGraphErrors *g0_shms=makeGr("xsec_0.txt",21.035);
  TGraphErrors *gp45_shms=makeGr("xsec_m45mr_extractm45.txt",21.00922);
  double x, y0, yp;
  int n=g0_shms->GetN();
  vector <double> xx_shms, yy_shms;
  for(int i=0;i<n;i++)
    {
      g0_shms->GetPoint(i,x,y0);
      gp45_shms->GetPoint(i,x,yp);
      double rat=yp/y0;
      xx_shms.push_back(x);
      yy_shms.push_back(rat);
    }
  TGraph *g1=new TGraph(n,&xx_shms[0],&yy_shms[0]);
  g1->SetMarkerStyle(33);
  g1->SetTitle("xsec (beamAngle=-0.45mr) / xsec (beamAngle=0.mr)");
  g1->GetYaxis()->SetRangeUser(.8,1.2);
  g1->Draw("ap");


  TGraphErrors *g0_hms=makeGr("xsec_0.txt",20.995);
  TGraphErrors *gp45_hms=makeGr("xsec_m45mr_extractm45.txt",21.02078);
  
  n=g0_hms->GetN();
  vector <double> xx_hms, yy_hms;
  for(int i=0;i<n;i++)
    {
      g0_hms->GetPoint(i,x,y0);
      gp45_hms->GetPoint(i,x,yp);
      double rat=yp/y0;
      xx_hms.push_back(x);
      yy_hms.push_back(rat);
    }
  TGraph *g2=new TGraph(n,&xx_hms[0],&yy_hms[0]);
  g2->SetMarkerStyle(33);
  g2->SetMarkerColor(kRed);
  g2->Draw("sp");

  TLegend *l=new TLegend(.2,.6,.6,.85);
  l->AddEntry(g1,"SHMS","p");
  l->AddEntry(g2,"HMS","p");
  l->Draw();
  return;
}
