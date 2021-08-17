#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void runNumbers(string spec="shms"){

  //  string froot;
  TString froot;
  ifstream file;
  ofstream outFile;
  string word, t, q, filename;
  string run, mom, tgt, ang, ene, tim, cur;

  outFile.open(Form("%sSimple.txt",spec.c_str()));

  int start=0;
  int stop=10;
  if(spec=="shms")
  {
    start=2200;
    stop=4000;

  }
  if(spec=="hms")
  {
    start=0;
    stop=2200;

  }
  for(Int_t i=start;i<stop;i++)
    {
      if(spec=="shms")froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3c-shms-report/replay_shms_production_%d_-1.report",i);
    if(spec=="hms")froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3b-hms-report/replay_hms_production_%d_-1.report",i);
      file.open(froot);
      cout <<i<<"  Is the File open?"<<  file.is_open()<<endl;
      if(file.is_open()==1)
 	{
 	  outFile<<i<<endl;
 	}
      file.close();
    }
  
  return;


}
