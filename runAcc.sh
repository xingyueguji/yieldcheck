#!/Bin/bash

root -b -q 'AccCxAndRatios.cpp(20)'
root -b -q 'AccCxAndRatios.cpp(21)'
root -b -q 'AccCxAndRatios.cpp(25)'
root -b -q 'AccCxAndRatios.cpp(29)'
root -b -q 'AccCxAndRatios.cpp(33)'
root -b -q 'AccCxAndRatios.cpp(39)'

pdfunite *acc1.pdf acceptanceMethod57a.pdf
