#include <iostream>
#include <iomanip>
#include "TGraph2D.h"
#include "TROOT.h"
#include "TFile.h"
#include "TF1.h"
#include "TTree.h"
#include "TSystem.h"
#include "src/readReport.cpp"
#include "src/getRadCorr.cpp"
#include "src/getCerEff.cpp"
#include "src/getCalEff.cpp"
#include "src/getLivetime.cpp"
#include "src/getPionContamination.cpp"
#include "src/fidCut.cpp"
#include "src/collCut.cpp"

using namespace std;

void dataYield(Int_t run=1565, Double_t ngcCut=2., Double_t betaMin =0.5, Double_t betaMax=1.5, 
	       Double_t deltaMin=-10., Double_t deltaMax=22., Double_t minEdep=0.7, Double_t curCut=5., TString fname="test.root"){
  string spec="shms";
  if(run<2200)spec="hms";

  ofstream outFile;
  outFile.open("dataYield_pass23.txt",ios::app | ios::out );
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
  Double_t trigEff=readReport(run,"trig eff");
  Double_t psFact=readReport(run,"Ps2 fact");
  Double_t currentAvg=readReport(run,"BCM4C cut current");
  Double_t target=readReport(run,"target");
  //		    if(target==1.01)boilCorr=1.-currentAvg/100.*0.064; 
  //		    if(target==2.01)boilCorr=1.-currentAvg/100.*0.08; 
  //  if(target==1.01)boilCorr=1.-currentAvg/100.*0.069; 
  //  if(target==2.01)boilCorr=1.-currentAvg/100.*0.073; 
  //  if(target==1.01)boilCorr=1.-currentAvg/100.*0.02675; 
  //  if(target==2.01)boilCorr=1.-currentAvg/100.*0.03798; 
  if(target==1.01)boilCorr=1.-currentAvg/100.*0.0383; 
  if(target==2.01)boilCorr=1.-currentAvg/100.*0.0444; 
  //  if(target==1.01)boilCorr=1.-currentAvg/100.*0.07223; 
  //  if(target==2.01)boilCorr=1.-currentAvg/100.*0.02129; 

  if(target>2.01)boilCorr=1; 

  Double_t scale = (Double_t)1/(1-deadTime)/trackEff/trigEff/(boilCorr)*psFact;
  //  Double_t scale = (Double_t)1/(1-deadTime)/trackEff/(boilCorr)*psFact;
  Double_t errCer=.02;
  Double_t errCal=.02;
  Double_t errTrack=.01;
  Double_t errTrig=.01;
  Double_t errPion=.02;
  //  Double_t errDead=getLivetime(run,"err")/(1.-deadTime);
  Double_t errDead=.01;
  Double_t errBoil=.02;
  Int_t nbins=60;//
  Double_t minBin=-30.;//
  Double_t maxBin=30.;//

  //  TFile *oFile=new TFile(Form("dataYieldOut/dataYield_%d.root",run),"RECREATE");
  TFile *oFile=new TFile("dataYieldOut/pass23/"+fname,"RECREATE");
  TTree *tree=new TTree("tree","Data");
  TTree *tree2=new TTree("tree2","Run Eff.");

  tree2->Branch("boilCorr",&boilCorr);
  tree2->Branch("deadTime",&deadTime);
  tree2->Branch("trackEff",&trackEff);
  tree2->Branch("trigEff",&trackEff);
  tree2->Branch("psFact",&psFact);
  tree2->Branch("scale",&scale);
  tree2->Fill();

  string arm;
  double xpCut, ypCut, yCut;
  if(spec=="shms"){
    arm="P";
    xpCut= 0.10;
    ypCut= 0.10;
    yCut= 10.;
  }    
  if(spec=="hms"){
    arm="H";
    xpCut= 0.1;
    ypCut= 0.05;
    yCut= 10.;
  }

  tree->Branch("calEff",&calEff);
  tree->Branch("piC",&piC);
  tree->Branch("cerEff",&cerEff);
  tree->Branch(Form("%s.gtr.dp",arm.c_str()), &delta);
  tree->Branch(Form("%s.gtr.ph",arm.c_str()), &phd);
  tree->Branch(Form("%s.gtr.thd",arm.c_str()), &thd);
  tree->Branch(Form("%s.gtr.y",arm.c_str()), &yd);
  tree->Branch(Form("%s.react.W2",arm.c_str()), &w2);
  tree->Branch("wt",&wt);

  if(spec=="shms"){
  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3c-shms-data/shms_replay_production_%d_-1.root",run);
  }
  if(spec=="hms"){
  
froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-hms-data/hms_replay_production_%d_-1.root",run);
 if(run>=1565 && run <= 1578)froot = Form("/volatile/hallc/xem2/abishek/ROOTfiles/no_offset/hms_replay_production_%d_-1.root",run);
  }
  if (gSystem->AccessPathName(froot)==0)
    {
      //      cout<<"Found "<<froot<<endl;

      TH1D *hyld=new TH1D("hyld","Data Delta",nbins,minBin,maxBin);
      Double_t scale = (Double_t)1/(1-deadTime)/trackEff/trigEff/(boilCorr)*psFact;
      TH1D *hdd2=new TH1D("hdd2","Data lt, ps",nbins,minBin,maxBin);
      TH1D *hdd3=new TH1D("hdd3","Data lt, ps, trk, ",nbins,minBin,maxBin);
      TH1D *hdd4=new TH1D("hdd4","Data lt, ps, trk, boil",nbins,minBin,maxBin);
      TH1D *hdd5=new TH1D("hdd5","Data lt, ps, trk, boil, trg",nbins,minBin,maxBin);
      TH1D *hdd6=new TH1D("hdd6","Data lt, ps, trk, boil, trg, cal",nbins,minBin,maxBin);
      TH1D *hdd7=new TH1D("hdd7","Data lt, ps, trk, boil, trg, cal, cer",nbins,minBin,maxBin);

      TH1D *hdd=new TH1D("hdd","Data Delta Corrected",nbins,minBin,maxBin);

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
      tr->SetBranchAddress(Form("%s.gtr.beta",arm.c_str()), &beta);
      tr->SetBranchAddress(Form("%s.gtr.dp",arm.c_str()), &delta);
      tr->SetBranchAddress(Form("%s.gtr.p",arm.c_str()), &mom);
      tr->SetBranchAddress(Form("%s.gtr.ph",arm.c_str()), &phd);
      tr->SetBranchAddress(Form("%s.gtr.th",arm.c_str()), &thd);
      tr->SetBranchAddress(Form("%s.gtr.x",arm.c_str()), &xd);
      tr->SetBranchAddress(Form("%s.gtr.y",arm.c_str()), &yd);
      tr->SetBranchAddress(Form("%s.dc.x_fp",arm.c_str()), &xfp);
      tr->SetBranchAddress(Form("%s.dc.y_fp",arm.c_str()), &yfp);
      tr->SetBranchAddress(Form("%s.dc.xp_fp",arm.c_str()), &xpfp);
      tr->SetBranchAddress(Form("%s.dc.yp_fp",arm.c_str()), &ypfp);
      tr->SetBranchAddress(Form("%s.kin.W2",arm.c_str()), &w2);
      tr->SetBranchAddress(Form("%s.kin.x_bj",arm.c_str()), &xb);
      tr->SetBranchAddress(Form("%s.cal.etracknorm",arm.c_str()), &etracknorm);
      tr->SetBranchAddress(Form("%s.bcm.bcm4c.AvgCurrent",arm.c_str()), &curr);
      if(spec=="shms")tr->SetBranchAddress("P.ngcer.npeSum", &ngc);
      if(spec=="hms")tr->SetBranchAddress("H.cer.npeSum", &ngc);
      Int_t nEvents = tr->GetEntries();
      //nEvents=1000;
      //      nEvents=10000;
      double p0 = 0;
      double p1 = 0.00066401;
      double p2 = -0.00219306;
      double p3 = 0.00009893395;
      double p4 = 0.000010109;

      for (Int_t iEvent = 0; iEvent < nEvents; iEvent++) 
	{
	  if(iEvent%100000==0)cout<<iEvent<<endl;
	  tr->GetEntry(iEvent);
	  //	  if(spec=="hms")delta=delta-p0+p1*delta+p2*pow(delta,2)+p3*pow(delta,3)+p4*pow(delta,4);
	  xCer=xfp-89.1*xpfp;
	  yCer=yfp-89.1*ypfp;
	  cerEff=hCerEff->GetBinContent(hCerEff->FindBin(yCer,xCer));
	  errCer=hCerErr->GetBinContent(hCerEff->FindBin(yCer,xCer));
	  if(cerEff==0)cerEff=1;
	  if(spec=="hms")cerEff=0.98;
	  bool fid=fidCut(xfp, yfp, xpfp, ypfp);//shms only
	  bool coll=collCut(thd, phd, delta, yd);//shms only
	  //	  if(ngc > ngcCut && beta > betaMin && beta < betaMax && delta > deltaMin && delta < deltaMax && etracknorm > minEdep){
	  if(ngc > ngcCut && delta > deltaMin && delta < deltaMax && etracknorm > minEdep){
	    //	  if(ngc > ngcCut && delta > deltaMin && delta < deltaMax ){
	    if(abs(thd)<xpCut && abs(phd)<ypCut && abs(yd) < yCut)
	      {
		if(curr>curCut){// && fid && coll){
		  if( w2>1.2)// || !(run>=1565 && run <= 1578))
		    {
		    //Get event by event corrections
		    if(spec=="shms")piC=pionC->Eval(mom);
		    else piC=0.0;
		    hpion->Fill(piC);
		    hcerr->Fill(cerEff);
		    if(spec=="shms")calEff=getCalEff(mom);
		    hcal->Fill(calEff);
		    wt=(1.0-piC)/calEff/cerEff*scale;
		    hdd7->Fill(delta,wt);
		    if(spec=="shms")calEff=1.0;
		    if(spec=="hms")calEff=0.998;
		    wt=(1.0-piC)/calEff/cerEff*scale;
		    //		    wt=1.0/cerEff/calEff/(boilCorr)*scale;
		    //		    wt=(1.0-piC)/cerEff/calEff/(boilCorr)*scale;
		    //wt=(1.0-piC)/cerEff/(boilCorr)*scale;
		    // .8
		   // scale = 1/(1-deadTime)/trackEff/trigEff/(boilCorr)*psFact;
		    hdd->Fill(delta,wt);
		    hdd2->Fill(delta,1/(1-deadTime)*psFact);
		    hdd3->Fill(delta,1/(1-deadTime)/trackEff*psFact);
		    hdd4->Fill(delta,1/(1-deadTime)/trackEff/boilCorr*psFact);
		    hdd5->Fill(delta,1/(1-deadTime)/trackEff/trigEff/boilCorr*psFact);
		    hdd6->Fill(delta,1/(1-deadTime)/trackEff/trigEff/boilCorr/calEff*psFact);

		    
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
		    terr+=pow(errTrig,2.);
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
	}
      
      // include "syst" + stat errors in delta histo. (hdd2)
      // needs some more thought
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
	  if(content1!=0)
	  cout <<center<<"\t"<<content1<<"\t"<<content2<<" +/- "<<sqrt(stat_sq)<<"(stat) +/- "<<sqrt(sys_sq)<<"(syst)\t"<<total<<"(total)"<<endl; 
	}
      

      cout << "***************************************************************************************"<<endl;
      cout << "***************************************************************************************"<<endl;
      cout << "ROOTfile: "<<f->GetName()<<endl;
      cout << "Run Number                             "<<run<<endl;
      cout << "File name                              "<<fname<<endl;
      cout << "Delta Cut                              " <<deltaMin<<" to "<<deltaMax <<endl;
      cout << "E/p Cut                                " <<minEdep <<endl;
      cout << "Cerenekov Cut                          " <<ngcCut <<endl;
      cout << "Current Cut (BCM4C)                    " <<curCut <<endl;
      cout << "Prescale Factor                        " <<psFact<<endl;
      cout<<fixed<<setprecision(4);
      cout << "Average Current (BCM4C)                " <<currentAvg<<" uA"<<endl;
      cout << "Boiling Correction                     " <<(1-boilCorr)*100<<" %"<<endl;
      cout << "Deadtime                               " <<deadTime*100.<<" %" <<endl;
      cout << "Tracking Efficiency                    " <<trackEff*100.<<" %" <<endl;
      cout << "Trigger Efficiency                     " <<trigEff*100.<<" %" <<endl;
      cout << "Pion Contamintaion (mean +/- rms)      " <<hpion->GetMean()*100<<" +/- "<<hpion->GetRMS()*100.<<" %" <<endl;
      cout << "Cerenkov Efficiency (mean +/- rms)     " <<hcerr->GetMean()*100.<<" +/- "<<hcerr->GetRMS()*100.<<" %" <<endl;
      cout << "Calorimeter Efficiency (mean +/- rms)  " <<hcal->GetMean()*100.<<" +/- "<<hcal->GetRMS()*100.<<" %" <<endl;
      cout << "Good electrons (raw)                   " <<goode<<endl;
      cout << "Good electrons (corr)                  " <<goode_corr<<endl;
      cout << "The integral of hdd                    "<<hdd->Integral()<<endl;
      cout << "Charge (BCM4C)                         "<<charge <<" uC."<<endl;
      cout << "QNY raw with prescale                  " << goode/charge*psFact<<  " e-/mC" << endl;
      cout << "QNY corrected (flat corrections)       "<< goode*scale/charge << " e-/mC" << endl;
      cout << "QNY corrected (all corrections)        "<< goode_corr/charge << " e-/mC" << endl;
      cout << "***************************************************************************************"<<endl;
      cout << "***************************************************************************************"<<endl;



      outFile << "***************************************************************************************"<<endl;
      outFile << "ROOTfile: "<<f->GetName()<<endl;
      outFile << "Run Number                             "<<run<<endl;
      outFile << "File name                              "<<fname<<endl;
      outFile << "Delta Cut                              " <<deltaMin<<" to "<<deltaMax <<endl;
      outFile << "E/p Cut                                " <<minEdep <<endl;
      outFile << "Cerenekov Cut                          " <<ngcCut <<endl;
      outFile << "Current Cut (BCM4C)                    " <<curCut <<endl;
      outFile << "Prescale Factor                        " <<psFact<<endl;
      outFile<<fixed<<setprecision(4);
      outFile << "Average Current (BCM4C)                " <<currentAvg<<" uA"<<endl;
      outFile << "Boiling Correction                     " <<(1-boilCorr)*100<<" %"<<endl;
      outFile << "Deadtime                               " <<deadTime*100.<<" %" <<endl;
      outFile << "Tracking Efficiency                    " <<trackEff*100.<<" %" <<endl;
      outFile << "Trigger Efficiency                     " <<trigEff*100.<<" %" <<endl;
      outFile << "Pion Contamintaion (mean +/- rms)      " <<hpion->GetMean()*100<<" +/- "<<hpion->GetRMS()*100.<<" %" <<endl;
      outFile << "Cerenkov Efficiency (mean +/- rms)     " <<hcerr->GetMean()*100.<<" +/- "<<hcerr->GetRMS()*100.<<" %" <<endl;
      outFile << "Calorimeter Efficiency (mean +/- rms)  " <<hcal->GetMean()*100.<<" +/- "<<hcal->GetRMS()*100.<<" %" <<endl;
      outFile << "Good electrons (raw)                   " <<goode<<endl;
      outFile << "Good electrons (corr)                  " <<goode_corr<<endl;
      outFile << "The integral of hdd                    "<<hdd->Integral()<<endl;
      outFile << "Charge (BCM4C)                         "<<charge <<" uC."<<endl;
      outFile << "QNY raw with prescale                  " << goode/charge*psFact<<  " e-/mC" << endl;
      outFile << "QNY corrected (flat corrections)       "<< goode*scale/charge << " e-/mC" << endl;
      outFile << "QNY corrected (all corrections)        "<< goode_corr/charge << " e-/mC" << endl;
      outFile << "***************************************************************************************"<<endl;
      outFile << endl;

      f->Close();
      delete f;

      oFile->cd();
      tree->Write();
      tree2->Write();
      hdd->Write();
      hdd2->Write();
      hdd3->Write();
      hdd4->Write();
      hdd5->Write();
      hdd6->Write();
      hdd7->Write();
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


