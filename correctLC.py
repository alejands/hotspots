from __future__ import division, print_function
import sys, os
import ROOT

poolOccResolution = False

ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetPalette(1)
ROOT.gStyle.SetOptStat(0)

f_eeCalib = ROOT.TFile.Open("eeCalib.root")
eeCalib = f_eeCalib.eeCalib
f_Occ = ROOT.TFile.Open("Out_Comp_2018D.root")

if not os.path.exists("out/"):
    os.mkdir("out/")
if not os.path.exists("img/correctLC/"):
    os.mkdir("img/correctLC")

outfile = ROOT.TFile.Open("out/correctLC.root", "RECREATE")
cc = ROOT.TCanvas("cc", "cc", 800, 800)
cc.SetRightMargin(0.125)

eeCalib.Draw("phi:-eta>>hNorm(200,-5,5, 200,-3.1416, 3.1416)", "(chStatus==0)")
hNorm = ROOT.gDirectory.Get("hNorm")
hEE = hNorm.Clone("hEE")
hEE.Divide(hEE)

# Calibration Values
eeCalib.Draw("phi:-eta>>hLC_EOY(200,-5,5, 200,-3.1416, 3.1416)", "(LC_EOY2018D)*(chStatus==0)")
hLC_EOY = ROOT.gDirectory.Get("hLC_EOY")
hLC_EOY.Divide(hNorm)
hLC_EOY.GetXaxis().SetTitle("#eta")
hLC_EOY.GetYaxis().SetTitle("#phi")
hLC_EOY.SetTitle("2018D EOY LC")
hLC_EOY.SetMaximum(30)
hLC_EOY.Draw("colz")
cc.Update()
cc.SaveAs("img/correctLC/hLC_EOY.pdf")
hLC_EOY.Write()

eeCalib.Draw("phi:-eta>>hLC_UL(200,-5,5, 200,-3.1416, 3.1416)", "(IC_UL2018D*LC_UL2018D)*(chStatus==0)")
hLC_UL = ROOT.gDirectory.Get("hLC_UL")
hLC_UL.Divide(hNorm)
hLC_UL.GetXaxis().SetTitle("#eta")
hLC_UL.GetYaxis().SetTitle("#phi")
hLC_UL.SetTitle("2018D UL LC")
hLC_UL.SetMaximum(30)
hLC_UL.Draw("colz")
cc.Update()
cc.SaveAs("img/correctLC/hLC_UL.pdf")
hLC_UL.Write()

hLC_Ratio = hLC_EOY.Clone("hRatio")
hLC_Ratio.Divide(hLC_UL)
hLC_Ratio.SetTitle("2018D LC Ratio")
hLC_Ratio.SetMaximum(3)
hLC_Ratio.Draw("colz")
cc.Update()
cc.SaveAs("img/correctLC/hLC_Ratio.pdf")
hLC_Ratio.Write()

# Occupancies
hOcc_EOY = f_Occ.Get("Prompth_jet200etavsphi_pass")
hOcc_EOY.GetXaxis().SetTitle("#eta")
hOcc_EOY.GetYaxis().SetTitle("#phi")
hOcc_EOY.SetTitle("2018D EOY Occupancy")
if poolOccResolution: hOcc_EOY.Rebin2D()
hOcc_EOY.Multiply(hEE)
if poolOccResolution:
    hOcc_EOY.SetMaximum(3000)
else:
    hOcc_EOY.SetMaximum(750)
hOcc_EOY.Draw("colz")
cc.Update()
cc.SaveAs("img/correctLC/hOcc_EOY.pdf")
hOcc_EOY.Write()

hOcc_UL = f_Occ.Get("106Xh_jet200etavsphi_pass")
hOcc_UL.GetXaxis().SetTitle("#eta")
hOcc_UL.GetYaxis().SetTitle("#phi")
hOcc_UL.SetTitle("2018D UL Occupancy")
if poolOccResolution: hOcc_UL.Rebin2D()
hOcc_UL.Multiply(hEE)
if poolOccResolution:
    hOcc_UL.SetMaximum(3000)
else:
    hOcc_UL.SetMaximum(750)
hOcc_UL.Draw("colz")
cc.Update()
cc.SaveAs("img/correctLC/hOcc_UL.pdf")
hOcc_UL.Write()

hOcc_Fix = hOcc_EOY.Clone("hOcc_Fix")
hOcc_Fix.Divide(hLC_Ratio)
hOcc_Fix.SetTitle("\"Fixed\" 2018D EOY Occupancies")
hOcc_Fix.Draw("colz")
cc.Update()
cc.SaveAs("img/correctLC/hOcc_Fix.pdf")
hOcc_Fix.Write()

eeCalib.Draw("phi:-eta>>hHighEta(200,-5,5, 200,-3.1416, 3.1416)", "(abs(eta)>2.5)*(chStatus==0)")
hHighEta = ROOT.gDirectory.Get("hHighEta")

hULvFix = ROOT.TH2F("hULvFix", "UL Occupancy vs \"Fixed\" Occupancy", 100,0,1000, 100,0,1000)
hULvFix.GetXaxis().SetTitle("UL Occupancy")
hULvFix.GetYaxis().SetTitle("Fixed Occupancy")
hULvFix_highEta = hULvFix.Clone("hULvFix_highEta")
hULvFix_highEta.SetTitle("UL Occupancy vs \"Fixed\" Occupancy |eta|>2.5")
hULvEOY = hULvFix.Clone("hULvEOY")
hULvEOY.GetYaxis().SetTitle("EOY Occupancy")

for i in range(1, hHighEta.GetNbinsX()*hHighEta.GetNbinsY() + 1):
    UL = hOcc_UL.GetBinContent(i)
    Fix = hOcc_Fix.GetBinContent(i)
    if UL==0: continue
    if Fix !=0:
        hULvFix.Fill(UL,Fix)
        if hHighEta.GetBinContent(i) != 0:
            hULvFix_highEta.Fill(UL, Fix)
        EOY = hOcc_EOY.GetBinContent(i)
        if EOY==0: continue
        hULvEOY.Fill(UL,EOY)
    

cc.SetMargin(0.125, 0.125, 0.1, 0.1)
slope1 = ROOT.TLine(0,0,1000,1000)

hULvFix.Draw("colz")
slope1.Draw("same")
print("Total correlation factor:", hULvFix.GetCorrelationFactor())
cc.Update()
cc.SaveAs("img/correctLC/hULvFix.pdf")
hULvFix.Write()

hULvFix_highEta.Draw("colz")
slope1.Draw("same")
print("High eta correlation factor:", hULvFix_highEta.GetCorrelationFactor())
cc.Update()
cc.SaveAs("img/correctLC/hULvFix_highEta.pdf")
hULvFix_highEta.Write()

hULvEOY.Draw("colz")
slope1.Draw("same")
print("High eta correlation factor:", hULvEOY.GetCorrelationFactor())
cc.Update()
cc.SaveAs("img/correctLC/hULvEOY.pdf")
hULvEOY.Write()
