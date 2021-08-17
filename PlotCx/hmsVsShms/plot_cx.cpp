#include "src/formatHist.cpp"
#include "src/getRadCorrW2.cpp"
//#include "src/readReport.cpp"
#include "src/getMom.cpp"
#include "src/getMomList.cpp"
#include "src/getAngle.cpp"

TGraphErrors* extractCS(string spec="shms", string target="d", string angle="21",string mom="2p7", int cs=1){
  string kin;
  if(target=="r")kin="h"+angle+"deg"+mom;
  else kin=target+angle+"deg"+mom;
  Double_t pc=getMom(kin,spec);
  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);

  Double_t offset=1.;
  cout << "The central momentum is "<<hsec<<endl;
  if(spec=="hms"&&hsec<5.5){  
    //      offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
    // hsec=hsec*offset;
  }
  cout << "The central momentum is "<<hsec<<endl;
  //  Double_t thetac=21.035;
  Double_t thetac=getAngle(angle,spec);
  //  thetac=21.035;
  TGraph2D *grh;
  TGraph2D *grd;

//Weighted MC 
//TFile *fr=new TFile(Form("ratiosOut/ratios%d_1.root",run));
  TFile *frd;

  if(spec=="shms")
  frd=new TFile(Form("ratiosOut/pass106/%s_ratiosd%sdeg%s.root",spec.c_str(),angle.c_str(),mom.c_str()));

  if(spec=="hms")
        frd=new TFile(Form("ratiosOut/pass107/%s_ratiosd%sdeg%s.root",spec.c_str(),angle.c_str(),mom.c_str()));
    //        frd=new TFile(Form("hmsratios/ratiosd%sdeg%s_1.root",angle.c_str(),mom.c_str()));
    //   frd=new TFile(Form("hmsTest/ratiosd%sdeg%s_1.root",angle.c_str(),mom.c_str()));

  TH1F *hrdd=(TH1F*)frd->Get("hrd");  
  hrdd->SetDirectory(0);
  frd->Close();

  TFile *frh;

  if(spec=="shms")
  frh=new TFile(Form("ratiosOut/pass106/%s_ratiosh%sdeg%s.root",spec.c_str(),angle.c_str(),mom.c_str()));

  if(spec=="hms")
    frh=new TFile(Form("ratiosOut/pass107/%s_ratiosh%sdeg%s.root",spec.c_str(),angle.c_str(),mom.c_str()));
    //      frh=new TFile(Form("hmsratios/ratiosh%sdeg%s_1.root",angle.c_str(),mom.c_str()));
    //  frh=new TFile(Form("hmsTest/ratiosh%sdeg%s_1.root",angle.c_str(),mom.c_str()));

  TH1F *hrdh=(TH1F*)frh->Get("hrd");  
  hrdh->SetDirectory(0);
  frh->Close();

  grh=getRadCorrW2("h",1,spec.c_str());  
  grd=getRadCorrW2("d",1,spec.c_str());   

  const Int_t nbins=hrdd->GetNbinsX();
  Float_t deltad, ratiod, errd, ep, modeld;
  Float_t deltah, ratioh, errh, modelh;
  vector <float> cx;
  vector <float> cxe;
  vector <float> eprime;

  for (Int_t i=1; i<=nbins; i++)
   {
     deltad=hrdd->GetBinCenter(i);
     ratiod=hrdd->GetBinContent(i);
     errd=hrdd->GetBinError(i);


     deltah=hrdh->GetBinCenter(i);
     ratioh=hrdh->GetBinContent(i);
     errh=hrdh->GetBinError(i);


     ep=(1+deltah/100)*hsec;
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     Double_t w2= mp*mp + 2.*mp*nu-q2;
     modeld=grd->Interpolate(w2,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(w2,thetac);  //<<"\t"<<
     cout <<deltah<<"\t"<<ratioh<<"\t"<<errh<<"\t"<<modelh<<"\t"<<ep<<"\t"<<thetac<<endl;
     if(ratioh!=0 && ratiod!=0)
       {
     if(cs==1)
       {
     if(target=="h")cx.push_back(ratioh*modelh);
     if(target=="d")cx.push_back(ratiod*modeld);
     if(target=="r")cx.push_back(ratiod*modeld/ratioh/modelh/2.);
     if(target=="h")cxe.push_back(errh*modelh);
     if(target=="d")cxe.push_back(errd*modeld);
     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))/2.);
     eprime.push_back(xb);
     cout<<xb<<endl;
       }
     if(cs==0)
       {
     if(target=="h")cx.push_back(ratioh);
     if(target=="d")cx.push_back(ratiod);
     if(target=="r")cx.push_back(ratiod/ratioh);
     if(target=="h")cxe.push_back(errh);
     if(target=="d")cxe.push_back(errd);
     if(target=="r")cxe.push_back(sqrt(pow(errd,2)+pow(errh,2))/2.);
     eprime.push_back(xb);
       }
       }
   }
  int npts=cx.size();
 TGraphErrors*gcx=new TGraphErrors(npts,&eprime[0],&cx[0],0,&cxe[0]);
 return gcx;
}

void plot_cx(string target="r", string angle="21", string spec="hms",float xbmin=0.2, float xbmax=.95, float cxmin=0.0, float cxmax = 50.0, float ratiomin = 0.85, float ratiomax =1.15 ){

 string pset[4];
 float psetf[4];
 getMomList(angle,pset,psetf);
  ////////////////////////////////////////
  ////////   MODEL   /////////////////////
  ////////////////////////////////////////

 vector <float> mx;
 vector <float> my;
 Float_t delta, ratio, err, ep, modeld, modelh, xmin, xmax;
 xmin=psetf[0]*(.9);
 xmax=psetf[3]*(1.22);

 Double_t thetac=getAngle(angle,spec);
 // thetac=20.995;
 TGraph2D *grd=getRadCorrW2("d",1,spec.c_str());    
 TGraph2D *grh=getRadCorrW2("h",1,spec.c_str());  
 for (Int_t i=0;i<1000;i++)
   {
     //     ep=2.2+i/1000.*3.8;
     ep=xmin+i/1000.*(xmax-xmin);
     //     modeld=grd->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<
     //     modelh=grh->Interpolate(2.2+i/1000.*3.8,thetac);  //<<"\t"<<
     Double_t ebeam=10.602;
     Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
     Double_t nu= ebeam-ep;
     Double_t q2 = 4.*ep*ebeam*sin2;
     Float_t mp = .9382723;
     Double_t xb=q2/2./mp/nu;
     Double_t w2= mp*mp + 2.*mp*nu-q2;
     modeld=grd->Interpolate(w2,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(w2,thetac);  //<<"\t"<<

     if(modelh!=0 && modeld!=0){ 
       mx.push_back(xb);
       if(target=="r")my.push_back(modeld/modelh/2.);
       if(target=="h")my.push_back(modelh);
       if(target=="d")my.push_back(modeld);
     }
   }
 Int_t pts=mx.size();
 TGraph *gm=new TGraph(pts,&mx[0],&my[0]);

 gm->GetXaxis()->SetTitle("Bjorken X");

 gm->SetLineColor(kBlack);
 gm->GetXaxis()->SetLimits(xbmin,xbmax);
 // gm->GetXaxis()->SetRangeUser(xbmin,xbmax);
 if(target=="h"){
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
 gm->SetTitle(Form("SHMS vs HMS Hydrogen %sdeg",angle.c_str()));
 gm->GetYaxis()->SetRangeUser(cxmin,cxmax);
 }
 if(target=="d"){
 gm->GetYaxis()->SetTitle("d#sigma/d#OmegadE' (nb/GeV/sr)");
 gm->SetTitle(Form("SHMS vs HMS Deuterium %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(cxmin*2,cxmax*2);
 }
if(target=="r"){
 gm->GetYaxis()->SetTitle("#sigma_{D}/#sigma_{H} (per nucleon)");
 gm->SetTitle(Form("SHMS vs HMS D/H %sdeg",angle.c_str()));
   gm->GetYaxis()->SetRangeUser(0.5,1.5);
 }
// TCanvas *c1=new TCanvas();
 gm->GetYaxis()->SetTitleSize(.055);

 gm->GetXaxis()->CenterTitle();
 gm->GetYaxis()->CenterTitle();
 gm->GetXaxis()->SetNdivisions(-5);

  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0.02,1,0.38);
  //  gStyle->SetGridStyle(1);
  // pad1->SetGrid();
  // pad2->SetGrid();
  pad1->SetBottomMargin(0.1);
  pad1->SetLeftMargin(0.1);
  pad2->SetLeftMargin(0.1);
  pad1->SetBorderMode(0);
  pad2->SetTopMargin(0.1);
  pad2->SetBottomMargin(0.17);
  pad2->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  gm->Draw();
  ////////   Data   /////////////////////
  ////////////////////////////////////////

 TGraphErrors *grcx1=extractCS("shms",target,angle,pset[0],1);
 TGraphErrors *grcx2=extractCS("shms",target,angle,pset[1],1);
 TGraphErrors *grcx3=extractCS("shms",target,angle,pset[2],1);
 TGraphErrors *grcx4=extractCS("shms",target,angle,pset[3],1);

 TGraphErrors *grcx5=extractCS("hms",target,angle,"3p3",1);
 TGraphErrors *grcx6=extractCS("hms",target,angle,"4p0",1);
 TGraphErrors *grcx7=extractCS("hms",target,angle,"4p5",1);
 TGraphErrors *grcx8=extractCS("hms",target,angle,"5p1",1);
 TGraphErrors *grcx9=extractCS("hms",target,angle,"5p7",1);
 grcx1->SetMarkerStyle(27);
 grcx2->SetMarkerStyle(27);
 grcx3->SetMarkerStyle(27);
 grcx4->SetMarkerStyle(27);
 grcx5->SetMarkerStyle(20);
 grcx6->SetMarkerStyle(20);
 grcx7->SetMarkerStyle(20);
 grcx8->SetMarkerStyle(20);
 grcx9->SetMarkerStyle(20);
 grcx1->SetMarkerColor(kRed);
 grcx2->SetMarkerColor(kBlack);
 grcx3->SetMarkerColor(kGreen+3);
 grcx4->SetMarkerColor(kViolet);

 grcx7->SetMarkerColor(kRed);
 grcx8->SetMarkerColor(kBlack);
 grcx9->SetMarkerColor(kGreen+3);
 grcx6->SetMarkerColor(kViolet);
 grcx5->SetMarkerColor(kBlue);


grcx1->Draw("sp");
grcx2->Draw("sp");
grcx3->Draw("sp");
grcx4->Draw("sp");
grcx5->Draw("sp");
grcx6->Draw("sp");
grcx7->Draw("sp");
grcx8->Draw("sp");
grcx9->Draw("sp");
 if(target=="r")pad1->SaveAs("doh.pdf");
 pad2->cd();
 TGraphErrors *gr1=extractCS("shms",target,angle,pset[0],0);
 TGraphErrors *gr2=extractCS("shms",target,angle,pset[1],0);
 TGraphErrors *gr3=extractCS("shms",target,angle,pset[2],0);
 TGraphErrors *gr4=extractCS("shms",target,angle,pset[3],0);
 TGraphErrors *gr5=extractCS("hms",target,angle,"3p3",0);
 TGraphErrors *gr6=extractCS("hms",target,angle,"4p0",0);
 TGraphErrors *gr7=extractCS("hms",target,angle,"4p5",0);
 TGraphErrors *gr8=extractCS("hms",target,angle,"5p1",0);
 TGraphErrors *gr9=extractCS("hms",target,angle,"5p7",0);

 //gStyle->SetTitleFontSize(.1);
 gr1->GetXaxis()->SetTitle("Bjorken X");
 gr1->GetYaxis()->SetTitleSize(.075);
 gr1->GetYaxis()->SetTitleOffset(.5);
 gr1->GetXaxis()->CenterTitle();
 gr1->GetYaxis()->CenterTitle();

 gr1->GetYaxis()->SetTitle("Data/Model");
gr1->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
//gr1->GetXaxis()->SetRangeUser(xbmin,xbmax);
 gr1->GetXaxis()->SetLimits(xbmin,xbmax);
  gr1->GetXaxis()->SetLabelSize(.06);
  gr1->GetYaxis()->SetLabelSize(.06);
 gr1->GetXaxis()->SetNdivisions(-5);
 gr1->SetMarkerStyle(27);
 gr2->SetMarkerStyle(27);
 gr3->SetMarkerStyle(27);
 gr4->SetMarkerStyle(27);
 gr5->SetMarkerStyle(20);
 gr6->SetMarkerStyle(20);
 gr7->SetMarkerStyle(20);
 gr8->SetMarkerStyle(20);
 gr9->SetMarkerStyle(20);
 gr1->SetMarkerColor(kRed);
 gr2->SetMarkerColor(kBlack);
 gr3->SetMarkerColor(kGreen+3);
 gr4->SetMarkerColor(kViolet);
 gr7->SetMarkerColor(kRed);
 gr8->SetMarkerColor(kBlack);
 gr9->SetMarkerColor(kGreen+3);
 gr6->SetMarkerColor(kViolet);
 gr5->SetMarkerColor(kBlue);

 gr1->Draw("ap");
 gr2->Draw("sp");
 gr3->Draw("sp");
 gr4->Draw("sp");
 gr5->Draw("sp");
 gr6->Draw("sp"); 
 gr7->Draw("sp");
 gr8->Draw("sp");
 gr9->Draw("sp");
 pad1->cd();
 TLegend *leg=new TLegend(.53,.55,.75,.85);
 leg->AddEntry(gm,"SHMS 21.035#circ","");
 leg->AddEntry(gm,"f1f220","l");
 leg->AddEntry(grcx1,Form("E'=%2.2f GeV/c",psetf[0]),"p");
 leg->AddEntry(grcx2,Form("E'=%2.2f GeV/c",psetf[1]),"p");
 leg->AddEntry(grcx3,Form("E'=%2.2f GeV/c",psetf[2]),"p");
 leg->AddEntry(grcx4,Form("E'=%2.2f GeV/c",psetf[3]),"p");

 TLegend *leg2=new TLegend(.2,.55,.42,.85);
 leg2->AddEntry(gm,"HMS 20.995#circ","");
 leg2->AddEntry(grcx5,"E'=3.3 GeV/c","p");
 leg2->AddEntry(grcx6,"E'=4.0 GeV/c","p");
 leg2->AddEntry(grcx7,"E'=4.5 GeV/c","p");
 leg2->AddEntry(grcx8,"E'=5.1 GeV/c","p");
 leg2->AddEntry(grcx9,"E'=5.7 GeV/c","p");

 if(target=="r") 
   {
     leg->Draw();
     leg2->Draw();
   }
 /// c1->SaveAs(Form("cs_%s%sdeg.pdf",target.c_str(),angle.c_str()));
  return;
}
