

void compareData(string tgt="h",string angle="29", string mom="3p0",string spec="shms"){
  string kin=tgt+angle+"deg"+mom; 
  cout << "Kinematic is : "<<kin<<endl;
  Int_t DRAW=1;
  gROOT->ForceStyle();
  TFile *fm=new TFile(Form("../dataYieldOut/pass51/%s_dataYield_%s.root",spec.c_str(),kin.c_str()));
  TH1F *hdd1=(TH1F*)fm->Get("hdd");
  hdd1->SetName("hdd1");
  hdd1->SetDirectory(0);

  TFile *fm2=new TFile(Form("../dataYieldOut/pass54/%s_dataYield_%s.root",spec.c_str(),kin.c_str()));
  TH1F *hdd2=(TH1F*)fm2->Get("hdd");
  hdd2->SetName("hdd2");
  hdd2->SetDirectory(0);

  TH1F *hboil=(TH1F*)fm2->Get("hBoilCorr");
  hboil->Divide(hdd2);
  double corr=hboil->GetBinContent(30);
  cout << "Going to scale by "<<1./corr<<" to add boiling"<<endl;
  hdd2->Scale(1./corr);
  
  TH1F *hrd=(TH1F*)hdd1->Clone();
  hrd->SetName("ratio");
  hrd->Divide(hdd2);
  hrd->GetYaxis()->SetRangeUser(.95,1.05);  
  hrd->Draw();
 
 return;
}
