void wtDebCSB(){
  TFile* f=new TFile("debCsb.root");
  TTree *tr=(TTree*)f->Get("MC");
  Double_t delta, wt;
  tr->SetBranchAddress("delta_MC",&delta);
  tr->SetBranchAddress("delta_MC_w_csb",&wt);

  TH1F *delWt3=new TH1F("delWt3","Monte Carlo Weighted delta",60,-30.,30.);
  //  Double_t scale=2.15019e-05; 
  Double_t scale=2.13429e-05; 
  Int_t nev=tr->GetEntries();
  for(Int_t i=0; i<nev; i++)
    {
      tr->GetEntry(i);
	    {
	      delWt3->Fill(delta,wt);
	    }
    }
   
  TCanvas *c1=new TCanvas();//c1->Divide(1,2);c1->cd(1);
  c1->Divide(1,2);
  c1->cd(1);
  delWt3->Draw();

  
//  f->Close();
  TFile *f2=new TFile("billCSB.root");
  delWt3->SetLineColor(kRed);//Deb
  TH1F * hbill=(TH1F*)f2->Get("delWt");
  //  */

  c1->cd(2);
  TH1F *hr=(TH1F*)delWt3->Clone();
  hr->Divide(hbill);
  hr->SetName("Deb/Bill");
  hr->GetYaxis()->SetRangeUser(1.,1.0015);
  hr->Draw();
  TLegend *leg=new TLegend(.15,.15,.4,.4);
  leg->AddEntry(delWt3,"Deb ","l");
  leg->AddEntry(hbill,"Bill ","l");
  leg->Draw("same");

  return;
}
