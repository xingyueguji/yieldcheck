double doIrebin(string spec="shms",string angle="21", string mom="3p3"){
  double res; 
  double aa=6;
  double bb=5;
  double cc=4;
  double dd=3;
  double ee=3;
  aa=3;
  bb=3;
  cc=2;
  dd=1;
  dd=1;
 if(spec=="shms"){
   if(angle=="21" && mom=="2p7")res=aa;
   if(angle=="21" && mom=="3p3")res=bb;
   if(angle=="21" && mom=="4p0")res=cc;
   if(angle=="21" && mom=="5p1")res=dd;

   if(angle=="25" && mom=="2p5")res=aa;
   if(angle=="25" && mom=="3p0")res=bb;
   if(angle=="25" && mom=="3p5")res=cc;
   if(angle=="25" && mom=="4p4")res=dd;

   if(angle=="29" && mom=="2p0")res=aa;
   if(angle=="29" && mom=="2p4")res=bb;
   if(angle=="29" && mom=="3p0")res=cc;
   if(angle=="29" && mom=="3p7")res=dd;

   if(angle=="33" && mom=="1p7")res=aa;
   if(angle=="33" && mom=="2p1")res=bb;
   if(angle=="33" && mom=="2p6")res=cc;
   if(angle=="33" && mom=="3p2")res=dd;

   if(angle=="39" && mom=="2p5")res=dd;
   if(angle=="39" && mom=="2p0")res=cc;
   if(angle=="39" && mom=="1p6")res=bb;
   if(angle=="39" && mom=="1p3")res=aa;



  }

  if(spec=="hms"){
   if(angle=="21" && mom=="3p3")res=2;
   if(angle=="21" && mom=="4p0")res=2;
   if(angle=="21" && mom=="4p5")res=2;
   if(angle=="21" && mom=="5p1")res=2;
   if(angle=="21" && mom=="5p7")res=1;
  }
  res=res*2;
  cout << spec<<"\t"<<angle <<"\t"<< mom<<"\t"<< res <<endl;
 return res;

}
