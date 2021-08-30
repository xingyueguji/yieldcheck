#include "getP2p.cpp"
#include "getGlob.cpp"


//TGraph* getP2p(string tgt="h",string angle="25", string mom="3p5",string spec="shms", string what="boil",double marker=33, double col=1, string name="gr1"){
// if(what=="pt2pt")herr_d=(TH1F*)fd->Get("herr_pt2pt");
// if(what=="stat")herr_d=(TH1F*)fd->Get("herr_pt2pt");
// if(what=="boil")herr_d=(TH1F*)fd->Get("herr_boil");
// if(what=="live")herr_d=(TH1F*)fd->Get("herr_live");
// if(what=="track")herr_d=(TH1F*)fd->Get("herr_track");
// if(what=="trig")herr_d=(TH1F*)fd->Get("herr_trig");


void errors(string tgt="h",string angle="21", string mom="3p5",string spec="shms"){
  float ang=getAngle(angle,spec);
  

  TGraph *g1=getP2p(tgt,angle,mom,spec,"pt2pt",33,1,"gpt2pt");
  TGraph *g2=getP2p(tgt,angle,mom,spec,"stat",33,2,"gstat");
  TGraph *g3=getP2p(tgt,angle,mom,spec,"boil",33,3,"gboil");
  TGraph *g4=getP2p(tgt,angle,mom,spec,"live",33,4,"glive");
  TGraph *g5=getP2p(tgt,angle,mom,spec,"track",33,5,"gtrack");
  TGraph *g6=getP2p(tgt,angle,mom,spec,"trig",33,6,"gtrig");

  TGraph *g7=getGlob(ang, spec, "pion", "g7",1,20);
  TGraph *g8=getGlob(ang, spec, "density", "g8",2,20);
  TGraph *g9=getGlob(ang, spec, "cer", "g9",3,20);
  TGraph *g10=getGlob(ang, spec, "boil", "g10",4,20);
  TGraph *g11=getGlob(ang, spec, "kin", "g11",5,20);
  TGraph *g12=getGlob(ang, spec, "csb", "g12",6,20);
  TGraph *g13=getGlob(ang, spec, "acc", "g13",7,20);
  TGraph *g14=getGlob(ang, spec, "rad", "g14",8,20);
  TGraph *g15=getGlob(ang, spec, "tot", "g15",9,20);


  g1->GetYaxis()->SetRangeUser(0,5);

  g1->Draw("sp");
  g2->Draw("sp");
  g3->Draw("sp");
  g4->Draw("sp");
  g5->Draw("sp");
  g6->Draw("sp");
  g7->Draw("sp");
  g8->Draw("sp");
  g9->Draw("sp");
  g10->Draw("sp");
  g11->Draw("sp");
  g12->Draw("sp");
  g13->Draw("sp");
  g14->Draw("sp");
  g15->Draw("sp");


  TLegend *leg=new TLegend(.13,.1,.3,.9);
  leg->AddEntry(g1,"Total point to point","p");
  leg->AddEntry(g2,"Statistical Error","p");
  leg->AddEntry(g3,"Boiling (pt to pt)","p");
  leg->AddEntry(g4,"Livetime","p");
  leg->AddEntry(g5,"Tracking Eff","p");
  leg->AddEntry(g6,"Trigger Eff","p");
  leg->AddEntry(g7,"Pion Contamination","p");
  leg->AddEntry(g8,"Target Density","p");
  leg->AddEntry(g9,"Cerenkov Eff.","p");
  leg->AddEntry(g10,"Boiling Corr.","p");
  leg->AddEntry(g11,"Kinematics","p");
  leg->AddEntry(g12,"CSB Correction","p");
  leg->AddEntry(g13,"Acceptance","p");
  leg->AddEntry(g14,"Radiative Corr","p");
  leg->AddEntry(g15,"Total Global","p");

  leg->Draw("same");

  return;
}
