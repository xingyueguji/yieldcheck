#include "./extractCS.cpp"


void plot_d21deg_zh(){
  ////////////////////////////////////////
  ////////   Data   /////////////////////
  ////////////////////////////////////////
 TGraphErrors *gr5p7=extractCS("hms","d","21","5p7",8,"pass326","w2",0);
 TGraphErrors *gr5p1=extractCS("hms","d","21","5p1",8,"pass326","w2",0);
 TGraphErrors *gr4p5=extractCS("hms","d","21","4p5",8,"pass326","w2",0);
 TGraphErrors *gr4p0=extractCS("hms","d","21","4p0",8,"pass326","w2",0);
 TGraphErrors *gr3p3=extractCS("hms","d","21","3p3",8,"pass326","w2",0);
 TGraph2D *gm = getRadCorrW2("d",1,"hms","v996t2");
 double w2array[100];
 for (int i=0;i<100;i++){
  w2array[i] = 1+ i*0.5;
 }
 double bornarray[100];
 for (int j=0;j<100;j++){
  bornarray[j] = gm->Interpolate(w2array[j],21);
 }
 TGraph *model = new TGraph(100,&w2array[0],&bornarray[0]);



 gr5p7->SetMarkerStyle(23);
 gr5p1->SetMarkerStyle(23);
 gr4p5->SetMarkerStyle(23);
 gr4p0->SetMarkerStyle(23);
 gr3p3->SetMarkerStyle(23);
 gr5p7->SetMarkerColor(kRed);
 gr5p1->SetMarkerColor(kOrange);
 gr4p5->SetMarkerColor(kGreen+3);
 gr4p0->SetMarkerColor(kViolet);
 gr3p3->SetMarkerColor(kCyan);
 model->SetLineColor(kBlack);
model->GetXaxis()->SetLimits(0,12);
model->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
model->GetXaxis()->SetTitle("W2 (GeV^2)");
model->SetTitle("xsection for Deuteron 21 degrees hms data");
model->Draw("ac");
gr5p7->GetXaxis()->SetRange(0,12);
gr5p7->Draw("sp");
gr5p1->GetXaxis()->SetRange(0,12);
gr5p1->Draw("sp");
gr4p5->GetXaxis()->SetRange(0,12);
gr4p5->Draw("sp");
gr4p0->GetXaxis()->SetRange(0,12);
gr4p0->Draw("sp");
gr3p3->GetXaxis()->SetRange(0,12);
gr3p3->Draw("sp");

 TLegend *leg=new TLegend(.6,.6,.9,.9);
 leg->AddEntry(model,"v996t2(Born)","l");
 leg->AddEntry(gr5p7,"E'=5.7 GeV/c","p");
 leg->AddEntry(gr5p1,"E'=5.1 GeV/c","p");
 leg->AddEntry(gr4p5,"E'=4.5 GeV/c","p");
 leg->AddEntry(gr4p0,"E'=4 GeV/c","p");
 leg->AddEntry(gr3p3,"E'=3.3 GeV/c","p");
 leg->Draw();

  return;
}
