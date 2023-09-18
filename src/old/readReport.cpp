
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

Double_t readReport(Int_t irun=2525, Int_t whatDoYouWant=5){
  //  string froot;
  TString froot;
  ifstream file;

  string word;
  Double_t result;
  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-3-shms-report/replay_shms_production_%d_-1.report",irun);
  file.open(froot);
  cout <<" Is the File open?"<<  file.is_open()<<endl;

    if(file.is_open()==1){
      cout<<froot<<endl;

      //// Get BCM4C Current /////
      if (whatDoYouWant==1){
	while (file >> word){
	  if (word=="BCM4C"){
	    file >> word; 
	    if (word=="Beam"){ 
	      file >> word; 
	      if (word=="Cut"){ 
		file >> word; 
		if (word=="Charge:"){ 
		  file >> result; 		
		}
	      }
	    }
	  }
	}
      }
    ///////////////////////////////////
      //// Get BCM4C Current /////
      if (whatDoYouWant==5){
	while (file >> word){
	  if (word=="BCM4C"){
	    file >> word; 
	    if (word=="Beam"){ 
	      file >> word; 
	      if (word=="Cut"){ 
		file >> word; 
		if (word=="Current:"){ 
		  file >> result; 		
		}
	      }
	    }
	  }
	}
      }
    ///////////////////////////////////

      //// Get Ps2 Deadtime /////
      if (whatDoYouWant==2){
	while (file >> word){
	  if (word=="Pre-Scaled"){
	    file >> word;
	    if(word=="Ps2"){
	      file >> word >> word >> word;
	      if(word=="Dead"){
		file >> word >> word >> result;
	      }
	    }
	  }
	}
      }

    ///////////////////////////////////

      //// Get tracking eff /////
      if (whatDoYouWant==3){
	while (file >> word){
	  if (word=="E"){
	    file >> word;
	    if (word=="SING"){ 
	    // Get "FID     TRACK   EFFIC : "
	      file >> word >> word >> word >> word; 
	      file >> result;
	      }
	    }
	  }
	}

    ///////////////////////////////////

      //// Get tracking eff /////
      if (whatDoYouWant==4){
	while (file >> word){
	  if (word=="Ps2_factor"){
	    file >> word >> result;
	  }
	}
      }

    }
	  
  file.close();

  return result;
}
