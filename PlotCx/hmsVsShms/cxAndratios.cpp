//#include "plot_cx.cpp"
#include "plot_cx.cpp"

void cxAndratios(double angle=21){
  TCanvas *c1=new TCanvas();
  c1->Divide(3,1);

  if(angle==21)
    {
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"h\",\"21\",\"shms\",.1,1.1,0.,4.,.8,1.2)");
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"d\",\"21\",\"shms\",.1,1.1,0.,4.,.8,1.2)");
      c1->cd(3);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"shms\",.1,1.1,0.,4.,.8,1.2)");
    }

  c1->SaveAs(Form("%2.0f.pdf",angle));
  return;
}
