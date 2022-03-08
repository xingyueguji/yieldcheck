#!/Bin/bash

root -b -q 'runDataYields.cpp("25","d","all")';
root -b -q 'runDataYields.cpp("25","c","all")';

cd dataYieldOut/pass56

hadd -f shms_dataYield_d25deg4p4.root shms_d25deg4p4*
hadd -f shms_dataYield_d25deg3p5.root shms_d25deg3p5*
hadd -f shms_dataYield_d25deg3p0.root shms_d25deg3p0*
hadd -f shms_dataYield_d25deg2p5.root shms_d25deg2p5*

hadd -f shms_dataYield_c25deg4p4.root shms_c25deg4p4*
hadd -f shms_dataYield_c25deg3p5.root shms_c25deg3p5*
hadd -f shms_dataYield_c25deg3p0.root shms_c25deg3p0*
hadd -f shms_dataYield_c25deg2p5.root shms_c25deg2p5*

