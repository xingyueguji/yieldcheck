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

TGraph* tableCheck2(string target="d", Int_t choice=1, string spec="shms", string version="v996t2"){
  //TGraph2D* getRadCorrW2(string target="h", Int_t choice=1, string spec="shms", string version="v0.995"){
  TGraph *graph;
  Float_t result=0;
  TString fname2, fname1;
  ifstream file1, file2;
  string word;

fname2="src/model/abel/externals/v0.995/d_sep/d10.6_21.0_f1f221.out";
fname1="src/model/abel/externals/v0.996t2/d_sep/d10.6_21.0_f1f221.out";


  file1.open(fname1);
  file2.open(fname2);

  cout <<" Is the File open?"<<  file1.is_open()<<endl;
  cout <<" Is the File open?"<<  file2.is_open()<<endl;

    if(file1.is_open()==1)
      {
      Int_t nlines1=0;
      Int_t nlines2=0;
      Int_t ncols=5;
      while(!file1.eof())
	{
	  for (Int_t i=0;i<ncols;i++)
	    {
	      file1 >> word;
	    }
	  nlines1++;
	}
      while(!file2.eof())
	{
	  for (Int_t i=0;i<ncols;i++)
	    {
	      file2 >> word;
	    }
	  nlines2++;
	}
      cout<<"There are " << nlines1 << " in " << fname1<<endl;
      file1.close();
      file2.close();
      // start at top of file
      file1.open(fname1);
      file2.open(fname2);
      const int size=nlines1;

      Double_t eBeam1[size];
      Double_t w21[size];
      Double_t theta1[size];
      Double_t born1[size];
      Double_t rci1[size];
      Double_t y1[size];

      Double_t eBeam2[size];
      Double_t w22[size];
      Double_t theta2[size];
      Double_t born2[size];
      Double_t rci2[size];
      Double_t y2[size];

      Double_t dum;

      vector <double> x,y;
      for (Int_t i=0;i<size;i++)
	{
	  file1 >> eBeam1[i];//
	  file1 >> w21[i];//ep
	  file1 >> theta1[i];
	  file1 >> dum;//x
	  file1 >> dum;//q2
	  file1 >> dum;//born 
	  file1 >> dum;//born inc
	  file1 >> born1[i];//born qe
	  file1 >> dum;//rad
	  file1 >> dum;//rad el
	  file1 >> dum;//rad qe
	  file1 >> dum;//rad dis
	  file1 >> dum;//?


	  file2 >> eBeam2[i];//
	  file2 >> w22[i];//ep
	  file2 >> theta2[i];
	  file2 >> dum;//x
	  file2 >> dum;//q2
	  file2 >> dum;//born
	  file2 >> dum;//born inc
	  file2 >> born2[i];//born qe
	  file2 >> dum;//rad
	  file2 >> dum;//rad el
	  file2 >> dum;//rad qe
	  file2 >> dum;//rad dis
	  file2 >> dum;//?



	  //	  if(i%1000==0.)cout << eBeam[i] <<"\t"<<w2[i]<<"\t"<<theta[i]<<"\t"<<born[i]<<endl;
	  if(theta1[i]==21.00){
	    cout <<setw(10)<<theta1[i]<<"\t";
	    cout <<setw(10)<<w21[i]<<"\t";
	    cout <<setw(10)<<born1[i]<<"\t";
	    cout <<setw(10)<<eBeam1[i]-eBeam2[i]<<"\t";
	    cout <<setw(10)<<w21[i]-w22[i]<<"\t";
	    cout <<setw(10)<<theta1[i]-theta2[i]<<"\t";
0	    cout <<setw(10)<<born1[i]-born2[i]<<"\t";
	    cout <<setw(10)<<rci1[i]-rci2[i]<<endl;

	    double val=100*(born1[i]-born2[i])/born1[i];
	    val=born1[i];
	    y.push_back(val);
	    val=w21[i];
	    x.push_back(val);
	  }
	}

      graph=new TGraph(x.size(),&x[0],&y[0]);
      graph->GetXaxis()->SetRangeUser(1.5,12.);
      graph->SetMarkerStyle(33);
      graph->SetMarkerColor(kRed);
        }//if file is open
      file1.close();
      file2.close();
  return graph;
}

