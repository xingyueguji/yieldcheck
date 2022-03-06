void compMc(){

 TFile *fm=new TFile("mcWtOut/pass65/shms_mcWth21deg3p3.root");
 TH1F *h65=(TH1F*)fm->Get("delWt")->Clone();
 h65->SetName("h65");
 h65->SetDirectory(0);

 fm=new TFile("mcWtOut/pass65/shms_mcWtd21deg3p3.root");
 TH1F *d65=(TH1F*)fm->Get("delWt")->Clone();
 d65->SetName("d65");
 d65->SetDirectory(0);

 fm=new TFile("mcWtOut/pass51/shms_mcWth21deg3p3.root");
 TH1F *h51=(TH1F*)fm->Get("delWt")->Clone();
 h51->SetName("h51");
 h51->SetDirectory(0);

 fm=new TFile("mcWtOut/pass51/shms_mcWtd21deg3p3.root");
 TH1F *d51=(TH1F*)fm->Get("delWt")->Clone();
 d51->SetName("d51");
 d51->SetDirectory(0);

 TH1F *hr=(TH1F*)h65->Clone();
 hr->SetName("hr");
 hr->SetDirectory(0);
 hr->Divide(h51);

 TH1F *dr=(TH1F*)d65->Clone();
 dr->SetName("dr");
 dr->SetDirectory(0);
 dr->Divide(d51);

 TH1F *doh65=(TH1F*)d65->Clone();
 doh65->SetName("doh65");
 doh65->SetDirectory(0);
 doh65->Divide(h65);

 TH1F *doh51=(TH1F*)d51->Clone();
 doh51->SetName("doh51");
 doh51->SetDirectory(0);
 doh51->Divide(h51);

 TH1F *dohr=(TH1F*)doh65->Clone();
 dohr->SetName("dohr");
 dohr->SetDirectory(0);
 dohr->Divide(doh51);


 hr->GetYaxis()->SetRangeUser(.95,1.05);
 dr->GetYaxis()->SetRangeUser(.95,1.05);
 dohr->GetYaxis()->SetRangeUser(.95,1.05);

 fm=new TFile("mcWtOut/pass65/shms_mcWth25deg2p5.root");
 TH1F *hh65=(TH1F*)fm->Get("delWt")->Clone();
 hh65->SetName("hh65");
 hh65->SetDirectory(0);

 fm=new TFile("mcWtOut/pass65/shms_mcWtd25deg2p5.root");
 TH1F *dd65=(TH1F*)fm->Get("delWt")->Clone();
 dd65->SetName("dd65");
 dd65->SetDirectory(0);

 fm=new TFile("mcWtOut/pass51/shms_mcWth25deg2p5.root");
 TH1F *hh51=(TH1F*)fm->Get("delWt")->Clone();
 hh51->SetName("hh51");
 hh51->SetDirectory(0);

 fm=new TFile("mcWtOut/pass51/shms_mcWtd25deg2p5.root");
 TH1F *dd51=(TH1F*)fm->Get("delWt")->Clone();
 dd51->SetName("dd51");
 dd51->SetDirectory(0);

 TH1F *hhr=(TH1F*)hh65->Clone();
 hhr->SetName("hhr");
 hhr->SetDirectory(0);
 hhr->Divide(hh51);

 TH1F *ddr=(TH1F*)dd65->Clone();
 ddr->SetName("ddr");
 ddr->SetDirectory(0);
 ddr->Divide(dd51);

 TH1F *ddoh65=(TH1F*)dd65->Clone();
 ddoh65->SetName("ddoh65");
 ddoh65->SetDirectory(0);
 ddoh65->Divide(hh65);

 TH1F *ddoh51=(TH1F*)dd51->Clone();
 ddoh51->SetName("ddoh51");
 ddoh51->SetDirectory(0);
 ddoh51->Divide(hh51);

 TH1F *ddohr=(TH1F*)ddoh65->Clone();
 ddohr->SetName("ddohr");
 ddohr->SetDirectory(0);
 ddohr->Divide(ddoh51);


 hhr->GetYaxis()->SetRangeUser(.95,1.05);
 ddr->GetYaxis()->SetRangeUser(.95,1.05);
 ddohr->GetYaxis()->SetRangeUser(.95,1.05);


 TCanvas *c1=new TCanvas();
 c1->Divide(3,2);
 c1->cd(1);
 hr->Draw();
 c1->cd(2);
 dr->Draw();
 c1->cd(3);
 dohr->Draw();
 c1->cd(4);
 hhr->Draw();
 c1->cd(5);
 ddr->Draw();
 c1->cd(6);
 ddohr->Draw();

 return;

}
