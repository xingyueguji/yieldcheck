#include "../src/getAngle.cpp"
#include "../src/getMom.cpp"

TGraph* getP2p(string tgt="h",string angle="25", string mom="3p5",string spec="shms", string what="boil",double marker=33, double col=1, string name="gr1"){

  string kinh="h"+angle+"deg"+mom; 
  string kind="d"+angle+"deg"+mom; 

 TFile *fd=new TFile(Form("../dataYieldOut/pass36/%s_dataYield_%s.root",spec.c_str(),kind.c_str()));
 TH1F *hdd_d=(TH1F*)fd->Get("hdd");
 TH1F* herr_d;
 if(what=="pt2pt")herr_d=(TH1F*)fd->Get("herr_pt2pt");
 if(what=="stat")herr_d=(TH1F*)fd->Get("herr_pt2pt");
 if(what=="boil")herr_d=(TH1F*)fd->Get("herr_boil");
 if(what=="live")herr_d=(TH1F*)fd->Get("herr_live");
 if(what=="track")herr_d=(TH1F*)fd->Get("herr_track");
 if(what=="trig")herr_d=(TH1F*)fd->Get("herr_trig");
 herr_d->SetName("herr_d");
 herr_d->Divide(hdd_d);

 // double test;
 // cin >> test;

 TFile *fh=new TFile(Form("../dataYieldOut/pass36/%s_dataYield_%s.root",spec.c_str(),kinh.c_str()));
 TH1F *hdd_h=(TH1F*)fh->Get("hdd");
 TH1F* herr_h;
 if(what=="pt2pt")herr_h=(TH1F*)fh->Get("herr_pt2pt");
 if(what=="stat")herr_h=(TH1F*)fh->Get("herr_pt2pt");
 if(what=="boil")herr_h=(TH1F*)fh->Get("herr_boil");
 if(what=="live")herr_h=(TH1F*)fh->Get("herr_live");
 if(what=="track")herr_h=(TH1F*)fh->Get("herr_track");
 if(what=="trig")herr_h=(TH1F*)fh->Get("herr_trig");
 herr_h->Divide(hdd_h);
 herr_h->SetName("herr_h");
 Double_t pc=getMom(kinh,spec);
 Double_t pOffset=0.;
 Double_t ebeam=10.602;
 Double_t thetac=getAngle(angle,"shms");
 Double_t hsec=pc*(1+pOffset);
 cout << "The central momentum is "<<hsec<<endl;
 if(spec=="hms"&&hsec<5.5){
   double offset = -0.000276*pow(hsec,3) + 0.002585*pow(hsec,2) - 0.008697*hsec+1.0064;
   hsec=hsec*offset;
 }
 cout << "The corrected central momentum is "<<hsec<<endl;


 vector <double> x;
 vector <double> y;
 double ep, delta;

 int nbins=hdd_h->GetNbinsX();

 for(int i=0;i<nbins;i++){
   delta=hdd_h->GetBinCenter(i);

   double stat_err_h=hdd_h->GetBinError(i)/hdd_h->GetBinContent(i);
   double stat_err_d=hdd_d->GetBinError(i)/hdd_d->GetBinContent(i);
   if(what=="stat")cout << delta <<"\t"<< stat_err_h<<"\t"<< stat_err_d<<endl;
   double total_stat_err=sqrt(pow(stat_err_h,2)+pow(stat_err_d,2));

   ep=(1+delta/100)*hsec;
   Double_t sin2 = sin(thetac/2/180*TMath::Pi())*sin(thetac/2/180*TMath::Pi());
   Double_t nu= ebeam-ep;
   Double_t q2 = 4.*ep*ebeam*sin2;
   Float_t mp = .9382723;
   Double_t xb=q2/2./mp/nu;
   Double_t w2= mp*mp + 2.*mp*nu-q2;

   double hyd_err=herr_h->GetBinContent(i);
   double deut_err=herr_d->GetBinContent(i);
   double tot_err=sqrt(hyd_err*hyd_err+deut_err*deut_err);

   cout << what << "\t"<< hyd_err << "\t"<< deut_err<< "\t"<< xb << endl;

   if(!TMath::IsNaN(total_stat_err)&&!TMath::IsNaN(tot_err)&&total_stat_err!=0&&tot_err!=0){
     x.push_back(xb);
     if(what=="stat"){
       y.push_back(total_stat_err*100);
       
   } 
     else 
       y.push_back(tot_err*100);
   }
 }
 int pts=x.size();
 TGraph *g=new TGraph(pts,&x[0],&y[0]);
 g->SetMarkerStyle(marker);
 g->SetMarkerColor(col);
 g->SetName(name.c_str());
 return g;
}
