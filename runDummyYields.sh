#!/Bin/bash

root -b -q 'runDataYields.cpp("21","al","2p7","shms","no")';
root -b -q 'runDataYields.cpp("25","al","2p5","shms","no")';
root -b -q 'runDataYields.cpp("29","al","2p4","shms","no")';
root -b -q 'runDataYields.cpp("33","al","2p6","shms","no")';
root -b -q 'runDataYields.cpp("39","al","2p0","shms","no")';
root -b -q 'runDataYields.cpp("39","al","2p5","shms","no")';

cd dataYieldOut/pass61

hadd -f shms_dataYield_ald21deg2p7_no.root shms_al21deg2p7_no*
hadd -f shms_dataYield_ald25deg2p5_no.root shms_al25deg2p5_no*
hadd -f shms_dataYield_ald29deg2p4_no.root shms_al29deg2p4_no*
hadd -f shms_dataYield_ald33deg2p6_no.root shms_al33deg2p6_no*
hadd -f shms_dataYield_ald39deg2p0_no.root shms_al39deg2p0_no*
hadd -f shms_dataYield_ald39deg2p5_no.root shms_al39deg2p5_no*






