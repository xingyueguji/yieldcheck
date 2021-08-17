#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;
//choice 1 DIS
//choice 1 Hybrid
TGraph2D* getKP(string what= "dis"){
  TGraph2D* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname=Form("%s_model.dat",what.c_str());

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
	}

      graph=new TGraph2D(size,x,q2,dop);

    }//if file is open
  file.close();
  return graph;
}
