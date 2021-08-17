#include "src/formatHist.cpp"
#include "src/getRadCorr.cpp"
#include "src/readReport.cpp"

TGraphErrors* extractCS(string spec="shms", string target="h", string angle="21",string mom="2p7", int cs=1){
  //  Double_t pOffset=-0.015;   
  Double_t pc;
  if(spec=="shms" && angle=="21")
    {
  if(mom=="2p7")pc=readReport(2551,"mom");
  if(mom=="3p3")pc=readReport(2524,"mom");
  if(mom=="4p0")pc=readReport(2521,"mom");
  if(mom=="5p1")pc=readReport(2484,"mom");
    }
  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  Double_t thetac=21.035;
  TGraph2D *grh;
  TGraph2D *grd;

//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *frd=new TFile(Form("ratiosOut/ratiosd%sdeg%s_1.root",angle.c_str(),mom.c_str()));
  TH1F *hrdd=(TH1F*)frd->Get("hrd");  
  hrdd->SetDirectory(0);
  frd->Close();

  TFile *frh=new TFile(Form("ratiosOut/ratiosh%sdeg%s_1.root",angle.c_str(),mom.c_str()));
  TH1F *hrdh=(TH1F*)frh->Get("hrd");  
  hrdh->SetDirectory(0);
  frh->Close();

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
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;

     deltad=hrdd->GetBinCenter(i);
     ratiod=hrdd->GetBinContent(i);
     errd=hrdd->GetBinError(i);
     modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<

     deltah=hrdh->GetBinCenter(i);
     ratioh=hrdh->GetBinContent(i);
     errh=hrdh->GetBinError(i);
     modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<

     //     cout <<delta<<"\t"<<ratio<<"\t"<<err<<"\t"<<model<<"\t"<<ep<<"\t"<<thetac<<endl;
     if(deltah>0 && deltad>0)
       {
     if(cs==1)
       {
     if(target=="h")cx.push_back(ratioh*modelh);
     if(target=="d")cx.push_back(ratiod*modeld);
     if(target=="r")cx.push_back(ratiod*modeld/ratioh/modelh/2.);
     if(target=="h")cxe.push_back(errh*modelh);
     if(target=="d")cxe.push_back(errd*modeld);
     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))/2.);

     eprime.push_back(xb);
       }
     if(cs==0)
       {
     if(target=="h")cx.push_back(ratioh);
     if(target=="d")cx.push_back(ratiod);
     if(target=="r")cx.push_back(ratiod/ratioh);
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

void plot_cx(string target="h", string angle="21"){

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
   gm->GetXaxis()->SetRangeUser(0,1.);
 if(target=="h" && angle=="21"){
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle("SHMS Hydrogen 21deg");
   gm->GetYaxis()->SetRangeUser(0,4);
 }
 if(target=="d" && angle=="21"){
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
   gm->SetTitle("SHMS Deuterium 21deg");
   gm->GetYaxis()->SetRangeUser(0,8);
 }
 if(target=="r" && angle=="21"){
   gm->SetTitle("SHMS D/H 21deg");
   gm->GetYaxis()->SetRangeUser(0.2,1.8);
 }
 TCanvas *c1=new TCanvas();

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
 TGraphErrors *gr2p7=extractCS("shms",target,angle,"2p7",1);
 TGraphErrors *gr3p3=extractCS("shms",target,angle,"3p3",1);
 TGraphErrors *gr4p0=extractCS("shms",target,angle,"4p0",1);
 TGraphErrors *gr5p1=extractCS("shms",target,angle,"5p1",1);
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

 pad2->cd();
 TGraphErrors *grat2p7=extractCS("shms",target,angle,"2p7",0);
 TGraphErrors *grat3p3=extractCS("shms",target,angle,"3p3",0);
 TGraphErrors *grat4p0=extractCS("shms",target,angle,"4p0",0);
 TGraphErrors *grat5p1=extractCS("shms",target,angle,"5p1",0);

 gStyle->SetTitleFontSize(.1);
 grat2p7->SetTitle("Data/Model");
 grat2p7->GetYaxis()->SetRangeUser(.9,1.1);
 grat2p7->GetXaxis()->SetLimits(0.,1.);
 grat2p7->GetXaxis()->SetLabelSize(.07);
 grat2p7->GetYaxis()->SetLabelSize(.07);
 grat2p7->SetMarkerStyle(33);
 grat3p3->SetMarkerStyle(33);
 grat4p0->SetMarkerStyle(33);
 grat5p1->SetMarkerStyle(33);
 grat2p7->SetMarkerColor(kRed);
 grat3p3->SetMarkerColor(kOrange);
 grat4p0->SetMarkerColor(kGreen+3);
 grat5p1->SetMarkerColor(kViolet);
grat2p7->Draw("ap");
grat3p3->Draw("sp");
grat4p0->Draw("sp");
grat5p1->Draw("sp");

 pad1->cd();
 TLegend *leg=new TLegend(.6,.6,.9,.9);
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(gr2p7,"E'=2.7 GeV/c","p");
 leg->AddEntry(gr3p3,"E'=3.3 GeV/c","p");
 leg->AddEntry(gr4p0,"E'=4.0 GeV/c","p");
 leg->AddEntry(gr5p1,"E'=5.1 GeV/c","p");
 leg->Draw();
 c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
