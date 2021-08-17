#!/Bin/bash

root -b -q 'runDataYields.cpp("21","al","all")';
root -b -q 'runDataYields.cpp("21","h","all")';

cd dataYieldOut/pass25

hadd -f shms_dataYield_al21deg5p1.root shms_al21deg5p1*
hadd -f shms_dataYield_al21deg4p0.root shms_al21deg4p0*
hadd -f shms_dataYield_al21deg3p3.root shms_al21deg3p3*
hadd -f shms_dataYield_al21deg2p7.root shms_al21deg2p7*

hadd -f shms_dataYield_h21deg5p1.root shms_h21deg5p1*
hadd -f shms_dataYield_h21deg4p0.root shms_h21deg4p0*
hadd -f shms_dataYield_h21deg3p3.root shms_h21deg3p3*
hadd -f shms_dataYield_h21deg2p7.root shms_h21deg2p7*

