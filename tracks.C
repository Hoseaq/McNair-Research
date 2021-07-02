#include <iostream>
//in root the file name must match the function name
void tracks()

{
  TCanvas c1("c1","");

  // --- open the file
  TFile* file = TFile::Open("quentin.root","read");

  // --- get the TProfile histograms from the file
  // <2> histogram.
  TProfile* c22 = (TProfile*)file->Get("nfvtxt_ac_fvtxc_tracks_c22");
  // <4> histogram.
  TProfile* c24 = (TProfile*)file->Get("nfvtxt_ac_fvtxc_tracks_c24");
  // <2>_{a|b} histogram
  TProfile* c22ab = (TProfile*)file->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c22");
  // <4>_{aa|bb} histogram
  TProfile* c24a = (TProfile*)file->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24a");
  // <4>_{ab|ab} histogram
  TProfile* c24b = (TProfile*)file->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24b");
  // <2>_{a|a} histogram
  TProfile* c22a = (TProfile*)file->Get("nfvtxt_ac_fvtxs_tracks_c22");
  // <2>_{b|b} histogramc
  TProfile* c22b = (TProfile*)file->Get("nfvtxt_ac_fvtxn_tracks_c22");

  // --- make TH1D histograms from the TProfiles to do mathematical operations on them

  TH1D* c22x = c22->ProjectionX("c22x");
  TH1D* c24x = c24->ProjectionX("c24x");

  TH1D* c22ax = c22a->ProjectionX("c22ax");
  TH1D* c22bx = c22b->ProjectionX("c22bx");
  TH1D* c22abx = c22ab->ProjectionX("c22abx");
  TH1D* c24ax  = c24a -> ProjectionX("c24ax");
  TH1D* c24bx = c24b ->ProjectionX("c24bx");

  // --- make clones for rebinning purposes prior to doing any math operations
  TH1D* c22x_rb1 = (TH1D*)c22x->Clone("c22x_rb1");
  TH1D* c24x_rb1 = (TH1D*)c24x->Clone("c24x_rb1");
  TH1D* c22x_rb2 = (TH1D*)c22x->Clone("c22x_rb2");
  TH1D* c24x_rb2 = (TH1D*)c24x->Clone("c24x_rb2");

  // --- math operations for full event cumulant
  //Retrieves specific files from local root file
  //TH1D histograms contain 1 double per bin
  //TH1D* creates a pointer to a histogram
  c22x -> Multiply(c22x);
  c22x -> Scale(2);
  c24x -> Add(c22x,-1);
  c24x -> Draw();
  c1.Print("Figures/c24x.png");
  //c2{4} histogram is now drawn



  // --- math operations for subevent cumulant ab|ab
  // --- add the math formulas here as a comment so you can verify you've done this correctly
  c22abx -> Multiply(c22abx);
  c22ax -> Multiply(c22bx);
  c22ax -> Add(c22abx, -1);
  c24bx -> Add(c22ax, -1);
  c24bx -> Draw();
  c1.Print("Figures/c24x_abab.png");
  //cn{4}ab|ab has been drawn



  // --- math operations for subevent cumulant aa|bb
  // --- add the math formulas here as a comment so you can verify you've done this correctly
  // --- be sure not to reuse histograms from other calculations, make more clones as needed
  c22abx -> Scale(2);
  c24ax -> Add(c22abx, -1);
  c24ax -> Draw();
  c1.Print("Figures/c24x_aabb.png");
  //cn{4}aa|bb histogram has been drawn

  //creation of single histogram


  THStack *hs = new THStack("hs", "");
  hs -> Add(c24ax);
  hs -> Add(c24bx);
  hs -> Add(c24x);
  hs -> Draw();
  hs -> GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hs -> GetYaxis()->SetTitle("c_{2}{4}");
  hs->SetMaximum(1.0e-4);
  hs->SetMinimum(-1.0e-4);
  hs->GetXaxis()->SetRangeUser(0,50);
  c1.Print("Figures/hs.png");

  //Rebinning of historgrams: seperate rebinning of <4> and <2> histograms

  int rebin = 2;

  c22x_rb1 -> Rebin(rebin);
  c22x_rb1 -> Scale(1.0/rebin);
  c24x_rb1 -> Rebin(rebin);
  c24x_rb1 -> Scale(1.0/rebin);
  c22x_rb1 -> Multiply(c22x_rb1);
  c22x_rb1 -> Scale(2);
  c24x_rb1 -> Add(c22x_rb1,-1);
  c24x_rb1 -> Draw();
  c1.Print("Figures/c24rb1.png");


  //Rebinned seperate  c2{4} histogram

  //Rebinning of histograms: merged
  c22x_rb2 -> Multiply(c22x_rb2);
  c22x_rb2 -> Scale(2);
  c24x_rb2 -> Add(c22x_rb2,-1);
  c24x_rb2 -> Rebin(rebin);
  c24x_rb2 -> Scale(1.0/rebin);
  c24x_rb2 -> Draw();
  c1.Print("Figures/c24rb2.png");

  // --- now drawing the different rebinnings together
  c24x->SetMarkerStyle(kOpenCircle);
  c24x->SetMarkerColor(kBlack);
  c24x->SetLineColor(kBlack);
  c24x_rb1->SetMarkerStyle(kOpenDiamond);
  c24x_rb1->SetMarkerColor(kBlue);
  c24x_rb1->SetLineColor(kBlue);
  c24x_rb2->SetMarkerStyle(kOpenCross);
  c24x_rb2->SetMarkerColor(kRed);
  c24x_rb2->SetLineColor(kRed);
  TH2D hdummy("hdummy","",1,0,50,1,-1e-4,1e-4);
  hdummy.Draw();
  hdummy.GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  hdummy.GetYaxis()->SetTitle("c_{2}{4}");
  c24x -> Draw("same ex0p");
  c24x_rb1 -> Draw("same ex0p");
  c24x_rb2 -> Draw("same ex0p");
  c1.Print("Figures/c24_rebin_comparison.png");

  // --- think like a physicist: take the ratio
  c24x_rb2->Divide(c24x_rb1);
  c24x_rb2->Draw();
  c24x_rb2->SetMaximum(2);
  c24x_rb2->SetMinimum(0);
  TLine line1(0,1,90,1);
  line1.Draw();
  c1.Print("Figures/c24_rebin_comparison_ratio.png");
  c24x_rb2->SetMaximum(1.1);
  c24x_rb2->SetMinimum(0.9);
  c1.Print("Figures/c24_rebin_comparison_ratio_zoom.png");

  return;

}
