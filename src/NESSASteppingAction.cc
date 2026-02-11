#include "NESSASteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include <algorithm>

NESSASteppingAction::NESSASteppingAction() {}
NESSASteppingAction::~NESSASteppingAction() {}

void NESSASteppingAction::Reset()
{
    fGlobalProd.clear();
    fVolumeProd.clear();
}

void NESSASteppingAction::UserSteppingAction(const G4Step* step)
{
    // Only track secondaries from neutron interactions
    auto* track = step->GetTrack();
    if (track->GetDefinition()->GetParticleName() != "neutron") return;
    
    const auto* secondaries = step->GetSecondaryInCurrentStep();
    if (!secondaries || secondaries->empty()) return;
    
    // Check the process that created the secondaries
    const G4VProcess* proc = step->GetPostStepPoint()->GetProcessDefinedStep();
    if (!proc) return;
    G4String procName = proc->GetProcessName();
    
    // We want hadronic processes: nCapture, neutronInelastic, hadElastic won't
    // produce new isotopes but (n,2n) is part of neutronInelastic
    // Also NeutronHP processes: nFission, nCapture, etc.
    // Simply: check all secondaries for ions/nuclei with Z>0
    
    G4double weight = track->GetWeight();
    G4String volName = step->GetPreStepPoint()->GetTouchableHandle()
                           ->GetVolume()->GetLogicalVolume()->GetName();
    G4double neutronE = step->GetPreStepPoint()->GetKineticEnergy();
    auto pos = step->GetPreStepPoint()->GetPosition();
    
    for (const auto* sec : *secondaries) {
        auto* def = sec->GetDefinition();
        G4int Z = def->GetAtomicNumber();
        G4int A = def->GetAtomicMass();
        
        // Skip light particles (n, p, alpha, deuteron, gamma, e-)
        // We want residual nuclei with Z >= 1 and A >= 2
        // But also skip stable ground-state of parent (no activation)
        if (Z < 1 || A < 2) continue;
        
        // Determine if this is a radioactive isotope
        // In Geant4, G4Ions have excitation energy and lifetime info
        G4double lifetime = def->GetPDGLifeTime();
        G4double halfLife_s = 0;
        
        // lifetime < 0 means stable in Geant4 convention
        // lifetime = 0 can mean not defined
        if (lifetime > 0 && lifetime < 1e30 * ns) {
            halfLife_s = lifetime * 0.693147 / ns * 1e-9;  // convert ns to s
            // Actually: lifetime is in Geant4 internal units (ns)
            // halfLife = lifetime * ln(2) 
            halfLife_s = (lifetime / s) * 0.693147;
        }
        
        // Check isomeric state
        G4int isomer = 0;
        G4double excitationE = 0;
        auto* ion = dynamic_cast<const G4Ions*>(def);
        if (ion) {
            excitationE = ion->GetExcitationEnergy();
            if (excitationE > 1.0*keV) isomer = 1;
        }
        
        IsotopeID id{Z, A, isomer};
        
        // Record production
        fGlobalProd[id].count += weight;
        if (halfLife_s > 0) fGlobalProd[id].halfLife_s = halfLife_s;
        
        fVolumeProd[volName][id].count += weight;
        if (halfLife_s > 0) fVolumeProd[volName][id].halfLife_s = halfLife_s;
        
        // Fill activation ntuple (ntuple ID 1)
        auto am = G4AnalysisManager::Instance();
        am->FillNtupleIColumn(1, 0, Z);
        am->FillNtupleIColumn(1, 1, A);
        am->FillNtupleIColumn(1, 2, isomer);
        am->FillNtupleDColumn(1, 3, pos.x() / cm);
        am->FillNtupleDColumn(1, 4, pos.y() / cm);
        am->FillNtupleDColumn(1, 5, pos.z() / cm);
        am->FillNtupleDColumn(1, 6, neutronE / MeV);
        am->FillNtupleDColumn(1, 7, weight);
        am->FillNtupleSColumn(1, 8, volName);
        am->FillNtupleSColumn(1, 9, procName);
        am->FillNtupleDColumn(1, 10, halfLife_s);
        am->AddNtupleRow(1);
    }
}

const char* NESSASteppingAction::ElementSymbol(G4int Z)
{
    static const char* sym[] = {
        "n", "H","He","Li","Be","B","C","N","O","F","Ne",
        "Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca",
        "Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn",
        "Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr",
        "Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn",
        "Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd",
        "Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb",
        "Lu","Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg",
        "Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th",
        "Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm"
    };
    if (Z >= 0 && Z < 100) return sym[Z];
    static std::string fallback;
fallback = "X" + std::to_string(Z);
return fallback.c_str();
}

std::string NESSASteppingAction::IsotopeName(const IsotopeID& id)
{
    std::string name = std::string(ElementSymbol(id.Z)) + "-" + std::to_string(id.A);
    if (id.isomer > 0) name += "m";
    return name;
}
