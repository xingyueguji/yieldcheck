#include <iostream>
#include "readIt.cpp"
#include "readE00116.cpp"
#include <algorithm>
#include <vector>

using namespace std;

Double_t myFun(double x){
  double mp2=0.9382723*0.9382723;
  
  Double_t res= (4.0 - mp2) / (1/x-1);
  return res;
}

void  figure(){
  //  gStyle->ForceStyle();
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetStatBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetTitleFillColor(0);
  //  gStyle->SetGridStyle(3);
  //  gStyle->SetTitleX(.5);
  //  gStyle->SetTitleW(.7);
  gStyle->SetOptTitle(0);
  //  gStyle->SetBorderSize(1);

  
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
    if(xb>0.5 && q2 >7)
    {
      xb_v.push_back(xb);
      q2_v.push_back(q2);
      stat_v.push_back(stat*100.);    
      cout << xb <<"\t"<<q2<<"\t"<<stat<<endl;
    }
  }
  int size=xb_v.size();

  TGraph* g1=new TGraph(size,&xb_v[0],&stat_v[0]);
  TGraph* g2=new TGraph(size,&q2_v[0],&stat_v[0]);
  TGraph* g3=new TGraph(size,&xb_v[0],&q2_v[0]);  

  g1->SetMarkerStyle(4);
  g2->SetMarkerStyle(4);
  g3->SetMarkerStyle(4);
  g1->SetMarkerColor(kRed);
  g2->SetMarkerColor(kRed);
  g3->SetMarkerColor(kRed);    
  g1->SetMarkerSize(.5);
  g2->SetMarkerSize(.5);
  g3->SetMarkerSize(.5);  

  g1->GetYaxis()->SetRangeUser(0,33);
  //  g2->GetYaxis()->SetRangeUser(0,30);
  g3->GetYaxis()->SetRangeUser(6,33);

  g1->GetXaxis()->SetRangeUser(0,1);
  //  g2->GetXaxis()->SetRangeUser(0,21);
  g3->GetXaxis()->SetRangeUser(0,1);  

  /*
  g1->GetYaxis()->SetRangeUser(0,25);
  g2->GetYaxis()->SetRangeUser(0,25);
  g3->GetYaxis()->SetRangeUser(7,20);

  g1->GetXaxis()->SetRangeUser(.5,1);
  g2->GetXaxis()->SetRangeUser(7,20);
  g3->GetXaxis()->SetRangeUser(.5,1);
  */
  g1->GetYaxis()->SetTitle("Uncertainity (%)");  
  g2->GetYaxis()->SetTitle("Uncertainity (%)");
  g3->GetYaxis()->SetTitle("Q^{2} (GeV^{2})");
  g1->GetXaxis()->SetTitle("Q^{2}");
  g2->GetXaxis()->SetTitle("X_{B}");
  g3->GetXaxis()->SetTitle("X_{B}");
  g1->GetYaxis()->SetTitleSize(.05);
  g2->GetYaxis()->SetTitleSize(.05);
  g3->GetYaxis()->SetTitleSize(.05);
  g1->GetXaxis()->SetTitleSize(.05);
  g2->GetXaxis()->SetTitleSize(.05);
  g3->GetXaxis()->SetTitleSize(.05);  
 g1->GetXaxis()->CenterTitle();
 g1->GetYaxis()->CenterTitle();
 g2->GetXaxis()->CenterTitle();
 g2->GetYaxis()->CenterTitle();
 g3->GetXaxis()->CenterTitle();
 g3->GetYaxis()->CenterTitle();

  g1->GetXaxis()->SetLabelOffset(3);


  g1->GetYaxis()->SetTitleOffset(.8);  
  g2->GetYaxis()->SetTitleOffset(.8);
  g3->GetYaxis()->SetTitleOffset(.8);

  g1->GetXaxis()->SetTitleOffset(3.0);
  g2->GetXaxis()->SetTitleOffset(1.);
  g3->GetXaxis()->SetTitleOffset(0.9);   

  g1->GetXaxis()->SetLabelSize(.05);
  g2->GetXaxis()->SetLabelSize(.05);
  g3->GetXaxis()->SetLabelSize(.05);
  g1->GetYaxis()->SetLabelSize(.05);
  g2->GetYaxis()->SetLabelSize(.05);
  g3->GetYaxis()->SetLabelSize(.05);    

  TGraph* g6gev1=readE00116(1);
  TGraph* g6gev2=readE00116(0);
  TGraph* g6gev3=readE00116(3);  

  TGraph *gwhit1=readIt(1);
  TGraph *gwhit2=readIt(0);
  TGraph *gwhit3=readIt(3);    

  TF1 *fun=new TF1("fun","(4.0 - pow(0.9382723,2))/(1/x-1)",0,1);
  //  TF1 *fun=new TF1("fun","myFun(x)",0.1,1.0);
  
  TCanvas *c1=new TCanvas("c1","c1",600,900);
  c1->SetGrayscale(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();

  
  //  c1->Divide(2,1,.005,.005);
  //  c1->cd(1);
  TLegend *leg=new TLegend(0.12,0.6,0.6,0.9);
  leg->AddEntry(g1,"This Work","p");
  leg->AddEntry(g6gev1,"E00-116 (JLab 6 GeV)","p");
  leg->AddEntry(gwhit1,"SLAC (Whitlow)","p");        


  TPad * pad1 = new TPad("pad1","pad1",0,0.5,1,1);
  TPad * pad2 = new TPad("pad2","pad2",0,0.02,1,0.5);
  pad1->SetFillColor(0);
  pad2->SetFillColor(0);  
  pad1->Draw();
  pad2->Draw();


  pad2->cd();
  //  gPad->SetBottomMargin(.13);
  //  gPad->SetRightMargin(.05);
    gPad->SetTopMargin(.00);
  //  gPad->SetLeftMargin(.1);
  g3->Draw("ap");    
  gwhit3->Draw("sp");
  g6gev3->Draw("sp");
  g3->Draw("sp");    
  fun->Draw("same");

  pad1->cd();
  gPad->SetBottomMargin(.03);
  //  gPad->SetRightMargin(.05);
  //  gPad->SetTopMargin(.01);
  //  gPad->SetLeftMargin(.1);

  g1->Draw("ap");
  gwhit1->Draw("sp");
  g6gev1->Draw("sp");
  g1->Draw("sp");
  leg->Draw();



  c1->SaveAs("figure1a.pdf");
  return;
}
