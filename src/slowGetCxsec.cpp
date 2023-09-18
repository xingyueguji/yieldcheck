#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

double getCxsec(double angle=21.1, double x=5., string target="h", Int_t choice=1, string spec="shms"){
  TGraph2D *graph;
  TString fname;
  ifstream file;
  string word;
  
  if(spec=="shms")
    {
      if(target=="c")fname = "src/model/abel/v0.990/shms_c10.6_all.dat_inel_f1f220";//target = c,d,h,
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
  //  cout <<" Is the File open?"<<  file.is_open()<<endl;
  Double_t eBeam;
  Double_t w2;
  Double_t theta;
  Double_t born;
  Double_t rci;
  Double_t val;
  Double_t t1=-1;
  Double_t t2=-1;
  Double_t t3=-1;
  Double_t t4=-1;
  Double_t x1=-1;
  Double_t x2=-1;
  Double_t x3=-1;
  Double_t x4=-1;
  Double_t z1=-1;
  Double_t z2=-1;
  Double_t z3=-1;
  Double_t z4=-1;
  Double_t lastw2=-1;
  Double_t lastval=-1;
  Double_t lastrci=-1;
  bool found_t1 = 0;
  bool found_t2 = 0;
  bool found_x1 = 0;
  bool found_x2 = 0;
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
      //      cout<<"There are " << nlines << " in " << fname<<endl;
      file.close();

      file.open(fname);
      
      for (Int_t i=0;i<nlines;i++)
	{
	  file >> eBeam;
	  file >> w2;
	  file >> theta;
	  file >> born;
	  file >> rci;
	  if(choice==1)val=born;
	  if(choice==2)val=rci;
	  if(choice==3)val=born/rci;
	  //	  if(i%1000==0.)cout << eBeam <<"\t"<<w2<<"\t"<<theta<<"\t"<<born<<endl;

	  if (abs(angle - theta) <= 0.2 && !found_t1){ 
	    t1=theta;
	    t2=t1;
	    //	    cout << "Found low 1: "<<t1<<endl;
	    found_t1=true; 
	  }

	  if(theta==t1 && w2-x < 0 && !found_x1)
	    {
	    found_x1=true;
	    x1=w2; 
	    x2=lastw2; 
	    z1=val;
	    z2=lastval;
	    //	    cout << "Found Low W2 : "<<x1<<endl;
	    //	    cout << "Found High W2 : "<<x2<<endl;
	    }

	  if (abs(angle - theta) <= 0.2 && !found_t2 && theta != t1){ 
	    t3=theta;
	    t4=t3;
	    //	    cout << "Found high theta : "<<t2<<endl;
	    found_t2=true; 
	  }
	  if(theta==t3 && w2-x < 0 && !found_x2)
	    {
	    found_x2=true;
	    x3=w2; 
	    x4=lastw2; 
	    z3=val;
	    z4=lastval;
	    //	    cout << "Found Low W2 : "<<x3<<endl;
	    //	    cout << "Found High W2 : "<<x4<<endl;
	    }
	     lastw2=w2;
	     lastval=val;
	     lastrci=rci;
        }
    }//if file is open
  file.close();

  /*
  cout << "***********************************************************"<<endl;
  cout <<"1:" <<"("<<t3<<", "<<x3<<", "<<z3<<")"<<"\t\t\t\t\t";;
  cout <<"2:" <<"("<<t4<<", "<<x4<<", "<<z4<<")"<<endl;
  cout << endl<< endl<< endl<< endl;
  cout <<"3:" <<"("<<t1<<", "<<x1<<", "<<z1<<")"<<"\t\t\t\t\t";
  cout <<"4:" <<"("<<t2<<", "<<x2<<", "<<z2<<")"<<endl;


  cout << "***********************************************************"<<endl;
  //      3_______4
  //      /       \
  //     /  *      \
  //    / (x,angle) \
  //   /_____________\
  //  1               2

  // interpolate bottom edge (1,2)
  */
  double width = x2 - x1;
  double bottom = (x2 - x)/width*z1 + (x - x1)/width*z2;

  width = x4- x3;
  double top = (x4 - x)/width*z3 + (x - x3)/width*z4;
  /*
  cout << "x"<<"\t"<<"x1"<<"\t"<<"x2"<<"\t"<<"z1"<<"\t"<<"z2"<<"\t"<<width<<endl;
  cout << x <<"\t"<< x1<<"\t"<<x2<<"\t"<<z1<<"\t"<<z2<<"\t"<<width<<endl;
  cout << "Value at bottom edge " << bottom << endl; 
  cout << "***********************************************************"<<endl;

  cout << "x"<<"\t"<<"x3"<<"\t"<<"x4"<<"\t"<<"z3"<<"\t"<<"z4"<<"\t"<<width<<endl;
  cout << x <<"\t"<< x3<<"\t"<<x4<<"\t"<<z3<<"\t"<<z4<<"\t"<<width<<endl;
  cout << "Value at top edge " << top << endl; 
  cout << "***********************************************************"<<endl;
  //       top  (t3)
  //       |
  //       |
  //       |
  //       * (angle)
  //       |
  //       bottom (t1)
  */
  width = t3 -t1;
  double result = (t3-angle)/width*bottom + (angle-t1)/width*top;
 
  return result;
}

