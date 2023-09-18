#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph2D* getRadCorr(string target="c", Int_t choice=1){
  TGraph2D* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  if(target=="c")fname = "src/model/abel/externals/externals_c_f1f220.out";//target = c,d,h,
  if(target=="d")fname = "src/model/abel/externals/externals_d_f1f220.out";//target = c,d,h,
  if(target=="h")fname = "src/model/abel/externals/externals_h_f1f220.out";//target = c,d,h,
  //  fname = Form("model/21deg%s18.out",target.c_str()); //target =h2cryo,... Dave's table
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
  // ***Ebeam    Eprime  Theta     x        Q2      Sig_Born     Sig_Born_In  Sig_Born_QE  Sig_Rad      Sig_Rad_EL   Sig_Rad_QE   Sig_Rad_DIS  C_cor
  if(file.is_open()==1)
    {
      Int_t nlines=0;
      while(!file.eof())
	{
	  for (Int_t i=0;i<13;i++)
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
      Double_t ePrime[size];
      Double_t theta[size];
      Double_t x[size];
      Double_t q2[size];
      Double_t born[size];
      Double_t bornInc[size];
      Double_t bornQe[size];
      Double_t rad[size];
      Double_t radEl[size];
      Double_t radQe[size];
      Double_t radDis[size];
      Double_t cCor[size];
      Double_t ratio[size];
      // grab and display header
      /*
      for (Int_t i=0;i<13;i++)
	{
	  file >> word;
	  //	  cout << word << "\t";      
	}
      //      cout << endl;
      */
      for (Int_t i=0;i<size;i++)
	{
	  file >> eBeam[i];
	  file >> ePrime[i];
	  file >> theta[i];
	  file >> x[i];
	  file >> q2[i];
	  file >> born[i];
	  file >> bornInc[i];
	  file >> bornQe[i];
	  file >> rad[i];
	  file >> radEl[i];
	  file >> radQe[i];
	  file >> radDis[i];
	  file >> cCor[i];
	  ratio[i]=born[i]/rad[i];

	}

      if(choice==1)graph=new TGraph2D(size,ePrime,theta,born);
      if(choice==2)graph=new TGraph2D (size,ePrime, theta,ratio);
      if(choice==3)graph=new TGraph2D(size,ePrime,theta,rad);

    }//if file is open
  file.close();
  return graph;
}
