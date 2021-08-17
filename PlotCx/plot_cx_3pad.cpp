#include "src/formatHist.cpp"
#include "src/getRadCorr.cpp"
//#include "src/readReport.cpp"
#include "src/getMom.cpp"
#include "src/getMomList.cpp"
#include "src/getAngle.cpp"
#include "src/getCSB.cpp"
#include "src/getCJ.cpp"
#include "src/getKull.cpp"
#include "src/getKP.cpp"
#include "jmu/getJmu.cpp"

void fillHist(TGraphErrors* g=0, TH1D *h=0){

  const int n=g->GetN();
  cout << "There are "<<n<<" points in "<<g->GetName()<<endl;
  double x,y;
  for(int i=0;i<n;i++)
    {
      g->GetPoint(i,x,y);
      // h->Fill(y);
            if(x<0.8)h->Fill(y);
      cout << "Filling " << g->GetName() << "  N: " << n << " num:" << y <<endl;
    }
  return;
} 

TGraphErrors* extractCS(string spec="shms", string target="d", string angle="39",string mom="1p3", int cs=1){

  string kin;
  if(target=="r")kin="h"+angle+"deg"+mom;
  else kin=target+angle+"deg"+mom;
  cout << "The Kinematic is " << kin <<endl;
  Double_t pc=getMom(kin,spec);
  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  Double_t thetac=getAngle(angle,spec);
  TGraph2D *grh;
  TGraph2D *grd;
  TGraph2D *grh2;
  TGraph2D *grd2;

//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *frd=new TFile(Form("ratiosOut/pass10/ratiosd%sdeg%s_1.root",angle.c_str(),mom.c_str()));
  TH1F *hrdd=(TH1F*)frd->Get("hrd");  
  hrdd->SetDirectory(0);
  frd->Close();

  TFile *frh=new TFile(Form("ratiosOut/pass10/ratiosh%sdeg%s_1.root",angle.c_str(),mom.c_str()));
  TH1F *hrdh=(TH1F*)frh->Get("hrd");  
  hrdh->SetDirectory(0);
  frh->Close();

  grh=getRadCorr("h",1);  
  grd=getRadCorr("d",1);  
  grh2=getRadCorr("h",2);  
  grd2=getRadCorr("d",2);  

  const Int_t nbins=hrdd->GetNbinsX();
  Float_t deltad, ratiod, errd, ep, modeld, rci_d, rci_h;
  Float_t deltah, ratioh, errh, modelh,csbh, csbd;
  vector <float> cx;
  vector <float> cxe;
  vector <float> eprime;

  //go bin by bin and wt ratios
  for (Int_t i=1; i<=nbins; i++)
   {
     deltad=hrdd->GetBinCenter(i);
     ratiod=hrdd->GetBinContent(i);
     errd=hrdd->GetBinError(i);

     deltah=hrdh->GetBinCenter(i);
     ratioh=hrdh->GetBinContent(i);
     errh=hrdh->GetBinError(i);

     ep=(1+deltah/100.)*hsec;

     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<
     rci_d=grd2->Interpolate(ep,thetac);  //<<"\t"<<
     rci_h=grh2->Interpolate(ep,thetac);  //<<"\t"<<

     if(ratioh!=0 && ratiod!=0)
       {
	 float cxh=(ratioh*modelh);
	 float cxd=(ratiod*modeld);
	 
	 if(cs==1)
	   {
	     if(target=="h")cx.push_back(cxh);
	     if(target=="d")cx.push_back(cxd);
	     if(target=="r")cx.push_back(cxd/cxh/2);
	     
	     if(target=="h")cxe.push_back(errh*modelh);
	     if(target=="d")cxe.push_back(errd*modeld);
	     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))/2.);
	     eprime.push_back(xb);
	   }
	 if(cs==0)
	   {
	     if(target=="h")cx.push_back(cxh/modelh);
	     if(target=="d")cx.push_back(cxd/modeld);
	     if(target=="r")cx.push_back(cxd/modeld/cxh*modelh);
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

void plot_cx(string target="d", string angle="39", string spec="shms",float xbmin=0.0, float xbmax=1.0, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.7, float ratiomax =1.3 ){

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
 TGraph2D *grd=getRadCorr("d",1);  
 TGraph2D *grh=getRadCorr("h",1);  
 for (Int_t i=0;i<1000;i++)
   {
     ep=xmin+i/1000.*(xmax-xmin);
     modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<
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

  TPad *pad1 = new TPad("pad1","pad1",0,0.6,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0.3,1,0.6);
  TPad *pad3 = new TPad("pad3","pad3",0,0.0,1,0.3);
  //  gStyle->SetGridStyle(1);
  // pad1->SetGrid();
  // pad2->SetGrid();
  pad1->SetBottomMargin(0.1);
  pad1->SetLeftMargin(0.13);
  pad2->SetLeftMargin(0.13);
  pad3->SetLeftMargin(0.13);
  //  pad1->SetBorderMode(0);
  pad2->SetTopMargin(0.1);
  pad2->SetBottomMargin(0.17);
  //  pad2->SetBorderMode(0);
  pad3->SetTopMargin(0.1);
  pad3->SetBottomMargin(0.17);
  //  pad3->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();
  pad1->cd();

  gm->Draw();
  //  if(target=="r"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}

  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////
  TH1D *h1=new TH1D("h1","data/f1f220",100,.7,1.3);
  TH1D *h2=new TH1D("h2","data/f1f220",100,.7,1.3);
  TGraphErrors *grcx1=extractCS("shms",target,angle,pset[0],1);
  TGraphErrors *grcx2=extractCS("shms",target,angle,pset[1],1);
  TGraphErrors *grcx3=extractCS("shms",target,angle,pset[2],1);
  TGraphErrors *grcx4=extractCS("shms",target,angle,pset[3],1);

 TGraphErrors *jmu=getJmu(target,angle,grd,grh,1);

 h1->SetLineColor(kRed);
 h1->SetFillStyle(3005);
 h1->SetFillColor(kRed);

 h2->SetLineColor(kBlue);
 h2->SetFillStyle(3004);
 h2->SetFillColor(kBlue);

 jmu->SetMarkerStyle(33);
 grcx1->SetMarkerStyle(27);
 grcx2->SetMarkerStyle(27);
 grcx3->SetMarkerStyle(27);
 grcx4->SetMarkerStyle(27);

 jmu->SetMarkerSize(.6);
 grcx1->SetMarkerSize(.6);
 grcx2->SetMarkerSize(.6);
 grcx3->SetMarkerSize(.6);
 grcx4->SetMarkerSize(.6);

 jmu->SetMarkerColor(kBlack);
 grcx1->SetMarkerColor(kRed);
 grcx2->SetMarkerColor(kOrange);
 grcx3->SetMarkerColor(kGreen+3);
 grcx4->SetMarkerColor(kViolet);

 jmu->Draw("sp");

 grcx1->Draw("sp");
 grcx2->Draw("sp");
 grcx3->Draw("sp");
 grcx4->Draw("sp");


 gm->Draw("same");

 // if(target=="r"){gm_k->Draw("same");gm_cj->Draw("same");gm_k1->Draw("same");}
 pad2->cd();
 TGraphErrors *gr1=extractCS("shms",target,angle,pset[0],0);
 TGraphErrors *gr2=extractCS("shms",target,angle,pset[1],0);
 TGraphErrors *gr3=extractCS("shms",target,angle,pset[2],0);
 TGraphErrors *gr4=extractCS("shms",target,angle,pset[3],0);
 TGraphErrors *jmur=getJmu(target,angle,grd,grh,0);

 fillHist(gr1,h1);
 fillHist(gr2,h1);
 fillHist(gr3,h1);
 fillHist(gr4,h1);
 fillHist(jmur,h2);
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
 jmur->Draw("sp");
 gr1->Draw("sp");
 gr2->Draw("sp");
 gr3->Draw("sp");
 gr4->Draw("sp");


 pad1->cd();
 TLegend *leg=new TLegend(.15,.5,.6,.87);
 leg->AddEntry(gm,"f1f220","l");
 // leg->AddEntry(gm_k,"KP DIS","l");
 // leg->AddEntry(gm_k1,"KP HYBRID","l");
 // leg->AddEntry(gm_cj,"CJ15","l");
 leg->AddEntry(grcx1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(grcx2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(grcx3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(grcx4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 leg->AddEntry(jmu,"JMU_{corr}","p");

 if(target=="r") leg->Draw();

 pad3->cd();

 h1->SetTitle("Data / f1f220 (X_B < 0.8");
 h1->SetName("Bill / f1f220");
 h2->SetName("JMU_{corr}  / f1f220");
 h1->GetYaxis()->SetRangeUser(0,25);
 h1->GetXaxis()->SetTitle("Bjorken X");
 h1->Draw();
 h2->Draw("sames");
 gPad->Update();
 TPaveStats *st1=(TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");
 st1->SetY1NDC(0.7);
 st1->SetY2NDC(0.9);
 st1->Draw("same");

 TPaveStats *st2=(TPaveStats*)h2->GetListOfFunctions()->FindObject("stats");
 st2->SetY1NDC(0.4);
 st2->SetY2NDC(0.6);
 st2->Draw("same");

 TLegend *leg3=new TLegend(.15,.6,.35,.8);
 leg3->AddEntry(h1,"Bill / f1f220)","lf");
 leg3->AddEntry(h2,"JMU_{corr} / f1f220)","lf");
 leg3->Draw("same");
 /// c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
