//g++ compiledMcWt.cpp -o mcWt `root-config --cflags --glibs`
#include "mcWt3.cpp"

int main(int argc, char **argv)
{
  cout << "argc:"<<argc<<endl; 
 if(argc==5)
    {
      string tgt=argv[1];
      string angle=argv[2];
      string mom=argv[3];
      string spec=argv[4];
      mcWt(tgt,angle,mom,spec);
    }
  else {
cout << "You need to enter:"<<endl;
cout << "1) Target:"<<endl;
cout << "2) Angle:"<<endl;
cout << "3) Momentum:"<<endl;
cout << "4) SHMS/HMS:"<<endl;
  }
  return 0;
}
