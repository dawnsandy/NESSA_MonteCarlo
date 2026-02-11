#ifndef NESSARunAction_h
#define NESSARunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Timer.hh"

class NESSASteppingAction;

class NESSARunAction : public G4UserRunAction
{
public:
    NESSARunAction(NESSASteppingAction* stepping);
    ~NESSARunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

private:
    void PrintActivationReport(G4int nEvents);
    
    G4Timer fTimer;
    NESSASteppingAction* fSteppingAction;
};

#endif
