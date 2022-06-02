
//#include "plot_cx.cpp"
//#include "plot_cxOnly.cpp"
#include "plot_cx_raffaella.cpp"

void ratiosPlot(double angle=21){
  //  gROOT->ForceStyle();
  //  gStyle->SetGridStyle(3);
  //  gStyle->SetTitleX(.5);
  //  gStyle->SetTitleW(.7);

  TCanvas *c1=new TCanvas("c1","c1",800,1000);
  //  c1->SetGrid();
  //void plot_cx(string target="d", string angle="39", string spec="shms",float "xb"min=0.0, float "xb"max=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){
  if(angle==21)
    {
      c1->Divide(1,2);
      c1->cd(1);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"hms\",\"pass125\",.2,1.,0.5,1.1,.9,1.1,\"xb\")");
      TPaveText *t=new TPaveText(.15,.15,.35,.25,"NDC");
      t->AddText("HMS 21deg");
      t->Draw();
      c1->cd(2);
      gROOT->ProcessLine("plot_cx(\"r\",\"21\",\"hms\",\"pass125\",.2,1.,0.5,1.1,.9,1.1,\"w2\")");
    }

  if(angle==25)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"25\",\"shms\",\"pass115\",.2,1.,0.5,1.1,.85,1.15,\"xb\")");
    }

  if(angle==29)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"29\",\"shms\",\"pass115\",.2,1.,0.5,1.1,.85,1.15,\"xb\")");
    }

  if(angle==33)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"33\",\"shms\",\"pass115\",.2,1.,0.5,1.1,.85,1.15,\"xb\")");
    }

  if(angle==39)
    {
      gROOT->ProcessLine("plot_cx(\"r\",\"39\",\"shms\",\"pass115\",.2,1.,0.5,1.1,.85,1.15,\"xb\")");
    }
  c1->SaveAs(Form("ratios%2.0fdeg.pdf",angle));
  return;
}
