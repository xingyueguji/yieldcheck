#include "src/getMom.cpp"
#include "src/getMomList.cpp"
#include "src/getAngle.cpp"
#include "eventCorr.cpp"
#include "makeRatio.cpp"

void plot_Evcorr(string angle="21", string spec="shms",float xbmin=0.0, float xbmax=1.0, float ymin=0.98, float ymax = 1.01, int choice =0){

 string pset[4];
 float psetf[4];
 getMomList(angle,pset,psetf);
 TCanvas *c1=new TCanvas();
 c1->Divide(3,1);
 c1->cd(1);
 TGraphErrors *grh1=eventCorr("shms","h",angle,pset[0],choice);
 TGraphErrors *grh2=eventCorr("shms","h",angle,pset[1],choice);
 TGraphErrors *grh3=eventCorr("shms","h",angle,pset[2],choice);
 TGraphErrors *grh4=eventCorr("shms","h",angle,pset[3],choice);
 grh1->SetName("grh1");
 grh3->SetName("grh2");
 grh3->SetName("grh3");
 grh4->SetName("grh4");
 string prefix;
 if(choice==1)prefix="Tracking Eff.";
 if(choice==0)prefix="Pion Contamination Factor";
 if(choice==2)prefix="Livetime";
 if(choice==3)prefix="Prescale Fact.";

 grh1->SetTitle(Form("Hydrogen %sdeg",angle.c_str()));
 grh1->GetYaxis()->SetTitle(prefix.c_str());
 grh1->GetXaxis()->SetTitle("X_B");
 grh1->Draw("ap");
 grh1->GetYaxis()->SetRangeUser(ymin,ymax);
 grh1->GetXaxis()->SetLimits(xbmin,xbmax);
 grh1->SetMarkerStyle(27);
 grh2->SetMarkerStyle(27);
 grh3->SetMarkerStyle(27);
 grh4->SetMarkerStyle(27);

 grh1->SetMarkerSize(.6);
 grh2->SetMarkerSize(.6);
 grh3->SetMarkerSize(.6);
 grh4->SetMarkerSize(.6);

 grh1->SetMarkerColor(kRed);
 grh2->SetMarkerColor(kOrange);
 grh3->SetMarkerColor(kGreen+3);
 grh4->SetMarkerColor(kViolet);


 grh1->Draw("ap");
 grh2->Draw("sp");
 grh3->Draw("sp");
 grh4->Draw("sp");

 c1->cd(2);

 TGraphErrors *grd1=eventCorr("shms","d",angle,pset[0],choice);
 TGraphErrors *grd2=eventCorr("shms","d",angle,pset[1],choice);
 TGraphErrors *grd3=eventCorr("shms","d",angle,pset[2],choice);
 TGraphErrors *grd4=eventCorr("shms","d",angle,pset[3],choice);

 grd1->SetName("grd1");
 grd3->SetName("grd2");
 grd3->SetName("grd3");
 grd4->SetName("grd4");

 grd1->Draw("ap");
 grd1->SetTitle(Form("Deuterium %sdeg",angle.c_str()));
 grd1->GetYaxis()->SetTitle(prefix.c_str());
 grd1->GetXaxis()->SetTitle("X_B");

 grd1->GetYaxis()->SetRangeUser(ymin,ymax);
 grd1->GetXaxis()->SetLimits(xbmin,xbmax);
 grd1->SetMarkerStyle(27);
 grd2->SetMarkerStyle(27);
 grd3->SetMarkerStyle(27);
 grd4->SetMarkerStyle(27);

 grd1->SetMarkerSize(.6);
 grd2->SetMarkerSize(.6);
 grd3->SetMarkerSize(.6);
 grd4->SetMarkerSize(.6);

 grd1->SetMarkerColor(kRed);
 grd2->SetMarkerColor(kOrange);
 grd3->SetMarkerColor(kGreen+3);
 grd4->SetMarkerColor(kViolet);


 grd1->Draw("ap");
 grd2->Draw("sp");
 grd3->Draw("sp");
 grd4->Draw("sp");

 c1->cd(3);

 TGraphErrors *grr1=makeRatio(grd1,grh1);
 TGraphErrors *grr2=makeRatio(grd2,grh2);
 TGraphErrors *grr3=makeRatio(grd3,grh3);
 TGraphErrors *grr4=makeRatio(grd4,grh4);

 grr1->Draw("ap");
 grr1->SetTitle(Form("D/H %sdeg",angle.c_str()));
 grr1->GetYaxis()->SetTitle(prefix.c_str());
 grr1->GetXaxis()->SetTitle("X_B");
 grr1->GetYaxis()->SetRangeUser(ymin,ymax);
 //  grr1->GetYaxis()->SetRangeUser(0.9,1.1);
 grr1->GetXaxis()->SetLimits(xbmin,xbmax);
 grr1->SetMarkerStyle(27);
 grr2->SetMarkerStyle(27);
 grr3->SetMarkerStyle(27);
 grr4->SetMarkerStyle(27);

 grr1->SetMarkerSize(.6);
 grr2->SetMarkerSize(.6);
 grr3->SetMarkerSize(.6);
 grr4->SetMarkerSize(.6);

 grr1->SetMarkerColor(kRed);
 grr2->SetMarkerColor(kOrange);
 grr3->SetMarkerColor(kGreen+3);
 grr4->SetMarkerColor(kViolet);


 grr1->Draw("ap");
 grr2->Draw("sp");
 grr3->Draw("sp");
 grr4->Draw("sp");
 TLegend *leg=new TLegend(.4,.15,.6,.35);

 leg->AddEntry(grh1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(grh2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(grh3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(grh4,Form("E'=%2.2f GeV/c",psetf[3]),"p");
 // leg->Draw("same");
 c1->SaveAs(Form("%sdeg_%d.pdf",angle.c_str(),choice));
  return;
}
