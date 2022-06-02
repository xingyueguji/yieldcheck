#include "extractCS.cpp"
#include "src/formatHist.cpp"
//#include "src/readReport.cpp"
#include "src/getMomList.cpp"
#include "src/getCSB.cpp"
#include "src/getCJ.cpp"
#include "src/getKull.cpp"
#include "src/getKP.cpp"
#include "jmu/getJmu.cpp"

void plot_ratioOnly(string target="r", string angle="25", string spec="shms",float xbmin=0.2, float xbmax=1.0, float cxmin=0.0, float cxmax = 3.0, float ratiomin = 0.5, float ratiomax =1.2 ){

 string pset[4];
 float psetf[4];
 getMomList(angle,pset,psetf);
  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////

 vector <float> mx;
 vector <float> my_kph;  //kp hybrid
 vector <float> my_kpd;  //kp dis 
 vector <float> my;    //CJ15
 Float_t delta, ratio, err, ep, model_k, modeld, modelh, xmin, xmax;
 xmin=psetf[0]*(.9);
 xmax=psetf[3]*(1.22);

 Double_t thetac=getAngle(angle,spec);
 TGraph2D *grd=getRadCorrW2("d",1);  
 TGraph2D *grh=getRadCorrW2("h",1);  
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
     if(modelh!=0 && modeld!=0){ 
       mx.push_back(xb);
       if(target=="r")my.push_back(modeld/modelh/2.);
       if(target=="h")my.push_back(modelh);
       if(target=="d")my.push_back(modeld);
     }
   }
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);
 TGraph *gm_cj=getCJ(angle);  
 TGraph *gm_k=getKP("dis",angle);  
 TGraph *gm_k1=getKP("hybrid",angle);  

 gm->GetXaxis()->SetTitle("Bjorken X");
 gm->GetXaxis()->SetLimits(xbmin,xbmax);

 gm->SetLineColor(kBlack);
 gm_cj->SetLineColor(kRed);
 gm_k->SetLineColor(kGreen+3);
 gm_k1->SetLineColor(kBlue+1);
 
 gm->SetLineStyle(1);
 gm_cj->SetLineStyle(2);
 gm_k->SetLineStyle(3);
 gm_k1->SetLineStyle(4);
 
 gm->SetLineWidth(2);
 gm_cj->SetLineWidth(2);
 gm_k->SetLineWidth(2);
 gm_k1->SetLineWidth(2);


 if(target=="h"){
   gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle(Form("SHMS Hydrogen %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin,cxmax);
 }
 if(target=="d"){
   gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle(Form("SHMS Deuterium %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin*2,cxmax*2);
 }
if(target=="r"){
  gm->SetTitle(Form("SHMS: %s#circ",angle.c_str()));
  gm->GetYaxis()->SetTitle("#sigma_{D} / #sigma_{H} (per nucleon)");
  //  gm->GetYaxis()->SetRangeUser(0.5,1.5);
  gm->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
 }

// gm->GetYaxis()->SetTitleSize(.035);
 gm->GetXaxis()->CenterTitle();
 gm->GetYaxis()->CenterTitle();
 gm->GetXaxis()->SetNdivisions(-5);
 // gm->GetXaxis()->SetLabelSize(0.06);// size of axis value font
  TCanvas *c1=new TCanvas();
 // c1->SetFillColor(0);
  gm->Draw("ac");
  if(target=="r"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}
  if(target=="r"){gm_k->Draw("same");gm_k1->Draw("same");}


  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////

 TGraphErrors *grcx1=extractCS("shms",target,angle,pset[0],1);
 TGraphErrors *grcx2=extractCS("shms",target,angle,pset[1],1);
 TGraphErrors *grcx3=extractCS("shms",target,angle,pset[2],1);
 TGraphErrors *grcx4=extractCS("shms",target,angle,pset[3],1);

 TGraphErrors *jmu=getJmu(target,angle,grd,grh,1);

 jmu->SetMarkerStyle(33);
 grcx1->SetMarkerStyle(33);
 grcx2->SetMarkerStyle(33);
 grcx3->SetMarkerStyle(33);
 grcx4->SetMarkerStyle(33);

 jmu->SetMarkerSize(1.4);
 grcx1->SetMarkerSize(1.4);
 grcx2->SetMarkerSize(1.4);
 grcx3->SetMarkerSize(1.4);
 grcx4->SetMarkerSize(1.4);

 jmu->SetMarkerColor(kBlack);
 grcx1->SetMarkerColor(kRed);
 // grcx2->SetMarkerColor(kOrange);
 grcx2->SetMarkerColor(kBlack);
 grcx3->SetMarkerColor(kGreen+3);
 grcx4->SetMarkerColor(kViolet);

 // jmu->Draw("sp");

 grcx1->Draw("sp");
 grcx2->Draw("sp");
 grcx3->Draw("sp");
 grcx4->Draw("sp");


 gm->Draw("sc");
  if(target=="r"){gm_k->Draw("same");gm_k1->Draw("same");}
  if(target=="r"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}
 TGraphErrors *gr1=extractCS("shms",target,angle,pset[0],0);
 TGraphErrors *gr2=extractCS("shms",target,angle,pset[1],0);
 TGraphErrors *gr3=extractCS("shms",target,angle,pset[2],0);
 TGraphErrors *gr4=extractCS("shms",target,angle,pset[3],0);
 TGraphErrors *jmur=getJmu(target,angle,grd,grh,0);

 //gStyle->SetTitleFontSize(.1);
 gr1->GetXaxis()->SetTitle("Bjorken X");
 gr1->GetXaxis()->SetTitleSize(.06);
 gr1->GetXaxis()->CenterTitle();
gr1->SetTitle("Data/F1F220");
gr1->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
//gr1->GetXaxis()->SetRangeUser(xbmin,xbmax);
 gr1->GetXaxis()->SetLimits(xbmin,xbmax);
  gr1->GetXaxis()->SetLabelSize(.06);
  gr1->GetYaxis()->SetLabelSize(.06);
 gr1->GetXaxis()->SetNdivisions(-5);
 // gr1->GetYaxis()->SetNdivisions(5);
 jmur->SetMarkerStyle(33);
 gr1->SetMarkerStyle(33);
 gr2->SetMarkerStyle(33);
 gr3->SetMarkerStyle(33);
 gr4->SetMarkerStyle(33);

 jmur->SetMarkerSize(.9);
 gr1->SetMarkerSize(.9);
 gr2->SetMarkerSize(.9);
 gr3->SetMarkerSize(.9);
 gr4->SetMarkerSize(.9);

 jmur->SetMarkerColor(kBlack);
 gr1->SetMarkerColor(kRed);
 // gr2->SetMarkerColor(kOrange);
 gr2->SetMarkerColor(kBlack);
 gr3->SetMarkerColor(kGreen+3);
 gr4->SetMarkerColor(kViolet);

 TLegend *leg=new TLegend(.35,.5,.65,.85);
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(gm_k,"KP DIS","l");
 leg->AddEntry(gm_k1,"KP HYBRID","l");
 leg->AddEntry(gm_cj,"CJ15","l");
 leg->AddEntry(grcx1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(grcx2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(grcx3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(grcx4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 grcx1->Draw("sp");
 grcx2->Draw("sp");
 grcx3->Draw("sp");
 grcx4->Draw("sp");
 // leg->AddEntry(jmu,"JMU","p");

 if(target=="r") leg->Draw();
  c1->SaveAs(Form("ratios%s.pdf",angle.c_str()));
  return;
}
