void checkcs(){
  TGraph *gr1=new TGraph();
  TGraph *gr2=new TGraph();
  TGraph *gr3=new TGraph();
  TGraph *gr4=new TGraph();

  TGraph *gr11=new TGraph();
  TGraph *gr12=new TGraph();
  TGraph *gr13=new TGraph();
  TGraph *gr14=new TGraph();

  TGraph *gr91=new TGraph();
  TGraph *gr92=new TGraph();
  TGraph *gr93=new TGraph();
  TGraph *gr94=new TGraph();

  Double_t e,ep,th,x,q2,sig,d1,d2,sigrad,d3,d4,d5,d6;
  Double_t e1,ep1,th1,x1,q21,sig1,d11,d21,sigrad1,d31,d41,d51,d61;
  cout<<"start"<<endl;
  ifstream file1;
  file1.open(Form("externals/v0.982/d_sep/d10.6_21.0_f1f220.out"));
  ifstream file11;
  file11.open(Form("externals/v0.982/h_sep/h10.6_21.0_f1f220.out"));
  while(true){
    file1>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    file11>>e1>>ep1>>th1>>x1>>q21>>sig1>>d11>>d21>>sigrad1>>d31>>d41>>d51>>d61;
    if(file1.eof())break;
    if(ep!=ep1)break;
    gr1->SetPoint(gr1->GetN(),x,sig);
    gr11->SetPoint(gr11->GetN(),x,sig1);
    if(sig1>0)gr91->SetPoint(gr91->GetN(),x,sig/sig1);
  }
  file1.close();
  file11.close();
  cout<<"file1"<<endl;
  ifstream file2;
  file2.open(Form("externals/v0.990/d_sep/d10.6_21.0_f1f220.out"));
  ifstream file12;
  file12.open(Form("externals/v0.990/h_sep/h10.6_21.0_f1f220.out"));
  while(true){
    file2>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    file12>>e1>>ep1>>th1>>x1>>q21>>sig1>>d11>>d21>>sigrad1>>d31>>d41>>d51>>d61;
    if(file2.eof())break;
    if(ep!=ep1)break;
    gr2->SetPoint(gr2->GetN(),x,sig);
    gr12->SetPoint(gr12->GetN(),x,sig1);
    if(sig1>0)gr92->SetPoint(gr92->GetN(),x,sig/sig1);
  }
  file2.close();
  file12.close();
  cout<<"file2"<<endl;
  ifstream file3;
  file3.open(Form("externals/v0.996t2/d_sep/d10.6_21.0_f1f221.out"));
  ifstream file13;
  file13.open(Form("externals/v0.996t2/h_sep/h10.6_21.0_f1f221.out"));
  while(true){
    file3>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    file13>>e1>>ep1>>th1>>x1>>q21>>sig1>>d11>>d21>>sigrad1>>d31>>d41>>d51>>d61;
    if(file3.eof())break;
    if(ep!=ep1)break;
    gr3->SetPoint(gr3->GetN(),x,sig);
    gr13->SetPoint(gr13->GetN(),x,sig1);
    if(sig1>0)gr93->SetPoint(gr93->GetN(),x,sig/sig1);

  }
  file3.close();
  file13.close();
  cout<<"file3"<<endl;
  ifstream file4;
  file4.open(Form("externals/v0.995/d_sep/d10.6_21.0_f1f221.out"));
  ifstream file14;
  file14.open(Form("externals/v0.995/h_sep/h10.6_21.0_f1f221.out"));
  while(true){
    file4>>e>>ep>>th>>x>>q2>>sig>>d1>>d2>>sigrad>>d3>>d4>>d5>>d6;
    file14>>e1>>ep1>>th1>>x1>>q21>>sig1>>d11>>d21>>sigrad1>>d31>>d41>>d51>>d61;
    if(file4.eof())break;
    if(ep!=ep1)break;
    gr4->SetPoint(gr4->GetN(),x,sig);
    gr14->SetPoint(gr14->GetN(),x,sig1);
    if(sig1>0)gr94->SetPoint(gr94->GetN(),x,sig/sig1);

  }
  file4.close();
  file14.close();
  cout<<"file4"<<endl;

  gr1->SetMarkerColor(kRed);
  gr2->SetMarkerColor(kBlue);
  gr3->SetMarkerColor(kGreen+1);
  gr4->SetMarkerColor(kCyan);
  gr1->SetLineColor(kRed);
  gr2->SetLineColor(kBlue);
  gr3->SetLineColor(kGreen+1);
  gr4->SetLineColor(kCyan);
  gr1->SetLineWidth(2);
  gr2->SetLineWidth(2);
  gr3->SetLineWidth(2);
  gr4->SetLineWidth(2);

  gr11->SetMarkerColor(kRed);
  gr12->SetMarkerColor(kBlue);
  gr13->SetMarkerColor(kGreen+1);
  gr14->SetMarkerColor(kCyan);
  gr11->SetLineColor(kRed);
  gr12->SetLineColor(kBlue);
  gr13->SetLineColor(kGreen+1);
  gr14->SetLineColor(kCyan);
  gr11->SetLineWidth(2);
  gr12->SetLineWidth(2);
  gr13->SetLineWidth(2);
  gr14->SetLineWidth(2);

  gr91->SetMarkerColor(kRed);
  gr92->SetMarkerColor(kBlue);
  gr93->SetMarkerColor(kGreen+1);
  gr94->SetMarkerColor(kCyan);
  gr91->SetLineColor(kRed);
  gr92->SetLineColor(kBlue);
  gr93->SetLineColor(kGreen+1);
  gr94->SetLineColor(kCyan);
  gr91->SetLineWidth(2);
  gr92->SetLineWidth(2);
  gr93->SetLineWidth(2);
  gr94->SetLineWidth(2);

  TCanvas *c1=new TCanvas();
  TMultiGraph *mg=new TMultiGraph();
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr4);
  mg->Add(gr3);
  mg->Draw("apl");
  TLegend *tl=new TLegend(0.7,0.6,0.9,0.9);
  tl->AddEntry(gr1,"v0.982","l");
  tl->AddEntry(gr2,"v0.990","l");
  tl->AddEntry(gr4,"v0.995","l");
  tl->AddEntry(gr3,"v0.996t2","l");
  tl->Draw();

  TCanvas *c2=new TCanvas();
  TMultiGraph *mg2=new TMultiGraph();
  mg2->Add(gr11);
  mg2->Add(gr12);
  mg2->Add(gr14);
  mg2->Add(gr13);
  mg2->Draw("apl");
  TLegend *tl2=new TLegend(0.7,0.6,0.9,0.9);
  tl2->AddEntry(gr11,"v0.982","l");
  tl2->AddEntry(gr12,"v0.990","l");
  tl2->AddEntry(gr14,"v0.995","l");
  tl2->AddEntry(gr13,"v0.996t2","l");
  tl2->Draw();


  TCanvas *c3=new TCanvas();
  TMultiGraph *mg3=new TMultiGraph();
  mg3->Add(gr91);
  mg3->Add(gr92);
  mg3->Add(gr94);
  mg3->Add(gr93);
  mg3->Draw("apl");
  TLegend *tl3=new TLegend(0.7,0.6,0.9,0.9);
  tl3->AddEntry(gr91,"v0.982","l");
  tl3->AddEntry(gr92,"v0.990","l");
  tl3->AddEntry(gr94,"v0.995","l");
  tl3->AddEntry(gr93,"v0.996t2","l");
  tl3->Draw();

}
