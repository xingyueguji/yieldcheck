TF1* oldgetPionContamination(double run=2525){
  // targets
  // al 26.98
  // h 1.01
  // d 2.01
  // c 12.01

  //angles
  // 21.035  38.975  32.975  28.99  24.98
  double target=readReport(run,"target");
  double angle=readReport(run,"Spec Angle");
  TF1 *pionC;

  if(target==1.01 && angle==21.035)
  pionC=new TF1("pionC","4.58*exp(2.25*x)/pow(x,13.2)",1.,8);
  if(target==2.01 && angle==21.035)
  pionC=new TF1("pionC","2.96*exp(.541*x)/pow(x,7.52)",1.,8);
  if(target==12.01 && angle==21.035)
  pionC=new TF1("pionC","0.401*exp(.513*x)/pow(x,6.00)",1.,8);
  if(target==26.98 && angle==21.035)
  pionC=new TF1("pionC",".236*exp(-1.23*x)/pow(x,.762)",1.,8);

  if(target==1.01 && angle==38.975)
  pionC=new TF1("pionC",".244*exp(-.162*x)/pow(x,5.27)",1.,8);
  if(target==2.01 && angle==38.975)
  pionC=new TF1("pionC","0.37*exp(0.0364*x)/pow(x,5.48)",1.,8);
  if(target==12.01 && angle==38.975)
  pionC=new TF1("pionC","3.30*exp(-2.8*x)/pow(x,1.12)",1.,8);
  if(target==26.98 && angle==38.975)
  pionC=new TF1("pionC","0.0144*exp(2.63*x)/pow(x,7.76)",1.,8);

  if(target==1.01 && angle==32.975)
  pionC=new TF1("pionC","1.0*exp(-1.94*x)/pow(x,1.83)",1.,8);
  if(target==2.01 && angle==32.975)
  pionC=new TF1("pionC","0.959*exp(-1.28*x)/pow(x,2.9)",1.,8);
  if(target==12.01 && angle==32.975)
  pionC=new TF1("pionC","22.4*exp(-6.61*x)/pow(x,-7.88)",1.,8);
  if(target==26.98 && angle==32.975)
  pionC=new TF1("pionC",".0809*exp(1.03*x)/pow(x,6.2)",1.,8);

  if(target==1.01 && angle==28.99)
  pionC=new TF1("pionC","0.406*exp(-0.396*x)/pow(x,4.49)",1.,8);
  if(target==2.01 && angle==28.99)
  pionC=new TF1("pionC",".961*exp(-1.24*x)/pow(x,2.42)",1.,8);
  if(target==12.01 && angle==28.99)
  pionC=new TF1("pionC",".672*exp(-.905*x)/pow(x,3.23)",1.,8);
  if(target==26.98 && angle==28.99)
  pionC=new TF1("pionC","0.106*exp(.748*x)/pow(x,5.69)",1.,8);

  if(target==1.01 && angle==24.98)
  pionC=new TF1("pionC","0.613*exp(-.55*x)/pow(x,3.96)",1.,8);
  if(target==2.01 && angle==24.98)
  pionC=new TF1("pionC","1.49*exp(.383*x)/pow(x,6.87)",1.,8);
  if(target==12.01 && angle==24.98)
  pionC=new TF1("pionC",".307*exp(-1.02*x)/pow(x,1.69)",1.,8);
  if(target==26.98 && angle==24.98)
  pionC=new TF1("pionC","0.394*exp(1.68*x)/pow(x,9.4)",1.,8);


  return pionC;

}
