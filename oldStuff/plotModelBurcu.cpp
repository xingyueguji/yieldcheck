#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

Int_t howManyThetas(Float_t *theta, Int_t n)
{
  Int_t num=1;
  for (Int_t i=0; i<n-1;i++)
    {
      if (theta[i]!=theta[i+1])
	{
	  //	cout << num << "\t" << theta[i] << endl;
        num++;
	}
    }
  cout << num << "\t" << theta[n-1] << endl;
  return num;
}


TGraph2D* getRadCorr(string target="c", Int_t choice=1){
  TGraph2D* graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  if(target=="c")fname = "/w/hallc-scifs17exp/inclusive/abels/MC/tables/externals/externals_c_f1f220.out";//target = c,d,h,
  if(target=="d")fname = "/w/hallc-scifs17exp/inclusive/abels/MC/tables/externals/externals_d_f1f220.out";//target = c,d,h,
  if(target=="h")fname = "/w/hallc-scifs17exp/inclusive/abels/MC/tables/externals/externals_h_f1f220.out";//target = c,d,h,
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
  // ***Ebeam    Eprime  Theta     x        Q2      Sig_Born     Sig_Born_In  Sig_Born_QE  Sig_Rad      Sig_Rad_EL   Sig_Rad_QE   Sig_Rad_DIS  C_cor
  // Count how many lines are in the file
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
      Float_t eBeam[size];
      Float_t ePrime[size];
      Float_t theta[size];
      Float_t x[size];
      Float_t q2[size];
      Float_t born[size];
      Float_t bornInc[size];
      Float_t bornQe[size];
      Float_t rad[size];
      Float_t radEl[size];
      Float_t radQe[size];
      Float_t radDis[size];
      Float_t cCor[size];
      Float_t ratio[size];

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
      Int_t numThetas=howManyThetas(theta, size);
      Int_t pts=size/numThetas;
      Int_t start=pts*25;
      if(choice==1)graph=new TGraph2D(size,ePrime,theta,born);
      if(choice==2)graph=new TGraph2D (size,ePrime, theta,ratio);
      if(choice==3)graph=new TGraph2D(size,ePrime,theta,rad);

    }//if file is open
  file.close();
  return graph;
}


void plotModelBurcu(){

  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////
 vector <float> mx;
 vector <float> my;
 Float_t delta, ratio, err, ep, model;
 Double_t thetac=21.;
 TGraph2D *gr=getRadCorr("h",1);  
 for (Int_t i=0;i<1000;i++)
   {
     ep=1.+i/1000.*5.;
     model=gr->Interpolate(ep,thetac);  //<<"\t"<<
     Double_t mp = .9382723;
     Double_t mp2 = mp*mp;
     Double_t ebeam=10.602l;
     Double_t sin2 = sin(thetac*TMath::Pi()/180/2.)*sin(thetac*TMath::Pi()/180/2.);
     Double_t nu = ebeam -ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     cout<<q2<<"\t"<<ep<<endl;
     Double_t w2= mp2 + 2.*mp*nu-q2;
     Double_t xb=q2/2./mp/nu;
     if(model>0)
       {
     mx.push_back(xb);
     my.push_back(model);
       }
   }
 TGraph *gm=new TGraph(mx.size(),&mx[0],&my[0]);
 gm->GetXaxis()->SetTitle("x_{B}");
 gm->SetTitle("Hydrogen 21deg");
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
 gm->GetYaxis()->SetTitleOffset(1.1);
 gm->GetYaxis()->SetRangeUser(0,3.2);
 gm->GetXaxis()->SetRangeUser(0.3,1);
 gm->SetLineColor(kRed);
 gm->SetLineWidth(3);
 gm->Draw("ac");
 TLegend *leg=new TLegend(.6,.6,.85,.75);
 leg->AddEntry(gm,"f1f220 (M.E. Christy)","l");
 leg->Draw();
  return;
}
