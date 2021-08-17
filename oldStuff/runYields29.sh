#!/Bin/bash

root -b -q 'runDataYields.cpp("29","al","all")';
root -b -q 'runDataYields.cpp("29","h","all")';
root -b -q 'runDataYields.cpp("29","d","all")';
root -b -q 'runDataYields.cpp("29","c","all")';

cd dataYieldOut/pass11
hadd -f dataYield_al29deg3p7.root al29deg3p7*
hadd -f dataYield_al29deg3p0.root al29deg3p0*
hadd -f dataYield_al29deg2p4.root al29deg2p4*
hadd -f dataYield_al29deg2p0.root al29deg2p0*
hadd -f dataYield_h29deg3p7.root h29deg3p7*
hadd -f dataYield_h29deg3p0.root h29deg3p0*
hadd -f dataYield_h29deg2p4.root h29deg2p4*
hadd -f dataYield_h29deg2p0.root h29deg2p0*
hadd -f dataYield_d29deg3p7.root d29deg3p7*
hadd -f dataYield_d29deg3p0.root d29deg3p0*
hadd -f dataYield_d29deg2p4.root d29deg2p4*
hadd -f dataYield_d29deg2p0.root d29deg2p0*
hadd -f dataYield_c29deg3p7.root c29deg3p7*
hadd -f dataYield_c29deg3p0.root c29deg3p0*
hadd -f dataYield_c29deg2p4.root c29deg2p4*
hadd -f dataYield_c29deg2p0.root c29deg2p0*
rm al29deg*
rm d29deg*
rm h29deg*
rm c29deg*
