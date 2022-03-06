#!/Bin/bash

root -b -q 'runDataYields.cpp("33","d","all")';

cd dataYieldOut/pass56
hadd -f shms_dataYield_d33deg3p2.root shms_d33deg3p2*
hadd -f shms_dataYield_d33deg2p6.root shms_d33deg2p6*
hadd -f shms_dataYield_d33deg2p1.root shms_d33deg2p1*
hadd -f shms_dataYield_d33deg1p7.root shms_d33deg1p7*

gocx
root -b -q 'runDataYields.cpp("39","d","all")';

cd dataYieldOut/pass56
hadd -f shms_dataYield_d39deg2p5.root shms_d39deg2p5*
hadd -f shms_dataYield_d39deg2p0.root shms_d39deg2p0*
hadd -f shms_dataYield_d39deg1p6.root shms_d39deg1p6*
hadd -f shms_dataYield_d39deg1p3.root shms_d39deg1p3*

gocx
root -b -q 'runDataYields.cpp("21","d","all","hms")';

cd dataYieldOut/pass56
hadd -f hms_dataYield_d21deg5p1.root hms_d21deg5p1*
hadd -f hms_dataYield_d21deg4p0.root hms_d21deg4p0*
hadd -f hms_dataYield_d21deg4p5.root hms_d21deg4p5*
hadd -f hms_dataYield_d21deg3p3.root hms_d21deg3p3*
hadd -f hms_dataYield_d21deg5p7.root hms_d21deg5p7*
