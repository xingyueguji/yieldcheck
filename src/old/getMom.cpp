//#include "readReport.cpp"
#include "readReport.cpp"
Float_t getMom(string kin="h21deg2p7", string spec="hms"){

Float_t mom=0;

 
 if(spec=="hms"){
  if(kin=="d21deg5p7")
    { 
      mom=readReport(1574,"mom");
    }

  if(kin=="h21deg5p7")
    { 
      mom=readReport(1565,"mom");
    }
  if(kin=="d21deg5p1")
    { 
      mom=readReport(1599,"mom");
    }

  if(kin=="h21deg5p1")
    { 
      mom=readReport(1600,"mom");
    }

  if(kin=="d21deg4p5")
    { 
      mom=readReport(1606,"mom");
    }

  if(kin=="h21deg4p5")
    { 
      mom=readReport(1603,"mom");
    }

  if(kin=="d21deg4p0")
    { 
      mom=readReport(1624,"mom");
    }

  if(kin=="h21deg4p0")
    { 
      mom=readReport(1626,"mom");
    }

  if(kin=="d21deg3p3")
    { 
      mom=readReport(1640,"mom");
    }

  if(kin=="h21deg3p3")
    { 
      mom=readReport(1639,"mom");
    }
 }
 
if(spec=="shms"){
   if(kin=="h21deg2p7")mom=readReport(2551,"mom");
   if(kin=="d21deg2p7")mom=readReport(2550,"mom");
   if(kin=="h21deg3p3")mom=readReport(2526,"mom");
   if(kin=="d21deg3p3")mom=readReport(2527,"mom");
   if(kin=="h21deg4p0")mom=readReport(2521,"mom");
   if(kin=="d21deg4p0")mom=readReport(2518,"mom");
   if(kin=="h21deg5p1")mom=readReport(2484,"mom");
   if(kin=="d21deg5p1")mom=readReport(2490,"mom");
   if(kin=="h39deg2p5")mom=2.458;
   if(kin=="h39deg2p0")mom=1.966;
   if(kin=="h39deg1p6")mom=1.573;
   if(kin=="h39deg1p3")mom=1.278;
   if(kin=="d39deg2p5")mom=2.458;
   if(kin=="d39deg2p0")mom=1.966;
   if(kin=="d39deg1p6")mom=1.573;
   if(kin=="d39deg1p3")mom=1.278;
 }

  return mom;
}
