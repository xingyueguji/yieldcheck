#!/Bin/bash


cd dataYieldOut/pass61

hadd -f shms_dataYield_al21deg3p3_h.root shms_al21deg3p3_h*
hadd -f shms_dataYield_al21deg3p3_d.root shms_al21deg3p3_d*
hadd -f shms_dataYield_h21deg3p3.root shms_h21deg3p3*
hadd -f shms_dataYield_d21deg3p3.root shms_d21deg3p3*

gocx

