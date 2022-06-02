#!/Bin/bash
root -b -q figure1.cpp
root -b -q figure2.cpp

rm xsec_*txt
rm glob*txt

root -b -q 'cxAndratios.cpp(20)'
root -b -q 'cxAndratios.cpp(21)'
root -b -q 'cxAndratios.cpp(25)'
root -b -q 'cxAndratios.cpp(29)'
root -b -q 'cxAndratios.cpp(33)'
root -b -q 'cxAndratios.cpp(39)'

pdfunite shms*deg_324*pdf noKin_xsec.pdf

