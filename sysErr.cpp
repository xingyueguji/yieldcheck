
void ratios(string tgt="h",string angle="39", string mom="1p3",Int_t AllCorr=1){
  string kin=tgt+angle+"deg"+mom; 
  cout << "Kinematic is : "<<kin<<endl;

  TFile *f=new TFile(Form("dataYieldOut/pass8/dataYield_%s.root",kin.c_str()));
  TTree *tr=(TTree*)f->Get("tree);

tr->SetBranchAddress(
