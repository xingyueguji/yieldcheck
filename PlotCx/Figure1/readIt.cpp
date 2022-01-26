TGraph* readIt(int opt=1){
  // I  J    x    Q¢2   F2d/F2p  dST  dSR  dN1  dN2  stat syst
   
  
  //  FILE *fp = fopen("data/sigma_d_whitlow.txt","r");
  FILE *fp = fopen("data/whitlow_dp.txt","r");  
  Int_t ncols,rn;
  Int_t dum1, dum2;
  Float_t e0, ep, theta, xb, q2, eps, w2, rci, sigma, stat, sys;

  vector <float> x;
  vector <float> y;
  vector <float> ye;  
  
while (1) {
  ncols = fscanf(fp,"%d %d %f %f %f %f %f %f %f %f %f", &dum1, &dum2, &xb, &q2, &sigma, &w2, &w2, &w2, &w2, &stat, &w2);
  if (ncols <= 0) break;
  cout << ncols << endl;
  if(q2>7.&&xb>0.5)
  {
    if(opt==1)    x.push_back(xb);
    if(opt==0)    x.push_back(q2);
    if(opt==1||opt==0)  y.push_back(stat*100);
    if(opt==3)    y.push_back(q2);
    if(opt==3)    x.push_back(xb);  
    cout << "xb: "<<xb<<"   q2:"<<q2<<"   stat:"<<stat*100<<endl;
  }
  }

 TGraph *g=new TGraph(x.size(), &x[0], &y[0]);
  g->SetMarkerStyle(26);
  g->SetMarkerSize(.5);  
  g->SetMarkerColor(kGreen+2);
  g->SetLineColor(kGreen+2);
  // g->Draw("ap");
  return g;

 }
