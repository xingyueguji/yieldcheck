#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraphErrors* getJAM(double angle=21.){
  TGraphErrors* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname="src/moreModels/JAM4f2_new.txt";
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
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
      Double_t th[size];
      Double_t q2[size];
      Double_t x[size];      
      Double_t f2dp[size];
      Double_t err[size];            

      for (Int_t i=0;i<size;i++)
	{
	  file >> x[i];
	  file >> q2[i];
	  file >> th[i];
	  file >> f2dp[i];	  
	  file >> err[i];
	}
      vector <double> xx,yy, ye;
      for (Int_t i=0;i<size-1;i++)
	{
	  if(abs(th[i]-angle)<.25)
	    {
	      /*
	      cout << x[i]<<"\t";
	      cout << q2[i]<<"\t";
	      cout << th[i]<<"\t";
	      cout << f2dp[i]<<"\t";
	      cout << err[i]<<endl;	      
	      */
	      xx.push_back(x[i]);
	      yy.push_back(f2dp[i]);
	      ye.push_back(err[i]);	      
	    }
	}
      //      graph=new TGraphErrors(xx.size(),&xx[0],&yy[0],0,&ye[0]);
      graph=new TGraphErrors(xx.size(),&xx[0],&yy[0],0,0);
      graph->SetMarkerStyle(33);
      graph->SetMarkerColor(kBlack);
      graph->SetLineColor(kBlack);
    }//if file is open
  file.close();
  return graph;
}
