//#include "plot_cx.cpp"
#include "plot_cx.cpp"

void justRatios(){
  TCanvas *c1=new TCanvas();
  c1->Divide(3,2);
  //void plot_cx(string target="d", string angle="39", string spec="shms",float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"shms\",.2,1.,0.,4.,.5,1.55)");

      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"r\",\"25\",\"shms\",.2,1.,0.,2.,.5,1.5)");

      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"29\",\"shms\",.2,1.,0.,1.2,.5,1.5)");

      c1->cd(4);
      gROOT->ProcessLine("plot_cx(\"r\",\"33\",\"shms\",.2,1.,0.,.8,.5,1.5)");

      c1->cd(5);
      gROOT->ProcessLine("plot_cx(\"r\",\"39\",\"shms\",.2,1.,0.,.5,.5,1.5)");
      c1->SaveAs("justRatios.pdf");
  return;
}
