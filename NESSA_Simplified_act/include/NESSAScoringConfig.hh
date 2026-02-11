//============================================================================
// NESSAScoringConfig.hh
// Singleton holding scoring point-detector definitions.
// Default 22 detectors from PHITS conversion; users add/remove via macro.
//============================================================================
#ifndef NESSAScoringConfig_h
#define NESSAScoringConfig_h 1

#include "globals.hh"
#include <vector>
#include <string>

struct ScoringPoint {
    std::string name;
    G4double x, y, z;     // position in cm
    G4double radius;      // scoring sphere radius in cm
    G4bool   active;
};

class NESSAScoringConfig
{
public:
    static NESSAScoringConfig& Instance() {
        static NESSAScoringConfig inst;
        return inst;
    }

    std::vector<ScoringPoint>& GetPoints() { return fPoints; }
    const std::vector<ScoringPoint>& GetPoints() const { return fPoints; }

    void AddDetector(const std::string& name,
                     G4double x, G4double y, G4double z, G4double r)
    { fPoints.push_back({name, x, y, z, r, true}); }

    void RemoveDetector(const std::string& name) {
        for (auto it = fPoints.begin(); it != fPoints.end(); ++it)
            if (it->name == name) { fPoints.erase(it); return; }
    }

    G4int GetNActive() const {
        G4int n = 0;
        for (const auto& p : fPoints) if (p.active) n++;
        return n;
    }

private:
    NESSAScoringConfig() {
        // Default 22 detectors from PHITS conversion
        // Beamline detectors (cylinders along Y at x=60 cm)
        for (int i = 0; i < 7; ++i) {
            double yStart = -110.0 + i * 5.0;
            fPoints.push_back({"Dtctr" + std::to_string(i+1),
                               60.0, yStart + 0.5, 0.0, 1.0, true});
        }
        fPoints.push_back({"Dtctr8",  60.0, -74.0, 0.0, 1.0, true});
        for (int i = 9; i <= 20; ++i) {
            double y = -70.0 + (i - 9) * 5.0 + 0.5;
            fPoints.push_back({"Dtctr" + std::to_string(i),
                               60.0, y, 0.0, 1.0, true});
        }
        // Source room detectors
        fPoints.push_back({"DtcIn1", 60.0, -149.5, 0.0, 1.0, true});
        fPoints.push_back({"DtcIn2", 10.0, -169.5, 0.0, 1.0, true});
    }

    std::vector<ScoringPoint> fPoints;
};

#endif
