//============================================================================
// NESSAActionInitialization.cc
//============================================================================
#include "NESSAActionInitialization.hh"
#include "NESSAPrimaryGeneratorAction.hh"
#include "NESSARunAction.hh"
#include "NESSAEventAction.hh"
#include "NESSASteppingAction.hh"

NESSAActionInitialization::NESSAActionInitialization()
    : G4VUserActionInitialization()
{}

NESSAActionInitialization::~NESSAActionInitialization()
{}

void NESSAActionInitialization::BuildForMaster() const
{
    SetUserAction(new NESSARunAction(nullptr));
}

void NESSAActionInitialization::Build() const
{
    SetUserAction(new NESSAPrimaryGeneratorAction());
    SetUserAction(new NESSAEventAction());
    auto* stepping = new NESSASteppingAction();
    SetUserAction(stepping);
    SetUserAction(new NESSARunAction(stepping));
}
