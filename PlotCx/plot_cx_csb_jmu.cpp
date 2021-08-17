#include "src/formatHist.cpp"
#include "src/getRadCorr.cpp"
//#include "src/readReport.cpp"
#include "src/getMom.cpp"
#include "src/getMomList.cpp"
#include "src/getAngle.cpp"
#include "src/getCSB.cpp"

TGraphErrors* extractCS(string spec="shms", string target="h", string angle="21",string mom="2p7", int cs=1){
  string kin;
  if(target=="r")kin="h"+angle+"deg"+mom;
  else kin=target+angle+"deg"+mom;
  Double_t pc=getMom(kin,spec);
  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  //  Double_t thetac=21.035;
  Double_t thetac=getAngle(angle,spec);
  //  thetac=21.035;
  TGraph2D *grh;
  TGraph2D *grd;
  TGraph2D *grh2;
  TGraph2D *grd2;

//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *frd=new TFile(Form("ratiosOut/pass2/ratiosd%sdeg%s_1.root",angle.c_str(),mom.c_str()));
  TH1F *hrdd=(TH1F*)frd->Get("hrd");  
  hrdd->SetDirectory(0);
  frd->Close();

  TFile *frh=new TFile(Form("ratiosOut/pass2/ratiosh%sdeg%s_1.root",angle.c_str(),mom.c_str()));
  TH1F *hrdh=(TH1F*)frh->Get("hrd");  
  hrdh->SetDirectory(0);
  frh->Close();

  grh=getRadCorr("h",1);  
  grd=getRadCorr("d",1);  
  grh2=getRadCorr("h",3);  
  grd2=getRadCorr("d",3);  
  TF1 *csb=getCSB(angle);
  const Int_t nbins=hrdd->GetNbinsX();
  Float_t deltad, ratiod, errd, ep, modeld, modeld2, modelh2;
  Float_t deltah, ratioh, errh, modelh,csbh, csbd;
  vector <float> cx;
  vector <float> cxe;
  vector <float> eprime;

  for (Int_t i=1; i<=nbins; i++)
   {
     deltad=hrdd->GetBinCenter(i);
     ratiod=hrdd->GetBinContent(i);
     errd=hrdd->GetBinError(i);


     deltah=hrdh->GetBinCenter(i);
     ratioh=hrdh->GetBinContent(i);
     errh=hrdh->GetBinError(i);



     ep=(1+deltah/100)*hsec;


     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<
     modeld2=grd2->Interpolate(ep,thetac);  //<<"\t"<<
     modelh2=grh2->Interpolate(ep,thetac);  //<<"\t"<<

     if(modelh2!=0){
     csbh=(modelh2-csb->Eval(ep))/(modelh2);
     }
     else csbh=1.;

     if(modeld2!=0){
     csbd=(modeld2-csb->Eval(ep))/(modeld2);
     }
     else csbd=1.;
     cout << "CSB:           "<<csbd <<"\t"<<csbh<<endl;
     //     cout <<delta<<"\t"<<ratio<<"\t"<<err<<"\t"<<model<<"\t"<<ep<<"\t"<<thetac<<endl;
     if(ratioh!=0 && ratiod!=0)
       {
     if(cs==1)
       {
     if(target=="h")cx.push_back(ratioh*modelh*csbh);
     if(target=="d")cx.push_back(ratiod*modeld*csbd);
     if(target=="r")cx.push_back(ratiod*modeld/ratioh/modelh/2.*csbd/csbh);
     if(target=="h")cxe.push_back(errh*modelh);
     if(target=="d")cxe.push_back(errd*modeld);
     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))/2.);
     eprime.push_back(xb);
     cout<<xb<<endl;
       }
     if(cs==0)
       {
     if(target=="h")cx.push_back(ratioh*csbh);
     if(target=="d")cx.push_back(ratiod*csbd);
     if(target=="r")cx.push_back(ratiod/ratioh*csbd/csbh);
     if(target=="h")cxe.push_back(errh);
     if(target=="d")cxe.push_back(errd);
     if(target=="r")cxe.push_back(sqrt(pow(errd,2)+pow(errh,2))/2.);
     eprime.push_back(xb);
       }
       }
   }
 TGraphErrors*gcx=new TGraphErrors(nbins,&eprime[0],&cx[0],0,&cxe[0]);
 return gcx;
}

void plot_cx_csb(string target="h", string angle="21", string spec="shms",float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){

 string pset[4];
 float psetf[4];
 getMomList(angle,pset,psetf);
  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////

 vector <float> mx;
 vector <float> my;
 Float_t delta, ratio, err, ep, modeld, modelh, xmin, xmax;
 xmin=psetf[0]*(.9);
 xmax=psetf[3]*(1.22);
 // Double_t thetac=21.035;
 Double_t thetac=getAngle(angle,spec);
 TGraph2D *grd=getRadCorr("d",1);  
 TGraph2D *grh=getRadCorr("h",1);  
 for (Int_t i=0;i<1000;i++)
   {
     //     ep=2.2+i/1000.*3.8;
     ep=xmin+i/1000.*(xmax-xmin);
     modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<
     //     modeld=grd->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<
     //     modelh=grh->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<
     Double_t ebeam=10.602;
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     if(modelh!=0 && modeld!=0){ 
       mx.push_back(xb);
       if(target=="r")my.push_back(modeld/modelh/2.);
       if(target=="h")my.push_back(modelh);
       if(target=="d")my.push_back(modeld);
     }
   }
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);

 gm->GetXaxis()->SetTitle("Bjorken X");

 gm->SetLineColor(kBlack);
 gm->GetXaxis()->SetRangeUser(xbmin,xbmax);
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
   gm->SetTitle(Form("SHMS D/H %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(0.5,1.6);
 }
 // TCanvas *c1=new TCanvas();

  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0.02,1,0.33);
  //  gStyle->SetGridStyle(1);
 pad1->SetGrid();
 pad2->SetGrid();
  pad1->SetBottomMargin(0.1);
  pad1->SetBorderMode(0);
  pad2->SetTopMargin(0.1);
  pad2->SetBottomMargin(0.1);
  pad2->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  gm->Draw();



  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////

 TGraphErrors *grcx1=extractCS("shms",target,angle,pset[0],1);
 TGraphErrors *grcx2=extractCS("shms",target,angle,pset[1],1);
 TGraphErrors *grcx3=extractCS("shms",target,angle,pset[2],1);
 TGraphErrors *grcx4=extractCS("shms",target,angle,pset[3],1);
 grcx1->SetMarkerStyle(33);
 grcx2->SetMarkerStyle(33);
 grcx3->SetMarkerStyle(33);
 grcx4->SetMarkerStyle(33);
 grcx1->SetMarkerColor(kRed);
 grcx2->SetMarkerColor(kOrange);
 grcx3->SetMarkerColor(kGreen+3);
 grcx4->SetMarkerColor(kViolet);
grcx1->Draw("sp");
grcx2->Draw("sp");
grcx3->Draw("sp");
grcx4->Draw("sp");

 pad2->cd();
 TGraphErrors *gr1=extractCS("shms",target,angle,pset[0],0);
 TGraphErrors *gr2=extractCS("shms",target,angle,pset[1],0);
 TGraphErrors *gr3=extractCS("shms",target,angle,pset[2],0);
 TGraphErrors *gr4=extractCS("shms",target,angle,pset[3],0);

gStyle->SetTitleFontSize(.1);
gr1->SetTitle("Data/Model");
gr1->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
gr1->GetXaxis()->SetLimits(xbmin,xbmax);
 gr1->GetXaxis()->SetLabelSize(.07);
 gr1->GetYaxis()->SetLabelSize(.07);
 gr1->SetMarkerStyle(33);
 gr2->SetMarkerStyle(33);
 gr3->SetMarkerStyle(33);
 gr4->SetMarkerStyle(33);
 gr1->SetMarkerColor(kRed);
 gr2->SetMarkerColor(kOrange);
 gr3->SetMarkerColor(kGreen+3);
 gr4->SetMarkerColor(kViolet);
 gr1->Draw("ap");
 gr2->Draw("sp");
 gr3->Draw("sp");
 gr4->Draw("sp");

 pad1->cd();
 TLegend *leg=new TLegend(.5,.5,.9,.9);
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(grcx1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(grcx2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(grcx3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(grcx4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 if(target=="d") leg->Draw();
 /// c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
