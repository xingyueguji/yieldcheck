#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph* getCJ( Int_t choice=1){
  TGraph* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname="CJ15sfn_25deg.out";
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
	  for(Int_t i=0; i<8; i++)file >> word;
	  f2dp[i]=f2d[i]/f2p[i];
	  cout << ep[i] << "\t" << f2dp[i] << endl ;
	}


      graph=new TGraph(size,x,f2dp);

    }//if file is open
  file.close();
  return graph;
}
