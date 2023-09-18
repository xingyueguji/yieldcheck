TGraphErrors* readIt(){
  // I  J    x    Q¢2   F2d/F2p  dST  dSR  dN1  dN2  stat syst
   

  FILE *fp = fopen("src/whitlow/data.txt","r");
  Int_t ncols,rn;
  Int_t dum1, dum2;
  Float_t xb,q2, rat, stat, sys, dst, dsr, dn1, dn2;

  vector <float> x;
  vector <float> y;
  vector <float> ye;  
  
while (1) {
  ncols = fscanf(fp,"%d %d %f %f %f %f %f %f %f %f %f", &dum1, &dum2, &xb, &q2, &rat, &dst, &dsr, &dn1, &dn2, &stat, &sys); 
  if (ncols == 0) break;
  //  cout << ncols << endl;
  //  if(q2 < 5.2 && q2 > 3.39 && xb > .2 && xb < .4){
  if(q2 > 3.39 && q2 < 8.25){
    x.push_back(xb);
    y.push_back(rat);
    ye.push_back(rat*stat);
  }
 }

 TGraphErrors *g=new TGraphErrors(x.size(), &x[0], &y[0], 0, &ye[0]);
  g->SetMarkerStyle(43);
  g->SetMarkerColor(kOrange+2);
  g->SetLineColor(kOrange+2);
  // g->Draw("ap");
  return g;

 }
