TH1F * makeSmallerHisto(TH1D *hold){
  // take a histo with 60 bins from -30,30
  //and make 32 bins from -10,22
  TH1F *hnew= new TH1F("hnew","hdd",32,-10,22);
  double delta=0;
  double wt=0;
  double err=0;
  for(int i=21; i<53; i++)
    {
      delta=-9.5+(i-21);
      wt=hold->GetBinContent(i);
      err=hold->GetBinError(i);
      cout << delta<<"\t"<<wt<<"\t"<<err<<endl;

      hnew->Fill(delta ,wt);
      hnew->SetBinError(i-20,err);
    }
  return hnew;
}
