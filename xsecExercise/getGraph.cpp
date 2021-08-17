#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

TGraph* getGraph(string title="nameMe", double angle=21,  string target="h", Int_t choice=1){
  TString fname;
  ifstream file;
  string word;
  double ang=0.0;
  double temp=0.0;
  if(target=="c")fname = "../src/model/abel/externals/externals_c_f1f220.out";//target = c,d,h,
  if(target=="d")fname = "../src/model/abel/externals/externals_d_f1f220.out";//target = c,d,h,
  if(target=="h")fname = "../src/model/abel/externals/externals_h_f1f220.out";//target = c,d,h,
  //  fname = Form("model/21deg%s18.out",target.c_str()); //target =h2cryo,... Dave's table
  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;

      vector<Double_t> eBeam;
      vector<Double_t> ePrime;
      vector<Double_t> theta;
      vector<Double_t> x;
      vector<Double_t> q2;
      vector<Double_t> born;
      vector<Double_t> bornInc;
      vector<Double_t> bornQe;
      vector<Double_t> rad;
      vector<Double_t> radEl;
      vector<Double_t> radQe;
      vector<Double_t> radDis;
      vector<Double_t> cCor;
      vector<Double_t> radElp2;
      vector<Double_t> radElm2;
      vector<Double_t> radp2;
      vector<Double_t> radm2;
      vector<Double_t> rad0;

      vector<Double_t> xx;
      vector<Double_t> yy;
      double vradEl, vradQe, vradDIS, vrad;
      Int_t nlines=0;
  // ***Ebeam    Eprime  Theta     x        Q2      Sig_Born     Sig_Born_In  Sig_Born_QE  Sig_Rad      Sig_Rad_EL   Sig_Rad_QE   Sig_Rad_DIS  C_cor
    if(file.is_open()==1)
      {

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
      file.open(fname);
      for (Int_t i=0;i<nlines;i++)
	{
	  file >> temp; eBeam.push_back(temp);
	  file >> temp; ePrime.push_back(temp);
	  file >> ang; theta.push_back(ang);
	  file >> temp; x.push_back(temp);
	  file >> temp; q2.push_back(temp);
	  file >> temp; born.push_back(temp);
	  file >> temp; bornInc.push_back(temp);
	  file >> temp; bornQe.push_back(temp);
	  file >> vrad; rad.push_back(vrad);
	  file >> vradEl; radEl.push_back(vradEl);
	  file >> vradQe; radQe.push_back(vradQe);
	  file >> vradDIS; radDis.push_back(vradDIS);
	  file >> temp; cCor.push_back(temp);
	  radElp2.push_back(1.02*vradEl);
	  radElm2.push_back(0.98*vradEl);
	  radp2.push_back((1.02*vradEl+1.02*vradQe+vradDIS)/vrad);
	  radm2.push_back((0.98*vradEl+0.98*vradQe+vradDIS)/vrad);
	  rad0.push_back((vradEl+vradQe+vradDIS)/vrad);

	  if(ang!=angle){
	    eBeam.pop_back();
	    ePrime.pop_back();
	    theta.pop_back();
	    x.pop_back();
	    q2.pop_back();
	    born.pop_back();
	    bornInc.pop_back();
	    bornQe.pop_back();
	    rad.pop_back();
	    radEl.pop_back();
	    radQe.pop_back();
	    radDis.pop_back();
	    cCor.pop_back();
	    radElp2.pop_back();
	    radElm2.pop_back();
	    radp2.pop_back();
	    radm2.pop_back();
	    rad0.pop_back();
	  }


	}
      cout <<"Number of rowa used: "<< eBeam.size() << endl;
      xx=x;
      if(choice==1)yy=born;
      if(choice==2)yy=bornInc;
      if(choice==3)yy=bornQe;
      if(choice==4)yy=rad;
      if(choice==5)yy=radEl;
      if(choice==6)yy=radQe;
      if(choice==7)yy=radDis;
      if(choice==8)yy=radElp2;
      if(choice==9)yy=radElm2;
      if(choice==10)yy=radp2;
      if(choice==11)yy=radm2;
      if(choice==12)yy=rad0;

        }//if file is open
    file.close();
    TGraph *gr=new TGraph(xx.size(),&xx[0],&yy[0]);
    gr->SetName(title.c_str());
    gr->SetTitle(title.c_str());
    return gr;
}
