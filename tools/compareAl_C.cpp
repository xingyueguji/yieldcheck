#include "src/getCxsec.cpp"
#include "src/getRadCorrW2.cpp"
#include "src/getRadCorrW2temp.cpp"
//double getCxsec(double angle=21.1, double x=5., string target="h", Int_t choice=1, string spec="shms"){
//TGraph2D* getRadCorrW2(string target="c", Int_t choice=1, string spec="shms"){

void compareAl_C(string target="d", int version=1, double thetac=21)
{
  TGraph2D * grc=getRadCorrW2("c",3,"shms");
  TGraph2D * gral=getRadCorrW2("alu",3,"shms","v996t2");

  Float_t delta, ratio, err, ep, modelc, modelal, xmin, xmax;
  xmin=2.7*.9;
  xmax=2.7*1.22;
  vector <float> mx;
  vector <float> myc;   
  vector <float> myal;   
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

     modelc=grc->Interpolate(w2,thetac);
     modelal=gral->Interpolate(w2,thetac);


     if(modelc!=0 && modelal!=0)
       {
	 mx.push_back(xb);
	 myc.push_back(modelc);
	 myal.push_back(modelal);

       }
   }
 Int_t pts=mx.size();
 TGraph *gal=new TGraph(pts,&mx[0],&myal[0]);
 TGraph *gc=new TGraph(pts,&mx[0],&myc[0]);
 gal->SetMarkerStyle(20);
 gal->SetMarkerSize(.5);
 gal->SetMarkerColor(kRed);
 gc->SetMarkerStyle(20);
 gc->SetMarkerSize(.5);
 gc->GetYaxis()->SetRangeUser(0,100);
 gc->Draw("ap");
 gal->Draw("sp");
 return;
}
