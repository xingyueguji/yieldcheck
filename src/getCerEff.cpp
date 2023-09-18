// function to return abishek's histogram
// of the noble gas cherenkov effiecieny
TH2F* getCerEff(Int_t effOrErr=0){
  TH2F* h;
  TFile *f=new TFile("ngcer_eff/model.root");
  if (effOrErr==0){
    h=(TH2F*)f->Get("histEff");}
  if (effOrErr==1){
    h=(TH2F*)f->Get("errhist");}
  return h;
}
