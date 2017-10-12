Producing the ntuple:
=====================
First you need to produce the ntuple from GJets datasets, with photon variables needed for the MVA training. The example dumper can be found inside flashgg area.
```
https://github.com/cms-analysis/flashgg/blob/master/Taggers/test/singlePhotonViewDumper_cfg.py
```

Three GJet datasets are normally used.
1. For standard Higgs to diphoton analysis
   a. GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8
   b. GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8
2. For low mass Higgs analysis
   a. GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8

You need to write a json with the available GJet datasets to run the jobs in batch using script fggRunJobs.py

Pt and eta reweight:
====================

Once you got the ntuple, you need to do a 2D reweigt (pt and eta) to prompt photons with respect to fake photons.
We usually do it in three steps.

1. Produce the 2D weight factors
```
root -l create2Dweights.cc
```

It will produce a root file with the weights which we need to use in the next step.
2. To add weights
```
root -l add2Dweights.cc
```

This step also splits the tree into half for training purpose. Normally we take the odd events for training purpose. There is also a similar script which basically do the same thing except it saves the even events for test purpose. 
```
root -l makeTestTree.cc
```

3. Now you need to produce the plots to check if the reweighting has been done successfully. 
```
root -l check2Dweights.cc
```
By default it produces plots only for barrel. For endcap you need to run again by modifying a few variable inside the scripts.

BDT training:
=============
For the TMVA training there are two scripts, 
1. For barrel: TMVAClassification_preSelCuts_Run2.C
2. For endcap: TMVAClassification_preSelCuts_Run2_EE_isoCorr_newMC.C

Once you are done with training, you need to produce the weight files from the output root files using the following scripts.
1. For barrel: evaluateMVA_EB_Hgg_newMC.cc
2. For endcap: evaluateMVA_EE_Hgg_corrIso_newMC.cc

To plot MVA output, ROC curves and efficiency plots:
====================================================
To plot the MVA output and ROC curves, use

1. plotMVARes_barrel_Hgg_newMC.cc (for barrel)
2. plotMVARes_endcap_Hgg_newMC.cc (for endcap)

To plot efficiency with respect to pT, no. of vertices and eta, use createHistoPhoEff_Hgg_2.cc.
