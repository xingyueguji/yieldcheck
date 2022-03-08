#!/Bin/bash

root -b -q 'runDataYields.cpp("33","al","1p7","shms","h")';
root -b -q 'runDataYields.cpp("33","al","1p7","shms","d")';
root -b -q 'runDataYields.cpp("33","h","1p7")';
root -b -q 'runDataYields.cpp("33","d","1p7")';
root -b -q 'runDataYields.cpp("33","c","1p7")';

cd dataYieldOut/pass56


hadd -f shms_dataYield_al33deg1p7_h.root shms_al33deg1p7_h*
hadd -f shms_dataYield_al33deg1p7_d.root shms_al33deg1p7_d*
hadd -f shms_dataYield_h33deg1p7.root shms_h33deg1p7*
hadd -f shms_dataYield_d33deg1p7.root shms_d33deg1p7*
hadd -f shms_dataYield_c33deg1p7.root shms_c33deg1p7*
