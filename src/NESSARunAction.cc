#include "NESSARunAction.hh"
#include "NESSASteppingAction.hh"
#include "NESSAScoringConfig.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

NESSARunAction::NESSARunAction(NESSASteppingAction* stepping)
    : fSteppingAction(stepping)
{
    auto am = G4AnalysisManager::Instance();
    am->SetVerboseLevel(1);
    am->SetFileName("nessa_output.root");
    
    G4cout << "Analysis manager type: " << am->GetType() << G4endl;
    
    const auto& pts = NESSAScoringConfig::Instance().GetPoints();
    G4int N = NESSAScoringConfig::Instance().GetNActive();
    
    // --- Neutron histograms: IDs 0..(2N-1) ---
    for (const auto& p : pts) {
        if (!p.active) continue;
        am->CreateH1("n_spec_" + p.name,
            "Neutron spectrum " + p.name, 300, 1e-9, 20.0);
        am->CreateH1("n_dose_" + p.name,
            "Neutron Edep " + p.name, 300, 1e-9, 20.0);
    }
    
    // --- Photon histograms: IDs 2N..(4N-1) ---
    for (const auto& p : pts) {
        if (!p.active) continue;
        am->CreateH1("g_spec_" + p.name,
            "Photon spectrum " + p.name, 200, 0.0, 10.0);
        am->CreateH1("g_dose_" + p.name,
            "Photon Edep " + p.name, 200, 0.0, 10.0);
    }
    
    // --- Ntuple 0: Point detector scoring ---
    am->CreateNtuple("scoring", "Point detector data");
    am->CreateNtupleIColumn("detID");       // 0
    am->CreateNtupleDColumn("energy_MeV");  // 1
    am->CreateNtupleDColumn("edep_MeV");    // 2
    am->CreateNtupleDColumn("trackLen_cm"); // 3
    am->CreateNtupleIColumn("particle");    // 4: 0=n, 1=gamma
    am->FinishNtuple();
    
    // --- Ntuple 1: Activation products (all isotopes) ---
    am->CreateNtuple("activation", "Radioactive isotope production");
    am->CreateNtupleIColumn("Z");            // 0
    am->CreateNtupleIColumn("A");            // 1
    am->CreateNtupleIColumn("isomer");       // 2
    am->CreateNtupleDColumn("x_cm");         // 3
    am->CreateNtupleDColumn("y_cm");         // 4
    am->CreateNtupleDColumn("z_cm");         // 5
    am->CreateNtupleDColumn("neutronE_MeV"); // 6
    am->CreateNtupleDColumn("weight");       // 7
    am->CreateNtupleSColumn("volume");       // 8
    am->CreateNtupleSColumn("process");      // 9
    am->CreateNtupleDColumn("halfLife_s");   // 10
    am->FinishNtuple();
}

NESSARunAction::~NESSARunAction() {}

void NESSARunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "\n### Run " << run->GetRunID() << " start ("
           << run->GetNumberOfEventToBeProcessed() << " events)" << G4endl;
    fTimer.Start();
    
    if (fSteppingAction) fSteppingAction->Reset();
    
    auto am = G4AnalysisManager::Instance();
    am->OpenFile();
}

void NESSARunAction::EndOfRunAction(const G4Run* run)
{
    fTimer.Stop();
    
    auto am = G4AnalysisManager::Instance();
    am->Write();
    am->CloseFile();
    
    G4int nEvents = run->GetNumberOfEvent();
    if (nEvents == 0) return;
    G4double elapsed = fTimer.GetRealElapsed();
    
    G4cout << "\n" << G4String(72, '=') << G4endl;
    G4cout << "  NESSA Run Summary" << G4endl;
    G4cout << G4String(72, '=') << G4endl;
    G4cout << "  Events processed:  " << nEvents << G4endl;
    G4cout << "  Wall-clock time:   " << std::fixed << std::setprecision(1)
           << elapsed << " s (" << nEvents / elapsed << " evt/s)" << G4endl;
    G4cout << "  Output file:       nessa_output (" << am->GetType() << ")" << G4endl;
    
    if (fSteppingAction) {
        PrintActivationReport(nEvents);
    }
    
    G4cout << G4String(72, '=') << G4endl;
}

void NESSARunAction::PrintActivationReport(G4int nEvents)
{
    const auto& globalProd = fSteppingAction->GetGlobalProduction();
    const auto& volumeProd = fSteppingAction->GetVolumeProduction();
    
    if (globalProd.empty()) {
        G4cout << "\n  No activation products detected." << G4endl;
        return;
    }
    
    // Typical Adelphi DT-110 source strength
    G4double sourceRate = 1.0e8;  // n/s
    
    // ================================================================
    // Build sorted list by saturation activity (radioactive only)
    // A_sat = production_rate = (count/nEvents) * sourceRate [Bq]
    // For stable products, activity = 0.
    // ================================================================
    struct RankedIsotope {
        IsotopeID id;
        G4double  count;
        G4double  halfLife_s;
        G4double  satActivity_Bq;  // production_rate (= sat. activity)
        G4double  perNeutron;
    };
    
    std::vector<RankedIsotope> ranked;
    G4double totalProd = 0;
    
    for (const auto& [id, rec] : globalProd) {
        G4double perN = rec.count / nEvents;
        G4double prodRate = perN * sourceRate;
        
        // Saturation activity: at equilibrium, production = decay
        // A_sat = production_rate [Bq] (only for radioactive isotopes)
        G4double satA = (rec.halfLife_s > 0) ? prodRate : 0;
        
        ranked.push_back({id, rec.count, rec.halfLife_s, satA, perN});
        totalProd += rec.count;
    }
    
    // Sort by saturation activity (highest first)
    std::sort(ranked.begin(), ranked.end(),
        [](const RankedIsotope& a, const RankedIsotope& b) {
            return a.satActivity_Bq > b.satActivity_Bq;
        });
    
    // ================================================================
    // Print: all isotopes summary
    // ================================================================
    G4cout << "\n  --- Activation Summary ---" << G4endl;
    G4cout << "  Total isotope production events: " << totalProd << G4endl;
    G4cout << "  Unique isotopes produced: " << ranked.size() << G4endl;
    G4cout << "  Source rate assumed: " << std::scientific << std::setprecision(1)
           << sourceRate << " n/s" << G4endl;
    
    // ================================================================
    // TOP 10 by saturation activity
    // ================================================================
    G4cout << "\n  --- Top 10 Radioactive Isotopes (by saturation activity) ---"
           << G4endl;
    G4cout << "  " << G4String(70, '-') << G4endl;
    G4cout << std::left
           << "  " << std::setw(4) << "#"
           << std::setw(12) << "Isotope"
           << std::setw(14) << "T_half"
           << std::right
           << std::setw(12) << "per neutron"
           << std::setw(14) << "A_sat [Bq]"
           << std::setw(14) << "A_sat"
           << G4endl;
    G4cout << "  " << G4String(70, '-') << G4endl;
    
    G4int rank = 0;
    for (const auto& r : ranked) {
        if (r.satActivity_Bq <= 0) continue;  // skip stable
        rank++;
        if (rank > 10) break;
        
        // Format half-life nicely
        G4String tStr;
        if (r.halfLife_s < 60)
            tStr = std::to_string((int)r.halfLife_s) + " s";
        else if (r.halfLife_s < 3600)
            tStr = std::to_string((int)(r.halfLife_s/60)) + " min";
        else if (r.halfLife_s < 86400)
            tStr = std::to_string((int)(r.halfLife_s/3600)) + " h";
        else if (r.halfLife_s < 365.25*86400)
            tStr = std::to_string((int)(r.halfLife_s/86400)) + " d";
        else
            tStr = std::to_string((int)(r.halfLife_s/(365.25*86400))) + " y";
        
        // Format activity with SI prefix
        G4String aStr;
        if (r.satActivity_Bq >= 1e9)
            aStr = std::to_string((int)(r.satActivity_Bq/1e9)) + " GBq";
        else if (r.satActivity_Bq >= 1e6)
            aStr = std::to_string((int)(r.satActivity_Bq/1e6)) + " MBq";
        else if (r.satActivity_Bq >= 1e3)
            aStr = std::to_string((int)(r.satActivity_Bq/1e3)) + " kBq";
        else
            aStr = std::to_string((int)r.satActivity_Bq) + " Bq";
        
        G4cout << std::left
               << "  " << std::setw(4) << rank
               << std::setw(12) << NESSASteppingAction::IsotopeName(r.id)
               << std::setw(14) << tStr
               << std::right << std::scientific << std::setprecision(3)
               << std::setw(12) << r.perNeutron
               << std::setw(14) << r.satActivity_Bq
               << "  " << std::left << aStr
               << G4endl;
    }
    
    // ================================================================
    // TOP 10 by total production count (includes stable products)
    // ================================================================
    std::sort(ranked.begin(), ranked.end(),
        [](const RankedIsotope& a, const RankedIsotope& b) {
            return a.count > b.count;
        });
    
    G4cout << "\n  --- Top 10 Isotopes by Production Count ---" << G4endl;
    G4cout << "  " << G4String(70, '-') << G4endl;
    G4cout << std::left
           << "  " << std::setw(4) << "#"
           << std::setw(12) << "Isotope"
           << std::setw(14) << "T_half"
           << std::right
           << std::setw(12) << "count"
           << std::setw(14) << "per neutron"
           << std::setw(14) << "fraction"
           << G4endl;
    G4cout << "  " << G4String(70, '-') << G4endl;
    
    rank = 0;
    for (const auto& r : ranked) {
        rank++;
        if (rank > 10) break;
        
        G4String tStr;
        if (r.halfLife_s <= 0) tStr = "stable";
        else if (r.halfLife_s < 60) tStr = std::to_string((int)r.halfLife_s) + " s";
        else if (r.halfLife_s < 3600) tStr = std::to_string((int)(r.halfLife_s/60)) + " min";
        else if (r.halfLife_s < 86400) tStr = std::to_string((int)(r.halfLife_s/3600)) + " h";
        else if (r.halfLife_s < 365.25*86400) tStr = std::to_string((int)(r.halfLife_s/86400)) + " d";
        else tStr = std::to_string((int)(r.halfLife_s/(365.25*86400))) + " y";
        
        G4cout << std::left
               << "  " << std::setw(4) << rank
               << std::setw(12) << NESSASteppingAction::IsotopeName(r.id)
               << std::setw(14) << tStr
               << std::right << std::fixed << std::setprecision(1)
               << std::setw(12) << r.count
               << std::scientific << std::setprecision(3)
               << std::setw(14) << r.perNeutron
               << std::fixed << std::setprecision(1)
               << std::setw(13) << (r.count / totalProd * 100) << "%"
               << G4endl;
    }
    
    // ================================================================
    // Ar-41 specific detail (important for air activation)
    // ================================================================
    IsotopeID ar41{18, 41, 0};
    auto it = globalProd.find(ar41);
    if (it != globalProd.end()) {
        G4double ar41Total = it->second.count;
        G4double perN = ar41Total / nEvents;
        G4double prodRate = perN * sourceRate;
        
        G4cout << "\n  --- Ar-41 Detail (air activation) ---" << G4endl;
        G4cout << "  Total Ar-41:           " << ar41Total << G4endl;
        G4cout << "  Per source neutron:    " << std::scientific
               << std::setprecision(4) << perN << G4endl;
        G4cout << "  Production rate:       " << prodRate << " /s" << G4endl;
        G4cout << "  Saturation activity:   " << prodRate << " Bq ("
               << prodRate / 1e6 << " MBq)" << G4endl;
        
        // Per-volume breakdown for Ar-41
        G4cout << "  Production by volume:" << G4endl;
        for (const auto& [vol, isomap] : volumeProd) {
            auto vit = isomap.find(ar41);
            if (vit != isomap.end() && vit->second.count > 0) {
                G4double frac = vit->second.count / ar41Total * 100.0;
                if (frac > 0.5) {
                    G4cout << "    " << std::setw(30) << std::left << vol
                           << std::fixed << std::setprecision(1)
                           << frac << "%" << G4endl;
                }
            }
        }
    }
    
    // ================================================================
    // Volume-wise top activators
    // ================================================================
    G4cout << "\n  --- Activation by Material Region (top isotope per volume) ---"
           << G4endl;
    
    // Group by material type (aggregate volumes with same material prefix)
    struct VolSummary {
        G4String volName;
        G4String topIsotope;
        G4double topCount;
        G4double totalCount;
    };
    std::vector<VolSummary> volSummaries;
    
    for (const auto& [vol, isomap] : volumeProd) {
        G4double totalInVol = 0;
        IsotopeID topID{0,0,0};
        G4double topCount = 0;
        
        for (const auto& [id, rec] : isomap) {
            totalInVol += rec.count;
            if (rec.count > topCount && rec.halfLife_s > 0) {
                topCount = rec.count;
                topID = id;
            }
        }
        if (totalInVol > 0) {
            VolSummary vs;
            vs.volName = vol;
            vs.topIsotope = NESSASteppingAction::IsotopeName(topID);
            vs.topCount = topCount;
            vs.totalCount = totalInVol;
            volSummaries.push_back(vs);
        }
    }
    
    std::sort(volSummaries.begin(), volSummaries.end(),
        [](const VolSummary& a, const VolSummary& b) {
            return a.totalCount > b.totalCount;
        });
    
    G4int nPrint = std::min((G4int)volSummaries.size(), 15);
    for (G4int i = 0; i < nPrint; i++) {
        const auto& vs = volSummaries[i];
        G4cout << "  " << std::setw(25) << std::left << vs.volName
               << " total=" << std::fixed << std::setprecision(1) << vs.totalCount
               << "  top radioactive: " << vs.topIsotope
               << " (" << vs.topCount << ")" << G4endl;
    }
}
