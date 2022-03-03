#include "src/readReport.cpp"
#include "src/getCharge.cpp"
#include "src/getHMSCharge.cpp"

void fixRange(TH1F *h){
  double min=0;
  double max=0;
  bool foundmin=0;
  bool foundmax=0;
  bool foundpeak=0;
  for(int i=0; i < h->GetNbinsX(); i++) {
    double val = h ->GetBinContent(i);
    if(val==h->GetMaximum())foundpeak=1;
    if(!foundmin && val>0){min=h->GetBinCenter(i);foundmin=1;}
    if(foundpeak==1 && foundmin && !foundmax && val==0){max=h->GetBinCenter(i);foundmax=1;}
  }
  cout<<"Found Min and max to be \t"<<min<<"  "<<max<<endl;
  Double_t fact=h->GetBinWidth(0);
  h->GetXaxis()->SetRangeUser(min-3*fact,max+3*fact);
  return;
}

void dummyRatios(string tgt="alu",string angle="21", string mom="2p7",string spec="shms"){
  //  gStyle->SetOptStat(0);

  string kin=tgt+angle+"deg"+mom; 
  cout << "Kinematic is : "<<kin<<endl;
  Int_t DRAW=1;
  bool scale_em=true;

  // histos
  // hm* MC
  // hd* Data
  // he* Dummy (empty)
  // hs* Data - dummy
  gROOT->ForceStyle();
  //*****MC Histograms*****
  //TFile *fm=new TFile(Form("mcWtOut/pass27/mcWt%s.root",kin.c_str()));
   TFile *fm=new TFile(Form("mcWtOut/pass65/%s_mcWt%s.root",spec.c_str(),kin.c_str()));
   if(!fm->IsOpen())return;
 TH1F *hmd=(TH1F*)fm->Get("delWt");
 TH1F *hmy=(TH1F*)fm->Get("yWt");
 TH1F *hmxp=(TH1F*)fm->Get("xpWt");
 TH1F *hmyp=(TH1F*)fm->Get("ypWt");
 TH1F *hmw2=(TH1F*)fm->Get("w2Wt");
 // hmd->Scale(1/1000.);
 // hmy->Scale(1/1000.);
// hmxp->Scale(1/1000.);
 // hmyp->Scale(1/1000.);
 // hmw2->Scale(1/1000.);
 //****Data Histograms***** 
 TFile *fd=new TFile(Form("dataYieldOut/pass55/%s_dataYield_%s_no.root",spec.c_str(),kin.c_str()));

if(!fd->IsOpen())return;
 TH1F *hdd=(TH1F*)fd->Get("hdd");
 TH1F *hdy=(TH1F*)fd->Get("hyd");
 TH1F *hdxp=(TH1F*)fd->Get("hxpd");
 TH1F *hdyp=(TH1F*)fd->Get("hypd");
 TH1F *hdw2=(TH1F*)fd->Get("hw2d");


 // Charge Normalize data yields
 //=============================
 Float_t charge=0;
 if(spec=="shms")charge=getCharge(tgt,angle,mom);
 if(spec=="hms")charge=getHMSCharge(kin);
 cout << "The Charge is: "<<charge<<endl;
 hdd->Scale(1./charge);
 hdy->Scale(1./charge);
 hdxp->Scale(1./charge);
 hdyp->Scale(1./charge);
 hdw2->Scale(1./charge);

 TH1F *hrd=(TH1F*)hdd->Clone();
 // TH1F *hrd=(TH1F*)hsw2->Clone();
 hrd->SetTitle("Ratio Data/MC");
 hmd->SetTitle("dp/p (%)");
 hmy->SetTitle("Y_{tar} (cm)");
 hmxp->SetTitle("X'_{tar} (mr)");
 hmyp->SetTitle("Y'_{tar} (mr)");
 hmw2->SetTitle("W2 (GeV^{2})");

 //  RATIO DATA/MC
  hrd->Divide(hmd);

 //  Foramatting
 hdd->SetLineColor(kBlack);
 hdy->SetLineColor(kBlack);
 hdxp->SetLineColor(kBlack);
 hdyp->SetLineColor(kBlack);
 hdw2->SetLineColor(kBlack);

 hmd->SetLineColor(kRed);
 hmy->SetLineColor(kRed);
 hmxp->SetLineColor(kRed);
 hmyp->SetLineColor(kRed);
 hmw2->SetLineColor(kRed);

 hmd->SetFillStyle(3002);
 hmd->SetFillColor(kRed);
 hmy->SetFillStyle(3002);
 hmy->SetFillColor(kRed);
 hmxp->SetFillStyle(3002);
 hmxp->SetFillColor(kRed);
 hmyp->SetFillStyle(3002);
 hmyp->SetFillColor(kRed);
 hmw2->SetFillStyle(3002);
 hmw2->SetFillColor(kRed);

 hrd->GetYaxis()->SetRangeUser(.50,1.2); 
 hrd->GetXaxis()->SetRangeUser(-11,23); 
 hdd->GetXaxis()->SetRangeUser(-11,23); 
 if(spec=="hms")
   {
 hmd->GetXaxis()->SetRangeUser(-6.5,9.5); 
 hrd->GetXaxis()->SetRangeUser(-6.5,9.5); 
   }
 hmxp->GetXaxis()->SetRangeUser(-60,60); 
 hmyp->GetXaxis()->SetRangeUser(-50,50); 
 hdy->GetXaxis()->SetRangeUser(-5,5); 
 hdw2->GetXaxis()->SetRangeUser(0,15); 

 Double_t fact=hdd->Integral()/hmd->Integral();
 // fact=1;
 
 if (DRAW==1)
   {
     if(scale_em)
       {
	 hdd->Scale(1/fact);
	 hdy->Scale(1/fact);
	 hdxp->Scale(1/fact);
	 hdyp->Scale(1/fact);
	 hdw2->Scale(1/fact);
       }
     // Drawing
     TCanvas *c1=new TCanvas("c1","c1",600,900);
     c1->Divide(2,3);
     c1->cd(4);
     hdd->Draw("E");
     hmd->Draw("HIST E same");

     TLegend *leg=new TLegend(.3,.1,.7,.3);
     leg->SetHeader(Form("Scale data/mc=%2.4f",fact));
     leg->AddEntry(hmd,"MC","lfp");
     //     leg->AddEntry(hdd,"Data","lfp");
     leg->AddEntry(hdd,"Data","lfp");

     c1->cd(6);
     hrd->Draw();
     gStyle->SetOptFit(1);
     hrd->Fit("pol1");
     //     fixRange(hrd);
     //     hrd->Draw();
     leg->Draw("same");
     c1->cd(1);


     hdy->Draw("E");
     //     fixRange(hsy);
     hmy->Draw("HIST E same");
     double max=hdy->GetMaximum();

     double val1=0;
     double val2=0;
     if(angle=="21")val1=1.794;
     if(angle=="25")val1=2.111;
     if(angle=="29")val1=2.423;
     if(angle=="33")val1=2.721;
     if(angle=="39")val1=3.212;
     val2=-val1;
     TLine *l1=new TLine(val1,0,val1,max);
     TLine *l2=new TLine(val2,0,val2,max);
     l1->Draw("same");
     l2->Draw("same");
     c1->cd(3);
     hdxp->Draw("E");
     hmxp->Draw("same HIST E");

     c1->cd(2);
     hdyp->Draw("E");
     hmyp->Draw("same HIST E");

     c1->cd(5);
     hdw2->Draw("E");
     hmw2->Draw("same HIST E");

     //     TPaveText *pt=new TPaveText(0.38,.3,.58,.55,"NDC");
     TPaveText *pt=new TPaveText(0.25,.45,.45,.55,"NDC");
     pt->AddText(kin.c_str());
     //     pt->AddText("Std; z target 3mm upstream");
     //     pt->AddText("Std; Spec. X' -3mr");
     //     pt->AddText("no_offset ROOTfiles");
     //     pt->SetFillColor(20);
     c1->cd(4);pt->Draw("BR");
     c1->SaveAs(Form("ratiosOut/pass306/%s_ratios%s.pdf",spec.c_str(),kin.c_str()));
     /*
     //    Figure for write up
     TCanvas *c2=new TCanvas("c2","c2",1200,600);
     c2->Divide(2,1);
     c2->cd(1);
     hsd->GetXaxis()->SetTitle("Delta");
     hsd->SetTitle("Charge Normalized Yield");
     hrd->GetXaxis()->SetTitle("Delta");
     hsd->Draw("E");
     hsd->GetYaxis()->SetRangeUser(0,1.6);
     hdd->Draw("E same");
     hmd->Draw("HIST E same");
     leg->Draw("same");
     if(tgt!="c")hed->Draw("HIST E same");
     pt->Draw("BR");
     c2->cd(2);
     hrd->Draw();
     c2->SaveAs("deltaHistos.pdf");
     */
   }


 TFile *oFile=new TFile(Form("ratiosOut/pass306/%s_ratios%s.root",spec.c_str(),kin.c_str()),"RECREATE");

 hdd->Write("hdd");
 hdy->Write("hdy");
 hdxp->Write("hdxp");
 hdyp->Write("hdyp");
 hdw2->Write("hdw2");

 hmd->Write("hmd");
 hmy->Write("hmy");
 hmxp->Write("hmxp");
 hmyp->Write("hmyp");
 hmw2->Write("hmw2");

 hrd->Write("hrd");
 oFile->Close();

 return;
}
