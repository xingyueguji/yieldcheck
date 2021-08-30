#include "errors.cpp"
#include "../src/getMomList.cpp"


//void errors(string tgt="h",string angle="25", string mom="3p5",string spec="shms"){

void plotAngle(string tgt="r",string angle="39",string spec="shms"){
  TCanvas *c1=new TCanvas();

 string pset[5];
 float psetf[5];
 getMomList(angle,pset,psetf,spec);
 double xdum[2]={-1,2};
 double ydum[2]={0,0};
 TGraph *gdum=new TGraph(2,xdum,ydum);
 gdum->GetYaxis()->SetRangeUser(0,5);
 gdum->GetXaxis()->SetRangeUser(-.1,.97);
 gdum->GetXaxis()->SetTitle("x_{B}");
 gdum->GetYaxis()->SetTitle("Error (%)");
 gdum->Draw("ap");
 gdum->SetTitle(Form("Uncertainities for %s %s#circ data",spec.c_str(), angle.c_str()));
 errors("r",angle,pset[0],spec);
 errors("r",angle,pset[1],spec);
 errors("r",angle,pset[2],spec);
 errors("r",angle,pset[3],spec);
 if(spec=="hms")errors("r",angle,pset[4],spec);
 
 c1->SaveAs(Form("%s%s.pdf",spec.c_str(),angle.c_str()));

  return;
}
