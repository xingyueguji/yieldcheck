#include "src/getMom.cpp"
#include "src/getMomList.cpp"
#include "src/getAngle.cpp"
#include "eventCorr.cpp"
#include "makeRatio.cpp"

void plot_Evcorr(string angle="21", string spec="shms",float xbmin=0.0, float xbmax=1.0, float ymin=0.98, float ymax = 1.01, int choice =1){

 string pset[4];
 float psetf[4];
 getMomList(angle,pset,psetf);
 TCanvas *c1=new TCanvas();
 c1->Divide(2,1);
 c1->cd(1);
 TGraphErrors *grh1=eventCorr("shms","h",angle,pset[0],choice);

 grh1->Draw("ap");

 c1->cd(2);

 TGraphErrors *grd1=eventCorr("shms","d",angle,pset[0],choice);

 grd1->Draw("ap");

  return;
}
