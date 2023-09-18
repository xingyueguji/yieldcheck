#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;
//choice 1 DIS
//choice 1 Hybrid
TGraph* getKP(string what= "dis", string angle="21"){

  double thetac=0;
  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21")thetac=21.035;
 


  TGraph* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname=Form("src/moreModels/%s_model.dat",what.c_str());

  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
  // *** x, Q2, F2p, F2n, F2d
  if(file.is_open()==1)
    {
      Int_t nlines=0;
      while(!file.eof())
	{
	  for (Int_t i=0;i<4;i++)
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
      Double_t x[size];
      Double_t q2[size];
      Double_t w2[size];
      Double_t dop[size]; //  F2d/F2p

      for (Int_t i=0;i<size;i++)
	{
	  file >> x[i];
	  file >> q2[i];
	  file >> w2[i];
	  file >> dop[i];
	  //	  cout << "Loading arrays "<< x[i] <<"\t"<< q2[i] <<"\t"<< w2[i]<<endl;
	}

      Double_t eb=10.602;
      Double_t mp = .9382723;
      Double_t mp2 = mp*mp;

      vector <double> vx;
      vector <double> vy;

      for (Int_t i=0;i<size;i++)
	{
	  Double_t ep = eb + (mp2 - w2[i])/(2*mp*(1-x[i]));
	  Double_t sin2=q2[i]/(4*eb*ep);
	  Double_t theta = asin(sqrt(sin2))*2*180/TMath::Pi();
	  //	  cout << ep <<"\t"<<theta<<endl;
	  //	  cout <<"Calculating....."<< x[i] <<"\t"<< q2[i] <<"\t"<< w2[i]<<"\t"<<ep <<"\t"<<theta<<endl;
	  //	  if(abs(theta-thetac)<1.)
	    {
	      vx.push_back(x[i]);
	      vy.push_back(q2[i]);
	    }
	}

      //      graph=new TGraph2D(size,x,q2,dop);
      graph=new TGraph(vx.size(),&vx[0],&vy[0]);

    }//if file is open
  file.close();
  return graph;
}
