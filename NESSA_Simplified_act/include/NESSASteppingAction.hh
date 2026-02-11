//============================================================================
// NESSASteppingAction.hh
// 1) Track ALL radioactive isotope production from neutron reactions
// 2) Fill 2D flux/dose maps over entire room
// 3) Score neutron AND gamma spectra+dose in point detectors
//============================================================================
#ifndef NESSASteppingAction_h
#define NESSASteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <map>
#include <string>

struct IsotopeID {
    G4int Z, A, isomer;
    bool operator<(const IsotopeID& o) const {
        if (Z != o.Z) return Z < o.Z;
        if (A != o.A) return A < o.A;
        return isomer < o.isomer;
    }
};

struct IsotopeRecord {
    G4double count      = 0;
    G4double halfLife_s = 0;
};

class NESSASteppingAction : public G4UserSteppingAction
{
public:
    NESSASteppingAction();
    ~NESSASteppingAction() override;

    void UserSteppingAction(const G4Step* step) override;
    void Reset();

    using IsotopeMap = std::map<IsotopeID, IsotopeRecord>;
    using VolumeIsotopeMap = std::map<std::string, IsotopeMap>;

    const IsotopeMap&       GetGlobalProduction() const { return fGlobalProd; }
    const VolumeIsotopeMap& GetVolumeProduction() const { return fVolumeProd; }

    static std::string IsotopeName(const IsotopeID& id);
    static const char* ElementSymbol(G4int Z);

private:
    IsotopeMap       fGlobalProd;
    VolumeIsotopeMap fVolumeProd;
};

#endif
