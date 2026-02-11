//============================================================================
// NESSARunAction.cc
// Histogram layout (N = number of active detectors):
//   H1 [0..N-1]      : neutron energy spectra (track-length weighted)
//   H1 [N..2N-1]     : neutron dose spectra (h*(10) × w × trkLen)
//   H1 [2N..3N-1]    : gamma energy spectra
//   H1 [3N..4N-1]    : gamma dose spectra (edep weighted)
//   H1 [4N]          : neutron dose summary bar chart
//   H1 [4N+1]        : gamma dose summary bar chart
//   H2 [0-3]         : 2D maps (flux, dose, thermal, fast)
//   Ntuple 0         : raw hits (n + gamma)
//   Ntuple 1         : activation products
//============================================================================
#include "NESSARunAction.hh"
#include "NESSASteppingAction.hh"
#include "NESSAScoringConfig.hh"

#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

NESSARunAction::NESSARunAction(NESSASteppingAction* stepping)
    : G4UserRunAction(), fStepping(stepping)
{}

NESSARunAction::~NESSARunAction()
{}

void NESSARunAction::BeginOfRunAction(const G4Run*)
{
    auto am = G4AnalysisManager::Instance();
    am->SetVerboseLevel(1);
    am->SetDefaultFileType("root");
    am->OpenFile("NESSA_spectra");

    const auto& pts = NESSAScoringConfig::Instance().GetPoints();
    G4int N = 0;

    // Count active detectors and build names
    std::vector<std::string> names;
    for (const auto& p : pts) {
        if (!p.active) continue;
        names.push_back(p.name);
        N++;
    }

    G4int nBins = 100;

    // --- H1 [0..N-1]: Neutron energy spectra ---
    for (G4int d = 0; d < N; ++d) {
        std::vector<G4double> edges(nBins + 1);
        G4double lMin = -9, lMax = 2;  // 1e-9 to 100 MeV
        G4double lStep = (lMax - lMin) / nBins;
        for (G4int i = 0; i <= nBins; ++i)
            edges[i] = std::pow(10.0, lMin + i * lStep) * MeV;
        am->CreateH1("n_" + names[d],
                      "Neutron spectrum " + names[d], edges);
    }

    // --- H1 [N..2N-1]: Neutron dose spectra ---
    for (G4int d = 0; d < N; ++d) {
        std::vector<G4double> edges(nBins + 1);
        G4double lMin = -9, lMax = 2;
        G4double lStep = (lMax - lMin) / nBins;
        for (G4int i = 0; i <= nBins; ++i)
            edges[i] = std::pow(10.0, lMin + i * lStep) * MeV;
        am->CreateH1("nDose_" + names[d],
                      "Neutron H*(10) " + names[d], edges);
    }

    // --- H1 [2N..3N-1]: Gamma energy spectra ---
    for (G4int d = 0; d < N; ++d) {
        am->CreateH1("g_" + names[d],
                      "Gamma spectrum " + names[d], 200, 0.0, 10.0 * MeV);
    }

    // --- H1 [3N..4N-1]: Gamma dose spectra ---
    for (G4int d = 0; d < N; ++d) {
        am->CreateH1("gDose_" + names[d],
                      "Gamma Edep " + names[d], 200, 0.0, 10.0 * MeV);
    }

    // --- H1 [4N]: Neutron dose summary ---
    am->CreateH1("NeutronDoseSummary",
                  "Neutron H*(10) per detector [pSv*cm]", N, -0.5, N - 0.5);

    // --- H1 [4N+1]: Gamma dose summary ---
    am->CreateH1("GammaDoseSummary",
                  "Gamma Edep per detector [MeV]", N, -0.5, N - 0.5);

    // --- H2 [0-3]: 2D maps ---
    G4int nx = 96, ny = 144;
    G4double xmin = -240.0 * cm, xmax = 240.0 * cm;
    G4double ymin = -360.0 * cm, ymax = 360.0 * cm;
    am->CreateH2("FluxXY_total",   "Total neutron flux XY",      nx, xmin, xmax, ny, ymin, ymax);
    am->CreateH2("DoseXY",         "H*(10) dose rate map XY",    nx, xmin, xmax, ny, ymin, ymax);
    am->CreateH2("FluxXY_thermal", "Thermal flux (E<0.5eV) XY", nx, xmin, xmax, ny, ymin, ymax);
    am->CreateH2("FluxXY_fast",    "Fast flux (E>0.1MeV) XY",   nx, xmin, xmax, ny, ymin, ymax);

    // --- Ntuple 0: Raw hits ---
    am->CreateNtuple("Hits", "Neutron and gamma hits in detectors");
    am->CreateNtupleIColumn("DetID");          // 0
    am->CreateNtupleDColumn("Energy_MeV");     // 1
    am->CreateNtupleDColumn("TrackLength_cm"); // 2
    am->CreateNtupleDColumn("Weight");         // 3
    am->CreateNtupleDColumn("Time_ns");        // 4
    am->CreateNtupleDColumn("X_cm");           // 5
    am->CreateNtupleDColumn("Y_cm");           // 6
    am->CreateNtupleDColumn("Z_cm");           // 7
    am->CreateNtupleIColumn("Particle");       // 8: 0=neutron, 1=gamma
    am->FinishNtuple();

    // --- Ntuple 1: Activation products ---
    am->CreateNtuple("Activation", "Radioactive isotope production");
    am->CreateNtupleIColumn("Z");              // 0
    am->CreateNtupleIColumn("A");              // 1
    am->CreateNtupleIColumn("Isomer");         // 2
    am->CreateNtupleDColumn("X_cm");           // 3
    am->CreateNtupleDColumn("Y_cm");           // 4
    am->CreateNtupleDColumn("Z_cm");           // 5
    am->CreateNtupleDColumn("NeutronE_MeV");   // 6
    am->CreateNtupleDColumn("Weight");         // 7
    am->CreateNtupleSColumn("Volume");         // 8
    am->CreateNtupleSColumn("Process");        // 9
    am->CreateNtupleDColumn("HalfLife_s");     // 10
    am->FinishNtuple();

    G4cout << "\n### NESSA Histograms booked:"
           << "\n###   H1[0.." << N-1 << "]     neutron spectra"
           << "\n###   H1[" << N << ".." << 2*N-1 << "]  neutron dose spectra"
           << "\n###   H1[" << 2*N << ".." << 3*N-1 << "]  gamma spectra"
           << "\n###   H1[" << 3*N << ".." << 4*N-1 << "]  gamma dose spectra"
           << "\n###   H1[" << 4*N << "]        neutron dose summary"
           << "\n###   H1[" << 4*N+1 << "]        gamma dose summary"
           << "\n###   H2[0-3]      2D maps"
           << "\n###   Ntuple[0]    raw hits"
           << "\n###   Ntuple[1]    activation products"
           << "\n###   Active detectors: " << N << G4endl;

    if (fStepping) fStepping->Reset();
}

void NESSARunAction::EndOfRunAction(const G4Run* run)
{
    G4int nEvents = run->GetNumberOfEvent();
    if (nEvents == 0) return;

    auto am = G4AnalysisManager::Instance();
    am->Write();
    am->CloseFile();

    G4cout << "\n### NESSA: Run completed with " << nEvents << " events"
           << "\n### Output: NESSA_spectra.root" << G4endl;

    if (fStepping) PrintActivationReport(nEvents);
}

void NESSARunAction::PrintActivationReport(G4int nEvents)
{
    const auto& globalProd = fStepping->GetGlobalProduction();
    const auto& volumeProd = fStepping->GetVolumeProduction();

    if (globalProd.empty()) {
        G4cout << "\n  No activation products detected." << G4endl;
        return;
    }

    G4double sourceRate = 1.0e8;  // n/s (typical Adelphi DT-110)

    // Build ranked list
    struct RankedIsotope {
        IsotopeID id;
        G4double count;
        G4double halfLife_s;
        G4double satActivity_Bq;
        G4double perNeutron;
    };

    std::vector<RankedIsotope> ranked;

    for (const auto& kv : globalProd) {
        const IsotopeID& id = kv.first;
        const IsotopeRecord& rec = kv.second;
        G4double perN = rec.count / nEvents;
        G4double prodRate = perN * sourceRate;
        G4double satA = (rec.halfLife_s > 0) ? prodRate : 0;
        RankedIsotope r;
        r.id = id;
        r.count = rec.count;
        r.halfLife_s = rec.halfLife_s;
        r.satActivity_Bq = satA;
        r.perNeutron = perN;
        ranked.push_back(r);
    }

    // Sort by saturation activity
    std::sort(ranked.begin(), ranked.end(),
        [](const RankedIsotope& a, const RankedIsotope& b) {
            return a.satActivity_Bq > b.satActivity_Bq;
        });

    G4cout << "\n" << std::string(72, '=')
           << "\n  ACTIVATION REPORT (source rate = "
           << std::scientific << std::setprecision(1) << sourceRate << " n/s)"
           << "\n  Total unique isotopes produced: " << ranked.size()
           << "\n" << std::string(72, '=') << G4endl;

    // --- Top 10 by saturation activity ---
    G4cout << "\n  --- Top 10 Radioactive Isotopes (by A_sat) ---" << G4endl;
    G4cout << "  " << std::string(68, '-') << G4endl;
    G4cout << std::left
           << "  " << std::setw(4) << "#"
           << std::setw(12) << "Isotope"
           << std::setw(14) << "T_half"
           << std::right
           << std::setw(12) << "per neutron"
           << std::setw(14) << "A_sat [Bq]"
           << std::setw(12) << "A_sat"
           << G4endl;
    G4cout << "  " << std::string(68, '-') << G4endl;

    G4int rank = 0;
    for (const auto& r : ranked) {
        if (r.satActivity_Bq <= 0) continue;
        rank++;
        if (rank > 10) break;

        // Human-readable half-life
        std::string tStr;
        if (r.halfLife_s < 60)
            tStr = std::to_string((int)r.halfLife_s) + " s";
        else if (r.halfLife_s < 3600)
            tStr = std::to_string((int)(r.halfLife_s / 60)) + " min";
        else if (r.halfLife_s < 86400)
            tStr = std::to_string((int)(r.halfLife_s / 3600)) + " h";
        else if (r.halfLife_s < 365.25 * 86400)
            tStr = std::to_string((int)(r.halfLife_s / 86400)) + " d";
        else
            tStr = std::to_string((int)(r.halfLife_s / (365.25 * 86400))) + " y";

        // SI prefix for activity
        std::string aStr;
        if (r.satActivity_Bq >= 1e9)
            aStr = std::to_string((int)(r.satActivity_Bq / 1e9)) + " GBq";
        else if (r.satActivity_Bq >= 1e6)
            aStr = std::to_string((int)(r.satActivity_Bq / 1e6)) + " MBq";
        else if (r.satActivity_Bq >= 1e3)
            aStr = std::to_string((int)(r.satActivity_Bq / 1e3)) + " kBq";
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

    // --- Top 10 by count (includes stable) ---
    std::sort(ranked.begin(), ranked.end(),
        [](const RankedIsotope& a, const RankedIsotope& b) {
            return a.count > b.count;
        });

    G4cout << "\n  --- Top 10 by Production Count (all isotopes) ---" << G4endl;
    G4cout << "  " << std::string(68, '-') << G4endl;
    G4cout << std::left
           << "  " << std::setw(4) << "#"
           << std::setw(12) << "Isotope"
           << std::setw(14) << "T_half"
           << std::right
           << std::setw(12) << "count"
           << std::setw(14) << "per neutron"
           << G4endl;
    G4cout << "  " << std::string(68, '-') << G4endl;

    rank = 0;
    for (const auto& r : ranked) {
        rank++;
        if (rank > 10) break;

        std::string tStr;
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
               << G4endl;
    }

    // --- Ar-41 specific detail ---
    IsotopeID ar41{18, 41, 0};
    auto it = globalProd.find(ar41);
    if (it != globalProd.end()) {
        G4double perN = it->second.count / nEvents;
        G4double prodRate = perN * sourceRate;
        G4cout << "\n  --- Ar-41 Detail (air activation) ---"
               << "\n  Total Ar-41:          " << it->second.count
               << "\n  Per source neutron:   " << std::scientific
               << std::setprecision(4) << perN
               << "\n  Saturation activity:  " << prodRate << " Bq ("
               << prodRate / 1e6 << " MBq)" << G4endl;

        // Breakdown by volume
        G4cout << "  Production by volume:" << G4endl;
        for (const auto& vkv : volumeProd) {
            const std::string& vol = vkv.first;
            const auto& isomap = vkv.second;
            auto vit = isomap.find(ar41);
            if (vit != isomap.end() && vit->second.count > 0) {
                G4double frac = vit->second.count / it->second.count * 100;
                if (frac > 0.5) {
                    G4cout << "    " << std::setw(30) << std::left << vol
                           << std::fixed << std::setprecision(1)
                           << frac << "%" << G4endl;
                }
            }
        }
    }

    G4cout << std::string(72, '=') << G4endl;
}
