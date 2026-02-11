#include "NESSAScoringSD.hh"
#include "NESSAScoringConfig.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include <map>

NESSAScoringSD::NESSAScoringSD(const G4String& name)
    : G4VSensitiveDetector(name) {}

NESSAScoringSD::~NESSAScoringSD() {}

void NESSAScoringSD::Initialize(G4HCofThisEvent*) {}

G4bool NESSAScoringSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    auto* track = step->GetTrack();
    G4String particleName = track->GetDefinition()->GetParticleName();
    
    if (particleName != "neutron" && particleName != "gamma") return true;
    
    G4double kE     = step->GetPreStepPoint()->GetKineticEnergy();
    G4double sLen   = step->GetStepLength();
    G4double edep   = step->GetTotalEnergyDeposit();
    G4double weight = track->GetWeight();
    
    // Map logical volume name → detector index (built once)
    static std::map<G4String, G4int> nameMap;
    if (nameMap.empty()) {
        const auto& pts = NESSAScoringConfig::Instance().GetPoints();
        for (G4int i = 0; i < (G4int)pts.size(); i++) {
            if (!pts[i].active) continue;
            if (pts[i].mcnpCell > 0)
                nameMap["logic_c" + std::to_string(pts[i].mcnpCell)] = i;
            else
                nameMap["score_" + pts[i].name] = i;
        }
    }
    
    G4String lvName = step->GetPreStepPoint()->GetTouchableHandle()
                          ->GetVolume()->GetLogicalVolume()->GetName();
    auto it = nameMap.find(lvName);
    if (it == nameMap.end()) return true;
    G4int idx = it->second;
    
    auto am = G4AnalysisManager::Instance();
    
    if (particleName == "neutron") {
        // H1 IDs: idx*2 = spectrum, idx*2+1 = dose
        am->FillH1(idx * 2,     kE / MeV, weight * sLen / cm);
        am->FillH1(idx * 2 + 1, kE / MeV, edep / MeV * weight);
    } else {
        // Photon histograms offset by 2*N
        G4int N = NESSAScoringConfig::Instance().GetNActive();
        am->FillH1(2*N + idx*2,     kE / MeV, weight * sLen / cm);
        am->FillH1(2*N + idx*2 + 1, kE / MeV, edep / MeV * weight);
    }
    
    // Ntuple
    am->FillNtupleIColumn(0, 0, idx);
    am->FillNtupleDColumn(0, 1, kE / MeV);
    am->FillNtupleDColumn(0, 2, edep / MeV);
    am->FillNtupleDColumn(0, 3, weight * sLen / cm);
    am->FillNtupleIColumn(0, 4, (particleName == "neutron") ? 0 : 1);
    am->AddNtupleRow(0);
    
    return true;
}

void NESSAScoringSD::EndOfEvent(G4HCofThisEvent*) {}
