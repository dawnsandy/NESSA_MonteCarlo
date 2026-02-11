//============================================================================
// plot_nessa.C
// ROOT macro for NESSA Geant4 simulation analysis
//
// Usage in ROOT:
//   root NESSA_spectra.root
//   .x plot_nessa.C
//
// Or directly:
//   root -l 'plot_nessa.C("NESSA_spectra.root")'
//
// Produces:
//   Canvas 1: Neutron spectra at 6 key detectors (log-log)
//   Canvas 2: 2D flux map COLZ + LEGO 3D projection
//   Canvas 3: Dose rate map + thermal/fast comparison
//   Canvas 4: Dose rate vs distance along beamline
//   Canvas 5: Dose-weighted spectra comparison
//
// To calculate absolute dose rate [uSv/hr]:
//   dose_rate = H*(10)_per_source [pSv] × S [n/s] × 3600 × 1e-6
//   For S = 1e8 n/s: multiply pSv/source by 3.6e5
//============================================================================

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLine.h"
#include "TPad.h"
#include "TColor.h"
#include "TROOT.h"

void plot_nessa(const char* filename = "NESSA_spectra.root")
{
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kRainBow);
    gStyle->SetNumberContours(100);

    TFile* f = TFile::Open(filename);
    if (!f || f->IsZombie()) {
        printf("ERROR: Cannot open %s\n", filename);
        return;
    }

    printf("\n=== NESSA Geant4 Analysis ===\n\n");
    printf("Contents of %s:\n", filename);
    f->ls();

    //=================================================================
    // Canvas 1: Neutron energy spectra at key detector positions
    //=================================================================
    TCanvas* c1 = new TCanvas("c_spectra", "NESSA Neutron Spectra", 1200, 800);
    c1->Divide(3, 2);

    const char* specDets[] = {"Dtctr1", "Dtctr5", "Dtctr10",
                               "Dtctr15", "DtcIn1", "DtcIn2"};
    const char* specLabels[] = {
        "Dtctr1 (y=-110, post-collimator)",
        "Dtctr5 (y=-90, mid-beamline)",
        "Dtctr10 (y=-65, beamline center)",
        "Dtctr15 (y=-40, ~100cm from src)",
        "DtcIn1 (y=-150, near source)",
        "DtcIn2 (y=-170, off-axis)"
    };
    int specColors[] = {kBlue+1, kRed+1, kGreen+2, kMagenta+1, kOrange+1, kCyan+2};

    for (int i = 0; i < 6; i++) {
        c1->cd(i + 1);
        gPad->SetLogx();
        gPad->SetLogy();
        gPad->SetGrid();

        TH1D* h = (TH1D*)f->Get(specDets[i]);
        if (h) {
            h->SetLineColor(specColors[i]);
            h->SetLineWidth(2);
            h->GetXaxis()->SetTitle("Neutron Energy [MeV]");
            h->GetYaxis()->SetTitle("w #times #ell [cm]");
            h->SetTitle(specLabels[i]);
            h->Draw("HIST");
            printf("  %s: %d entries, integral=%.3e\n",
                   specDets[i], (int)h->GetEntries(), h->Integral());
        } else {
            printf("  WARNING: %s not found\n", specDets[i]);
        }
    }
    c1->SaveAs("NESSA_spectra.png");

    //=================================================================
    // Canvas 2: 2D flux maps - COLZ and LEGO3D
    //=================================================================
    TCanvas* c2 = new TCanvas("c_flux2d", "NESSA 2D Flux Maps", 1400, 700);
    c2->Divide(2, 1);

    TH2D* hFlux = (TH2D*)f->Get("FluxXY_total");
    if (hFlux) {
        // Left: COLZ top-down view
        c2->cd(1);
        gPad->SetLogz();
        gPad->SetRightMargin(0.15);
        hFlux->GetXaxis()->SetTitle("X [mm]");
        hFlux->GetYaxis()->SetTitle("Y [mm]");
        hFlux->SetTitle("Neutron Flux XY (z=0 slice)");
        hFlux->Draw("COLZ");

        // Mark source position
        TLatex* srcMark = new TLatex(600, -1400, "#star Source");
        srcMark->SetTextColor(kRed);
        srcMark->SetTextSize(0.035);
        srcMark->Draw();

        // Right: 3D LEGO projection
        c2->cd(2);
        gPad->SetLogz();
        gPad->SetTheta(35);
        gPad->SetPhi(225);
        TH2D* hFluxClone = (TH2D*)hFlux->Clone("FluxXY_3D");
        hFluxClone->SetTitle("3D Neutron Flux Distribution");
        hFluxClone->Draw("LEGO2Z");

        printf("  FluxXY_total: entries=%.0f, max=%.3e\n",
               hFlux->GetEntries(), hFlux->GetMaximum());
    }
    c2->SaveAs("NESSA_flux2D.png");

    //=================================================================
    // Canvas 3: Dose + thermal/fast maps
    //=================================================================
    TCanvas* c3 = new TCanvas("c_dosemap", "NESSA Dose & Component Maps", 1400, 700);
    c3->Divide(2, 2);

    const char* map_names[] = {"FluxXY_total", "DoseXY", "FluxXY_thermal", "FluxXY_fast"};
    const char* map_titles[] = {"Total Neutron Flux", "H*(10) Dose Rate Map",
                                 "Thermal Neutrons (E<0.5eV)", "Fast Neutrons (E>0.1MeV)"};

    for (int i = 0; i < 4; i++) {
        c3->cd(i + 1);
        gPad->SetLogz();
        gPad->SetRightMargin(0.15);
        TH2D* hmap = (TH2D*)f->Get(map_names[i]);
        if (hmap) {
            hmap->SetTitle(map_titles[i]);
            hmap->GetXaxis()->SetTitle("X [mm]");
            hmap->GetYaxis()->SetTitle("Y [mm]");
            hmap->Draw("COLZ");
        }
    }
    c3->SaveAs("NESSA_dose_maps.png");

    //=================================================================
    // Canvas 4: Dose rate vs distance along beamline
    //=================================================================
    TCanvas* c4 = new TCanvas("c_doserate", "NESSA Dose Rate Profile", 900, 600);
    gPad->SetLogy();
    gPad->SetGrid();

    TH1D* hDoseSummary = (TH1D*)f->Get("DoseRateSummary");
    if (hDoseSummary) {
        // Extract dose per detector and plot vs Y position
        double ypos[] = {-110,-105,-100,-95,-90,-85,-80,-74.5,-70,-65,
                         -60,-55,-50,-45,-40,-35,-30,-25,-20,-15,
                         -150,-170};
        const int nDet = 22;
        double dose[nDet], yvals[nDet];
        double detVol = 3.14159265 * 1.0 * 1.0 * 1.0;  // pi cm³

        printf("\n  === Dose Rate Summary (per source neutron) ===\n");
        printf("  %-10s  %8s  %15s\n", "Detector", "Y [cm]", "H*(10) [pSv/src]");

        for (int i = 0; i < nDet; i++) {
            // Bin i+1 (ROOT bins are 1-indexed)
            dose[i] = hDoseSummary->GetBinContent(i + 1) / detVol;
            yvals[i] = ypos[i];

            const char* dnames[] = {
                "Dtctr1","Dtctr2","Dtctr3","Dtctr4","Dtctr5",
                "Dtctr6","Dtctr7","Dtctr8","Dtctr9","Dtctr10",
                "Dtctr11","Dtctr12","Dtctr13","Dtctr14","Dtctr15",
                "Dtctr16","Dtctr17","Dtctr18","Dtctr19","Dtctr20",
                "DtcIn1","DtcIn2"};
            printf("  %-10s  %8.1f  %15.4e\n", dnames[i], ypos[i], dose[i]);
        }

        // Plot beamline detectors only (0-19)
        TGraph* gr = new TGraph(20, yvals, dose);
        gr->SetTitle("Neutron Dose Rate Along Beamline;Y position [cm];H*(10) per source [pSv]");
        gr->SetMarkerStyle(20);
        gr->SetMarkerColor(kRed+1);
        gr->SetMarkerSize(1.2);
        gr->SetLineColor(kRed+1);
        gr->SetLineWidth(2);
        gr->Draw("APL");

        // Annotate
        TLine* collLine = new TLine(-75, gr->GetYaxis()->GetXmin(),
                                     -75, gr->GetHistogram()->GetMaximum());
        collLine->SetLineStyle(2);
        collLine->SetLineColor(kBlue);
        collLine->Draw();

        TLatex* collLabel = new TLatex(-73, gr->GetHistogram()->GetMaximum()*0.5,
                                        "Collimator exit");
        collLabel->SetTextSize(0.03);
        collLabel->SetTextColor(kBlue);
        collLabel->Draw();

        printf("\n  To convert to uSv/hr at source strength S [n/s]:\n");
        printf("  dose_rate [uSv/hr] = H*(10) [pSv/src] x S x 3600 x 1e-6\n");
        printf("  Example: S=1e8 n/s, Dtctr1 = %.3e pSv/src\n", dose[0]);
        printf("    -> %.3e uSv/hr\n\n", dose[0] * 1e8 * 3600 * 1e-6);
    }
    c4->SaveAs("NESSA_dose_profile.png");

    //=================================================================
    // Canvas 5: Dose-weighted spectra overlay
    //=================================================================
    TCanvas* c5 = new TCanvas("c_dosespec", "NESSA Dose Spectra", 900, 600);
    gPad->SetLogx();
    gPad->SetLogy();
    gPad->SetGrid();

    TLegend* leg = new TLegend(0.15, 0.65, 0.45, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);

    const char* doseDets[] = {"Dose_Dtctr1", "Dose_Dtctr5",
                               "Dose_Dtctr10", "Dose_DtcIn1"};
    const char* doseLabels[] = {"Dtctr1 (post-coll.)", "Dtctr5 (mid)",
                                 "Dtctr10 (center)", "DtcIn1 (source)"};
    int doseColors[] = {kBlue+1, kRed+1, kGreen+2, kOrange+1};

    bool first = true;
    for (int i = 0; i < 4; i++) {
        TH1D* hd = (TH1D*)f->Get(doseDets[i]);
        if (hd && hd->GetEntries() > 0) {
            hd->SetLineColor(doseColors[i]);
            hd->SetLineWidth(2);
            hd->GetXaxis()->SetTitle("Neutron Energy [MeV]");
            hd->GetYaxis()->SetTitle("H*(10) contribution [pSv #upoint cm]");
            if (first) {
                hd->SetTitle("Dose-Weighted Neutron Spectra");
                hd->Draw("HIST");
                first = false;
            } else {
                hd->Draw("HIST SAME");
            }
            leg->AddEntry(hd, doseLabels[i], "l");
        }
    }
    if (!first) leg->Draw();
    c5->SaveAs("NESSA_dose_spectra.png");

    printf("\n=== Plots saved: ===\n");
    printf("  NESSA_spectra.png      - energy spectra\n");
    printf("  NESSA_flux2D.png       - 2D flux + 3D LEGO\n");
    printf("  NESSA_dose_maps.png    - dose & component maps\n");
    printf("  NESSA_dose_profile.png - dose vs distance\n");
    printf("  NESSA_dose_spectra.png - dose-weighted spectra\n");
    printf("\n=== Interactive 3D: ===\n");
    printf("  FluxXY_total->Draw(\"LEGO2Z\")  then rotate with mouse\n");
    printf("  FluxXY_total->Draw(\"SURF2Z\")  smooth 3D surface\n");
    printf("  DoseXY->Draw(\"LEGO2Z\")        dose in 3D\n");
    printf("  FluxXY_total->Draw(\"GL\")       OpenGL 3D (if available)\n\n");
}
