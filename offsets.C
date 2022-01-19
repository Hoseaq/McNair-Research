#include <iostream>

//in root the file name must match the function name
void offsets()

{
  // --- open the file
  TFile* file = TFile::Open("quentin.root","read");

  TProfile* c22 = (TProfile*)file->Get("nfvtxt_ac_fvtxc_tracks_c22");

  // KEY: TProfile	nfvtxt_ac_fvtxc_tracks_cos21;1
  // KEY: TProfile	nfvtxt_ac_fvtxc_tracks_sin21;1
  // KEY: TProfile	nfvtxt_ac_fvtxc_tracks_cossum22;1
  // KEY: TProfile	nfvtxt_ac_fvtxc_tracks_sinsum22;1
  // KEY: TProfile	nfvtxt_ac_fvtxc_tracks_cos23;1
  // KEY: TProfile	nfvtxt_ac_fvtxc_tracks_sin23;1
  // KEY: TProfile	nfvtxt_ac_fvtxs_tracks_cos21;1
  // KEY: TProfile	nfvtxt_ac_fvtxs_tracks_sin21;1
  // KEY: TProfile	nfvtxt_ac_fvtxs_tracks_cossum22;1
  // KEY: TProfile	nfvtxt_ac_fvtxs_tracks_sinsum22;1
  // KEY: TProfile	nfvtxt_ac_fvtxs_tracks_cos23;1
  // KEY: TProfile	nfvtxt_ac_fvtxs_tracks_sin23;1
  // KEY: TProfile	nfvtxt_ac_fvtxn_tracks_cos21;1
  // KEY: TProfile	nfvtxt_ac_fvtxn_tracks_sin21;1
  // KEY: TProfile	nfvtxt_ac_fvtxn_tracks_cossum22;1
  // KEY: TProfile	nfvtxt_ac_fvtxn_tracks_sinsum22;1
  // KEY: TProfile	nfvtxt_ac_fvtxn_tracks_cos23;1
  // KEY: TProfile	nfvtxt_ac_fvtxn_tracks_sin23;1

}
