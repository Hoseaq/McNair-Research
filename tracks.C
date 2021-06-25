#include <iostream>
//in root the file name must match the function name
void tracks()

{
  TCanvas c1("c1","");
  TFile* file = TFile::Open("quentin.root","read");
  //opens local root file
  TProfile* c22 = (TProfile*)file->Get("nfvtxt_ac_fvtxc_tracks_c22");
  TProfile* c24 = (TProfile*)file->Get("nfvtxt_ac_fvtxc_tracks_c24");
  TProfile* c22ab = (TProfile*)file->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c22");
  TProfile* c24a = (TProfile*)file->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24a");
  TProfile* c24b = (TProfile*)file->Get("nfvtxt_ac_fvtxsfvtxn_tracks_c24b");
  TProfile* c22a = (TProfile*)file->Get("nfvtxt_ac_fvtxs_tracks_c22");
  TProfile* c22b = (TProfile*)file->Get("nfvtxt_ac_fvtxn_tracks_c22");

  //Retrieves specific files from local root file
  //TH1D histograms contain 1 double per bin
  //TH1D* creates a pointer to a histogram
  TH1D* c22x = c22->ProjectionX("c22x");
  TH1D* c24x = c24->ProjectionX("c24X");
  c22x -> Multiply(c22x);
  c22x -> Scale(2);
  c24x -> Add(c22x,-1);
  c24x -> Draw();
  c1.Print("c24x.png");
  //c2{4} histogram is now drawn

  // creation of cn{4} ab|ab histogram
  TH1D* c24bx = c24b ->ProjectionX("c24bx");
  TH1D* c22ax = c22a->ProjectionX("c22ax");
  TH1D* c22bx = c22b->ProjectionX("c22bx");
  if ( c22ab == NULL )
    {
      cout << "cannot find c22ab" <<  endl;
      return;
    }

  TH1D* c22abx = c22ab->ProjectionX("c22abx");

  c22abx -> Multiply(c22abx);
  c22ax -> Multiply(c22bx);
  c22ax -> Add(c22abx, -1);
  c24bx -> Add(c22ax, -1);
  c24bx -> Draw();
  c1.Print("c24bx.png");
  //cn{4}ab|ab has been drawn


  //Creation of cn{4}aa|bb histogram
  TH1D* c24ax  = c24a -> ProjectionX("c24ax");
  c22abx -> Scale(2);
  c24ax -> Add(c22abx, -1);
  c24ax -> Draw();
  c1.Print("c24ax.png");
  //cn{4}aa|bb histogram has been drawn

  //creation of single histogram

  THStack *hs = new THStack("hs", "Superimposed histograms");
  // hs -> GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  //hs -> GetYaxis()->SetTitle("c_{2}{4}");
  hs -> Add(c24ax);
  hs -> Add(c24bx);
  hs -> Add(c24x);
  //  hs -> GetXaxis()->SetTitle("N_{tracks}^{FVTX}");
  //  hs -> GetYaxis()->SetTitle("c_{2}{4}");
  hs -> Draw();
  hs ->GetXaxis()->SetTitle("N_{tracks}{FVTX}");
  hs ->GetYaxis()->SetTitle("c_{2}{4}");
  c1.Print("hs.png");

  return;
}
