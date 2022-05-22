#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
void  histoOverlaps(){

  FILE *f = fopen("overlaps.txt","r");  
  Int_t ncols; 

  int dup=-1;
  double pd=1;
  vector <double> dupv,pdv;
  while (1) { 
    ncols = fscanf(f,"%i %lf ",&dup,&pd);
    if (ncols < 0) break;
    dupv.push_back(dup);
    pdv.push_back(pd);
  }
  TH1D *h1=new TH1D ("h1","h1" , 500 , -.5 , .5 ) ;
  TH1D *h2=new TH1D ("h2","h2" , 500 , -.5, .5 ) ;
  int size=dupv.size();
  for(int i=0;i<size;i++)
    {

      dup=dupv.at(i);
      pd=pdv.at(i);

      cout <<i<<"\t"<<pd<<"\t"<<dup<<endl;
      if(dup==0)
	h1->Fill(pd);
      else
	h2->Fill(pd);
    }
  TCanvas*c1=new TCanvas();

  c1->Divide(1,2);
  c1->cd(1);
  h1->Draw();
  h1->Fit("gaus");
  c1->cd(2);
  h2->Draw();
  h2->Fit("gaus");
  return 0;
}
