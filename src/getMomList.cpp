void getMomList(string angle, string (&arrs)[5], float (&arrf)[5], string arm="shms"){

  if(arm=="hms" && angle=="21")
    {
      arrs[0]="3p3";
      arrs[1]="4p0";
      arrs[2]="4p5";
      arrs[3]="5p1";
      arrs[4]="5p7";
      arrf[0]=3.3;
      arrf[1]=4.0;
      arrf[2]=4.5;
      arrf[3]=5.1;
      arrf[4]=5.7;
    }

  if(arm=="shms"){arrs[4]="";arrf[4]=0.0;}

  if(arm=="shms" && angle=="21")
    {
      arrs[0]="2p7";
      arrs[1]="3p3";
      arrs[2]="4p0";
      arrs[3]="5p1";
      arrf[0]=2.7;
      arrf[1]=3.3;
      arrf[2]=4.0;
      arrf[3]=5.1;
    }

  if(arm=="shms" && angle=="25")
    {
      arrs[0]="2p5";
      arrs[1]="3p0";
      arrs[2]="3p5";
      arrs[3]="4p4";
      arrf[0]=2.5;
      arrf[1]=3.0;
      arrf[2]=3.5;
      arrf[3]=4.4;
    }

  if(arm=="shms" && angle=="29")
    {
      arrs[0]="2p0";
      arrs[1]="2p4";
      arrs[2]="3p0";
      arrs[3]="3p7";
      arrf[0]=2.0;
      arrf[1]=2.4;
      arrf[2]=3.0;
      arrf[3]=3.7;
    }

  if(arm=="shms" && angle=="33")
    {
      arrs[0]="1p7";
      arrs[1]="2p1";
      arrs[2]="2p6";
      arrs[3]="3p2";
      arrf[0]=1.7;
      arrf[1]=2.1;
      arrf[2]=2.6;
      arrf[3]=3.2;
    }

  if(arm=="shms" && angle=="39")
    {
      arrs[3]="2p5";
      arrs[2]="2p0";
      arrs[1]="1p6";
      arrs[0]="1p3";
      arrf[3]=2.5;
      arrf[2]=2.0;
      arrf[1]=1.6;
      arrf[0]=1.3;
    }
  return;
}
