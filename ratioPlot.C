void ratioPlot()
{
    // -----------------------------
    // Histograms
    // -----------------------------
    TH1D* h1 = new TH1D("h1", "", 100, -5, 5);
    TH1D* h2 = new TH1D("h2", "", 100, -5, 5);

    h1->FillRandom("gaus", 10000);
    h2->FillRandom("gaus", 10000);

    h1->SetLineColor(kBlue);
    h1->SetLineWidth(2);

    h2->SetLineColor(kRed);
    h2->SetLineWidth(2);

    // -----------------------------
    // Canvas and Pads
    // -----------------------------
    TCanvas* c = new TCanvas("c", "hist + ratio", 800, 800);

    TPad* pad1 = new TPad("pad1", "", 0.0, 0.30, 1.0, 1.0);
    pad1->SetBottomMargin(0.02);
    pad1->Draw();
    pad1->cd();

    // -----------------------------
    // Top pad: histograms
    // -----------------------------
    h1->GetYaxis()->SetTitle("h1 and h2 Gaussian histograms");
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.04);
    h1->GetXaxis()->SetLabelSize(0);

    h1->Draw("hist");
    h2->Draw("hist same");

    // -----------------------------
    // Bottom pad
    // -----------------------------
    c->cd();
    TPad* pad2 = new TPad("pad2", "", 0.0, 0.0, 1.0, 0.30);
    pad2->SetTopMargin(0.02);
    pad2->SetBottomMargin(0.35);
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();

    // -----------------------------
    // Ratio histogram
    // -----------------------------
    TH1D* hratio = (TH1D*)h1->Clone("hratio");
    hratio->Divide(h2);

    hratio->SetMarkerStyle(20);
    hratio->SetMarkerSize(0.8);
    hratio->SetLineColor(kBlack);

    hratio->GetYaxis()->SetTitle("ratio h1/h2");
    hratio->GetYaxis()->SetTitleSize(0.10);
    hratio->GetYaxis()->SetLabelSize(0.08);
    hratio->GetYaxis()->SetNdivisions(505);

    hratio->GetXaxis()->SetTitle("X title");
    hratio->GetXaxis()->SetTitleSize(0.12);
    hratio->GetXaxis()->SetLabelSize(0.10);

    hratio->SetMinimum(0.5);
    hratio->SetMaximum(1.5);

    hratio->Draw("E1");

    // -----------------------------
    // Reference line at ratio = 1
    // -----------------------------
    TLine* line = new TLine(-5, 1.0, 5, 1.0);
    line->SetLineStyle(2);
    line->Draw();

    c->Update();
}