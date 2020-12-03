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

void dataYield(Int_t run=2525, Double_t ngcCut=2., Double_t betaMin =0.5, Double_t betaMax=1.5, 
	       Double_t deltaMin=-10., Double_t deltaMax=22., Double_t minEdep=0.7, Double_t curCut=5., TString fname="test.root")

{

  ofstream outFile;
  outFile.open("dataYield.txt",ios::app | ios::out );
  Double_t beta, delta, etracknorm, ngc, curr, phd, thd, xfp, yfp, xpfp, ypfp, xCer, yCer, xb;
  Double_t  w2,cerEff, calEff, mom, xd, yd, goode=0, goode_corr=0, boilCorr, wt=0, sime=0,terr=0, piC=0;
  TString froot, report, fmc;
  TH2F *hCerEff=getCerEff(0);
  TH2F *hCerErr=getCerEff(1);
  TF1 *pionC=getPionContamination(run);
  Double_t charge=readReport(run,"BCM4C charge");
  //   Double_t deadTime=readReport(run,"edtm dt")/100.;
  Double_t deadTime=1.-readReport(run,"ps2 clt et");
  //    Double_t deadTime=1.-getLivetime(run,"lt");

  Double_t trackEff=readReport(run,"tr eff");
  Double_t psFact=readReport(run,"Ps2 fact");
  Double_t currentAvg=readReport(run,"BCM4C cut current");
  Double_t target=readReport(run,"target");

  //		    if(target==1.01)boilCorr=1.-currentAvg/100.*0.064; 
  //		    if(target==2.01)boilCorr=1.-currentAvg/100.*0.08; 
  if(target==1.01)boilCorr=1.-currentAvg/100.*0.069; 
  if(target==2.01)boilCorr=1.-currentAvg/100.*0.073; 
  //		    if(target==1.01)boilCorr=1.-currentAvg/100.*0.02675; 
  //		    if(target==2.01)boilCorr=1.-currentAvg/100.*0.03798; 
  if(target>2.01)boilCorr=1; 

  Double_t scale = (Double_t)1/(1-deadTime)/trackEff/(boilCorr)*psFact;
  cout <<charge<<"\t"<<deadTime<<"\t"<<trackEff<<"\t"<<psFact<<"\t"<<currentAvg<<endl;
  Double_t errCer=.02;
  Double_t errCal=.02;
  Double_t errTrack=.01;
  Double_t errPion=.02;
  //  Double_t errDead=getLivetime(run,"err")/(1.-deadTime);

  Double_t errDead=.01;
  Double_t errBoil=.02;

  Int_t nbins=60;
  Double_t minBin=-30.;
  Double_t maxBin=30.;


  //  TFile *oFile=new TFile(Form("dataYieldOut/dataYield_%d.root",run),"RECREATE");
  TFile *oFile=new TFile("dataYieldOut/pass10/"+fname,"RECREATE");
  TTree *tree=new TTree("tree","Data");
  TTree *tree2=new TTree("tree2","Run Eff.");

  tree2->Branch("boilCorr",&boilCorr);
  tree2->Branch("deadTime",&deadTime);
  tree2->Branch("trackEff",&trackEff);
  tree2->Branch("psFact",&psFact);
  tree2->Branch("scale",&scale);
  tree2->Fill();

  tree->Branch("calEff",&calEff);
  tree->Branch("piC",&piC);
  tree->Branch("cerEff",&cerEff);
  tree->Branch("P.gtr.dp",&delta);
  tree->Branch("P.gtr.ph",&phd);
  tree->Branch("P.gtr.thd",&thd);
  tree->Branch("P.gtr.y",&yd);
  tree->Branch("P.react.W2",&w2);
  tree->Branch("wt",&wt);


  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3c-shms-data/shms_replay_production_%d_-1.root",run);


  if (gSystem->AccessPathName(froot)==0)
    {
      //      cout<<"Found "<<froot<<endl;
      TH1D *hdd=new TH1D("hdd","Data Delta",nbins,minBin,maxBin);
      TH1D *hdd2=new TH1D("hdd2","Data Delta with Errors",nbins,minBin,maxBin);
      TH1D *hyld=new TH1D("hyld","Data Delta",nbins,minBin,maxBin);
      TH1D *heff=new TH1D("heff","Efficiency",nbins,minBin,maxBin);
      TH1D *heffcal=new TH1D("heffcal","Calo. Efficiency",nbins,minBin,maxBin);
      TH1D *heffcer=new TH1D("heffcer","Cer. Efficiency",nbins,minBin,maxBin);
      TH1D *heffpion=new TH1D("heffpion","Pion Contamination",nbins,minBin,maxBin);
      TH1D *herr=new TH1D("herr","Efficiency Error",nbins,minBin,maxBin);
      TH1D *herr2=new TH1D("herr2","Efficiency Error (#delta Y)^2",nbins,minBin,maxBin);
      TH1D *hxpd=new TH1D("hxpd","Data xptar",100,-100,100);
      TH1D *hypd=new TH1D("hypd","Data yptar",100,-100,100);
      TH1D *hxd=new TH1D("hxd","Data x tar",100,-1.,1.);
      TH1D *hyd=new TH1D("hyd","Data y tar",334,-10,10);
      TH1D *hw2d=new TH1D("hw2d","Data W2",375,-10,20);
      TH1D *hcerr=new TH1D("hcerr","Cer Eff",100,.9,1.0);      
      TH1D *hpion=new TH1D("hpion","Pion Contamination",200,0,.2);      
      TH1D *hcal=new TH1D("hcal","Cal Eff",100,.995,1.);      
      TH1D *hxb=new TH1D("hxb","xb Good Events",120,0,3);      
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
    	                    nEvents=1000;
      //            nEvents=100000;
      for (Int_t iEvent = 0; iEvent < nEvents; iEvent++) 
	{
	  if(iEvent%25000==0)cout<<iEvent<<endl;
	  tr->GetEntry(iEvent);
	  xCer=xfp-89.1*xpfp;
	  yCer=yfp-89.1*ypfp;
	  cerEff=hCerEff->GetBinContent(hCerEff->FindBin(yCer,xCer));
	  errCer=hCerErr->GetBinContent(hCerEff->FindBin(yCer,xCer));
	  bool fid=fidCut(xfp, yfp, xpfp, ypfp);
	  bool coll=collCut(thd, phd, delta, yd);
	  if(cerEff==0)cerEff=1;
	  if(ngc > ngcCut && beta > betaMin && beta < betaMax && delta > deltaMin && delta < deltaMax && etracknorm > minEdep){
	    //	  if(ngc > ngcCut && delta > deltaMin && delta < deltaMax && etracknorm > minEdep){
	    if(abs(thd)<0.1 && abs(phd)<0.1 && abs(yd) < 10.0){
	      if(curr>curCut && fid && coll){
		//Get event by event corrections
		piC=pionC->Eval(mom);
		hpion->Fill(piC);
		hcerr->Fill(cerEff);
		calEff=getCalEff(mom);
		hcal->Fill(calEff);
		wt=(1.0-piC)/cerEff*scale;
		//		    wt=1.0/cerEff/calEff/(boilCorr)*scale;
		//		    wt=(1.0-piC)/cerEff/calEff/(boilCorr)*scale;
		//wt=(1.0-piC)/cerEff/(boilCorr)*scale;
		// .8
		hdd->Fill(delta,wt);
		hdd2->Fill(delta,wt);
		hxpd->Fill(thd*1000,wt);
		hypd->Fill(phd*1000,wt);
		hxd->Fill(xd,wt);
		hyd->Fill(yd,wt);
		hw2d->Fill(w2,wt);
		hxb->Fill(xb,wt);
		hyld->Fill(delta);
		heff->Fill(delta,wt);
		heffcal->Fill(delta,calEff);
		heffcer->Fill(delta,cerEff);
		heffpion->Fill(delta,1-piC);
		//wt=(1.0-piC)/cerEff/(boilCorr)*scale;
		// errors should be fractional (%)
		terr=0;
		terr+=pow(errCer,2.);
		//		    terr+=pow(errCal,2);
		terr+=pow(errBoil,2.);
		terr+=pow(errDead,2.);
		terr+=pow(errTrack,2.);
		terr+=pow(errPion,2.);
		terr=sqrt(terr);
		herr->Fill(delta,terr*wt);
		herr2->Fill(delta,terr*terr*wt*wt);
		goode++;
		goode_corr+=wt;
		tree->Fill();
	      }
	    }
	  }
	}
      f->Close();
      delete f;

      for(Int_t i=1;i<=nbins;i++)
	{
	  double center=hdd2->GetBinCenter(i);
	  double content1=hyld->GetBinContent(i);
	  double content2=hdd2->GetBinContent(i);
	  double stat_sq=pow(hdd2->GetBinError(i),2.);
	  double sys_sq=pow(herr->GetBinContent(i),2);
	  double total=sqrt(stat_sq+sys_sq);
	  hdd2->SetBinError(i,total);
	  //	  cout <<center<<"\t"<<content<<"\t"<<sqrt(stat_sq)/content*100.<<"%\t"<<sqrt(sys_sq)/content*100<<"%\t"<<total<<endl; 
	  cout <<center<<"\t"<<content1<<"\t"<<content2<<" +/- "<<sqrt(stat_sq)<<"(stat) +/- "<<sqrt(sys_sq)<<"(syst)\t"<<total<<"(total)"<<endl; 
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
      tree2->Write();
      hdd->Write();
      hdd2->Write();
      hyld->Write();
      heff->Write();
      heffcal->Write();
      heffcer->Write();
      heffpion->Write();
      herr->Write();
      hxpd->Write();
      hypd->Write();
      hxd->Write();
      hyd->Write();
      hw2d->Write();
      hxb->Write();
      hcerr->Write();
      hpion->Write();
      hcal->Write();
      oFile->Close();
      delete oFile;
      
    }
  
  else {cout << "Couldn't find "<<froot<<endl;}
  
  return;
}


