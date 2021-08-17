#!/Bin/bash

root -b -q 'runDataYields.cpp("39","al","all")';
root -b -q 'runDataYields.cpp("39","h","all")';
root -b -q 'runDataYields.cpp("39","d","all")';
root -b -q 'runDataYields.cpp("39","c","all")';

cd dataYieldOut/pass11

hadd -f dataYield_al39deg2p5.root al39deg2p5*
hadd -f dataYield_al39deg2p0.root al39deg2p0*
hadd -f dataYield_al39deg1p6.root al39deg1p6*
hadd -f dataYield_al39deg1p3.root al39deg1p3*

hadd -f dataYield_h39deg2p5.root h39deg2p5*
hadd -f dataYield_h39deg2p0.root h39deg2p0*
hadd -f dataYield_h39deg1p6.root h39deg1p6*
hadd -f dataYield_h39deg1p3.root h39deg1p3*

hadd -f dataYield_d39deg2p5.root d39deg2p5*
hadd -f dataYield_d39deg2p0.root d39deg2p0*
hadd -f dataYield_d39deg1p6.root d39deg1p6*
hadd -f dataYield_d39deg1p3.root d39deg1p3*

hadd -f dataYield_c39deg2p5.root c39deg2p5*
hadd -f dataYield_c39deg2p0.root c39deg2p0*
hadd -f dataYield_c39deg1p6.root c39deg1p6*
hadd -f dataYield_c39deg1p3.root c39deg1p3*

rm al39deg*
rm d39deg*
rm h39deg*
rm c39deg*
