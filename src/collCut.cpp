
bool collCut(double th=0., double ph=0., double delta=0., double y = 0.){

  bool success=false;
  if(abs(253.*th) < 12.5)
    {
      if(abs( y + 253.* ph - 0.039*delta)<8.5)
	{
	  if(abs(253.*th) <= (6.25 + 1.470588*(y + 253.*ph - 0.039*delta + 8.50)))
	    {
	      if(abs(253.*th) <= (12.5 - 1.470588*(y + 253.*ph - 0.039*delta - 4.25)))
		{
		  success=true;
		}
	    }
	}
    }
  return success;
}
