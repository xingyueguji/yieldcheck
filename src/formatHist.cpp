void formatHist(TH1F* h,Int_t style=0,TString ytit="", TString xtit="", TString tit=""){
  h->SetTitleSize(.5);
  h->GetYaxis()->SetTitle(ytit);
  h->GetXaxis()->SetTitle(xtit);
  h->GetYaxis()->SetTitleSize(.045);
  h->GetXaxis()->SetTitleSize(.055);
  h->GetYaxis()->SetTitleOffset(.9);
  h->GetXaxis()->SetTitleOffset(.8);
  h->SetTitle(tit);
  h->SetLabelSize(.05,"x");
  h->SetLabelSize(.05,"y");

  if(style==0)
    {
  h->SetMarkerStyle(28);
  h->SetMarkerSize(.5);
  h->SetFillStyle(3009);
  h->SetMarkerColor(kMagenta); 
  h->SetFillColor(kMagenta);
  h->SetLineColor(kMagenta);
  h->SetLineWidth(1);
   }

  if(style==1)
    {
  h->SetMarkerStyle(25);
  h->SetMarkerSize(.5);
  h->SetFillStyle(3010);
  h->SetMarkerColor(kRed); 
  h->SetFillColor(kRed);
  h->SetLineColor(kRed);
  h->SetLineWidth(1);
   }

  if(style==2)
    {
  h->SetMarkerStyle(24);
  h->SetMarkerSize(.5);
  h->SetFillStyle(3018);
  h->SetMarkerColor(kBlue); 
  h->SetFillColor(kBlue);
  h->SetLineColor(kBlue);
  h->SetLineWidth(1);
   }

  if(style==4)
    {
  h->SetMarkerStyle(30);
  h->SetMarkerSize(.5);
  h->SetFillStyle(3010);
  h->SetMarkerColor(kGreen+3); 
  h->SetFillColor(kGreen+3);
  h->SetLineColor(kGreen+3);
  h->SetLineWidth(1);
   }

  if(style==5)
    {
  h->SetMarkerStyle(31);
  h->SetMarkerSize(.5);
  h->SetFillStyle(3144);
  h->SetMarkerColor(kBlack); 
  h->SetFillColor(kBlack);
  h->SetLineColor(kBlack);
  h->SetLineWidth(1);
   }

  if(style==3)
    {
  h->SetMarkerStyle(27);
  h->SetMarkerSize(.5);
  h->SetFillStyle(3002);
  h->SetMarkerColor(kBlack); 
  h->SetFillColor(kBlack);
  h->SetLineColor(kBlack);
  h->SetLineWidth(1);
   }


  return;
}
