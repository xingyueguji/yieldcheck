//#include "readReport.cpp"

//double getCharge(char const *target="h", char const *angle="21", char const *pcent="3p3"){
double getCharge(string target="h", string angle="21", string pcent="3p3"){
  double totalCharge=0;
  FILE *fp = fopen("src/allShmsRuns.txt","r");
  char  mom[10], tgt[10], theta[10], ebeam[10], bcm[10], ps2[10], ps3[10];
  int ncols=0;
  int run;
  ncols = fscanf(fp,"%s %s %s %s %s %s %s %s",mom, mom, tgt, theta, ebeam, bcm, ps2, ps3);
  while(1){
    ncols = fscanf(fp,"%d %s %s %s %s %s %s %s",&run, mom, tgt, theta, ebeam, bcm, ps2, ps3);
    //    cout << "looping ncols="<<ncols<<endl;
    if(ncols<=0)break;
    //    cout << run <<"\t"<< mom <<"\t"<< tgt <<"\t"<< theta << endl;
    if(strncmp(tgt,"12.01",5)==0)strcpy(tgt,"c");
    if(strncmp(tgt,"26.98",5)==0)strcpy(tgt,"al");
    if(strncmp(tgt,"1.01",4)==0)strcpy(tgt,"h");
    if(strncmp(tgt,"2.01",4)==0)strcpy(tgt,"d");
    if(strncmp(theta,"21.035",6)==0)strcpy(theta,"21");
    if(strncmp(theta,"38.975",6)==0)strcpy(theta,"39");
    if(strncmp(theta,"32.975",6)==0)strcpy(theta,"33");
    if(strncmp(theta,"28.99",6)==0)strcpy(theta,"29");
    if(strncmp(theta,"24.98",6)==0)strcpy(theta,"25");
    if(strncmp(mom,"5.013",4)==0)strcpy(mom,"5p1");
    if(strncmp(mom,"3.932",4)==0)strcpy(mom,"4p0");
    if(strncmp(mom,"3.244",4)==0)strcpy(mom,"3p3");
    if(strncmp(mom,"2.654",4)==0)strcpy(mom,"2p7");
    if(strncmp(mom,"2.458",4)==0)strcpy(mom,"2p5");
    if(strncmp(mom,"1.966",4)==0)strcpy(mom,"2p0");
    if(strncmp(mom,"1.769",4)==0)strcpy(mom,"1p8");
    if(strncmp(mom,"1.573",4)==0)strcpy(mom,"1p6");
    if(strncmp(mom,"1.278",4)==0)strcpy(mom,"1p3");
    if(strncmp(mom,"3.146",4)==0)strcpy(mom,"3p2");
    if(strncmp(mom,"2.556",4)==0)strcpy(mom,"2p6");
    if(strncmp(mom,"2.064",4)==0)strcpy(mom,"2p1");
    if(strncmp(mom,"1.671",4)==0)strcpy(mom,"1p7");
    if(strncmp(mom,"2.359",4)==0)strcpy(mom,"2p4");
    if(strncmp(mom,"2.949",4)==0)strcpy(mom,"3p0");
    if(strncmp(mom,"3.637",4)==0)strcpy(mom,"3p7");
    if(strncmp(mom,"4.325",4)==0)strcpy(mom,"4p4");
    if(strncmp(mom,"3.441",4)==0)strcpy(mom,"3p5");

    if(strncmp(theta,angle.c_str(),2)==0 && strncmp(tgt,target.c_str(),1)==0&& strncmp(ps2,"-1",1)!=0){
      if(strncmp(mom,pcent.c_str(),3)==0 || strncmp("all",pcent.c_str(),3)==0){
	//	cout << run <<"\t"<< readReport(run,"BCM4C charge") << endl;
	totalCharge += readReport(run,"BCM4C charge");
      }
    }
  }
  return totalCharge;
  }
