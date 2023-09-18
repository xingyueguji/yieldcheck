#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

double getCxsec(TGraph2D *gr, double angle=21.1, double x=5.){
  bool debug=false;
  //  cout <<" Is the File open?"<<  file.is_open()<<endl;

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
  bool found_t1 = 0;
  bool found_t2 = 0;
  bool found_x1 = 0;
  bool found_x2 = 0;
  Int_t nlines=gr->GetN();
  Double_t *w2=gr->GetX();
  Double_t *theta=gr->GetY();
  Double_t *val=gr->GetZ();
      
      for (Int_t i=0;i<nlines;i++)
	{
	  if (abs(angle - theta[i]) < 0.20 && !found_t1){ 
	    t1=theta[i];
	    t2=t1;
	    if(debug)cout << "Found low 1: "<<t1<<endl;
	    found_t1=true; 
	  }

	  if(theta[i]==t1 && w2[i]-x < 0 && !found_x1)
	    {
	    found_x1=true;
	    x1=w2[i]; 
	    x2=lastw2; 
	    z1=val[i];
	    z2=lastval;
	    if(debug)cout << "Found Low W2 : "<<x1<<endl;
	    if(debug)cout << "Found High W2 : "<<x2<<endl;
	    }

	  if (found_x1 && !found_t2 && theta[i] != t1){ 

	    t3=theta[i];
	    t4=t3;
	    if(debug)cout << "Found high theta[i] : "<<t3<<endl;
	    found_t2=true; 
	  }
	  if(theta[i]==t3 && w2[i]-x < 0 && !found_x2)
	    {
	    found_x2=true;
	    x3=w2[i]; 
	    x4=lastw2; 
	    z3=val[i];
	    z4=lastval;
	    if(debug)cout << "Found Low W2 : "<<x3<<endl;
	    if(debug)cout << "Found High W2 : "<<x4<<endl;
	    }
	     lastw2=w2[i];
	     lastval=val[i];
	     if(z4!=-1)break;
        }

      if(debug){
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
      }
  double width = x2 - x1;
  double bottom = (x2 - x)/width*z1 + (x - x1)/width*z2;

  width = x4- x3;
  double top = (x4 - x)/width*z3 + (x - x3)/width*z4;
  if(debug){
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
  }
  width = t3 -t1;

  double result = (t3-angle)/width*bottom + (angle-t1)/width*top;
  if(TMath::IsNaN(result))result=0; 
  return result;
}

