#include "extractCS.cpp"
#include "src/formatHist.cpp"
#include "src/xsecTable.cpp"
//#include "src/getRadCorr.cpp"
//#include "src/readReport.cpp"
#include "src/getMomList.cpp"
#include "src/getCSB.cpp"
#include "src/getCJ.cpp"
#include "src/getKull.cpp"
#include "src/getKP.cpp"
#include "jmu/getJmu.cpp"

void plot_cx(string target="d", string angle="39", string spec="shms", string pass="pass308", float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3, string xaxis = "xb", int numPad=2 ){
  cout << " ***************** " << pass << " ***************** "<<endl;

  gPad->SetGrid();
  gStyle->SetTitleY(1.);
  gStyle->SetTitleH(.1);
  gStyle->SetTitleX(.2);
  gStyle->SetTitleW(.6);
 Float_t delta, ratio, err, ep, model_k, modeld, modelh, xmin, xmax;
 string pset[5];
 float psetf[5];
 getMomList(angle,pset,psetf,spec);
 xmin=psetf[0]*(.9);
 xmax=psetf[3]*(1.22);
 if(spec=="hms")xmax=psetf[4]*(1.1);

  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////

 vector <float> mx;
 vector <float> my_kph;  //kp hybrid
 vector <float> my_kpd;  //kp dis 
 vector <float> my;    //CJ15
 double wmin,wmax;

 Double_t thetac=getAngle(angle,spec);
  
  TGraphErrors *gr1=extractCS(spec,target,angle,pset[0],0,pass,xaxis);
  TGraphErrors *gr2=extractCS(spec,target,angle,pset[1],0,pass,xaxis);
  TGraphErrors *gr3=extractCS(spec,target,angle,pset[2],0,pass,xaxis);
  TGraphErrors *gr4=extractCS(spec,target,angle,pset[3],0,pass,xaxis);
  TGraphErrors *gr5;
  if(spec=="hms")gr5=extractCS(spec,target,angle,pset[4],0,pass,xaxis);

 if(xaxis=="xb") gr1->GetXaxis()->SetTitle("Bjorken X");
 if(xaxis=="ep") gr1->GetXaxis()->SetTitle("E' (GeV)");
 if(xaxis=="w2") gr1->GetXaxis()->SetTitle("W2 (GeV^2)");
 gr1->GetXaxis()->SetTitleSize(.06);
 gr1->GetXaxis()->CenterTitle();
 if(target=="h")target="LH2";
 if(target=="d")target="LD2";
 if(target=="r")target="D/H";
  string version="v996t2";
  if(pass=="pass310")version="v0.995";
  if(pass=="pass311")version="v0.990";
  gr1->SetTitle(Form("%s Data/MC %s",target.c_str(), version.c_str()));
 gr1->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
 //gr1->GetXaxis()->SetRangeUser(xbmin,xbmax);
     if(xaxis=="xb") gr1->GetXaxis()->SetLimits(xbmin,xbmax);
     if(xaxis=="ep") gr1->GetXaxis()->SetLimits(xmin-.1,xmax+.1);
     if(xaxis=="w2") gr1->GetXaxis()->SetLimits(wmin,wmax);
     gr1->GetXaxis()->SetLabelSize(.06);
     gr1->GetYaxis()->SetLabelSize(.06);
     gr1->GetXaxis()->SetNdivisions(-5);
 // gr1->GetYaxis()->SetNdivisions(5);
 
     gr1->SetMarkerStyle(27);
     gr2->SetMarkerStyle(27);
     gr3->SetMarkerStyle(27);
     gr4->SetMarkerStyle(27);
     if(spec=="hms")gr5->SetMarkerStyle(27);

 
     gr1->SetMarkerSize(.6);
     gr2->SetMarkerSize(.6);
     gr3->SetMarkerSize(.6);
     gr4->SetMarkerSize(.6);
     if(spec=="hms")gr5->SetMarkerSize(.6);

      gr1->SetMarkerColor(kRed);
     gr2->SetMarkerColor(kBlue);
     gr3->SetMarkerColor(kGreen+3);
     gr4->SetMarkerColor(kViolet);
     if(spec=="hms")gr5->SetMarkerColor(kBlack);

     gr1->Draw("ap");
     // jmur->Draw("sp");
     gr1->Draw("sp");
     gr2->Draw("sp");
     gr3->Draw("sp");
     gr4->Draw("sp");
     if(spec=="hms")gr5->Draw("sp");
     
  return;
}
