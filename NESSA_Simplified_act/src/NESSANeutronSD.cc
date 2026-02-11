//============================================================================
// NESSANeutronSD.cc
// Sensitive detector for neutron spectra measurement
// Records neutron kinetic energy and track length for each step in detectors
// This is equivalent to the PHITS T-Track tally (unit=3: 1/cm^2/MeV/source)
//============================================================================

#include "NESSANeutronSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Neutron.hh"

NESSANeutronSD::NESSANeutronSD(const G4String& name,
                                const G4String& hitsCollectionName,
                                G4int nDetectors)
    : G4VSensitiveDetector(name),
      fHitsCollection(nullptr),
      fHCID(-1),
      fNDetectors(nDetectors)
{
    collectionName.insert(hitsCollectionName);
}

NESSANeutronSD::~NESSANeutronSD()
{
}

void NESSANeutronSD::Initialize(G4HCofThisEvent* hce)
{
    // Create hits collection
    fHitsCollection = new NESSANeutronHitsCollection(
        SensitiveDetectorName, collectionName[0]);

    // Register collection in the event
    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(
            SensitiveDetectorName + "/" + collectionName[0]);
    }
    hce->AddHitsCollection(fHCID, fHitsCollection);
}

G4bool NESSANeutronSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    // Only score neutrons
    if (step->GetTrack()->GetDefinition() != G4Neutron::NeutronDefinition())
        return false;

    G4double stepLength = step->GetStepLength();
    if (stepLength <= 0.) return false;

    // Get detector copy number (= detector index)
    G4int detID = step->GetPreStepPoint()->GetTouchableHandle()
                       ->GetCopyNumber();

    // Create a new hit for this step
    auto hit = new NESSANeutronHit();
    hit->SetDetectorID(detID);
    hit->SetKineticEnergy(step->GetPreStepPoint()->GetKineticEnergy());
    hit->SetPosition(step->GetPreStepPoint()->GetPosition());
    hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());
    hit->SetTrackLength(stepLength);
    hit->SetWeight(step->GetPreStepPoint()->GetWeight());

    fHitsCollection->insert(hit);

    return true;
}

void NESSANeutronSD::EndOfEvent(G4HCofThisEvent*)
{
    // Optionally print summary per event (verbose mode)
    if (verboseLevel > 1) {
        G4int nHits = fHitsCollection->entries();
        G4cout << "\n----> Neutron hits in this event: " << nHits << G4endl;
    }
}
