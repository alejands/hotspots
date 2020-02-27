#include <iostream>
#include <cstdlib>

#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TPad.h>
#include <TStyle.h>

void makeRatioPlots(){

    TFile *infile = TFile::Open("eeCalib.root");
    TTree *calib = 0;

    infile->GetObject("eeCalib", calib);
    if (!calib){
        cout << "unable to open input tree!" << endl;
        exit(EXIT_FAILURE);
    }

    gStyle->SetOptStat(0);
    //gStyle->SetPalette(kRainBow);
    gStyle->SetPalette(1);
    TCanvas *cEOY = new TCanvas("cEOY", "cEOY", 800, 600);
    TCanvas *cUL = new TCanvas("cUL", "cUL", 800, 600);
    TCanvas *cRatio = new TCanvas("cRatio", "cRatio", 800, 600);
    TCanvas *cEEMap = new TCanvas("cEEMap", "cEEMap", 1200,600);
    TCanvas *cEtaPhi = new TCanvas("cEtaPhi", "cEtaPhi", 600, 600);
    TCanvas *cIring = new TCanvas("cIring", "cIring", 1000,800);
    TCanvas *cHighEta = new TCanvas("cHighEta", "cHighEta", 800, 800);

    // Occupancy studies
    

    // loop over all eras

    vector<string> eras;
    eras.push_back("2017F");
    eras.push_back("2018A");
    eras.push_back("2018B");
    eras.push_back("2018C");
    eras.push_back("2018D");

    for (int i=0; i<eras.size(); i++){

        TCut isBad;
        if (eras[i] == "2017F") isBad = "istatus == 1";
        if (eras[i] == "2018A") isBad = "istatus == 1 || istatus == 2";
        if (eras[i] == "2018B") isBad = "istatus == 1 || istatus == 2";
        if (eras[i] == "2018C") isBad = "istatus == 1 || istatus == 2";
        if (eras[i] == "2018D") isBad = "istatus == 1 || istatus == 2 || istatus == 3";

        TCut chGood = "chStatus == 0";

        string EOY_ICxLC = "(IC_EOY" + eras[i] + "*LC_EOY" + eras[i] + ")";
        string UL_ICxLC = "(IC_UL" + eras[i] + "*LC_UL" + eras[i] + ")";
        string ICxLCbins = "(60,0,60)";

        string ratio_ICxLC = EOY_ICxLC + "/" + UL_ICxLC;
        string ratioBins = "(60,0,3)";

        // EOY
        string htemp = "hEOYGood"+ eras[i];
        string plot = EOY_ICxLC+">>"+htemp+ICxLCbins; 
        calib->Draw(plot.c_str(), chGood);
        TH1F *hEOYGood = (TH1F*)gDirectory->Get(htemp.c_str()); 
        hEOYGood->SetTitle("Good");
        hEOYGood->SetFillColor(kBlue);

        htemp = "hEOYBad" + eras[i];
        plot = EOY_ICxLC+">>"+htemp+ICxLCbins;
        calib->Draw(plot.c_str(), isBad && chGood);
        TH1F *hEOYBad = (TH1F*)gDirectory->Get(htemp.c_str());
        hEOYBad->SetTitle("Bad");
        hEOYBad->SetFillColor(kOrange);

        htemp = "hEOYWorst" + eras[i];
        plot = EOY_ICxLC+">>"+htemp+ICxLCbins; 
        calib->Draw(plot.c_str(), isBad && "iworst==1" && chGood);
        TH1F *hEOYWorst = (TH1F*)gDirectory->Get(htemp.c_str());
        hEOYWorst->SetTitle("Worst");
        hEOYWorst->SetFillColor(kRed);

        // UL
        htemp = "hULGood" + eras[i];
        plot = UL_ICxLC+">>"+htemp+ICxLCbins;
        calib->Draw(plot.c_str(), chGood);
        TH1F* hULGood = (TH1F*)gDirectory->Get(htemp.c_str());
        hULGood->SetTitle("Good");
        hULGood->SetFillColor(kBlue);

        htemp = "hULBad" + eras[i];
        plot = UL_ICxLC+">>"+htemp+ICxLCbins;
        calib->Draw(plot.c_str(), isBad && chGood);
        TH1F* hULBad = (TH1F*)gDirectory->Get(htemp.c_str());
        hULBad->SetTitle("Bad");
        hULBad->SetFillColor(kOrange);

        htemp = "hULWorst" + eras[i];
        plot = UL_ICxLC+">>"+htemp+ICxLCbins;
        calib->Draw(plot.c_str(), isBad && "iworst==1" && chGood);
        TH1F* hULWorst = (TH1F*)gDirectory->Get(htemp.c_str());
        hULWorst->SetTitle("Worst");
        hULWorst->SetFillColor(kRed);

        // Ratio        
        htemp = "hRatioGood" + eras[i];
        plot = ratio_ICxLC+">>"+htemp+ratioBins;
        calib->Draw(plot.c_str(), chGood);
        TH1F* hRatioGood = (TH1F*)gDirectory->Get(htemp.c_str());
        hRatioGood->SetTitle("Good");
        hRatioGood->SetFillColor(kBlue);

        htemp = "hRatioBad" + eras[i];
        plot = ratio_ICxLC+">>"+htemp+ratioBins;
        calib->Draw(plot.c_str(), isBad && chGood);
        TH1F* hRatioBad = (TH1F*)gDirectory->Get(htemp.c_str());
        hRatioBad->SetTitle("Bad");
        hRatioBad->SetFillColor(kOrange);

        htemp = "hRatioWorst" + eras[i];
        plot = ratio_ICxLC+">>"+htemp+ratioBins;
        calib->Draw(plot.c_str(), isBad && "iworst==1" && chGood);
        TH1F* hRatioWorst = (TH1F*)gDirectory->Get(htemp.c_str());
        hRatioWorst->SetTitle("Worst");
        hRatioWorst->SetFillColor(kRed);

        // EE Map
        htemp = "hEEMap"+eras[i];
        plot = "iy-0.5:ix-0.5+100*(iz>0)>>"+htemp+"(200,0,200,100,0,100)";
        calib->Draw(plot.c_str(), (ratio_ICxLC+"*("+UL_ICxLC+"!=0)*(chStatus==0)").c_str());
        TH2F *hEEMap = (TH2F*)gDirectory->Get(htemp.c_str());
        hEEMap->SetTitle(("IC*LC^(alpha) | Ratio" + eras[i] + " (EOY/UL)").c_str());
        hEEMap->GetXaxis()->SetTitle("ix + 100*(iz>0)");
        hEEMap->GetYaxis()->SetTitle("iy");
        hEEMap->SetMinimum(0.0);
        hEEMap->SetMaximum(3.0);

        // EtaPhi Map
        htemp = "hNorm"+eras[i];
        plot = "phi:-eta>>"+htemp+"(100,-5.0,5.0,100,-3.1416,3.1416)";
        calib->Draw(plot.c_str(), chGood);
        TH2F *hNorm = (TH2F*)gDirectory->Get(htemp.c_str());
        
        htemp = "hEtaPhi"+eras[i];
        plot = "phi:-eta>>"+htemp+"(100,-5.0,5.0,100,-3.1416,3.1416)";
        calib->Draw(plot.c_str(), (ratio_ICxLC+"*(chStatus==0)").c_str());
        TH2F *hEtaPhi = (TH2F*)gDirectory->Get(htemp.c_str());
        hEtaPhi->Divide(hNorm);
        hEtaPhi->SetTitle(("IC*LC^(alpha) Ratio " + eras[i]).c_str());
        hEtaPhi->GetXaxis()->SetTitle("#eta");
        hEtaPhi->GetYaxis()->SetTitle("#phi");
        hEtaPhi->SetMinimum(0.0);
        hEtaPhi->SetMaximum(3.0);

        // Iring Ratio Map
        htemp = "hIring"+eras[i];
        plot = ratio_ICxLC+":iring*iz>>"+htemp+"(80,-40,40,60,0,3)";
        calib->Draw(plot.c_str(), chGood);
        TH2F* hIring = (TH2F*)gDirectory->Get(htemp.c_str());
        hIring->SetTitle(("IC*LC^(alpha) | Ratio"+eras[i]+" (EOY/UL) by iring").c_str());
        hIring->GetXaxis()->SetTitle("iring");
        hIring->GetYaxis()->SetTitle("Ratio (EOY/UL)");
        hIring->SetMinimum(0.1);
        hIring->SetMaximum(1000);

        htemp = "hIringBad"+eras[i];
        plot = ratio_ICxLC+":iring*iz>>"+htemp+"(80,-40,40,60,0,3)";
        calib->Draw(plot.c_str(), isBad && chGood);
        TH2F *hIringBad = (TH2F*)gDirectory->Get(htemp.c_str());
        hIringBad->Scale(100);

        // High Eta Vs
        htemp = "hHighEta"+eras[i];
        plot = EOY_ICxLC+":"+UL_ICxLC+">>"+htemp+"(60,0,60,60,0,60)";
        calib->Draw(plot.c_str(), chGood && "iring>=35");
        TH2F *hHighEta = (TH2F*)gDirectory->Get(htemp.c_str());
        hHighEta->SetTitle(("IC*LC^(alpha) | "+eras[i]+" EOY vs UL | abs(iring) >= 35").c_str());
        hHighEta->GetXaxis()->SetTitle((eras[i]+" UL").c_str());
        hHighEta->GetYaxis()->SetTitle((eras[i]+" EOY").c_str());
        hHighEta->SetMinimum(0.1);
        hHighEta->SetMaximum(50);

        htemp = "hHighEtaBad"+eras[i];
        plot = EOY_ICxLC+":"+UL_ICxLC+">>"+htemp+"(60,0,60,60,0,60)";
        calib->Draw(plot.c_str(), chGood && "iring >=35" && isBad);
        TH2F *hHighEtaBad = (TH2F*)gDirectory->Get(htemp.c_str());
        hHighEtaBad->Scale(9);

        TLine *slope1 = new TLine(0,0,60,60);
        TLine *slope2 = new TLine(0,0,30,60);
        TLine *slope3 = new TLine(0,0,20,60);

        // Draw and save plots
        cEOY->cd();
        cEOY->SetLogy();
        string hsName = "ICxLC_EOY" + eras[i];
        string hsTitle = "IC*LC^(alpha) | EOY" + eras[i];
        THStack *hsEOY = new THStack(hsName.c_str(), hsTitle.c_str());
        hsEOY->Add(hEOYGood);
        hsEOY->Add(hEOYBad);
        hsEOY->Add(hEOYWorst);
        hsEOY->Draw("nostack");
        hsEOY->SetMinimum(0.5);
        hsEOY->SetMaximum(14648);
        hsEOY->GetXaxis()->SetTitle("IC*LC^(alpha)");
        hsEOY->GetYaxis()->SetTitle("EE Xtal Occupancy");
        cEOY->BuildLegend(0.7, 0.7, 0.9, 0.9);
        cEOY->SaveAs(("img/calibEOY"+eras[i]+".png").c_str());

        cUL->cd();
        cUL->SetLogy();
        hsName = "ICxLC_UL" + eras[i];
        hsTitle = "IC*LC^(alpha) | UL" + eras[i];
        THStack *hsUL = new THStack(hsName.c_str(), hsTitle.c_str());
        hsUL->Add(hULGood);
        hsUL->Add(hULBad);
        hsUL->Add(hULWorst);
        hsUL->Draw("nostack");
        hsUL->SetMinimum(0.5);
        hsUL->SetMaximum(14648);
        hsUL->GetXaxis()->SetTitle("IC*LC^(alpha)");
        hsUL->GetYaxis()->SetTitle("EE Xtal Occupancy");
        cUL->BuildLegend(0.7, 0.7, 0.9, 0.9);
        cUL->SaveAs(("img/calibUL"+eras[i]+".png").c_str());

        cRatio->cd();
        cRatio->SetLogy();
        hsName = "ICxLC_Ratio" + eras[i];
        hsTitle = "IC*LC^(alpha) | Ratio" + eras[i] + " (EOY/UL)";
        THStack *hsRatio = new THStack(hsName.c_str(), hsTitle.c_str());
        hsRatio->Add(hRatioGood);
        hsRatio->Add(hRatioBad);
        hsRatio->Add(hRatioWorst);
        hsRatio->Draw("nostack");
        hsRatio->SetMinimum(0.5);
        hsRatio->SetMaximum(14648);
        hsRatio->GetXaxis()->SetTitle("(IC*LC^(alpha) EOY)/(IC*LC^(alpha) UL)");
        hsRatio->GetYaxis()->SetTitle("EE Xtal Occupancy");
        cRatio->BuildLegend(0.7, 0.7, 0.9, 0.9);
        cRatio->SaveAs(("img/calibRatio"+eras[i]+".png").c_str());

        cEEMap->cd();
        hEEMap->Draw("colz");
        cEEMap->SaveAs(("img/calibEEMap"+eras[i]+".png").c_str());

        cEtaPhi->cd();
        cEtaPhi->SetRightMargin(0.15);
        hEtaPhi->Draw("colz");
        cEtaPhi->SaveAs(("img/calibEtaPhi"+eras[i]+".png").c_str());

        cIring->cd();
        cIring->SetLogz();
        hIring->Draw("colz");
        hIringBad->Draw("box same");
        cIring->SaveAs(("img/calibIring"+eras[i]+".png").c_str());

        cHighEta->cd();
        cHighEta->SetLogz();
        hHighEta->Draw("colz");
        hHighEtaBad->Draw("box same");
        slope1->Draw("same");
        slope2->Draw("same");
        slope3->Draw("same");
        cHighEta->SaveAs(("img/calibHighEta"+eras[i]+".png").c_str());
    }
}
