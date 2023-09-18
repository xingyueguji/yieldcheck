#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

double getKinErr(string kine="h21deg2p7",double xbb=.22872){

  FILE *fp = fopen("src/globErr.txt","r");  

  Int_t ncols; 
  double result=0;
  double spec, ang, xb, pion,modErr, density, cer, boil, kin, csb, acc, rad, tot, live, qerr, boilp2p;
  char label[10];
  while (1) { 

    //    cout << "In while loop 1"<<endl;
    ncols = fscanf(fp,"%lf %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&spec,label,&xb,&pion,&density,&cer,&modErr,&kin,&csb,&acc,&rad,&live,&qerr,&boilp2p, &tot);
    if (ncols < 0) break;
    if(label==kine && (xb-xbb)<.001)result=kin;
  }

  return result;

}
