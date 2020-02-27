#include <iostream>
#include <cstdlib>

#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TPad.h>
#include <TStyle.h>

using namespace std;

// studies using Amandeep's ROOT files as inputs ///////////////////////
void occStudies(){

    bool cropEE = true;
    float intEOY, intUL;

    TFile* f_2018A = TFile::Open("Out_Comp_2018A.root");
    TFile* f_2018C = TFile::Open("Out_Comp_2018C.root");
    TFile* f_2018D = TFile::Open("Out_Comp_2018D.root");

    gStyle->SetOptStat(0);
    gStyle->SetPalette(1);
    TCanvas* cc = new TCanvas("cc", "cc", 800, 800);
    cc->SetRightMargin(0.125); // avoid cutting out right margin of plots

    // Get EE Crystal Locations in Eta-Phi Map /////////////////////////
    TFile* f_eeCalib = TFile::Open("eeCalib.root");
    TTree* eeCalib;
    f_eeCalib->GetObject("eeCalib", eeCalib);
    eeCalib->Draw("phi:-eta>>hNorm(200,-5,5,200,-3.1416,3.1416)", "chStatus==0", "colz");
    TH2F* hNorm = (TH2F*)gDirectory->Get("hNorm");
    TH2F* hIsEE = (TH2F*)hNorm->Clone("hIsEE");
    hIsEE->Divide(hIsEE);

    // 2018A //////////////////////////////////////////////////////////
    TH2F* h_EOY2018A;
    TH2F* h_UL2018A;
    f_2018A->GetObject("Sept17h_jet200etavsphi_pass", h_EOY2018A);
    f_2018A->GetObject("106Xh_jet200etavsphi_pass", h_UL2018A);

    if (cropEE) h_EOY2018A->Multiply(hIsEE);
    intEOY = h_EOY2018A->Integral();
    h_EOY2018A->Scale(1.f/intEOY);
    h_EOY2018A->SetMaximum(0.001);
    h_EOY2018A->GetXaxis()->SetTitle("#eta");
    h_EOY2018A->GetYaxis()->SetTitle("#phi");
    h_EOY2018A->SetTitle("EE Occupancy EOY2018A");
    h_EOY2018A->Draw("colz");
    cc->SaveAs("img/Occ2018A_EOY.pdf");

    if (cropEE) h_UL2018A->Multiply(hIsEE);
    intUL = h_UL2018A->Integral();
    h_UL2018A->Scale(1.f/intUL);
    h_UL2018A->SetMaximum(0.001);
    h_UL2018A->GetXaxis()->SetTitle("#eta");
    h_UL2018A->GetYaxis()->SetTitle("#phi");
    h_UL2018A->SetTitle("EE Occupancy UL2018A");
    h_UL2018A->Draw("colz");
    cc->SaveAs("img/Occ2018A_UL.pdf");

    TH2F* h_Ratio2018A = (TH2F*)h_EOY2018A->Clone("h_Ratio2018A");
    h_Ratio2018A->Divide(h_UL2018A);
    h_Ratio2018A->SetMaximum(3);
    h_Ratio2018A->GetXaxis()->SetTitle("#eta");
    h_Ratio2018A->GetYaxis()->SetTitle("#phi");
    h_Ratio2018A->SetTitle("EE Occupancy Ratio 2018A");
    h_Ratio2018A->Draw("colz");
    cc->SaveAs("img/Occ2018A_Ratio.pdf");

    // 2018C //////////////////////////////////////////////////////////
    TH2F* h_EOY2018C;
    TH2F* h_UL2018C;
    f_2018C->GetObject("Sept17h_jet200etavsphi_pass", h_EOY2018C);
    f_2018C->GetObject("106Xh_jet200etavsphi_pass", h_UL2018C);

    if (cropEE) h_EOY2018C->Multiply(hIsEE);
    intEOY = h_EOY2018C->Integral();
    h_EOY2018C->Scale(1.f/intEOY);
    h_EOY2018C->SetMaximum(0.001);
    h_EOY2018C->GetXaxis()->SetTitle("#eta");
    h_EOY2018C->GetYaxis()->SetTitle("#phi");
    h_EOY2018C->SetTitle("EE Occupancy EOY2018C");
    h_EOY2018C->Draw("colz");
    cc->SaveAs("img/Occ2018C_EOY.pdf");

    if (cropEE) h_UL2018C->Multiply(hIsEE);
    intUL = h_UL2018C->Integral();
    h_UL2018C->Scale(1.f/intUL);
    h_UL2018C->SetMaximum(0.001);
    h_UL2018C->GetXaxis()->SetTitle("#eta");
    h_UL2018C->GetYaxis()->SetTitle("#phi");
    h_UL2018C->SetTitle("EE Occupancy UL2018C");
    h_UL2018C->Draw("colz");
    cc->SaveAs("img/Occ2018C_UL.pdf");

    TH2F* h_Ratio2018C = (TH2F*)h_EOY2018C->Clone("h_Ratio2018C");
    h_Ratio2018C->Divide(h_UL2018C);
    h_Ratio2018C->SetMaximum(3);
    h_Ratio2018C->GetXaxis()->SetTitle("#eta");
    h_Ratio2018C->GetYaxis()->SetTitle("#phi");
    h_Ratio2018C->SetTitle("EE Occupancy Ratio 2018C");
    h_Ratio2018C->Draw("colz");
    cc->SaveAs("img/Occ2018C_Ratio.pdf");

    // 2018D ///////////////////////////////////////////////////////////
    TH2F* h_EOY2018D;
    TH2F* h_UL2018D;
    f_2018D->GetObject("Prompth_jet200etavsphi_pass", h_EOY2018D);
    f_2018D->GetObject("106Xh_jet200etavsphi_pass", h_UL2018D);

    if (cropEE) h_EOY2018D->Multiply(hIsEE);
    intEOY = h_EOY2018D->Integral();
    //h_EOY2018D->Scale(1.f/intEOY);
    h_EOY2018D->SetMaximum(1000);
    h_EOY2018D->GetXaxis()->SetTitle("#eta");
    h_EOY2018D->GetYaxis()->SetTitle("#phi");
    //h_EOY2018D->GetZaxis()->SetTitle("num rechits");
    h_EOY2018D->SetTitle("EE Occupancy EOY2018D");
    h_EOY2018D->Draw("colz");
    cc->SaveAs("img/Occ2018D_EOY.pdf");

    if (cropEE) h_UL2018D->Multiply(hIsEE);
    intUL = h_UL2018D->Integral();
    //h_UL2018D->Scale(1.f/intUL);
    h_UL2018D->SetMaximum(1000);
    h_UL2018D->GetXaxis()->SetTitle("#eta");
    h_UL2018D->GetYaxis()->SetTitle("#phi");
    //h_UL2018D->GetZaxis()->SetTitle("num rechits");
    h_UL2018D->SetTitle("EE Occupancy UL2018D");
    h_UL2018D->Draw("colz");
    cc->SaveAs("img/Occ2018D_UL.pdf");

    TH2F* h_Ratio2018D = (TH2F*)h_EOY2018D->Clone("h_Ratio2018D");
    h_Ratio2018D->Divide(h_UL2018D);
    h_Ratio2018D->SetMaximum(5);
    h_Ratio2018D->GetXaxis()->SetTitle("#eta");
    h_Ratio2018D->GetYaxis()->SetTitle("#phi");
    //h_Ratio2018D->GetZaxis()->SetTitle("EOY/UL Occupancy Ratio");
    h_Ratio2018D->SetTitle("EE Occupancy Ratio 2018D");
    h_Ratio2018D->Draw("colz");
    cc->SaveAs("img/Occ2018D_Ratio.pdf");

    // Calib Ratio vs Occ Ratio ///////////////////////////////////////
    TCanvas* c2 = new TCanvas("c2", "c2", 1000, 600);
    c2->SetRightMargin(0.15);
    c2->SetLogz();

    // 2018A //////////////
    eeCalib->Draw("phi:-eta>>h_Calib2018A(200,-5,5,200,-3.1416,3.1416","(IC_EOY2018A*LC_EOY2018A)/(IC_UL2018A*LC_UL2018A)*(chStatus==0)");
    TH2F* h_Calib2018A = (TH2F*)gDirectory->Get("h_Calib2018A");
    h_Calib2018A->Divide(hNorm);

    TH2F* h_VS2018A = new TH2F("h_VS2018A","h_VS2018A",100,0,5,60,0,3);
    for (int i=1; i<=40000; i++){
        double cal = h_Calib2018A->GetBinContent(i);
        double occ = h_Ratio2018A->GetBinContent(i);
        if (cal==0 || occ==0) continue;
        h_VS2018A->Fill(occ,cal);
    }
    h_VS2018A->GetXaxis()->SetTitle("Occupancy Ratio");
    h_VS2018A->GetYaxis()->SetTitle("IC*LC^(alpha) Ratio");
    h_VS2018A->GetZaxis()->SetTitle("Bin Counts");
    h_VS2018A->SetTitle("IC*LC^(alpha) Ratio vs Occupancy Ratio 2018A");
    h_VS2018A->SetMaximum(1000);

    cout << "2018A:" << endl;
    cout << "Correlation Factor: " << h_VS2018A->GetCorrelationFactor() << endl;
    cout << "Covariance" << h_VS2018A->GetCovariance() << endl;
    cout << endl;
    h_VS2018A->Draw("colz");
    c2->SaveAs("img/ratioVS_2018A.pdf");

    // 2018C //////////////
    eeCalib->Draw("phi:-eta>>h_Calib2018C(200,-5,5,200,-3.1416,3.1416","(IC_EOY2018C*LC_EOY2018C)/(IC_UL2018C*LC_UL2018C)*(chStatus==0)");
    TH2F* h_Calib2018C = (TH2F*)gDirectory->Get("h_Calib2018C");
    h_Calib2018C->Divide(hNorm);

    TH2F* h_VS2018C = new TH2F("h_VS2018C","h_VS2018C",100,0,5,60,0,3);
    for (int i=1; i<=40000; i++){
        double cal = h_Calib2018C->GetBinContent(i);
        double occ = h_Ratio2018C->GetBinContent(i);
        if (cal==0 || occ==0) continue;
        h_VS2018C->Fill(occ,cal);
    }
    h_VS2018C->GetXaxis()->SetTitle("Occupancy Ratio");
    h_VS2018C->GetYaxis()->SetTitle("IC*LC^(alpha) Ratio");
    h_VS2018C->GetZaxis()->SetTitle("Bin Counts");
    h_VS2018C->SetTitle("IC*LC^(alpha) Ratio vs Occupancy Ratio 2018C");
    h_VS2018C->SetMaximum(1000);

    cout << "2018C:" << endl;
    cout << "Correlation Factor: " << h_VS2018C->GetCorrelationFactor() << endl;
    cout << "Covariance" << h_VS2018C->GetCovariance() << endl;
    cout << endl;
    h_VS2018C->Draw("colz");
    c2->SaveAs("img/ratioVS_2018C.pdf");

    // 2018D //////////////
    eeCalib->Draw("phi:-eta>>h_Calib2018D(200,-5,5,200,-3.1416,3.1416","(IC_EOY2018D*LC_EOY2018D)/(IC_UL2018D*LC_UL2018D)*(chStatus==0)");
    //eeCalib->Draw("phi:-eta>>h_Calib2018D(200,-5,5,200,-3.1416,3.1416","(LC_EOY2018D)/(LC_UL2018D)*(chStatus==0)");
    TH2F* h_Calib2018D = (TH2F*)gDirectory->Get("h_Calib2018D");
    h_Calib2018D->Divide(hNorm);

    TH2F* h_VS2018D = new TH2F("h_VS2018D","h_VS2018D",100,0,5,60,0,3);
    for (int i=1; i<=40000; i++){
        double cal = h_Calib2018D->GetBinContent(i);
        double occ = h_Ratio2018D->GetBinContent(i);
        if (cal==0 || occ==0) continue;
        h_VS2018D->Fill(occ,cal);
    }
    h_VS2018D->GetXaxis()->SetTitle("Occupancy Ratio");
    h_VS2018D->GetYaxis()->SetTitle("IC*LC^(alpha) Ratio");
    h_VS2018D->GetZaxis()->SetTitle("Bin Counts");
    h_VS2018D->SetTitle("IC*LC^(alpha) Ratio vs Occupancy Ratio 2018D");
    h_VS2018D->SetMaximum(1000);

    cout << "2018D:" << endl;
    cout << "Correlation Factor: " << h_VS2018D->GetCorrelationFactor() << endl;
    cout << "Covariance" << h_VS2018D->GetCovariance() << endl;
    cout << endl;
    h_VS2018D->Draw("colz");
    c2->SaveAs("img/ratioVS_2018D.pdf");

    // Calibration Ratio vs Prompt Occupancies //////////////////////////////////
    cc->cd();
    cc->SetLogz();

    // 2018A //////////////
    TH2F* h_PromptVS2018A = new TH2F("h_PromptVS2018A", "IC*LC^(alpha) Ratio vs EOY Occupancy 2018A", 60, 0, 0.001, 60, 0, 3);
    for (int i=1; i<=40000; i++){
        double cal = h_Calib2018A->GetBinContent(i);
        double occ = h_EOY2018A->GetBinContent(i);
        if (cal==0 || occ==0) continue;
        h_PromptVS2018A->Fill(occ, cal);
    }
    h_PromptVS2018A->GetXaxis()->SetTitle("Normalized EOY Occupancy");
    h_PromptVS2018A->GetYaxis()->SetTitle("IC*LC^(alpha) Ratio");
    h_PromptVS2018A->GetZaxis()->SetTitle("Bin Counts");
    h_PromptVS2018A->SetMaximum(1000);
    TGaxis::SetMaxDigits(2);
    h_PromptVS2018A->Draw("colz");
    cc->SaveAs("img/promptsVS_2018A.pdf");

    // 2018C //////////////
    TH2F* h_PromptVS2018C = new TH2F("h_PromptVS2018C", "IC*LC^(alpha) Ratio vs EOY Occupancy 2018C", 60, 0, 0.001, 60, 0, 3);
    for (int i=1; i<=40000; i++){
        double cal = h_Calib2018C->GetBinContent(i);
        double occ = h_EOY2018C->GetBinContent(i);
        if (cal==0 || occ==0) continue;
        h_PromptVS2018C->Fill(occ, cal);
    }
    h_PromptVS2018C->GetXaxis()->SetTitle("Normalized EOY Occupancy");
    h_PromptVS2018C->GetYaxis()->SetTitle("IC*LC^(alpha) Ratio");
    h_PromptVS2018C->GetZaxis()->SetTitle("Bin Counts");
    h_PromptVS2018C->SetMaximum(1000);
    TGaxis::SetMaxDigits(2);
    h_PromptVS2018C->Draw("colz");
    cc->SaveAs("img/promptsVS_2018C.pdf");

    // 2018D //////////////
    TH2F* h_PromptVS2018D = new TH2F("h_PromptVS2018D", "IC*LC^(alpha) Ratio vs EOY Occupancy 2018D", 60, 0, 0.001, 60, 0, 3);
    for (int i=1; i<=40000; i++){
        double cal = h_Calib2018D->GetBinContent(i);
        double occ = h_EOY2018D->GetBinContent(i);
        if (cal==0 || occ==0) continue;
        h_PromptVS2018D->Fill(occ, cal);
    }
    h_PromptVS2018D->GetXaxis()->SetTitle("Normalized EOY Occupancy");
    h_PromptVS2018D->GetYaxis()->SetTitle("IC*LC^(alpha) Ratio");
    h_PromptVS2018D->GetZaxis()->SetTitle("Bin Counts");
    h_PromptVS2018D->SetMaximum(1000);
    TGaxis::SetMaxDigits(2);
    h_PromptVS2018D->Draw("colz");
    cc->SaveAs("img/promptsVS_2018D.pdf");

    // 2018D IC*LC vs Occupancies for high eta ///////////////////////////////////
    TGaxis::SetMaxDigits();
    TCanvas* c3 = new TCanvas("c3", "c3", 1600, 1200);
    c3->SetRightMargin(0.15);

    // set eta range here
    eeCalib->Draw("phi:-eta>>h_HighEtaEE(200,-5,5,200,-3.1416,3.1416)", "chStatus==0 && abs(eta)>2.5", "colz"); // EDIT HERE
    TH2F* h_HighEtaEE = (TH2F*)gDirectory->Get("h_HighEtaEE");
    h_HighEtaEE->Divide(h_HighEtaEE);

    // get indiv calib values for EOY and UL
    eeCalib->Draw("phi:-eta>>h_CalibEOY2018D(200,-5,5,200,-3.1416,3.1416)", "(IC_EOY2018D*LC_EOY2018D)*(chStatus==0)", "colz");
    TH2F* h_CalibEOY2018D = (TH2F*)gDirectory->Get("h_CalibEOY2018D");
    h_CalibEOY2018D->Divide(hNorm);
    
    eeCalib->Draw("phi:-eta>>h_CalibUL2018D(200,-5,5,200,-3.1416,3.1416)", "(IC_UL2018D*LC_UL2018D)*(chStatus==0)", "colz");
    TH2F* h_CalibUL2018D = (TH2F*)gDirectory->Get("h_CalibUL2018D");
    h_CalibUL2018D->Divide(hNorm);

    // LC
    eeCalib->Draw("phi:-eta>>h_LC_EOY2018D(200,-5,5,200,-3.1416,3.1416)", "(LC_EOY2018D)*(chStatus==0)", "colz");
    TH2F* h_LC_EOY2018D = (TH2F*)gDirectory->Get("h_LC_EOY2018D");
    h_LC_EOY2018D->Divide(hNorm);
    
    eeCalib->Draw("phi:-eta>>h_LC_UL2018D(200,-5,5,200,-3.1416,3.1416)", "(LC_UL2018D)*(chStatus==0)", "colz");
    TH2F* h_LC_UL2018D = (TH2F*)gDirectory->Get("h_LC_UL2018D");
    h_LC_UL2018D->Divide(hNorm);

    h_EOY2018D->Scale(intEOY);
    h_UL2018D->Scale(intUL);
    h_Ratio2018D = (TH2F*)h_EOY2018D->Clone("h_Ratio2018Dv2");
    h_Ratio2018D->Divide(h_UL2018D);

    // Keep only eta range
    h_Calib2018D->Multiply(h_HighEtaEE);
    h_Ratio2018D->Multiply(h_HighEtaEE);
    h_EOY2018D->Multiply(h_HighEtaEE);
    h_UL2018D->Multiply(h_HighEtaEE);
    h_CalibEOY2018D->Multiply(h_HighEtaEE);
    h_CalibUL2018D->Multiply(h_HighEtaEE);
    h_LC_EOY2018D->Multiply(h_HighEtaEE);
    h_LC_UL2018D->Multiply(h_HighEtaEE);

    // Calib values vs Occupancy Ratio ///////////////////////////
    TH2F* h_EOYHighEta = new TH2F("h_EOYHighEta", "EE EOY IC*LC vs Occupancy Ratio 2018D |eta|>2.5", 80, 0, 8, 60, 0, 60); // EDIT HERE
    TH2F* h_ULHighEta = new TH2F("h_ULHighEta", "EE UL IC*LC vs Occupancy Ratio 2018D |eta|>2.5", 80, 0, 8, 60, 0, 60); // EDIT HERE
    for (int i=1; i<=40000; i++){
        double eoy = h_CalibEOY2018D->GetBinContent(i);
        double ul = h_CalibUL2018D->GetBinContent(i);
        double occRatio = h_Ratio2018D->GetBinContent(i);
        if (occRatio!=0 && eoy!=0) h_EOYHighEta->Fill(occRatio, eoy);
        if (occRatio!=0 && ul!=0) h_ULHighEta->Fill(occRatio, ul);
    }
    c3->cd();
    c3->SetLogz(0);

    h_EOYHighEta->SetMaximum(20);
    h_EOYHighEta->GetXaxis()->SetTitle("EOY/UL Occupancy Ratio");
    h_EOYHighEta->GetYaxis()->SetTitle("EOY IC*LC");
    h_EOYHighEta->GetZaxis()->SetTitle("Bin Counts");
    h_EOYHighEta->Draw("colz");
    c3->SaveAs("img/highEta/HighEta_EOYCalibVsOccRatio_2018D.pdf"); //EDIT HERE

    h_ULHighEta->SetMaximum(20);
    h_ULHighEta->GetXaxis()->SetTitle("EOY/UL Occupancy Ratio");
    h_ULHighEta->GetYaxis()->SetTitle("UL IC*LC");
    h_ULHighEta->GetZaxis()->SetTitle("Bin Counts");
    h_ULHighEta->Draw("colz");
    c3->SaveAs("img/highEta/HighEta_ULCalibVsOccRatio_2018D.pdf"); //EDIT HERE

    h_EOYHighEta->SetTitle("EE IC*LC vs Occupancy Ratio 2018D |eta|>2.5"); //EDIT HERE
    h_EOYHighEta->GetYaxis()->SetTitle("IC*LC");
    h_EOYHighEta->SetLineColor(kRed);
    h_ULHighEta->SetLineColor(kBlue);
    h_EOYHighEta->Draw("box");
    h_ULHighEta->Draw("box same");

    TLegend* legend = new TLegend(0.70,0.75,0.85,0.90);
    legend->AddEntry(h_EOYHighEta, "EOY");
    legend->AddEntry(h_ULHighEta, "UL");
    legend->Draw();
    c3->SaveAs("img/highEta/HighEta_CombCalibVsOccRatio_2018D.pdf"); // EDIT HERE

    //THStack* ts_CombHighEta = new THStack("ts_CombHighEta", "EE IC*LC vs Occupancy Ratio 2018D |eta|>2.5");
    //ts_CombHighEta->Add(h_EOYHighEta, "box");
    //ts_CombHighEta->Add(h_ULHighEta, "box");
    //ts_CombHighEta->Draw("nostack");
    //ts_CombHighEta->GetXaxis()->SetTitle("EOY/UL Occupancy Ratio");
    //ts_CombHighEta->GetYaxis()->SetTitle("2018D IC*LC");
    //gPad->BuildLegend(0.70,0.75,0.85,0.90,"");
    //c3->SaveAs("img/highEta/HighEta_CombCalibVsOccRatio_2018D.pdf");

    // eta slices
    //eeCalib->Draw("iring", "abs(eta)>2.5")
    

/*
    // Calib Ratio vs Occupancy Values ///////////////////////////
    TCanvas* c4 = new TCanvas("c4", "c4", 1800, 1400);
    c4->SetRightMargin(0.15);

    TH2F* h_EOYHighEta2 = new TH2F("h_EOYHighEta2", "EE EOY IC*LC vs Occupancy Ratio 2018D |eta|>2.5", 90, 0, 1800, 70, 0, 3.5);
    TH2F* h_ULHighEta2 = new TH2F("h_ULHighEta2", "EE UL IC*LC vs Occupancy Ratio 2018D |eta|>2.5", 90, 0, 1800, 70, 0, 3.5);
    for (int i=1; i<=40000; i++){
        double calRatio = h_Calib2018D->GetBinContent(i);
        double eoy = h_EOY2018D->GetBinContent(i);
        double ul = h_UL2018D->GetBinContent(i);
        if (calRatio!=0 && eoy!=0) h_EOYHighEta2->Fill(eoy, calRatio);
        if (calRatio!=0 && ul!=0) h_ULHighEta2->Fill(ul, calRatio);
    }

    h_EOYHighEta2->SetMaximum(40);
    h_EOYHighEta2->GetXaxis()->SetTitle("EOY Occupancy");
    h_EOYHighEta2->GetYaxis()->SetTitle("EOY/UL IC*LC Ratio");
    h_EOYHighEta2->GetZaxis()->SetTitle("Bin Counts");
    h_EOYHighEta2->Draw("colz");
    c4->SaveAs("img/highEta/HighEta2_EOYCalibVsOccRatio_2018D.pdf");

    h_ULHighEta2->SetMaximum(40);
    h_ULHighEta2->GetXaxis()->SetTitle("UL Occupancy");
    h_ULHighEta2->GetYaxis()->SetTitle("EOY/UL IC*LC Ratio");
    h_ULHighEta2->GetZaxis()->SetTitle("Bin Counts");
    h_ULHighEta2->Draw("colz");
    c4->SaveAs("img/highEta/HighEta2_ULCalibVsOccRatio_2018D.pdf");

    h_EOYHighEta2->SetLineColor(kRed);
    h_EOYHighEta2->SetTitle("EOY");
    h_ULHighEta2->SetLineColor(kBlue);
    h_ULHighEta2->SetTitle("UL");

    THStack* ts_CombHighEta2 = new THStack("ts_CombHighEta2", "EE IC*LC vs Occupancy Ratio 2018D |eta|>2.5");
    ts_CombHighEta2->Add(h_EOYHighEta2, "box");
    ts_CombHighEta2->Add(h_ULHighEta2, "box");
    ts_CombHighEta2->Draw("nostack");
    ts_CombHighEta2->GetXaxis()->SetTitle("2018D Occupancy");
    ts_CombHighEta2->GetYaxis()->SetTitle("EOY/UL IC*LC Ratio");
    gPad->BuildLegend(0.70,0.75,0.85,0.90,"");
    c4->SaveAs("img/highEta/HighEta2_CombCalibVsOccRatio_2018D.pdf");
*/

/*
    // Only LC values vs Occupancy Ratio ///////////////////////////
    TH2F* h_EOYHighEta = new TH2F("h_EOYHighEta", "EE EOY LC vs Occupancy Ratio 2018D |eta|>2.5", 80, 0, 16, 60, 0, 60);
    TH2F* h_ULHighEta = new TH2F("h_ULHighEta", "EE UL LC vs Occupancy Ratio 2018D |eta|>2.5", 80, 0, 16, 60, 0, 60);
    for (int i=1; i<=40000; i++){
        double eoy = h_CalibEOY2018D->GetBinContent(i);
        double ul = h_CalibUL2018D->GetBinContent(i);
        double occRatio = h_Ratio2018D->GetBinContent(i);
        if (occRatio!=0 && eoy!=0) h_EOYHighEta->Fill(occRatio, eoy);
        if (occRatio!=0 && ul!=0) h_ULHighEta->Fill(occRatio, ul);
    }
    c3->cd();
    c3->SetLogz(0);

    h_EOYHighEta->SetMaximum(40);
    h_EOYHighEta->GetXaxis()->SetTitle("EOY/UL Occupancy Ratio");
    h_EOYHighEta->GetYaxis()->SetTitle("EOY IC*LC");
    h_EOYHighEta->GetZaxis()->SetTitle("Bin Counts");
    h_EOYHighEta->Draw("colz");
    c3->SaveAs("img/highEta/HighEta3_EOYCalibVsOccRatio_2018D.pdf");

    h_ULHighEta->SetMaximum(40);
    h_ULHighEta->GetXaxis()->SetTitle("EOY/UL Occupancy Ratio");
    h_ULHighEta->GetYaxis()->SetTitle("UL IC*LC");
    h_ULHighEta->GetZaxis()->SetTitle("Bin Counts");
    h_ULHighEta->Draw("colz");
    c3->SaveAs("img/highEta/HighEta3_ULCalibVsOccRatio_2018D.pdf");

    h_EOYHighEta->SetLineColor(kRed);
    h_EOYHighEta->SetTitle("EOY");
    h_ULHighEta->SetLineColor(kBlue);
    h_ULHighEta->SetTitle("UL");

    THStack* ts_CombHighEta = new THStack("ts_CombHighEta", "EE IC*LC vs Occupancy Ratio 2018D |eta|>2.5");
    ts_CombHighEta->Add(h_EOYHighEta, "box");
    ts_CombHighEta->Add(h_ULHighEta, "box");
    ts_CombHighEta->Draw("nostack");
    ts_CombHighEta->GetXaxis()->SetTitle("EOY/UL Occupancy Ratio");
    ts_CombHighEta->GetYaxis()->SetTitle("2018D IC*LC");
    gPad->BuildLegend(0.70,0.75,0.85,0.90,"");
    c3->SaveAs("img/highEta/HighEta3_CombCalibVsOccRatio_2018D.pdf");
*/
}

