TF1* getCSB(string angle="21"){

  TF1 *fun=new TF1("fun","exp([0])*(exp([1]*(10.602-x))-1.)",0.5,7);
  if(angle=="21")fun->SetParameters(-31.4,3.57);
  if(angle=="25")fun->SetParameters(-39.74,4.36);
  if(angle=="29")fun->SetParameters(-48.2,5.19);
  if(angle=="33")fun->SetParameters(-56.45,5.96);
  if(angle=="39")fun->SetParameters(-69.0,7.14);
  return fun;
}
