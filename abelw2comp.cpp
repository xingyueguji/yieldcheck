//#include "src/getAngle.cpp"

TGraphErrors* abelw2comp(string ang="21",string tgt="h"){

  double angle=getAngle(ang,"shms");
  FILE *file;

  if(tgt=="h")file = fopen("abelsData/h.dat","r");  
  if(tgt=="d")file = fopen("abelsData/d.dat","r");  

  double e, th, q2, xb, w2, xsec, stat, xsecmod, p2pmod, sysmod;
  //Ebeam  Theta       x          Q2          W2         xsec       staterr   xsec/model  p2perr/model sys/model
  int ncols;
  vector <double> y, ye, x;

  while (1) { 
    ncols = fscanf(file,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &e, &th, &xb, &q2, &w2, &xsec, &stat, &xsecmod, &p2pmod, &sysmod);
    if (ncols < 0) break;
    if(abs(angle-th)<.1){
      cout << "hey" <<endl;
      y.push_back(xsecmod);
      x.push_back(w2);
      double model=xsec/xsecmod;
      double error=stat/model;
      ye.push_back(error);
      //ye.push_back(stat);
    }
  }
  int npts=y.size();
  //  TGraphErrors *g=new TGraphErrors(npts,&x[0],&y[0],0,&ye[0]);
  TGraphErrors *g=new TGraphErrors(npts,&x[0],&y[0],0,&ye[0]);
  return g;
}
