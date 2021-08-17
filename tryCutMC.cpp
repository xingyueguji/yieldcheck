#include <iostream>
#include <iomanip>
#include "src/readReport.cpp"
#include "src/getRadCorr.cpp"
#include "src/getCerEff.cpp"
#include "src/getCalEff.cpp"
#include "src/getLivetime.cpp"
#include "src/getPionContamination.cpp"
#include "src/fidCut.cpp"
#include "src/collCut.cpp"

using namespace std;

void tryCutMC(string tgt="h",string angle="21", string mom="2p7", string spec="shms"){
  string kin=tgt+angle+"deg"+mom;
  cout <<" The Kinematic is " << kin<<endl;
  TH2D *hcol=new TH2D("hcol","Pos. at Collimator (z = 253 cm);ytar(cm);xtar(cm)",100.,-20,20,100,-20,20);
  TH2D *hcol2=new TH2D("hcol2","Pos. at Collimator after cut (z = 253 cm);ytar(cm);xtar(cm)",100.,-20,20,100,-20,20);
  TH2D *hcolmc=new TH2D("hcolmc","Pos. at Collimator (MC) (z = 253 cm);ytar(cm);xtar(cm)",100.,-2,2,100,-2,2);
  TH2D *hcol2mc=new TH2D("hcol2mc","Pos. at Collimator after cut (MC) (z = 253 cm);ytar(cm);xtar(cm)",100.,-20,20,100,-20,20);
  

  Double_t dxp, dyp, delup, deldown, hsec, thetac;
  dxp=60;
  dyp=65;
  delup=25;
  deldown=-15;

  cout << "The central momentum is "<<hsec<<endl;

  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21"&&spec=="shms")thetac=21.035;
  if(angle=="21"&&spec=="hms")thetac=20.995;
  if(angle=="59")thetac=58.98;

  Double_t thetacrad=thetac*TMath::Pi()/180;
  Float_t xfoc, yfoc, dxdz, dydz, ztarini, ytarini, delini, xptarini, yptarini;
  Float_t zrec, ytarrec, delrec, yptarrec, xptarrec, xtarini, xstop, ystop, fail_id;
   TString fmc = "mc/shms_"+kin+".root";
  TFile *fm=new TFile(fmc);
  fm->Print();
  TTree *trm=(TTree*)fm->Get("h1411");
  cout << "The MC files has "<<trm->GetEntries()<< " entries"<< endl;
  trm->SetBranchAddress("psxfp", &xfoc);
  trm->SetBranchAddress("psyfp", &yfoc);
  trm->SetBranchAddress("psxpfp", &dxdz);
  trm->SetBranchAddress("psypfp", &dydz);
  trm->SetBranchAddress("psztari", &ztarini);
  trm->SetBranchAddress("psytari", &ytarini);
  trm->SetBranchAddress("psdeltai", &delini);
  trm->SetBranchAddress("psyptari", &yptarini);
  trm->SetBranchAddress("psxptari", &xptarini);
  trm->SetBranchAddress("psztar", &zrec);
  trm->SetBranchAddress("psytar", &ytarrec);
  trm->SetBranchAddress("psdelta", &delrec);
  trm->SetBranchAddress("psyptar", &yptarrec);
  trm->SetBranchAddress("psxptar", &xptarrec);
  trm->SetBranchAddress("psxtari", &xtarini);
  trm->SetBranchAddress("xsieve", &xstop);
  trm->SetBranchAddress("ysieve", &ystop);
  trm->SetBranchAddress("stop_id", &fail_id);

  Float_t born_corr, rad, rci, hstheta, sigmac, q2, w2, csb_cx;
  Float_t hse, hsev, thetaini, sin2, nu, wt, xb, dt, phasespcor, phasespcorCos; 
  double xCol, yCol,xmc,ymc;
  Int_t nEvents=trm->GetEntries();
  //        nEvents=100000;
  Int_t wtf=0;
  cout << "About to loop"<<endl;

  for (Int_t i=0; i<nEvents; i++)
    {
      if(i%250000==0)cout<<i<<endl;
      trm->GetEntry(i);
      if(fail_id==0 && delrec<22. && delrec >-10.)
       {
	 if(abs(xptarrec)<.1 && abs(yptarrec)<.1 && abs(ytarrec)<10.0)
	   {
	     xmc=xtarini+22.4*xptarini;
	     ymc=ytarini+22.4*yptarini;
	     hcolmc->Fill(ymc,xmc);
	     xCol=253.*xptarrec;
	     yCol=253.*yptarrec + ytarrec - 0.039*delrec;
	     hcol->Fill(yCol,xCol);
	     bool fid=fidCut(xfoc, yfoc, dxdz, dydz);
	     bool coll=collCut(xptarrec, yptarrec, delrec, ytarrec);
	     if(coll)hcol2->Fill(yCol,xCol);
	   }
       }
    }
     
  TCanvas *c1=new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  hcol->Draw("COLZ");
  c1->cd(2);
  hcol2->Draw("COLZ");
  c1->cd(3);
  hcolmc->Draw("COLZ");
  
  return;
}


