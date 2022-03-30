#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void maxmin(vector <double> w2, vector <double> xsec, vector <double> v, TString name)
{
  double max,min;
  max=0.;
  min=100;
  int size=v.size();
  for (int i=0;i<size;i++){
    if(xsec.at(i)<1.15 && w2.at(i)>4){
      double val=v.at(i);
      if(val>max)max=val;
      if(val<min)min=val;
    }
  }
  cout << setw(10)<<max<<"\t"<<setw(10)<<min<<"\t";
  cout <<"Max and Min for "<<name<<endl;

}

void compare(){

  FILE *fp = fopen("../f2_data.txt","r");  
  FILE *fp2 = fopen("f2_data_308all.txt","r");  
  //  FILE *fout = fopen("f2_data.txt");  
  Int_t ncols; 
  //      spec     ebeam        ep    thetac        xb        q2        w2      xsec      perr      stat      gerr   density       cer       kin       csb       acc       rad      live      pion

  double spec, ebeam, ep, xb, theta, q2, w2, xsec, perr, stat, gerr, density, cer, kin, csb, acc, rad, live, pion;
  double spec2, ebeam2, ep2, xb2, theta2, q22, w22, xsec2, perr2, stat2, gerr2, density2, cer2, kin2, csb2, acc2, rad2, live2, pion2;
  vector <double> spec_v, ebeam_v, ep_v, xb_v, theta_v, q2_v, w2_v, xsec_v, perr_v, stat_v, gerr_v, density_v, cer_v, kin_v, csb_v, acc_v, rad_v, live_v, pion_v;
  vector <double> spec2_v, ebeam2_v, ep2_v, xb2_v, theta2_v, q22_v, w22_v, xsec2_v, perr2_v, stat2_v, gerr2_v, density2_v, cer2_v, kin2_v, csb2_v, acc2_v, rad2_v, live2_v, pion2_v;
  vector <double> spec3_v, ebeam3_v, ep3_v, xb3_v, theta3_v, q33_v, w33_v, xsec3_v, perr3_v, stat3_v, gerr3_v, density3_v, cer3_v, kin3_v, csb3_v, acc3_v, rad3_v, live3_v, pion3_v;
  int xx;
  while (1) { 
    ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&spec, &ebeam, &ep, &theta, &xb, &q2, &w2, &xsec, &perr, &stat, &gerr, &density, &cer, &kin, &csb, &acc, &rad, &live, &pion);
    //    cout <<ncols<<endl;
    //    cin >> xx;
    if (ncols <= 0) break;
    //    if(abs(angle-ang) < .5 && arm == spec ){
      //      cout << "found a point"<<endl;
    spec_v.push_back(spec);
    ebeam_v.push_back(ebeam);
    ep_v.push_back(ep);
    xb_v.push_back(xb);
    theta_v.push_back(theta);
    q2_v.push_back(q2);
    w2_v.push_back(w2);
    xsec_v.push_back(xsec);
    perr_v.push_back(perr);
    stat_v.push_back(stat);
    gerr_v.push_back(gerr);
    density_v.push_back(density);
    cer_v.push_back(cer);
    kin_v.push_back(kin);
    csb_v.push_back(csb);
    acc_v.push_back(acc);
    rad_v.push_back(rad);
    live_v.push_back(live);
    pion_v.push_back(pion);
    }
  int c1=0;
  int c2=0;
  int c3=0;
  int c4=0;
  int c5=0;
  int c6=0;

  while (1) { 
    ncols = fscanf(fp2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&spec2, &ebeam2, &ep2, &theta2, &xb2, &q22, &w22, &xsec2, &perr2, &stat2, &gerr2, &density2, &cer2, &kin2, &csb2, &acc2, &rad2, &live2, &pion2);
    if (ncols <= 0) break;
    //    if(abs(angle-ang) < .5 && arm == spec ){
      //      cout << "found a point"<<endl;

    spec2_v.push_back(spec2);
    ebeam2_v.push_back(ebeam2);
    ep2_v.push_back(ep2);
    xb2_v.push_back(xb2);
    theta2_v.push_back(theta2);
    q22_v.push_back(q22);
    w22_v.push_back(w22);
    xsec2_v.push_back(xsec2);
    perr2_v.push_back(perr2);
    stat2_v.push_back(stat2);
    gerr2_v.push_back(gerr2);
    density2_v.push_back(density2);
    cer2_v.push_back(cer2);
    kin2_v.push_back(kin2);
    csb2_v.push_back(csb2);
    acc2_v.push_back(acc2);
    rad2_v.push_back(rad2);
    live2_v.push_back(live2);
    pion2_v.push_back(pion2);
    if(spec2==0.0)c1++;
    if(spec2!=0){
      cout <<theta2-21.0<<endl; 
      if(abs(theta2-21.0) < 1.)c2++;
      if(abs(theta2-25.0) < 1.)c3++;
      if(abs(theta2-29.0) < 1.)c4++;
      if(abs(theta2-33.0) < 1.)c5++;
      if(abs(theta2-39.0) < 1.)c6++;
    }

 }
 
  int size1=xb_v.size();
  int size2=xb2_v.size();
  cout << "There were "<<size1<<" points in the file 1"<<endl;
  cout << "There were "<<size2<<" points in the file 2"<<endl;
  /*
  for(int i=0;i<size1;i++){
    boilp2p=sqrt( pow(perr_v.at(i),2)-pow(stat_v.at(i),2) - pow(qerr_v.at(i),2) - 2*pow(0.0002,2) - 2*pow(0.002,2) );
    cout << pow(perr_v.at(i),2)-pow(stat_v.at(i),2) - pow(qerr_v.at(i),2) - 2*pow(0.0002,2) - 2*pow(0.002,2) <<"\t";
    cout << perr_v.at(i) << "\t"<<stat_v.at(i) << "\t"<<qerr_v.at(i) << "\t"<< - 2*pow(0.0002,2) - 2*pow(0.002,2) << endl;
    boilp2p_v.push_back(boilp2p);
  }
  */
    for(int i =0;i<size1;i++){
      xsec3_v.push_back((xsec_v.at(i)-xsec2_v.at(i))/xsec_v.at(i)*100.);
      cout << xb_v.at(i)<<"\t"<<xb2_v.at(i)<<"\t"<<((xsec_v.at(i)-xsec2_v.at(i))/xsec_v.at(i)*100.)<<endl;

    }
    cout << "c1 "<< c1 <<endl;
    cout << "c2 "<< c2 <<endl;
    cout << "c3 "<< c3 <<endl;
    cout << "c4 "<< c4 <<endl;
    cout << "c5 "<< c5 <<endl;
    cout << "c6 "<< c6 <<endl;
    /*
c1 69
c2 123
c3 122
c4 121
c5 119
c6 122
    */
  int start=0;
  TGraph *g=new TGraph(c1,&xb_v[start],&xsec3_v[start]);
  start=start+c1;
  TGraph *g2=new TGraph(c2,&xb_v[start],&xsec3_v[start]);
  start=start+c2;
  TGraph *g3=new TGraph(c3,&xb_v[start],&xsec3_v[start]);
  start=start+c3;
  TGraph *g4=new TGraph(c4,&xb_v[start],&xsec3_v[start]);
  start=start+c4;
  TGraph *g5=new TGraph(c5,&xb_v[start],&xsec3_v[start]);
  start=start+c5;
  TGraph *g6=new TGraph(c6,&xb_v[start],&xsec3_v[start]);


    g->SetMarkerStyle(33);
    g2->SetMarkerStyle(33);
    g3->SetMarkerStyle(33);
    g4->SetMarkerStyle(33);
    g5->SetMarkerStyle(33);
    g6->SetMarkerStyle(33);

    g2->SetMarkerColor(kRed);
    g3->SetMarkerColor(kBlue);
    g4->SetMarkerColor(kGreen+3);
    g5->SetMarkerColor(kOrange+3);
    g6->SetMarkerColor(kViolet);

    g->GetYaxis()->SetRangeUser(-15,15);
    TAxis* ax=g->GetXaxis();
    ax->SetLimits(0,1);

    g->Draw("ap");

    g2->Draw("sp");
    g3->Draw("sp");
    g4->Draw("sp");
    g5->Draw("sp");
    g6->Draw("sp");

    //    cout << "Max, Min p2p error: " << *max_element(perr_v.begin(),perr_v.end()) <<"\t"<<*min_element(perr_v.begin(),perr_v.end())<<endl;
  return;
}
