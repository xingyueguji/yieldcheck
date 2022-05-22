
void w2cutTest(){

  TH1F *w2Wt=new TH1F("w2Wt","Monte Carlo Weighted W2",375,-10,20);

  Double_t mp = .9382723;
  Double_t mp2 = mp*mp;
  Double_t ebeam=10.602;

  int nbins=w2Wt->GetNbinsX();
  for(int i=0;i<nbins;i++)
      //  int i=180;
    {
  Double_t w2=w2Wt->GetBinCenter(i);
  Double_t width=w2Wt->GetBinWidth(i);
  Double_t w2_min=w2-width/2;
  Double_t w2_max=w2+width/2;
  Double_t hsec=5.1;
  Double_t ep_min=hsec*.9;
  Double_t ep_max=hsec*1.22;
  ep_min=5.1;
  ep_max=5.7;
  Double_t theta_min=2*asin(sqrt((-w2_min+mp2+2*mp*(ebeam-ep_max))/(4*ebeam*ep_max)));
  Double_t theta_max=2*asin(sqrt((-w2_max+mp2+2*mp*(ebeam-ep_min))/(4*ebeam*ep_min)));
  //  cout << w2_min <<"\t"<< w2_max <<"\t"<< ep_min <<"\t"<< ep_max << endl;
  cout << "w2: "<<w2<<"\t";
  cout << "Theta min: "<<theta_min<<"\t Theta Max: "<<theta_max<<"\t Difference: "<<theta_max-theta_min<<endl;
  }

  return;
}
