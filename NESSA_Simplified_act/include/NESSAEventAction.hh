//============================================================================
// NESSAEventAction.hh
// Event action: processes hits at end of each event and fills histograms
//============================================================================
#ifndef NESSAEventAction_h
#define NESSAEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class NESSAEventAction : public G4UserEventAction
{
public:
    NESSAEventAction();
    ~NESSAEventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

private:
    G4int fHCID;  // Hits collection ID
};

#endif
