Double_t getCalEff(Double_t ene=1.){
  Double_t result=-0.000005759 + 0.9984 - exp(-1.98-0.2356*pow(ene,3));
  return result;
}
