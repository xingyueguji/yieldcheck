
TGraphErrors* makeGr(string fname="xsec_0.txt",double shms=1, Int_t xval=1, Int_t yval=1){
  vector <double>x;
  vector <double>y;

  FILE *fp = fopen(fname.c_str(),"r");  

  double ebeam, ep, theta, q2, w2, nu, eps, flux, xb, xsec, perr;
  Int_t ncols; 

  while (1) { 
    ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &ebeam, &ep, &theta, &q2, &w2, &nu, &eps, &flux, &xb, &xsec, &perr);
    if (ncols < 0) break;
    if((shms==1 && theta > 21.) || (shms==0. && theta < 21.)){
    x.push_back(xb);
    y.push_back(xsec);
    }
  }

  
  Int_t pts=x.size();
  TGraphErrors *g=new TGraphErrors(pts,&x[0],&y[0],0,0);
  //  g->SetMarkerStyle(20);
  //  g->Draw();
  return g;
}

