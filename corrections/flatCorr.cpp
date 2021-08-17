
TGraphErrors* flatCorr(string spec="shms", string target="h", string angle="21",string mom="2p7", int opt=1){

  string kin=target+angle+"deg"+mom;
  cout << "The Kinematic is " << kin <<endl;
  TFile *f=new TFile(Form("../dataYieldOut/pass9/dataYield_%s.root",kin.c_str()));
  TTree* tr=(TTree*)f->Get("tree2");
  double trackEff, boilCorr, deadTime, psFact, scale;
  tr->SetBranchAddress("boilCorr",&boilCorr);
  tr->SetBranchAddress("deadTime",&deadTime);
  tr->SetBranchAddress("trackEff",&trackEff);
  tr->SetBranchAddress("psFact",&psFact);
  tr->SetBranchAddress("scale",&scale);
  TH1D *h=new TH1D("h","h",1000,0,20);

  for(Int_t i=0; i < tr->GetEntries(); i++){
    tr->GetEntry();
    if(opt==0)h->Fill(trackEff);
    if(opt==1)h->Fill(boilCorr);
    if(opt==2)h->Fill(1-deadTime);
    if(opt==3)h->Fill(psFact);
    if(opt==3)h->Fill(scale);
  }
  double mean=h->GetMean();
  double rms=h->GetRMS();

  vector <double> x;
  vector <double> y;
  vector <double> ye;

  double low = -10.;
  double high = 22.;

  Double_t hsec=getMom(kin,spec);
  Double_t ebeam=10.602;
  Double_t thetac=getAngle(angle,spec);

  for(int i=low; i<high; i++){
    double ep=(1+(i+.5)/100.)*hsec;
    y.push_back(mean);
    ye.push_back(rms);

    Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     x.push_back(xb); 
     cout << ep << endl;
  }
     TGraphErrors *g=new TGraphErrors(x.size(),&x[0],&y[0],0,&ye[0]);
     g->SetName(kin.c_str());
     return g;
 }
