void xsecTable(TGraphErrors *gcxa, TGraphErrors *gcx, TGraphErrors *grerr, TGraphErrors *gdm, Double_t thetac, string kin, string target){
  //gcxa 3   statOnly
  //gcx  1   xsec
  //grerr2   band
  //gdm  0   data/MC




  ofstream outFile;
  if(target=="h")outFile.open("xsec_H_Table.txt",ios::app | ios::out );
  if(target=="d")outFile.open("xsec_D_Table.txt",ios::app | ios::out );
  if(target=="r")outFile.open("xsec_R_Table.txt",ios::app | ios::out );

  cout << gcx->GetN()<<"\t";
  cout << gcxa->GetN()<<"\t";
  cout << grerr->GetN()<<"\t";
  cout << gdm->GetN()<<"\t";
  cout<<endl;
  for(int i=0; i < gcx->GetN(); i++){
    //    cout << "There are " << gcx->GetN()<<"points"<<endl;
    double xb, xsec, perr, gerr, dum, delta, rat, raterr, staterr;

  int offset=-10;
    if(gcx->GetN()<11){
      offset=-8;
      if(thetac-20.995<.01)offset=-5;
      delta=3*i+offset+0.5;

    }
    else{
      offset=-10;
      if(thetac-20.995<.01)offset=-6;
      delta=i+offset+0.5;
    }

    gcx->GetPoint(i,xb,xsec);
    gdm->GetPoint(i,dum,rat);

    raterr=gdm->GetErrorY(i)/rat;
    perr=gcx->GetErrorY(i)/xsec;
    gerr=grerr->GetErrorY(i)/xsec;
    staterr=gcxa->GetErrorY(i)/xsec;

    Double_t alpha = 1./137.036;
    Double_t ebeam=10.602;
    Double_t mp = .9382723;
    Double_t mp2= mp*mp;
    Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
    Double_t ep= (mp*xb*ebeam) / (2*ebeam*sin2+mp*xb );
    Double_t nu= ebeam-ep;
    Double_t q2 = 4.*ep*ebeam*sin2;
    cout <<"q2"<<"\t"<<"ep"<<"\t"<<"ebeam"<<"\t"<<sin2<<"\t"<<"thetac"<<endl;
    cout <<q2<<"\t"<<ep<<"\t"<<ebeam<<"\t"<<sin2<<"\t"<<thetac<<endl;
    Double_t w2= mp*mp + 2.*mp*nu-q2;
    Double_t nu2=nu*nu;
    Double_t tan2=tan(thetac/2/180*TMath::Pi())*tan(thetac/2/180*TMath::Pi());
    Double_t kappa=(w2-mp2)/2./mp;
    Double_t eps=1./(1.+2.*(1.+nu2/q2)*tan2);
    Double_t fluxnum=alpha*kappa*ep;
    Double_t fluxden=2.*TMath::Pi()*TMath::Pi()*q2*ebeam*(1.-eps);
    Double_t flux=fluxnum/fluxden;

    //    gerr=perr/xsec*100;
    //    cout <<spec<<angle<<target<<pset[0]<<"\t";
    //    cout << kin << "\t"<< ebeam <<"\t"<< ep <<"\t"<< thetac <<"\t"<<q2<<"\t";
    //    cout << w2 <<"\t"<< xb<< "\t"<<xsec <<"\t"<< perr <<"\t"<<gerr<< "\t"<< staterr<< endl;


    /*
    // This format matches resdata but reading with fortran proved challenging
    //    outFile <<kin;
    outFile << fixed << setprecision(3);
    outFile << ebeam <<"\t"<< ep <<"\t"<< thetac <<"\t"<<q2<<"\t";
    outFile <<w2 <<"\t"<< nu << "\t"<< eps<< "\t"<< scientific << flux<< "\t"<< fixed << xb<<"\t";
    outFile <<setprecision(5)<<xsec <<"\t"<< perr;
    //    outFile <<"\t"<<gerr;
    */
    if(abs(gerr)<1.){
      outFile << fixed << setprecision(5);
      //    outFile << setw(10) << kin;
      outFile << setw(10) << ebeam;
      outFile << setw(10) << ep;
      outFile << setw(10) << thetac;
      outFile << setw(10) << q2;
      outFile << setw(10) << w2;
      outFile << setw(10) << nu;
      outFile << setw(10) << eps;
      outFile << setw(12) << scientific<<flux<<fixed;
      outFile << setw(10) << xb;
      outFile << setw(10) << xsec;
      outFile << setw(10) << staterr;
      outFile << setw(10) << perr;
      outFile << setw(10) << gerr;
      outFile << setw(10) << delta;
      outFile << setw(10) << rat;
      outFile << setw(10) << raterr;

      outFile<<endl;
    }
  }
  outFile.close();
  cout << "done in xsecTable for kin "<<kin<<"  target: "<< target<<endl;
  return 0;

}

