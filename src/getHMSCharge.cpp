Float_t getHMSCharge(string kin="h21deg2p7"){

Float_t charge=0;

 
  if(kin=="h21deg5p7")
    { 
      charge+=readReport(1565,"BCM4C charge");
      charge+=readReport(1571,"BCM4C charge");
      charge+=readReport(1572,"BCM4C charge");
    }

  if(kin=="d21deg5p7")
    { 
      charge+=readReport(1574,"BCM4C charge");
      charge+=readReport(1575,"BCM4C charge");
      charge+=readReport(1576,"BCM4C charge");
      charge+=readReport(1577,"BCM4C charge");
      charge+=readReport(1578,"BCM4C charge");
    }

  if(kin=="h21deg5p1")
    { 
      charge+=readReport(1600,"BCM4C charge");
      charge+=readReport(1601,"BCM4C charge");
      charge+=readReport(1602,"BCM4C charge");
    }
  if(kin=="d21deg5p1")
    { 
      charge+=readReport(1597,"BCM4C charge");
      charge+=readReport(1599,"BCM4C charge");
    }
  if(kin=="h21deg4p5")
    { 
      //      charge+=readReport(1603,"BCM4C charge");
      charge+=readReport(1604,"BCM4C charge");
      charge+=readReport(1605,"BCM4C charge");
    }

  if(kin=="d21deg4p5")
    { 
      charge+=readReport(1606,"BCM4C charge");
      charge+=readReport(1607,"BCM4C charge");
      //      charge+=readReport(1608,"BCM4C charge");
      charge+=readReport(1617,"BCM4C charge");
    }

  if(kin=="h21deg4p0")
    { 
      charge+=readReport(1626,"BCM4C charge");
      charge+=readReport(1627,"BCM4C charge");
    }
  if(kin=="d21deg4p0")
    { 
      charge+=readReport(1624,"BCM4C charge");
      charge+=readReport(1625,"BCM4C charge");
    }

  if(kin=="h21deg3p3")
    { 
      charge+=readReport(1637,"BCM4C charge");
      charge+=readReport(1638,"BCM4C charge");
      charge+=readReport(1639,"BCM4C charge");
    }
  if(kin=="d21deg3p3")
    { 
      charge+=readReport(1640,"BCM4C charge");
    }


  if(kin=="c21deg4p0")
    { 
      charge+=readReport(1622,"BCM4C charge");
      charge+=readReport(1623,"BCM4C charge");
    }
  if(kin=="c21deg4p5")
    { 
      charge+=readReport(1619,"BCM4C charge");
    }
  if(kin=="c21deg5p1")
    { 
      charge+=readReport(1590,"BCM4C charge");
      charge+=readReport(1591,"BCM4C charge");
    }
  if(kin=="c21deg5p7")
    { 
      charge+=readReport(1588,"BCM4C charge");
      charge+=readReport(1589,"BCM4C charge");
    }



  return charge;
}
