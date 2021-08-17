#!/Bin/bash

root -b -q 'runDataYields.cpp("25","al","4p4")';
root -b -q 'runDataYields.cpp("25","h","4p4")';
root -b -q 'runDataYields.cpp("25","d","4p4")';
root -b -q 'runDataYields.cpp("25","c","4p4")';

cd dataYieldOut/pass22

hadd -f shms_dataYield_al25deg4p4.root shms_al25deg4p4*

hadd -f shms_dataYield_h25deg4p4.root shms_h25deg4p4*

hadd -f shms_dataYield_d25deg4p4.root shms_d25deg4p4*
hadd -f shms_dataYield_c25deg4p4.root shms_c25deg4p4*

