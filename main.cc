// ============================================================
// NESSA Bunker Geant4 Simulation - Main Program
// Converted from MCNP5: FREIA/NESSA facility, Uppsala University
// Adelphi DT-110 neutron generator (14 MeV)
// ============================================================

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BIC_HP.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "NESSADetectorConstruction.hh"
#include "NESSAActionInitialization.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Serial mode for stability with complex boolean geometry
    auto* runManager = G4RunManagerFactory::CreateRunManager(
        G4RunManagerType::Serial);

    // Detector
    runManager->SetUserInitialization(new NESSADetectorConstruction());

    // Physics: QGSP_BIC_HP (high-precision neutron transport)
    // + RadioactiveDecay for Ar-41 production tracking
    auto physicsList = new QGSP_BIC_HP;
    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics());
    runManager->SetUserInitialization(physicsList);

    // User actions
    runManager->SetUserInitialization(new NESSAActionInitialization());

    // MUST initialize before visualization
    runManager->Initialize();

    // Visualization
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    auto UImanager = G4UImanager::GetUIpointer();

    if (!ui) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        UImanager->ApplyCommand("/control/execute macros/init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
    return 0;
}
