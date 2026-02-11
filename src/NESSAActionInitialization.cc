#include "NESSAActionInitialization.hh"
#include "NESSAPrimaryGeneratorAction.hh"
#include "NESSARunAction.hh"
#include "NESSASteppingAction.hh"

void NESSAActionInitialization::BuildForMaster() const
{
    SetUserAction(new NESSARunAction(nullptr));
}

void NESSAActionInitialization::Build() const
{
    SetUserAction(new NESSAPrimaryGeneratorAction());
    auto* stepping = new NESSASteppingAction();
    SetUserAction(stepping);
    SetUserAction(new NESSARunAction(stepping));
}
