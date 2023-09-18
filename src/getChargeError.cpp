// goes through run list and counts the number of runs that match 
// kinemtaic given in argument.  Then calculates the error on the 
// charge as 0.5%/sqrt(#runs)

double getChargeError(char const *angle="21", char const *target="d", char const *pcent="5p1", char const *spec="hms"){

  double cntr=0;
  FILE *fp;
  if(strncmp(spec,"shms",3)==0)fp = fopen("./makeRunList/allShmsRuns.txt","r");
  if(strncmp(spec,"hms",3)==0)fp = fopen("./makeRunList/allHmsRuns.txt","r");
  if (fp == NULL){
    cout << "Error in opening the run text file" << endl;
  }
  char  mom[10], tgt[10], theta[10], ebeam[10], bcm[10], ps2[10], ps3[10];
  int ncols=0;
  int run;
  ncols = fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",mom, mom, tgt, theta, ebeam, bcm, ps2, ps3);
  //cout << ncols << endl;
  //cout << ps3 << endl;
  while(1){
    ncols = fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s",&run, mom, tgt, theta, ebeam, bcm, ps2, ps3);
    //cout << run << endl;
        cout << "looping ncols="<<ncols<<endl;
    if(ncols<=0)break;
    //    cout << run <<"\t"<< mom <<"\t"<< tgt <<"\t"<< theta << endl;
    if(strncmp(tgt,"12.01",5)==0)strcpy(tgt,"c");
    if(strncmp(tgt,"26.98",5)==0)strcpy(tgt,"al");
    if(strncmp(tgt,"1.01",4)==0)strcpy(tgt,"h");
    if(strncmp(tgt,"2.01",4)==0)strcpy(tgt,"d");
    if(strncmp(theta,"21.035",6)==0)strcpy(theta,"21");
    if(strncmp(theta,"-20.995",6)==0)strcpy(theta,"21");
    if(strncmp(theta,"38.975",6)==0)strcpy(theta,"39");
    if(strncmp(theta,"32.975",6)==0)strcpy(theta,"33");
    if(strncmp(theta,"28.99",6)==0)strcpy(theta,"29");
    if(strncmp(theta,"24.98",6)==0)strcpy(theta,"25");
    if(strncmp(theta,"-58.98",6)==0)strcpy(theta,"59");
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
    if(strncmp(mom,"5.7",3)==0)strcpy(mom,"5p7");
    if(strncmp(mom,"5.1",3)==0)strcpy(mom,"5p1");
    if(strncmp(mom,"4.5",3)==0)strcpy(mom,"4p5");
    if(strncmp(mom,"4p5",3)!=0 && strncmp(mom,"4p4",3)!=0&&strncmp(mom,"4",1)==0)strcpy(mom,"4p0");
    if(strncmp(mom,"3.3",3)==0)strcpy(mom,"3p3");
    if(strncmp(mom,"1.5",3)==0)strcpy(mom,"1p5");
    if(strncmp(mom,"1.35",3)==0)strcpy(mom,"1p4");
    if(strncmp(mom,"1.18",3)==0)strcpy(mom,"1p2");
    if(strncmp(mom,"1.05",3)==0)strcpy(mom,"1p1");
    //positron runs hms
    if(strncmp(mom,"1.2",3)==0)strcpy(mom,"1p2");


    if(strncmp(theta,angle,2)==0 && strncmp(tgt,target,1)==0&& strncmp(ps2,"-1",1)!=0){
      if(strncmp(mom,pcent,3)==0 || strncmp("all",pcent,3)==0){
	string fname=Form("%s_%s%sdeg%s_%d",spec,tgt,angle,mom,run);
	//	cout << run <<"\t"<< fname << endl; 
	cntr++;
      }
    }
  }
  cout << "There were "<<cntr<<" runs for this kinematic"<<endl;
  double error=0.005/sqrt(cntr);
    cout << "The error on the charge is "<<error*100<<"%"<<endl;
  return error;
  }
