#!/Bin/bash
cd dataYieldOut/pass40

hadd -f hms_dataYield_al21deg5p1_h.root hms_al21deg5p1_h*
hadd -f hms_dataYield_al21deg4p0_h.root hms_al21deg4p0_h*
hadd -f hms_dataYield_al21deg4p5_h.root hms_al21deg4p5_h*
hadd -f hms_dataYield_al21deg3p3_h.root hms_al21deg3p3_h*
hadd -f hms_dataYield_al21deg5p7_h.root hms_al21deg5p7_h*

hadd -f hms_dataYield_al21deg5p1_d.root hms_al21deg5p1_d*
hadd -f hms_dataYield_al21deg4p0_d.root hms_al21deg4p0_d*
hadd -f hms_dataYield_al21deg4p5_d.root hms_al21deg4p5_d*
hadd -f hms_dataYield_al21deg3p3_d.root hms_al21deg3p3_d*
hadd -f hms_dataYield_al21deg5p7_d.root hms_al21deg5p7_d*

hadd -f hms_dataYield_h21deg5p1.root hms_h21deg5p1*
hadd -f hms_dataYield_h21deg4p0.root hms_h21deg4p0*
hadd -f hms_dataYield_h21deg4p5.root hms_h21deg4p5*
hadd -f hms_dataYield_h21deg3p3.root hms_h21deg3p3*
hadd -f hms_dataYield_h21deg5p7.root hms_h21deg5p7*

hadd -f hms_dataYield_d21deg5p1.root hms_d21deg5p1*
hadd -f hms_dataYield_d21deg4p0.root hms_d21deg4p0*
hadd -f hms_dataYield_d21deg4p5.root hms_d21deg4p5*
hadd -f hms_dataYield_d21deg3p3.root hms_d21deg3p3*
hadd -f hms_dataYield_d21deg5p7.root hms_d21deg5p7*

