#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;
//choice 1 ==born
//choice 2 ==rci
//choice 3 ==rad

//TGraph2D* getRadCorrW2(string target="h", Int_t choice=1, string spec="shms", string version="v0.990"){
//TGraph2D* getRadCorrW2(string target="h", Int_t choice=1, string spec="shms", string version="v996t2"){
TGraph2D* getRadCorrW2(string target="h", Int_t choice=1, string spec="shms", string version="v996t2"){
  TGraph2D *graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;

  fname = Form("src/model/abel/%s/%s_%s10.6_all.dat_inel_f1f220",version.c_str(),spec.c_str(),target.c_str());//target = c,d,h,

  if(version=="newest")
    {  
      fname = Form("src/model/abel/%s_%s10.6_all.dat_inel_f1f220",spec.c_str(),target.c_str());//target = c,d,h,
    }


  if(version=="v0.995")
    {  
      fname = Form("src/model/abel/%s/%s_%s10.6_all.dat_inel_f1f221",version.c_str(),spec.c_str(),target.c_str());//target = c,d,h,
    }

  if(version=="v0.990")
    {  
      fname = Form("src/model/abel/%s/%s_%s10.6_all.dat_inel_f1f220",version.c_str(),spec.c_str(),target.c_str());//target = c,d,h,
    }



  if(version=="f1f209")
    {  
      fname = Form("src/model/abel/shms_%s10.6_all.dat_inel_f1f209",target.c_str());//target = c,d,h,
    }


  if(version=="v996t2")
    {  
      fname = Form("src/model/abel/v0.996t2/%s_%s10.6_all.dat_inel_f1f221",spec.c_str(),target.c_str());//target = c,d,h,
      if(target=="d" && spec=="shms")fname="src/model/abel/v0.996t2/shms_d100.dat";
      if(target=="d" && spec=="hms")fname="src/model/abel/v0.996t2/hms_d100.dat";
    }


  file.open(fname);

  //  cout <<" Is the File open?"<<  file.is_open()<<endl;
    if(file.is_open()==1)
      {
      Int_t nlines=0;
      Int_t ncols=5;
      if(version=="v996t2")ncols=5;
      while(!file.eof())
	{
	  for (Int_t i=0;i<ncols;i++)
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
      Double_t dum;
      for (Int_t i=0;i<size;i++)
	{
	  file >> eBeam[i];
	  file >> w2[i];
	  file >> theta[i];
	  file >> born[i];
	  //	  if(version=="v996t2")file >> dum;
	  file >> rci[i];
	  //	  if(i%1000==0.)cout << eBeam[i] <<"\t"<<w2[i]<<"\t"<<theta[i]<<"\t"<<born[i]<<endl;
	  if(choice==1)y[i]=born[i];
	  if(choice==2)y[i]=rci[i];
	  if(choice==3)y[i]=born[i]/rci[i];
	}

      graph=new TGraph2D(size,w2,theta,y);
        }//if file is open
  file.close();
  return graph;
}
