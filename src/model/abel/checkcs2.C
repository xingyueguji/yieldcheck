void checkcs2(){
  Int_t anglec=21;
  Double_t mp=0.9382727;
  Double_t mp2=mp*mp;
  Double_t angle=0.;
  Double_t e0=10.602;
  if(anglec==21)angle=21.035;
  //if(anglec==21)angle=20.995;//hms
  if(anglec==25)angle=24.98;
  if(anglec==29)angle=28.98;
  if(anglec==33)angle=32.975;
  if(anglec==39)angle=38.975;
  if(angle==0.){
    cout<<"angle fail"<<endl;
    return;
  }
  Double_t sin1=TMath::Sin(angle*TMath::Pi()/180./2.);
  Double_t sin2=sin1*sin1;

  TGraph2D *g1=new TGraph2D();
  TGraph2D *g2=new TGraph2D();
  TGraph2D *g3=new TGraph2D();
  TGraph2D *g4=new TGraph2D();
  TGraph *gr1=new TGraph();
  TGraph *gr2=new TGraph();
  TGraph *gr3=new TGraph();
  TGraph *gr4=new TGraph();

  ifstream file1;
  //file1.open(Form("externals/v0.982/h_sep/h10.6_21.0_f1f220.out"));
  file1.open(Form("externals/v0.982/externals_d_f1f220.out"));

  while(true){
    Double_t e,ep,th,x,q2,sig,d1,d2,sigrad,d3,d4,d5,d6;
    file1>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    if(file1.eof())break;
    Double_t w2=mp2+2.*mp*(e-ep)-q2;
    g1->SetPoint(g1->GetN(),w2,th,sig);
    //gr1->SetPoint(gr1->GetN(),x,sig);
  }
  file1.close();

  ifstream file2;
  //file2.open(Form("externals/v0.990/h_sep/h10.6_21.0_f1f220.out"));
  file2.open(Form("externals/v0.990/externals_d_f1f220.out"));

  while(true){
    Double_t e,ep,th,x,q2,sig,d1,d2,sigrad,d3,d4,d5,d6;
    file2>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    if(file2.eof())break;
    Double_t w2=mp2+2.*mp*(e-ep)-q2;
    g2->SetPoint(g2->GetN(),w2,th,sig);
    //gr2->SetPoint(gr2->GetN(),x,sig);
  }
  file2.close();

  ifstream file3;
  //file3.open(Form("externals/v0.995b/h_sep/h10.6_21.0_f1f221.out"));
  file3.open(Form("externals/v0.995b/externals_d_f1f221.out"));
  while(true){
    Double_t e,ep,th,x,q2,sig,d1,d2,sigrad,d3,d4,d5,d6;
    file3>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    if(file3.eof())break;
    Double_t w2=mp2+2.*mp*(e-ep)-q2;
    g3->SetPoint(g3->GetN(),w2,th,sig);
    //gr3->SetPoint(gr3->GetN(),x,sig);
  }
  file3.close();

  ifstream file4;
  file4.open(Form("externals/v0.999test/externals_d_f1f221.out"));
  while(true){
    Double_t e,ep,th,x,q2,sig,d1,d2,sigrad,d3,d4,d5,d6;
    file4>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    if(file4.eof())break;
    Double_t w2=mp2+2.*mp*(e-ep)-q2;
    g4->SetPoint(g4->GetN(),w2,th,sig);
  }
  file4.close();

  for(Int_t i=0;i<=1000;i++){
    Double_t x=0.2+0.0008*i;
    Double_t ep=mp*e0*x/(mp*x+2*e0*sin2);
    Double_t nu=e0-ep;
    Double_t q2=2.*mp*nu*x;
    Double_t w2=mp2+q2*(1./x-1.);
    gr1->SetPoint(gr1->GetN(),x,g1->Interpolate(w2,angle));
    gr2->SetPoint(gr2->GetN(),x,g2->Interpolate(w2,angle));
    gr3->SetPoint(gr3->GetN(),x,g3->Interpolate(w2,angle));
    gr4->SetPoint(gr4->GetN(),x,g4->Interpolate(w2,angle));
  }

  gr1->SetMarkerColor(kRed);
  gr2->SetMarkerColor(kBlue);
  gr3->SetMarkerColor(kGreen+1);
  gr4->SetMarkerColor(kViolet);
  gr1->SetLineColor(kRed);
  gr2->SetLineColor(kBlue);
  gr3->SetLineColor(kGreen+1);
  gr4->SetLineColor(kViolet);
  gr1->SetLineWidth(2);
  gr2->SetLineWidth(2);
  gr3->SetLineWidth(2);
  gr4->SetLineWidth(2);

  TMultiGraph *mg=new TMultiGraph();
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Add(gr4);
  mg->Draw("apl");
}
