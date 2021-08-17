
#include "src/formatHist.cpp"
#include "src/getRadCorr.cpp"

TGraphErrors* extractCS(string mom="2p7"){
  Double_t pc;
  if(mom=="2p5")pc=2.5;
  if(mom=="3p0")pc=3.0;
  if(mom=="3p5")pc=3.5;
  if(mom=="4p4")pc=4.4;
//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *fr=new TFile(Form("ratiosOut/ratiosc25deg%s_1.root",mom.c_str()));
  TH1F *hrd=(TH1F*)fr->Get("hrd");  
  hrd->SetDirectory(0);
  fr->Close();

  Double_t pOffset=-0.017;   
  //Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  Double_t thetac=24.98;
  TGraph2D *gr;
  /*
  if(run==2525)
    gr=getRadCorr("h2cryo",1);  
  else if(run==2528)
    gr=getRadCorr("d2cryo",1);  
  else if(run==2540)
    gr=getRadCorr("carbon",1);  
  */
  gr=getRadCorr("c",1);  

const Int_t nbins=hrd->GetNbinsX();

 Float_t delta, ratio, err, ep, model;
 vector <float> cx;
 vector <float> cxe;
 vector <float> eprime;
 for (Int_t i=1; i<=nbins; i++)
   {
     delta=hrd->GetBinCenter(i);
     ratio=hrd->GetBinContent(i);
     err=hrd->GetBinError(i);
     ep=(1+delta/100)*hsec;
     model=gr->Interpolate(ep,thetac);  //<<"\t"<<
     cout <<delta<<"\t"<<ratio<<"\t"<<err<<"\t"<<model<<"\t"<<ep<<"\t"<<thetac<<endl;
     cx.push_back(ratio*model);
     cxe.push_back(err*model);
     eprime.push_back(ep);
   }
 TGraphErrors*gcx=new TGraphErrors(nbins,&eprime[0],&cx[0],0,&cxe[0]);
 // gcx->SetMarkerStyle(22);
 // gcx->Draw("ap");


 return gcx;
}

void plotModel(){

  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////
 vector <float> mx;
 vector <float> my;
 Float_t delta, ratio, err, ep, model;
 Double_t thetac=21.;
 TGraph2D *gr=getRadCorr("h",1);  
 for (Int_t i=0;i<1000;i++)
   {
     ep=1.+i/1000.*5.;
     model=gr->Interpolate(ep,thetac);  //<<"\t"<<
     Double_t mp = .9382723;
     Double_t mp2 = mp*mp;
     Double_t ebeam=10.602l;
     Double_t sin2 = sin(thetac*TMath::Pi()/180/2.)*sin(thetac*TMath::Pi()/180/2.);
     Double_t nu = ebeam -ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     cout<<q2<<"\t"<<ep<<endl;
     Double_t w2= mp2 + 2.*mp*nu-q2;
     Double_t xb=q2/2./mp/nu;
     if(model>0)
       {
     mx.push_back(xb);
     my.push_back(model);
       }
   }
 TGraph *gm=new TGraph(mx.size(),&mx[0],&my[0]);

 gm->GetXaxis()->SetTitle("x_{B}");
 gm->SetTitle("Hydrogen 21deg");
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
 gm->GetYaxis()->SetTitleOffset(1.1);
 gm->GetYaxis()->SetRangeUser(0,3.2);
 gm->GetXaxis()->SetRangeUser(0.3,1);
 gm->SetLineColor(kRed);
 gm->SetLineWidth(3);
 // gm->SetLineColor(kBlack);
 gm->Draw("ac");



 TLegend *leg=new TLegend(.6,.6,.85,.75);
 leg->AddEntry(gm,"f1f220 (M.E. Christy)","l");
 // leg->AddEntry(gr2p5,"E'=2.5 GeV/c","p");
 // leg->AddEntry(gr3p0,"E'=3.0 GeV/c","p");
 // leg->AddEntry(gr3p5,"E'=3.5 GeV/c","p");
 // leg->AddEntry(gr4p4,"E'=4.4 GeV/c","p");
 leg->Draw();

  return;
}
