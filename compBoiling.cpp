
#include "plot_cxAr.cpp"
//#include "plot_cx_raffaella.cpp"

void compBoiling(double angle=20){
  //  gROOT->ForceStyle();
  //  gStyle->SetGridStyle(3);
  //  gStyle->SetTitleX(.5);
  //  gStyle->SetTitleW(.7);

  TCanvas *c1=new TCanvas();
  c1->Divide(4,1);
  c1->SetGrid();
  //void plot_cx(string target="d", string angle="39", string spec="shms",float "xb"min=0.0, float "xb"max=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){
  if(angle==21)
    {

      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"shms\",\"pass306\",.2,1.,-.1,8.,.9,1.1,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"shms\",\"pass308\",.2,1.,-.1,8.,.9,1.1,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"shms\",\"pass306\",.2,1.,0.6,1.1,.9,1.1,\"xb\")");
      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"shms\",\"pass308\",.2,1.,0.6,1.1,.9,1.1,\"xb\")");
    }
  if(angle==20)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"hms\",\"pass306\",.2,1.,-.1,8.,.9,1.1,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"hms\",\"pass308\",.2,1.,-.1,8.,.9,1.1,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"hms\",\"pass306\",.2,1.,0.6,1.1,.9,1.1,\"xb\")");
      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"hms\",\"pass308\",.2,1.,0.6,1.1,.9,1.1,\"xb\")");
    }

  if(angle==25)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"d\",\"25\",\"shms\",\"pass306\",.2,1.,-.1,4.,.85,1.15,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"25\",\"shms\",\"pass308\",.2,1.,-.1,4.,.85,1.15,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"25\",\"shms\",\"pass306\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"25\",\"shms\",\"pass308\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
    }

  if(angle==29)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"d\",\"29\",\"shms\",\"pass306\",.2,1.,-.1,2.4,.85,1.15,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"29\",\"shms\",\"pass308\",.2,1.,-.1,2.4,.85,1.15,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"29\",\"shms\",\"pass306\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"29\",\"shms\",\"pass308\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
    }

  if(angle==33)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"d\",\"33\",\"shms\",\"pass306\",.2,1.,-.1,1.6,.85,1.15,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"33\",\"shms\",\"pass308\",.2,1.,-.1,1.6,.85,1.15,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"33\",\"shms\",\"pass306\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"33\",\"shms\",\"pass308\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
    }

  if(angle==39)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"d\",\"39\",\"shms\",\"pass306\",.2,1.,-.1,1.,.85,1.15,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"39\",\"shms\",\"pass308\",.2,1.,-.1,1.,.85,1.15,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"39\",\"shms\",\"pass306\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"39\",\"shms\",\"pass308\",.2,1.,0.6,1.1,.85,1.15,\"xb\")");
    }

  TPaveText *t1=new TPaveText(.1,.1,.3,.3,"NSC");
  c1->SaveAs(Form("compBoiling_%2.0fdeg_306.pdf",angle));
  return;
}
