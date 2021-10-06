double scalerYield(int run=2802,int opt=0){
  ofstream outFile;
  outFile.open("qny_pTrig3_d33deg1p7.txt",ios::app | ios::out );

  double scaler, charge;
  double qny, error;
  TString froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3d-shms-data/shms_replay_production_%d_-1.root",run);

  if (gSystem->AccessPathName(froot)==0)
    {
      TFile *f=new TFile(froot);
      f->Print();
      TTree *tr=(TTree*)f->Get("TSP");
      //P.pTRIG2.scalerCut
      //P.BCM4C.scalerChargeCut
      tr->SetBranchAddress("P.pTRIG3.scalerCut",&scaler);
      tr->SetBranchAddress("P.BCM4C.scalerChargeCut",&charge);
      Int_t nev=tr->GetEntries();
      for (int i=0;i<nev;i++)tr->GetEntry(i);
      cout << "The QNY is "<<scaler/charge<<" +/- " << sqrt(scaler)/charge <<endl;

    }
  qny=scaler/charge;
  error=sqrt(scaler)/charge;
  double val=qny;
  if(opt!=0)val=error;

  outFile << run <<"\t"<< qny <<"\t"<< error << endl;
  outFile.close();
  return val;
}
