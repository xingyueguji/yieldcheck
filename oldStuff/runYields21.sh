#!/Bin/bash

root -b -q 'runDataYields.cpp("21","al","all")';
root -b -q 'runDataYields.cpp("21","h","all")';
root -b -q 'runDataYields.cpp("21","d","all")';
#root -b -q 'runDataYields.cpp("21","c","all")';

cd dataYieldOut/pass20

hadd -f dataYield_al21deg5p1.root al21deg5p1*
hadd -f dataYield_al21deg4p0.root al21deg4p0*
hadd -f dataYield_al21deg3p3.root al21deg3p3*
hadd -f dataYield_al21deg2p7.root al21deg2p7*
rm al21deg*

hadd -f dataYield_h21deg5p1.root h21deg5p1*
hadd -f dataYield_h21deg4p0.root h21deg4p0*
hadd -f dataYield_h21deg3p3.root h21deg3p3*
hadd -f dataYield_h21deg2p7.root h21deg2p7*
rm h21deg*

hadd -f dataYield_d21deg5p1.root d21deg5p1*
hadd -f dataYield_d21deg4p0.root d21deg4p0*
hadd -f dataYield_d21deg3p3.root d21deg3p3*
hadd -f dataYield_d21deg2p7.root d21deg2p7*
rm d21deg*

#hadd -f dataYield_c21deg5p1.root c21deg5p1*
#hadd -f dataYield_c21deg4p0.root c21deg4p0*
#hadd -f dataYield_c21deg3p3.root c21deg3p3*
#hadd -f dataYield_c21deg2p7.root c21deg2p7*
#rm c21deg*

