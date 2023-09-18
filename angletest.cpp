void angletest(){
TFile *data = new TFile("./dataYieldOut/pass70/hms_dataYield_d21deg5p1.root");
TH2F *yield4acc = (TH2F*)data->Get("yield4acc");


Double_t hsec = 5.1;
double offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
hsec=hsec*offset;
Double_t ebeam=10.602;
Double_t thetac = 20.995;
Double_t thetacrad=thetac*TMath::Pi()/180;
Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());    
Double_t ep,delta,nu,q2,xb,thetacsingle,sin2single;
Double_t mp = .9382723;

const Int_t nbinsY = yield4acc->GetNbinsY();
const Int_t nbinsX = yield4acc->GetNbinsX();

TH1D *h_singlebin = new TH1D("h_singlebin","",120,0,3);
TH1D *h_central = new TH1D("h_central","",120,0,3);

for(int i=0;i<nbinsY;i++){
  delta = yield4acc->GetYaxis()->GetBinCenter(i+1);
  //Calculate all kin using central angle;
  ep=(1+delta/100)*hsec;
  nu= ebeam-ep;
  q2 = 4.*ep*ebeam*sin2;
  xb=q2/2./mp/nu;
  Double_t combinedY = 0;
  Double_t combinedYforsingle = 0;

  for (int k=0;k<nbinsX;k++){

    combinedY += yield4acc->GetBinContent(k+1,i+1);
  }
  h_central->Fill(xb,combinedY); // combined Y bins and fill;
  cout << "For the" << i << " Y bin, the xb value for central angle is " << xb << endl;
  for (int j=0;j<nbinsX;j++){


    Double_t bincentralangle = yield4acc->GetXaxis()->GetBinCenter(j+1);
    thetacsingle = (bincentralangle/1000)+thetacrad; // change mrad to rad and + central angle
    sin2single = sin(thetacsingle/2)*sin(thetacsingle/2);
    q2 = 4.*ep*ebeam*sin2single;
    xb = q2/2./mp/nu;
    combinedYforsingle += yield4acc->GetBinContent(j+1,i+1);
    h_singlebin->Fill(xb,yield4acc->GetBinContent(j+1,i+1)); // fill single bin along Y direction using angle from single bin;
    cout << "For the " << i << " Y bin, the " << j << " X bin has xb of " << xb << endl;
  }
}
//data->Close();
TCanvas *c1 = new TCanvas("c1","",1600,800);
c1->Divide(2,1);
c1->cd(1);
h_central->Draw();
c1->cd(2);
h_singlebin->Draw();









return;
}

