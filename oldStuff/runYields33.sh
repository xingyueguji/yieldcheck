#!/Bin/bash

root -b -q 'runDataYields.cpp("33","al","all")';
root -b -q 'runDataYields.cpp("33","h","all")';
root -b -q 'runDataYields.cpp("33","d","all")';
root -b -q 'runDataYields.cpp("33","c","all")';

cd dataYieldOut/pass11
hadd -f dataYield_al33deg3p2.root al33deg3p2*
hadd -f dataYield_al33deg2p6.root al33deg2p6*
hadd -f dataYield_al33deg2p1.root al33deg2p1*
hadd -f dataYield_al33deg1p7.root al33deg1p7*
hadd -f dataYield_h33deg3p2.root h33deg3p2*
hadd -f dataYield_h33deg2p6.root h33deg2p6*
hadd -f dataYield_h33deg2p1.root h33deg2p1*
hadd -f dataYield_h33deg1p7.root h33deg1p7*
hadd -f dataYield_d33deg3p2.root d33deg3p2*
hadd -f dataYield_d33deg2p6.root d33deg2p6*
hadd -f dataYield_d33deg2p1.root d33deg2p1*
hadd -f dataYield_d33deg1p7.root d33deg1p7*
hadd -f dataYield_c33deg3p2.root c33deg3p2*
hadd -f dataYield_c33deg2p6.root c33deg2p6*
hadd -f dataYield_c33deg2p1.root c33deg2p1*
hadd -f dataYield_c33deg1p7.root c33deg1p7*
rm al33deg*
rm d33deg*
rm h33deg*
rm c33deg*
