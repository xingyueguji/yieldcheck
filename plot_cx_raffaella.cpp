#include "extractCS.cpp"
#include "src/formatHist.cpp"
//#include "src/getRadCorr.cpp"
//#include "src/readReport.cpp"
#include "src/getMomList.cpp"
#include "src/getCSB.cpp"
#include "src/getCJ.cpp"
#include "src/getKull.cpp"
#include "src/getKP.cpp"
#include "jmu/getJmu.cpp"

void plot_cx(string target="r", string angle="39", string spec="shms", string pass="pass105", float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3, string xaxis = "xb" ){

 Float_t delta, ratio, err, ep, model_k, modeld, modelh, xmin, xmax;
 string pset[5];
 float psetf[5];
 getMomList(angle,pset,psetf,spec);
 xmin=psetf[0]*(.9);
 xmax=psetf[3]*(1.22);
 if(spec=="hms")xmax=psetf[4]*(1.1);


  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////

 vector <float> mx;
 vector <float> my_kph;  //kp hybrid
 vector <float> my_kpd;  //kp dis 
 vector <float> my;    //CJ15
 double wmin,wmax;

 Double_t thetac=getAngle(angle,spec);
 TGraph2D *grd=getRadCorrW2("d",1,spec);  
 TGraph2D *grh=getRadCorrW2("h",1,spec);  
 for (Int_t i=0;i<1000;i++)
   {
     ep=xmin+i/1000.*(xmax-xmin);
     Double_t ebeam=10.602;
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     Double_t w2= mp*mp + 2.*mp*nu-q2;
     modeld=grd->Interpolate(w2,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(w2,thetac);  //<<"\t"<<
     if(i==0)wmax=w2+.5;
     if(i==999)wmin=w2-.1;
     if(modelh!=0 && modeld!=0){ 

       if(xaxis=="xb")mx.push_back(xb);
       if(xaxis=="w2")mx.push_back(w2);
       if(xaxis=="ep")mx.push_back(ep);

       if(target=="r")my.push_back(modeld/modelh/2.);
       if(target=="h")my.push_back(modelh);
       if(target=="d")my.push_back(modeld);
     }
   }
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);
 TGraph *gm_cj=getCJ(angle);  //at SHMS angles
 TGraph *gm_k=getKP("dis",angle);  
 TGraph *gm_k1=getKP("hybrid",angle);  
 if(xaxis=="xb") gm->GetXaxis()->SetTitle("Bjorken x");
 if(xaxis=="ep") gm->GetXaxis()->SetTitle("E' (GeV)");
 if(xaxis=="w2") gm->GetXaxis()->SetTitle("W2 (GeV^2)");
 gm->GetXaxis()->SetLimits(xbmin,xbmax);
 if(xaxis=="ep")gm->GetXaxis()->SetLimits(xmin-.1,xmax+.1);
 if(xaxis=="w2")gm->GetXaxis()->SetLimits(wmin,wmax);

 gm->SetLineColor(kBlue);
 gm_cj->SetLineColor(kRed);
 gm_k->SetLineColor(kGreen+3);
 gm_k1->SetLineColor(kOrange-6);
 
 // gm->SetLineStyle(1);
 gm_cj->SetLineStyle(2);
 gm_k->SetLineStyle(3);
 gm_k1->SetLineStyle(4);
 
 gm->SetLineWidth(2);
 gm_cj->SetLineWidth(2);
 gm_k->SetLineWidth(2);
 gm_k1->SetLineWidth(2);


 if(target=="h"){
   gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle(Form("%s Hydrogen %sdeg",spec.c_str(),angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin,cxmax);
 }
 if(target=="d"){
   gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle(Form("%s Deuterium %sdeg",spec.c_str(),angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin*2,cxmax*2);
 }
if(target=="r"){
   gm->GetYaxis()->SetTitle("#sigma_{D}/#sigma_{H} (per nucleon)");
  gm->SetTitle("");
  //  gm->SetTitle(Form("%s D/H/2 %sdeg",spec.c_str(),angle.c_str()));
  //  gm->GetYaxis()->SetRangeUser(cxmin,cxmax);
  gm->GetYaxis()->SetRangeUser(.55,cxmax);
  gm->GetYaxis()->SetTitleOffset(0.8);
 }

 gm->GetYaxis()->SetTitleSize(.055);
 gm->GetXaxis()->CenterTitle();
 gm->GetYaxis()->CenterTitle();
 gm->GetXaxis()->SetNdivisions(-508);
 // gm->GetXaxis()->SetLabelSize(0.06);// size of axis value font
 // TCanvas *c1=new TCanvas();


  gm->Draw();
  if(target=="r" && spec=="shms" && xaxis=="xb"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}


  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////
  double mrthn_x[7]={.195, .225, .255, .285, .315, .345, .375};
  double mrthn_w[7]={12.2,11.7,11.3,10.9,10.5,10.1,9.63};
  if(xaxis=="w2"){
  for(int i=0;i<7;i++)mrthn_x[i]=mrthn_w[i];
  }
  double mrthn_y[7]={1.725, 1.697, 1.674, 1.656, 1.629, 1.588, 1.544};
  double mrthn_ye[7]={.015, .014, .014, .016, .016, .016, .023};
  for(int i=0;i<7;i++)mrthn_y[i]=mrthn_y[i]/2;
  for(int i=0;i<7;i++)mrthn_ye[i]=mrthn_ye[i]/2;
  TGraphErrors *mrthn=new TGraphErrors(7,mrthn_x,mrthn_y,0,mrthn_ye);
  mrthn->SetMarkerStyle(21);
  mrthn->SetMarkerSize(1);
  mrthn->SetMarkerColor(kMagenta+2);
  /////////////////////////////////////////////////////////////////////
  TGraphErrors *grcx1=extractCS(spec,target,angle,pset[0],1,pass,xaxis);
  TGraphErrors *grcx2=extractCS(spec,target,angle,pset[1],1,pass,xaxis);
  TGraphErrors *grcx3=extractCS(spec,target,angle,pset[2],1,pass,xaxis);
  TGraphErrors *grcx4=extractCS(spec,target,angle,pset[3],1,pass,xaxis);
  TGraphErrors *grcx5;
  if(spec=="hms")grcx5=extractCS(spec,target,angle,pset[4],1,pass,xaxis);

  TGraphErrors *jmu=getJmu(target,angle,grd,grh,1);

 jmu->SetMarkerStyle(33);
 grcx1->SetMarkerStyle(27);
 grcx2->SetMarkerStyle(27);
 grcx3->SetMarkerStyle(27);
 grcx4->SetMarkerStyle(27);
 if(spec=="hms")grcx5->SetMarkerStyle(27);

 jmu->SetMarkerSize(.6);
 grcx1->SetMarkerSize(1);
 grcx2->SetMarkerSize(1);
 grcx3->SetMarkerSize(1);
 grcx4->SetMarkerSize(1);
 if(spec=="hms")grcx5->SetMarkerSize(1);

 jmu->SetMarkerColor(kBlue);
 gm->SetMarkerColor(kBlue);
 grcx1->SetMarkerColor(kBlack);
 grcx2->SetMarkerColor(kBlack);
 grcx3->SetMarkerColor(kBlack);
 grcx4->SetMarkerColor(kBlack);
 if(spec=="hms")grcx5->SetMarkerColor(kBlack);

 // jmu->Draw("sp");

 grcx1->Draw("sp");
 grcx2->Draw("sp");
 grcx3->Draw("sp");
 grcx4->Draw("sp");
 if(spec=="hms") grcx5->Draw("sp");
 mrthn->Draw("sp");
 // gm->Draw("same");

 // if(target=="r"&&spec=="shms"&&xaxis=="xb"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}

 TLegend *leg;
 if(xaxis!="w2")
   {
     leg=new TLegend(.35,.6,.65,.9);
   }
 else leg=new TLegend(.35,.6,.65,.9);
 leg->AddEntry(gm,"F1F221","l");
 if(xaxis=="xb")
   {
     leg->AddEntry(gm_k,"KP DIS","l");
     leg->AddEntry(gm_k1,"KP HYBRID","l");
     leg->AddEntry(gm_cj,"CJ15","l");
     leg->AddEntry(grcx1,"Hall C, E12-10-002","p");
     leg->AddEntry(mrthn,"Hall A, MARATHON","p");
   }
 // leg->AddEntry(grcx1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 // leg->AddEntry(grcx2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 // leg->AddEntry(grcx3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 // leg->AddEntry(grcx4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 // if(spec=="hms") leg->AddEntry(grcx5,Form("E'=%2.2f GeV/c",psetf[4]),"p");
 leg->Draw();
 /// c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
