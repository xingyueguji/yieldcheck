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
	  cout<<theta[i]<<endl;
        num++;
	}
    }
  //  cout << num << "\t" << theta[n-1] << endl;
  return num;
}


Int_t pointsPerAngle(Float_t *theta, Int_t n, Float_t ang)
{
  Int_t num=0;
  for (Int_t i=0; i<n-1;i++)
    {
      if (theta[i]==ang)
	{
	  //	cout << num << "\t" << theta[i] << endl;
        num++;
	}
    }
  //  cout << num << "\t" << theta[n-1] << endl;
  return num;
}


void testInterpolation1(string target="h2cryo", Int_t choice=1){
  TGraph2D* graph;
   Float_t result=0;
  gStyle->SetMarkerStyle(6);
  //  string froot;
  TString fname;
  ifstream file;
  
  string word;
  fname = "model/abel/externals/externals_d_f1f220.out";//target = c,d,h,
  //  fname = Form("model/21deg%s18.out",target.c_str());
  file.open(fname);
  //  cout <<" Is the File open?"<<  file.is_open()<<endl;
  
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
      // grab and display header
      //      for (Int_t i=0;i<13;i++)
      //	{
	  //	  file >> word;
	  //	  cout << word << "\t";      
      //	}
      //      cout << endl;
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

      cout << "There will be thismany pts:" << pts << "    numThetas= "<<numThetas<<endl;

       

      pts=pointsPerAngle(theta, size, 39.00);
      Int_t pts2=pointsPerAngle(theta, size, 39.20);
      TGraph *gr=new TGraph(pts,&ePrime[46333],&rad[46333]);
      TGraph *gr2=new TGraph(pts2,&ePrime[46333+pts],&rad[46333+pts]);
      gr->SetMarkerColor(kBlack);
      gr->SetLineColor(kBlack);
      gr2->SetMarkerColor(kGreen+3);
      gr2->SetLineColor(kGreen+3);
      gr->Draw("apl");
      gr2->Draw("spl");
      if(choice==3)graph=new TGraph2D(size,ePrime,theta,born);
      if(choice==2)graph=new TGraph2D (size,ePrime, theta,ratio);
      if(choice==1)graph=new TGraph2D(size,ePrime,theta,rad);


      //interpolate 16.1 degress from 2.2 to 6.2 2000pts
      Double_t xx[2000];
      Double_t y[2000];
      for(Int_t i=0;i<2000;i++)
	{
	  xx[i]=1.0+(2.5-1)/2000*i;
	  y[i]=graph->Interpolate(1.00+(2.5-1.0)/2000.*i,39.1);
	  //	  cout << y[i] << endl;
	}
      TGraph *gr9=new TGraph(2000,xx,y);
      gr9->SetLineColor(kRed);
      gr9->SetMarkerColor(kRed);
      gr9->Draw("spl");
      cout << "Angles"<<theta[46333]<<"\t"<<theta[46333+pts]<<endl;
      cout << "Angles"<<theta[46333-1]<<"\t"<<theta[46333+pts-1]<<endl;
      //      graph=new TGraph2D(size,ePrime,theta,ratio);

      //      graph->GetZaxis()->SetTitle("ratio");      
      /*
      graph->SetTitle("#sigma_{Rad}(#Theta,E')");
      graph->GetXaxis()->SetTitle("E' (GeV)");
      graph->GetYaxis()->SetTitle("#Theta (degree)");
      graph->Draw("COLZ"); 
      */
      //      result = graph->Interpolate(ep,thVal);



    }//if file is open
  file.close();
  //  graph2->Draw("ap");
  //    delete graph;
    //    delete graph2;
  //  return;
}
