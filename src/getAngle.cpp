Float_t getAngle(string angle="21",string spec="shms"){
  Float_t thetac=0;
  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21"&&spec=="shms")thetac=21.035;
  if(angle=="21"&&spec=="hms")thetac=20.995;
  if(angle=="59")thetac=58.98;

  if(angle=="21m"&&spec=="shms")thetac=20.535;
  if(angle=="21p"&&spec=="shms")thetac=21.535;
  ////****  Beam is not along z ******
  cout << "Correcting central angle for beam angle"<<endl;
  cout << "Before: "<<thetac<<endl;
  Float_t beamTheta=0.0;
  //beamTheta=-.00045; //shooting beam right .45mr
  if(spec=="hms")beamTheta*=-1;
    thetac+=beamTheta*180./TMath::Pi();
  cout << "After: "<<thetac<<endl;
  //////////////////////////////////////

  return thetac;
}
