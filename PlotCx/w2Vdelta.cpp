#include "src/getMomList.cpp"
#include "extractCS.cpp"

void w2Vdelta(string ang="21"){
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
  c1->Divide(1,3);


  TGraphErrors *g13, *g14, *g15;
  TGraphErrors *g32, *g33, *g34;
  auto g1=extractCS(spec,"h",angle,pset[0],0);
  auto g2=extractCS(spec,"h",angle,pset[1],0);
  auto g3=extractCS(spec,"h",angle,pset[2],0);
  auto g4=extractCS(spec,"h",angle,pset[3],0);
  auto g5=extractCS(spec,"d",angle,pset[0],0);
  auto g6=extractCS(spec,"d",angle,pset[1],0);
  auto g7=extractCS(spec,"d",angle,pset[2],0);
  auto g8=extractCS(spec,"d",angle,pset[3],0);
  auto g9=extractCS(spec,"r",angle,pset[0],0);
  auto g10=extractCS(spec,"r",angle,pset[1],0);
  auto g11=extractCS(spec,"r",angle,pset[2],0);
  auto g12=extractCS(spec,"r",angle,pset[3],0);
  if(spec=="hms"){
  g13=extractCS(spec,"h",angle,pset[4],0);
  g14=extractCS(spec,"d",angle,pset[4],0);
  g15=extractCS(spec,"r",angle,pset[4],0);
  }
  auto g20=extractCS(spec,"h",angle,pset[0],5);
  auto g21=extractCS(spec,"h",angle,pset[1],5);
  auto g22=extractCS(spec,"h",angle,pset[2],5);
  auto g23=extractCS(spec,"h",angle,pset[3],5);
  auto g24=extractCS(spec,"d",angle,pset[0],5);
  auto g25=extractCS(spec,"d",angle,pset[1],5);
  auto g26=extractCS(spec,"d",angle,pset[2],5);
  auto g27=extractCS(spec,"d",angle,pset[3],5);
  auto g28=extractCS(spec,"r",angle,pset[0],5);
  auto g29=extractCS(spec,"r",angle,pset[1],5);
  auto g30=extractCS(spec,"r",angle,pset[2],5);
  auto g31=extractCS(spec,"r",angle,pset[3],5);

  if(spec=="hms"){
  g32=extractCS(spec,"h",angle,pset[4],5);
  g33=extractCS(spec,"d",angle,pset[4],5);
  g34=extractCS(spec,"r",angle,pset[4],5);
  }

  g1->SetTitle("Hydrogen");
  g5->SetTitle("Deuterium");
  g9->SetTitle("D/H");
  g1->SetMarkerStyle(20);
  g2->SetMarkerStyle(20);
  g3->SetMarkerStyle(20);
  g4->SetMarkerStyle(20);
  g5->SetMarkerStyle(20);
  g6->SetMarkerStyle(20);
  g7->SetMarkerStyle(20);
  g8->SetMarkerStyle(20);
  g9->SetMarkerStyle(20);
  g10->SetMarkerStyle(20);
  g11->SetMarkerStyle(20);
  g12->SetMarkerStyle(20);

  if(spec=="hms"){
  g13->SetMarkerStyle(20);
  g14->SetMarkerStyle(20);
  g15->SetMarkerStyle(20);
  g32->SetMarkerStyle(25);
  g33->SetMarkerStyle(25);
  g34->SetMarkerStyle(25);
  g13->SetMarkerColor(kRed);
  g14->SetMarkerColor(kRed);
  g15->SetMarkerColor(kRed);
  g32->SetMarkerColor(kRed);
  g33->SetMarkerColor(kRed);
  g34->SetMarkerColor(kRed);
  }

  g20->SetMarkerStyle(25);
  g21->SetMarkerStyle(25);
  g22->SetMarkerStyle(25);
  g23->SetMarkerStyle(25);
  g24->SetMarkerStyle(25);
  g25->SetMarkerStyle(25);
  g26->SetMarkerStyle(25);
  g27->SetMarkerStyle(25);
  g28->SetMarkerStyle(25);
  g29->SetMarkerStyle(25);
  g30->SetMarkerStyle(25);
  g31->SetMarkerStyle(25);


  g1->SetMarkerColor(kRed);
  g3->SetMarkerColor(kRed);
  g5->SetMarkerColor(kRed);
  g7->SetMarkerColor(kRed);
  g9->SetMarkerColor(kRed);
  g11->SetMarkerColor(kRed);





  g21->SetMarkerColor(kBlue);
  g23->SetMarkerColor(kBlue);
  g25->SetMarkerColor(kBlue);
  g27->SetMarkerColor(kBlue);
  g29->SetMarkerColor(kBlue);
  g31->SetMarkerColor(kBlue);

    g1->GetYaxis()->SetRangeUser(.80,1.2);
    g5->GetYaxis()->SetRangeUser(.80,1.2);
    g9->GetYaxis()->SetRangeUser(.80,1.2);
    g1->GetXaxis()->SetTitle("W2    ");
    g5->GetXaxis()->SetTitle("W2    ");
    g9->GetXaxis()->SetTitle("W2    ");
    //    g1->GetXaxis()->SetTitle("Xb    ");
    //    g5->GetXaxis()->SetTitle("Xb    ");
    //    g9->GetXaxis()->SetTitle("Xb    ");

    g1->GetYaxis()->SetTitle("Data/Model");
    g5->GetYaxis()->SetTitle("Data/Model");
    g9->GetYaxis()->SetTitle("Data/Model");
    g1->GetXaxis()->SetLimits(0,14.);
    g5->GetXaxis()->SetLimits(0,14.);
    g9->GetXaxis()->SetLimits(0,14.);
    //g1->GetXaxis()->SetLimits(.2,1.);
    //    g5->GetXaxis()->SetLimits(.2,1.);
    //    g9->GetXaxis()->SetLimits(.2,1.);


  c1->cd(1);
  gPad->SetLeftMargin(.06);
  g1->Draw("ap");
  g2->Draw("sp");
  g3->Draw("sp");
  g4->Draw("sp");
  g20->Draw("sp");
  g21->Draw("sp");
  g22->Draw("sp");
  g23->Draw("sp");
  if(spec=="hms")g13->Draw("sp");
  if(spec=="hms")g32->Draw("sp");

  c1->cd(2);
  gPad->SetLeftMargin(.06);
  g5->Draw("ap");
  g6->Draw("sp");
  g7->Draw("sp");
  g8->Draw("sp");
  g24->Draw("sp");
  g25->Draw("sp");
  g26->Draw("sp");
  g27->Draw("sp");
  if(spec=="hms")g14->Draw("sp");
  if(spec=="hms")g33->Draw("sp");
  c1->cd(3);
  gPad->SetLeftMargin(.06);
  g9->Draw("ap");
  g10->Draw("sp");
  g11->Draw("sp");
  g12->Draw("sp");
  g28->Draw("sp");
  g29->Draw("sp");
  g30->Draw("sp");
  g31->Draw("sp");
  if(spec=="hms")g15->Draw("sp");
  if(spec=="hms")g34->Draw("sp");
  TLegend *l1=new TLegend(.9,.36,.99,.8);
  l1->AddEntry(g1,"Delta Binning","p");
  l1->AddEntry(g2,"Delta Binning","p");
  l1->AddEntry(g24,"W2 Binning","p");
  l1->AddEntry(g25,"W2 Binning","p");
  c1->cd(1);l1->Draw();
  c1->cd(2);l1->Draw();
  c1->cd(3);l1->Draw();
  TPaveText *tt=new TPaveText(.9,.12,.99,.33,"NDC");
  tt->AddText(angle.c_str());
  tt->AddText(spec.c_str());
  c1->cd(1);tt->Draw();
  c1->cd(2);tt->Draw();
  c1->cd(3);tt->Draw();

  //  c1->SaveAs("w2vsDelta.pdf");
  c1->SaveAs(Form("w2VsDelta%s.pdf",ang.c_str()));
  return;
}
