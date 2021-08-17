{
  gStyle->SetTitleX(.1);
  gStyle->SetTitleW(.8);
  gStyle->SetOptStat(0);
  TFile *fo4p0=new TFile("with/hms_ratiosc21deg4p0.root");
  TH1D *ho4p0=(TH1D*)fo4p0->Get("hdd");
  ho4p0->SetName("ho4p0");

  TFile *fo4p5=new TFile("with/hms_ratiosc21deg4p5.root");
  TH1D *ho4p5=(TH1D*)fo4p5->Get("hdd");
  ho4p5->SetName("ho4p5");

  TFile *fo5p1=new TFile("with/hms_ratiosc21deg5p1.root");
  TH1D *ho5p1=(TH1D*)fo5p1->Get("hdd");
  ho5p1->SetName("ho5p1");

  TFile *fo5p7=new TFile("with/hms_ratiosc21deg5p7.root");
  TH1D *ho5p7=(TH1D*)fo5p7->Get("hdd");
  ho5p7->SetName("ho5p7");

  TFile *fn4p0=new TFile("without/hms_ratiosc21deg4p0.root");
  TH1D *hn4p0=(TH1D*)fn4p0->Get("hdd");
  hn4p0->SetName("hn4p0");

  TFile *fn4p5=new TFile("without/hms_ratiosc21deg4p5.root");
  TH1D *hn4p5=(TH1D*)fn4p5->Get("hdd");
  hn4p5->SetName("hn4p5");

  TFile *fn5p1=new TFile("without/hms_ratiosc21deg5p1.root");
  TH1D *hn5p1=(TH1D*)fn5p1->Get("hdd");
  hn5p1->SetName("hn5p1");

  TFile *fn5p7=new TFile("without/hms_ratiosc21deg5p7.root");
  TH1D *hn5p7=(TH1D*)fn5p7->Get("hdd");
  hn5p7->SetName("hn5p7");

  ho4p0->Add(hn4p0,-1);
  ho4p5->Add(hn4p5,-1);
  ho5p1->Add(hn5p1,-1);
  ho5p7->Add(hn5p7,-1);
  ho4p0->Divide(hn4p0);
  ho4p5->Divide(hn4p5);
  ho5p1->Divide(hn5p1);
  ho5p7->Divide(hn5p7);
  ho4p0->Scale(100.);
  ho4p5->Scale(100.);
  ho5p1->Scale(100.);
  ho5p7->Scale(100.);

  ho4p0->SetMarkerStyle(20);
  ho4p0->SetMarkerColor(kBlack);
  ho4p0->GetXaxis()->SetRangeUser(-6,9);
  ho4p0->GetYaxis()->SetRangeUser(-2,2);
  ho4p0->GetYaxis()->SetTitle("100*(w/ Corr. - w/o corr)/ w/o corr  (%)");
  ho4p0->GetXaxis()->SetTitle("Delta");
  ho4p0->SetTitle("HMS Carbon (hsatcorr flag on/off) ");

  ho4p5->SetMarkerStyle(20);
  ho4p5->SetMarkerColor(kMagenta);

  ho5p1->SetMarkerStyle(20);
  ho5p1->SetMarkerColor(kRed);


  ho5p7->SetMarkerStyle(20);
  ho5p7->SetMarkerColor(kBlue);

  TLegend *leg=new TLegend(.4,.7,.6,.9);
  leg->AddEntry(ho4p0,"4.0 Gev","p");
  leg->AddEntry(ho4p5,"4.5 Gev","p");
  leg->AddEntry(ho5p1,"5.1 Gev","p");
  //  leg->AddEntry(ho5p7,"5.7 Gev","p");

  ho4p0->Draw("HIST p");
  ho4p5->Draw("HIST same p");
  ho5p1->Draw("HIST same p");
  //  ho5p7->Draw("HIST same p");
  leg->Draw("same");

}
