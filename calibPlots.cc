void calibPlots(){

    TFile* f_eeCalib = TFile::Open("eeCalib.root");
    TTree* eeCalib;
    f_eeCalib->GetObject("eeCalib", eeCalib);

    TFile* f_calibPlots = new TFile("img/calib/calibPlots.root", "RECREATE");

    gStyle->SetOptStat(0);
    gStyle->SetPalette(1);
    TCanvas* cc = new TCanvas("cc", "cc", 800, 800);
    cc->SetRightMargin(0.125);

    eeCalib->Draw("phi:-eta>>hNorm(200,-5,5,200,-3.1416,3.1416)", "(chStatus==0)");
    TH2F* hNorm = (TH2F*)gDirectory->Get("hNorm");
    hNorm->Write();

    eeCalib->Draw("phi:-eta>>hEOYCalib(200,-5,5,200,-3.1416,3.1416)", "IC_EOY2018D*LC_EOY2018D*(chStatus==0)");
    TH2F* hEOYCalib = (TH2F*)gDirectory->Get("hEOYCalib");
    hEOYCalib->Divide(hNorm);
    hEOYCalib->GetXaxis()->SetTitle("#eta");
    hEOYCalib->GetYaxis()->SetTitle("#phi");
    hEOYCalib->SetTitle("EOY2018D IC*LC");
    hEOYCalib->SetMaximum(30);
    hEOYCalib->Draw("colz");
    cc->SaveAs("img/calib/EOY2018D.pdf");
    hEOYCalib->Write();

    eeCalib->Draw("phi:-eta>>hULCalib(200,-5,5,200,-3.1416,3.1416)", "IC_UL2018D*LC_UL2018D*(chStatus==0)");
    TH2F* hULCalib = (TH2F*)gDirectory->Get("hULCalib");
    hULCalib->Divide(hNorm);
    hULCalib->GetXaxis()->SetTitle("#eta");
    hULCalib->GetYaxis()->SetTitle("#phi");
    hULCalib->SetTitle("UL2018D IC*LC");
    hULCalib->SetMaximum(30);
    hULCalib->Draw("colz");
    cc->SaveAs("img/calib/UL2018D.pdf");
    hULCalib->Write();

    TH2F* hRatio = (TH2F*)hEOYCalib->Clone("hRatio");
    hRatio->Divide(hULCalib);
    hRatio->SetTitle("2018D IC*LC EOY/UL Ratio");
    hRatio->SetMaximum(3);
    hRatio->Draw("colz");
    cc->SaveAs("img/calib/ZRatio2018D.pdf");
    hRatio->Write();
}
