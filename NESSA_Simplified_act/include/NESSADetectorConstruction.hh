//============================================================================
// NESSADetectorConstruction.hh
// Geometry definition for the NESSA neutron beamline facility
// Converted from PHITS input: bunker walls, collimator, shielding, detectors
//============================================================================
#ifndef NESSADetectorConstruction_h
#define NESSADetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "globals.hh"
#include <vector>

class NESSADetectorConstruction : public G4VUserDetectorConstruction
{
public:
    NESSADetectorConstruction();
    ~NESSADetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    // Accessor for detector logical volumes (for sensitive detector assignment)
    const std::vector<G4LogicalVolume*>& GetDetectorLogVols() const
    { return fDetectorLogVols; }

    G4LogicalVolume* GetDetectorLogVol(G4int idx) const
    { return fDetectorLogVols.at(idx); }

    G4int GetNumberOfDetectors() const
    { return static_cast<G4int>(fDetectorLogVols.size()); }

private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // Materials
    G4Material* fAir;
    G4Material* fConcrete;
    G4Material* fStainlessSteel;
    G4Material* fLead;
    G4Material* fAluminum;
    G4Material* fPolyethylene;
    G4Material* fBoratedPoly;

    // Detector logical volumes for scoring
    std::vector<G4LogicalVolume*> fDetectorLogVols;

    G4bool fCheckOverlaps;
};

#endif
