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

void plot_dataMc(string target="h", string angle="21", string spec="hms", string pass="pass106", float xbmin=0.25, float xbmax=1.0, float cxmin=0.0, float cxmax = 3.0, float ratiomin = 0.7, float ratiomax =1.3 ){

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
 
 // gm->SetLineStyle(1);
 gm_cj->SetLineStyle(2);
 gm_k->SetLineStyle(3);
 gm_k1->SetLineStyle(4);
 
 gm->SetLineWidth(1);
 gm_cj->SetLineWidth(1);
 gm_k->SetLineWidth(1);
 gm_k1->SetLineWidth(1);


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
  gm->SetTitle(Form("%s D/H/2 %sdeg",spec.c_str(),angle.c_str()));
  gm->GetYaxis()->SetRangeUser(0.5,1.6);
 }

 gm->GetYaxis()->SetTitleSize(.055);
 gm->GetXaxis()->CenterTitle();
 gm->GetYaxis()->CenterTitle();
 gm->GetXaxis()->SetNdivisions(-5);
 // gm->GetXaxis()->SetLabelSize(0.06);// size of axis value font
 // TCanvas *c1=new TCanvas();

 TGraphErrors *gr1=extractCS(spec.c_str(),target,angle,pset[0],0,pass);
 TGraphErrors *gr2=extractCS(spec.c_str(),target,angle,pset[1],0,pass);
 TGraphErrors *gr3=extractCS(spec.c_str(),target,angle,pset[2],0,pass);
 TGraphErrors *gr4=extractCS(spec.c_str(),target,angle,pset[3],0,pass);
 TGraphErrors *gr5;
 if(spec=="hms")gr5=extractCS(spec.c_str(),target,angle,pset[4],0,pass);
 TGraphErrors *jmur=getJmu(target,angle,grd,grh,0);

 //gStyle->SetTitleFontSize(.1);
 gr1->GetXaxis()->SetTitle("Bjorken X");
 gr1->GetXaxis()->SetTitleSize(.05);
 gr1->GetXaxis()->SetTitleOffset(.6);
 gr1->GetXaxis()->CenterTitle();
 string tit="Hydrogen";
 if(target=="d")tit="Deuterium";
 gr1->SetTitle(Form("Data/MC %s",tit.c_str()));
gr1->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
//gr1->GetXaxis()->SetRangeUser(xbmin,xbmax);
 gr1->GetXaxis()->SetLimits(xbmin,xbmax);
  gr1->GetXaxis()->SetLabelSize(.04);
  gr1->GetYaxis()->SetLabelSize(.06);
 gr1->GetXaxis()->SetNdivisions(-5);
 // gr1->GetYaxis()->SetNdivisions(5);
 jmur->SetMarkerStyle(33);
 gr1->SetMarkerStyle(33);
 gr2->SetMarkerStyle(33);
 gr3->SetMarkerStyle(33);
 gr4->SetMarkerStyle(33);
 gr5->SetMarkerStyle(33);

 jmur->SetMarkerSize(.8);
 gr1->SetMarkerSize(.8);
 gr2->SetMarkerSize(.8);
 gr3->SetMarkerSize(.8);
 gr4->SetMarkerSize(.8);
 gr5->SetMarkerSize(.8);

 jmur->SetMarkerColor(kBlack);
 gr1->SetMarkerColor(kRed);
 gr2->SetMarkerColor(kMagenta);
 gr3->SetMarkerColor(kGreen+3);
 gr4->SetMarkerColor(kViolet);
 gr5->SetMarkerColor(kBlack);

 gr1->Draw("ap");
 // jmur->Draw("sp");
 gr1->Draw("sp");
 gr2->Draw("sp");
 gr3->Draw("sp");
 gr4->Draw("sp");
 if(spec=="hms")gr5->Draw("sp");

 TPaveText *t1=new TPaveText(.1,.7,.5,.9,"NDC");
 string l1="Delta  Corr?  Yes";
 string l2="P_cent Corr?  Yes";
 if(pass=="pass107" || pass=="pass108")l1="Delta  Corr?  No";
 if(pass=="pass107" || pass=="pass109")l2="P_cent Corr?  No";
 t1->AddText(pass.c_str());
 t1->AddText(l1.c_str());
 t1->AddText(l2.c_str());
 t1->Draw();
 TLegend *leg=new TLegend(.5,.7,.9,.9);
 leg->AddEntry(gr1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(gr2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(gr3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(gr4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 if(spec=="hms") leg->AddEntry(gr5,Form("E'=%2.2f GeV/c",psetf[4]),"p");
 // leg->AddEntry(jmu,"JMU","p");

 leg->Draw();
 /// c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
