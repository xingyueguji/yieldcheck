#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;
//choice 1 DIS
//choice 1 Hybrid
TGraphErrors* getJmu(string what= "h", string angle="21",TGraph2D* grd=0, TGraph2D* grh=0, Int_t cx=1){

  double thetac=0;
  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21")thetac=21.035;
 


  TGraphErrors* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  fname="jmu/jmu_pass3c_shms_xsect.txt";

  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
  // *** A, E, E', theta, sigma_h, err, sigma_d, err
  if(file.is_open()==1)
    {
      Int_t nlines=0;
      while(!file.eof())
	{
	  for (Int_t i=0;i<8;i++)
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
      Double_t a, e ,ep, th, xh, xhe, xd, xde;
      vector <Double_t>x;
      vector <Double_t>y;
      vector <Double_t>ye;
      for (Int_t i=0;i<size;i++)
	{
	  file >> a>>e>>ep>>th>>xh>>xhe>>xd>>xde;


	  xd=xd*2;
	  xde=xde*2;
	  Double_t sin2 = sin(th/2/180*TMath::Pi())*sin(th/2/180*TMath::Pi());
	  Double_t nu= e-ep;
	  Double_t q2 = 4.*ep*e*sin2;
	  Float_t mp = .9382723;
	  Double_t xb=q2/2./mp/nu;
	  Double_t modeld=grd->Interpolate(ep,thetac);  //<<"\t"<<
	  Double_t modelh=grh->Interpolate(ep,thetac);  //<<"\t"<<
	  Double_t modeld_o=grd->Interpolate(ep,thetac + 0.11459);  //<<"\t"<<
	  Double_t modelh_o=grh->Interpolate(ep,thetac + 0.11459);  //<<"\t"<<
	  xd=xd*modeld/modeld_o;
	  xh=xh*modelh/modelh_o;
	  if(abs(th-thetac)<.3)
	    {

	      if(cx==0) //data/model
		{

		  xh=xh/modelh;
		  xhe=xhe/modelh;
		  xd=xd/modeld;
		  xde=xde/modeld;
		}

	      x.push_back(xb);
	      if(what=="h")
		{
		  y.push_back(xh);
		  ye.push_back(xhe);
		}
	      if(what=="d")
		{
		  y.push_back(xd);
		  ye.push_back(xde);
		}
	      if(what=="r")
		{
		  Double_t r=xd/xh/2;
		  Double_t re=sqrt(xde*xde+xhe*xhe)*r/2;

		  if(cx==0){ r=r*2; re=re*2;}

		  y.push_back(r);
		  ye.push_back(re);
		}
	    }
	}

      graph=new TGraphErrors(x.size(),&x[0],&y[0],0,&ye[0]);

    }//if file is open
  file.close();
  return graph;
}
