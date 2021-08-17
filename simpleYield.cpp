#include <iostream>
#include <iomanip>
#include "src/readReport.cpp"
#include "src/getRadCorr.cpp"
#include "src/getCerEff.cpp"
#include "src/getCalEff.cpp"
#include "src/getLivetime.cpp"

using namespace std;

void dataYield(Int_t run=3226, Double_t ngcCut=2., Double_t betaMin =0.5, Double_t betaMax=1.5, 
Double_t deltaMin=-10., Double_t deltaMax=22., Double_t minEdep=0.7, Double_t curCut=5.)

{

  ofstream outFile;
  outFile.open("dataYield.txt",ios::app | ios::out );
  Double_t beta, delta, etracknorm, ngc, curr, phd, thd, xfp, yfp, xpfp, ypfp, xCer, yCer, xb;
  Double_t  w2,cerEff, calEff, mom, xd, yd, goode=0, goode_corr=0, boilCorr, wt=0, sime=0,terr=0;
  TString froot, report, fmc;
  TH2F *hCerEff=getCerEff(0);
  TH2F *hCerErr=getCerEff(1);

  Double_t charge=readReport(run,"BCM4C charge");
  //   Double_t deadTime=readReport(run,"edtm dt")/100.;
     Double_t deadTime=1.-readReport(run,"ps2 clt et");
  //    Double_t deadTime=1.-getLivetime(run,"lt");

  Double_t trackEff=readReport(run,"tr eff");
  Double_t psFact=readReport(run,"Ps2 fact");
  Double_t currentAvg=readReport(run,"BCM4C cut current");
  Double_t target=readReport(run,"target");
  Double_t scale = (Double_t)1/(1-deadTime)/trackEff*psFact;
  cout <<charge<<"\t"<<deadTime<<"\t"<<trackEff<<"\t"<<psFact<<"\t"<<currentAvg<<endl;
  Double_t errCer=0.01;
  Double_t errCal=0.01;
  Double_t errTrack=0.01;
  //  Double_t errDead=getLivetime(run,"err")/(1.-deadTime);

  Double_t errDead=0.01;
  Double_t errBoil=0.01;

  Int_t nbins=32;
  Double_t minBin=-10.;
  Double_t maxBin=22.;


  TFile *oFile=new TFile(Form("dataYieldOut/dataYield_%d.root",run),"RECREATE");
  TTree *tree=new TTree("tree","Data");
  tree->Branch("calEff",&calEff);
  tree->Branch("cerEff",&cerEff);
  tree->Branch("boilCorr",&boilCorr);
  tree->Branch("P.gtr.dp",&delta);
  tree->Branch("P.gtr.ph",&phd);
  tree->Branch("P.gtr.thd",&thd);
  tree->Branch("P.gtr.y",&yd);
  tree->Branch("P.react.W2",&w2);
  tree->Branch("scale",&scale);


  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3c-shms-data/shms_replay_production_%d_-1.root",run);


  if (gSystem->AccessPathName(froot)==0)
    {


      //      cout<<"Found "<<froot<<endl;

      TH1D *hdd=new TH1D("hdd","Data Delta",nbins,minBin,maxBin);

      TH1D *hyld=new TH1D("hyld","Data Delta",nbins,minBin,maxBin);
      TH1D *heff=new TH1D("heff","Efficiency",nbins,minBin,maxBin);
      TH1D *herr=new TH1D("herr","Efficiency Error",nbins,minBin,maxBin);

      TH1D *hxpd=new TH1D("hxpd","Data xptar",50,-.1,.1);
      TH1D *hypd=new TH1D("hypd","Data yptar",50,-.1,.1);
      TH1D *hxd=new TH1D("hxd","Data x tar",100,-1.,1.);
      TH1D *hyd=new TH1D("hyd","Data y tar",50,-6,6);
      TH1D *hw2d=new TH1D("hw2d","Data W2",100,0,13);
      TH1D *hcerr=new TH1D("hcerr","Cer Eff",100,.9,1.0);      
      TH1D *hcal=new TH1D("hcal","Cal Eff",100,.995,1.);      
      TH1D *hboil=new TH1D("hboil","Boiling Eff",100,.95,1.0);      
      TH1D *hxb=new TH1D("hxb","xb Good Events",100,0,1);      

      heff->Sumw2();
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
      //            nEvents=1000;
      //      nEvents=10000;
      for (Int_t iEvent = 0; iEvent < nEvents; iEvent++) 
	{
	  if(iEvent%25000==0)cout<<iEvent<<endl;
	  tr->GetEntry(iEvent);
	  xCer=xfp-89.1*xpfp;
	  yCer=yfp-89.1*ypfp;
	  cerEff=hCerEff->GetBinContent(hCerEff->FindBin(yCer,xCer));
	  errCer=hCerErr->GetBinContent(hCerEff->FindBin(yCer,xCer));
	  if(ngc > ngcCut && beta > betaMin && beta < betaMax && delta > deltaMin && delta < deltaMax && etracknorm > minEdep)
	    if(abs(thd)<0.1 && abs(phd)<0.1 && abs(yd) < 6.0)

	      {
		if(curr>curCut){
		  {//Get event by event corrections


		    hcerr->Fill(cerEff);
		    calEff=getCalEff(mom);
		    hcal->Fill(calEff);
		    if(target==1.01)boilCorr=1.-currentAvg/100.*0.064; 
		    if(target==2.01)boilCorr=1.-currentAvg/100.*0.08; 
		    if(target>2.01)boilCorr=1; 
		    if(cerEff==0)cerEff=1;
		    hboil->Fill(boilCorr);
		    wt=1/cerEff/calEff/(boilCorr)*scale;

		    hdd->Fill(delta,wt);
		    hxpd->Fill(thd,wt);
		    hypd->Fill(phd,wt);
		    hxd->Fill(xd,wt);
		    hyd->Fill(yd,wt);
		    hw2d->Fill(w2,wt);
		    hxb->Fill(xb,wt);

		    hyld->Fill(delta);
		    heff->Fill(delta,wt);
		    terr+=pow(errCer,2);
		    terr+=pow(errCal,2);
		    terr+=pow(errBoil,2);
		    terr+=pow(errDead,2);
		    terr+=pow(errTrack,2);
		    terr=sqrt(terr);
		    herr->Fill(delta,terr);
		    terr=0;
		    goode++;
		    goode_corr+=wt;
		    tree->Fill();
		  }
	      }
	    }
	}
      heff->Divide(hyld);
      herr->Divide(hyld);
      f->Close();
      delete f;

      for(Int_t i=1;i<=nbins;i++)
	{
	  //	  heff->SetBinError(i,herr->GetBinContent(i));
	  heff->SetBinError(i,0);
	  outFile << run <<"\t"<< charge <<"\t"<< psFact <<"\t"<< hyld->GetBinCenter(i);
	  outFile <<"\t"<< hyld->GetBinContent(i)<<"\t"<< heff->GetBinContent(i)<<"\t"<< herr->GetBinContent(i)<<endl;
	}
      
      cout<<fixed<<setprecision(4);
      cout << " psFact is : "<<psFact<<endl;
      cout <<" There were " <<goode <<" good electrons"<<endl;
      cout <<" There were " <<goode_corr <<" good electrons after cal., cer. , boil, tracking, deadtime, prescale"<<endl;
      cout << "The integral of hdd (QNY corrected in delta) is "<<hdd->Integral()<<endl;
      cout << "The total charge from bcm4c was "<<charge <<" uC."<<endl;
      cout << "QNY raw with prescale                              :" << goode/charge*psFact<<  "e-/mC" << endl;
      cout << "QNY corrected for tracking, lt, ps                 :"<< goode*scale/charge << "e-/mC" << endl;
      cout << "QNY corrected for tracking, lt, ps, cal, cer, boil :"<< goode_corr/charge << "e-/mC" << endl;
      oFile->cd();
      tree->Write();
      hdd->Write();
      hyld->Write();
      heff->Write();
      herr->Write();
      hxpd->Write();
      hypd->Write();
      hxd->Write();
      hyd->Write();
      hw2d->Write();
      hxb->Write();
      hcerr->Write();
      hcal->Write();
      hboil->Write();
      oFile->Close();
      delete oFile;
      
    }
  
  else {cout << "Couldn't find "<<froot<<endl;}
  
  return;
}


