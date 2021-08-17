void wtDeb(){
  TFile* f=new TFile("deb.root");
  TTree *tr=(TTree*)f->Get("re_weighted");
  Double_t yfp, xpfp, ypfp, w2, q2, delta, stop_id, born, rce;
  tr->SetBranchAddress("yfp_rw",&yfp);
  tr->SetBranchAddress("xpfp_rw",&xpfp);
  tr->SetBranchAddress("ypfp_rw",&ypfp);
  tr->SetBranchAddress("w2_rw",&w2);
  tr->SetBranchAddress("q2_rw",&q2);
  tr->SetBranchAddress("delta_rw",&delta);
  tr->SetBranchAddress("stop_id_rw",&stop_id);
  tr->SetBranchAddress("born_rw",&born);
  tr->SetBranchAddress("rce_rw",&rce);

  TH1F *delWt3=new TH1F("delWt3","Monte Carlo Weighted delta",32,-10.,22.);
  //  Double_t scale=2.15019e-05; 
  Double_t scale=2.13429e-05; 
  Int_t nev=tr->GetEntries();
  for(Int_t i=0; i<nev; i++)
    {
      tr->GetEntry(i);
      if(stop_id==0 && delta>-10 &&delta<22)
	{
	  if(abs(xpfp) < .1  && abs(ypfp) < .1 && abs(yfp) < 10. )
	    {
	      delWt3->Fill(delta,born/rce*scale);
	    }
	}
    }
  TCanvas *c1=new TCanvas();//c1->Divide(1,2);c1->cd(1);
  delWt3->Scale(1000.);// mC to uC
  delWt3->Draw();

  
//  f->Close();
  Float_t yfp2, xpfp2, ypfp2, w22, q22, delta2, stop_id2, born2, rce2,phsp;
  TFile *f2=new TFile("billCSB.root");
  TTree *tr2=(TTree*)f2->Get("tree");
  tr2->SetBranchAddress("ytarrec",&yfp2);
  tr2->SetBranchAddress("xptarrec",&xpfp2);
  tr2->SetBranchAddress("yptarrec",&ypfp2);
  tr2->SetBranchAddress("w2",&w22);
  tr2->SetBranchAddress("q2",&q22);
  tr2->SetBranchAddress("delrec",&delta2);
  tr2->SetBranchAddress("fail_id",&stop_id2);
  tr2->SetBranchAddress("born",&born2);
  tr2->SetBranchAddress("rci",&rce2);
  tr2->SetBranchAddress("phaseSpaceCorr",&phsp);

  TH1F *delWt2=new TH1F("delWt2","Monte Carlo Weighted delta",60,-30.,30.);
  //  scale=4.935536e-03; 
  scale=0.0213428;
  nev=tr2->GetEntries();
  Int_t acc=0;
  for(Int_t i=0; i<nev; i++)
    {
      tr2->GetEntry(i);
      if(stop_id2==0 && delta2>-10 &&delta2<22)
	{
	  if(abs(xpfp2) < .1  && abs(ypfp2) < .1 && abs(yfp2) < 10. )
	    {
	      	            delWt2->Fill(delta2,born2/rce2*phsp*scale);
	      //	            delWt2->Fill(delta2,born2/rce2*scale);
		    acc++;
	    }
	}
    }

  delWt3->SetLineColor(kRed);//Deb
  delWt2->SetLineColor(kGreen+3);//Bill
  delWt2->Draw("same");

  // Draw histogram that is weighted in the root file
  //Should be the same as delWt2

  f2->Get("delWt")->Draw("same");
  //  */
  cout <<endl <<endl<<acc<<endl<<endl;

  TLegend *leg=new TLegend(.15,.15,.4,.4);
  leg->AddEntry("delWt3","Deb (tree)","l");
  leg->AddEntry("delWt2","Bill (tree)","l");
  leg->AddEntry("delWt","Bill (histo)","l");
  leg->Draw("same");

  return;
}
