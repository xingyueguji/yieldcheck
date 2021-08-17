#!/bin/bash

# Run	Mom	Tgt	Theta	Beam E	BCM1PS2	PS3	
# 2484	5.013	1.01	21.035	10.602	46.953	1	-1
# 2485	5.013	1.01	21.035	10.602	42.8	1	-1
# 2486	5.013	1.01	21.035	10.602	45.927	1	-1
# 2487	5.013	1.01	21.035	10.602	45.809	1	-1
# 2488	5.013	1.01	21.035	10.602	44.626	1	-1

#2489	5.013	26.98	21.035	10.602	38.267	1	-1

#2490	5.013	2.01	21.035	10.602	48.337	2	-1
#2491	5.013	2.01	21.035	10.602	47.078	2	-1
#2492	5.013	2.01	21.035	10.602	46.403	2	-1
#2493	5.013	2.01	21.035	10.602	47.984	2	-1
#2494	5.013	2.01	21.035	10.602	48.678	2	-1

#2517	3.932	26.98	21.035	10.602	35.04	1	-1
#2518	3.932	2.01	21.035	10.602	32.001	5	-1
#2519	3.932	2.01	21.035	10.602	38.99	5	-1
#2520	3.932	2.01	21.035	10.602	37.028	5	-1
#2521	3.932	1.01	21.035	10.602	35.075	2	-1
#2522	3.932	1.01	21.035	10.602	36.427	2	-1
#2523	3.932	1.01	21.035	10.602	34.663	2	-1

#2524	3.244	1.01	21.035	10.602	36.606	3	-1
#2525	3.244	1.01	21.035	10.602	36.587	3	-1
#2526	3.244	1.01	21.035	10.602	37.382	3	-1
#2527	3.244	2.01	21.035	10.602	38.137	3	-1
#2528	3.244	2.01	21.035	10.602	38.862	3	-1
#2529	3.244	2.01	21.035	10.602	35.361	9	-1
#2530	3.244	26.98	21.035	10.602	35.776	2	-1
#2531	3.244	26.98	21.035	10.602	38.789	2	-1

#2549	2.654	2.01	21.035	10.602	54.444	17	-1
#2550	2.654	2.01	21.035	10.602	49.227	17	-1
#2551	2.654	1.01	21.035	10.602	42.698	17	-1
#2552	2.654	1.01	21.035	10.602	43.483	9	-1
#2553	2.654	26.98	21.035	10.602	38.625	3	-1
#2554	2.654	26.98	21.035	10.602	34.697	3	-1

hadd -f dataYieldOut/dataYield_2553_4.root dataYieldOut/dataYield_2553.root dataYieldOut/dataYield_2554.root 
hadd -f dataYieldOut/dataYield_h21deg2p7.root dataYieldOut/dataYield_2551.root dataYieldOut/dataYield_2552.root 
hadd -f dataYieldOut/dataYield_h21deg3p3.root dataYieldOut/dataYield_2524.root dataYieldOut/dataYield_2525.root dataYieldOut/dataYield_2526.root 
hadd -f dataYieldOut/dataYield_h21deg4p0.root dataYieldOut/dataYield_2521.root dataYieldOut/dataYield_2522.root dataYieldOut/dataYield_2523.root 
hadd -f dataYieldOut/dataYield_h21deg5p1.root dataYieldOut/dataYield_2484.root dataYieldOut/dataYield_2485.root dataYieldOut/dataYield_2486.root dataYieldOut/dataYield_2487.root dataYieldOut/dataYield_2488.root 

hadd -f dataYieldOut/dataYield_d21deg2p7.root dataYieldOut/dataYield_2549.root dataYieldOut/dataYield_2550.root 
hadd -f dataYieldOut/dataYield_d21deg3p3.root dataYieldOut/dataYield_2527.root dataYieldOut/dataYield_2528.root dataYieldOut/dataYield_2529.root 
hadd -f dataYieldOut/dataYield_d21deg4p0.root dataYieldOut/dataYield_2518.root dataYieldOut/dataYield_2519.root dataYieldOut/dataYield_2520.root 
hadd -f dataYieldOut/dataYield_d21deg5p1.root dataYieldOut/dataYield_2490.root dataYieldOut/dataYield_2491.root dataYieldOut/dataYield_2492.root dataYieldOut/dataYield_2493.root dataYieldOut/dataYield_2494.root 

