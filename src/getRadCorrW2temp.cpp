//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include "TPaveLabel.h"
//#include "TH2F.h"
//#include "TCanvas.h"

using namespace std;

TGraph2D* getRadCorrW2temp(string target="c", Int_t choice=1, string spec="shms"){
  TGraph2D *graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;

  if(spec=="shms")
    {
      //      if(target=="c")fname = "src/model/abel/externals/externals_c_f1f220.out";//target = c,d,h,
      //      if(target=="d")fname = "src/model/abel/externals/externals_d_f1f220.out";//target = c,d,h,
      //      if(target=="h")fname = "src/model/abel/externals/externals_h_f1f220.out";//target = c,d,h,
      if(target=="c")fname = "src/model/abel/v0.990/shms_c10.6_all.dat_inel_f1f2210";//target = c,d,h,
      if(target=="d")fname = "src/model/abel/v0.990/shms_d10.6_all.dat_inel_f1f220";//target = c,d,h,
      if(target=="h")fname = "src/model/abel/v0.990/shms_h10.6_all.dat_inel_f1f220";//target = c,d,h,
    }

  if(spec=="hms")
    {
      if(target=="c")fname = "src/model/abel/v0.990/hms_c10.6_all.dat_inel_f1f220";//target = c,d,h,
      if(target=="d")fname = "src/model/abel/v0.990/hms_d10.6_all.dat_inel_f1f220";//target = c,d,h,
      if(target=="h")fname = "src/model/abel/v0.990/hms_h10.6_all.dat_inel_f1f220";//target = c,d,h,
    }
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
      Double_t eBeam[size];
      Double_t w2[size];
      Double_t theta[size];
      Double_t born[size];
      Double_t rci[size];
      Double_t y[size];

      for (Int_t i=0;i<size;i++)
	{
	  file >> eBeam[i];
	  file >> w2[i];
	  file >> theta[i];
	  file >> born[i];
	  file >> rci[i];
	  if(choice==1)y[i]=born[i];
	  if(choice==2)y[i]=rci[i];
	  if(choice==3)y[i]=born[i]/rci[i];
	}

      graph=new TGraph2D(size,w2,theta,y);
        }//if file is open
  file.close();
  return graph;
}
