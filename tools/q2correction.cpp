#include "src/getRadCorrW2.cpp"
double getF2w2(double x=.3){

  Double_t mp = .9382723;
  Double_t mp2 = mp*mp;
  Double_t Eb=10.602;
  Double_t theta_deg=21.035;
  Double_t theta = theta_deg*TMath::Pi()/180;
  Double_t sin2 = sin(theta/2.)*sin(theta/2.);
  Double_t num=8*mp*x*Eb*Eb*sin2;
  Double_t denom=2*mp*x+4*Eb*sin2;
  Double_t q2=num/denom;
  Double_t Ep=q2/(4*Eb*sin2);
  Double_t nu=Eb-Ep;
  Double_t w2= mp2 + 2.*mp*nu - q2;

  return w2;

}

double getFactor(double x, double q2, double w2){ 
  w2=w2*w2;
  Double_t Eb=10.59;
  Double_t Ep=3.1;
  Double_t mp = .9382723;
  Double_t mp2 = mp*mp;
  //  Double_t theta = angle*TMath::Pi()/180;
  Double_t sin2 = q2/Eb/Ep/4;
  Double_t sin1=sqrt(sin2);
  double angle=2*asin(sin1)*180/TMath::Pi();
  Double_t nu=Eb-Ep;
  //  Double_t w2= mp2 + 2.*mp*nu - q2;

  TGraph2D* gr1=getRadCorrW2("h",1,"shms");  
  TGraph2D* gr2=getRadCorrW2("d",1,"shms");  

  double cxh1 = gr1->Interpolate(w2,angle);// born
  double cxd1 = gr2->Interpolate(w2,angle);// born
  double doh1=cxd1/cxh1/2;
  cout << "W2: "<<w2<<"  Theta: "<<angle<<"  D/H: "<<doh1<<endl;
  w2=getF2w2(x);
  angle=21.035;
  double cxh2 = gr1->Interpolate(w2,angle);// born
  double cxd2 = gr2->Interpolate(w2,angle);// born
  double doh2=cxd2/cxh2/2;
  cout << "W2: "<<w2<<"  Theta: "<<angle<<"  D/H: "<<doh2<<endl<<endl;
  //  cout << doh1 << "\t" << doh2 << endl;
  double correction=doh2/doh1;
  return correction;

}

void q2correction(){
  vector <double> x;
  vector <double> y;
  y.push_back(getFactor(0.225,3.15,3.42));
  y.push_back(getFactor(0.255,3.57,3.36));
  y.push_back(getFactor(0.285,3.99,3.30));
  y.push_back(getFactor(0.315,4.41,3.24));
  y.push_back(getFactor(0.345,4.83,3.17));
  y.push_back(getFactor(0.375,5.25,3.10));

  x.push_back(.225);
  x.push_back(.255);
  x.push_back(.285);
  x.push_back(.315);
  x.push_back(.345);
  x.push_back(.375);
  TGraph *g=new TGraph(6,&x[0],&y[0]);
  g->SetTitle("Q2 Correction vs X_B");
  g->SetMarkerStyle(33);
  g->Draw("ap");
  return;
}
