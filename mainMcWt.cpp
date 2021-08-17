

//  g++ calEff.C -o calEff `root-config --cflags --glibs`

#include "mcWt.cpp"
//void mcWt(string tgt="h",string angle="21", string mom="5p7", string spec="hms"){

int main(int argc, char *argv[]){

  string tgt=argv[1];
  string angle=argv[2];
  string mom=argv[3];
  string spec=argv[4];
  cout << tgt <<"\t"<<angle<<"\t"<<mom<<"\t"<<spec<<endl;
  mcWt(tgt,angle,mom,spec);
  return 0;
}
