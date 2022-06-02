#include "src/getMomList.cpp"
#include "extractCS.cpp"
#include "abelw2comp.cpp"
void abelcomp(string ang="21"){
  gStyle->SetTitleX(.4);
  gStyle->SetTitleH(.1);
  gStyle->SetTitleW(.2);
  gStyle->SetTitleY(.99);
  gStyle->SetTitleSize(.06,"XY");
  gStyle->SetTitleOffset(.4,"XY");
  gStyle->SetLabelSize(.07,"XY");

  string spec="shms";
  string angle=ang; 
  if(ang=="20"){
    spec="hms";
    angle="21";
  }
  string pset[5];
  float psetf[5];
  getMomList(angle,pset,psetf,spec);

  TCanvas *c1=new TCanvas("c1","c1",900,600);
  c1->Divide(1,2);


  TGraphErrors *g13, *g14, *g15;
  TGraphErrors *g32, *g33, *g34;
  auto g1=abelw2comp(angle,"h");
  auto g2=abelw2comp(angle,"d");

  auto g20=extractCS(spec,"h",angle,pset[0],5);
  auto g21=extractCS(spec,"h",angle,pset[1],5);
  auto g22=extractCS(spec,"h",angle,pset[2],5);
  auto g23=extractCS(spec,"h",angle,pset[3],5);
  auto g24=extractCS(spec,"d",angle,pset[0],5);
  auto g25=extractCS(spec,"d",angle,pset[1],5);
  auto g26=extractCS(spec,"d",angle,pset[2],5);
  auto g27=extractCS(spec,"d",angle,pset[3],5);

  g1->SetTitle("Hydrogen");
  g2->SetTitle("Deuterium");

  g1->SetMarkerStyle(20);
  g2->SetMarkerStyle(20);

  g20->SetMarkerStyle(25);
  g21->SetMarkerStyle(25);
  g22->SetMarkerStyle(25);
  g23->SetMarkerStyle(25);
  g24->SetMarkerStyle(25);
  g25->SetMarkerStyle(25);
  g26->SetMarkerStyle(25);
  g27->SetMarkerStyle(25);

  g1->SetMarkerColor(kRed);
  g2->SetMarkerColor(kRed);

  g21->SetMarkerColor(kBlue);
  g23->SetMarkerColor(kBlue);
  g25->SetMarkerColor(kBlue);
  g27->SetMarkerColor(kBlue);


    g1->GetYaxis()->SetRangeUser(.80,1.2);
    g2->GetYaxis()->SetRangeUser(.80,1.2);

    g1->GetXaxis()->SetTitle("W2    ");
    g2->GetXaxis()->SetTitle("W2    ");

    //    g1->GetXaxis()->SetTitle("Xb    ");
    //    g5->GetXaxis()->SetTitle("Xb    ");
    //    g9->GetXaxis()->SetTitle("Xb    ");

    g1->GetYaxis()->SetTitle("Data/Model");
    g2->GetYaxis()->SetTitle("Data/Model");
    g1->GetXaxis()->SetLimits(0,14.);
    g2->GetXaxis()->SetLimits(0,14.);
    //g1->GetXaxis()->SetLimits(.2,1.);
    //    g5->GetXaxis()->SetLimits(.2,1.);
    //    g9->GetXaxis()->SetLimits(.2,1.);


  c1->cd(1);
  gPad->SetLeftMargin(.06);
  g1->Draw("ap");
  g20->Draw("sp");
  g21->Draw("sp");
  g22->Draw("sp");
  g23->Draw("sp");

  c1->cd(2);
  gPad->SetLeftMargin(.06);
  g2->Draw("ap");
  g24->Draw("sp");
  g25->Draw("sp");
  g26->Draw("sp");
  g27->Draw("sp");

  TLegend *l1=new TLegend(.9,.36,.99,.8);
  l1->AddEntry(g1,"Abel","p");
  l1->AddEntry(g24,"Bill","p");
  l1->AddEntry(g25,"Bill","p");
  c1->cd(1);l1->Draw();
  c1->cd(2);l1->Draw();
  c1->cd(3);l1->Draw();
  TPaveText *tt=new TPaveText(.9,.12,.99,.33,"NDC");
  tt->AddText(angle.c_str());
  tt->AddText(spec.c_str());
  c1->cd(1);tt->Draw();
  c1->cd(2);tt->Draw();

  //  c1->SaveAs("w2vsDelta.pdf");
  c1->SaveAs(Form("w2VsDelta%s.pdf",ang.c_str()));
  return;
}
