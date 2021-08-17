#!/Bin/bash

root -b -q 'runDataYields.cpp("25","al","all")';
root -b -q 'runDataYields.cpp("25","h","all")';
root -b -q 'runDataYields.cpp("25","d","all")';
root -b -q 'runDataYields.cpp("25","c","all")';

cd dataYieldOut/pass11

hadd -f dataYield_al25deg4p4.root al25deg4p4*
hadd -f dataYield_al25deg3p5.root al25deg3p5*
hadd -f dataYield_al25deg3p0.root al25deg3p0*
hadd -f dataYield_al25deg2p5.root al25deg2p5*
hadd -f dataYield_h25deg4p4.root h25deg4p4*
hadd -f dataYield_h25deg3p5.root h25deg3p5*
hadd -f dataYield_h25deg3p0.root h25deg3p0*
hadd -f dataYield_h25deg2p5.root h25deg2p5*
hadd -f dataYield_d25deg4p4.root d25deg4p4*
hadd -f dataYield_d25deg3p5.root d25deg3p5*
hadd -f dataYield_d25deg3p0.root d25deg3p0*
hadd -f dataYield_d25deg2p5.root d25deg2p5*
hadd -f dataYield_c25deg4p4.root c25deg4p4*
hadd -f dataYield_c25deg3p5.root c25deg3p5*
hadd -f dataYield_c25deg3p0.root c25deg3p0*
hadd -f dataYield_c25deg2p5.root c25deg2p5*

rm al25deg*
rm d25deg*
rm h25deg*
rm c25deg*
