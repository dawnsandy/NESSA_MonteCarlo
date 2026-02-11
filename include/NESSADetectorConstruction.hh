#ifndef NESSADetectorConstruction_h
#define NESSADetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include <map>
#include <vector>
#include <string>

class G4VPhysicalVolume;

class NESSADetectorConstruction : public G4VUserDetectorConstruction
{
public:
    NESSADetectorConstruction();
    ~NESSADetectorConstruction() override;
    
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
    
    G4LogicalVolume* GetWorldLogical() const { return fWorldLogical; }
    const std::map<G4int, G4Material*>& GetMaterials() const { return fMaterials; }
    
private:
    void DefineMaterials();
    void ConstructBunkerGeometry(G4LogicalVolume* worldLV);
    void ApplyVisAttributes();
    void ApplyGeometryLabels();
    
    std::map<G4int, G4Material*> fMaterials;
    G4LogicalVolume* fWorldLogical = nullptr;
    G4bool fCheckOverlaps = false;
};

#endif
