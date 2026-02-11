#ifndef NESSAScoringSD_h
#define NESSAScoringSD_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;

/// Records neutron/photon energy spectra and dose in scoring volumes.
/// Uses G4AnalysisManager histograms and ntuples for ROOT output.
class NESSAScoringSD : public G4VSensitiveDetector
{
public:
    NESSAScoringSD(const G4String& name);
    ~NESSAScoringSD() override;

    void Initialize(G4HCofThisEvent*) override;
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;
};

#endif
