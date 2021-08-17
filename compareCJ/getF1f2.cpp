#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph* getF1f2( string choice="25"){
  TGraph* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname="f2d_f2p_v995.dat";
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
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
      Double_t f2d[size];
      Double_t f2p[size];
      Double_t f2r[size];      

      for (Int_t i=0;i<size;i++)
	{
	  file >> x[i];
	  file >> f2d[i];
	  file >> f2p[i];
	  file >> f2r[i];	  
	}
      vector <double> xx,yy;
      for (Int_t i=0;i<size-1;i++)
	{
	  if(x[i]<0.95)
	    {
	      xx.push_back(x[i]);
	      yy.push_back(f2r[i]);
	    }
	}
      graph=new TGraph(xx.size(),&xx[0],&yy[0]);
      graph->SetName("f2");
    }//if file is open
  file.close();
  return graph;
}
