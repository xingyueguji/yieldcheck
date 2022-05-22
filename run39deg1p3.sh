#!/Bin/bash

root -b -q 'runDataYields.cpp("39","al","1p3","shms","h")';
root -b -q 'runDataYields.cpp("39","h","1p3")';

cd dataYieldOut/pass62

hadd -f shms_dataYield_al39deg1p3_h.root shms_al39deg1p3_h*

hadd -f shms_dataYield_h39deg1p3.root shms_h39deg1p3*

