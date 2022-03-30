#include "TH1.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TGraph2D.h"
#include "TMath.h"
#include <iostream>
#include <iomanip>
//#include "src/readReport.cpp"
//#include "src/getRadCorr.cpp"
#include "src/getCerEff.cpp"
#include "src/getMom.cpp"
#include "src/getCharge.cpp"
#include "src/getHMSCharge.cpp"
#include "src/collCut.cpp"
#include "src/fidCut.cpp"
#include "src/getRadCorrW2.cpp"
#include "src/getRadCorr.cpp"

using namespace std;

void Acceptance(string tgt="h",string angle="21", string mom="3p3", string spec="shms"){

  string kin=tgt+angle+"deg"+mom;
  cout <<" The Kinematic is " << kin<<endl;
  Double_t pOffset=0.;
  Double_t mp = .9382723;
  Double_t mp2 = mp*mp;
  Double_t dxp, dyp, delup, deldown, delCutHi, delCutLo, xpCut, ypCut, yCut;
  Double_t target, ebeam, hsec, thetac, tgtDenLen, tgtMass, offset,beamTheta;
  Double_t charge=0;

  if(spec=="shms")
    {
      //      dxp=60;//phi in MC xp_tar
      //      dyp=65;
      dxp=30.;//phi in MC xp_tar
      dyp=30.;//phi in MC xp_tar
      delup=25;
      deldown=-15;
      //match data cuts
      delCutLo = -10.;
      delCutHi = +22.;
      xpCut= 0.03;
      ypCut= 0.03;
      yCut= 10.;
    }

  if(spec=="hms")
    {
      dxp=110;
      dyp=65;
      delup=15;
      deldown=-15;      
      delCutLo = -6.;
      delCutHi = +9.;
      xpCut= 0.1;
      ypCut= 0.05;
      yCut= 10.;
    }

  ebeam=10.602;//*(1.0-0.001);
  charge=1.;

  hsec=getMom(kin,spec);
  cout << "The central momentum is "<<hsec<<endl;
  if(spec=="hms"&&hsec<5.5){  
    offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
    hsec=hsec*offset;
  }
  cout << "The central momentum is "<<hsec<<endl;
  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21"&&spec=="shms")thetac=21.035;
  if(angle=="21"&&spec=="hms")thetac=20.995;

  cout << "The central angle is "<<thetac<<endl;
  if(angle=="59")thetac=58.98;

  cout << "Correcting central angle for beam angle"<<endl;
  cout << "Before: "<<thetac<<endl;
  beamTheta=0.00045;//-0.00025; //shooting beam right .45mr
  if(spec=="hms")beamTheta*=-1;
  thetac+=beamTheta*180./TMath::Pi();
  cout << "After: "<<thetac<<endl;
  //////////////////////////////////////
  Double_t thetacrad=thetac*TMath::Pi()/180;
  Float_t xfoc, yfoc, dxdz, dydz, ztarini, ytarini, delini, xptarini, yptarini;
  Float_t zrec, ytarrec, delrec, yptarrec, xptarrec, xtarini, xstop, ystop, fail_id;
  TString fmc = "mc/casey/"+spec+"_mc_"+kin+".root";
  TString fdata = "dataYieldOut/pass58/"+spec+"_dataYield_"+kin+".root";
  TString fdum = "dataYieldOut/pass58/"+spec+"_dataYield_al21deg3p3_h.root";

  TFile *fm=new TFile(fmc);
  fm->Print();

  TTree *trm;
  string arm;
  if(spec=="shms")
    {
      trm=(TTree*)fm->Get("h1411");
      arm="p";
    }
  if(spec=="hms")
    {
      trm=(TTree*)fm->Get("h1");
      arm="h";
    }

  cout << "The MC files has "<<trm->GetEntries()<< " entries"<< endl;

  trm->SetBranchAddress(Form("%ssxfp",arm.c_str()), &xfoc);
  trm->SetBranchAddress(Form("%ssyfp",arm.c_str()), &yfoc);
  trm->SetBranchAddress(Form("%ssxpfp",arm.c_str()), &dxdz);
  trm->SetBranchAddress(Form("%ssypfp",arm.c_str()), &dydz);
  trm->SetBranchAddress(Form("%ssztari",arm.c_str()), &ztarini);
  trm->SetBranchAddress(Form("%ssytari",arm.c_str()), &ytarini);
  trm->SetBranchAddress(Form("%ssdeltai",arm.c_str()), &delini);
  trm->SetBranchAddress(Form("%ssyptari",arm.c_str()), &yptarini);
  trm->SetBranchAddress(Form("%ssxptari",arm.c_str()), &xptarini);
  trm->SetBranchAddress(Form("%ssztar",arm.c_str()), &zrec);
  trm->SetBranchAddress(Form("%ssytar",arm.c_str()), &ytarrec);
  trm->SetBranchAddress(Form("%ssdelta",arm.c_str()), &delrec);
  trm->SetBranchAddress(Form("%ssyptar",arm.c_str()), &yptarrec);
  trm->SetBranchAddress(Form("%ssxptar",arm.c_str()), &xptarrec);
  trm->SetBranchAddress(Form("%ssxtari",arm.c_str()), &xtarini);
  trm->SetBranchAddress("xsieve", &xstop);
  trm->SetBranchAddress("ysieve", &ystop);
  trm->SetBranchAddress("stop_id", &fail_id);

  TString fOut=Form("acc30bins_tight_cut__%s_%s.root",spec.c_str(),kin.c_str());
  TFile *out=new TFile(fOut,"RECREATE");

  Float_t hse, hsev, sin2, xb, nu, wt, q2, w2,thetaini, dt, phasespcor, phasespcorCos; 
  //  Float_t born, rad, rci;
  TGraph2D *gr;
  TGraph2D *gr2;
  TGraph2D *gr3;
  if(tgt=="h")
    {
      gr=getRadCorrW2("h",1,spec.c_str());  
      gr->SetName("gr");
      gr2=getRadCorrW2("h",2,spec.c_str());  
      gr2->SetName("gr2");
      gr3=getRadCorrW2("h",3,spec.c_str());  
      gr3->SetName("gr3");
      //      tgtDenLen=0.0723*9.9659*.996;
      //      tgtMass=1.0079;
    }



  Int_t ngen=0;
  Int_t nacc=0;
  Float_t born=0;
  Float_t rad=0;
  Float_t rci=0;
  Double_t totalWt=0;
  Double_t sigave=0;
  Int_t nbin_delta=30;
  Int_t nbin_theta=30;
  Double_t delta_low=-15.;
  Double_t delta_high=25.;
  Double_t theta_low=-65.;
  Double_t theta_high=65.;

  TH1D *hdt=new TH1D("hdt","Data Weighted",nbin_delta, delta_low, delta_high);
  TH1D *hda=new TH1D("hda","Data Weighted",nbin_delta, delta_low, delta_high);
  TH1D *htt=new TH1D("htt","Solid Angle Acc",nbin_theta, theta_low, theta_high);
  TH1D *hta=new TH1D("hta","Solid Angle Thrown",nbin_theta, theta_low, theta_high);
  TH1D *hrad_xs=new TH1D("hrad_xs","sigma rad",nbin_delta, delta_low, delta_high);
  TH1D *hborn_xs=new TH1D("hborn_xs","sigma born",nbin_delta, delta_low, delta_high);

  TH2D *hacc=new TH2D("hacc","Acceptance;#theta - #theta_{C} (mrad);#deltaP/P %;Accetpance",nbin_theta, theta_low, theta_high,nbin_delta, delta_low, delta_high);
  TH2D *hthn=new TH2D("hthn","Acceptance;#theta - #theta_{C} (mrad);#deltaP/P %;Accetpance",nbin_theta, theta_low, theta_high,nbin_delta, delta_low, delta_high);
  TH2D *hsus=new TH2D("hsus","Acceptance;#theta - #theta_{C} (mrad);#deltaP/P %;Accetpance",nbin_theta, theta_low, theta_high,nbin_delta, delta_low, delta_high);
  TH2D *heff=new TH2D("heff","Acceptance;#theta - #theta_{C} (mrad);#deltaP/P %;Accetpance",nbin_theta, theta_low, theta_high,nbin_delta, delta_low, delta_high);
  TH2D *hbc=new TH2D("hbc","BinCentering;#theta - #theta_{C} (mrad);#deltaP/P %;Correction",nbin_theta, theta_low, theta_high,nbin_delta, delta_low, delta_high);
  TH2D *herr=new TH2D("herr","error;#theta - #theta_{C} (mrad);#deltaP/P %;Correction",nbin_theta, theta_low, theta_high,nbin_delta, delta_low, delta_high);


  TH2D *xyt=new TH2D("xyt","Thrown xp vs yp",100,-75,75,100,-75,75);
  TH2D *xya=new TH2D("xya","Accept xp vs yp",100,-75,75,100,-75,75);



  Int_t nx=hbc->GetNbinsX();
  Int_t ny=hbc->GetNbinsY();
  for(Int_t i=1; i <= nx; i++){
    for(Int_t j=1; j <= ny; j++){
      //Calculate E' and apply offset

      Double_t delrec=hbc->GetYaxis()->GetBinCenter(j);
      Double_t thetaini=hbc->GetXaxis()->GetBinCenter(i)/1000.+thetacrad;
      hse=hsec*(1. + delrec/100.);
      //      hse=hse*(1+pOffset);
      //call cross sections with initial quantities
      sin2 = sin(thetaini/2.)*sin(thetaini/2.);
      nu = ebeam - hse;
      q2 = 4.*hse*ebeam*sin2;
      w2= mp2 + 2.*mp*nu - q2;
      xb=q2/2./mp/nu;

      rad = gr3->Interpolate(w2,thetaini*180./TMath::Pi());// rad

      sin2 = sin(thetacrad/2.)*sin(thetacrad/2.);
      q2 = 4.*hse*ebeam*sin2;
      w2= mp2 + 2.*mp*nu - q2;

      Double_t radc = gr3->Interpolate(w2,thetacrad*180./TMath::Pi());// rad
      //      Double_t bc_corr=radc/rad*born/rad;
      Double_t bc_corr=radc/rad;

      //      cout <<"i, j, delta, theta, bc_corr: "<< i<<"\t"<<j<<"\t"<<delrec <<"  " <<thetaini*180./TMath::Pi()<<"\t"<<bc_corr<<endl;
      if(rad>0)hbc->SetBinContent(i,j,bc_corr);
      if(rad>0)hbc->SetBinError(i,j,0);
    }
  }

  Int_t nEvents=trm->GetEntries();
  Double_t nEve=0;
  Int_t wtf=0;
  cout << "About to loop"<<endl;
  // nEvents=0;
  for (Int_t i=0; i<nEvents; i++)
    {
      trm->GetEntry(i);
      if(abs(yptarini)<ypCut && abs(xptarini)<xpCut){     
	nEve++;
      //      yptarini= yptarini*1000.;
      thetaini = acos(cos(thetacrad + yptarini)*cos(xptarini))-thetacrad;
      //      yptarini=thetaini*180.00/TMath::Pi();
      if(i%250000==0)cout<<i<<endl;
      thetaini=thetaini*1000;
      xptarini=xptarini*1000;
      yptarini=yptarini*1000;

      if(thetaini<-21.55555&&thetaini>-26.0000&&delini>1.33333&&delini<4.33333){xyt->Fill(yptarini,xptarini);}
      hthn->Fill(thetaini, delini);
      hdt->Fill(delini);
      htt->Fill(thetaini);

      if(fail_id==0){
	if(thetaini<-21.55555&&thetaini>-26.0000&&delini>1.33333&&delini<4.33333){xya->Fill(yptarini,xptarini);}
	hda->Fill(delini);
	hta->Fill(thetaini);
	hacc->Fill(thetaini, delini);
	hsus->Fill(thetaini, delini);
	heff->Fill(thetaini, delini);
      }


      }
    }
  //  Double_t lumdata=tgtDenLen*6.022137e-10/tgtMass*charge/1.602177e-13; // targets/nb
  //  charge=70028.476;
  cout << "There were "<<nEve<<" events that passed xp, yp, cut"<<endl;
  charge=1;
  double lumi=2676.31*charge;

  double factor=(dxp*dyp*4*nbin_delta/nEve/1000./1000.);
  cout << "The factor to scale heff is "<<factor<<endl;
  double dep=0.4*3.3/nbin_delta;
  heff->Scale(factor);
  //  hda->Scale(factor); 
  auto heffLumi=(TH2D*)heff->Clone();
  heffLumi->SetName("hEffLumi");
  heffLumi->Scale(lumi*dep);
  hacc->Divide(hthn);
 
  hacc->GetYaxis()->SetTitleOffset(1.4);
  hacc->GetXaxis()->SetTitleOffset(1.8);
  hacc->GetXaxis()->CenterTitle(1);
  hacc->GetYaxis()->CenterTitle(1);
  hacc->GetZaxis()->CenterTitle(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);


  //  TCanvas *c1=new TCanvas();

  //    c1->SetPhi(120);
  //    hacc->Draw("LEGO2");

  //  c1->Divide(3,1);
  //  c1->cd(1);
  //  hthn->Draw("LEGO");
  //  c1->cd(2);
  //  hsus->Draw("LEGO");
  //  c1->cd(3);
  //  hacc->Draw("LEGO")

  xyt->Write();
  xya->Write();
    hbc->Write();
    heff->Write();
    heffLumi->Write();
    hthn->Write();
    hsus->Write();
    hacc->Write();
    hdt->Write();
    hda->Write();
    htt->Write();
    hta->Write();

    TFile *fd=new TFile(fdata);
    fd->Print();
    auto hdata=(TH2D*)fd->Get("yield4acc")->Clone();
    hdata->SetName("hdata");
    hdata->SetDirectory(0);

    auto hdata_raw=(TH2D*)fd->Get("yield4acc")->Clone();
    hdata_raw->SetName("hdata_raw");
    hdata_raw->SetDirectory(0);

    auto hdd=(TH2D*)fd->Get("hdd")->Clone();
    hdd->SetName("hdd");
    hdd->SetDirectory(0);

    auto hBoilCorr=(TH1D*)fd->Get("hBoilCorr")->Clone();
    hBoilCorr->SetName("hBoilCorr");
    hBoilCorr->SetDirectory(0);
    hBoilCorr->Divide(hdd);
    double density_corr=hBoilCorr->GetBinContent(30);
    cout <<density_corr<<endl;
    //    density_corr=1;
    fd->Close();
    TFile *fd2=new TFile(fdum);
    fd2->Print();
    auto hdum=(TH2D*)fd2->Get("yield4acc")->Clone();
    hdum->SetName("hdum");
    hdum->SetDirectory(0);

    out->cd();

    if(spec=="shms")charge=getCharge(tgt,angle,mom);
    if(spec=="hms")charge=getHMSCharge(kin);
    cout << "The Charge is: "<<charge<<endl;
    hdata->Scale(1./charge);
   for(int i=0;i<10;i++)cout << hdata->GetBinContent(15,15);
   cout << "#1"<<hdata_raw->GetBinContent(15,15);
 //=============================
 // Dummy normalized data yields
 //=============================
   Float_t charged=0;
   if(spec=="hms")
     {
       if(kin=="h21deg3p3"||kin=="d21deg3p3"){
	 charged+=readReport(1641,"BCM4C charge");
       }
       if(kin=="h21deg4p0"||kin=="d21deg4p0"){
	 charged+=readReport(1628,"BCM4C charge");
	 charged+=readReport(1629,"BCM4C charge");
       }
       if(kin=="h21deg4p5"||kin=="d21deg4p5"){
	 charged+=readReport(1609,"BCM4C charge");
	 charged+=readReport(1610,"BCM4C charge");
       }
       if(kin=="h21deg5p1"||kin=="d21deg5p1"){
	 charged+=readReport(1596,"BCM4C charge");
       }
       if(kin=="h21deg5p7"||kin=="d21deg5p7"){
	 charged+=readReport(1573,"BCM4C charge");
       }
     }
   if(spec=="shms")charged=getCharge("al",angle,mom);
   hdum->Scale(1/charged);

   hdata->Add(hdum,-1);
   cout << "#1"<<hdata_raw->GetBinContent(15,15);
   hdata->Scale(1/density_corr);
   hdata->Divide(heffLumi);
   //  The errors on hdata are correct so far 
   // includes dummy stat + yield stat + MC stat
   nx=hdata->GetNbinsX();
   ny=hdata->GetNbinsY();
   //  
   for(Int_t i=1; i <= nx; i++){
     for(Int_t j=1; j <= ny; j++){
       double err=hdata->GetBinError(i,j);
       double content=hdata->GetBinContent(i,j);
       double rel_err=0;
       if(content!=0)rel_err=err/content;
       //       cout << hdata->GetBinContent(i,j)<<endl;
       cout << i <<"\t"<<j<<"\t"<<err<<"\t"<<content<<"\t"<<rel_err<<endl;
       herr->SetBinContent(i,j,rel_err);
       if(rel_err>.05)hdata->SetBinContent(i,j,0);
     }
   }
   //  Average Over theta and do bin centering
   hdata->Multiply(hbc);



   cout << endl;
   //  j  =  y  =   delta
   //  i  =  x  =   theta
   for(Int_t j=1; j <= ny; j++){
     double wav=0;
     double sum_wt=0;
     double wav_err=0;

     for(Int_t i=11; i <= 20; i++){
       double center= hdata->GetXaxis()->GetBinCenter(i);
       double content=hdata->GetBinContent(i,j);
       double error=  hdata->GetBinError(i,j);
       cout <<"Theta: "<< center << "\t" << content <<" +/- "<<error;
       if(content!=0){       
	 sum_wt+=1/pow(error,2); 
	 wav+=content/pow(error,2); 
       }
     }
     
     if(sum_wt!=0){
       wav+=wav/sum_wt;
       wav_err+=1/sqrt(sum_wt);
       double center= hdata->GetYaxis()->GetBinCenter(j);
       cout << "The weighted average is "<<wav<<" +/- "<<wav_err << " for delta= "<<center<<endl;   
     }
     hrad_xs->SetBinContent(j,wav);
     hrad_xs->SetBinError(j,wav_err);
     double center=hrad_xs->GetBinCenter(j);

   }




   /*
	  if(choice==1)y[i]=born[i];
	  if(choice==2)y[i]=ratio[i];
	  if(choice==3)y[i]=rad[i];
	  if(choice==4)y[i]=bornInc[i];
	  if(choice==5)y[i]=bornQe[i];
	  if(choice==6)y[i]=radEl[i];
	  if(choice==7)y[i]=radQe[i];
	  if(choice==8)y[i]=radDis[i];
   */

   TGraph2D *gBorn=getRadCorr(tgt.c_str(),1,spec.c_str());  
   gBorn->SetName("gBorn");
   TGraph2D *gRadEl=getRadCorr(tgt.c_str(),6,spec.c_str());  
   gRadEl->SetName("gRadEl");
   TGraph2D *gRadQe=getRadCorr(tgt.c_str(),7,spec.c_str());  
   gRadQe->SetName("gRadQe");
   TGraph2D *gRadDis=getRadCorr(tgt.c_str(),8,spec.c_str());  
   gRadDis->SetName("gRadDis");


   for(int i=0; i<nbin_delta; i++){

     double delt=hrad_xs->GetBinCenter(i);
     double radxs=hrad_xs->GetBinContent(i);
     double errorxs=hrad_xs->GetBinError(i)/radxs;
     double ep=hsec*(1. + delt/100.);

     double born=gBorn->Interpolate(ep, thetac);
     double radEl=gRadEl->Interpolate(ep, thetac);
     double radQe=gRadQe->Interpolate(ep, thetac);
     double radDis=gRadDis->Interpolate(ep, thetac);

     double born_xs=(radxs-radEl-radQe)*born/radDis;
     double born_err=born_xs*errorxs;
     hborn_xs->SetBinContent(i,born_xs);
     hborn_xs->SetBinError(i,born_err);
   }


   hrad_xs->Write();
   hborn_xs->Write();
   herr->Write();
   hdata->Write();
   hdata_raw->Write();
   hdum->Write();
   hBoilCorr->Write();
   hdd->Write();
   out->Close();
  return;
}

