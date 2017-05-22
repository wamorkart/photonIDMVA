#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TObjArray.h"
#include "THStack.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TMath.h"
#include "TCut.h"
#include "TPaletteAxis.h"

#include "TMVA/Reader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>


void saveHistoToFile(){

  // string fileName_EB_wRho = "mvares_Hgg_phoId_80X_EB_wRhoRew.root";
  string fileName_EB = "mvares_Hgg_phoId_80X_EB.root";

  // string fileName_EE_wRho = "mvares_Hgg_phoId_80X_EE_corrIso_wRhoRew.root";
  string fileName_EE = "mvares_Hgg_phoId_80X_EE.root";

  //EB , no mvares cut

  TFile *file_EB = new TFile(fileName_EB.c_str());

  TTree *t_EB_s = (TTree*)file_EB->Get("promptPhotons");
  TTree *t_EB_b = (TTree*)file_EB->Get("fakePhotons");

  // TFile *file_EB_wRho = new TFile(fileName_EB_wRho.c_str());

  // TTree *t_EB_wRho_s = (TTree*)file_EB_wRho->Get("promptPhotons");
  // TTree *t_EB_wRho_b = (TTree*)file_EB_wRho->Get("fakePhotons");

  TH1F * h_pt_EB_s = new TH1F ("h_pt_EB_s","h_pt_EB_s",25,0,250);
  TH1F * h_pt_EB_b = new TH1F ("h_pt_EB_b","h_pt_EB_b",25,0,250);

  TH1F * h_nVtx_EB_s = new TH1F ("h_nVtx_EB_s","h_nVtx_EB_s",40,0,40);
  TH1F * h_nVtx_EB_b = new TH1F ("h_nVtx_EB_b","h_nVtx_EB_b",40,0,40);

  // TH1F * h_pt_EB_wRho_s = new TH1F ("h_pt_EB_wRho_s","h_pt_EB_wRho_s",25,0,250);
  // TH1F * h_pt_EB_wRho_b = new TH1F ("h_pt_EB_wRho_b","h_pt_EB_wRho_b",25,0,250);

  // TH1F * h_nVtx_EB_wRho_s = new TH1F ("h_nVtx_EB_wRho_s","h_nVtx_EB_wRho_s",40,0,40);
  // TH1F * h_nVtx_EB_wRho_b = new TH1F ("h_nVtx_EB_wRho_b","h_nVtx_EB_wRho_b",40,0,40);

  TCut EB_s ="mvares>-2 && abs(scEta)<1.5";
  TCut EB_b  = "mvares>-2 && abs(scEta)<1.5";

  // TCut EB_wRho_s ="(mvares>-2 && abs(scEta)<1.5)*rhoRew";
  // TCut EB_wRho_b  = "(mvares>-2 && abs(scEta)<1.5)*rhoRew";

  h_pt_EB_s->Sumw2();
  h_pt_EB_b->Sumw2();

  h_nVtx_EB_s->Sumw2();
  h_nVtx_EB_b->Sumw2();

  // h_pt_EB_wRho_s->Sumw2();
  // h_pt_EB_wRho_b->Sumw2();

  // h_nVtx_EB_wRho_s->Sumw2();
  // h_nVtx_EB_wRho_b->Sumw2();


  t_EB_s->Draw("pt>>h_pt_EB_s",EB_s,"goff");
  t_EB_b->Draw("pt>>h_pt_EB_b",EB_b,"goff");

  t_EB_s->Draw("nvtx>>h_nVtx_EB_s",EB_s,"goff");
  t_EB_b->Draw("nvtx>>h_nVtx_EB_b",EB_b,"goff");

  // t_EB_wRho_s->Draw("pt>>h_pt_EB_wRho_s",EB_wRho_s,"goff");
  // t_EB_wRho_b->Draw("pt>>h_pt_EB_wRho_b",EB_wRho_b,"goff");

  // t_EB_wRho_s->Draw("nvtx>>h_nVtx_EB_wRho_s",EB_wRho_s,"goff");
  // t_EB_wRho_b->Draw("nvtx>>h_nVtx_EB_wRho_b",EB_wRho_b,"goff");

  //EB, mvares cut

  TH1F * h_pt_EB_Cut_s = new TH1F ("h_pt_EB_Cut_s","h_pt_EB_Cut_s",25,0,250);
  TH1F * h_pt_EB_Cut_b = new TH1F ("h_pt_EB_Cut_b","h_pt_EB_Cut_b",25,0,250);

  TH1F * h_nVtx_EB_Cut_s = new TH1F ("h_nVtx_EB_Cut_s","h_nVtx_EB_Cut_s",40,0,40);
  TH1F * h_nVtx_EB_Cut_b = new TH1F ("h_nVtx_EB_Cut_b","h_nVtx_EB_Cut_b",40,0,40);

  // TH1F * h_pt_EB_wRho_Cut_s = new TH1F ("h_pt_EB_wRho_Cut_s","h_pt_EB_wRho_Cut_s",25,0,250);
  // TH1F * h_pt_EB_wRho_Cut_b = new TH1F ("h_pt_EB_wRho_Cut_b","h_pt_EB_wRho_Cut_b",25,0,250);

  // TH1F * h_nVtx_EB_wRho_Cut_s = new TH1F ("h_nVtx_EB_wRho_Cut_s","h_nVtx_EB_wRho_Cut_s",40,0,40);
  // TH1F * h_nVtx_EB_wRho_Cut_b = new TH1F ("h_nVtx_EB_wRho_Cut_b","h_nVtx_EB_wRho_Cut_b",40,0,40);

  //WP 95%
  TCut EB_Cut_s ="mvares>0.1 && abs(scEta)<1.5 && pt > 18";
  TCut EB_Cut_b  = "mvares>0.1 && abs(scEta)<1.5 && pt > 18";
  
  //WP 95%:
  //TCut EB_wRho_Cut_s ="(mvares>0.1 && abs(scEta)<1.5 && pt > 18)*rhoRew";
  //TCut EB_wRho_Cut_b  = "(mvares>0.1 && abs(scEta)<1.5 && pt > 18)*rhoRew";

  h_pt_EB_Cut_s->Sumw2();
  h_pt_EB_Cut_b->Sumw2();

  h_nVtx_EB_Cut_s->Sumw2();
  h_nVtx_EB_Cut_b->Sumw2();

  // h_pt_EB_wRho_Cut_s->Sumw2();
  // h_pt_EB_wRho_Cut_b->Sumw2();

  // h_nVtx_EB_wRho_Cut_s->Sumw2();
  // h_nVtx_EB_wRho_Cut_b->Sumw2();


  t_EB_s->Draw("pt>>h_pt_EB_Cut_s",EB_Cut_s,"goff");
  t_EB_b->Draw("pt>>h_pt_EB_Cut_b",EB_Cut_b,"goff");

  t_EB_s->Draw("nvtx>>h_nVtx_EB_Cut_s",EB_Cut_s,"goff");
  t_EB_b->Draw("nvtx>>h_nVtx_EB_Cut_b",EB_Cut_b,"goff");

  // t_EB_wRho_s->Draw("pt>>h_pt_EB_wRho_Cut_s",EB_wRho_Cut_s,"goff");
  // t_EB_wRho_b->Draw("pt>>h_pt_EB_wRho_Cut_b",EB_wRho_Cut_b,"goff");

  // t_EB_wRho_s->Draw("nvtx>>h_nVtx_EB_wRho_Cut_s",EB_wRho_Cut_s,"goff");
  // t_EB_wRho_b->Draw("nvtx>>h_nVtx_EB_wRho_Cut_b",EB_wRho_Cut_b,"goff");


  //EE, no mvares cut

  
  TFile *file_EE_noCut = new TFile(fileName_EE.c_str());
  TTree *t_EE_noCut_s = (TTree*)file_EE_noCut->Get("promptPhotons");
  TTree *t_EE_noCut_b = (TTree*)file_EE_noCut->Get("fakePhotons");

  // TFile *file_EE_wRho = new TFile(fileName_EE_wRho.c_str());
  // TTree *t_EE_wRho_s = (TTree*)file_EE_wRho->Get("promptPhotons");
  // TTree *t_EE_wRho_b = (TTree*)file_EE_wRho->Get("fakePhotons");


  TH1F * h_pt_EE_noCut_s = new TH1F ("h_pt_EE_noCut_s","h_pt_EE_noCut_s",25,0,250);
  TH1F * h_pt_EE_noCut_b = new TH1F ("h_pt_EE_noCut_b","h_pt_EE_noCut_b",25,0,250);

  TH1F * h_nVtx_EE_noCut_s = new TH1F ("h_nVtx_EE_noCut_s","h_nVtx_EE_noCut_s",40,0,40);
  TH1F * h_nVtx_EE_noCut_b = new TH1F ("h_nVtx_EE_noCut_b","h_nVtx_EE_noCut_b",40,0,40);


  // TH1F * h_pt_EE_wRho_noCut_s = new TH1F ("h_pt_EE_wRho_noCut_s","h_pt_EE_wRho_noCut_s",25,0,250);
  // TH1F * h_pt_EE_wRho_noCut_b = new TH1F ("h_pt_EE_wRho_noCut_b","h_pt_EE_wRho_noCut_b",25,0,250);

  // TH1F * h_nVtx_EE_wRho_noCut_s = new TH1F ("h_nVtx_EE_wRho_noCut_s","h_nVtx_EE_wRho_noCut_s",40,0,40);
  // TH1F * h_nVtx_EE_wRho_noCut_b = new TH1F ("h_nVtx_EE_wRho_noCut_b","h_nVtx_EE_wRho_noCut_b",40,0,40);

  h_pt_EE_noCut_s->Sumw2();
  h_pt_EE_noCut_b->Sumw2();

  h_nVtx_EE_noCut_s->Sumw2();
  h_nVtx_EE_noCut_b->Sumw2();


  // h_pt_EE_wRho_noCut_s->Sumw2();
  // h_pt_EE_wRho_noCut_b->Sumw2();

  // h_nVtx_EE_wRho_noCut_s->Sumw2();
  // h_nVtx_EE_wRho_noCut_b->Sumw2();


  TCut EE_noCut_s ="mvares>-2 && abs(scEta)>1.5 && pt > 18";
  TCut EE_noCut_b  = "mvares>-2 && abs(scEta)>1.5 && pt > 18";

  // TCut EE_wRho_noCut_s ="(mvares>-2 && abs(scEta)>1.5 && pt > 18)*rhoRew";
  // TCut EE_wRho_noCut_b  = "(mvares>-2 && abs(scEta)>1.5 && pt > 18)*rhoRew";

  t_EE_noCut_s->Draw("pt>>h_pt_EE_noCut_s",EE_noCut_s,"goff");
  t_EE_noCut_b->Draw("pt>>h_pt_EE_noCut_b",EE_noCut_b,"goff");

  t_EE_noCut_s->Draw("nvtx>>h_nVtx_EE_noCut_s",EE_noCut_s,"goff");
  t_EE_noCut_b->Draw("nvtx>>h_nVtx_EE_noCut_b",EE_noCut_b,"goff");

  // t_EE_wRho_s->Draw("pt>>h_pt_EE_wRho_noCut_s",EE_wRho_noCut_s,"goff");
  // t_EE_wRho_b->Draw("pt>>h_pt_EE_wRho_noCut_b",EE_wRho_noCut_b,"goff");

  // t_EE_wRho_s->Draw("nvtx>>h_nVtx_EE_wRho_noCut_s",EE_wRho_noCut_s,"goff");
  // t_EE_wRho_b->Draw("nvtx>>h_nVtx_EE_wRho_noCut_b",EE_wRho_noCut_b,"goff");


  //EE, mvares cut

  TH1F * h_pt_EE_Cut_s = new TH1F ("h_pt_EE_Cut_s","h_pt_EE_Cut_s",25,0,250);
  TH1F * h_pt_EE_Cut_b = new TH1F ("h_pt_EE_Cut_b","h_pt_EE_Cut_b",25,0,250);

  TH1F * h_nVtx_EE_Cut_s = new TH1F ("h_nVtx_EE_Cut_s","h_nVtx_EE_Cut_s",40,0,40);
  TH1F * h_nVtx_EE_Cut_b = new TH1F ("h_nVtx_EE_Cut_b","h_nVtx_EE_Cut_b",40,0,40);

  // TH1F * h_pt_EE_wRho_Cut_s = new TH1F ("h_pt_EE_wRho_Cut_s","h_pt_EE_wRho_Cut_s",25,0,250);
  // TH1F * h_pt_EE_wRho_Cut_b = new TH1F ("h_pt_EE_wRho_Cut_b","h_pt_EE_wRho_Cut_b",25,0,250);

  // TH1F * h_nVtx_EE_wRho_Cut_s = new TH1F ("h_nVtx_EE_wRho_Cut_s","h_nVtx_EE_wRho_Cut_s",40,0,40);
  // TH1F * h_nVtx_EE_wRho_Cut_b = new TH1F ("h_nVtx_EE_wRho_Cut_b","h_nVtx_EE_wRho_Cut_b",40,0,40);

 //WP90%

  TCut EE_Cut_s = "mvares>0.15 && abs(scEta)>1.5 && pt > 18";
  TCut EE_Cut_b  = "mvares>0.15 && abs(scEta)>1.5 && pt > 18";
  
  // TCut EE_wRho_Cut_s = "(mvares>0.15 && abs(scEta)>1.5 && pt > 18 )*rhoRew";
  // TCut EE_wRho_Cut_b  = "(mvares>0.15 && abs(scEta)>1.5 && pt > 18 )*rhoRew";
  
  h_pt_EE_Cut_s->Sumw2();
  h_pt_EE_Cut_b->Sumw2();

  h_nVtx_EE_Cut_s->Sumw2();
  h_nVtx_EE_Cut_b->Sumw2();

  // h_pt_EE_wRho_Cut_s->Sumw2();
  // h_pt_EE_wRho_Cut_b->Sumw2();

  // h_nVtx_EE_wRho_Cut_s->Sumw2();
  // h_nVtx_EE_wRho_Cut_b->Sumw2();

  t_EE_noCut_s->Draw("pt>>h_pt_EE_Cut_s",EE_Cut_s,"goff");
  t_EE_noCut_b->Draw("pt>>h_pt_EE_Cut_b",EE_Cut_b,"goff");

  t_EE_noCut_s->Draw("nvtx>>h_nVtx_EE_Cut_s",EE_Cut_s,"goff");
  t_EE_noCut_b->Draw("nvtx>>h_nVtx_EE_Cut_b",EE_Cut_b,"goff");

  // t_EE_wRho_s->Draw("pt>>h_pt_EE_wRho_Cut_s",EE_wRho_Cut_s,"goff");
  // t_EE_wRho_b->Draw("pt>>h_pt_EE_wRho_Cut_b",EE_wRho_Cut_b,"goff");

  // t_EE_wRho_s->Draw("nvtx>>h_nVtx_EE_wRho_Cut_s",EE_wRho_Cut_s,"goff");
  // t_EE_wRho_b->Draw("nvtx>>h_nVtx_EE_wRho_Cut_b",EE_wRho_Cut_b,"goff");


  //effs EB

  TH1F * h_pt_EB_eff_s = new TH1F ("h_pt_EB_eff_s","h_pt_EB_eff_s",25,0,250);
  TH1F * h_pt_EB_eff_b = new TH1F ("h_pt_EB_eff_b","h_pt_EB_eff_b",25,0,250);

  TH1F * h_nVtx_EB_eff_s = new TH1F ("h_nVtx_EB_eff_s","h_nVtx_EB_eff_s",40,0,40);
  TH1F * h_nVtx_EB_eff_b = new TH1F ("h_nVtx_EB_eff_b","h_nVtx_EB_eff_b",40,0,40);

  // TH1F * h_pt_EB_wRho_eff_s = new TH1F ("h_pt_EB_wRho_eff_s","h_pt_EB_wRho_eff_s",25,0,250);
  // TH1F * h_pt_EB_wRho_eff_b = new TH1F ("h_pt_EB_wRho_eff_b","h_pt_EB_wRho_eff_b",25,0,250);

  // TH1F * h_nVtx_EB_wRho_eff_s = new TH1F ("h_nVtx_EB_wRho_eff_s","h_nVtx_EB_wRho_eff_s",40,0,40);
  // TH1F * h_nVtx_EB_wRho_eff_b = new TH1F ("h_nVtx_EB_wRho_eff_b","h_nVtx_EB_wRho_eff_b",40,0,40);


  h_pt_EB_eff_s->Sumw2();
  h_pt_EB_eff_b->Sumw2();

  h_nVtx_EB_eff_s->Sumw2();
  h_nVtx_EB_eff_b->Sumw2();

  // h_pt_EB_wRho_eff_s->Sumw2();
  // h_pt_EB_wRho_eff_b->Sumw2();

  // h_nVtx_EB_wRho_eff_s->Sumw2();
  // h_nVtx_EB_wRho_eff_b->Sumw2();


  h_pt_EB_eff_s = (TH1F*)h_pt_EB_Cut_s->Clone("h_pt_EB_eff_s");
  h_pt_EB_eff_s->Divide(h_pt_EB_s);

  h_pt_EB_eff_b = (TH1F*)h_pt_EB_Cut_b->Clone("h_pt_EB_eff_b");
  h_pt_EB_eff_b->Divide(h_pt_EB_b);

  h_nVtx_EB_eff_s = (TH1F*)h_nVtx_EB_Cut_s->Clone("h_nVtx_EB_eff_s");
  h_nVtx_EB_eff_s->Divide(h_nVtx_EB_s);

  h_nVtx_EB_eff_b = (TH1F*)h_nVtx_EB_Cut_b->Clone("h_nVtx_EB_eff_b");
  h_nVtx_EB_eff_b->Divide(h_nVtx_EB_b);

  // h_pt_EB_wRho_eff_s = (TH1F*)h_pt_EB_wRho_Cut_s->Clone("h_pt_EB_wRho_eff_s");
  // h_pt_EB_wRho_eff_s->Divide(h_pt_EB_wRho_s);

  // h_pt_EB_wRho_eff_b = (TH1F*)h_pt_EB_wRho_Cut_b->Clone("h_pt_EB_wRho_eff_b");
  // h_pt_EB_wRho_eff_b->Divide(h_pt_EB_wRho_b);

  // h_nVtx_EB_wRho_eff_s = (TH1F*)h_nVtx_EB_wRho_Cut_s->Clone("h_nVtx_EB_wRho_eff_s");
  // h_nVtx_EB_wRho_eff_s->Divide(h_nVtx_EB_wRho_s);

  // h_nVtx_EB_wRho_eff_b = (TH1F*)h_nVtx_EB_wRho_Cut_b->Clone("h_nVtx_wRho_EB_eff_b");
  // h_nVtx_EB_wRho_eff_b->Divide(h_nVtx_EB_wRho_b);


  //effs EE

  TH1F * h_pt_EE_eff_s = new TH1F ("h_pt_EE_eff_s","h_pt_EE_eff_s",25,0,250);
  TH1F * h_pt_EE_eff_b = new TH1F ("h_pt_EE_eff_b","h_pt_EE_eff_b",25,0,250);

  TH1F * h_nVtx_EE_eff_s = new TH1F ("h_nVtx_EE_eff_s","h_nVtx_EE_eff_s",40,0,40);
  TH1F * h_nVtx_EE_eff_b = new TH1F ("h_nVtx_EE_eff_b","h_nVtx_EE_eff_b",40,0,40);

  // TH1F * h_pt_EE_wRho_eff_s = new TH1F ("h_pt_EE_wRho_eff_s","h_pt_EE_wRho_eff_s",25,0,250);
  // TH1F * h_pt_EE_wRho_eff_b = new TH1F ("h_pt_EE_wRho_eff_b","h_pt_EE_wRho_eff_b",25,0,250);

  // TH1F * h_nVtx_EE_wRho_eff_s = new TH1F ("h_nVtx_EE_wRho_eff_s","h_nVtx_EE_wRho_eff_s",40,0,40);
  // TH1F * h_nVtx_EE_wRho_eff_b = new TH1F ("h_nVtx_EE_wRho_eff_b","h_nVtx_EE_wRho_eff_b",40,0,40);

  TH1F * ratio_pt_eff_EE_76_80_s = new TH1F("ratio_pt_eff_EE_76_80_s","ratio_pt_eff_EE_76_80_s",25,0,250);
  TH1F * ratio_pt_eff_EE_76_80_b = new TH1F("ratio_pt_eff_EE_76_80_b","ratio_pt_eff_EE_76_80_b",25,0,250);

  ratio_pt_eff_EE_76_80_s->Sumw2();
  ratio_pt_eff_EE_76_80_b->Sumw2();

  h_pt_EE_eff_s->Sumw2();
  h_pt_EE_eff_b->Sumw2();

  h_nVtx_EE_eff_s->Sumw2();
  h_nVtx_EE_eff_b->Sumw2();

  // h_pt_EE_wRho_eff_s->Sumw2();
  // h_pt_EE_wRho_eff_b->Sumw2();

  // h_nVtx_EE_wRho_eff_s->Sumw2();
  // h_nVtx_EE_wRho_eff_b->Sumw2();


  h_pt_EE_eff_s = (TH1F*)h_pt_EE_Cut_s->Clone("h_pt_EE_eff_s");
  h_pt_EE_eff_s->Divide(h_pt_EE_noCut_s);

  h_pt_EE_eff_b = (TH1F*)h_pt_EE_Cut_b->Clone("h_pt_EE_eff_b");
  h_pt_EE_eff_b->Divide(h_pt_EE_noCut_b);


  h_nVtx_EE_eff_s = (TH1F*)h_nVtx_EE_Cut_s->Clone("h_nVtx_EE_eff_s");
  h_nVtx_EE_eff_s->Divide(h_nVtx_EE_noCut_s);

  h_nVtx_EE_eff_b = (TH1F*)h_nVtx_EE_Cut_b->Clone("h_nVtx_EE_eff_b");
  h_nVtx_EE_eff_b->Divide(h_nVtx_EE_noCut_b);


  // h_pt_EE_wRho_eff_s = (TH1F*)h_pt_EE_wRho_Cut_s->Clone("h_pt_EE_wRho_eff_s");
  // h_pt_EE_wRho_eff_s->Divide(h_pt_EE_wRho_noCut_s);

  // h_pt_EE_wRho_eff_b = (TH1F*)h_pt_EE_wRho_Cut_b->Clone("h_pt_EE_wRho_eff_b");
  // h_pt_EE_wRho_eff_b->Divide(h_pt_EE_wRho_noCut_b);


  // h_nVtx_EE_wRho_eff_s = (TH1F*)h_nVtx_EE_wRho_Cut_s->Clone("h_nVtx_EE_wRho_eff_s");
  // h_nVtx_EE_wRho_eff_s->Divide(h_nVtx_EE_wRho_noCut_s);

  // h_nVtx_EE_wRho_eff_b = (TH1F*)h_nVtx_EE_wRho_Cut_b->Clone("h_nVtx_EE_wRho_eff_b");
  // h_nVtx_EE_wRho_eff_b->Divide(h_nVtx_EE_wRho_noCut_b);

  ratio_pt_eff_EE_76_80_s = (TH1F*)h_pt_EE_eff_s->Clone("ratio_pt_eff_EE_76_80_s");
  ratio_pt_eff_EE_76_80_s->Divide(h_pt_EE_eff_b);

  //ratio_pt_eff_EE_76_80_b= (TH1F*)h_pt_EE_wRho_eff_s->Clone("ratio_pt_eff_EE_76_80_b");
  //ratio_pt_eff_EE_76_80_b->Divide(h_pt_EE_wRho_eff_b);


  //plot eff histos:

  TLegend *leg = new TLegend(0.4,0.4,0.6,0.6);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetHeader(" EB :");

  TLegend *leg_EE = new TLegend(0.4,0.4,0.6,0.6);
  leg_EE->SetBorderSize(0);
  leg_EE->SetFillColor(0);
  leg_EE->SetHeader(" EE :");


  TCanvas * can_pt_eff_EB = new TCanvas("can_pt_eff_EB","can_pt_eff_EB",800,600);

  can_pt_eff_EB->SetGrid();

  h_pt_EB_eff_s->SetStats(0);
  h_pt_EB_eff_s->SetTitle("");
  h_pt_EB_eff_s->GetXaxis()->SetTitle("Pt (GeV)");
  h_pt_EB_eff_s->GetYaxis()->SetTitle("Efficiency");
  h_pt_EB_eff_s->GetYaxis()->SetRangeUser(0.,1.);

  h_pt_EB_eff_s->SetLineColor(kBlue);
  h_pt_EB_eff_s->SetMarkerStyle(20);
  h_pt_EB_eff_s->SetMarkerSize(0.7);
  h_pt_EB_eff_s->SetMarkerColor(kBlue);
  h_pt_EB_eff_s->Draw("P");

  //h_pt_EB_wRho_eff_s->SetLineColor(kAzure-4);
  //h_pt_EB_wRho_eff_s->SetMarkerStyle(20);
  //h_pt_EB_wRho_eff_s->SetMarkerSize(0.7);
  //h_pt_EB_wRho_eff_s->SetMarkerColor(kAzure-4);
  //h_pt_EB_wRho_eff_s->Draw("Psame");


  h_pt_EB_eff_b->SetLineColor(kRed);
  h_pt_EB_eff_b->SetMarkerStyle(20);
  h_pt_EB_eff_b->SetMarkerSize(0.7);
  h_pt_EB_eff_b->SetMarkerColor(kRed);
  h_pt_EB_eff_b->Draw("Psame");

  //h_pt_EB_wRho_eff_b->SetLineColor(kRed-9);
  //h_pt_EB_wRho_eff_b->SetMarkerStyle(20);
  //h_pt_EB_wRho_eff_b->SetMarkerSize(0.7);
  //h_pt_EB_wRho_eff_b->SetMarkerColor(kRed-9);
  //h_pt_EB_wRho_eff_b->Draw("Psame");


  /*
  leg->AddEntry(h_pt_EB_eff_s, "Signal : no rho rew","P");
  leg->AddEntry(h_pt_EB_eff_b, "Bkg : no rho rew","P");
  */

  leg->AddEntry(h_pt_EB_eff_s, "Signal : new MC","P");
  leg->AddEntry(h_pt_EB_eff_b, "Bkg : new MC","P");

  //leg->AddEntry(h_pt_EB_wRho_eff_s, "Signal : old MC, rho rew","P");
  //leg->AddEntry(h_pt_EB_wRho_eff_b, "Bkg : old MC, rho rew","P");

  leg->Draw("same");


  can_pt_eff_EB->SaveAs("phoId_eff_vs_pt_barrel_Hgg_90_newMC.pdf");
  can_pt_eff_EB->SaveAs("phoId_eff_vs_pt_barrel_Hgg_90_newMC.png");
  can_pt_eff_EB->SaveAs("phoId_eff_vs_pt_barrel_Hgg_90_newMC.root");


  TCanvas * can_nVtx_eff_EB = new TCanvas("can_nVtx_eff_EB","can_nVtx_eff_EB",800,600);
  can_nVtx_eff_EB->SetGrid();

  h_nVtx_EB_eff_s->SetStats(0);
  h_nVtx_EB_eff_s->SetTitle("");
  h_nVtx_EB_eff_s->GetXaxis()->SetTitle("number of vertices");
  h_nVtx_EB_eff_s->GetYaxis()->SetTitle("Efficiency");
  h_nVtx_EB_eff_s->GetYaxis()->SetRangeUser(0.,1.);

  h_nVtx_EB_eff_s->SetLineColor(kBlue);
  h_nVtx_EB_eff_s->SetMarkerStyle(20);
  h_nVtx_EB_eff_s->SetMarkerSize(0.7);
  h_nVtx_EB_eff_s->SetMarkerColor(kBlue);
  h_nVtx_EB_eff_s->Draw("P");

  //h_nVtx_EB_wRho_eff_s->SetLineColor(kAzure-4);
  //h_nVtx_EB_wRho_eff_s->SetMarkerStyle(20);
  //h_nVtx_EB_wRho_eff_s->SetMarkerSize(0.7);
  //h_nVtx_EB_wRho_eff_s->SetMarkerColor(kAzure-4);
  //h_nVtx_EB_wRho_eff_s->Draw("Psame");

  h_nVtx_EB_eff_b->SetLineColor(kRed);
  h_nVtx_EB_eff_b->SetMarkerStyle(20);
  h_nVtx_EB_eff_b->SetMarkerSize(0.7);
  h_nVtx_EB_eff_b->SetMarkerColor(kRed);
  h_nVtx_EB_eff_b->Draw("Psame");


  //h_nVtx_EB_wRho_eff_b->SetLineColor(kRed-9);
  //h_nVtx_EB_wRho_eff_b->SetMarkerStyle(20);
  //h_nVtx_EB_wRho_eff_b->SetMarkerSize(0.7);
  //h_nVtx_EB_wRho_eff_b->SetMarkerColor(kRed-9);
  //h_nVtx_EB_wRho_eff_b->Draw("Psame");

  leg->Draw("same");


  can_nVtx_eff_EB->SaveAs("phoId_eff_vs_nVtx_barrel_Hgg_90_newMC.pdf");
  can_nVtx_eff_EB->SaveAs("phoId_eff_vs_nVtx_barrel_Hgg_90_newMC.png");
  can_nVtx_eff_EB->SaveAs("phoId_eff_vs_nVtx_barrel_Hgg_90_newMC.root");

  //effs EE draw

  TCanvas * can_pt_eff_EE = new TCanvas("can_pt_eff_EE","can_pt_eff_EE",800,600);

  can_pt_eff_EE->SetGrid();

  h_pt_EE_eff_s->SetStats(0);
  h_pt_EE_eff_s->SetTitle("");
  h_pt_EE_eff_s->GetXaxis()->SetTitle("Pt (GeV)");
  h_pt_EE_eff_s->GetYaxis()->SetTitle("Efficiency");
  h_pt_EE_eff_s->GetYaxis()->SetRangeUser(0.,1.);
  //  h_pt_EE_eff_s->GetXaxis()->SetLabelSize(0.);

  h_pt_EE_eff_s->SetLineColor(kBlue);
  h_pt_EE_eff_s->SetMarkerStyle(20);
  h_pt_EE_eff_s->SetMarkerSize(0.7);
  h_pt_EE_eff_s->SetMarkerColor(kBlue);
  h_pt_EE_eff_s->Draw("P");

  //h_pt_EE_wRho_eff_s->SetLineColor(kAzure-4);
  //h_pt_EE_wRho_eff_s->SetMarkerStyle(20);
  //h_pt_EE_wRho_eff_s->SetMarkerSize(0.7);
  //h_pt_EE_wRho_eff_s->SetMarkerColor(kAzure-4);
  //h_pt_EE_wRho_eff_s->Draw("Psame");
  ////h_pt_EE_wRho_eff_s->Draw("P");


  h_pt_EE_eff_b->SetLineColor(kRed);
  h_pt_EE_eff_b->SetMarkerStyle(20);
  h_pt_EE_eff_b->SetMarkerSize(0.7);
  h_pt_EE_eff_b->SetMarkerColor(kRed);
  h_pt_EE_eff_b->Draw("Psame");

  //h_pt_EE_wRho_eff_b->SetLineColor(kRed-9);
  //h_pt_EE_wRho_eff_b->SetMarkerStyle(20);
  //h_pt_EE_wRho_eff_b->SetMarkerSize(0.7);
  //h_pt_EE_wRho_eff_b->SetMarkerColor(kRed-9);
  //h_pt_EE_wRho_eff_b->Draw("Psame");

  /*
  leg_EE->AddEntry(h_pt_EE_eff_s, "Signal : no rho rew","P");
  leg_EE->AddEntry(h_pt_EE_eff_b, "Bkg : no rho rew","P");
  */

  leg_EE->AddEntry(h_pt_EE_eff_s, "Signal : new MC","P");
  leg_EE->AddEntry(h_pt_EE_eff_b, "Bkg : new MC","P");

  //leg_EE->AddEntry(h_pt_EE_wRho_eff_s, "Signal : old MC, rho rew","P");
  //leg_EE->AddEntry(h_pt_EE_wRho_eff_b, "Bkg : old MC, rho rew","P");

  leg_EE->Draw("same");

  can_pt_eff_EE->Update();
  can_pt_eff_EE->Modified();

  can_pt_eff_EE->SaveAs("phoId_eff_vs_pt_endcap_Hgg_90_newMC.pdf");
  can_pt_eff_EE->SaveAs("phoId_eff_vs_pt_endcap_Hgg_90_newMC.png");
  can_pt_eff_EE->SaveAs("phoId_eff_vs_pt_endcap_Hgg_90_newMC.root");

  TCanvas * can_nVtx_eff_EE = new TCanvas("can_nVtx_eff_EE","can_nVtx_eff_EE",800,600);
  can_nVtx_eff_EE->SetGrid();

  h_nVtx_EE_eff_s->SetStats(0);
  h_nVtx_EE_eff_s->SetTitle("");
  h_nVtx_EE_eff_s->GetXaxis()->SetTitle("number of vertices");
  h_nVtx_EE_eff_s->GetYaxis()->SetTitle("Efficiency");
  h_nVtx_EE_eff_s->GetYaxis()->SetRangeUser(0.,1.);

  h_nVtx_EE_eff_s->SetLineColor(kBlue);
  h_nVtx_EE_eff_s->SetMarkerStyle(20);
  h_nVtx_EE_eff_s->SetMarkerSize(0.7);
  h_nVtx_EE_eff_s->SetMarkerColor(kBlue);
  h_nVtx_EE_eff_s->Draw("P");

  //h_nVtx_EE_wRho_eff_s->SetLineColor(kAzure-4);
  //h_nVtx_EE_wRho_eff_s->SetMarkerStyle(20);
  //h_nVtx_EE_wRho_eff_s->SetMarkerSize(0.7);
  //h_nVtx_EE_wRho_eff_s->SetMarkerColor(kAzure-4);
  //h_nVtx_EE_wRho_eff_s->Draw("Psame");
  //h_nVtx_EE_wRho_eff_s->Draw("P");


  h_nVtx_EE_eff_b->SetLineColor(kRed);
  h_nVtx_EE_eff_b->SetMarkerStyle(20);
  h_nVtx_EE_eff_b->SetMarkerSize(0.7);
  h_nVtx_EE_eff_b->SetMarkerColor(kRed);
  h_nVtx_EE_eff_b->Draw("Psame");

  //h_nVtx_EE_wRho_eff_b->SetLineColor(kRed-9);
  //h_nVtx_EE_wRho_eff_b->SetMarkerStyle(20);
  //h_nVtx_EE_wRho_eff_b->SetMarkerSize(0.7);
  //h_nVtx_EE_wRho_eff_b->SetMarkerColor(kRed-9);
  //h_nVtx_EE_wRho_eff_b->Draw("Psame");

  leg_EE->Draw("same");

  can_nVtx_eff_EE->SaveAs("phoId_eff_vs_nVtx_endcap_Hgg_90_newMC.pdf");
  can_nVtx_eff_EE->SaveAs("phoId_eff_vs_nVtx_endcap_Hgg_90_newMC.png");
  can_nVtx_eff_EE->SaveAs("phoId_eff_vs_nVtx_endcap_Hgg_90_newMC.root");

}
