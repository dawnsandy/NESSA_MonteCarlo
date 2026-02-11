//============================================================================
// NESSAEventAction.cc
// Simplified: all per-detector scoring is now in NESSASteppingAction.
// The sensitive detector hits collection is still built (for future use)
// but histograms are filled by the stepping action for both n and gamma.
//============================================================================
#include "NESSAEventAction.hh"
#include "G4Event.hh"

NESSAEventAction::NESSAEventAction()
    : G4UserEventAction(), fHCID(-1)
{}

NESSAEventAction::~NESSAEventAction()
{}

void NESSAEventAction::BeginOfEventAction(const G4Event*)
{}

void NESSAEventAction::EndOfEventAction(const G4Event*)
{
    // Scoring is handled by NESSASteppingAction which fires for
    // every step in detector volumes AND tracks activation products.
}
