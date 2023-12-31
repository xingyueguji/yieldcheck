#include "src/getRadCorrW2.cpp"
#include "src/getAngle.cpp"
#include "src/getMom.cpp"

// returns cross section in a TGraph for a given spectrometer/kinematic if cs==1
// returns ratio xsec/model in a TGraph for a given spectrometer/kinematic if cs==0

TGraphErrors* extractCS(string spec="shms", string target="d", string angle="39",string mom="1p3", int cs=1, string pass="pass103", string xaxis="xb"){

  string kin;
  if(target=="r")kin="h"+angle+"deg"+mom;
  else kin=target+angle+"deg"+mom;
  cout << "The Kinematic is " << kin <<endl;
  Double_t pc=getMom(kin,spec);
  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  Double_t thetac=getAngle(angle,"shms");
  TGraph2D *grh;
  TGraph2D *grd;
  TGraph2D *grh2;
  TGraph2D *grd2;

  cout << "The central momentum is "<<hsec<<endl;
  if(spec=="hms"&&hsec<5.5){
    double offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
    hsec=hsec*offset;
  }
  
cout << "The corrected central momentum is "<<hsec<<endl;

//Weighted MC //change be back to d
  TFile *frd=new TFile(Form("ratiosOut/%s/%s_ratiosd%sdeg%s.root",pass.c_str(),spec.c_str(),angle.c_str(),mom.c_str()));
  TH1F *hrdd=(TH1F*)frd->Get("hrd");  
  hrdd->SetDirectory(0);
  if( (target=="r" || target=="d") && spec=="hms" && angle=="21" && mom == "3p3"){
    hrdd->Scale(1.0229);
    cout << endl << endl <<"Correcting for run 1640" << endl << endl;
  }
  frd->Close();

  TFile *frh=new TFile(Form("ratiosOut/%s/%s_ratiosh%sdeg%s.root",pass.c_str(),spec.c_str(),angle.c_str(),mom.c_str()));
  TH1F *hrdh=(TH1F*)frh->Get("hrd");  
  hrdh->SetDirectory(0);
  frh->Close();

  grh=getRadCorrW2("h",1,spec);  
  grd=getRadCorrW2("d",1,spec);  
  grh2=getRadCorrW2("h",2,spec);  
  grd2=getRadCorrW2("d",2,spec);  

  const Int_t nbins=hrdd->GetNbinsX();
  Float_t deltad, ratiod, errd, ep, modeld, rci_d, rci_h;
  Float_t deltah, ratioh, errh, modelh,csbh, csbd;
  vector <float> cx;
  vector <float> cxe;
  vector <float> eprime;

  //go bin by bin and wt ratios
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
     ///////////
     //     w2=deltah;
     ///////////
     modeld=grd->Interpolate(w2,thetac);  //<<"\t"<<
     modelh=grh->Interpolate(w2,thetac);  //<<"\t"<<
     rci_d=grd2->Interpolate(w2,thetac);  //<<"\t"<<
     rci_h=grh2->Interpolate(w2,thetac);  //<<"\t"<<

     if(ratioh!=0 && ratiod!=0)
       {
	 float cxh=(ratioh*modelh);
	 float cxd=(ratiod*modeld);
	 
	 if(cs==1)
	   {
	     if(target=="h")cx.push_back(cxh);
	     if(target=="d")cx.push_back(cxd);
	     if(target=="r")cx.push_back(cxd/cxh/2);
	     
	     if(target=="h")cxe.push_back(errh*modelh);
	     if(target=="d")cxe.push_back(errd*modeld);
	     //	     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))/2.);
	     //	     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))*cxd/cxh/2.);
	     if(target=="r")cxe.push_back(sqrt(pow(errd/ratiod,2)+pow(errh/ratioh,2))*cxd/cxh/2.);
	     if(xaxis=="xb")eprime.push_back(xb);
	     if(xaxis=="w2")eprime.push_back(w2);
	     if(xaxis=="ep")eprime.push_back(ep);
	   }
	 if(cs==0)
	   {
	     if(target=="h")cx.push_back(cxh/modelh);
	     if(target=="d")cx.push_back(cxd/modeld);
	     if(target=="r")cx.push_back(cxd/modeld/cxh*modelh);
	     if(target=="h")cxe.push_back(errh);
	     if(target=="d")cxe.push_back(errd);
	     	     if(target=="r")cxe.push_back(sqrt(pow(errd,2)+pow(errh,2))/2.);
	     //	     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))*cxd/cxh/2.;)
	     if(xaxis=="xb")eprime.push_back(xb);
	     if(xaxis=="w2")eprime.push_back(w2);
	     if(xaxis=="ep")eprime.push_back(ep);

	   }
       }
   }
  int pts=eprime.size();
  for(int i=0;i<pts;i++)
    {
      cout<<eprime.at(i)<<"\t";
      cout<<cx.at(i)<<"\t +/-";
      cout<<cxe.at(i)<<endl;
    }

  TGraphErrors*gcx=new TGraphErrors(pts,&eprime[0],&cx[0],0,&cxe[0]);
  return gcx;
}

