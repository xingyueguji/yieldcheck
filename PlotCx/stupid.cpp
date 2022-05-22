void stupid(double pmax=80., double perr=1, double werr=3.){
  vector <double> x,y;
  perr=perr/180.*TMath::Pi();
  werr=werr/180.*TMath::Pi();

  for(int i=-45; i<=45;i++){
    x.push_back(i);
    double ang=i/180.*TMath::Pi();
    double val=sqrt(pow(sin(ang)*perr,2)+pow(pmax*cos(ang)*werr,2));
    y.push_back(val);
  }
  int n=x.size();
  TGraph *g=new TGraphErrors(n,&x[0],&y[0]);
  g->SetMarkerStyle(33);
  g->Draw("ap");
  return;
}
