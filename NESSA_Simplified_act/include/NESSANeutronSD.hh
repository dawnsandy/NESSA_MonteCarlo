//============================================================================
// NESSANeutronSD.hh
// Sensitive detector for neutron spectral measurements
// Implements track-length estimator equivalent to PHITS T-Track tally
//============================================================================
#ifndef NESSANeutronSD_h
#define NESSANeutronSD_h 1

#include "G4VSensitiveDetector.hh"
#include "NESSANeutronHit.hh"

class G4Step;
class G4HCofThisEvent;

class NESSANeutronSD : public G4VSensitiveDetector
{
public:
    NESSANeutronSD(const G4String& name,
                   const G4String& hitsCollectionName,
                   G4int nDetectors);
    ~NESSANeutronSD() override;

    // Methods from G4VSensitiveDetector
    void   Initialize(G4HCofThisEvent* hitCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    void   EndOfEvent(G4HCofThisEvent* hitCollection) override;

private:
    NESSANeutronHitsCollection* fHitsCollection;
    G4int fHCID;
    G4int fNDetectors;
};

#endif
