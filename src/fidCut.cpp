
bool fidCut(double xfp=0, double yfp=0, double xpfp=0, double ypfp=0 ){
  bool success=false;

  if (xfp <= 38. && xfp >=-38.)
    if (yfp <= 38. && yfp >=-38.)
      if (xpfp <= 0.15 && xpfp >=-0.15)
	if (ypfp <= 0.08 && ypfp >= -0.08)
	  if(abs(xfp - 460. * xpfp) <= 20.)
	    if(abs(yfp - 460. * ypfp) <= 20.)
	    success=true;
  return success;
}
