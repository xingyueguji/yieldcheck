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

void compareData(string tgt="h",string angle="21", string mom="3p3",string spec="shms"){

  //  string what="New Cherenkov / Old Cherenkov";
  string what="(- 0.45 mr beam angle) / (no offset)";
  string kin=tgt+angle+"deg"+mom; 
 TFile *fd1=new TFile(Form("dataYieldOut/pass49/%s_dataYield_%s.root",spec.c_str(),kin.c_str()));
 TH1F *hdd1=(TH1F*)fd1->Get("hdd");
 TH1F *hdy1=(TH1F*)fd1->Get("hyd");
 TH1F *hdxp1=(TH1F*)fd1->Get("hxpd");
 TH1F *hdyp1=(TH1F*)fd1->Get("hypd");
 TH1F *hdw21=(TH1F*)fd1->Get("hw2d_calc");

 TFile *fd2=new TFile(Form("dataYieldOut/pass50/%s_dataYield_%s.root",spec.c_str(),kin.c_str()));
 TH1F *hdd2=(TH1F*)fd2->Get("hdd");
 TH1F *hdy2=(TH1F*)fd2->Get("hyd");
 TH1F *hdxp2=(TH1F*)fd2->Get("hxpd");
 TH1F *hdyp2=(TH1F*)fd2->Get("hypd");
 TH1F *hdw22=(TH1F*)fd2->Get("hw2d_calc");


 hdd1->Divide(hdd2);
 hdy1->Divide(hdy2);
 hdxp1->Divide(hdxp2);
 hdyp1->Divide(hdyp2);
 hdw21->Divide(hdw22);
 // TH1F *hsys=(TH1F*)fd->Get("herrBand");
 // TH1F *hsysR=(TH1F*)fd->Get("herrBandR");

 hdd1->GetYaxis()->SetRangeUser(.95,1.05);
 hdy1->GetYaxis()->SetRangeUser(.95,1.05);
 hdxp1->GetYaxis()->SetRangeUser(.95,1.05);
 hdyp1->GetYaxis()->SetRangeUser(.95,1.05);
 hdw21->GetYaxis()->SetRangeUser(.95,1.05);

 hdd1->GetXaxis()->SetRangeUser(-10,22);
 hdy1->GetXaxis()->SetRangeUser(-5.,5.);
 hdxp1->GetXaxis()->SetRangeUser(-100,100);
 hdyp1->GetXaxis()->SetRangeUser(-50,50);
 hdw21->GetXaxis()->SetRangeUser(0,15);

 hdd1->SetMarkerStyle(33);
 hdy1->SetMarkerStyle(33);
 hdxp1->SetMarkerStyle(33);
 hdyp1->SetMarkerStyle(33);
 hdw21->SetMarkerStyle(33);

 TCanvas *c1=new TCanvas();
 c1->Divide(2,3);
 c1->cd(1);
 hdd1->Draw("HIST p");
 c1->cd(2);
 hdy1->Draw("HIST p");
 c1->cd(3);
 hdxp1->Draw("HIST p");
 c1->cd(4);
 hdyp1->Draw("HIST p");
 c1->cd(5);
 hdw21->Draw("HIST p");
 c1->cd(6);
 TPaveText *t=new TPaveText(.1,.1,.9,.9);
 t->AddText(what.c_str());
 t->AddText(kin.c_str());
 t->Draw();
 return;

}
