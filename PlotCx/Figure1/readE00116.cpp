TGraph* readE00116(int opt=1){

  //     x         Q^2         F2          i        stat        syst       dummy      dummy
       
  FILE *fp = fopen("data/e00116_f2p.txt","r");
  FILE *fd = fopen("data/e00116_f2d.txt","r");  
  int ncols, i, n1, n2;
  double dum1;
  double xp, q2p, f2p, statp, dum2;
  double xn, q2n, f2n, statn;  

  vector <double> x;
  vector <double> y;
  vector <double> ye;  
  i=0;
  n1=0;
  n2=0;
while (1) {
  i++;
  ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf", &xp, &q2p, &f2p, &dum1, &statp, &dum2, &dum1, &dum1);
  ncols = fscanf(fd,"%lf %lf %lf %lf %lf %lf %lf %lf", &xn, &q2n, &f2n, &dum1, &statn, &dum2, &dum1, &dum1);   
  if (ncols <= 0) break;
  cout << ncols << endl;
  cout << i <<"\t"<< xp << "\t"<< xn << endl;

  if(xp-xn>.0002){cout<<"These tables don't match fo xb"<<endl;cout<<xp<<"\t"<<xn<<endl;n1++;}
  if(q2p-q2n>0.002){cout<<"These tables don't match fo xb"<<endl;cout<<q2p<<"\t"<<q2n<<endl;n2++;}
  double err=sqrt(statp*statp/f2p/f2p+statn*statn/f2n/f2n);
  if(q2p>7.&&xp>0.5)
  {
    if(opt==1)    x.push_back(xp);
    if(opt==0)    x.push_back(q2p);
    if(opt==1||opt==0)  y.push_back(err*100.);
    if(opt==3)    y.push_back(q2p);
    if(opt==3)    x.push_back(xp);  
  }
  }
 cout << "i:"<<i<<"   n1:"<<n1<<"   n2:"<<n2<<endl;
 TGraph *g=new TGraph(x.size(), &x[0], &y[0]);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(.5);  
  g->SetMarkerColor(kBlue);
  g->SetLineColor(kBlue);
  // g->Draw("ap");
  return g;

 }
