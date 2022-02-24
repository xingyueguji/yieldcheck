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

void makeTable(){

  FILE *fp = fopen("globErr.txt","r");  
  FILE *fp2 = fopen("xsec_R_Table.txt","r");  
  //  FILE *fout = fopen("f2_data.txt");  
  Int_t ncols; 

  double spec, ang, xb, pion, density, cer, boil, kin, csb, acc, rad, tot, live, qerr, boilp2p;
  vector <double> spec_v, ang_v, xb_v, pion_v, density_v, cer_v, boil_v, kin_v, csb_v, acc_v, rad_v, tot_v, live_v, qerr_v, stat_v, boilp2p_v;
  char label[10];
  while (1) { 

    cout << "In while loop 1"<<endl;
    ncols = fscanf(fp,"%lf %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&spec,label,&xb,&pion,&density,&cer,&boil,&kin,&csb,&acc,&rad,&live,&qerr,&boilp2p, &tot);
    if (ncols < 0) break;
    //    if(abs(angle-ang) < .5 && arm == spec ){
      //      cout << "found a point"<<endl;
    if(label[0]=='r'){
    spec_v.push_back(spec);
    //    ang_v.push_back(ang);
    xb_v.push_back(xb);
    pion_v.push_back(pion);
    density_v.push_back(density);
    cer_v.push_back(cer);
    boil_v.push_back(boil);
    kin_v.push_back(kin);
    csb_v.push_back(csb);
    acc_v.push_back(acc);
    rad_v.push_back(rad);
    live_v.push_back(live);
    qerr_v.push_back(qerr);
    boilp2p_v.push_back(boilp2p);
    tot_v.push_back(tot);
    }
  }
  double ebeam, ep, thetac, q2, w2, nu, eps, flux, xb2, xsec, perr, gerr, delta, rat, raterr, stat;
  vector <double> ebeam_v, ep_v, thetac_v, q2_v, w2_v, nu_v, eps_v, flux_v, xb2_v, xsec_v, perr_v, gerr_v, delta_v, rat_v, raterr_v;
  vector <double> track_v, trigger_v;
  double track=sqrt(2*pow(.002,2));
  double trigger=sqrt(2*pow(.0003,2));
  while (1) { 
    cout << "In while loop 2"<<endl;
    ncols = fscanf(fp2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &ebeam, &ep, &thetac, &q2, &w2, &nu, &eps, &flux, &xb2, &xsec, &stat, &perr, &gerr, &delta, &rat, &raterr);
    if (ncols < 0) break;
    if(gerr>0)
      {

    if(abs(thetac-20.995)<.001)thetac=21.035;//HMS xsec quoted at SHMS angle
    perr=sqrt(perr*perr+0.0015*0.0015);
    ebeam_v.push_back(ebeam);
    ep_v.push_back(ep);
    thetac_v.push_back(thetac);
    q2_v.push_back(q2);
    w2_v.push_back(w2);
    nu_v.push_back(nu);
    eps_v.push_back(eps);
    flux_v.push_back(flux);
    xb2_v.push_back(xb2);
    xsec_v.push_back(xsec);
    stat_v.push_back(stat);
    perr_v.push_back(perr);
    gerr_v.push_back(gerr);
    delta_v.push_back(delta);
    rat_v.push_back(rat);
    raterr_v.push_back(raterr);
    track_v.push_back(track);
    trigger_v.push_back(trigger);
      }
  }

  int size1=tot_v.size();
  int size2=ebeam_v.size();
  cout << "There were "<<size1<<" points in the global text file"<<endl;
  cout << "There were "<<size2<<" points in the xsec text file"<<endl;
  /*
  for(int i=0;i<size1;i++){
    boilp2p=sqrt( pow(perr_v.at(i),2)-pow(stat_v.at(i),2) - pow(qerr_v.at(i),2) - 2*pow(0.0002,2) - 2*pow(0.002,2) );
    cout << pow(perr_v.at(i),2)-pow(stat_v.at(i),2) - pow(qerr_v.at(i),2) - 2*pow(0.0002,2) - 2*pow(0.002,2) <<"\t";
    cout << perr_v.at(i) << "\t"<<stat_v.at(i) << "\t"<<qerr_v.at(i) << "\t"<< - 2*pow(0.0002,2) - 2*pow(0.002,2) << endl;
    boilp2p_v.push_back(boilp2p);
  }
  */
  ofstream outFile;
  outFile.open("f2_data.txt",ios::app | ios::out );

    outFile << fixed << setprecision(5);

      outFile << setw(10) << " spec";
      outFile << setw(10) << " ebeam";
      outFile << setw(10) << " ep";
      outFile << setw(10) << " thetac";
      outFile << setw(10) << " xb";
      outFile << setw(10) << " q2";
      outFile << setw(10) << " w2";
      outFile << setw(10) << " xsec";
      // p2p errors
      outFile << setw(10) << " perr";
      outFile << setw(10) << " stat";
      //      outFile << setw(10) << " qerr";
      //      outFile << setw(10) << " boilp2p";
      //      outFile << setw(10) << " track";
      //      outFile << setw(10) << " trigger";
      // global
      outFile << setw(10) << " gerr";
      outFile << setw(10) << " density";
      outFile << setw(10) << " cer";
      //      outFile << setw(10) << " boil";
      outFile << setw(10) << " kin";
      outFile << setw(10) << " csb";
      outFile << setw(10) << " acc";
      outFile << setw(10) << " rad";
      outFile << setw(10) << " live";
      outFile << setw(10) << " pion";
      outFile<<endl;

    for(int i =0;i<size1;i++){
      /*
      outFile << setw(10) << spec_v.at(i);
      outFile << setw(10) << ang_v.at(i);
      outFile << setw(10) << xb_v.at(i);
      outFile << setw(10) << pion_v.at(i);
      outFile << setw(10) << density_v.at(i);
      outFile << setw(10) << cer_v.at(i);
      outFile << setw(10) << boil_v.at(i);
      outFile << setw(10) << kin_v.at(i);
      outFile << setw(10) << csb_v.at(i);
      outFile << setw(10) << acc_v.at(i);
      outFile << setw(10) << rad_v.at(i);
      outFile << setw(10) << live_v.at(i);
      outFile << setw(10) << qerr_v.at(i);
      outFile << setw(10) << tot_v.at(i);

      outFile << setw(10) << ebeam_v.at(i);
      outFile << setw(10) << ep_v.at(i);
      outFile << setw(10) << thetac_v.at(i);
      outFile << setw(10) << q2_v.at(i);
      outFile << setw(10) << w2_v.at(i);
      outFile << setw(10) << nu_v.at(i);
      outFile << setw(10) << eps_v.at(i);
      outFile << setw(10) << flux_v.at(i);
      outFile << setw(10) << xb2_v.at(i);
      outFile << setw(10) << xsec_v.at(i);
      outFile << setw(10) << stat_v.at(i);
      outFile << setw(10) << perr_v.at(i);
      outFile << setw(10) << gerr_v.at(i);
      outFile << setw(10) << delta_v.at(i);
      outFile << setw(10) << rat_v.at(i);
      outFile << setw(10) << raterr_v.at(i);
      */

      outFile << setw(10) << spec_v.at(i);
      outFile << setw(10) << ebeam_v.at(i);
      outFile << setw(10) << ep_v.at(i);
      outFile << setw(10) << thetac_v.at(i);
      outFile << setw(10) << xb_v.at(i);
      outFile << setw(10) << q2_v.at(i);
      outFile << setw(10) << w2_v.at(i);
      outFile << setw(10) << xsec_v.at(i);
      // p2p errors
      outFile << setw(10) << perr_v.at(i);
      outFile << setw(10) << stat_v.at(i);
      //      outFile << setw(10) << qerr_v.at(i);
      //      outFile << setw(10) << boilp2p_v.at(i);
      //      outFile << setw(10) << track_v.at(i);
      //      outFile << setw(10) << trigger_v.at(i);
      // global
      outFile << setw(10) << gerr_v.at(i);
      outFile << setw(10) << density_v.at(i);
      outFile << setw(10) << cer_v.at(i);
      //      outFile << setw(10) << boil_v.at(i);
      outFile << setw(10) << kin_v.at(i);
      outFile << setw(10) << csb_v.at(i);
      outFile << setw(10) << acc_v.at(i);
      outFile << setw(10) << rad_v.at(i);
      outFile << setw(10) << live_v.at(i);
      outFile << setw(10) << pion_v.at(i);
      outFile<<endl;

    }
    maxmin(w2_v, xsec_v,perr_v, "p2p err");
    maxmin(w2_v, xsec_v,stat_v, "stat err");
    maxmin(w2_v, xsec_v,qerr_v, "qerr err");
    maxmin(w2_v, xsec_v,boilp2p_v, "boilp2p err");
    maxmin(w2_v, xsec_v,track_v, "track err");
    maxmin(w2_v, xsec_v,trigger_v, "trigger err");

    maxmin(w2_v, xsec_v,gerr_v, "global err");
    maxmin(w2_v, xsec_v,density_v, "density err");
    maxmin(w2_v, xsec_v,cer_v, "cerenkov err");
    maxmin(w2_v, xsec_v,boil_v, "boiling err");
    maxmin(w2_v, xsec_v,csb_v, "csb err");
    maxmin(w2_v, xsec_v,kin_v, "kinematic err");
    maxmin(w2_v, xsec_v,acc_v, "acceptance err");
    maxmin(w2_v, xsec_v,rad_v, "radiative err");
    maxmin(w2_v, xsec_v,live_v, "livetime err");
    maxmin(w2_v, xsec_v,pion_v, "Pion Cont err");

    //    cout << "Max, Min p2p error: " << *max_element(perr_v.begin(),perr_v.end()) <<"\t"<<*min_element(perr_v.begin(),perr_v.end())<<endl;
  return;
}
