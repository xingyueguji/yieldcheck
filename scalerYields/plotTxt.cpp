void plotTxt(){

  gStyle->SetOptFit();
  gStyle->SetOptTitle(0);
  FILE *fp = fopen("data.txt","r"); 

  Int_t ncols,rn; 
  double rr, qq, ee;
  vector <float> run, qny, err;

  while (1) { 
    ncols = fscanf(fp,"%lf %lf %lf",&rr, &qq, &ee);
    if (ncols < 0) break;
    run.push_back(rr);
    qny.push_back(qq);
    err.push_back(ee);
    cout << rr<<"\t"<<qq<<"\t"<<ee<<endl;
  }

  int n=run.size();
  TGraphErrors *g1=new TGraphErrors(n, &run[0], &qny[0], 0, &err[0]);
  TGraphErrors *g2=new TGraphErrors(2, &run[0], &qny[0], 0, &err[0]);
  TGraphErrors *g3=new TGraphErrors(n-2, &run[2], &qny[2], 0, &err[2]);

  g1->Draw("ap");

  g1->GetYaxis()->SetTitle("pTRIG1.scalerCut / BCM4C.scalerChargeCut");
  g1->GetXaxis()->SetTitle("Run Number");

  g2->Draw("sp");
  g3->Draw("sp");

  g2->Fit("pol0");
  g3->Fit("pol0");
  return;
}
