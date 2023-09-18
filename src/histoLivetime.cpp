// remember to remove first row with column labels
double histoLivetim(Double_t run=2550,TString what="tlt"){

  FILE *fp = fopen("src/livetimes/livetimes_April2021.txt","r");  
  Double_t s1x,rn, clt, clterr, elt, elterr, tlt, tlterr;
  Int_t ncols; 
  double_t result=-99;

  TH1D *h=new TH1D("h","h",100,.05,.05);
  while (1) { 
    ncols = fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf",&rn, &s1x, &clt, &clterr,&elt, &elterr,&tlt, &tlterr);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if( (rn>2484 && rn < 3102) || (rn>1565 && rn < 1862) )
h->Fill(tlterr);
  }
  h->Draw();
  fclose (fp);

  return 3 ;
}

