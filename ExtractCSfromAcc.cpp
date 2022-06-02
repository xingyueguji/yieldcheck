//#include "src/getRadCorrW2.cpp"
//#include "src/getAngle.cpp"
//#include "src/getMom.cpp"
#include "extractCS.cpp"

// returns cross section w stat error only in a TGraph for a given spectrometer/kinematic if cs==3
// returns error band in a TGraph for a given spectrometer/kinematic if cs==2
// returns cross section in a TGraph for a given spectrometer/kinematic if cs==1
// returns ratio xsec/model in a TGraph for a given spectrometer/kinematic if cs==0

TGraphErrors* ExtractCSfromAcc(string spec="shms", string target="h", string angle="21",string mom="3p3", int cs=3, string pass="acc1", string xaxis="xb"){
  cout << "*****************  extracting .... **************************"<<endl;

  double ang=21;
  double spec_flag=0.;
  if(spec=="shms")spec_flag=1.;
  if(angle=="25")ang=25;
  if(angle=="29")ang=29;
  if(angle=="33")ang=33;
  if(angle=="39")ang=39;
  //////////////////////////////

  Float_t deltad, Xsecd, errd, ep, modeld;
  Float_t deltah, Xsech, errh, modelh,csbh, csbd;
  vector <float> cx;
  vector <float> cxe;
  vector <float> eprime;
  
  string kin;
  if(target=="r")kin="h"+angle+"deg"+mom;
  else kin=target+angle+"deg"+mom;
  cout << "The Kinematic is " << kin <<endl;
  Double_t pc=getMom(kin,spec);
  kin=target+angle+"deg"+mom;

  Double_t pOffset=0.;
  Double_t ebeam=10.602;
  Double_t hsec=pc*(1+pOffset);
  //  Double_t thetac=getAngle(angle,spec);
  Double_t thetac=getAngle(angle,"shms");

  // I correct for the beam angle in data theta calulation,
  // bin centering, and rad correction
  // 
  Double_t beamTheta=0.0;
  cout << "Correcting central angle for beam angle"<<endl;
  cout << "Before: "<<thetac<<endl;
  beamTheta=0.00045;//-0.00025; //shooting beam right .45mr
  if(spec=="hms")beamTheta*=-1;
  thetac+=beamTheta*180./TMath::Pi();
  cout << "After: "<<thetac<<endl;


  string version="v996t2";
  cout << "Going to use version "<<version<<" for "<<pass<<endl;

  cout << "The central momentum is "<<hsec<<endl;
  if(spec=="hms"&&hsec<5.5){
    double offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
    hsec=hsec*offset;
  }
  
  cout << "The corrected central momentum is "<<hsec<<endl;

  TGraph2D *grh=getRadCorrW2("h",1,spec,version);  
  grh->SetName("grh");
  TGraph2D *grd=getRadCorrW2("d",1,spec,version);  
  grd->SetName("grd");


  // GET HISTOGRAMS FROM RATIOS.CPP
  //*******************************************************************************************
  // Deuterium
  TFile *frd=new TFile(Form("../dataYieldOut/%s/acc60bins_%s_d%sdeg%s.root",pass.c_str(),spec.c_str(),angle.c_str(),mom.c_str()));
  TH1F *hrdd;
  hrdd=(TH1F*)frd->Get("hborn_xs");                  // with pt2pt error
  hrdd->SetDirectory(0);
  // correctrun run 1640 for temp. fluctuation
  if( (target=="r" || target=="d") && spec=="hms" && angle=="21" && mom == "3p3"){
    hrdd->Scale(1.0229);
    cout << endl << endl <<"Correcting for run 1640" << endl << endl;
  }
  frd->Close();
  // Hydrogen
  TFile *frh=new TFile(Form("../dataYieldOut/%s/acc60bins_%s_h%sdeg%s.root",pass.c_str(),spec.c_str(),angle.c_str(),mom.c_str()));
  TH1F *hrdh;
  hrdh=(TH1F*)frh->Get("hborn_xs");                  // with pt2pt error
  hrdh->SetDirectory(0);
  frh->Close();

//*******************************************************************************************
  const Int_t nbins=hrdd->GetNbinsX();
  //go bin by bin and wt ratios
  for (Int_t i=1; i<=nbins; i++)
    {
      // deltax: Bin Center
      // ratiox: Data/MC
      // errx:   Errors includes pt2pt, MC, stat

      deltad=hrdd->GetBinCenter(i);
      Xsecd=hrdd->GetBinContent(i);
      errd=hrdd->GetBinError(i); 
      deltah=hrdh->GetBinCenter(i);
      Xsech=hrdh->GetBinContent(i);
      errh=hrdh->GetBinError(i); 
      if( (deltad>-10&&deltad<21&&spec=="shms") || spec=="hms") //This is how I handle rebinned data
	{
	  //Debs delta correction for SHMS  
	  if(spec=="shms")
	    {
	      double p0 = 1.00156;
	      double p1 = -0.002473; 
	      double p2 = -1.54588e-05;
	      double p3 = 6.63986e-06;
	      double shms_delta_corr=p0+p1*deltad+p2*pow(deltad,2)+p3*pow(deltad,3);
	      Xsecd=Xsecd/shms_delta_corr;
	      Xsech=Xsech/shms_delta_corr;
	    }
	  
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
	  modeld=grd->Interpolate(w2,thetac);  //born
	  modelh=grh->Interpolate(w2,thetac);  //
	  //  data/model
	  if(cs==0){
	    Xsech=Xsech/modelh;
	    Xsecd=Xsecd/modeld;
	    errh=errh/modelh;
	    errd=errd/modeld;
	    if(target=="r"){
	      Xsecd=Xsecd*2;
	      errd=errd*2;
	    }
	  }
	  if(Xsech!=0 && Xsecd!=0 && modelh!=0 && modeld!=0)
	    {
		  if(target=="h")cx.push_back(Xsech);
		  if(target=="d")cx.push_back(Xsecd);
		  if(target=="r")cx.push_back(Xsecd/Xsech/2.);

		  if(target=="h")cxe.push_back(errh);
		  if(target=="d")cxe.push_back(errd);
		  double ratErr=Xsecd/Xsech/2.*sqrt(errh*errh/Xsech/Xsech+errd*errd/Xsecd/Xsecd);
		  if(target=="r")cxe.push_back(ratErr);		  
	  
		  if(xaxis=="xb")eprime.push_back(xb);
		  if(xaxis=="w2")eprime.push_back(w2);
		  if(xaxis=="ep")eprime.push_back(ep);
	    }
	}
    }

  int pts=eprime.size();
  for(int i=0;i<pts;i++)
    {
      //      cout<<eprime.at(i)<<"\t";
      //      cout<<cx.at(i)<<"\t +/-";
      //      cout<<cxe.at(i)<<endl;
    }

  TGraphErrors *gcx=new TGraphErrors(pts,&eprime[0],&cx[0],0,&cxe[0]);
  return gcx;
}

