//#include "src/formatHist.cpp"
//#include "src/getRadCorr.cpp"

TGraphErrors* extractCS(string mom="2p7"){
  Double_t pc;
  if(mom=="2p7")pc=2.7;
  if(mom=="3p3")pc=3.3;
  if(mom=="4p0")pc=4.0;
  if(mom=="5p1")pc=5.2;
//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *fr=new TFile(Form("ratiosOut/ratiosc21deg%s_1.root",mom.c_str()));
  TH1F *hrd=(TH1F*)fr->Get("hrd");  
  hrd->SetDirectory(0);
  fr->Close();

  Double_t pOffset=-0.015;   
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  Double_t thetac=21.035;
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
 gcx->Draw("ap");

 /*
 //  GRAPH model
 vector <float> mx;
 vector <float> my;
 for (Int_t i=0;i<1000;i++)
   {
     model=gr->Interpolate(0.+i/1000.*6,thetac);  //<<"\t"<<
     ep=i/1000.*6.;
     mx.push_back(ep);
     my.push_back(model);
   }
 TGraph *gm=new TGraph(1000,&mx[0],&my[0]);
 gm->Draw("same");
 */
 return gcx;
}
