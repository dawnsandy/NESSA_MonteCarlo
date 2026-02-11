// ============================================================
// plot_results.C - NESSA output analysis
// Usage: root -l 'macros/plot_results.C("nessa_output.root")'
// ============================================================

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include <map>
#include <vector>
#include <algorithm>

const char* elemSym[] = {
    "n","H","He","Li","Be","B","C","N","O","F","Ne",
    "Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca",
    "Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn",
    "Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr",
    "Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn"
};

void plot_results(const char* fname = "nessa_output.root")
{
    gStyle->SetOptStat(0);
    
    auto* f = TFile::Open(fname);
    if (!f || f->IsZombie()) { printf("Cannot open %s\n", fname); return; }
    
    // --- Plot 1: Neutron spectra at CUP positions ---
    auto* c1 = new TCanvas("c1", "Neutron Spectra - CUP", 1200, 800);
    c1->SetLogy(); c1->SetLogx();
    
    const char* cup[] = {"CUP_0mm","CUP_3mm","CUP_10mm","CUP_43mm","CUP_93mm"};
    int col[] = {kRed, kBlue, kGreen+2, kMagenta, kCyan+1};
    auto* leg1 = new TLegend(0.55, 0.6, 0.88, 0.88);
    
    for (int i = 0; i < 5; i++) {
        auto* h = (TH1*)f->Get(Form("n_spec_%s", cup[i]));
        if (!h) continue;
        h->SetLineColor(col[i]); h->SetLineWidth(2);
        h->GetXaxis()->SetTitle("Energy [MeV]");
        h->GetYaxis()->SetTitle("Track-length estimator [cm/MeV]");
        h->Draw(i==0 ? "" : "same");
        leg1->AddEntry(h, cup[i], "l");
    }
    leg1->Draw();
    c1->SaveAs("neutron_spectra_CUP.png");
    
    // --- Plot 2: Neutron spectra along beamline ---
    auto* c2 = new TCanvas("c2", "Neutron Spectra - Beamline", 1200, 800);
    c2->SetLogy(); c2->SetLogx();
    
    const char* beam[] = {"CUP_0mm","CollimatorIn","CollimatorOut",
                           "HVS","OutLabyrinth","Lab_exit"};
    auto* leg2 = new TLegend(0.5, 0.55, 0.88, 0.88);
    for (int i = 0; i < 6; i++) {
        auto* h = (TH1*)f->Get(Form("n_spec_%s", beam[i]));
        if (!h) continue;
        h->SetLineColor(col[i%5]); h->SetLineWidth(2);
        h->Draw(i==0 ? "" : "same");
        leg2->AddEntry(h, beam[i], "l");
    }
    leg2->Draw();
    c2->SaveAs("neutron_spectra_beamline.png");
    
    // --- Plot 3: Activation product spatial map ---
    auto* act = (TTree*)f->Get("activation");
    if (act && act->GetEntries() > 0) {
        printf("\nActivation ntuple: %lld entries\n", act->GetEntries());
        
        // XY map of all activation
        auto* c3 = new TCanvas("c3", "Activation Map XY", 1000, 800);
        act->Draw("y_cm:x_cm>>h_act_xy(100,-500,500,100,-400,1000)",
                  "halfLife_s>0", "colz");
        c3->SaveAs("activation_map_xy.png");
        
        // Neutron energy causing activation
        auto* c4 = new TCanvas("c4", "Activation vs Neutron Energy", 800, 600);
        c4->SetLogx(); c4->SetLogy();
        act->Draw("neutronE_MeV>>h_actE(200,1e-9,20)", "halfLife_s>0", "");
        c4->SaveAs("activation_vs_energy.png");
        
        // Top isotopes bar chart from ntuple
        int Z, A, isomer;
        double weight, halfLife;
        act->SetBranchAddress("Z", &Z);
        act->SetBranchAddress("A", &A);
        act->SetBranchAddress("isomer", &isomer);
        act->SetBranchAddress("weight", &weight);
        act->SetBranchAddress("halfLife_s", &halfLife);
        
        std::map<std::tuple<int,int,int>, double> counts;
        std::map<std::tuple<int,int,int>, double> halflives;
        
        for (Long64_t i = 0; i < act->GetEntries(); i++) {
            act->GetEntry(i);
            if (halfLife <= 0) continue;  // skip stable
            auto key = std::make_tuple(Z, A, isomer);
            counts[key] += weight;
            halflives[key] = halfLife;
        }
        
        // Sort by count
        std::vector<std::pair<std::tuple<int,int,int>, double>> sorted(
            counts.begin(), counts.end());
        std::sort(sorted.begin(), sorted.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        
        printf("\n=== Top 15 Radioactive Isotopes ===\n");
        printf("%-12s %12s %12s %12s\n", "Isotope", "T_half", "Count", "A_sat(1e8n/s)");
        int nPrint = std::min((int)sorted.size(), 15);
        for (int i = 0; i < nPrint; i++) {
            auto [z, a, iso] = sorted[i].first;
            double cnt = sorted[i].second;
            double hl = halflives[sorted[i].first];
            const char* sym = (z < 50) ? elemSym[z] : "??";
            printf("%-3s-%-3d%-1s %10.0f s %12.1f %12.2e Bq\n",
                   sym, a, iso ? "m" : " ", hl, cnt, cnt/act->GetEntries()*1e8);
        }
    }
    
    printf("\nPlots saved. Done.\n");
}
