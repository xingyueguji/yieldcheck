

void compareRatios(string tgt="h",string angle="21", string mom="3p3",string spec="shms"){
  string kin=tgt+angle+"deg"+mom; 
  cout << "Kinematic is : "<<kin<<endl;
  Int_t DRAW=1;
  gROOT->ForceStyle();
  TFile *fm=new TFile(Form("../ratiosOut/pass303saved/%s_ratios%s.root",spec.c_str(),kin.c_str()));
  TH1F *hdd1=(TH1F*)fm->Get("hrd");
  hdd1->SetName("hdd1");
  hdd1->SetDirectory(0);

  TFile *fm2=new TFile(Form("../ratiosOut/pass251save/%s_ratios%s.root",spec.c_str(),kin.c_str()));
  TH1F *hdd2=(TH1F*)fm2->Get("hrd");
  hdd2->SetName("hdd2");
  hdd2->SetDirectory(0);

  TH1F *hrdm=(TH1F*)hdd1->Clone();
  hrdm->SetName("ratio");
  hrdm->Divide(hdd2);
  hrdm->GetYaxis()->SetRangeUser(.95,1.05);  
  hrdm->Draw();
 
 return;
}
