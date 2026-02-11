#ifndef NESSAScoringConfig_h
#define NESSAScoringConfig_h 1

#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include <vector>
#include <string>

/// A single scoring point detector
struct ScoringPoint {
    G4String name;
    G4double x, y, z;    // cm
    G4double radius;      // cm
    G4int    mcnpCell;    // corresponding MCNP cell, -1 if new
    G4bool   active;      // can be toggled from macro
};

/// Singleton configuration for scoring
class NESSAScoringConfig {
public:
    static NESSAScoringConfig& Instance() {
        static NESSAScoringConfig instance;
        return instance;
    }
    
    const std::vector<ScoringPoint>& GetPoints() const { return fPoints; }
    std::vector<ScoringPoint>& GetPointsMutable() { return fPoints; }
    
    /// Add a detector from macro command
    void AddDetector(const G4String& name, G4double x, G4double y, G4double z,
                     G4double r) {
        fPoints.push_back({name, x, y, z, r, -1, true});
    }
    
    /// Remove detector by name
    void RemoveDetector(const G4String& name) {
        for (auto it = fPoints.begin(); it != fPoints.end(); ++it) {
            if (it->name == name) { fPoints.erase(it); return; }
        }
    }
    
    /// Enable/disable
    void SetActive(const G4String& name, G4bool active) {
        for (auto& p : fPoints) {
            if (p.name == name) { p.active = active; return; }
        }
    }
    
    G4int GetNActive() const {
        G4int n = 0;
        for (const auto& p : fPoints) if (p.active) n++;
        return n;
    }
    
private:
    NESSAScoringConfig() {
        // Default detectors matching MCNP irradiation positions
        // CUP positions (directly above source)
        fPoints.push_back({"CUP_0mm",       195, 371, 150.7, 0.10, 8000, true});
        fPoints.push_back({"CUP_3mm",       195, 371, 151.0, 0.19, 8001, true});
        fPoints.push_back({"CUP_10mm",      195, 371, 151.7, 0.25, 8002, true});
        fPoints.push_back({"CUP_43mm",      195, 371, 155.0, 0.25, 8003, true});
        fPoints.push_back({"CUP_93mm",      195, 371, 160.0, 0.25, 8004, true});
        // Beamline positions
        fPoints.push_back({"CollimatorIn",   195, 390, 150, 5.0, 8100, true});
        fPoints.push_back({"CollimatorOut",  195, 420, 150, 5.0, 8200, true});
        fPoints.push_back({"OutLabyrinth",   195, 635, 150, 5.0, 8300, true});
        fPoints.push_back({"FissionChamber",  85, 380, 210, 5.0, 8400, true});
        fPoints.push_back({"HVS",           195, 533, 150, 1.5, 8500, true});
        fPoints.push_back({"HVS_offset",    145, 533, 150, 1.5, 8600, true});
        // External dose points
        fPoints.push_back({"D1_detector",    185, 564.5, 150, 2.3, -1, true});
        fPoints.push_back({"OutsideRight",   380, 400, 150, 5.0, -1, true});
        fPoints.push_back({"OutsideLeft",   -150, 400, 150, 5.0, -1, true});
        fPoints.push_back({"OutsideFront",   195, 900, 150, 5.0, -1, true});
        fPoints.push_back({"OutsideBack",    195, 140, 150, 5.0, -1, true});
        fPoints.push_back({"AboveRoof",      195, 400, 340, 5.0, -1, true});
        fPoints.push_back({"Lab_entrance",   195, 720, 150, 5.0, -1, true});
        fPoints.push_back({"Lab_middle",     195, 780, 150, 5.0, -1, true});
        fPoints.push_back({"Lab_exit",       195, 860, 150, 5.0, -1, true});
    }
    
    std::vector<ScoringPoint> fPoints;
};

#endif
