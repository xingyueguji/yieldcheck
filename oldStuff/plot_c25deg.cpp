
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

void plot_c21deg(){

  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////
 vector <float> mx;
 vector <float> my;
 Float_t delta, ratio, err, ep, model;
 Double_t thetac=24.98;
 TGraph2D *gr=getRadCorr("c",1);  
 for (Int_t i=0;i<1000;i++)
   {
     model=gr->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<
     ep=2.2+i/1000.*3.8;
     mx.push_back(ep);
     my.push_back(model);
   }
 TGraph *gm=new TGraph(1000,&mx[0],&my[0]);
 gm->GetXaxis()->SetTitle("E'");
 gm->SetTitle("Carbon 25deg");
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
 gm->SetLineColor(kBlack);
 // gm->SetLineColor(kBlack);
 gm->Draw("ac");


  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////
 TGraphErrors *gr2p5=extractCS("2p5");
 TGraphErrors *gr3p0=extractCS("3p0");
 TGraphErrors *gr3p5=extractCS("3p5");
 TGraphErrors *gr4p4=extractCS("4p4");


 gr2p5->SetMarkerStyle(33);
 gr3p0->SetMarkerStyle(33);
 gr3p5->SetMarkerStyle(33);
 gr4p4->SetMarkerStyle(33);
 gr2p5->SetMarkerColor(kRed);
 gr3p0->SetMarkerColor(kOrange);
 gr3p5->SetMarkerColor(kGreen+3);
 gr4p4->SetMarkerColor(kViolet);
gr2p5->Draw("sp");
gr3p0->Draw("sp");
gr3p5->Draw("sp");
gr4p4->Draw("sp");

 TLegend *leg=new TLegend(.6,.6,.9,.9);
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(gr2p5,"E'=2.5 GeV/c","p");
 leg->AddEntry(gr3p0,"E'=3.0 GeV/c","p");
 leg->AddEntry(gr3p5,"E'=3.5 GeV/c","p");
 leg->AddEntry(gr4p4,"E'=4.4 GeV/c","p");
 leg->Draw();

  return;
}
