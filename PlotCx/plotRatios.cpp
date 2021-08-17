
#include "plot_cx.cpp"
//#include "plot_cx_raffaella.cpp"

void plotRatios(double angle=21){
  //  gROOT->ForceStyle();
  //  gStyle->SetGridStyle(3);
  //  gStyle->SetTitleX(.5);
  //  gStyle->SetTitleW(.7);

  TCanvas *c1=new TCanvas();
  //void plot_cx(string target="d", string angle="39", string spec="shms",float "xb"min=0.0, float "xb"max=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){

  if(angle==20)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"hms\",\"pass130\",.2,1.,0.4,1.15,.9,1.1,\"xb\",1)");
    }

  if(angle==21)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"shms\",\"pass130\",.2,1.,0.4,1.15,.9,1.1,\"xb\",1)");
    }

  if(angle==25)
    {
  
      gROOT->ProcessLine("plot_cx(\"r\",\"25\",\"shms\",\"pass130\",.2,1.,0.4,1.15,.85,1.15,\"xb\",1)");
    }

  if(angle==29)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"29\",\"shms\",\"pass130\",.2,1.,0.4,1.15,.85,1.15,\"xb\",1)");
    }

  if(angle==33)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"33\",\"shms\",\"pass130\",.2,1.,0.4,1.15,.85,1.15,\"xb\",1)");
    }

  if(angle==39)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"39\",\"shms\",\"pass130\",.2,1.,0.4,1.15,.85,1.15,\"xb\",1)");
    }
  c1->SaveAs(Form("doh%2.0fdeg.pdf",angle));
  return;
}
