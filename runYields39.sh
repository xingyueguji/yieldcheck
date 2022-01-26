#!/Bin/bash

root -b -q 'runDataYields.cpp("39","al","all","shms","h")';
root -b -q 'runDataYields.cpp("39","al","all","shms","d")';
root -b -q 'runDataYields.cpp("39","h","all")';
root -b -q 'runDataYields.cpp("39","d","all")';
root -b -q 'runDataYields.cpp("39","c","all")';

cd dataYieldOut/pass53

hadd -f shms_dataYield_al39deg2p5_h.root shms_al39deg2p5_h*
hadd -f shms_dataYield_al39deg2p0_h.root shms_al39deg2p0_h*
hadd -f shms_dataYield_al39deg1p6_h.root shms_al39deg1p6_h*
hadd -f shms_dataYield_al39deg1p3_h.root shms_al39deg1p3_h*

hadd -f shms_dataYield_al39deg2p5_d.root shms_al39deg2p5_d*
hadd -f shms_dataYield_al39deg2p0_d.root shms_al39deg2p0_d*
hadd -f shms_dataYield_al39deg1p6_d.root shms_al39deg1p6_d*
hadd -f shms_dataYield_al39deg1p3_d.root shms_al39deg1p3_d*

hadd -f shms_dataYield_h39deg2p5.root shms_h39deg2p5*
hadd -f shms_dataYield_h39deg2p0.root shms_h39deg2p0*
hadd -f shms_dataYield_h39deg1p6.root shms_h39deg1p6*
hadd -f shms_dataYield_h39deg1p3.root shms_h39deg1p3*

hadd -f shms_dataYield_d39deg2p5.root shms_d39deg2p5*
hadd -f shms_dataYield_d39deg2p0.root shms_d39deg2p0*
hadd -f shms_dataYield_d39deg1p6.root shms_d39deg1p6*
hadd -f shms_dataYield_d39deg1p3.root shms_d39deg1p3*

hadd -f shms_dataYield_c39deg2p5.root shms_c39deg2p5*
hadd -f shms_dataYield_c39deg2p0.root shms_c39deg2p0*
hadd -f shms_dataYield_c39deg1p6.root shms_c39deg1p6*
hadd -f shms_dataYield_c39deg1p3.root shms_c39deg1p3*

