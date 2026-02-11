//============================================================================
// NESSASteppingAction.cc
// Three roles:
//   1) Activation inventory — catch every residual nucleus from neutron
//      reactions (nCapture, neutronInelastic, etc.)
//   2) 2D flux/dose maps over the bunker (as before)
//   3) Neutron AND gamma spectra + dose in macro-defined point detectors
//============================================================================
#include "NESSASteppingAction.hh"
#include "NESSADoseCalculator.hh"
#include "NESSAScoringConfig.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

#include <cmath>

NESSASteppingAction::NESSASteppingAction()
    : G4UserSteppingAction()
{}

NESSASteppingAction::~NESSASteppingAction()
{}

void NESSASteppingAction::Reset()
{
    fGlobalProd.clear();
    fVolumeProd.clear();
}

void NESSASteppingAction::UserSteppingAction(const G4Step* step)
{
    auto* track = step->GetTrack();
    auto* def   = track->GetDefinition();
    G4bool isNeutron = (def == G4Neutron::NeutronDefinition());
    G4bool isGamma   = (def == G4Gamma::GammaDefinition());

    if (!isNeutron && !isGamma) return;

    auto prePoint   = step->GetPreStepPoint();
    G4double energy = prePoint->GetKineticEnergy();
    G4double weight = prePoint->GetWeight();
    G4double sLen   = step->GetStepLength();
    if (sLen <= 0.) return;

    G4ThreeVector pos = prePoint->GetPosition();
    G4double trkLen_cm = sLen / cm;
    G4double energy_MeV = energy / MeV;

    auto am = G4AnalysisManager::Instance();

    //------------------------------------------------------------------
    // Part A: 2D maps (neutrons only, z=0 ± 10 cm slice)
    //------------------------------------------------------------------
    if (isNeutron && std::abs(pos.z()) < 10.0*cm) {
        // H2[0] total flux, H2[1] dose, H2[2] thermal, H2[3] fast
        am->FillH2(0, pos.x(), pos.y(), weight * trkLen_cm);
        G4double h10 = NESSADoseCalculator::Instance().GetH10(energy_MeV);
        am->FillH2(1, pos.x(), pos.y(), h10 * weight * trkLen_cm);
        if (energy < 5.0e-7 * MeV) am->FillH2(2, pos.x(), pos.y(), weight * trkLen_cm);
        if (energy > 0.1 * MeV)    am->FillH2(3, pos.x(), pos.y(), weight * trkLen_cm);
    }

    //------------------------------------------------------------------
    // Part B: Point-detector scoring (neutron + gamma spectra & dose)
    //
    // Histogram layout booked in NESSARunAction:
    //   H1 [0 .. N-1]       : neutron spectrum per detector
    //   H1 [N .. 2N-1]      : neutron dose spectrum per detector
    //   H1 [2N .. 3N-1]     : gamma spectrum per detector
    //   H1 [3N .. 4N-1]     : gamma dose spectrum per detector
    //   H1 [4N]             : neutron dose summary (1 bin per det)
    //   H1 [4N+1]           : gamma dose summary
    // where N = number of active detectors
    //------------------------------------------------------------------
    {
        std::string volName = prePoint->GetTouchableHandle()
                                  ->GetVolume()->GetLogicalVolume()->GetName();

        // Build lookup once (static map: volume name → detector index)
        static std::map<std::string, G4int> sDetMap;
        static G4int sN = 0;
        if (sDetMap.empty()) {
            const auto& pts = NESSAScoringConfig::Instance().GetPoints();
            G4int idx = 0;
            for (const auto& p : pts) {
                if (!p.active) continue;
                sDetMap[p.name + "_log"] = idx;
                idx++;
            }
            sN = idx;
        }

        auto it = sDetMap.find(volName);
        if (it != sDetMap.end()) {
            G4int d = it->second;
            G4int N = sN;

            if (isNeutron) {
                // H1[d]: neutron spectrum
                am->FillH1(d, energy, weight * trkLen_cm);
                // H1[N+d]: neutron dose-weighted spectrum
                G4double h10 = NESSADoseCalculator::Instance().GetH10(energy_MeV);
                G4double doseCont = h10 * weight * trkLen_cm;
                am->FillH1(N + d, energy, doseCont);
                // H1[4N]: neutron dose summary bar
                am->FillH1(4 * N, G4double(d), doseCont);
            }
            else if (isGamma) {
                // H1[2N+d]: gamma spectrum
                am->FillH1(2 * N + d, energy, weight * trkLen_cm);
                // H1[3N+d]: gamma dose (energy deposit as proxy)
                G4double edep = step->GetTotalEnergyDeposit();
                am->FillH1(3 * N + d, energy, edep / MeV * weight);
                // H1[4N+1]: gamma dose summary bar
                am->FillH1(4 * N + 1, G4double(d), edep / MeV * weight);
            }

            // Ntuple 0: raw hits
            am->FillNtupleIColumn(0, 0, d);
            am->FillNtupleDColumn(0, 1, energy_MeV);
            am->FillNtupleDColumn(0, 2, trkLen_cm);
            am->FillNtupleDColumn(0, 3, weight);
            am->FillNtupleDColumn(0, 4, prePoint->GetGlobalTime() / ns);
            am->FillNtupleDColumn(0, 5, pos.x() / cm);
            am->FillNtupleDColumn(0, 6, pos.y() / cm);
            am->FillNtupleDColumn(0, 7, pos.z() / cm);
            am->FillNtupleIColumn(0, 8, isNeutron ? 0 : 1);
            am->AddNtupleRow(0);
        }
    }

    //------------------------------------------------------------------
    // Part C: Activation inventory (neutron interactions only)
    //------------------------------------------------------------------
    if (!isNeutron) return;

    const auto* secondaries = step->GetSecondaryInCurrentStep();
    if (!secondaries || secondaries->empty()) return;

    const G4VProcess* proc = step->GetPostStepPoint()->GetProcessDefinedStep();
    if (!proc) return;
    std::string procName = proc->GetProcessName();

    std::string volName = prePoint->GetTouchableHandle()
                              ->GetVolume()->GetLogicalVolume()->GetName();

    for (const auto* sec : *secondaries) {
        auto* secDef = sec->GetDefinition();
        G4int Z = secDef->GetAtomicNumber();
        G4int A = secDef->GetAtomicMass();
        if (Z < 1 || A < 2) continue;

        G4double lifetime = secDef->GetPDGLifeTime();
        G4double halfLife_s = 0;
        if (lifetime > 0 && lifetime < 1e30 * ns) {
            halfLife_s = (lifetime / s) * 0.693147;
        }

        G4int isomer = 0;
        auto* ion = dynamic_cast<const G4Ions*>(secDef);
        if (ion && ion->GetExcitationEnergy() > 1.0 * keV) isomer = 1;

        IsotopeID id{Z, A, isomer};

        fGlobalProd[id].count += weight;
        if (halfLife_s > 0) fGlobalProd[id].halfLife_s = halfLife_s;

        fVolumeProd[volName][id].count += weight;
        if (halfLife_s > 0) fVolumeProd[volName][id].halfLife_s = halfLife_s;

        // Ntuple 1: activation products
        am->FillNtupleIColumn(1, 0, Z);
        am->FillNtupleIColumn(1, 1, A);
        am->FillNtupleIColumn(1, 2, isomer);
        am->FillNtupleDColumn(1, 3, pos.x() / cm);
        am->FillNtupleDColumn(1, 4, pos.y() / cm);
        am->FillNtupleDColumn(1, 5, pos.z() / cm);
        am->FillNtupleDColumn(1, 6, energy_MeV);
        am->FillNtupleDColumn(1, 7, weight);
        am->FillNtupleSColumn(1, 8, volName);
        am->FillNtupleSColumn(1, 9, procName);
        am->FillNtupleDColumn(1, 10, halfLife_s);
        am->AddNtupleRow(1);
    }
}

//--- Element symbols ---
const char* NESSASteppingAction::ElementSymbol(G4int Z)
{
    static const char* sym[] = {
        "n","H","He","Li","Be","B","C","N","O","F","Ne",
        "Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca",
        "Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn",
        "Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr",
        "Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn",
        "Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd",
        "Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb",
        "Lu","Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg",
        "Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th",
        "Pa","U","Np","Pu"
    };
    if (Z >= 0 && Z < 94) return sym[Z];
    static std::string fallback;
    fallback = "Z" + std::to_string(Z);
    return fallback.c_str();
}

std::string NESSASteppingAction::IsotopeName(const IsotopeID& id)
{
    std::string name = std::string(ElementSymbol(id.Z))
                     + "-" + std::to_string(id.A);
    if (id.isomer > 0) name += "m";
    return name;
}
