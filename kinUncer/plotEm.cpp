#include "getKinErrorFromMc.cpp"


void formatMe(TH1F* h, string name, int col)
{

  h->GetYaxis()->SetRangeUser(.9,1.1);
  h->GetXaxis()->SetRangeUser(-10,22);
  h->SetTitle(name.c_str());
  h->SetMarkerStyle(33);
  h->SetMarkerColor(col);
}
void plotEm(string angle="21", string mom="5p1",string spec="shms"){
  TString kin=angle+"deg "+mom+ "GeV "+spec;
  TH1F* h38=unc("h",angle,mom,spec,"pass38");
  TH1F* d38=unc("d",angle,mom,spec,"pass38");
  TH1F* r38=unc("r",angle,mom,spec,"pass38");

  TH1F* h39=unc("h",angle,mom,spec,"pass39");
  TH1F* d39=unc("d",angle,mom,spec,"pass39");
  TH1F* r39=unc("r",angle,mom,spec,"pass39");

  TH1F* h40=unc("h",angle,mom,spec,"pass40");
  TH1F* d40=unc("d",angle,mom,spec,"pass40");
  TH1F* r40=unc("r",angle,mom,spec,"pass40");

  TH1F* h41=unc("h",angle,mom,spec,"pass41");
  TH1F* d41=unc("d",angle,mom,spec,"pass41");
  TH1F* r41=unc("r",angle,mom,spec,"pass41");

  TH1F* h42=unc("h",angle,mom,spec,"pass42");
  TH1F* d42=unc("d",angle,mom,spec,"pass42");
  TH1F* r42=unc("r",angle,mom,spec,"pass42");

  TH1F* h43=unc("h",angle,mom,spec,"pass43");
  TH1F* d43=unc("d",angle,mom,spec,"pass43");
  TH1F* r43=unc("r",angle,mom,spec,"pass43");

  TH1F* htot_h=getKinErrorFromMc("h",angle,mom,spec);
  htot_h->SetName("htot_h");
  TH1F* htot_d=getKinErrorFromMc("d",angle,mom,spec);
  htot_d->SetName("htot_d");
  TH1F* htot_r=getKinErrorFromMc("r",angle,mom,spec);
  htot_r->SetName("htot_r");


  formatMe(htot_h,"Hydrogen",28);
  formatMe(htot_d,"Deuterium",28);
  formatMe(htot_r,"D/H ratio",28);

  formatMe(h38,"Hydrogen",1);
  formatMe(d38,"Deuterium",1);
  formatMe(r38,"D/H ratio",1);

  formatMe(h39,"Hydrogen",2);
  formatMe(d39,"Deuterium",2);
  formatMe(r39,"D/H ratio",2);

  formatMe(h40,"Hydrogen",4);
  formatMe(d40,"Deuterium",4);
  formatMe(r40,"D/H ratio",4);

  formatMe(h41,"Hydrogen",6);
  formatMe(d41,"Deuterium",6);
  formatMe(r41,"D/H ratio",6);

  formatMe(h42,"Hydrogen",8);
  formatMe(d42,"Deuterium",8);
  formatMe(r42,"D/H ratio",8);

  formatMe(h43,"Hydrogen",9);
  formatMe(d43,"Deuterium",9);
  formatMe(r43,"D/H ratio",9);


  TPaveText* tb=new TPaveText(.1,.7,.9,.9);
  tb->AddText(kin);
  TLine *t=new TLine(16,.9,16,1.1);

  TCanvas *c1=new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  h38->Draw("p");
  h39->Draw("same p");
  h40->Draw("same p");
  h41->Draw("same p");
  h42->Draw("same p");
  h43->Draw("same p");
  htot_h->Draw("same");

  if(mom=="5p1")t->Draw("same");

  c1->cd(2);
  d38->Draw("p");
  d39->Draw("same p");
  d40->Draw("same p");
  d41->Draw("same p");
  d42->Draw("same p");
  d43->Draw("same p");
  htot_d->Draw("same");
  if(mom=="5p1")t->Draw("same");


  c1->cd(3);
  r38->Draw("p");
  r39->Draw("same p");
  r40->Draw("same p");
  r41->Draw("same p");
  r42->Draw("same p");
  r43->Draw("same p");
  htot_r->Draw("same");
  if(mom=="5p1")t->Draw("same");

  c1->cd(4);
  tb->Draw("same");
  TLegend *leg=new TLegend(.1,.1,.9,.7);
    leg->AddEntry(h38,"#theta_{C} + 0.25 mr","p");
    leg->AddEntry(h39,"#theta_{C} - 0.25 mr","p");
    leg->AddEntry(h40,"Ebeam +0.1%","p");
    leg->AddEntry(h41,"Ebeam -0.1%","p");
    leg->AddEntry(h42,"E' +0.1%","p");
    leg->AddEntry(h43,"E' +0.1%","p");
    leg->AddEntry(htot_h,"Total Error","p");

    leg->Draw();
}
