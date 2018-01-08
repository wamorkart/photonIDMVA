## Producing the ntuple

First you need to produce the ntuple from GJets datasets, with photon variables needed for the MVA training. The example dumper can be found inside flashgg area.
* [Taggers/test/singlePhotonViewDumper_cfg.py](https://github.com/cms-analysis/flashgg/blob/master/Taggers/test/singlePhotonViewDumper_cfg.py)

Three GJet datasets are normally used.
1. For standard Higgs to diphoton analysis
* GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8
* GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8
2. For low mass Higgs analysis
* GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8

You need to write a json with the available GJet datasets to run the jobs in batch using script fggRunJobs.py

## MVA part
#### Pt and eta reweight:

Once you got the ntuple, you need to do a 2D reweigt (pt and eta) to prompt photons with respect to fake photons.
We usually do it in three steps.

1. To Produce the 2D weight factors 
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

#### BDT training:

For the TMVA training there are two scripts, 
- For barrel: TMVAClassification_preSelCuts_Run2_EB.C
- For endcap: TMVAClassification_preSelCuts_Run2_EE.C

Once you are done with training, you need to produce the weight files from the output root files using the following scripts.
- For barrel: evaluateMVA_EB_Hgg_newMC.cc
- For endcap: evaluateMVA_EE_Hgg_newMC.cc

#### To plot MVA output, ROC curves and efficiency plots:

To plot the MVA output and ROC curves, use

- plotMVARes_barrel_Hgg_newMC.cc (for barrel)
- plotMVARes_endcap_Hgg_newMC.cc (for endcap)

To plot efficiency with respect to pT, no. of vertices and eta, use `createHistoPhoEff_Hgg_2.cc`.
