#!/Bin/bash

root -b -q 'runDataYields.cpp("33","al","all","shms","h")';
root -b -q 'runDataYields.cpp("33","al","all","shms","d")';
root -b -q 'runDataYields.cpp("33","h","all")';
root -b -q 'runDataYields.cpp("33","d","all")';
root -b -q 'runDataYields.cpp("33","c","all")';

cd dataYieldOut/pass51

hadd -f shms_dataYield_al33deg3p2_h.root shms_al33deg3p2_h*
hadd -f shms_dataYield_al33deg2p6_h.root shms_al33deg2p6_h*
hadd -f shms_dataYield_al33deg2p1_h.root shms_al33deg2p1_h*
hadd -f shms_dataYield_al33deg1p7_h.root shms_al33deg1p7_h*

hadd -f shms_dataYield_al33deg3p2_d.root shms_al33deg3p2_d*
hadd -f shms_dataYield_al33deg2p6_d.root shms_al33deg2p6_d*
hadd -f shms_dataYield_al33deg2p1_d.root shms_al33deg2p1_d*
hadd -f shms_dataYield_al33deg1p7_d.root shms_al33deg1p7_d*

hadd -f shms_dataYield_h33deg3p2.root shms_h33deg3p2*
hadd -f shms_dataYield_h33deg2p6.root shms_h33deg2p6*
hadd -f shms_dataYield_h33deg2p1.root shms_h33deg2p1*
hadd -f shms_dataYield_h33deg1p7.root shms_h33deg1p7*
hadd -f shms_dataYield_d33deg3p2.root shms_d33deg3p2*
hadd -f shms_dataYield_d33deg2p6.root shms_d33deg2p6*
hadd -f shms_dataYield_d33deg2p1.root shms_d33deg2p1*
hadd -f shms_dataYield_d33deg1p7.root shms_d33deg1p7*
hadd -f shms_dataYield_c33deg3p2.root shms_c33deg3p2*
hadd -f shms_dataYield_c33deg2p6.root shms_c33deg2p6*
hadd -f shms_dataYield_c33deg2p1.root shms_c33deg2p1*
hadd -f shms_dataYield_c33deg1p7.root shms_c33deg1p7*
