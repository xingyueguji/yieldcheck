#include "src/getKineUnc.cpp"
#include "src/readReport.cpp"
#include "src/getRadCorrW2.cpp"

TGraphErrors* testKin(string spec="shms",double thetac =21.035, double hsec=5.1){
  vector <double>x,y;

  TGraph2D *grh=getRadCorrW2("h",3,spec);
  grh->SetName("grh");
  TGraph2D *grd=getRadCorrW2("d",3,spec);
  grd->SetName("grd");
  
  double delta1=-10;
  double delta2=22;
    for(double i=delta1+0.5; i<=delta2; i++){
      double center = i;
      double eprime=hsec*(1+center/100.);
      //      double val=getKineUnc(gr1, eprime, thetac);
      //	  if(!TMath::IsNaN(val))herrKin->Fill(center,val*weight);
      double val=getKineUncRatio(grh, grd, eprime, thetac);
      double thetacrad=thetac/180.*TMath::Pi();
      double mp = .9382723;
      double mp2 = mp*mp;
      double sin2 = sin(thetacrad/2.)*sin(thetacrad/2.);
      double nu = 10.602 - eprime;
      double q2 = 4.*eprime*10.602*sin2;
      double xb=q2/2./mp/nu;

      if(!TMath::IsNaN(val) &&xb > 0.75 && xb< 0.925){
	y.push_back(val);
	x.push_back(xb);
      }
      cout << "eprime: "<<eprime<<"   theta:"<<thetac<<"   unc: "<<val << endl;
    }
    TGraphErrors *g=new TGraphErrors(x.size(),&x[0],&y[0],0,0);


    return g;
}
