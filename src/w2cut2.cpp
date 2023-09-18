//#include "getMom.cpp"

using namespace std;

//  Weights mc-single-arm output with a given model

bool w2cut(string spec="hms",string angle="21", string mom="3p3", Double_t center=10.0, Double_t binWidth=.04,TFile* fm=0){
  Double_t w2min=center-binWidth/2;
  Double_t w2max=center+binWidth/2;
  cout <<"w2min/max"<<w2min<<"\t"<<w2max<<endl;
  string kin="h"+angle+"deg"+mom;
  cout <<" The Kinematic is " << kin<<endl;
  Double_t mp = .9382723;
  Double_t mp2 = mp*mp;
  Double_t dxp, dyp, delup, deldown, delCutHi, delCutLo, xpCut, ypCut, yCut,thetacrad;
  Double_t target, ebeam, hsec, thetac, tgtDenLen, tgtMass, offset,beamTheta;
  Double_t charge=0;
  if(spec=="shms")
    {
      dxp=60;//phi in MC xp_tar
      dyp=65;
      delup=25;
      deldown=-15;
      //match data cuts
      delCutLo = -10.;
      delCutHi = +22.;
      xpCut= 0.10;
      ypCut= 0.10;
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
  if(spec=="hms"&&hsec<5.5){  
    offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
    hsec=hsec*offset;
  }
  //  hsec=hsec*(1.-0.001);
  //  cout << "The central momentum is "<<hsec<<endl;
  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21"&&spec=="shms")thetac=21.035;
  if(angle=="21"&&spec=="hms")thetac=20.995;

  //  cout << "The central angle is "<<thetac<<endl;
  if(angle=="59")thetac=58.98;
  ////****  Beam is not along z ******
  //  cout << "Correcting central angle for beam angle"<<endl;
  //  cout << "Before: "<<thetac<<endl;
  beamTheta=0.00045;//-0.00025; //shooting beam right .45mr
  if(spec=="hms")beamTheta*=-1;
  thetac+=beamTheta*180./TMath::Pi();
  //  cout << "After: "<<thetac<<endl;

  thetacrad=thetac*TMath::Pi()/180;
  Float_t born_corr, rad, rci, hstheta, sigmac, q2, w2, csb_cx;
  Float_t hse, hsev, thetaini, sin2, nu, wt, xb, dt, phasespcor, phasespcorCos; 
  Float_t xfoc, yfoc, dxdz, dydz, ztarini, ytarini, delini, xptarini, yptarini;
  Float_t zrec, ytarrec, delrec, yptarrec, xptarrec, xtarini, xstop, ystop, fail_id;
  //  TString fmc = "../mc/casey/"+spec+"_mc_"+kin+".root";
  //  fm=new TFile(fmc);
  //fm->Print();
  TTree *trm;
  string arm;
  if(spec=="shms"){
    
      trm=(TTree*)fm->Get("h1411");
      arm="p";
    }
  if(spec=="hms")
    {
      trm=(TTree*)fm->Get("h1");
      arm="h";
    }

  //  cout << "The MC files has "<<trm->GetEntries()<< " entries"<< endl;

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


  TH1F *ypWt=new TH1F("ypWt","Monte Carlo Weighted yp_tar",100,-.1,.1);

  Int_t nEvents=trm->GetEntries();
  nEvents=1000000;
  Int_t wtf=0;
  cout << "About to loop"<<endl;

  for (Int_t i=0; i<nEvents; i++)
    {
      if(i%250000==0)cout<<i<<endl;
      trm->GetEntry(i);
      //Calculate E' and apply offset
      hsev=hsec*(1. + delini/100.);
      hse=hsec*(1. + delrec/100.);
      //Calculate theta
      if(spec=="shms"){
	thetaini = acos(cos(thetacrad + yptarini)*cos(xptarini));
	hstheta = acos(cos(thetacrad + yptarrec)*cos(xptarrec));
      }
      if(spec=="hms"){
	thetaini = acos(cos(thetacrad - yptarini)*cos(xptarini));
	hstheta = acos(cos(thetacrad - yptarrec)*cos(xptarrec));
      }
      //call cross sections with initial quantities
      sin2 = sin(thetaini/2.)*sin(thetaini/2.);
      nu = ebeam - hsev;
      q2 = 4.*hsev*ebeam*sin2;
      w2= mp2 + 2.*mp*nu - q2;
      xb=q2/2./mp/nu;

      if(fail_id==0 && delrec<delCutHi && delrec >delCutLo)
	{
	  //	  cout <<w2<<"\t"<<w2min<<"\t"<<w2max<<"\t"<<yptarini<<endl;
	  if(w2>w2min && w2<w2max){
	    ypWt->Fill(yptarini);
	  }
	}
	  //	  if(abs(xptarrec)<xpCut && abs(yptarrec)<ypCut && abs(ytarrec-1.5)<0.5)
    }
  Int_t nbins=ypWt->GetNbinsX();
  Double_t min=100000;
  Double_t max=-1;
  Double_t last=0;
  Double_t content=0;

  for(int i=0; i< nbins; i++){
    content=ypWt->GetBinContent(i);
    min=ypWt->GetBinCenter(i);
    if(content!=0)break;
  }

  for(int i=nbins; i>0; i--){
    content=ypWt->GetBinContent(i);
    max=ypWt->GetBinCenter(i);
    if(content!=0)break;
  }

  cout << "Min: "<<min<<"    Max: "<<max<<endl;
  ypWt->Draw();
  Double_t diff=max-min;
  cout << "Range:  "<<diff<<endl;
  bool good=true;
  if(diff<.04)good=false;
  if(spec=="hms" && diff<.03)good=false; 
  //  delete ypWt;
  return good;
}
