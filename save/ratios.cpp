#include "src/readReport.cpp"
#include "src/getCharge.cpp"

void ratios(string kin="h21deg3p3", Int_t AllCorr=1){
  Int_t DRAW=1;
  // histos
  // hm* MC
  // hd* Data
  // he* Dummy (empty)
  // hs* Data - dummy
cout << "AllCorr: "<< AllCorr<< endl;
gROOT->ForceStyle();

 TFile *fm=new TFile(Form("mcWtOut/mcWt%s.root",kin.c_str()));
TH1F *hmd=(TH1F*)fm->Get("delWt");
TH1F *hmy=(TH1F*)fm->Get("yWt");
TH1F *hmxp=(TH1F*)fm->Get("xpWt");
TH1F *hmyp=(TH1F*)fm->Get("ypWt");
TH1F *hmw2=(TH1F*)fm->Get("w2Wt");
//scaling by 50 because I had ngen hard coded 
// in mcWt.cpp to 1M.  shoud have been 50M
// hmd->Scale(1/50.);
// hmy->Scale(1/50.);
// hmxp->Scale(1/50.);
// hmyp->Scale(1/50.);
// hmw2->Scale(1/50.);

// TH1F *hdd, *hed;

 TFile *fd=new TFile(Form("dataYieldOut/dataYield_%s.root",kin.c_str()));
 //if(AllCorr==1)hdd=(TH1F*)fd->Get("hdelAllCorr");
 //if(AllCorr==0)hdd=(TH1F*)fd->Get("hdelSomeCorr");
TH1F *hdd=(TH1F*)fd->Get("hdd");
TH1F *hdy=(TH1F*)fd->Get("hyd");
TH1F *hdxp=(TH1F*)fd->Get("hxpd");
TH1F *hdyp=(TH1F*)fd->Get("hypd");
TH1F *hdw2=(TH1F*)fd->Get("hw2d");

 Float_t charge=0;
 Float_t charged=0;
 TFile *fdum;

  charge=getCharge(kin);

 if(kin=="h21deg2p7"||kin=="d21deg2p7"){
 charged+=readReport(2553,"BCM4C charge");
 charged+=readReport(2554,"BCM4C charge");
 fdum=new TFile("dataYieldOut/dataYield_2553_4.root");
 }

 if(kin=="h21deg3p3"||kin=="d21deg3p3"){
 charged+=readReport(2530,"BCM4C charge");
fdum=new TFile("dataYieldOut/dataYield_2530.root");
 }

 if(kin=="h21deg4p0"||kin=="d21deg4p0"){
 charged+=readReport(2517,"BCM4C charge");
fdum=new TFile("dataYieldOut/dataYield_2517.root");
 }

 if(kin=="h21deg5p1"||kin=="d21deg5p1"){
 charged+=readReport(2489,"BCM4C charge");
 fdum=new TFile("dataYieldOut/dataYield_2489.root");
 }

charge=charge/1000.;
 hdd->Scale(1./charge);
 hdy->Scale(1./charge);
 hdxp->Scale(1./charge);
 hdyp->Scale(1./charge);
 hdw2->Scale(1./charge);

 charge=0;


//if (AllCorr==1)hed=(TH1F*)fdum->Get("hdelAllCorr");
//if (AllCorr==0)hed=(TH1F*)fdum->Get("hdelSomeCorr");
TH1F *hed=(TH1F*)fdum->Get("hdd");
TH1F *hey=(TH1F*)fdum->Get("hyd");
TH1F *hexp=(TH1F*)fdum->Get("hxpd");
TH1F *heyp=(TH1F*)fdum->Get("hypd");
TH1F *hew2=(TH1F*)fdum->Get("hw2d");

 hed->Scale(1./charged*1000.);
 hey->Scale(1./charged*1000.);
 hexp->Scale(1./charged*1000.);
 heyp->Scale(1./charged*1000.);
 hew2->Scale(1./charged*1000.);

// Clone data histos
TH1F *hsd=(TH1F*)hdd->Clone();
TH1F *hsy=(TH1F*)hdy->Clone();
TH1F *hsxp=(TH1F*)hdxp->Clone();
TH1F *hsyp=(TH1F*)hdyp->Clone();
TH1F *hsw2=(TH1F*)hdw2->Clone();
 cout <<"d data="<<hsd->Integral()<<endl;
 cout <<"y data="<<hsy->Integral()<<endl;
 cout <<"yp data="<<hsyp->Integral()<<endl;
   cout <<"xp data="<<hsxp->Integral()<<endl;

   //   if(kin=="h21deg3p3"){   
   hed->Scale(1/3.789);
   hey->Scale(1/3.789);
   hexp->Scale(1/3.789);
   heyp->Scale(1/3.789);
   hew2->Scale(1/3.789);
   // }
 if(kin=="d21deg3p3"){
   hed->Scale(1/4.063);
   hey->Scale(1/4.063);
   hexp->Scale(1/4.063);
   heyp->Scale(1/4.063);
   hew2->Scale(1/4.063);
 }

hsd->Add(hed,-1);
hsy->Add(hey,-1);
hsxp->Add(hexp,-1);
hsyp->Add(heyp,-1);
hsw2->Add(hew2,-1);
 cout<<"After subtracting dummy"<<endl;
 cout <<"d data="<<hsd->Integral()<<endl;
 cout <<"y data="<<hsy->Integral()<<endl;
 cout <<"yp data="<<hsyp->Integral()<<endl;
   cout <<"xp data="<<hsxp->Integral()<<endl;
TH1F *hrd=(TH1F*)hsd->Clone();
hrd->SetTitle("Ratio Data/MC");
hmd->SetTitle("dp/p (%)");
hmy->SetTitle("Y_{tar} (cm)");
hmxp->SetTitle("X'_{tar} (mr)");
hmyp->SetTitle("Y'_{tar} (mr)");
hmw2->SetTitle("W2 (GeV^{2})");
hrd->Divide(hmd);

 // hr->Sumw2();

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

 hsd->SetLineColor(kBlue);
 hsy->SetLineColor(kBlue);
 hsxp->SetLineColor(kBlue);
 hsyp->SetLineColor(kBlue);
 hsw2->SetLineColor(kBlue);

 hed->SetLineColor(kMagenta);
 hey->SetLineColor(kMagenta);
 hexp->SetLineColor(kMagenta);
 heyp->SetLineColor(kMagenta);
 hew2->SetLineColor(kMagenta);

 hed->SetFillStyle(3003);
 hed->SetFillColor(kMagenta);
 hey->SetFillStyle(3003);
 hey->SetFillColor(kMagenta);
 hexp->SetFillStyle(3003);
 hexp->SetFillColor(kMagenta);
 heyp->SetFillStyle(3003);
 heyp->SetFillColor(kMagenta);
 hew2->SetFillStyle(3003);
 hew2->SetFillColor(kMagenta);

 // if(run==2525)hmd->GetYaxis()->SetRangeUser(0,1600);
 // if(run==2528)hmd->GetYaxis()->SetRangeUser(0,3000);
 // if(run==2540)hmd->GetYaxis()->SetRangeUser(0,900);
 hrd->GetYaxis()->SetRangeUser(0.8,1.2); 

 cout <<"d data="<<hsd->Integral()<<endl;
 cout <<"y data="<<hsy->Integral()<<endl;
 cout <<"yp data="<<hsyp->Integral()<<endl;
   cout <<"xp data="<<hsxp->Integral()<<endl;

 cout <<"d mc="<<hmd->Integral()<<endl;
 cout <<"y mc="<<hmy->Integral()<<endl;
 cout <<"yp mc="<<hmyp->Integral()<<endl;
   cout <<"xp mc="<<hmxp->Integral()<<endl;


 cout <<"d data/mc="<<hsd->Integral()/hmd->Integral()<<endl;
 cout <<"y data/mc="<<hsy->Integral()/hmy->Integral()<<endl;
 cout <<"yp data/mc="<<hsyp->Integral()/hmyp->Integral()<<endl;
 cout <<"xp data/mc="<<hsxp->Integral()/hmxp->Integral()<<endl;
   Double_t fact=hsd->Integral()/hmd->Integral();
 //  Double_t fact=1;

 if (DRAW==1)
   {
 hsd->Scale(1/fact);
 hsy->Scale(1/fact);
 hsxp->Scale(1/fact);
 hsyp->Scale(1/fact);
 TCanvas *c1=new TCanvas("c1","c1",600,900);
 c1->Divide(2,3);
 c1->cd(4);
 hmd->Draw("HIST E");
 hsd->Draw("HIST E same");
 // hdd->Draw("E same");
 hed->Draw("HIST E same");

 TLegend *leg=new TLegend(.1,.7,.75,.9);
 leg->AddEntry(hmd,"MC","lfp");
 // leg->AddEntry(hdd,"Data","lp");
 leg->AddEntry(hsd,"Data","lfp");
 leg->AddEntry(hed,"Dummy","lfp");
 leg->SetHeader(Form("Scale data/mc=%2.4f",fact));

 c1->cd(6);
 hrd->Draw();
 leg->Draw("same");
 c1->cd(1);
 hmy->Draw("HIST E");
 // hdy->Draw("same");
 hey->Draw("same HIST E");
 hsy->Draw("same HIST E");

 c1->cd(3);
 hmxp->Draw("HIST E");
 // hdxp->Draw("same");
 hexp->Draw("same HIST E");
 hsxp->Draw("same HIST E");

 c1->cd(2);
 hmyp->Draw("HIST E");
 // hdyp->Draw("same");
 heyp->Draw("same HIST E");
 hsyp->Draw("same HIST E");

 c1->cd(5);
 hmw2->Draw("HIST E");
 // hdw2->Draw("same");
 hew2->Draw("same HIST E");
 hsw2->Draw("same HIST E");

 TPaveText *pt=new TPaveText(0.0,.75,.3,1,"NDC");
 // if (run==2525) pt->AddText("H") ;
 // if (run==2528) pt->AddText("D");
 // if (run==2540) pt->AddText("C ");
 pt->AddText(kin.c_str());
 pt->SetFillColor(20);
 c1->cd(1);pt->Draw("BR");

 c1->SaveAs(Form("ratiosOut/ratios%s_%d.pdf",kin.c_str(),AllCorr));
   }

 TFile *oFile=new TFile(Form("ratiosOut/ratios%s_%d.root",kin.c_str(),AllCorr),"RECREATE");

 hdd->Write("hdd");
 hdy->Write("hdy");
 hdxp->Write("hdxp");
 hdyp->Write("hdyp");
 hdw2->Write("hdw2");

 hed->Write("hed");
 hey->Write("hey");
 hexp->Write("hexp");
 heyp->Write("heyp");
 hew2->Write("hew2");

 hsd->Write("hsd");
 hsy->Write("hsy");
 hsxp->Write("hsxp");
 hsyp->Write("hsyp");
 hsw2->Write("hsw2");

 hmd->Write("hmd");
 hmy->Write("hmy");
 hmxp->Write("hmxp");
 hmyp->Write("hmyp");
 hmw2->Write("hmw2");

 hrd->Write("hrd");
 oFile->Close();


 
 cout<<fixed<<setprecision(4);
 cout <<endl<<"Delta Histigrams Integrals"<<endl;
 cout <<"Only trust this if DRAw=0"<<endl;
 cout << "RawData\t\tDummyt\t\tDummySub\t\tMC"<<endl;
 cout << hdd->Integral()<<"\t";
 cout << hed->Integral()<<"\t";
 cout << hsd->Integral()<<"\t";
 cout << hmd->Integral()<<endl;
 return;
}
