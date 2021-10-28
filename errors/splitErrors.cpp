#include "getP2p.cpp"
#include "getGlob.cpp"


//TGraph* getP2p(string tgt="h",string angle="25", string mom="3p5",string spec="shms", string what="boil",double marker=33, double col=1, string name="gr1"){
// if(what=="pt2pt")herr_d=(TH1F*)fd->Get("herr_pt2pt");
// if(what=="stat")herr_d=(TH1F*)fd->Get("herr_pt2pt");
// if(what=="boil")herr_d=(TH1F*)fd->Get("herr_boil");
// if(what=="live")herr_d=(TH1F*)fd->Get("herr_live");
// if(what=="track")herr_d=(TH1F*)fd->Get("herr_track");
// if(what=="trig")herr_d=(TH1F*)fd->Get("herr_trig");


void splitErrors(string tgt="h",string angle="21", string mom="3p5",string spec="shms", TCanvas *c1=new TCanvas()){
  float ang=getAngle(angle,spec);
  

  TGraph *g1=getP2p(tgt,angle,mom,spec,"pt2pt",33,1,"gpt2pt");
  TGraph *g2=getP2p(tgt,angle,mom,spec,"stat",33,2,"gstat");
  TGraph *g3=getP2p(tgt,angle,mom,spec,"boil",33,3,"gboil");
  //  TGraph *g4=getP2p(tgt,angle,mom,spec,"live",33,4,"glive");
  TGraph *g5=getP2p(tgt,angle,mom,spec,"track",33,2,"gtrack");
  TGraph *g6=getP2p(tgt,angle,mom,spec,"trig",33,6,"gtrig");

  TGraph *g7=getGlob(ang, spec, "pion", "g7",1,20);
  TGraph *g8=getGlob(ang, spec, "density", "g8",2,20);
  TGraph *g9=getGlob(ang, spec, "cer", "g9",3,20);
  TGraph *g10=getGlob(ang, spec, "boil", "g10",4,20);
  TGraph *g11=getGlob(ang, spec, "kin", "g11",2,20);
  TGraph *g12=getGlob(ang, spec, "csb", "g12",6,20);
  TGraph *g13=getGlob(ang, spec, "acc", "g13",7,20);
  TGraph *g14=getGlob(ang, spec, "rad", "g14",8,20);
  TGraph *g15=getGlob(ang, spec, "tot", "g15",9,20);
  TGraph *g4=getGlob(ang, spec, "live", "g4",4,20);


  g1->GetYaxis()->SetRangeUser(0,5);
  c1->cd(1);
  g2->Draw("sp");
  c1->cd(2);
  g8->Draw("sp");
  c1->cd(3);
  g1->Draw("sp");

  g3->Draw("sp");
  g5->Draw("sp");
  g6->Draw("sp");
  c1->cd(4);
  g4->Draw("sp");
  g7->Draw("sp");
  //  g8->Draw("sp");
  g9->Draw("sp");
  //  g10->Draw("sp");
  g11->Draw("sp");
  g12->Draw("sp");
  g13->Draw("sp");
  g14->Draw("sp");
  g15->Draw("sp");

  TPaveText *t1=new TPaveText(.4,.75,.9,.9,"NDC");
  TPaveText *t2=new TPaveText(.4,.75,.9,.9,"NDC");
  TPaveText *t3=new TPaveText(.4,.75,.9,.9,"NDC");
  TPaveText *t4=new TPaveText(.4,.75,.9,.9,"NDC");
  t1->AddText("Uncorrelated Point to Point");
  t2->AddText("Overall Relative Normalization");
  t3->AddText("Uncorrelated Point to Point");
  t4->AddText("Correlated Point to Point");
  TLegend *leg1=new TLegend(.13,.75,.4,.9);
  TLegend *leg2=new TLegend(.13,.75,.4,.9);
  TLegend *leg3=new TLegend(.13,.5,.3,.9);
  TLegend *leg4=new TLegend(.11,.1,.33,.9);
  //  leg->AddEntry(g1,"Total point to point","p");
  leg1->AddEntry(g2,"Statistical Error","p");
  leg3->AddEntry(g3,"Boiling (pt to pt)","p");
  leg4->AddEntry(g4,"Livetime","p");
  leg3->AddEntry(g5,"Tracking Eff","p");
  leg3->AddEntry(g6,"Trigger Eff","p");
  leg4->AddEntry(g7,"Pion Contamination","p");
  leg2->AddEntry(g8,"Target Density","p");
  leg4->AddEntry(g9,"Cerenkov Eff.","p");
  //  leg->AddEntry(g10,"Boiling Corr.","p");
  leg4->AddEntry(g11,"Kinematics","p");
  leg4->AddEntry(g12,"CSB Correction","p");
  leg4->AddEntry(g13,"Acceptance","p");
  leg4->AddEntry(g14,"Radiative Corr","p");
  leg4->AddEntry(g15,"Total Global (with targ. #rho)","p");
  c1->cd(1);
  t1->Draw("same");
  leg1->Draw("same");
  c1->cd(2);
  t2->Draw("same");
  leg2->Draw("same");
  c1->cd(3);
  t3->Draw("same");
  leg3->Draw("same");
  c1->cd(4);
  t4->Draw("same");
  leg4->Draw("same");

  return;
}
