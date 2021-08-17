k#include "getKull.cpp"
#include "getCJ.cpp"
#include "getAngle.cpp"

void plot_cx(string angle="21",string spec="shms"){

  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////

 vector <float> mx;
 vector <float> my;
 vector <float> mcj; 
 Float_t model,modelcj,  xmin, xmax, ep;
 xmin=1.;
 xmax=5.;
 Double_t thetac=25.;//getAngle(angle,"shms");

 TGraph2D *gr=getKull(1);  
 TGraph *gmcj=getCJ(1);  
 for (Int_t i=0;i<1000;i++)
   {
     //     ep=2.2+i/1000.*3.8;
     ep=xmin+i/1000.*(xmax-xmin);
     Double_t ebeam=10.602;
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     model=gr->Interpolate(xb,q2);  //<<"\t"<<
     mx.push_back(xb);
     my.push_back(model);

   }
 TCanvas *c1=new TCanvas();
 //  c1->Divide(2,1);
 // c1->cd(1);
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);

 gm->GetXaxis()->SetTitle("Bjorken X");
 gm->SetLineColor(kBlack);
 gmcj->SetLineColor(kRed); 
 gm->Draw();
 // c1->cd(2);
 gmcj->Draw("same"); 

  return;
}
