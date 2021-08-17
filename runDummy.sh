#!/Bin/bash

#root -b -q 'runDataYields.cpp("21","al","all","shms","d")';
#root -b -q 'runDataYields.cpp("21","al","all","shms","h")';
cd dataYieldOut/pass43

hadd -f shms_dataYield_al21deg5p1_h.root shms_al21deg5p1_h*
hadd -f shms_dataYield_al21deg4p0_h.root shms_al21deg4p0_h*
hadd -f shms_dataYield_al21deg3p3_h.root shms_al21deg3p3_h*
hadd -f shms_dataYield_al21deg2p7_h.root shms_al21deg2p7_h*

hadd -f shms_dataYield_al21deg5p1_d.root shms_al21deg5p1_d*
hadd -f shms_dataYield_al21deg4p0_d.root shms_al21deg4p0_d*
hadd -f shms_dataYield_al21deg3p3_d.root shms_al21deg3p3_d*
hadd -f shms_dataYield_al21deg2p7_d.root shms_al21deg2p7_d*

gocx

root -b -q 'runDataYields.cpp("25","al","all","shms","d")';
root -b -q 'runDataYields.cpp("25","al","all","shms","h")';

cd dataYieldOut/pass43

hadd -f shms_dataYield_al25deg4p4_h.root shms_al25deg4p4_h*
hadd -f shms_dataYield_al25deg3p5_h.root shms_al25deg3p5_h*
hadd -f shms_dataYield_al25deg3p0_h.root shms_al25deg3p0_h*
hadd -f shms_dataYield_al25deg2p5_h.root shms_al25deg2p5_h*

hadd -f shms_dataYield_al25deg4p4_d.root shms_al25deg4p4_d*
hadd -f shms_dataYield_al25deg3p5_d.root shms_al25deg3p5_d*
hadd -f shms_dataYield_al25deg3p0_d.root shms_al25deg3p0_d*
hadd -f shms_dataYield_al25deg2p5_d.root shms_al25deg2p5_d*

gocx

root -b -q 'runDataYields.cpp("29","al","all","shms","h")';
root -b -q 'runDataYields.cpp("29","al","all","shms","d")';

cd dataYieldOut/pass43

hadd -f shms_dataYield_al29deg3p7_h.root shms_al29deg3p7_h*
hadd -f shms_dataYield_al29deg3p0_h.root shms_al29deg3p0_h*
hadd -f shms_dataYield_al29deg2p4_h.root shms_al29deg2p4_h*
hadd -f shms_dataYield_al29deg2p0_h.root shms_al29deg2p0_h*

hadd -f shms_dataYield_al29deg3p7_d.root shms_al29deg3p7_d*
hadd -f shms_dataYield_al29deg3p0_d.root shms_al29deg3p0_d*
hadd -f shms_dataYield_al29deg2p4_d.root shms_al29deg2p4_d*
hadd -f shms_dataYield_al29deg2p0_d.root shms_al29deg2p0_d*

gocx

root -b -q 'runDataYields.cpp("33","al","all","shms","h")';
root -b -q 'runDataYields.cpp("33","al","all","shms","d")';

cd dataYieldOut/pass43

hadd -f shms_dataYield_al33deg3p2_h.root shms_al33deg3p2_h*
hadd -f shms_dataYield_al33deg2p6_h.root shms_al33deg2p6_h*
hadd -f shms_dataYield_al33deg2p1_h.root shms_al33deg2p1_h*
hadd -f shms_dataYield_al33deg1p7_h.root shms_al33deg1p7_h*

hadd -f shms_dataYield_al33deg3p2_d.root shms_al33deg3p2_d*
hadd -f shms_dataYield_al33deg2p6_d.root shms_al33deg2p6_d*
hadd -f shms_dataYield_al33deg2p1_d.root shms_al33deg2p1_d*
hadd -f shms_dataYield_al33deg1p7_d.root shms_al33deg1p7_d*

gocx

root -b -q 'runDataYields.cpp("39","al","all","shms","h")';
root -b -q 'runDataYields.cpp("39","al","all","shms","d")';

cd dataYieldOut/pass43

hadd -f shms_dataYield_al39deg2p5_h.root shms_al39deg2p5_h*
hadd -f shms_dataYield_al39deg2p0_h.root shms_al39deg2p0_h*
hadd -f shms_dataYield_al39deg1p6_h.root shms_al39deg1p6_h*
hadd -f shms_dataYield_al39deg1p3_h.root shms_al39deg1p3_h*

hadd -f shms_dataYield_al39deg2p5_d.root shms_al39deg2p5_d*
hadd -f shms_dataYield_al39deg2p0_d.root shms_al39deg2p0_d*
hadd -f shms_dataYield_al39deg1p6_d.root shms_al39deg1p6_d*
hadd -f shms_dataYield_al39deg1p3_d.root shms_al39deg1p3_d*

gocx

root -b -q 'runDataYields.cpp("21","al","all","hms","h")';
root -b -q 'runDataYields.cpp("21","al","all","hms","d")';

cd dataYieldOut/pass43

hadd -f hms_dataYield_al21deg5p1_h.root hms_al21deg5p1_h*
hadd -f hms_dataYield_al21deg4p0_h.root hms_al21deg4p0_h*
hadd -f hms_dataYield_al21deg4p5_h.root hms_al21deg4p5_h*
hadd -f hms_dataYield_al21deg3p3_h.root hms_al21deg3p3_h*
hadd -f hms_dataYield_al21deg5p7_h.root hms_al21deg5p7_h*

hadd -f hms_dataYield_al21deg5p1_d.root hms_al21deg5p1_d*
hadd -f hms_dataYield_al21deg4p0_d.root hms_al21deg4p0_d*
hadd -f hms_dataYield_al21deg4p5_d.root hms_al21deg4p5_d*
hadd -f hms_dataYield_al21deg3p3_d.root hms_al21deg3p3_d*
hadd -f hms_dataYield_al21deg5p7_d.root hms_al21deg5p7_d*
