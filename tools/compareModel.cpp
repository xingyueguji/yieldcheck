#include "src/getCxsec.cpp"
#include "src/getRadCorrW2.cpp"
#include "src/getRadCorrW2temp.cpp"
//double getCxsec(double angle=21.1, double x=5., string target="h", Int_t choice=1, string spec="shms"){
//TGraph2D* getRadCorrW2(string target="c", Int_t choice=1, string spec="shms"){

TGraph* compareModel(string target="d", double thetac=21)
{
  TGraph2D * grh=getRadCorrW2("h",1,"shms","v0.995");
  TGraph2D * grd=getRadCorrW2("d",1,"shms","v0.995");
  TGraph2D * grh2=getRadCorrW2("h",1,"shms","v996t2");
  TGraph2D * grd2=getRadCorrW2("d",1,"shms","v996t2");

  Float_t delta, ratio, err, ep, modeld, modelh, xmin, xmax, modelh2, modeld2;
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

     modelh=grh->Interpolate(w2,thetac);
     modeld=grd->Interpolate(w2,thetac);
     modelh2=grh2->Interpolate(w2,thetac);
     modeld2=grd2->Interpolate(w2,thetac);
     
     modelh=modelh/modelh2;
     modeld=modeld/modeld2;


     if(modelh!=0 && modeld!=0 && w2 > 1.2)
       {
     mx.push_back(xb);
     if(target=="h")my.push_back(modelh);
     if(target=="d")my.push_back(modeld);
     if(target=="r")my.push_back(modeld/modelh);
       }
   }
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);
 gm->SetMarkerStyle(20);
 gm->SetMarkerSize(.5);
 gm->GetXaxis()->SetTitle("x_b");
 gm->GetYaxis()->SetTitle("v0.995 / v0.996t2");
 if(target=="h")gm->SetMarkerColor(kRed);
 if(target=="d")gm->SetMarkerColor(kBlue);
 return gm;
}
