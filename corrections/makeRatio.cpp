TGraphErrors* makeRatio(TGraphErrors* g1=0,TGraphErrors* g2=0){

  const int n=g1->GetN();
  double x1,y1, x2,y2;
  vector <double> x;
  vector <double> y;

  for(int i=0;i<n;i++)
    {
      g1->GetPoint(i,x1,y1);
      g2->GetPoint(i,x2,y2);
      x.push_back(x1);
      y.push_back(y1/y2);
      cout << x1 << "\t" << y1 <<"\t" << y2<<"\t" << y1/y2<<endl;
    }
  TGraphErrors *g=new TGraphErrors(n,&x[0],&y[0],0,0);
  return g;
}
