#include "getCSBerr.cpp"
#include "getKinErr.cpp"

//#include "getKineUnc.cpp"
//#include "getRadError.cpp"

double getGlobalError(TGraph2D* grd,TGraph2D*  grh, Float_t ep, Double_t w2, Double_t thetac, Double_t hsec,Float_t deltah,string spec, string angle, string target, string mom, double xb, TGraph * g, TH1F* hkinErr, int bin, double lte, double qerr, double boil_err, double modErr){

  double ang=21; 
  double spec_flag=0.;
  if(spec=="shms")spec_flag=1.;

  string kin=target+angle+"deg"+mom;
  string skin=target+angle+"deg";

  ofstream outFile;
  outFile.open("globErr.txt",ios::app | ios::out );

  //Pion Contamination Error


  double pion_err=0.001;
  if(angle=="39")pion_err=.002;
  double density_err=.0075;
  double cer_err=0.003;

  if(target=="r"){
    pion_err=0.0014;
    if(angle=="39")pion_err=.0028;    
    density_err=0.0106;
    cer_err=0.001;
  }
  
  if (angle=="39" || angle == "21" || angle == "33"){
    if(target=="r")density_err=0.0113;
    if(target=="d")density_err=0.0085;
    if(target=="h")density_err=0.0075;
    if(mom=="1p6"){
    if(target=="r")density_err=0.0110;
    if(target=="d")density_err=0.0085;
    }
  }

  //  double kin_err=hkinErr->GetBinContent(bin);//can handle h Vs d vs r
  double kin_err=getKinErr(kin,xb);
  //  cout << "Bin, w2, delta, kinErr, boil: "<<bin<<"\t"<<w2<<"\t"<<deltah<<"\t"<<kin_err<<"\t"<<boil_err<<endl;
  double csb_h_err=getCSBerr(thetac,hsec,deltah,1.01,0,grh);
  double csb_d_err=getCSBerr(thetac,hsec,deltah,2.01,0,grd);
  if(spec=="hms")csb_h_err=csb_h_err/.03;
  if(spec=="hms")csb_d_err=csb_d_err/.03;
  double csb_err=0;
  if(target=="r")csb_err=sqrt(pow(csb_h_err,2)+pow(csb_d_err,2));
  if(target=="h")csb_err=csb_h_err;
  if(target=="d")csb_err=csb_d_err;  



  double acc_err=0.003;
  if(spec_flag==1)
    {
      if(target=="r")acc_err=0.0018/pow(w2-1.1,1.13);
      if(target=="h")acc_err=0.0003902+deltah*-5.019E-5+pow(deltah,2)*1.671E-6+pow(deltah,3)*5.811E-6+pow(deltah,4)*-2.572E-7;
      if(target=="d")acc_err=0.0003619+deltah*-6.701E-5+pow(deltah,2)*1.919E-7+pow(deltah,3)*6.077E-6+pow(deltah,4)*-2.62E-7;
      acc_err=abs(acc_err);
      //0.0003902+x*-5.019E-5+pow(x,2)*1.671E-6+pow(x,3)*5.811E-6+pow(x,4)*-2.572E-7;
      //0.0003619+x*-6.701E-5+pow(x,2)*1.919E-7+pow(x,3)*6.077E-6+pow(x,4)*-2.62E-7;
    }


  double rad_err= g->Eval(xb)/100.;

  double result = sqrt(pow(pion_err,2) + pow(density_err,2) + pow(cer_err,2)  + pow(kin_err,2) + pow(csb_err,2) + pow(acc_err,2) + pow(rad_err,2)+pow(lte,2)+pow(modErr,2));

  //  cout <<  pion_err  <<"\t"<<density_err<<"\t"<<cer_err<<"\t"<<boil_err<<"\t"<<kin_err<<"\t"<<csb_err<<"\t"<<acc_err<<"\t" <<rad_err<<"\t"<< lte <<"\t"<<qerr<<"\t"<<boil_err<<"\t"<<result << endl;

      outFile << fixed << setprecision(5);
      //    outFile << setw(10) << kin;
      outFile << setw(10) << spec_flag;
      outFile << setw(10) << kin;
      outFile << setw(10) << xb;
      outFile << setw(10) << pion_err;
      outFile << setw(10) << density_err;
      outFile << setw(10) << cer_err;
      outFile << setw(10) << modErr;
      outFile << setw(10) << kin_err;
      outFile << setw(10) << csb_err;
      outFile << setw(10) << acc_err;
      outFile << setw(10) << rad_err;
      outFile << setw(10) << lte;
      outFile << setw(10) << qerr;
      outFile << setw(10) << boil_err;
      outFile << setw(10) << result;
      outFile<<endl;

  outFile.close();
  return result;
}  
