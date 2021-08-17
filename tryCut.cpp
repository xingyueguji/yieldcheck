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

void tryCut(Int_t run=2525, Double_t ngcCut=2., Double_t betaMin =0.5, Double_t betaMax=1.5, Double_t deltaMin=-10., Double_t deltaMax=22., Double_t minEdep=0.7, Double_t curCut=5., TString fname="test.root")
{
  Double_t beta, delta, etracknorm, ngc, curr, phd, thd, xfp, yfp, xpfp, ypfp, xCol, yCol, xb;
  Double_t  w2,cerEff, calEff, mom, xd, yd, goode=0, goode_corr=0, boilCorr, wt=0, sime=0,terr=0, piC=0;
  TString froot, report, fmc;
  TH2D *hcol=new TH2D("hcol","Pos. at Collimator (z = 253 cm);ytar(cm);xtar(cm)",100.,-20,20,100,-20,20);
  TH2D *hcol2=new TH2D("hcol2","Pos. at Collimator after cut (z = 253 cm);ytar(cm);xtar(cm)",100.,-20,20,100,-20,20);
  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3c-shms-data/shms_replay_production_%d_-1.root",run);

  if (gSystem->AccessPathName(froot)==0)
    {
      TFile *f=new TFile(froot);
      f->Print();
      TTree *tr=(TTree*)f->Get("T");
      tr->SetBranchAddress("P.gtr.beta", &beta);
      tr->SetBranchAddress("P.gtr.dp", &delta);
      tr->SetBranchAddress("P.gtr.p", &mom);
      tr->SetBranchAddress("P.gtr.ph", &phd);
      tr->SetBranchAddress("P.gtr.th", &thd);
      tr->SetBranchAddress("P.gtr.x", &xd);
      tr->SetBranchAddress("P.gtr.y", &yd);
      tr->SetBranchAddress("P.dc.x_fp", &xfp);
      tr->SetBranchAddress("P.dc.y_fp", &yfp);
      tr->SetBranchAddress("P.dc.xp_fp", &xpfp);
      tr->SetBranchAddress("P.dc.yp_fp", &ypfp);
      tr->SetBranchAddress("P.kin.W2", &w2);
      tr->SetBranchAddress("P.kin.x_bj", &xb);
      tr->SetBranchAddress("P.cal.etracknorm", &etracknorm);
      tr->SetBranchAddress("P.ngcer.npeSum", &ngc);
      tr->SetBranchAddress("P.bcm.bcm4c.AvgCurrent", &curr);
      Int_t nEvents = tr->GetEntries();
      //      nEvents=100000;

      for (Int_t iEvent = 0; iEvent < nEvents; iEvent++) 
	{
	  if(iEvent%25000==0)cout<<iEvent<<endl;
	  tr->GetEntry(iEvent);
	  if(ngc > ngcCut && delta > deltaMin && delta < deltaMax && etracknorm > minEdep && abs(thd)<0.1 && abs(phd)<0.1 && abs(yd) < 10.0){
	    xCol=253.*thd;
	    yCol=253.*phd + yd - 0.039*delta;
	    hcol->Fill(yCol,xCol);
	    bool fid=fidCut(xfp, yfp, xpfp, ypfp);
	    bool coll=collCut(thd, phd, delta, yd);
	    if(coll)hcol2->Fill(yCol,xCol);
	  }
	}
    }
      
  TCanvas *c1=new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  hcol->Draw("COLZ");
  c1->cd(2);
  hcol2->Draw("COLZ");
  
  return;
}


