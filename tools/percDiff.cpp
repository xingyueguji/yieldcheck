//give two graphs and return a graph of differnce

TGraph *percDiff(TGraph *g1, TGraph *g2, string name){

  vector <double> xx,yy;
  int n;
  /////////////////////////////////////
  n=g1->GetN();
  for(int i=0; i<n;i++){
    double x1,y1;
    double x2,y2;
    g1->GetPoint(i,x1,y1);
    g2->GetPoint(i,x2,y2);
    xx.push_back(x1);
    yy.push_back( (y2-y1) / (y2) * 100.);
  }
  int pts=xx.size();
  TGraphErrors *gr=new TGraphErrors(pts,&xx[0],&yy[0]);
  gr->SetName(name.c_str());
  gr->SetMarkerStyle(33);
  return gr;
  }
