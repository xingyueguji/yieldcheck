Float_t getCharge(string kin="h21deg2p7"){

Float_t charge=0;

 
  if(kin=="c25deg2p5")
    { 
      charge+=readReport(3083,"BCM4C charge");
      charge+=readReport(3084,"BCM4C charge");
    }

  if(kin=="c25deg3p0")
    { 
      charge+=readReport(3070,"BCM4C charge");
      charge+=readReport(3071,"BCM4C charge");
    }

  if(kin=="c25deg3p5")
    { 
      charge+=readReport(3057,"BCM4C charge");
      charge+=readReport(3058,"BCM4C charge");
      charge+=readReport(3059,"BCM4C charge");
    }

  if(kin=="c25deg4p4")
    { 
      charge+=readReport(3056,"BCM4C charge");
      charge+=readReport(3036,"BCM4C charge");
      charge+=readReport(3037,"BCM4C charge");
    }

  if(kin=="c21deg2p7")
    { 
      charge+=readReport(2547,"BCM4C charge");
      charge+=readReport(2548,"BCM4C charge");
    }
  if(kin=="c21deg3p3")
    { 
      charge+=readReport(2540,"BCM4C charge");
      charge+=readReport(2541,"BCM4C charge");
    }
  if(kin=="c21deg4p0")
    { 
      charge+=readReport(2509,"BCM4C charge");
      charge+=readReport(2510,"BCM4C charge");
    }
  if(kin=="c21deg5p1")
    { 
      charge+=readReport(2507,"BCM4C charge");
      charge+=readReport(2508,"BCM4C charge");
    }

  if(kin=="d21deg5p1")
    { 
      charge+=readReport(2490,"BCM4C charge");
      charge+=readReport(2491,"BCM4C charge");
      charge+=readReport(2492,"BCM4C charge");
      charge+=readReport(2493,"BCM4C charge");
      charge+=readReport(2494,"BCM4C charge");
    }

  if(kin=="h21deg5p1")
    { 
      charge+=readReport(2484,"BCM4C charge");
      charge+=readReport(2485,"BCM4C charge");
      charge+=readReport(2486,"BCM4C charge");
      charge+=readReport(2487,"BCM4C charge");
      charge+=readReport(2488,"BCM4C charge");
    }

  if(kin=="d21deg4p0")
    { 
      charge+=readReport(2518,"BCM4C charge");
      charge+=readReport(2519,"BCM4C charge");
      charge+=readReport(2520,"BCM4C charge");
    }

  if(kin=="h21deg4p0")
    { 
      charge+=readReport(2521,"BCM4C charge");
      charge+=readReport(2522,"BCM4C charge");
      charge+=readReport(2523,"BCM4C charge");
    }

  if(kin=="d21deg3p3")
    { 
      charge+=readReport(2527,"BCM4C charge");
      charge+=readReport(2528,"BCM4C charge");
      charge+=readReport(2529,"BCM4C charge");
    }

  if(kin=="h21deg3p3")
    { 
      charge+=readReport(2524,"BCM4C charge");
      charge+=readReport(2525,"BCM4C charge");
      charge+=readReport(2526,"BCM4C charge");
    }

  if(kin=="d21deg2p7")
    { 
      charge+=readReport(2549,"BCM4C charge");
      charge+=readReport(2550,"BCM4C charge");
    }

  if(kin=="h21deg2p7")
    { 
      charge+=readReport(2551,"BCM4C charge");
      charge+=readReport(2552,"BCM4C charge");
    }

  return charge;
}
