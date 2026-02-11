//============================================================================
// nessa_sim.cc
// Main program for NESSA simulation with activation tracking
//============================================================================
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SteppingVerbose.hh"

#include "NESSADetectorConstruction.hh"
#include "NESSAPhysicsList.hh"
#include "NESSAActionInitialization.hh"
#include "NESSADetectorMessenger.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4int precision = 4;
    G4SteppingVerbose::UseBestUnit(precision);

    // Serial mode — SteppingAction accumulates activation inventory
    // which is not safe to merge across threads without extra work
    auto runManager = G4RunManagerFactory::CreateRunManager(
        G4RunManagerType::Serial);

    runManager->SetUserInitialization(new NESSADetectorConstruction());
    runManager->SetUserInitialization(new NESSAPhysicsList());
    runManager->SetUserInitialization(new NESSAActionInitialization());

    // Instantiate detector messenger (registers /nessa/detector/ commands)
    auto* messenger = new NESSADetectorMessenger();

    auto visManager = new G4VisExecutive();
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

    delete messenger;
    delete visManager;
    delete runManager;

    return 0;
}
