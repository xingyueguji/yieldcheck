#include "src/formatHist.cpp"
#include "src/getRadCorr.cpp"
#include "src/readReport.cpp"

TGraphErrors* extractCS(string mom="2p7"){
  Double_t pc;
  if(mom=="2p7")pc=readReport(2551,"mom");
  if(mom=="3p3")pc=readReport(2524,"mom");
  if(mom=="4p0")pc=readReport(2521,"mom");
  if(mom=="5p1")pc=readReport(2484,"mom");
//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *frd=new TFile(Form("ratiosOut/ratiosd21deg%s_1.root",mom.c_str()));
  TH1F *hrdd=(TH1F*)frd->Get("hrd");  
  hrdd->SetDirectory(0);
  frd->Close();

  TFile *frh=new TFile(Form("ratiosOut/ratiosh21deg%s_1.root",mom.c_str()));
  TH1F *hrdh=(TH1F*)frh->Get("hrd");  
  hrdh->SetDirectory(0);
  frh->Close();

  //  Double_t pOffset=-0.015;   
  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  Double_t thetac=21.035;
  TGraph2D *grh;
  TGraph2D *grd;
  /*
  if(run==2525)
    gr=getRadCorr("h2cryo",1);  
  else if(run==2528)
    gr=getRadCorr("d2cryo",1);  
  else if(run==2540)
    gr=getRadCorr("carbon",1);  
  */
  grh=getRadCorr("h",1);  
  grd=getRadCorr("d",1);  

const Int_t nbins=hrdd->GetNbinsX();

 Float_t deltad, ratiod, errd, ep, modeld;
 Float_t deltah, ratioh, errh, modelh;
 vector <float> cx;
 vector <float> cxe;
 vector <float> eprime;
 for (Int_t i=1; i<=nbins; i++)
   {
     ep=(1+deltah/100)*hsec;

     deltad=hrdd->GetBinCenter(i);
     ratiod=hrdd->GetBinContent(i);
     errd=hrdd->GetBinError(i);
     modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<

     deltah=hrdh->GetBinCenter(i);
     ratioh=hrdh->GetBinContent(i);
     errh=hrdh->GetBinError(i);
     modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<

     //     cout <<delta<<"\t"<<ratio<<"\t"<<err<<"\t"<<model<<"\t"<<ep<<"\t"<<thetac<<endl;
     cx.push_back(ratiod*modeld/ratioh/modelh);
     cxe.push_back(0.);
     eprime.push_back(ep);
   }
 TGraphErrors*gcx=new TGraphErrors(nbins,&eprime[0],&cx[0],0,&cxe[0]);
 // gcx->SetMarkerStyle(22);
 // gcx->Draw("ap");


 return gcx;
}

void plot_ratio21deg(){

  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////
 vector <float> mx;
 vector <float> my;
 Float_t delta, ratio, err, ep, modeld, modelh;
 Double_t thetac=21.035;
 TGraph2D *grd=getRadCorr("d",1);  
 TGraph2D *grh=getRadCorr("h",1);  
 for (Int_t i=0;i<1000;i++)
   {
     modeld=grd->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<

     ep=2.2+i/1000.*3.8;
     if(modelh!=0 && modeld!=0){ 
       mx.push_back(ep);
       my.push_back(modeld/modelh);
     }
     cout << ep << "\t"<<modeld/modelh<<endl;
   }
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);
 gm->GetXaxis()->SetTitle("E'");
 gm->SetTitle("D/H 21deg");
 gm->GetYaxis()->SetTitle("");
 gm->SetLineColor(kBlack);
 // gm->SetLineColor(kBlack);
 gm->GetYaxis()->SetRangeUser(-10,10);
 gm->Draw("ac");


  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////
 TGraphErrors *gr2p7=extractCS("2p7");
 TGraphErrors *gr3p3=extractCS("3p3");
 TGraphErrors *gr4p0=extractCS("4p0");
 TGraphErrors *gr5p1=extractCS("5p1");


 gr2p7->SetMarkerStyle(33);
 gr3p3->SetMarkerStyle(33);
 gr4p0->SetMarkerStyle(33);
 gr5p1->SetMarkerStyle(33);
 gr2p7->SetMarkerColor(kRed);
 gr3p3->SetMarkerColor(kOrange);
 gr4p0->SetMarkerColor(kGreen+3);
 gr5p1->SetMarkerColor(kViolet);
gr2p7->Draw("sp");
gr3p3->Draw("sp");
gr4p0->Draw("sp");
gr5p1->Draw("sp");

 TLegend *leg=new TLegend(.6,.6,.9,.9);
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(gr2p7,"E'=2.7 GeV/c","p");
 leg->AddEntry(gr3p3,"E'=3.3 GeV/c","p");
 leg->AddEntry(gr4p0,"E'=4.0 GeV/c","p");
 leg->AddEntry(gr5p1,"E'=5.1 GeV/c","p");
 leg->Draw();

  return;
}
