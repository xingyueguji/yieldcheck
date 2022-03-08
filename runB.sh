#!/Bin/bash

root -b -q 'runDataYields.cpp("29","d","all")';
root -b -q 'runDataYields.cpp("29","c","all")';

cd dataYieldOut/pass56

hadd -f shms_dataYield_d29deg3p7.root shms_d29deg3p7*
hadd -f shms_dataYield_d29deg3p0.root shms_d29deg3p0*
hadd -f shms_dataYield_d29deg2p4.root shms_d29deg2p4*
hadd -f shms_dataYield_d29deg2p0.root shms_d29deg2p0*

hadd -f shms_dataYield_c29deg3p7.root shms_c29deg3p7*
hadd -f shms_dataYield_c29deg3p0.root shms_c29deg3p0*
hadd -f shms_dataYield_c29deg2p4.root shms_c29deg2p4*
hadd -f shms_dataYield_c29deg2p0.root shms_c29deg2p0*

