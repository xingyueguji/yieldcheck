#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void makeRunTable(){

  //  string froot;
  TString froot;
  ifstream file;
  ofstream outFile;
  string word, t, q, filename;
  string run, mom, tgt, ang, ene, tim, cur;

  outFile.open("runTable.txt");
  outFile << "Run"<<"\t"<<"Mom"<<"\t"<<"Tgt"<<"\t"<<"Theta"<<"\t"<<"Beam E"<<"\t"<<"BCM1"<<"\t"<<"Time (s)"<<endl;

  for(Int_t i=2400;i<3200;i++){
  //  for(Int_t i=3000;i<3010;i++){
        froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-0-shms-report/replay_shms_production_%d_-1.report",i);
  //string froot ="/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-0-shms-report/replay_shms_production_3000_-1.report";
  file.open(froot);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
    if(file.is_open()==1){
  cout<<froot<<endl;
  // extracting words from the file                                                  
  while (file >> word)
    {
      if (word=="Num"){
        file >> word; //get colon                                                      
        file >> run; //get value                                                       
      }
      if (word=="Momentum"){
        file >> word; //get colon                                                      
        file >> mom; //get value                                                       
      }
      if (word=="AMU"){
        file >> word; //get colon                                                      
        file >> tgt; //get value                                                       
      }
      if (word=="Theta"){
        file >> word; //get colon                                                      
        file >> ang; //get value                                                       
      }
      if (word=="Energy"){
        file >> word; //get colon                                                      
        file >> ene; //get value                                                       
      }
      if (word=="Length"){
        file >> word; //get colon                                                      
        file >> tim; //get value                                                       
      }
      if (word=="BCM1"){
        file >> word; 
	if (word=="Current:"){ //is the next word current
        file >> cur; //get value                                                       
      }
      }
      //    }
  }
  // displaying content                                                                 
  cout << "Run"<<"\t"<<"Mom"<<"\t"<<"Tgt"<<"\t"<<"Theta"<<"\t"<<"Beam E"<<"\t"<<"BCM1"<<"\t"<<"time (s)"<<endl;
  cout << run<<"\t"<<mom<<"\t"<<tgt<<"\t"<<ang<<"\t"<<ene<<"\t"<<cur<<"\t"<<tim<<endl;
  outFile<<run<<"\t"<<mom<<"\t"<<tgt<<"\t"<<ang<<"\t"<<ene<<"\t"<<cur<<"\t"<<tim<<endl;
  file.close();

    }  
}

  outFile.close();
  return 0;
  
}
