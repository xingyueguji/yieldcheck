

TH1F* unc(string tgt="h",string angle="21", string mom="5p1",string spec="shms", string pass="pass38"){
  //  gStyle->SetOptStat(0);

  string hkin="h"+angle+"deg"+mom; 
  string dkin="d"+angle+"deg"+mom; 

  TFile *f36h=new TFile(Form("../mcWtOut/pass36/%s_mcWt%s.root",spec.c_str(),hkin.c_str()));

  TH1F *h36h=(TH1F*)f36h->Get("delWt");
  h36h->SetName("h36h");
  h36h->SetDirectory(0);
  f36h->Close();

  TFile *f36d=new TFile(Form("../mcWtOut/pass36/%s_mcWt%s.root",spec.c_str(),dkin.c_str()));
  TH1F *h36d=(TH1F*)f36d->Get("delWt");
  h36d->SetName("h36d");
  h36d->SetDirectory(0);
  f36d->Close();

  TFile *fModh=new TFile(Form("../mcWtOut/%s/%s_mcWt%s.root",pass.c_str(),spec.c_str(),hkin.c_str()));
  TH1F *hModh=(TH1F*)fModh->Get("delWt");
  hModh->SetName("hModh");
  hModh->SetDirectory(0);
  fModh->Close();

  TFile *fModd=new TFile(Form("../mcWtOut/%s/%s_mcWt%s.root",pass.c_str(),spec.c_str(),dkin.c_str()));
  TH1F *hModd=(TH1F*)fModd->Get("delWt");
  hModd->SetName("hModd");
  hModd->SetDirectory(0);
  fModd->Close();

  TH1F* hd=(TH1F*)hModd->Clone();
  hd->SetName("hd");
  hd->Divide(h36d);


  TH1F* hh=(TH1F*)hModh->Clone();
  hh->SetName("hh");
  hh->Divide(h36h);


  TH1F* hrMod=(TH1F*)hModd->Clone();
  hrMod->SetName("hrMod");
  hrMod->Divide(hModh);

  TH1F* hr36=(TH1F*)h36d->Clone();
  hr36->SetName("hr36");
  hr36->Divide(h36h);
  hrMod->Divide(hr36);

  TH1F *result;
  if (tgt=="h")result=hh;
  if (tgt=="d")result=hd;
  if (tgt=="r")result=hrMod;


  /*
  hh->GetYaxis()->SetRangeUser(.9,1.1);
  hh->GetXaxis()->SetRangeUser(-10,22);
  hh->Draw();
  hd->Draw("same");
  hrMod->Draw("same");
  */

  return result;

}

