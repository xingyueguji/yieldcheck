//#include "plot_cx.cpp"
#include "plot_cx.cpp"

void justratio(double angle=21){
  TCanvas *c1=new TCanvas();

  if(angle==21)
    {

      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"shms\",.2,.95,0.,4.,.8,1.2)");
    }

  c1->SaveAs(Form("%2.0fratio.pdf",angle));
  return;
}
