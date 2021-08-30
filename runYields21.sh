#!/Bin/bash

root -b -q 'runDataYields.cpp("21","al","all","shms","d")';
root -b -q 'runDataYields.cpp("21","al","all","shms","h")';
root -b -q 'runDataYields.cpp("21","h","all","shms")';
root -b -q 'runDataYields.cpp("21","d","all","shms")';
root -b -q 'runDataYields.cpp("21","c","all","shms")';

cd dataYieldOut/pass36

hadd -f shms_dataYield_al21deg5p1_h.root shms_al21deg5p1_h*
hadd -f shms_dataYield_al21deg4p0_h.root shms_al21deg4p0_h*
hadd -f shms_dataYield_al21deg3p3_h.root shms_al21deg3p3_h*
hadd -f shms_dataYield_al21deg2p7_h.root shms_al21deg2p7_h*

hadd -f shms_dataYield_al21deg5p1_d.root shms_al21deg5p1_d*
hadd -f shms_dataYield_al21deg4p0_d.root shms_al21deg4p0_d*
hadd -f shms_dataYield_al21deg3p3_d.root shms_al21deg3p3_d*
hadd -f shms_dataYield_al21deg2p7_d.root shms_al21deg2p7_d*

hadd -f shms_dataYield_h21deg5p1.root shms_h21deg5p1*
hadd -f shms_dataYield_h21deg4p0.root shms_h21deg4p0*
hadd -f shms_dataYield_h21deg3p3.root shms_h21deg3p3*
hadd -f shms_dataYield_h21deg2p7.root shms_h21deg2p7*

hadd -f shms_dataYield_d21deg5p1.root shms_d21deg5p1*
hadd -f shms_dataYield_d21deg4p0.root shms_d21deg4p0*
hadd -f shms_dataYield_d21deg3p3.root shms_d21deg3p3*
hadd -f shms_dataYield_d21deg2p7.root shms_d21deg2p7*

hadd -f shms_dataYield_c21deg5p1.root shms_c21deg5p1*
hadd -f shms_dataYield_c21deg4p0.root shms_c21deg4p0*
hadd -f shms_dataYield_c21deg3p3.root shms_c21deg3p3*
hadd -f shms_dataYield_c21deg2p7.root shms_c21deg2p7*


