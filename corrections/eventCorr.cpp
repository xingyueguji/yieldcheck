
TGraphErrors* eventCorr(string spec="shms", string target="h", string angle="21",string mom="2p7", int opt=0){

  string kin=target+angle+"deg"+mom;
  cout << "The Kinematic is " << kin <<endl;
  TFile *f=new TFile(Form("../dataYieldOut/pass9/dataYield_%s.root",kin.c_str()));

  TH1D *heff;
  TH1D *hyield;
  if(opt==0)heff=(TH1D*)f->Get("heffpion");
  if(opt==1)heff=(TH1D*)f->Get("heffcal");
  if(opt==2)heff=(TH1D*)f->Get("heffcer");
  hyield=(TH1D*)f->Get("hyld");
  heff->Divide(hyield);

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
    Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
    Double_t nu= ebeam-ep;
    Double_t q2 = 4.*ep*ebeam*sin2;
    Float_t mp = .9382723;
    Double_t xb=q2/2./mp/nu;
    x.push_back(xb); 
    int bin=heff->FindBin(i+.5);
    double mean=heff->GetBinContent(bin);
    double rms=heff->GetBinError(bin);
    y.push_back(mean);
    ye.push_back(rms);
  }
  //     TGraphErrors *g=new TGraphErrors(x.size(),&x[0],&y[0],0,&ye[0]);
     TGraphErrors *g=new TGraphErrors(x.size(),&x[0],&y[0],0,0);
     //     g->SetName(kin.c_str());
     f->Close();
     return g;
 }
