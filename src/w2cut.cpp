bool w2cut(string spec="shms", string angle="21",string mom="5p1", double w2=10){

  string kin=angle+"deg"+mom;
  bool good=false;
  //  bool   res = false;
  //  double lo=25;
  //  double hi=0;
  //  double w2hi=w2+.08*3;
  //  double w2lo=w2-.08*7;
  double w2hi=w2;
  double w2lo=w2;
 if(spec=="shms"){
if(kin=="21deg2p7" && w2hi<=12.76 && w2lo>=10.2)good=true;
if(kin=="21deg3p3" && w2hi<=10.92 && w2lo>=7.8)good=true;
 if(kin=="21deg4p0" && w2hi<=8.84 && w2lo>=5.08)good=true;
 if(kin=="21deg5p1" && w2hi<=5.48 && w2>=1.2)good=true;
if(kin=="25deg2p5" && w2hi<=12.04 && w2lo>=9.24)good=true;
if(kin=="25deg3p0" && w2hi<=10.28 && w2lo>=6.92)good=true;
if(kin=="25deg3p5" && w2hi<=8.52 && w2lo>=4.68)good=true;
if(kin=="25deg4p4" && w2hi<=5.4 && w2>=1.2)good=true;
if(kin=="29deg2p0" && w2hi<=12.6 && w2lo>=9.88)good=true;
if(kin=="29deg2p4" && w2hi<=10.92 && w2lo>=7.8)good=true;
if(kin=="29deg3p0" && w2hi<=8.44 && w2lo>=4.52)good=true;
if(kin=="29deg3p7" && w2hi<=5.56 && w2>=1.2)good=true;
if(kin=="33deg1p7" && w2hi<=12.76 && w2lo>=10.04)good=true;
if(kin=="33deg2p1" && w2hi<=10.76 && w2lo>=7.4)good=true;
if(kin=="33deg2p6" && w2hi<=8.36 && w2lo>=4.36)good=true;
if(kin=="33deg3p2" && w2hi<=5.48 && w2>=1.2)good=true;
if(kin=="39deg1p3" && w2hi<=13.08 && w2lo>=10.36)good=true;
if(kin=="39deg1p6" && w2hi<=11.32 && w2lo>=8.04)good=true;
if(kin=="39deg2p0" && w2hi<=8.92 && w2lo>=4.92)good=true;
if(kin=="39deg2p5" && w2hi<=5.96 && w2>=1.2)good=true;
 }

 if(spec=="hms"){
   /*
   if(kin=="21deg3p3" && w2<10.44 && w2>9.16)good=true;
   if(kin=="21deg4p0" && w2<8.28 && w2>6.68)good=true;
   if(kin=="21deg4p5" && w2<6.68 && w2>4.92)good=true;
   if(kin=="21deg5p1" && w2<4.84 && w2>2.84)good=true;
   if(kin=="21deg5p7" && w2<2.84 && w2>1.24)good=true;
   */
   if(kin=="21deg3p3" && w2hi<=10.44 && w2lo>=9.16)good=true;
   if(kin=="21deg4p0" && w2hi<=8.28 && w2lo>=6.68)good=true;
   if(kin=="21deg4p5" && w2hi<=6.68 && w2lo>=4.92)good=true;
   if(kin=="21deg5p1" && w2hi<=4.84 && w2lo>=2.84)good=true;
   if(kin=="21deg5p7" && w2hi<=2.84 && w2>=1.2)good=true;
   cout << "In cut W2: "<<w2 << " good: "<<good<<endl;
 }


 cout <<"w2, goodW"<<w2<<"\t"<<good<<endl;

  return good;
}


/*
  if(test<=hi&&test>=lo)res=true;
  if(kin==""shms21deg2p7"){lo=10.6;hi=12.5;}
  if(kin==""shms21deg3p3"){lo=8.4;hi=10.7;}
  if(kin==""shms21deg4p0"){lo=5.8;hi=8.6;}
  if(kin==""shms21deg5p1"){lo=1.75;hi=5.2;}
 */
