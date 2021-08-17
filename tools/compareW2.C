void compareW2()
{

TCanvas *c1=new TCanvas();
c1->Divide(2,2);

c1->cd(1);
hw2d->GetXaxis()->SetRangeUser(0,6);
hw2d->Draw();
hw2d_calc->SetLineColor(kRed);
hw2d_calc->Draw("same");
c1->cd(3);
TH1D * w2r=(TH1D*)hw2d->Clone();
w2r->Divide(hw2d_calc);
w2r->Draw();

c1->cd(2);
hq2d->GetXaxis()->SetRangeUser(5,10);
hq2d->Draw();
hq2d_calc->SetLineColor(kRed);
hq2d_calc->Draw("same");
c1->cd(4);
TH1D * q2r=(TH1D*)hq2d->Clone();
q2r->Divide(hq2d_calc);
q2r->Draw();

}
