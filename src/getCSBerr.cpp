
double getCSBerr(double theta=21., double pc=3.3, double delta=-5, double target=1.01, int what=0, TGraph2D *gr1=0)
{
  double thetaini=theta*TMath::Pi()/180.;
  Double_t mp = .9382723;
  Double_t mp2 = mp*mp;

  string tgt;
  if(abs(target - 1.) < .2)tgt="h";
  if(abs(target - 2.) < .2)tgt="d";
  if(abs(target - 12.) < .2)tgt="c";

  double ebeam=10.602;
  double hsev=pc*(1+delta/100.);
  double csb_cx=0;
  Double_t p0=-2.09 * thetaini*180./TMath::Pi() +12.47;
  Double_t p1=0.2 * thetaini*180./TMath::Pi() -0.6338;
  csb_cx=exp(p0)*(exp(p1*(ebeam-hsev))-1.);
  if(tgt=="d")csb_cx=2*csb_cx;
  if(tgt=="c")csb_cx=12*csb_cx*19.32/((890.4+769.1)/2); //need to add. (use rad length)

  double  sin2 = sin(thetaini/2.)*sin(thetaini/2.);
  double  nu = ebeam - hsev;
  double  q2 = 4.*hsev*ebeam*sin2;
  double  w2= mp2 + 2.*mp*nu - q2;
  double rad = gr1->Interpolate(w2,thetaini*180./TMath::Pi());// rad
  //  cout << csb_cx<<"\t"<<rad<<endl;

  double sizeOfCorrection=csb_cx/(rad+csb_cx);
  double errorOnCorrection=csb_cx/(rad+csb_cx)*.03;

  double result=errorOnCorrection;
  if(what!=0)result=sizeOfCorrection;
  return result;
}
