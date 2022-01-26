#!/Bin/bash

root -b -q 'runDataYields.cpp("25","al","4p4","shms","d")';
root -b -q 'runDataYields.cpp("25","al","4p4","shms","h")';
root -b -q 'runDataYields.cpp("25","h","4p4")';
root -b -q 'runDataYields.cpp("25","d","4p4")';
root -b -q 'runDataYields.cpp("25","c","4p4")';

cd dataYieldOut/pass53

hadd -f shms_dataYield_al25deg4p4_h.root shms_al25deg4p4_h*
hadd -f shms_dataYield_al25deg4p4_d.root shms_al25deg4p4_d*
hadd -f shms_dataYield_h25deg4p4.root shms_h25deg4p4*
hadd -f shms_dataYield_d25deg4p4.root shms_d25deg4p4*
hadd -f shms_dataYield_c25deg4p4.root shms_c25deg4p4*


