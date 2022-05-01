#include "src/getMomList.cpp"
#include "extractCS.cpp"


TGraphErrors *percDiff(TGraphErrors *g1, TGraphErrors *g2,
		       TGraphErrors *g3, TGraphErrors *g4,
		       TGraphErrors *g5, TGraphErrors *g6,
		       TGraphErrors *g7, TGraphErrors *g8,
		       TGraphErrors *g9, TGraphErrors *g10,
		       string spec, string target, string angle){

  string kin = spec+"_"+target+angle+"deg";
  vector <double> xx,yy, ye;
  int n;
  /////////////////////////////////////
  n=g1->GetN();
  for(int i=0; i<n;i++){
    double x1,y1;
    double x2,y2;
    g1->GetPoint(i,x1,y1);
    g2->GetPoint(i,x2,y2);
    xx.push_back(x1);
    yy.push_back( (y1-y2) / ((y1+y2)/2) * 100.);
  }
  /////////////////////////////////////
  n=g3->GetN();
  for(int i=0; i<n;i++){
    double x1,y1;
    double x2,y2;
    g3->GetPoint(i,x1,y1);
    g4->GetPoint(i,x2,y2);
    xx.push_back(x1);
    yy.push_back( (y1-y2) / ((y1+y2)/2) * 100.);
  }
  /////////////////////////////////////
  n=g5->GetN();
  for(int i=0; i<n;i++){
    double x1,y1;
    double x2,y2;
    g5->GetPoint(i,x1,y1);
    g6->GetPoint(i,x2,y2);
    xx.push_back(x1);
    yy.push_back( (y1-y2) / ((y1+y2)/2) * 100.);
  }
  /////////////////////////////////////
  n=g7->GetN();
  for(int i=0; i<n;i++){
    double x1,y1;
    double x2,y2;
    g7->GetPoint(i,x1,y1);
    g8->GetPoint(i,x2,y2);
    xx.push_back(x1);
    yy.push_back( (y1-y2) / ((y1+y2)/2) * 100.);
  }

  /////////////////////////////////////
  if(spec=="hms"){
    n=g9->GetN();
    for(int i=0; i<n;i++){
      double x1,y1;
      double x2,y2;
      g9->GetPoint(i,x1,y1);
      g10->GetPoint(i,x2,y2);
      xx.push_back(x1);
      yy.push_back( (y1-y2) / ((y1+y2)/2) * 100.);
    }
  }
  int pts=xx.size();
  TGraphErrors *gr=new TGraphErrors(pts,&xx[0],&yy[0],0,&ye[0]);
  gr->SetName(kin.c_str());
  gr->SetMarkerStyle(33);
  return gr;
  }

void scaleIt(TGraphErrors *g, string spec, string target, string angle){
			 
  TGraph2D *grh=getRadCorrW2("h",1,spec.c_str(),"v0.990");  
  grh->SetName("grh");
  TGraph2D *grd=getRadCorrW2("d",1,spec.c_str(),"v0.990");  
  grd->SetName("grd");
  TGraph2D *grhn=getRadCorrW2("h",1,spec.c_str());  
  grhn->SetName("grhn");
  TGraph2D *grdn=getRadCorrW2("d",1,spec.c_str());  
  grdn->SetName("grdn");
  Double_t thetac=getAngle(angle,spec);

  int n=g->GetN();
  for(int i=0; i<n;i++){
    double w2,y;
    g->GetPoint(i,w2,y);

    double modeld=grd->Interpolate(w2,thetac);  //<<"\t"<<
    double modelh=grh->Interpolate(w2,thetac);  //<<"\t"<<
    double modeldn=grdn->Interpolate(w2,thetac);  //<<"\t"<<
    double modelhn=grhn->Interpolate(w2,thetac);  //<<"\t"<<
    if((w2-2.04)<.03){

    cout <<"born_h v996: "<<modelhn<<endl;
    cout <<"born_h v990: "<<modelh<<endl;
    cout <<"ratio: modelhn/modelh "<<modelhn/modelh<<endl;
    cout << "w2,theta: " <<w2<<"\t"<<thetac<<endl;
    }

    if(target=="h")y=y*modelh/modelhn;
    if(target=="d")y=y*modeld/modeldn;
    if(target=="r")y=y*modeld/modeldn*modelhn/modelh;
    g->SetPoint(i,w2,y);
  }
}

void w2VdiffModels(string ang="21"){
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
  TCanvas *c2=new TCanvas("c2","c2",900,600);
  c2->Divide(1,3);
  //TGraphErrors* extractCS(string spec="shms", string target="h", string angle="21",string mom="5p1", int cs=5, string pass="pass314", string xaxis="w2"){

  TGraphErrors *g13, *g14, *g15;
  TGraphErrors *g32, *g33, *g34;

  auto g1=extractCS(spec,"h",angle,pset[0],0,"pass314");
  auto g2=extractCS(spec,"h",angle,pset[1],0,"pass314");
  auto g3=extractCS(spec,"h",angle,pset[2],0,"pass314");
  auto g4=extractCS(spec,"h",angle,pset[3],0,"pass314");
  auto g5=extractCS(spec,"d",angle,pset[0],0,"pass314");
  auto g6=extractCS(spec,"d",angle,pset[1],0,"pass314");
  auto g7=extractCS(spec,"d",angle,pset[2],0,"pass314");
  auto g8=extractCS(spec,"d",angle,pset[3],0,"pass314");
  auto g9=extractCS(spec,"r",angle,pset[0],0,"pass314");
  auto g10=extractCS(spec,"r",angle,pset[1],0,"pass314");
  auto g11=extractCS(spec,"r",angle,pset[2],0,"pass314");
  auto g12=extractCS(spec,"r",angle,pset[3],0,"pass314");
  if(spec=="hms"){
  g13=extractCS(spec,"h",angle,pset[4],0,"pass314");
  g14=extractCS(spec,"d",angle,pset[4],0,"pass314");
  g15=extractCS(spec,"r",angle,pset[4],0,"pass314");
  }

  auto g20=extractCS(spec,"h",angle,pset[0],0,"pass316");
  auto g21=extractCS(spec,"h",angle,pset[1],0,"pass316");
  auto g22=extractCS(spec,"h",angle,pset[2],0,"pass316");
  auto g23=extractCS(spec,"h",angle,pset[3],0,"pass316");
  auto g24=extractCS(spec,"d",angle,pset[0],0,"pass316");
  auto g25=extractCS(spec,"d",angle,pset[1],0,"pass316");
  auto g26=extractCS(spec,"d",angle,pset[2],0,"pass316");
  auto g27=extractCS(spec,"d",angle,pset[3],0,"pass316");
  auto g28=extractCS(spec,"r",angle,pset[0],0,"pass316");
  auto g29=extractCS(spec,"r",angle,pset[1],0,"pass316");
  auto g30=extractCS(spec,"r",angle,pset[2],0,"pass316");
  auto g31=extractCS(spec,"r",angle,pset[3],0,"pass316");
  scaleIt(g20,spec,"h",angle);
  scaleIt(g21,spec,"h",angle);
  scaleIt(g22,spec,"h",angle);
  scaleIt(g23,spec,"h",angle);
  scaleIt(g24,spec,"d",angle);
  scaleIt(g25,spec,"d",angle);
  scaleIt(g26,spec,"d",angle);
  scaleIt(g27,spec,"d",angle);
  scaleIt(g28,spec,"r",angle);
  scaleIt(g29,spec,"r",angle);
  scaleIt(g30,spec,"r",angle);
  scaleIt(g31,spec,"r",angle);
  if(spec=="hms"){
  g32=extractCS(spec,"h",angle,pset[4],0,"pass316");
  g33=extractCS(spec,"d",angle,pset[4],0,"pass316");
  g34=extractCS(spec,"r",angle,pset[4],0,"pass316");
  scaleIt(g32,spec,"h",angle);
  scaleIt(g33,spec,"d",angle);
  scaleIt(g34,spec,"r",angle);

  }

  TGraphErrors *g40,*g41,*g42;
  g40=percDiff(g1,g20,g2,g21,g3,g22,g4,g23,g13,g32,spec,"h",angle);
  g41=percDiff(g5,g24,g6,g25,g7,g26,g8,g27,g14,g33,spec,"d",angle);
  g42=percDiff(g9,g28,g10,g29,g11,g30,g12,g31,g15,g34,spec,"r",angle);
  g40->SetTitle("Hydrogen");
  g41->SetTitle("Deuterium");
  g42->SetTitle("D/H");
  g40->GetXaxis()->SetTitle("W2    ");
  g41->GetXaxis()->SetTitle("W2    ");
  g42->GetXaxis()->SetTitle("W2    ");
  //    g1->GetXaxis()->SetTitle("Xb    ");
  //    g5->GetXaxis()->SetTitle("Xb    ");
  //    g9->GetXaxis()->SetTitle("Xb    ");

  g40->GetYaxis()->SetTitle("Percent Difference (%)");
  g41->GetYaxis()->SetTitle("Percent Difference (%)");
  g42->GetYaxis()->SetTitle("Percent Difference (%)");
  g40->GetYaxis()->SetRangeUser(-15,15);
  g41->GetYaxis()->SetRangeUser(-15,15);
  g42->GetYaxis()->SetRangeUser(-15,15);
  //    g40->GetXaxis()->SetTitle("Xb    ");
  //    g41->GetXaxis()->SetTitle("Xb    ");
  //    g42->GetXaxis()->SetTitle("Xb    ");
  
  g40->GetXaxis()->SetLimits(0,14.);
  g41->GetXaxis()->SetLimits(0,14.);
  g42->GetXaxis()->SetLimits(0,14.);


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

  g1->GetYaxis()->SetRangeUser(.7,1.3);
  g5->GetYaxis()->SetRangeUser(.7,1.3);
  g9->GetYaxis()->SetRangeUser(.7,1.3);
  g1->GetXaxis()->SetTitle("W2    ");
  g5->GetXaxis()->SetTitle("W2    ");
  g9->GetXaxis()->SetTitle("W2    ");
  //    g1->GetXaxis()->SetTitle("Xb    ");
  //    g5->GetXaxis()->SetTitle("Xb    ");
  //    g9->GetXaxis()->SetTitle("Xb    ");
  
  g1->GetYaxis()->SetTitle("#sigma/model_{v0.996}");
  g5->GetYaxis()->SetTitle("#sigma/model_{v0.996}");
  g9->GetYaxis()->SetTitle("#sigma/model_{v0.996}");
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
  TLegend *l1=new TLegend(.9,.46,.99,.89);
  l1->AddEntry(g1,"v990","p");
  l1->AddEntry(g2,"v990","p");
  l1->AddEntry(g24,"v996t2","p");
  l1->AddEntry(g25,"v996t2","p");
  c1->cd(1);l1->Draw();
  c1->cd(2);l1->Draw();
  c1->cd(3);l1->Draw();
  TPaveText *tt=new TPaveText(.9,.12,.99,.43,"NDC");
  tt->AddText("Delta Binning");
  tt->AddText(angle.c_str());
  tt->AddText(spec.c_str());
  c1->cd(1);tt->Draw();
  c1->cd(2);tt->Draw();
  c1->cd(3);tt->Draw();


  //  c1->SaveAs("w2vsDelta.pdf");
  c1->SaveAs(Form("modelDependence/%s_delta.pdf",ang.c_str()));

  c2->cd(1);
  gPad->SetLeftMargin(.06);
  g40->Draw("ap");
  tt->Draw("same");
  c2->cd(2);
  gPad->SetLeftMargin(.06);
  g41->Draw("ap");
  c2->cd(3);
  gPad->SetLeftMargin(.06);
  g42->Draw("ap");
  TPaveText *tt2=new TPaveText(.8,.12,.99,.88,"NDC");  
  tt2->AddText("Delta Binning");
  tt2->AddText("#frac{#sigma_{v0.996t2}  - #sigma_{v0.990}}{(#sigma_{v0.996t2} + #sigma_{v0.990})/2}");
  tt2->Draw();
  c2->SaveAs(Form("modelDependence/%s_percDiff_delta.pdf",ang.c_str()));
  return;
}
