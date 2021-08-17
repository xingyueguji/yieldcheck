
#include "plot_cxShmsHms.cpp"
//#include "plot_cx_raffaella.cpp"

void shmsHms(){
  //  gROOT->ForceStyle();
  //  gStyle->SetGridStyle(3);
  //  gStyle->SetTitleX(.5);
  //  gStyle->SetTitleW(.7);

  TCanvas *c1=new TCanvas();
  c1->Divide(3,1);
  c1->SetGrid();
  //void plot_cx(string target="d", string angle="39", string spec="shms",float "xb"min=0.0, float "xb"max=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"shms\",\"pass135\",.2,1.,-.1,4.,.9,1.1,\"xb\")");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"shms\",\"pass135\",.2,1.,-.1,8.,.9,1.1,\"xb\")");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"shms\",\"pass135\",.2,1.,0.6,1.1,.9,1.1,\"xb\")");

      c1->SaveAs("shmsHms.pdf");
  return;
}
