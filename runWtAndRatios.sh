#!/Bin/bash

#source runShms21deg.sh
#source combineShms21deg.sh
#
root -b -q 'mcWt.cpp("h","21","2p7")'
root -b -q 'mcWt.cpp("h","21","3p3")'
root -b -q 'mcWt.cpp("h","21","4p0")'
root -b -q 'mcWt.cpp("h","21","5p1")'
root -b -q 'mcWt.cpp("d","21","2p7")'
root -b -q 'mcWt.cpp("d","21","3p3")'
root -b -q 'mcWt.cpp("d","21","4p0")'
root -b -q 'mcWt.cpp("d","21","5p1")'

root -b -q 'ratios.cpp("h21deg2p7")'
root -b -q 'ratios.cpp("h21deg3p3")'
root -b -q 'ratios.cpp("h21deg4p0")'
root -b -q 'ratios.cpp("h21deg5p1")'

root -b -q 'ratios.cpp("d21deg2p7")'
root -b -q 'ratios.cpp("d21deg3p3")'
root -b -q 'ratios.cpp("d21deg4p0")'
root -b -q 'ratios.cpp("d21deg5p1")'

root -b -q 'plot_cx.cpp("h","21")'
root -b -q 'plot_cx.cpp("d","21")'
root -b -q 'plot_cx.cpp("r","21")'

