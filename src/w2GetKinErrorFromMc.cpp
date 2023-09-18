
TH1F* unc(string tgt="h",string angle="21", string mom="5p1",string spec="shms", string pass="pass38"){
  //  gStyle->SetOptStat(0);

  string hkin="h"+angle+"deg"+mom; 
  string dkin="d"+angle+"deg"+mom; 

  //  Nominal   h36h h36d 
  TFile *f36h=new TFile(Form("../mcWtOut/pass36/%s_mcWt%s.root",spec.c_str(),hkin.c_str()));
  TH1F *h36h=(TH1F*)f36h->Get("w2Wt");
  h36h->SetName("h36h");
  h36h->SetDirectory(0);
  f36h->Close();
  TFile *f36d=new TFile(Form("../mcWtOut/pass36/%s_mcWt%s.root",spec.c_str(),dkin.c_str()));
  TH1F *h36d=(TH1F*)f36d->Get("w2Wt");
  h36d->SetName("h36d");
  h36d->SetDirectory(0);
  f36d->Close();

  //  Modified   hModh hModd 
  TFile *fModh=new TFile(Form("../mcWtOut/%s/%s_mcWt%s.root",pass.c_str(),spec.c_str(),hkin.c_str()));
  TH1F *hModh=(TH1F*)fModh->Get("w2Wt");
  hModh->SetName("hModh");
  hModh->SetDirectory(0);
  fModh->Close();
  TFile *fModd=new TFile(Form("../mcWtOut/%s/%s_mcWt%s.root",pass.c_str(),spec.c_str(),dkin.c_str()));
  TH1F *hModd=(TH1F*)fModd->Get("w2Wt");
  hModd->SetName("hModd");
  hModd->SetDirectory(0);
  fModd->Close();

  // hd = hModd/nominal   
  // hh = hModh/nominal   
  TH1F* hd=(TH1F*)hModd->Clone();
  hd->SetName("hd");
  hd->Divide(h36d);
  TH1F* hh=(TH1F*)hModh->Clone();
  hh->SetName("hh");
  hh->Divide(h36h);

  // hrMod = hModd/hModh
  TH1F* hrMod=(TH1F*)hModd->Clone();
  hrMod->SetName("hrMod");
  hrMod->Divide(hModh);

  // hr36= nominal d / nominal h
  TH1F* hr36=(TH1F*)h36d->Clone();
  hr36->SetName("hr36");
  hr36->Divide(h36h);

  // hrMod = (modified d/h)/(nominal d/h)
  hrMod->Divide(hr36);

  TH1F *result;
  if (tgt=="h")result=hh;
  if (tgt=="d")result=hd;
  if (tgt=="r")result=hrMod;


  /*
  hh->GetYaxis()->SetRangeUser(.9,1.1);
  hh->GetXaxis()->SetRangeUser(-10,22);
  hh->Draw();
  hd->Draw("same");
  hrMod->Draw("same");
  */

  return result;

}


TGraph* w2GetKinErrorFromMc(string tgt="h", string angle="21", string mom="5p7",string spec="hms"){


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

  double nbins=h38->GetNbinsX();
  TH1F* h_tot=(TH1F*)h38->Clone();
  h_tot->SetName("h_tot");

  vector <double> xx,yy;

  for(int i=1;i<=nbins;i++)
    {
      float h38n=abs(1.0-h38->GetBinContent(i));
      float d38n=abs(1.0-d38->GetBinContent(i));
      float r38n=abs(1.0-r38->GetBinContent(i));

      float h39n=abs(1.0-h39->GetBinContent(i));
      float d39n=abs(1.0-d39->GetBinContent(i));
      float r39n=abs(1.0-r39->GetBinContent(i));

      float h40n=abs(1.0-h40->GetBinContent(i));
      float d40n=abs(1.0-d40->GetBinContent(i));
      float r40n=abs(1.0-r40->GetBinContent(i));

      float h41n=abs(1.0-h41->GetBinContent(i));
      float d41n=abs(1.0-d41->GetBinContent(i));
      float r41n=abs(1.0-r41->GetBinContent(i));

      float h42n=abs(1.0-h42->GetBinContent(i));
      float d42n=abs(1.0-d42->GetBinContent(i));
      float r42n=abs(1.0-r42->GetBinContent(i));

      float h43n=abs(1.0-h43->GetBinContent(i));
      float d43n=abs(1.0-d43->GetBinContent(i));
      float r43n=abs(1.0-r43->GetBinContent(i));

      float xval=(r43->GetBinCenter(i));

      float tot_h_err = sqrt(pow((h38n+h39n)/2,2)+pow((h40n+h41n)/2,2)+pow((h42n+h43n)/2,2));
      float tot_d_err = sqrt(pow((d38n+d39n)/2,2)+pow((d40n+d41n)/2,2)+pow((d42n+d43n)/2,2));
      float tot_r_err= sqrt(pow((r38n+r39n)/2,2)+pow((r40n+r41n)/2,2)+pow((r42n+r43n)/2,2));
      
      if(tot_h_err<1.5){
	if(tgt=="h"){
	  yy.push_back(tot_h_err);
	  xx.push_back(xval);
	}
      }

      if(tot_d_err<1.5){
	if(tgt=="d"){
	  yy.push_back(tot_d_err);
	  xx.push_back(xval);
	}
      }
      
      if(tot_r_err<1.5){
	if(tgt=="r"){
	  yy.push_back(tot_r_err);
	  xx.push_back(xval);
	}
      }

    }
  TGraph *g=new TGraph(xx.size(),&xx[0],&yy[0]);
  return g;
}

