#ifndef NESSASteppingAction_h
#define NESSASteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4String.hh"
#include "G4Types.hh"
#include <map>
#include <string>

class G4Step;

/// Isotope identifier: (Z, A, isomer)
struct IsotopeID {
    G4int Z;
    G4int A;
    G4int isomer;  // 0 = ground state, 1 = metastable
    
    bool operator<(const IsotopeID& o) const {
        if (Z != o.Z) return Z < o.Z;
        if (A != o.A) return A < o.A;
        return isomer < o.isomer;
    }
    bool operator==(const IsotopeID& o) const {
        return Z == o.Z && A == o.A && isomer == o.isomer;
    }
};

/// Production record for one isotope
struct IsotopeRecord {
    G4double count = 0;       // weighted production count
    G4double halfLife_s = 0;  // half-life in seconds (0 = stable)
};

/// Tracks ALL radioactive isotope production from neutron reactions.
/// Catches secondaries from nCapture, neutronInelastic, etc.
/// At end-of-run, RunAction queries and ranks the top activated isotopes.
class NESSASteppingAction : public G4UserSteppingAction
{
public:
    NESSASteppingAction();
    ~NESSASteppingAction() override;
    
    void UserSteppingAction(const G4Step*) override;
    void Reset();
    
    /// Global production: isotope -> total weighted count
    using IsotopeMap = std::map<IsotopeID, IsotopeRecord>;
    const IsotopeMap& GetGlobalProduction() const { return fGlobalProd; }
    
    /// Per-volume production: volume -> (isotope -> record)
    using VolumeIsotopeMap = std::map<std::string, IsotopeMap>;
    const VolumeIsotopeMap& GetVolumeProduction() const { return fVolumeProd; }
    
    /// Human-readable isotope name (e.g. "Ar-41", "Fe-59m")
    static std::string IsotopeName(const IsotopeID& id);
    
    /// Element symbol from Z
    static const char* ElementSymbol(G4int Z);
    
private:
    IsotopeMap       fGlobalProd;
    VolumeIsotopeMap fVolumeProd;
};

#endif
