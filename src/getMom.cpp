//#include "readReport.cpp"
//#include "readReport.cpp"
Float_t getMom(string kin="h21deg2p7", string spec="shms"){
  Float_t mom=0;
  
  if(spec=="shms"){
    if(kin=="h21deg5p1"||kin=="d21deg5p1"||kin=="c21deg5p1")mom=5.013;
    if(kin=="h21deg4p0"||kin=="d21deg4p0"||kin=="c21deg4p0")mom=3.932;
    if(kin=="h21deg3p3"||kin=="d21deg3p3"||kin=="c21deg3p3")mom=3.244;
    if(kin=="h21deg2p7"||kin=="d21deg2p7"||kin=="c21deg2p7")mom=2.654;
    if(kin=="h39deg2p5"||kin=="d39deg2p5"||kin=="c39deg2p5")mom=2.458;
    if(kin=="h39deg2p0"||kin=="d39deg2p0"||kin=="c39deg2p0")mom=1.966;
    if(kin=="h39deg1p6"||kin=="d39deg1p6"||kin=="c39deg1p6")mom=1.573;
    if(kin=="h39deg1p3"||kin=="d39deg1p3"||kin=="c39deg1p3")mom=1.278;
    if(kin=="h33deg3p2"||kin=="d33deg3p2"||kin=="c33deg3p2")mom=3.146;
    if(kin=="h33deg2p6"||kin=="d33deg2p6"||kin=="c33deg2p6")mom=2.556;
    if(kin=="h33deg2p1"||kin=="d33deg2p1"||kin=="c33deg2p1")mom=2.064;
    if(kin=="h33deg1p7"||kin=="d33deg1p7"||kin=="c33deg1p7")mom=1.661;
    if(kin=="h29deg3p7"||kin=="d29deg3p7"||kin=="c29deg3p7")mom=3.637;
    if(kin=="h29deg3p0"||kin=="d29deg3p0"||kin=="c29deg3p0")mom=2.949;
    if(kin=="h29deg2p4"||kin=="d29deg2p4"||kin=="c29deg2p4")mom=2.359;
    if(kin=="h29deg2p0"||kin=="d29deg2p0"||kin=="c29deg2p0")mom=1.966;
    if(kin=="h25deg4p4"||kin=="d25deg4p4"||kin=="c25deg4p4")mom=4.325;
    if(kin=="h25deg3p5"||kin=="d25deg3p5"||kin=="c25deg3p5")mom=3.441;
    if(kin=="h25deg3p0"||kin=="d25deg3p0"||kin=="c25deg3p0")mom=2.949;
    if(kin=="h25deg2p5"||kin=="d25deg2p5"||kin=="c25deg2p5")mom=2.458;
  }
  if(spec=="hms"){
    if(kin=="h21deg5p7"||kin=="d21deg5p7"||kin=="c21deg5p7")mom=5.7;
    if(kin=="h21deg5p1"||kin=="d21deg5p1"||kin=="c21deg5p1")mom=5.1;
    if(kin=="h21deg4p5"||kin=="d21deg4p5"||kin=="c21deg4p5")mom=4.5;
    if(kin=="h21deg4p0"||kin=="d21deg4p0"||kin=="c21deg4p0")mom=4.0;
    if(kin=="h21deg3p3"||kin=="d21deg3p3"||kin=="c21deg3p3")mom=3.3;
    if(kin=="h59deg1p5"||kin=="d59deg1p5"||kin=="c59deg1p5")mom=1.5;
    if(kin=="h59deg1p4"||kin=="d59deg1p4"||kin=="c59deg1p4")mom=1.35;
    if(kin=="h59deg1p2"||kin=="d59deg1p2"||kin=="c59deg1p2")mom=1.18;
    if(kin=="h59deg1p1"||kin=="d59deg1p1"||kin=="c59deg1p1")mom=1.05;
  }
  return mom;
}
