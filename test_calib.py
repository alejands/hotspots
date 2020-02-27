from __future__ import division, print_function
import ROOT

ROOT.gROOT.SetBatch(ROOT.kTRUE)

f_calib = ROOT.TFile.Open("eeCalib.root")
eeCalib = ROOT.TTree()
eeCalib = f_calib.eeCalib
outfile = ROOT.TFile.Open("outfile.root", "RECREATE")

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPalette(1)
cc = ROOT.TCanvas("cc", "Canvas", 800, 800)

eeCalib.Draw("phi:-eta>>htemp(200,-5,5,200,-3.1416, 3.1416)", "IC_EOY2018D*LC_EOY2018D")
htemp = ROOT.TH2F()
htemp = ROOT.gDirectory.Get("htemp")
htemp.SetMaximum(30)
htemp.Draw("colz")
cc.SaveAs("imgtest.png")
cc.Update()

htemp.Write()
