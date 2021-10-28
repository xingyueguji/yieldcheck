TGraph* readIt(int opt=1){
  // I  J    x    Q¢2   F2d/F2p  dST  dSR  dN1  dN2  stat syst
   

  FILE *fp = fopen("data/sigma_d_whitlow.txt","r");
  Int_t ncols,rn;
  Int_t dum1, dum2;
  Float_t e0, ep, theta, xb, q2, eps, w2, rci, sigma, stat, sys;

  vector <float> x;
  vector <float> y;
  vector <float> ye;  
  
while (1) {
  ncols = fscanf(fp,"%d %d %f %f %f %f %f %f %f %f %f %f %f", &dum1, &dum2, &e0, &ep, &theta, &xb, &q2, &eps, &w2, &rci, &sigma, &stat, &sys); 
  if (ncols <= 0) break;
  cout << ncols << endl;
  if(opt==1)    x.push_back(xb);
  if(opt==0)    x.push_back(q2);
    y.push_back(stat);
 }

 TGraph *g=new TGraph(x.size(), &x[0], &y[0]);
  g->SetMarkerStyle(43);
  g->SetMarkerColor(kOrange+2);
  g->SetLineColor(kOrange+2);
  // g->Draw("ap");
  return g;

 }
