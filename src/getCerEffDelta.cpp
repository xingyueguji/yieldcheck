TF1* getCerEffDelta(double target){

  TF1 *fcer;

  if(abs(target-1.)<.3){
    cout << "Got cer. eff function for LH2"<<endl;
    fcer=new TF1("fcer","-0.01079*exp(-pow((x-1.679)/(x>1.679?3.806:0.8675),2.)/2.)+(x>1.679?(0.9973+x*-0.000205):0.9994)",-20,30);
  }


  else if(abs(target-2.)<.3){
    cout << "Got cer. eff function for LD2"<<endl;
    fcer=new TF1("fcer","-0.01079*exp(-pow((x-1.679)/(x>1.679?3.806:0.8675),2.)/2.)+(x>1.679?(0.9973+x*-0.000205):0.9994)",-20,30);
  }


  else if(abs(target-27.)<.3){
    cout << "Got cer. eff function for AL27"<<endl;
    fcer=new TF1("fcer"," -0.006581*exp(-pow((x-1.498)/(x>1.679?6.616:0.8785),2.)/2.)+(x>1.498?(0.9984+x*-0.0002489):0.9984)",-20,30);
  }
  else{
    cout << "Got cer. eff function for solid target"<<endl;
    fcer=new TF1("fcer","-0.02447*exp(-pow((x-2.512)/(x>2.512?2.396:1.058),2.)/2.)+(x>2.512?(0.9958+x*-0.000122):0.9995)",-20,30);
  }

  return fcer;
}
