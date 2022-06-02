//#include "plot_cx.cpp"
#include "plot_cx.cpp"

void hmsCxAndRatios(double angle=21){
  TCanvas *c1=new TCanvas();
  c1->Divide(3,1);
  //void plot_cx(string target="d", string angle="39", string spec="shms",float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){
  if(angle==21)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"hms\",\"pass130\",.3,1.,0.,3.,.75,1.1)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"hms\",\"pass130\",.3,1.,0.,5.,.75,1.1)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"hms\",\"pass130\",.3,1.,0.55,0.9,.9,1.05)");
    }

  c1->SaveAs(Form("hms%2.0fdeg.pdf",angle));
  return;
}
