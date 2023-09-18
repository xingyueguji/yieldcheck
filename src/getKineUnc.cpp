
using namespace std;

double getW2(double ebeam, double hsec, double thetacrad){
double mp = .9382723;
double mp2 = mp*mp;
double sin2 = sin(thetacrad/2.)*sin(thetacrad/2.);
double nu = ebeam - hsec;
double q2 = 4.*hsec*ebeam*sin2;
double w2= mp2 + 2.*mp*nu-q2;
return w2;
}

double getXb(double ebeam, double hsec, double thetacrad){
double mp = .9382723;
double mp2 = mp*mp;
double sin2 = sin(thetacrad/2.)*sin(thetacrad/2.);
double nu = ebeam - hsec;
double q2 = 4.*hsec*ebeam*sin2;
double w2= mp2 + 2.*mp*nu-q2;
return q2/2/mp/nu;
}

double getKineUncRatio(TGraph2D*grh, TGraph2D *grd, double mom, double angle){
  double uncT,uncTdeg, uncB, uncP;
  angle=abs(angle);
  uncT=0.25/1000.;//mr
  uncTdeg=uncT*180./TMath::Pi();
  uncB=.001;//fractional
  uncP=.001;//fractional
  double cx_nom, cx_plus,cx_minus,w2,avg;
  
  double tunc=0;
  double ebeam=10.602;
  double thetacrad=angle/180.*TMath::Pi();
  
  w2=getW2(ebeam, mom, thetacrad);
  cx_nom=grd->Interpolate(w2,angle)/grh->Interpolate(w2,angle);
  // +/- Theta

  w2=getW2(ebeam, mom, thetacrad+uncT);
  cx_plus=grd->Interpolate(w2,angle+uncTdeg)/grh->Interpolate(w2,angle+uncTdeg);

  w2=getW2(ebeam, mom, thetacrad-uncT);
  cx_minus=grd->Interpolate(w2,angle-uncTdeg)/grh->Interpolate(w2,angle-uncTdeg);

  cout << cx_nom <<"\t"<<cx_plus <<"\t"<<cx_minus <<endl;
  avg=1./2./cx_nom*(abs(cx_plus-cx_nom)+abs(cx_minus-cx_nom));
  cout << "The average uncertainity from +/- theta is "<<avg<<endl; 
  tunc+=pow(avg,2);
  // +/- ebeam

  w2=getW2(ebeam*(1.+uncB), mom, thetacrad);
  cx_plus=grd->Interpolate(w2,angle)/grh->Interpolate(w2,angle);
  w2=getW2(ebeam*(1.-uncB), mom, thetacrad);
  cx_minus=grd->Interpolate(w2,angle)/grh->Interpolate(w2,angle);
  avg=1./2./cx_nom*(abs(cx_plus-cx_nom)+abs(cx_minus-cx_nom));
  cout << "The average uncertainity from +/- ebeam is "<<avg<<endl; 
  tunc+=pow(avg,2);
  // +/- Theta
  w2=getW2(ebeam, mom*(1.+uncP), thetacrad);
  cx_plus=grd->Interpolate(w2,angle)/grh->Interpolate(w2,angle);
  w2=getW2(ebeam, mom*(1-uncP), thetacrad);
  cx_minus=grd->Interpolate(w2,angle)/grh->Interpolate(w2,angle);
  avg=1./2./cx_nom*(abs(cx_plus-cx_nom)+abs(cx_minus-cx_nom));
  cout << "The average uncertainity from +/- mom is "<<avg<<endl; 
  tunc+=pow(avg,2);
  tunc=sqrt(tunc);
  cout << "The total uncertainity is "<<tunc<<endl; 
  
  return tunc;
}

double getKineUnc(TGraph2D *gr, double mom, double angle){
  double uncT,uncTdeg, uncB, uncP;
  uncT=0.25/1000.;//mr
  uncTdeg=uncT*180./TMath::Pi();
  uncB=.001;//fractional
  uncP=.001;//fractional
  double cx_nom, cx_plus,cx_minus,w2,avg;
  
  double tunc=0;
  double ebeam=10.602;
  double thetacrad=angle/180.*TMath::Pi();
  
  w2=getW2(ebeam, mom, thetacrad);
  cx_nom=gr->Interpolate(w2,angle);
  // +/- Theta

  w2=getW2(ebeam, mom, thetacrad+uncT);
  cx_plus=gr->Interpolate(w2,angle+uncTdeg);

  w2=getW2(ebeam, mom, thetacrad-uncT);
  cx_minus=gr->Interpolate(w2,angle-uncTdeg);

  cout << cx_nom <<"\t"<<cx_plus <<"\t"<<cx_minus <<endl;
  avg=1./2./cx_nom*(abs(cx_plus-cx_nom)+abs(cx_minus-cx_nom));
  cout << "The average uncertainity from +/- theta is "<<avg<<endl; 
  tunc+=pow(avg,2);
  // +/- ebeam
  w2=getW2(ebeam*(1.+uncB), mom, thetacrad);
  cx_plus=gr->Interpolate(w2,angle);
  w2=getW2(ebeam*(1.-uncB), mom, thetacrad);
  cx_minus=gr->Interpolate(w2,angle);
  avg=1./2./cx_nom*(abs(cx_plus-cx_nom)+abs(cx_minus-cx_nom));
  cout << "The average uncertainity from +/- ebeam is "<<avg<<endl; 
  tunc+=pow(avg,2);
  // +/- Theta
  w2=getW2(ebeam, mom*(1.+uncP), thetacrad);
  cx_plus=gr->Interpolate(w2,angle);
  w2=getW2(ebeam, mom*(1-uncP), thetacrad);
  cx_minus=gr->Interpolate(w2,angle);
  avg=1./2./cx_nom*(abs(cx_plus-cx_nom)+abs(cx_minus-cx_nom));
  cout << "The average uncertainity from +/- mom is "<<avg<<endl; 
  tunc+=pow(avg,2);
  tunc=sqrt(tunc);
  cout << "The total uncertainity is "<<tunc<<endl; 
  
  return tunc;
}
