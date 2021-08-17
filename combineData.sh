#!/bin/bash

hadd -f dataYieldOut/dataYield_h21deg2p7.root dataYieldOut/h21deg2p7*
hadd -f dataYieldOut/dataYield_h21deg3p3.root dataYieldOut/h21deg3p3*
hadd -f dataYieldOut/dataYield_h21deg4p0.root dataYieldOut/h21deg4p0*
hadd -f dataYieldOut/dataYield_h21deg5p1.root dataYieldOut/h21deg5p1*

hadd -f dataYieldOut/dataYield_d21deg2p7.root dataYieldOut/d21deg2p7*
hadd -f dataYieldOut/dataYield_d21deg3p3.root dataYieldOut/d21deg3p3*
hadd -f dataYieldOut/dataYield_d21deg4p0.root dataYieldOut/d21deg4p0*
hadd -f dataYieldOut/dataYield_d21deg5p1.root dataYieldOut/d21deg5p1*

hadd -f dataYieldOut/dataYield_al21deg2p7.root dataYieldOut/al21deg2p7*
hadd -f dataYieldOut/dataYield_al21deg3p3.root dataYieldOut/al21deg3p3*
hadd -f dataYieldOut/dataYield_al21deg4p0.root dataYieldOut/al21deg4p0*
hadd -f dataYieldOut/dataYield_al21deg5p1.root dataYieldOut/al21deg5p1*
