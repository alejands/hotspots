from __future__ import print_function, division
import ROOT
from ROOT import gROOT, TFile, TTree, gStyle, gDirectory, TCanvas, TH1F, TH2F, kTRUE
import sys, os

gROOT.SetBatch(kTRUE)

f_calib = TFile.Open("eeCalib.root")
eeCalib = f_calib.Get("eeCalib")

if not os.path.exists("out"):
    os.mkdir("out")
if not os.path.exists("img/flagOccRatio.py")
    os.mkdir("img/flagOccRatio.py")

