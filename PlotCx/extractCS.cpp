#include "src/getRadCorrW2.cpp"
#include "src/getChargeError.cpp"
#include "src/getRadError.cpp"
#include "src/getGlobalError.cpp"
#include "src/getAngle.cpp"
#include "src/getMom.cpp"

// returns cross section w stat error only in a TGraph for a given spectrometer/kinematic if cs==3
// returns error band in a TGraph for a given spectrometer/kinematic if cs==2
// returns cross section in a TGraph for a given spectrometer/kinematic if cs==1
// returns ratio xsec/model in a TGraph for a given spectrometer/kinematic if cs==0

TGraphErrors* extractCS(string spec="shms", string target="d", string angle="39",string mom="1p3", int cs=2, string pass="pass103", string xaxis="xb"){
  //  int cnt=0;
  // cout << "Hello"<<cnt<<endl;cnt++;
  //  ofstream ofile;
  //  ofile.open("q2range.txt",ios::app | ios::out );

  ////////////////////////////
  ////   Just for printing charge error
  bool done=0;
  ofstream ofile2;
  ofile2.open("qError.txt",ios::app | ios::out );
  double ang=21;
  double spec_flag=0.;
  if(spec=="shms")spec_flag=1.;
  if(angle=="25")ang=25;
  if(angle=="29")ang=29;
  if(angle=="33")ang=33;
  if(angle=="39")ang=39;
  //////////////////////////////

  TGraph *g_rad;
  if(angle=="21")g_rad=getRadError(21, target);
  if(angle=="25")g_rad=getRadError(25, target);
  if(angle=="29")g_rad=getRadError(29, target);
  if(angle=="33")g_rad=getRadError(33, target);
  if(angle=="39")g_rad=getRadError(39, target);

  Float_t deltad, ratiod, errd, ep, modeld;
  Float_t deltah, ratioh, errh, modelh,csbh, csbd;
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

  TGraph2D *grh=getRadCorrW2("h",1,spec);  
  TGraph2D *grd=getRadCorrW2("d",1,spec);  


  cout << "The central momentum is "<<hsec<<endl;
  if(spec=="hms"&&hsec<5.5){
    double offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
    hsec=hsec*offset;
  }
  
  cout << "The corrected central momentum is "<<hsec<<endl;

  // GET HISTOGRAMS FROM RATIOS.CPP
  //*******************************************************************************************
  // Deuterium
  TFile *frd=new TFile(Form("ratiosOut/%s/%s_ratiosd%sdeg%s.root",pass.c_str(),spec.c_str(),angle.c_str(),mom.c_str()));
  TH1F *hrdd;
  hrdd=(TH1F*)frd->Get("hrd");                  // with pt2pt error
  if(cs==3)hrdd=(TH1F*)frd->Get("hrd_stat");    // stat error only  
  TH1F *hsysd=(TH1F*)frd->Get("hsys");          
  TH1F *hsysdR=(TH1F*)frd->Get("hsysR");  
  hrdd->SetDirectory(0);
  hsysd->SetDirectory(0);
  hsysdR->SetDirectory(0);
  // correctrun run 1640 for temp. fluctuation
  if( (target=="r" || target=="d") && spec=="hms" && angle=="21" && mom == "3p3"){
    hrdd->Scale(1.0229);
    cout << endl << endl <<"Correcting for run 1640" << endl << endl;
  }
  frd->Close();
  
  // Hydrogen
  TFile *frh=new TFile(Form("ratiosOut/%s/%s_ratiosh%sdeg%s.root",pass.c_str(),spec.c_str(),angle.c_str(),mom.c_str()));
  TH1F *hrdh;
  hrdh=(TH1F*)frh->Get("hrd");           // with pt2pt error
  if(cs==3)hrdh=(TH1F*)frh->Get("hrd");  // stat error only
  TH1F *hsysh=(TH1F*)frh->Get("hsys");  
  TH1F *hsyshR=(TH1F*)frh->Get("hsysR");  
  hrdh->SetDirectory(0);
  hsysh->SetDirectory(0);
  hsyshR->SetDirectory(0);
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
      ratiod=hrdd->GetBinContent(i);
      errd=hrdd->GetBinError(i); 
      deltah=hrdh->GetBinCenter(i);
      ratioh=hrdh->GetBinContent(i);
      errh=hrdh->GetBinError(i); 
      
      if(cs==2){ //Error band
	errh=hsysh->GetBinContent(i)*ratioh;
	errd=hsysd->GetBinContent(i)*ratiod;
	if(target=="r"){
	  errh=hsyshR->GetBinContent(i)*ratioh;
	  errd=hsysdR->GetBinContent(i)*ratiod;
	}
      }
      if(cs==2)cout << errh<<"\t"<<errd<<endl;

      if(cs==1){   
	double qh_err=getChargeError(angle.c_str(), "h", mom.c_str(), spec.c_str());
	double qd_err=getChargeError(angle.c_str(), "d", mom.c_str(), spec.c_str());
	// add charge error to pt2pt
	if(!done){
	  ofile2 << spec_flag << "\t"<< ang << "\t" << qh_err << "\t"<< qd_err <<endl; 
	  done=1;
	}
	errh=sqrt(errh*errh+qh_err*qh_err);
	errd=sqrt(errd*errd+qd_err*qd_err);
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
      modeld=grd->Interpolate(w2,thetac);  //<<"\t"<<
      modelh=grh->Interpolate(w2,thetac);  //<<"\t"<<
      if(ratioh!=0 && ratiod!=0 && modelh!=0 && modeld!=0)
	{
	  float cxh=(ratioh*modelh);
	  float cxd=(ratiod*modeld);
	  double sys_y=0.58;
	  if(angle=="21"){ 
	    sys_y=.53;
	    //	   	   if(spec=="shms")sys_y=.525;
	    //	   if(spec=="hms")sys_y=.56;
	  }
	  if(cs==2 && cxd/cxh/2<1.15)//error band
	    {
	      //	     ofile << kin << "\t" << ep << "\t" << q2 << endl;
	      if(target=="h")cx.push_back(0.);
	      if(target=="d")cx.push_back(0.);
	      if(target=="r")cx.push_back(sys_y);
	     	      
	      if(target=="h")cxe.push_back(errh*modelh); //need to fix
	      if(target=="d")cxe.push_back(errd*modeld); //need to fix
	      //if(target=="r")cxe.push_back(sqrt(pow(errd/ratiod,2)+pow(errh/ratioh,2))*cxd/cxh/2.*modeld/modelh/2);
	      if(target=="r"){// correct for D/H
		double val=getGlobalError(grd, grh, ep, w2, thetac, hsec, deltah, spec, angle, target, mom, xb, g_rad);  
		//		cxe.push_back(sqrt(pow(errd/ratiod,2)+pow(errh/ratioh,2))*cxd/cxh/2.);
		cxe.push_back(val*cxd/cxh/2);
		//		cxe.push_back(val);
	      }

	      if(xaxis=="xb")eprime.push_back(xb);
	      if(xaxis=="w2")eprime.push_back(w2);
	      if(xaxis=="ep")eprime.push_back(ep);
	    }	 
	  if(cs==1 || cs==3)//cross section
	    {
	      if(target=="h")cx.push_back(cxh);
	      if(target=="d")cx.push_back(cxd);
	      if(target=="r")cx.push_back(cxd/cxh/2);
	      
	      if(target=="h")cxe.push_back(errh*modelh);
	      if(target=="d")cxe.push_back(errd*modeld);
	      //	     if(target=="r")cxe.push_back(sqrt(pow(errd*modeld,2)+pow(errh*modelh,2))/2.);
	      if(target=="r")cxe.push_back(sqrt(pow(errd*modeld/cxd,2)+pow(errh*modelh/cxh,2))*cxd/cxh/2.);
	      //	     if(target=="r")cxe.push_back(sqrt(pow(errd/ratiod,2)+pow(errh/ratioh,2))*cxd/cxh/2.*modeld/modelh/2);
	      if(deltah==-0.5){for(int k=0;k<20;k++)cout << deltah <<"\t"<< errh <<"\t"<< modelh <<"\t"<<ep<<endl;}
	      if(xaxis=="xb")eprime.push_back(xb);
	      if(xaxis=="w2")eprime.push_back(w2);
	      if(xaxis=="ep")eprime.push_back(ep);
	    }
	  if(cs==0)//data/model
	    {
	      if(target=="h")cx.push_back(ratioh);
	      if(target=="d")cx.push_back(ratiod);
	      if(target=="r")cx.push_back(ratiod/ratioh);
	      if(target=="h")cxe.push_back(errh);
	      if(target=="d")cxe.push_back(errd);
	      if(target=="r")cxe.push_back(sqrt(pow(errd/ratiod,2)+pow(errh/ratioh,2))*ratiod/ratioh);
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
  //  ofile.close();
  ofile2.close();
  TGraphErrors *gcx=new TGraphErrors(pts,&eprime[0],&cx[0],0,&cxe[0]);
  return gcx;
}
