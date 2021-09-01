#include <iostream>
#include <iomanip>
#include <fstream>
#include "readReport.cpp"

using namespace std;

void makeRunTable(){
  ofstream outFile;
  double run, mom, tgt, ang, ene, cur, ps2, ps3;
  outFile.open("allShmsElCleanRuns.txt");
  outFile << "Run"<<"\t"<<"Mom"<<"\t"<<"Tgt"<<"\t"<<"Theta"<<"\t"<<"Beam E"<<"\t"<<"BCM1"<<"PS2\t"<<"PS3\t"<<endl;
  cout << "Run"<<"\t"<<"Mom"<<"\t"<<"Tgt"<<"\t"<<"Theta"<<"\t"<<"Beam E"<<"\t"<<"BCM1"<<"\t"<<ps2<<"\t"<<ps3<<endl;

  for(Int_t i=2400;i<3300;i++){
    run=i;
    mom=readReport(i,"mom");
    tgt=readReport(i,"target");
    ang=readReport(i,"Spec Angle");
    ene=readReport(i,"energy");
    cur=readReport(i,"BCM4C cut current");
    ps2=readReport(i,"Ps2 fact");
    ps3=readReport(i,"Ps3 fact");      
    if(ene>.1 && ps2<0)
      {
	cout << run<<"\t"<<mom<<"\t"<<tgt<<"\t"<<ang<<"\t"<<ene<<"\t"<<cur<<"\t"<<ps2<<"\t"<<ps3<<endl;
	outFile<<run<<"\t"<<mom<<"\t"<<tgt<<"\t"<<ang<<"\t"<<ene<<"\t"<<cur<<"\t"<<ps2<<"\t"<<ps3<<endl;
      }
  }
  outFile.close();
  return 0;
  
}
