#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph2D* getKull( Int_t choice=1){
  TGraph2D* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname="src/moreModels/f2_tm1ht1th1os1.dat";
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
  // *** x, Q2, F2p, F2n, F2d
  if(file.is_open()==1)
    {
      Int_t nlines=0;
      while(!file.eof())
	{
	  for (Int_t i=0;i<5;i++)
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
      Double_t f2p[size];
      Double_t f2n[size];
      Double_t f2d[size];
      Double_t f2dh[size];

      for (Int_t i=0;i<size;i++)
	{
	  file >> x[i];
	  file >> q2[i];
	  file >> f2p[i];
	  file >> f2n[i];
	  file >> f2d[i];
	  f2dh[i]=f2d[i]/f2p[i];

	}

      graph=new TGraph2D(size,x,q2,f2dh);

    }//if file is open
  file.close();
  return graph;
}
