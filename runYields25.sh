#!/Bin/bash

root -b -q 'runDataYields.cpp("25","al","all","shms","d")';
root -b -q 'runDataYields.cpp("25","al","all","shms","h")';
root -b -q 'runDataYields.cpp("25","h","all")';
root -b -q 'runDataYields.cpp("25","d","all")';
root -b -q 'runDataYields.cpp("25","c","all")';

cd dataYieldOut/pass51

hadd -f shms_dataYield_al25deg4p4_h.root shms_al25deg4p4_h*
hadd -f shms_dataYield_al25deg3p5_h.root shms_al25deg3p5_h*
hadd -f shms_dataYield_al25deg3p0_h.root shms_al25deg3p0_h*
hadd -f shms_dataYield_al25deg2p5_h.root shms_al25deg2p5_h*

hadd -f shms_dataYield_al25deg4p4_d.root shms_al25deg4p4_d*
hadd -f shms_dataYield_al25deg3p5_d.root shms_al25deg3p5_d*
hadd -f shms_dataYield_al25deg3p0_d.root shms_al25deg3p0_d*
hadd -f shms_dataYield_al25deg2p5_d.root shms_al25deg2p5_d*

hadd -f shms_dataYield_h25deg4p4.root shms_h25deg4p4*
hadd -f shms_dataYield_h25deg3p5.root shms_h25deg3p5*
hadd -f shms_dataYield_h25deg3p0.root shms_h25deg3p0*
hadd -f shms_dataYield_h25deg2p5.root shms_h25deg2p5*

hadd -f shms_dataYield_d25deg4p4.root shms_d25deg4p4*
hadd -f shms_dataYield_d25deg3p5.root shms_d25deg3p5*
hadd -f shms_dataYield_d25deg3p0.root shms_d25deg3p0*
hadd -f shms_dataYield_d25deg2p5.root shms_d25deg2p5*

hadd -f shms_dataYield_c25deg4p4.root shms_c25deg4p4*
hadd -f shms_dataYield_c25deg3p5.root shms_c25deg3p5*
hadd -f shms_dataYield_c25deg3p0.root shms_c25deg3p0*
hadd -f shms_dataYield_c25deg2p5.root shms_c25deg2p5*

