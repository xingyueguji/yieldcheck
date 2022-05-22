#!/Bin/bash

root -b -q 'runDataYields.cpp("29","al","all","shms","h")';
root -b -q 'runDataYields.cpp("29","al","all","shms","d")';
root -b -q 'runDataYields.cpp("29","h","all")';
root -b -q 'runDataYields.cpp("29","d","all")';
root -b -q 'runDataYields.cpp("29","c","all")';

cd dataYieldOut/pass64

hadd -f shms_dataYield_al29deg3p7_h.root shms_al29deg3p7_h*
hadd -f shms_dataYield_al29deg3p0_h.root shms_al29deg3p0_h*
hadd -f shms_dataYield_al29deg2p4_h.root shms_al29deg2p4_h*
hadd -f shms_dataYield_al29deg2p0_h.root shms_al29deg2p0_h*

hadd -f shms_dataYield_al29deg3p7_d.root shms_al29deg3p7_d*
hadd -f shms_dataYield_al29deg3p0_d.root shms_al29deg3p0_d*
hadd -f shms_dataYield_al29deg2p4_d.root shms_al29deg2p4_d*
hadd -f shms_dataYield_al29deg2p0_d.root shms_al29deg2p0_d*

hadd -f shms_dataYield_h29deg3p7.root shms_h29deg3p7*
hadd -f shms_dataYield_h29deg3p0.root shms_h29deg3p0*
hadd -f shms_dataYield_h29deg2p4.root shms_h29deg2p4*
hadd -f shms_dataYield_h29deg2p0.root shms_h29deg2p0*

hadd -f shms_dataYield_d29deg3p7.root shms_d29deg3p7*
hadd -f shms_dataYield_d29deg3p0.root shms_d29deg3p0*
hadd -f shms_dataYield_d29deg2p4.root shms_d29deg2p4*
hadd -f shms_dataYield_d29deg2p0.root shms_d29deg2p0*

hadd -f shms_dataYield_c29deg3p7.root shms_c29deg3p7*
hadd -f shms_dataYield_c29deg3p0.root shms_c29deg3p0*
hadd -f shms_dataYield_c29deg2p4.root shms_c29deg2p4*
hadd -f shms_dataYield_c29deg2p0.root shms_c29deg2p0*

