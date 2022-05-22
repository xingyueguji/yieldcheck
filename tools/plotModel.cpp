#include "src/getCxsec.cpp"
#include "src/getRadCorrW2.cpp"
#include "src/getRadCorrW2temp.cpp"
//double getCxsec(double angle=21.1, double x=5., string target="h", Int_t choice=1, string spec="shms"){
//TGraph2D* getRadCorrW2(string target="c", Int_t choice=1, string spec="shms"){

TGraph* plotModel(string target="d", string version="v996t2", double thetac=21)
{
  //  TGraph2D * grh=getRadCorrW2("h",1,"shms","v0.995");
  //  TGraph2D * grd=getRadCorrW2("d",1,"shms","v0.995");
  TGraph2D * gr=getRadCorrW2(target.c_str(),1,"shms",version.c_str());
 

  Float_t delta, ratio, err, ep, model, xmin, xmax;
  xmin=2.7*.9;
  xmax=5.1*1.22;
  vector <float> mx;
  vector <float> my;   
  for (Int_t i=0;i<1000;i++)
   {
     cout <<i<<endl;
     ep=xmin+i/1000.*(xmax-xmin);
     Double_t ebeam=10.602;
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     Double_t w2= mp*mp + 2.*mp*nu-q2;

     model=gr->Interpolate(w2,thetac);

     if(model!=0)
       {
	 mx.push_back(w2);
	 my.push_back(model);
       }
   }
  Int_t pts=mx.size();
  TGraph *gm=new TGraph(pts,&mx[0],&my[0]);
  gm->SetMarkerStyle(20);
  gm->SetMarkerSize(.5);
  return gm;
}
