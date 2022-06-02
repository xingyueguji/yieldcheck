#include "src/getMomList.cpp"
#include "extractCS.cpp"

void makeW2cut(string angle="21"){

  string spec="hms";
 string pset[5];
 float psetf[5];
 angle="21";
 getMomList(angle,pset,psetf,spec);
 auto g20=extractCS(spec,"h",angle,pset[0],5);
 auto g21=extractCS(spec,"h",angle,pset[1],5);
 auto g22=extractCS(spec,"h",angle,pset[2],5);
 auto g23=extractCS(spec,"h",angle,pset[3],5);
 auto g24=extractCS(spec,"h",angle,pset[4],5);
 /*
 angle="21";
 getMomList(angle,pset,psetf,spec);
 auto g20=extractCS(spec,"h",angle,pset[0],5);
 auto g21=extractCS(spec,"h",angle,pset[1],5);
 auto g22=extractCS(spec,"h",angle,pset[2],5);
 auto g23=extractCS(spec,"h",angle,pset[3],5);
 angle="25";
 getMomList(angle,pset,psetf,spec);
  g20=extractCS(spec,"h",angle,pset[0],5);
  g21=extractCS(spec,"h",angle,pset[1],5);
  g22=extractCS(spec,"h",angle,pset[2],5);
  g23=extractCS(spec,"h",angle,pset[3],5);

 angle="29";
 getMomList(angle,pset,psetf,spec);
  g20=extractCS(spec,"h",angle,pset[0],5);
  g21=extractCS(spec,"h",angle,pset[1],5);
  g22=extractCS(spec,"h",angle,pset[2],5);
  g23=extractCS(spec,"h",angle,pset[3],5);

 angle="33";
 getMomList(angle,pset,psetf,spec);
  g20=extractCS(spec,"h",angle,pset[0],5);
  g21=extractCS(spec,"h",angle,pset[1],5);
  g22=extractCS(spec,"h",angle,pset[2],5);
  g23=extractCS(spec,"h",angle,pset[3],5);

 angle="39";
 getMomList(angle,pset,psetf,spec);
  g20=extractCS(spec,"h",angle,pset[0],5);
  g21=extractCS(spec,"h",angle,pset[1],5);
  g22=extractCS(spec,"h",angle,pset[2],5);
  g23=extractCS(spec,"h",angle,pset[3],5);
 spec="hms";
 angle="21";
 g20=extractCS(spec,"h",angle,pset[0],5);
 g21=extractCS(spec,"h",angle,pset[1],5);
 g22=extractCS(spec,"h",angle,pset[2],5);
 g23=extractCS(spec,"h",angle,pset[3],5);
 auto g24=extractCS(spec,"h",angle,pset[3],5);

 */
  return;
}
