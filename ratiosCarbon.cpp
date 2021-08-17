#include "src/readReport.cpp"

void ratiosCarbon(string kin="c21deg5p1", Int_t AllCorr=1){
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


 TFile *fd=new TFile(Form("dataYieldOut/dataYield_%s.root",kin.c_str()));
 TH1F *hdd=(TH1F*)fd->Get("hdd");
 TH1F *hdy=(TH1F*)fd->Get("hyd");
 TH1F *hdxp=(TH1F*)fd->Get("hxpd");
 TH1F *hdyp=(TH1F*)fd->Get("hypd");
 TH1F *hdw2=(TH1F*)fd->Get("hw2d");
 Float_t charge=0;

 if(kin=="c25deg2p5"){
 charge+=readReport(3083,"BCM4C charge");
 charge+=readReport(3084,"BCM4C charge");
 }

 if(kin=="c25deg3p0"){
 charge+=readReport(3070,"BCM4C charge");
 charge+=readReport(3071,"BCM4C charge");
 }

 if(kin=="c25deg3p5"){
 charge+=readReport(3057,"BCM4C charge");
 charge+=readReport(3058,"BCM4C charge");
 charge+=readReport(3059,"BCM4C charge");
 }

 if(kin=="c25deg4p4"){
 charge+=readReport(3035,"BCM4C charge");
 charge+=readReport(3036,"BCM4C charge");
 charge+=readReport(3037,"BCM4C charge");
 }

 if(kin=="c21deg2p7"){
 charge+=readReport(2547,"BCM4C charge");
 charge+=readReport(2548,"BCM4C charge");
 }

 if(kin=="c21deg3p3"){
 charge+=readReport(2540,"BCM4C charge");
 charge+=readReport(2541,"BCM4C charge");
 }

 if(kin=="c21deg4p0"){
 charge+=readReport(2509,"BCM4C charge");
 charge+=readReport(2510,"BCM4C charge");
 }

 if(kin=="c21deg5p1"){
 charge+=readReport(2507,"BCM4C charge");
 charge+=readReport(2508,"BCM4C charge");
 }

 charge=charge/1000;
 cout << "Total charge:"<<charge<<endl; 

 hdd->Scale(1/charge);
 hdy->Scale(1/charge);
 hdxp->Scale(1/charge);
 hdyp->Scale(1/charge);
 hdw2->Scale(1/charge);

 TH1F *hrd=(TH1F*)hdd->Clone();
 hrd->SetName("hrd");
hdd->SetTitle("Ratio Data/MC");
hmd->SetTitle("dp/p (%)");
hmy->SetTitle("Y_{tar}");
hmxp->SetTitle("X'_{tar}");
hmyp->SetTitle("Y'_{tar}");
hmw2->SetTitle("W2 (GeV^{2})");
hrd->Divide(hmd);
 hrd->Sumw2();
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

		    // if(run==2525)hmd->GetYaxis()->SetRangeUser(0,1600);
		    // if(run==2528)hmd->GetYaxis()->SetRangeUser(0,3000);
		    //if(run==2540)hmd->GetYaxis()->SetRangeUser(0,900);
 hrd->GetYaxis()->SetRangeUser(0.8,1.2); 
 hmd->GetYaxis()->SetTitle("Yield (counts/mC)");
 hrd->GetYaxis()->SetTitle("Ratio (data/MC)");
 hrd->GetXaxis()->SetTitle("SHMS #delta ");

 cout <<"data/mc="<<hdd->Integral()/hmd->Integral()<<endl;
 cout <<"data/mc="<<hdy->Integral()/hmy->Integral()<<endl;
 cout <<"data/mc="<<hdyp->Integral()/hmyp->Integral()<<endl;
 cout <<"data/mc="<<hdxp->Integral()/hmxp->Integral()<<endl;
 // Double_t fact=hdd->Integral()/hmd->Integral();
 Double_t fact=1;
		    	   
 if(DRAW==1){
 TCanvas *c1=new TCanvas("c1","c1",600,900);
 hdd->Scale(1/fact);
 hdy->Scale(1/fact);
 hdxp->Scale(1/fact);
 hdyp->Scale(1/fact);
 c1->Divide(2,3);
 c1->cd(4);
 hmd->Draw("HIST E");
 hdd->Draw("HIST E same");

 TLegend *leg=new TLegend(.1,.6,.75,.9);
 leg->AddEntry(hmd,"MC","lfp");
 // leg->AddEntry(hdd,"Data","lp");
 leg->AddEntry(hdd,"Data","lfp");
 // leg->AddEntry(hed,"Dummy","lfp");
 leg->SetHeader(Form("Scale data/mc=%2.4f",fact));

 c1->cd(6);
 hrd->Draw();
 leg->Draw("same");
 c1->cd(1);
 hmy->Draw("HIST E");
 hdy->Draw("same HIST E");

 c1->cd(3);
 hmxp->Draw("HIST E");
 hdxp->Draw("same HIST E");

 c1->cd(2);
 hmyp->Draw("HIST E");
 hdyp->Draw("same HIST E");
 c1->cd(5);
 hmw2->Draw("HIST E");
 // hdw2->Draw("same");
 hdw2->Draw("same HIST E");
 TPaveText *pt=new TPaveText(0.0,.75,.3,1,"NDC");
 // if (run==2525) pt->AddText("H") ;
 // if (run==2528) pt->AddText("D");
 // if (run==2540) pt->AddText("C ");
 pt->AddText("C ");
 pt->AddText("21deg 3.3 GeV");
 pt->SetFillColor(20);
 c1->cd(1);pt->Draw("BR");
 c1->SaveAs(Form("ratiosOut/ratios%s_%d.pdf",kin.c_str(),AllCorr));
 }
 
 
 TFile *oFile=new TFile(Form("ratiosOut/ratios%s_%d.root",kin.c_str(),AllCorr),"RECREATE");
 hrd->Write("hrd");
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

 oFile->Close();

 cout<<fixed<<setprecision(4);
 cout <<endl<<"Delta Histigrams Integrals"<<endl;
 cout <<"Only trust this if DRAw=0"<<endl;
 cout << "RawData\t\tDummyt\t\tDummySub\t\tMC"<<endl;
 cout << hdd->Integral()<<"\t";
 cout << hmd->Integral()<<endl;

 return;
}
