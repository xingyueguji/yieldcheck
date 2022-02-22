
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

void compareMC(string tgt="h",string angle="29", string mom="3p0",string spec="shms"){
  string kin=tgt+angle+"deg"+mom; 
  cout << "Kinematic is : "<<kin<<endl;
  Int_t DRAW=1;
  gROOT->ForceStyle();
  TFile *fm=new TFile(Form("../mcWtOut/pass65/%s_mcWt%s.root",spec.c_str(),kin.c_str()));
 TH1F *hmd=(TH1F*)fm->Get("delWt");
 TH1F *hmy=(TH1F*)fm->Get("yWt");
 TH1F *hmxp=(TH1F*)fm->Get("xpWt");
 TH1F *hmyp=(TH1F*)fm->Get("ypWt");
 TH1F *hmw2=(TH1F*)fm->Get("w2Wt");

   TFile *fm2=new TFile(Form("../mcWtOut/pass64/%s_mcWt%s.root",spec.c_str(),kin.c_str()));
 TH1F *hmd2=(TH1F*)fm2->Get("delWt");
 TH1F *hmy2=(TH1F*)fm2->Get("yWt");
 TH1F *hmxp2=(TH1F*)fm2->Get("xpWt");
 TH1F *hmyp2=(TH1F*)fm2->Get("ypWt");
 TH1F *hmw22=(TH1F*)fm2->Get("w2Wt");

 TH1F *hrd=(TH1F*)hmd->Clone();
 hrd->SetName("ratio");
 hrd->Divide(hmd2);

 hrd->SetTitle("Ratio MC_60cm/MC_10cm");
 hmd->SetTitle("dp/p (%)");
 hmy->SetTitle("Y_{tar} (cm)");
 hmxp->SetTitle("X'_{tar} (mr)");
 hmyp->SetTitle("Y'_{tar} (mr)");
 hmw2->SetTitle("W2 (GeV^{2})");

 //  Foramatting

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

 hmd2->SetMarkerStyle(21);
 hmy2->SetMarkerStyle(21);
 hmxp2->SetMarkerStyle(21);
 hmyp2->SetMarkerStyle(21);
 hmw22->SetMarkerStyle(21);

 hmd2->SetMarkerSize(.5);
 hmy2->SetMarkerSize(.5);
 hmxp2->SetMarkerSize(.5);
 hmyp2->SetMarkerSize(.5);
 hmw22->SetMarkerSize(.5);

 hmd2->SetLineColor(kBlue);
 hmy2->SetLineColor(kBlue);
 hmxp2->SetLineColor(kBlue);
 hmyp2->SetLineColor(kBlue);
 hmw22->SetLineColor(kBlue);

 hmd2->SetMarkerColor(kBlue);
 hmy2->SetMarkerColor(kBlue);
 hmxp2->SetMarkerColor(kBlue);
 hmyp2->SetMarkerColor(kBlue);
 hmw22->SetMarkerColor(kBlue);

 hrd->GetYaxis()->SetRangeUser(0.95,1.05); 
 hmd->GetXaxis()->SetRangeUser(-11,23); 
 hmd->GetXaxis()->SetRangeUser(-11,23); 
 hmxp->GetXaxis()->SetRangeUser(-80,80); 
 hmyp->GetXaxis()->SetRangeUser(-50,50); 
 hmy->GetXaxis()->SetRangeUser(-6,6); 

 TCanvas *c1=new TCanvas("c1","c1",600,900);
 c1->Divide(2,3);
 c1->cd(4);
 hmd->Draw("HIST");
 hmd2->Draw("E same");

 TLegend *leg=new TLegend(.1,.6,.9,.9);
 leg->AddEntry(hmd,"recon_cosy_refit_1.576_60cm","lfp");
 leg->AddEntry(hmd2,"recon_cosy_refit_1.576","lfp");
 // hrd->GetXaxis()->SetRangeUser(-10,10);
 // hmd->GetXaxis()->SetRangeUser(-10,10);
     c1->cd(6);
     hrd->Draw();
     hrd->Fit("pol0");
     //     leg->Draw("same");
     c1->cd(1);
     hmy->Draw("HIST");
     fixRange(hmy);
     hmy2->Draw("same E");
     c1->cd(3);
     hmxp->Draw("HIST");
     fixRange(hmxp);
     hmxp2->Draw("same E");
     c1->cd(2);
     hmyp->Draw("HIST");
     fixRange(hmyp);
     hmyp2->Draw("same E");
     c1->cd(5);
     hmw2->Draw("HIST");
     fixRange(hmw2);
     hmw22->Draw("same E");

     TPaveText *pt=new TPaveText(0.38,.3,.58,.55,"NDC");
     pt->AddText(kin.c_str());
     //     pt->AddText("ELOG457");
     //     pt->AddText("no_offset ROOTfiles");
     //     pt->SetFillColor(20);
     c1->cd(2);pt->Draw("BR");
     c1->SaveAs(Form("%s_compMC%s.pdf",spec.c_str(),kin.c_str()));

 return;
}
