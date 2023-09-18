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
  if(target=="c")fname = "src/model/abel/externals/externals_c_f1f220.out";//target = c,d,h,
  if(target=="d")fname = "src/model/abel/externals/externals_d_f1f220.out";//target = c,d,h,
  if(target=="h")fname = "src/model/abel/externals/externals_h_f1f220.out";//target = c,d,h,
  //  fname = Form("model/21deg%s18.out",target.c_str()); //target =h2cryo,... Dave's table
  file.open(fname);
  //  cout <<" Is the File open?"<<  file.is_open()<<endl;

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
	  radp2.push_back((1.02*vradEl+1.02*vradQe+vradDIS-vrad)/vrad);
	  radm2.push_back((0.98*vradEl+0.98*vradQe+vradDIS-vrad)/vrad);
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
      //      cout <<"Number of rowa used: "<< eBeam.size() << endl;
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
      if(choice==10)yy=(radp2);
      if(choice==11)yy=(radm2);
      if(choice==12)yy=rad0;

        }//if file is open
    file.close();
    TGraph *gr=new TGraph(xx.size(),&xx[0],&yy[0]);
    gr->SetName(title.c_str());
    gr->SetTitle(title.c_str());
    return gr;
}

TGraph* getRadError(double angle=21, string target="h"){
  //TGraph* getGraph(string title="nameMe", double angle=21,  string target="h", Int_t choice=1){
  /*
      if(choice==1)yy=born;
      if(choice==2)yy=bornInc;
      if(choice==3)yy=bornQe;
      if(choice==4)yy=rad;
      if(choice==5)yy=radEl;
      if(choice==6)yy=radQe;
      if(choice==7)yy=radDis;
  */

  TGraph* gRadp2h=getGraph("radp2h", angle, "h", 10);
  TGraph* gRadm2h=getGraph("radm2h", angle, "h", 11);
  gRadp2h->SetLineColor(kRed);
  gRadm2h->SetLineColor(kBlack);
  gRadp2h->SetLineStyle(9);
  gRadm2h->SetLineStyle(9);

  TGraph* gRadp2d=getGraph("radp2d", angle, "d", 10);
  TGraph* gRadm2d=getGraph("radm2d", angle, "d", 11);
  gRadp2d->SetLineColor(kGreen+3);
  gRadm2d->SetLineColor(kBlue);
  gRadp2d->SetLineStyle(9);
  gRadm2d->SetLineStyle(9);

    TLegend *leg3=new TLegend(.2,.6,.8,.85);
  leg3->AddEntry(gRadp2h, "Rad (with RadEl/RadQE scaled up 2%)","l");
  leg3->AddEntry(gRadm2h, "Rad (with RadEl/RadQE scaled down 2%)","l");
  leg3->AddEntry(gRadp2d, "Rad (with RadEl/RadQE scaled up 2%)","l");
  leg3->AddEntry(gRadm2d, "Rad (with RadEl/RadQE scaled down 2%)","l");

  /*
  TCanvas *c1=new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  gRadp2h->GetYaxis()->SetRangeUser(-0.02,0.02);
  gRadp2h->GetXaxis()->SetRangeUser(.2,0.95);
  gRadp2h->SetTitle("Ratio  (Rad with Scaling)/(Rad)");
  gRadp2h->Draw("al");
  gRadm2h->Draw("sl");
  gRadp2d->Draw("sl");
  gRadm2d->Draw("sl");
  leg3->Draw("same");

  TPaveText *tb=new TPaveText(.35,.13,.65,.25,"NDC");
  tb->AddText(Form("Angle:%2.0f",angle));
  tb->Draw();

  */
  double x1,y1,x2,y2;
  vector <double> sx;
  vector <double> sy;
  int npts=gRadp2h->GetN();
  for(int i=0; i<npts; i++){

    gRadp2h->GetPoint(i,x1,y1);
    gRadp2d->GetPoint(i,x2,y2);
    double val1=abs(y1);
    double val2=abs(y2);
    double total;// error on model + method
    if(target=="h")total=sqrt(val1*val1+0.01*0.01);
    if(target=="d")total=sqrt(val2*val2+0.01*0.01);
    if(target=="r")total=sqrt(val1*val1+val2*val2+0.005*0.005);    
    //    cout << y1 <<"\t"<<  y2 <<"\t"<< total << endl;
    sx.push_back(x1);
    sy.push_back(total*100);
  } 

  TGraph *g=new TGraph(npts, &sx[0], &sy[0]);
  /*
  c1->cd(2);
  g->GetYaxis()->SetRangeUser(0,2);
  g->GetXaxis()->SetRangeUser(.2,0.95);
  g->SetTitle("Uncertainty in D/H ratio");
  g->GetYaxis()->SetTitle("%");
  g->GetXaxis()->SetTitle("X");
  g->Draw();
  c1->SaveAs(Form("rat%2.0f.pdf",angle));
  */
  return g;
}
