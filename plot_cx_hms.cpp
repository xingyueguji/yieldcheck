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

void plot_cx(string target="d", string angle="39", string spec="shms", string pass="pass105", float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){

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
 TGraph2D *grd=getRadCorrW2("d",1,"hms");  
 TGraph2D *grh=getRadCorrW2("h",1,"hms");  
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
   gm->SetTitle(Form("SHMS Hydrogen %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin,cxmax);
 }
 if(target=="d"){
   gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle(Form("SHMS Deuterium %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin*2,cxmax*2);
 }
if(target=="r"){
  gm->SetTitle(Form("SHMS D/H/2 %sdeg",angle.c_str()));
  gm->GetYaxis()->SetRangeUser(0.5,1.6);
 }

 gm->GetYaxis()->SetTitleSize(.055);
 gm->GetXaxis()->CenterTitle();
 gm->GetYaxis()->CenterTitle();
 gm->GetXaxis()->SetNdivisions(-5);
 // gm->GetXaxis()->SetLabelSize(0.06);// size of axis value font
 // TCanvas *c1=new TCanvas();

  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0.02,1,0.38);
  //  gStyle->SetGridStyle(1);
  // pad1->SetGrid();
  // pad2->SetGrid();
  pad1->SetBottomMargin(0.1);
  pad1->SetLeftMargin(0.13);
  pad2->SetLeftMargin(0.13);
  pad1->SetBorderMode(0);
  pad2->SetTopMargin(0.1);
  pad2->SetBottomMargin(0.17);
  pad2->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();

  gm->Draw();
  if(target=="r"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}


  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////

  TGraphErrors *grcx1=extractCS("hms",target,angle,"3p3",1,pass);
  TGraphErrors *grcx2=extractCS("hms",target,angle,"4p0",1,pass);
  TGraphErrors *grcx3=extractCS("hms",target,angle,"4p5",1,pass);
  TGraphErrors *grcx4=extractCS("hms",target,angle,"5p1",1,pass);
  TGraphErrors *grcx5=extractCS("hms",target,angle,"5p7",1,pass);

 grcx1->SetMarkerStyle(27);
 grcx2->SetMarkerStyle(27);
 grcx3->SetMarkerStyle(27);
 grcx4->SetMarkerStyle(27);
 grcx5->SetMarkerStyle(27);

 grcx1->SetMarkerSize(.6);
 grcx2->SetMarkerSize(.6);
 grcx3->SetMarkerSize(.6);
 grcx4->SetMarkerSize(.6);
 grcx5->SetMarkerSize(.6);

 grcx1->SetMarkerColor(kRed);
 grcx2->SetMarkerColor(kOrange);
 grcx3->SetMarkerColor(kGreen+3);
 grcx4->SetMarkerColor(kViolet);

 // jmu->Draw("sp");

 grcx1->Draw("sp");
 grcx2->Draw("sp");
 grcx3->Draw("sp");
 grcx4->Draw("sp");


 gm->Draw("same");

 if(target=="r"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}
 pad2->cd();
 TGraphErrors *gr1=extractCS("shms",target,angle,pset[0],0,pass);
 TGraphErrors *gr2=extractCS("shms",target,angle,pset[1],0,pass);
 TGraphErrors *gr3=extractCS("shms",target,angle,pset[2],0,pass);
 TGraphErrors *gr4=extractCS("shms",target,angle,pset[3],0,pass);
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
 gr1->SetMarkerStyle(27);
 gr2->SetMarkerStyle(27);
 gr3->SetMarkerStyle(27);
 gr4->SetMarkerStyle(27);

 jmur->SetMarkerSize(.6);
 gr1->SetMarkerSize(.6);
 gr2->SetMarkerSize(.6);
 gr3->SetMarkerSize(.6);
 gr4->SetMarkerSize(.6);

 jmur->SetMarkerColor(kBlack);
 gr1->SetMarkerColor(kRed);
 gr2->SetMarkerColor(kOrange);
 gr3->SetMarkerColor(kGreen+3);
 gr4->SetMarkerColor(kViolet);

 gr1->Draw("ap");
 // jmur->Draw("sp");
 gr1->Draw("sp");
 gr2->Draw("sp");
 gr3->Draw("sp");
 gr4->Draw("sp");

 TPaveText *t1=new TPaveText(.4,.7,.6,.9,"NDC");
 t1->AddText(pass.c_str());
 t1->Draw();
 pad1->cd();
 TLegend *leg=new TLegend(.5,.5,.9,.9);
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(gm_k,"KP DIS","l");
 leg->AddEntry(gm_k1,"KP HYBRID","l");
 leg->AddEntry(gm_cj,"CJ15","l");
 leg->AddEntry(grcx1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(grcx2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(grcx3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(grcx4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 // leg->AddEntry(jmu,"JMU","p");

 if(target=="d") leg->Draw();
 /// c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
