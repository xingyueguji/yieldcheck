

TGraph* getGlob(double angle, string spect, string what, string name, double col=1, double marker=20)
{
  FILE *fp = fopen("globErr.txt","r");  
  Int_t ncols; 
  int arm=1;
  if (spect=="hms")arm=0;
  double spec, ang, xb, pion, density, cer, boil, kin, csb, acc, rad, tot, live, qerr, boilp2p;
  //  ofile << spec_flag <<"\t"<<ang<<"\t"<<xb<<"\t";
  //  ofile <<  pion_err  <<"\t"<<density_err<<"\t"<<cer_err<<"\t"<<boil_err<<"\t"<<kin_err<<"\t"<<csb_err<<"\t"<<acc_err<<"\t"<<rad_err<<"\t"<< result << endl;

  vector <double> x;
  vector <double> y;
  while (1) { 
    ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&spec,&ang,&xb,&pion,&density,&cer,&boil,&kin,&csb,&acc,&rad,&live,&qerr,&boilp2p, &tot);

    if (ncols < 0) break;
    if(abs(angle-ang) < .5 && arm == spec ){
      //      cout << "found a point"<<endl;
      x.push_back(xb);
      if(what=="pion")y.push_back(100.*pion);
      if(what=="density")y.push_back(100.*density);
      if(what=="cer")y.push_back(100.*cer);
      if(what=="boil")y.push_back(100.*boil);
      if(what=="kin")y.push_back(100.*kin);
      if(what=="csb")y.push_back(100.*csb);
      if(what=="acc")y.push_back(100.*acc);
      if(what=="rad")y.push_back(100.*rad);
      if(what=="tot")y.push_back(100.*tot);
      if(what=="live")y.push_back(100.*live);

    }
  }

  TGraph *g=new TGraph(x.size(),&x[0],&y[0]);
  g->SetMarkerStyle(marker);
  g->SetMarkerColor(col);
  g->SetName(name.c_str());
  return g;
}
