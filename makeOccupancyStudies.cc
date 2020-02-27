#include <iostream>
#include <cstdlib>

#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TPad.h>
#include <TStyle.h>

void makeOccupancyStudies(){

    TFile *infile = TFile::Open("eeCalib.root");
    TTree *calib = 0;

    infile->GetObject("eeCalib", calib);
    if (!calib){
        cout << "unable to open input tree!" << endl;
        exit(EXIT_FAILURE);
    }

    gStyle->SetOptStat(0);
    gStyle->SetPalette(kRainBow);
    gStyle->SetPalette(1);
    TCanvas *cEOY = new TCanvas("cEOY", "cEOY", 800, 600);
    TCanvas *cUL = new TCanvas("cUL", "cUL", 800, 600);
    TCanvas *cRatio = new TCanvas("cRatio", "cRatio", 800, 600);
    TCanvas *cEEMap = new TCanvas("cEEMap", "cEEMap", 1200,600);
    TCanvas *cEtaPhi = new TCanvas("cEtaPhi", "cEtaPhi", 600, 600);
    //TCanvas *cIring = new TCanvas("cIring", "cIring", 1000,800);
    //TCanvas *cHighEta = new TCanvas("cHighEta", "cHighEta", 800, 800);

    // Occupancy studies
    // EE Map
    cEEMap->cd();

    calib->Draw("iy-0.5:ix-0.5+100*(iz>0)>>hOccEOY(200,0,200,100,0,100)", "doubleMuonOccEOY2017*(chStatus==0)");
    TH2F *hOccEOY = (TH2F*)gDirectory->Get("hOccEOY");
    float numEOY = hOccEOY->Integral();
    hOccEOY->Scale(1.f/hOccEOY->Integral());
    hOccEOY->SetTitle("Double Muon Normalized Occupancy EOY2017F");
    hOccEOY->GetXaxis()->SetTitle("ix+100*(iz>0)");
    hOccEOY->GetYaxis()->SetTitle("iy");
    hOccEOY->SetMaximum(0.001);

    calib->Draw("iy-0.5:ix-0.5+100*(iz>0)>>hOccUL(200,0,200,100,0,100)", "doubleMuonOccUL2017*(chStatus==0)");
    TH2F *hOccUL = (TH2F*)gDirectory->Get("hOccUL");
    float numUL = hOccUL->Integral();
    hOccUL->Scale(1.f/hOccUL->Integral());
    hOccUL->SetTitle("Double Muon Normalized Occupancy UL2017F");
    hOccUL->GetXaxis()->SetTitle("ix+100*(iz>0)");
    hOccUL->GetYaxis()->SetTitle("iy");
    hOccUL->SetMaximum(0.001);

    TH2F* hOccRatio = (TH2F*)hOccEOY->Clone("hOccRatio");
    hOccRatio->Divide(hOccUL);
    hOccRatio->SetTitle("Double Muon Occupancy Ratio EOY/UL 2017F");
    hOccRatio->SetMaximum(5);

    cEEMap->SetLogz(0);
    hOccEOY->Draw("colz");
    cEEMap->SaveAs("img/OccEEMapEOY2017.png");
    hOccUL->Draw("colz");
    cEEMap->SaveAs("img/OccEEMapUL2017.png");
    hOccRatio->Draw("colz");
    cEEMap->SaveAs("img/OccEEMapRatio2017F.png");

    // EtaPhi Map
    cEtaPhi->cd();
    cEtaPhi->SetLogz(0);

    calib->Draw("phi:-eta>>hOccNorm(100,-5.0,5.0,100,-3.15,3.15)", "chStatus==0");
    TH2F* hOccNorm = (TH2F*)gDirectory->Get("hOccNorm");

    calib->Draw("phi:-eta>>hOccEtaPhiEOY(100,-5.0,5.0,100,-3.15,3.15)", "doubleMuonOccEOY2017*(chStatus==0)");
    TH2F* hOccEtaPhiEOY = (TH2F*)gDirectory->Get("hOccEtaPhiEOY");
    hOccEtaPhiEOY->Scale(1.f/hOccEtaPhiEOY->Integral());
    hOccEtaPhiEOY->Divide(hOccNorm);
    hOccEtaPhiEOY->SetTitle("Double Muon Normalized Occupancy EOY2017F");
    hOccEtaPhiEOY->GetXaxis()->SetTitle("#eta");
    hOccEtaPhiEOY->GetYaxis()->SetTitle("#phi");
    hOccEtaPhiEOY->SetMaximum(0.001);
    hOccEtaPhiEOY->Draw("colz");
    cEtaPhi->SetRightMargin(0.15);
    cEtaPhi->SaveAs("img/OccEtaPhiEOY2017.png");

    calib->Draw("phi:-eta>>hOccEtaPhiUL(100,-5.0,5.0,100,-3.15,3.15)", "doubleMuonOccUL2017*(chStatus==0)");
    TH2F* hOccEtaPhiUL = (TH2F*)gDirectory->Get("hOccEtaPhiUL");
    hOccEtaPhiUL->Scale(1.f/hOccEtaPhiUL->Integral());
    hOccEtaPhiUL->Divide(hOccNorm);
    hOccEtaPhiUL->SetTitle("Double Muon Normalized Occupancy UL2017F");
    hOccEtaPhiUL->GetXaxis()->SetTitle("#eta");
    hOccEtaPhiUL->GetYaxis()->SetTitle("#phi");
    hOccEtaPhiUL->SetMaximum(0.001);
    hOccEtaPhiUL->Draw("colz");
    cEtaPhi->SaveAs("img/OccEtaPhiUL2017.png");

    cEtaPhi->SetLogz(0);
    TH2F* hOccEtaPhiRatio = (TH2F*)hOccEtaPhiEOY->Clone("hOccEtaPhiEOY");
    hOccEtaPhiRatio->Divide(hOccEtaPhiUL);
    hOccEtaPhiRatio->SetTitle("Double Muon Occupancy Ratio EOY/UL 2017F");
    //hOccEtaPhiRatio->GetXaxis()->SetTitle("#eta");
    //hOccEtaPhiRatio->GetYaxis()->SetTitle("#phi");
    hOccEtaPhiRatio->SetMaximum(5);
    hOccEtaPhiRatio->Draw("colz");
    cEtaPhi->SaveAs("img/OccEtaPhiRatio2017.png");


    cEOY->cd();
    cEOY->SetLogy(1);
    calib->Draw(("doubleMuonOccEOY2017/"+to_string(numEOY)+"*(chStatus==0)>>hEOY").c_str());
    TH1F* hEOY = (TH1F*)gDirectory->Get("hEOY");
    hEOY->SetTitle("Double Muon Normalized Occupancy EOY2017F");
    cEOY->SaveAs("img/Occ1dEOY2017.png");
    

    cUL->cd();
    cUL->SetLogy(1);
    calib->Draw(("doubleMuonOccUL2017/"+to_string(numUL)+"*(chStatus==0)>>hUL").c_str());
    TH1F* hUL = (TH1F*)gDirectory->Get("hUL");
    hUL->SetTitle("Double Muon Normalized Occupancy UL2017F");
    cUL->SaveAs("img/Occ1dUL2017.png");

    cRatio->cd();
    cRatio->SetLogy(1);
    calib->Draw("doubleMuonOccEOY2017/doubleMuonOccUL2017*(chStatus==0)>>hRatio");
    TH1F* hRatio = (TH1F*)gDirectory->Get("hRatio");
    hRatio->SetTitle("Double Muon Occupancy Ratio EOY/UL 2017");
    cRatio->SaveAs("img/Occ1dRatio2017.png");
    
}











