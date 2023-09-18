#include "src/w2cut.cpp"

void angletestratio(){
TFile *data=new TFile("./ratiosOut/pass326/hms_ratiosd21deg5p1.root");
TH2F *dataYield = (TH2F*)data->Get("yieldofw2S");
dataYield->SetName("dataYield");
TH2F *mcYield = (TH2F*)data->Get("mcw2wt");
mcYield->SetName("mcYield");
TH1F *deltaratio = (TH1F*)data->Get("hrd");
deltaratio->SetName("deltaratio");

Double_t hsec = 5.1;
double offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
hsec=hsec*offset;
Double_t ebeam=10.602;
Double_t thetac = 20.995;
Double_t thetacrad=thetac*TMath::Pi()/180;
Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());    
Double_t ep,delta,nu,q2,xb,thetacsingle,sin2single,w2;
Double_t mp = .9382723;

const Int_t nbinsY = dataYield->GetNbinsY();
const Int_t nbinsX = dataYield->GetNbinsX();
const Int_t nbinsXdelta = deltaratio->GetNbinsX();

TH1F *h_deltatow2 = new TH1F("h_deltatow2","",720,-10,26);
TH1F *h_1DdataYield= new TH1F("h_1DdataYield","",720,-10,26);
TH1F *h_1DmcYield= new TH1F("h_1DmcYield","",720,-10,26);
TH1F *h_1Dw2ratio = new TH1F("h_1Dw2ratio","",720,-10,26);
for(int i=0;i<nbinsXdelta;i++){
  delta = deltaratio->GetBinCenter(i+1);
  ep=(1+delta/100)*hsec;
  nu= ebeam-ep;
	q2 = 4.*ep*ebeam*sin2;
	w2= mp*mp + 2.*mp*nu-q2;
  h_deltatow2->Fill(w2,deltaratio->GetBinContent(i+1));
}

for(int i=0;i<nbinsY;i++){
  w2 = dataYield->GetYaxis()->GetBinCenter(i+1);
  //Calculate all kin using central angle;
  double dataYieldsum = 0;
  double mcYieldsum = 0;
  for(int k=0; k<nbinsX;k++){
    dataYieldsum += dataYield->GetBinContent(k+1,i+1);
    mcYieldsum += mcYield->GetBinContent(k+1,i+1);
    if (dataYield->GetBinContent(k+1,i+1)!=0){
      //cout << dataYield->GetBinContent(k+1,i+1) << " " << mcYield->GetBinContent(k+1,i+1) << endl;
    }
  }
  if (w2cut("hms","21","5p1",w2)){
    cout << w2 << " is Good " << endl; 
    h_1DdataYield->Fill(w2,dataYieldsum);
    h_1DmcYield->Fill(w2,mcYieldsum);    
  }
}
for(int i=0; i<720; i++){
  double hist2content = h_1DmcYield->GetBinContent(i+1);
  if (hist2content!=0){
    double hist1content = h_1DdataYield->GetBinContent(i+1);
    double ratio = hist1content / hist2content;
    h_1Dw2ratio->SetBinContent(i,ratio);
    if (ratio >= 1){
      cout << "W2 value is " << h_1Dw2ratio->GetBinCenter(i+1) << " Ratio value is" << ratio << endl;
    }
  }
}

//data->Close();
TCanvas *c1 = new TCanvas("c1","",3200,3200);
c1->Divide(2,1);
gStyle->SetOptFit(1);
c1->cd(1);
h_deltatow2->GetYaxis()->SetRangeUser(0.1,1.1);
h_deltatow2->GetXaxis()->SetRangeUser(2.5,5);
h_deltatow2->Fit("pol1");
h_deltatow2->Draw();
c1->cd(2);
h_1Dw2ratio->GetYaxis()->SetRangeUser(0.1,1.1); 
h_1Dw2ratio->GetXaxis()->SetRangeUser(2.5,5); 
h_1Dw2ratio->Draw();
h_1Dw2ratio->Fit("pol1");





// need to figure out why xb < 0 ? 
// sum before take ratio






return;
}

