#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph* getCJ( string choice="25"){
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
      vector <double> xx,yy;
      for (Int_t i=0;i<size-1;i++)
	{
	  if(x[i]<0.94)
	    {
	      xx.push_back(x[i]);
	      yy.push_back(f2dp[i]);
	    }
	}
      graph=new TGraph(xx.size(),&xx[0],&yy[0]);

    }//if file is open
  file.close();
  return graph;
}
