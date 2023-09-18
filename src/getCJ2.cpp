#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph* getCJ2( string choice="25"){
  TGraph* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  if(choice=="21")fname="src/moreModels/CJ15sfn_21deg.out";
  if(choice=="25")fname="src/moreModels/CJ15sfn_25deg.out";
  if(choice=="29")fname="src/moreModels/CJ15sfn_29deg.out";
  if(choice=="33")fname="src/moreModels/CJ15sfn_33deg.out";
  if(choice=="39")fname="src/moreModels/CJ15sfn_39deg.out";
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
  if(file.is_open()==1)
    {
      Int_t nlines=0;
      while(!file.eof())
	{
	  for (Int_t i=0;i<15;i++)
	    {
	      file >> word;
	    }
	  nlines++;
	}
      cout<<"There are " << nlines << " in " << fname<<endl;
      file.close();
      // start at top of file
      file.open(fname);
      //      const int size=nlines-1;
      const int size=nlines;
      Double_t th[size];
      Double_t ep[size];
      Double_t q2[size];
      Double_t x[size];      
      Double_t f2p[size];
      Double_t f2n[size];
      Double_t f2d[size];
      Double_t r98[size];
      Double_t dr98[size];
      Double_t f2dp[size];

      for (Int_t i=0;i<size;i++)
	{
	  file >> th[i];
	  file >> ep[i];
	  file >> q2[i];
	  file >> x[i];	  
	  file >> f2p[i];
	  file >> f2n[i];
	  file >> f2d[i];
	  for(Int_t i=0; i<6; i++)file >> word;
	  file >> r98[i];
	  file >> dr98[i];
	  double alpha = 1./137.;
	  double mp = .9382723;
	  double mp2 = mp*mp;
	  double ang=th[i]*TMath::Pi()/180.;
	  double tan2=tan(ang/2)*tan(ang/2);
	  double nu = 10.602 - ep[i];
	  double nu2=nu*nu;
	  double w2 = mp2 + 2*mp*nu - q2[i];
	  double k = (w2-mp2)/(2*mp);
	  double a = 1+q2[i]/(4.*mp2*x[i]*x[i]);
	  double eps = 1./(1+2*tan2*a);
	  double gamma_num=alpha*k*ep[i];
	  double gamma_denom=2*TMath::Pi()*TMath::Pi()*q2[i]*10.602*(1.-eps);
	  double gamma = gamma_num/gamma_denom;
	  double kinem1=(k*nu)/(4*TMath::Pi()*TMath::Pi()*alpha);
	  double kinem2=1./(1+nu2/q2[i]);
	  double kinem=kinem1*kinem2/gamma;
	  double cs_h =  (f2p[i]*(1+eps*r98[i])) / (kinem*(1+r98[i]));
	  double cs_d =  (f2d[i]*(1+eps*dr98[i])) / (kinem*(1+dr98[i]));
	  //	  f2dp[i]=f2d[i]/f2p[i];
	  f2dp[i]=cs_d/cs_h;;
	  cout << ep[i] << "\t" << f2dp[i] << endl ;
	}


      graph=new TGraph(size-1,x,f2dp);

    }//if file is open
  file.close();
  return graph;
}
