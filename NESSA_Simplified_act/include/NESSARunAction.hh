//============================================================================
// NESSARunAction.hh
// Books histograms, writes output, prints activation top-10 report
//============================================================================
#ifndef NESSARunAction_h
#define NESSARunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class NESSASteppingAction;
class G4Run;

class NESSARunAction : public G4UserRunAction
{
public:
    NESSARunAction(NESSASteppingAction* stepping);
    ~NESSARunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

private:
    void PrintActivationReport(G4int nEvents);
    NESSASteppingAction* fStepping;
};

#endif
