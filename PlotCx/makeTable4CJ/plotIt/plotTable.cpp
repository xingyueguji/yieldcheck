#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
void  plotTable(){

  FILE *f = fopen("f2_data.txt","r");  
  Int_t ncols; 
  /*
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
      */
  double spec, ang, xb, pion, density, cer, boil, kin, csb, acc, rad, tot, live, qerr, boilp2p;
  vector <double> spec_v, ang_v, xb_v, pion_v, density_v, cer_v, boil_v, kin_v, csb_v, acc_v, rad_v, tot_v, live_v, qerr_v, stat_v, boilp2p_v;

  double ebeam, ep, thetac, q2, w2, nu, eps, flux, xb2, xsec, perr, gerr, delta, rat, raterr, stat;
  vector <double> ebeam_v, ep_v, thetac_v, q2_v, w2_v, nu_v, eps_v, flux_v, xb2_v, xsec_v, perr_v, gerr_v, delta_v, rat_v, raterr_v;
  vector <double> track_v, trigger_v;

  while (1) { 
    ncols = fscanf(f,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ",&spec, &ebeam, &ep, &thetac,&xb,&q2, &w2, &xsec, &perr, &stat);
    ncols = fscanf(f,"%lf %lf %lf %lf %lf %lf %lf %lf %lf ",&gerr, &density, &cer, &kin, &csb, &acc, &rad, &live, &pion);    
    if (ncols < 0) break;
    xb_v.push_back(xb);
    q2_v.push_back(q2);
    stat_v.push_back(stat*100.);    
    cout << xb <<"\t"<<q2<<"\t"<<stat<<endl;
  }
  int size=xb_v.size();

  TGraph* g1=new TGraph(size,&xb_v[0],&stat_v[0]);
  TGraph* g2=new TGraph(size,&q2_v[0],&stat_v[0]);
  TGraph* g3=new TGraph(size,&xb_v[0],&q2_v[0]);  
  g1->SetMarkerStyle(33);
  g2->SetMarkerStyle(33);
  g3->SetMarkerStyle(33);  
  g1->GetYaxis()->SetRangeUser(0,80);
  g2->GetYaxis()->SetRangeUser(0,80);
  g3->GetYaxis()->SetRangeUser(0,20);

  g1->GetYaxis()->SetTitle("Uncertainity (%)");  
  g2->GetYaxis()->SetTitle("Uncertainity (%)");
  g3->GetYaxis()->SetTitle("Q2 (GeV^2)");
  g1->GetXaxis()->SetTitle("X_B");
  g2->GetXaxis()->SetTitle("X_B");
  g3->GetXaxis()->SetTitle("X_B");
  
  TCanvas *c1=new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  TPad * pad1 = new TPad("pad1","pad1",0,0.52,1,1);
  TPad * pad2 = new TPad("pad2","pad2",0,0.02,1,0.48);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  g1->Draw("ap");
  pad2->cd();
  gPad->cd(2);
  g2->Draw("ap");  
  c1->cd(2);
  g3->Draw("ap");    
  return;
}
