TF1* getPionContamination(double run=2525){
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
  pionC=new TF1("pionC","4.49937*exp(1.75345*x)/pow(x,11.7137)",1.,8);
  if(target==2.01 && angle==21.035)
  pionC=new TF1("pionC","1.59403*exp(-1.38128*x)/pow(x,1.59377)",1.,8);
  if(target==12.01 && angle==21.035)
  pionC=new TF1("pionC","0.417755*exp(0.563993*x)/pow(x,6.14275)",1.,8);
  if(target==26.98 && angle==21.035)
   pionC=new TF1("pionC","0.291226*exp(-0.330604*x)/pow(x,3.40186)",1.,8);

  if(target==1.01 && angle==-20.995)
  pionC=new TF1("pionC","4.49937*exp(1.75345*x)/pow(x,11.7137)",1.,8);
  if(target==2.01 && angle==-20.995)
  pionC=new TF1("pionC","1.59403*exp(-1.38128*x)/pow(x,1.59377)",1.,8);
  if(target==12.01 && angle==-20.995)
  pionC=new TF1("pionC","0.417755*exp(0.563993*x)/pow(x,6.14275)",1.,8);
  if(target==26.98 && angle==-20.995)
   pionC=new TF1("pionC","0.291226*exp(-0.330604*x)/pow(x,3.40186)",1.,8);


  if(target==1.01 && angle==38.975)
  pionC=new TF1("pionC",".166675*exp(0.299433*x)/pow(x,5.98419)",1.,8);
  if(target==2.01 && angle==38.975)
  pionC=new TF1("pionC","0.400041*exp(0.00551476*x)/pow(x,5.43935)",1.,8);
  if(target==12.01 && angle==38.975)
  pionC=new TF1("pionC","3.30*exp(-2.8*x)/pow(x,1.12)",1.,8);
  if(target==26.98 && angle==38.975)
  pionC=new TF1("pionC","0.00749856*exp(3.35537*x)/pow(x,8.82817)",1.,8);

  if(target==1.01 && angle==32.975)
  pionC=new TF1("pionC","8.55560*exp(-5.18789*x)/pow(x,-4.72197)",1.,8);
  if(target==2.01 && angle==32.975)
  pionC=new TF1("pionC","2.64807*exp(-2.73395*x)/pow(x,0.0435966)",1.,8);
  if(target==12.01 && angle==32.975)
  pionC=new TF1("pionC","22.4*exp(-6.61*x)/pow(x,-7.88)",1.,8);
  if(target==26.98 && angle==32.975)
  pionC=new TF1("pionC","0.0807092*exp(1.04335*x)/pow(x,6.21548)",1.,8);

  if(target==1.01 && angle==28.99)
  pionC=new TF1("pionC","0.393917*exp(-0.471598*x)/pow(x,4.18430)",1.,8);
  if(target==2.01 && angle==28.99)
  pionC=new TF1("pionC","1.25565*exp(-1.93012*x)/pow(x,0.761512)",1.,8);
  if(target==12.01 && angle==28.99)
  pionC=new TF1("pionC","2.68261*exp(-3.80868*x)/pow(x,-3.27890)",1.,8);
  if(target==26.98 && angle==28.99)
  pionC=new TF1("pionC","0.130350*exp(.306715*x)/pow(x,4.64607)",1.,8);

  if(target==1.01 && angle==24.98)
  pionC=new TF1("pionC","0.574647*exp(-0.373983*x)/pow(x,4.36376)",1.,8);
  if(target==2.01 && angle==24.98)
  pionC=new TF1("pionC","1.50256*exp(-0.279117*x)/pow(x,5.03933)",1.,8);
  if(target==12.01 && angle==24.98)
  pionC=new TF1("pionC","0.284990*exp(-1.91949*x)/pow(x,-0.905901)",1.,8);
  if(target==26.98 && angle==24.98)
  pionC=new TF1("pionC","0.449401*exp(0.987751*x)/pow(x,7.56522)",1.,8);


  return pionC;

}
