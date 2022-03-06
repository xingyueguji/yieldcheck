#!/Bin/bash

root -b -q 'runDataYields.cpp("21","d","all","shms")';

cd dataYieldOut/pass56
hadd -f shms_dataYield_d21deg5p1.root shms_d21deg5p1*
hadd -f shms_dataYield_d21deg4p0.root shms_d21deg4p0*
hadd -f shms_dataYield_d21deg3p3.root shms_d21deg3p3*
hadd -f shms_dataYield_d21deg2p7.root shms_d21deg2p7*

gocx
root -b -q 'runDataYields.cpp("25","d","all","shms")';

cd dataYieldOut/pass56
hadd -f shms_dataYield_d25deg4p4.root shms_d25deg4p4*
hadd -f shms_dataYield_d25deg3p5.root shms_d25deg3p5*
hadd -f shms_dataYield_d25deg3p0.root shms_d25deg3p0*
hadd -f shms_dataYield_d25deg2p5.root shms_d25deg2p5*

gocx
root -b -q 'runDataYields.cpp("29","d","all","shms")';

cd dataYieldOut/pass56
hadd -f shms_dataYield_d29deg3p7.root shms_d29deg3p7*
hadd -f shms_dataYield_d29deg3p0.root shms_d29deg3p0*
hadd -f shms_dataYield_d29deg2p4.root shms_d29deg2p4*
hadd -f shms_dataYield_d29deg2p0.root shms_d29deg2p0*
