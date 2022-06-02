//#include "plot_cx.cpp"
#include "plot_cx.cpp"

void compareCxsec(double angle=21){
  TCanvas *c1=new TCanvas();
  c1->Divide(1,3);
  //void plot_cx(string target="d", string angle="39", string spec="shms",float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){
  if(angle==21)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"shms\",\"ELOG458\",.2,1.,0.,4.,.85,1.15)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"shms\",\"ELOG457\",.2,1.,0.,4.,.85,1.15)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"shms\",\"ORIG\",.2,1.,0.,4.,.85,1.15)");
    }

  if(angle==25)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"25\",\"shms\",\"pass103\",.2,1.,0.,2.,.85,1.15)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"25\",\"shms\",\"pass103\",.2,1.,0.,2.,.85,1.15)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"25\",\"shms\",\"pass103\",.2,1.,0.,2.,.85,1.15)");
    }

  if(angle==29)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"29\",\"shms\",\"pass103\",.2,1.,0.,1.2,.85,1.15)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"29\",\"shms\",\"pass103\",.2,1.,0.,1.2,.85,1.15)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"29\",\"shms\",\"pass103\",.2,1.,0.,1.2,.85,1.15)");
    }

  if(angle==33)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"33\",\"shms\",\"pass103\",.2,1.,0.,.8,.85,1.15)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"33\",\"shms\",\"pass103\",.2,1.,0.,.8,.85,1.15)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"33\",\"shms\",\"pass103\",.2,1.,0.,.8,.85,1.15)");
    }

  if(angle==39)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"39\",\"shms\",\"pass103\",.2,1.,0.,.5,.85,1.15)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"39\",\"shms\",\"pass103\",.2,1.,0.,.5,.85,1.15)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"39\",\"shms\",\"pass103\",.2,1.,0.,.5,.85,1.15)");
    }
  c1->SaveAs(Form("shms%2.0fdeg.pdf",angle));
  return;
}
