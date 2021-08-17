#include <iostream>
#include <iomanip>
#include "src/readReport.cpp"
#include "src/getRadCorr.cpp"
#include "src/getCerEff.cpp"

using namespace std;

void mcWt(string kin="c21deg5p1")

{
  Float_t pOffset=-0.017;
  Float_t mp = .9382723;
  Float_t mp2 = mp*mp;
  TGraph2D *gr;
  TGraph2D *gr2;
  TGraph2D *gr3;
  Float_t maxev, dxp, dyp, delup, deldown;
  Float_t target, ebeam, hsec, thetac, tgtDenLen, tgtMass;
  Float_t charge=0;
  ofstream oFile;

  ofstream outFile;
  outFile.open("mcWt.txt",ios::app | ios::out );
  maxev=1000000;
  dxp=60;
  dyp=65;
  delup=25;
  deldown=-15;

  if(kin=="c25deg2p5")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=2.5*(1+pOffset);
      thetac=24.98;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(3083,"BCM4C charge");
      charge+=readReport(3084,"BCM4C charge");
    }

  if(kin=="c25deg3p0")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=3.0*(1+pOffset);
      thetac=24.98;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(3070,"BCM4C charge");
      charge+=readReport(3071,"BCM4C charge");
    }

  if(kin=="c25deg3p5")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=3.5*(1+pOffset);
      thetac=24.98;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(3057,"BCM4C charge");
      charge+=readReport(3058,"BCM4C charge");
      charge+=readReport(3059,"BCM4C charge");
    }

  if(kin=="c25deg4p4")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=4.4*(1+pOffset);
      thetac=24.98;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(3035,"BCM4C charge");
      charge+=readReport(3036,"BCM4C charge");
      charge+=readReport(3037,"BCM4C charge");
    }

  if(kin=="c21deg2p7")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=2.7*(1+pOffset);
      thetac=21.035;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(2547,"BCM4C charge");
      charge+=readReport(2548,"BCM4C charge");
    }
  if(kin=="c21deg3p3")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=3.3*(1+pOffset);
      thetac=21.035;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(2540,"BCM4C charge");
      charge+=readReport(2541,"BCM4C charge");
    }
  if(kin=="c21deg4p0")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=4.0*(1+pOffset);
      thetac=21.035;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(2509,"BCM4C charge");
      charge+=readReport(2510,"BCM4C charge");
    }
  if(kin=="c21deg5p1")
    { 
      gr=getRadCorr("c",1);  
      gr2=getRadCorr("c",2);  
      gr3=getRadCorr("c",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=5.1*(1+pOffset);
      thetac=21.035;
      tgtDenLen=2.19*(.5244/2.19);
      tgtMass=12.011;
      charge+=readReport(2507,"BCM4C charge");
      charge+=readReport(2508,"BCM4C charge");
    }

  cout << "Made it throught if(kin==)"<<endl;
  if(kin=="h21deg3p3")
    { 
      gr=getRadCorr("h2cryo",1);  
      gr2=getRadCorr("h2cryo",2);  
      gr3=getRadCorr("h2cryo",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=3.30*(1+pOffset);
      thetac=21.035;
      tgtDenLen=0.0723*9.9659*.996;
      tgtMass=1.0079;
      charge+=readReport(2524,"BCM4C charge");
      charge+=readReport(2525,"BCM4C charge");
      charge+=readReport(2526,"BCM4C charge");
    }

  if(kin=="d21deg3p3")
    { 
      gr=getRadCorr("d2cryo",1);  
      gr2=getRadCorr("d2cryo",2);  
      gr3=getRadCorr("d2cryo",3);  
      target=11;//not used
      ebeam=10.602;
      hsec=3.30*(1+pOffset);
      thetac=21.035;
      tgtDenLen=.167*9.9682*.996;
      tgtMass=2.014;
    }

  Float_t thetacrad=thetac*TMath::Pi()/180;
  Float_t lumdata=tgtDenLen*6.022137e-10/tgtMass*charge/1.602177e-13; // targets/nb
  cout << "lumdata: "<<lumdata<<"targets/cm^2"<<endl;
  outFile <<kin<<"\t"<< ebeam <<"\t"<< thetac<<"\t"<<pOffset <<"\t" << lumdata <<"\t";
  Float_t xfoc, yfoc, dxdz, dydz, ztarini, ytarini, delini, xptarini, yptarini;
  Float_t zrec, ytarrec, delrec, yptarrec, xptarrec, xtarini, xstop, ystop, fail_id;
  //  TString fmc = Form("mc/%s.root",kin);
  TString fmc = "mc/shms_"+kin+".root";
  TFile *fm=new TFile(fmc);
  fm->Print();
  TTree *trm=(TTree*)fm->Get("h1411");

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

  //  TString fOut=Form("mcWtOut/mcWt%s.root",kin);
  TString fOut = "mcWtOut/mcWt"+kin+".root";
  TFile *out=new TFile(fOut,"RECREATE");
  TTree *tree=new TTree("tree","Monte Carlo Weighted");
  cout << "opened two more files"<<endl;
  //Copy the original mc-single-arm branchs
  tree->Branch("xfoc",&xfoc);
  tree->Branch("yfoc",&yfoc);
  tree->Branch("dxdz",&dxdz);
  tree->Branch("dydz",&dydz);
  tree->Branch("ztarini",&ztarini);
  tree->Branch("ytarini",&ytarini);
  tree->Branch("delini",&delini);
  tree->Branch("yptarini",&yptarini);
  tree->Branch("xptarini",&xptarini);
  tree->Branch("zrec",&zrec);
  tree->Branch("ytarrec",&ytarrec);
  tree->Branch("delrec",&delrec);
  tree->Branch("yptarrec",&yptarrec);
  tree->Branch("xptarrec",&xptarrec);
  tree->Branch("xtarini",&xtarini);
  tree->Branch("xstop",&xstop);
  tree->Branch("ystop",&ystop);
  tree->Branch("fail_id",&fail_id);

  Float_t born_corr, rad, rci, hstheta, sigmac, q2, w2;
  Float_t hsev, thetaini, sin2, nu, wt, xb, dt, phasespcor, phasespcorCos; 
  Int_t ngen=0;
  Int_t nacc=0;
  Float_t born=0;
  Float_t totalWt=0;
  Float_t sigave=0;
  // These will be the new branches
  tree->Branch("born",&born);
  tree->Branch("rad",&rad);
  tree->Branch("wt",&wt);
  tree->Branch("born_corr",&born_corr);
  tree->Branch("rci",&rci);
  tree->Branch("hsev",&hsev);
  tree->Branch("thetaini",&thetaini);
  tree->Branch("hstheta",&hstheta);
  tree->Branch("sigmac",&sigmac);
  tree->Branch("q2",&q2);
  tree->Branch("w2",&w2);
  tree->Branch("xb",&xb);
  tree->Branch("phaseSpaceCorr",&phasespcor);
  tree->Branch("phaseSpaceCorrCos",&phasespcorCos);

  TH1F *centralBorn=new TH1F("avgBorn","#sigma_{born}(#delta,#theta_{central) ",32,-10.,22.);
  TH1F *delWt=new TH1F("delWt","Monte Carlo Weighted delta",32,-10.,22.);
  TH1F *xpWt=new TH1F("xpWt","Monte Carlo Weighted xp_tar",50,-.1,.1);
  TH1F *ypWt=new TH1F("ypWt","Monte Carlo Weighted yp_tar",50,-.1,.1);
  TH1F *yWt=new TH1F("yWt","Monte Carlo Weighted y_tar",50,-6,6);
  TH1F *w2Wt=new TH1F("w2Wt","Monte Carlo Weighted W2",100,0,13);
  TH1F *xbWt=new TH1F("xbWt","Monte Carlo Weighted X_{B}",100,0,1);
TH1F *htemp=new TH1F("htemp","Born for event with 9<#delta<10",100,0,10);
  TH2F *thetaBorn=new TH2F("thetaBorn","Born vs thetaini;#theta (rad);born (nb/GeV/sr)",50,.25,.50,250,0,100);
  TH2F *epBorn=new TH2F("epBorn","Born vs Eprime;E' (GeV);born (nb/GeV/sr)",50,0,8,250,0,100);
  TH2F *thetaRad=new TH2F("thetaRad","Rad vs thetaini;#theta (rad);born (nb/GeV/sr)",50,.25,.50,250,0,100);
  TH2F *epRad=new TH2F("epRad","Rad vs Eprime;E' (GeV);born (nb/GeV/sr)",50,0.,8.0,250,0,100);
  sigmac = gr->Interpolate(hsec,thetacrad*180./TMath::Pi());// born
  TProfile* hp=new TProfile("hp","Profile of xB Born",100,0,1); 
  TProfile* deltaBornProf=new TProfile("deltaBornProf","Profile of delta Born",32,-10,22); 
  Int_t nEvents=trm->GetEntries();
  //      nEvents=1000;
  Int_t wtf=0;
  cout << "About to loop"<<endl;
  for (Int_t i=0; i<nEvents; i++)
    {
      //      if(i%25000==0)cout<<i<<endl;
      trm->GetEntry(i);

      //Calculate E' and apply offset
      hsev=hsec*(1. + delini/100.);

      //      hsev=hsev*(1+pOffset);
      thetaini = acos(cos(thetacrad + yptarini)*cos(xptarini));
      sin2 = sin(thetaini/2.)*sin(thetaini/2.);
      nu = ebeam -hsev;
      q2 = 4.*hsev*ebeam*sin2;
      w2= mp2 + 2.*mp*nu-q2;
      xb=q2/2./mp/nu;
      
      hstheta = acos(cos(thetacrad+yptarrec)*cos(xptarrec));
      //step 6
      born = gr->Interpolate(hsev,thetaini*180./TMath::Pi());// born
      rci = gr2->Interpolate(hsev,thetaini*180./TMath::Pi());// born/rad
      rad = gr3->Interpolate(hsev,thetaini*180./TMath::Pi());// rad
      thetaBorn->Fill(thetaini,born);
      epBorn->Fill(hsev,born);
      thetaRad->Fill(thetaini,rad);
      epRad->Fill(hsev,rad);

      hp->Fill(xb,born);
      //step 7
      dt=thetaini-thetacrad;
      phasespcorCos=1./cos(dt)/cos(dt)/cos(dt);
      phasespcor=pow(1+pow(xptarini,2)+pow(yptarini,2),1.5);
      born_corr=born/phasespcor;
      //      born=born/phasespcor;
      //step 8
	wt=0;
	//      if(i%25000==0)cout<<"hsev,thetaini,born,rci\t";

	//	if(born==0)
	//	  {
	//		wtf++;
	//		cout<<hsev<<"\t"<<thetaini*180./TMath::Pi()<<"\t"<<born<<"\t"<<rci<<"\t"<<rad<<"\t"<<wtf<<endl;
	// 	  }
 
     if(abs(xptarini)<dxp && abs(yptarini)<dyp && delini>deldown && delini<delup && born>0)
	{
	  sigave+=born;
	  ngen++;
	  wt=rad/phasespcor;
	}
      if(fail_id==0 && delrec<22. && delrec >-10.)
	{
	 	  if(abs(xptarrec)<.1 && abs(yptarrec)<.1 && abs(ytarrec)<6.0)
	  {
	    //	    w=born_corr/rci;
	    if(wt==0)
	      {
		wtf++;
		cout<<hsev<<"\t"<<thetaini*180./TMath::Pi()<<"\t"<<born<<"\t"<<rci<<"\t"<<rad<<"\t"<<wtf<<endl;
	      }
	    deltaBornProf->Fill(delrec,born);
	    delWt->Fill(delrec,wt);
	    ypWt->Fill(yptarrec,wt);
	    xpWt->Fill(xptarrec,wt);
	    yWt->Fill(ytarrec,wt);
	    w2Wt->Fill(w2,wt);
	    xbWt->Fill(xb,wt);
	    totalWt+=wt;
	    nacc++;
	    if(9.<delrec<10.)htemp->Fill(born);
	  }
	}
      tree->Fill();
    }

  for (Int_t i=0;i<32;i++){
      hsev=hsec*(1. + delini/100.);
      Float_t ene=hsec*(1. + (-9.5+i)/100.);
      born = gr->Interpolate(ene,thetacrad*180./TMath::Pi());// born
      centralBorn->Fill(-9.5+i,born);
      cout << "Delta: "<<-9.5+i<<"  born: "<<born<<endl;
  }
  TH1F *h100=(TH1F*)epBorn->ProfileX();
  TH1F *h101=(TH1F*)thetaBorn->ProfileX();
  h100->SetTitle("E' Born Profile");
  h101->SetTitle("Theta Born Profile");
  fm->Close();
  // *************************************
  ngen=1000000;
  // *************************************

  cout <<"ngen= "<<ngen<<endl;
  cout << "Integrals after filling "<<nacc<<" events, del, yp, xp, y, w2"<<endl;
  cout << setprecision(8);
  cout << "Total Wt: "<<totalWt<< endl;
  cout << delWt->Integral() << endl;
  cout << ypWt->Integral() << endl;
  cout << xpWt->Integral() << endl;
  cout << yWt->Integral() << endl;
  cout << w2Wt->Integral() << endl;
  //(.25+.15)*3.3=1.32
  //3.3*1.25=4.125
  //3.3*.85=2.805
  //3.3(1.25-.85)=1.32
  Float_t dep=(delup-deldown)/100.*hsec;
  Float_t phase_space=4.0*dxp*dyp*dep/1000.;
  Float_t lummc=1/phase_space*ngen*1000.;
  Float_t fract=lumdata*phase_space/ngen/1000.;
  cout << "dep" << "\t"<< "phase_space" << "\t"<< "fract" << endl;
  cout << dep << "\t"<< phase_space << "\t"<< fract << endl;
  cout << "Norm: "<< fract << endl;
  cout << "Charge: "<< charge/1000 << endl;

  outFile << lummc << "\t"<<charge/1000<<"\t"<<ngen <<"\t"<< nacc <<"\t"<< sigave/ngen <<"\t"<< fract/charge*1000 << "\t"<<totalWt/nacc<<"\t";

  delWt->Scale(fract/charge*1000);
  ypWt->Scale(fract/charge*1000);
  xpWt->Scale(fract/charge*1000);
  yWt->Scale(fract/charge*1000);
  w2Wt->Scale(fract/charge*1000);
  xbWt->Scale(fract/charge*1000);

  cout << "Integrals after sacling, del, yp, xp, y, w2"<<endl;
  cout << delWt->Integral() << endl;
  cout << ypWt->Integral() << endl;
  cout << xpWt->Integral() << endl;
  cout << yWt->Integral() << endl;
  cout << w2Wt->Integral() << endl;
  //  cout <<"delWt->Integral: "<< delWt->Integral() <<endl;
  cout << "MC Yield: "<<totalWt*fract/charge*1000<<endl; 
  outFile<<totalWt*fract/charge*1000<<endl; 
  delWt->Sumw2();
  centralBorn->Write();
  htemp->Write();
  delWt->Write();
  xpWt->Write();
  ypWt->Write();
  yWt->Write();
  w2Wt->Write();
  xbWt->Write();
  deltaBornProf->Write();
  thetaBorn->Write();
  epBorn->Write();
  thetaRad->Write();
  epRad->Write();
  hp->Write();
  tree->Write();
  h100->Write();
  h101->Write();
  out->Close();
  
  return;
}

