//============================================================================
// NESSAPhysicsList.cc
// Physics list using QGSP_BIC_HP + thermal neutron scattering
// 
// QGSP_BIC_HP is the gold standard for neutron transport simulations:
//   - HP (High Precision) neutron models below 20 MeV using evaluated data
//   - BIC (Binary Cascade) for intermediate energies
//   - Thermal neutron scattering (important for concrete/polyethylene moderators)
//
// This is critical for the NESSA facility where we transport 14 MeV neutrons
// through concrete shielding and need accurate spectra at detector positions.
//============================================================================

#include "NESSAPhysicsList.hh"

#include "G4SystemOfUnits.hh"

// Physics constructors from the factory
#include "G4PhysListFactory.hh"

// Individual physics constructors we register
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4ThermalNeutrons.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4RadioactiveDecayPhysics.hh"

NESSAPhysicsList::NESSAPhysicsList()
    : G4VModularPhysicsList()
{
    // Set default cut value (production threshold)
    // 1 mm is a good default; neutrons are not affected by this cut
    SetDefaultCutValue(1.0*mm);
    SetVerboseLevel(1);

    // Electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Extra EM physics (gamma-nuclear, muon-nuclear, etc.)
    RegisterPhysics(new G4EmExtraPhysics());

    // Decay physics
    RegisterPhysics(new G4DecayPhysics());

    // Hadron elastic scattering with HP neutron data (crucial for 14 MeV)
    RegisterPhysics(new G4HadronElasticPhysicsHP());

    // Hadron inelastic: QGSP_BIC_HP
    // HP = High Precision neutron models using G4NDL data library
    // This handles n,2n / n,gamma / n,alpha / n,p etc. reactions accurately
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());

    // Stopping physics (for captured particles)
    RegisterPhysics(new G4StoppingPhysics());

    // Ion physics
    RegisterPhysics(new G4IonPhysics());

    // Thermal neutron scattering (S(alpha,beta) treatment)
    // Essential for hydrogen in concrete and polyethylene
    RegisterPhysics(new G4ThermalNeutrons());

    // Neutron tracking cut - kill neutrons below time limit to save CPU
    RegisterPhysics(new G4NeutronTrackingCut());

    // Radioactive decay (needed for activation product tracking)
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}

NESSAPhysicsList::~NESSAPhysicsList()
{
}

void NESSAPhysicsList::SetCuts()
{
    G4VUserPhysicsList::SetCuts();

    // For neutron shielding problems, the default 1mm cut is fine.
    // Neutrons are tracked down to thermal energies by HP models.
    // Secondary gammas are tracked with default threshold.
    G4cout << "### NESSA Physics List: Cuts set ###" << G4endl;
    DumpCutValuesTable();
}
