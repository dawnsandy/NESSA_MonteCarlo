#ifndef NESSAPrimaryGeneratorAction_h
#define NESSAPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include <vector>

class G4Event;

/// Adelphi DT neutron generator source.
/// Implements the MCNP FDIR (direction-dependent energy) source:
/// - Source position: (195, 371, 150) cm
/// - Source axis: (0, 0, 1) = Z-axis
/// - Radial distribution: uniform disk, R=0.9 cm
/// - Extension along axis: 0 to 0.00001 cm (essentially a point)
/// - Angular-energy correlation from Adelphi DT kinematics
///   (200 direction cosine bins × 501 energy bins each)
class NESSAPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    NESSAPrimaryGeneratorAction();
    ~NESSAPrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event*) override;

private:
    void LoadSourceData(const G4String& filename);
    G4double SampleEnergy(G4int dirBin);
    G4int SampleDirectionBin();
    
    G4ParticleGun* fParticleGun = nullptr;
    
    // Source position and geometry
    G4ThreeVector fSourcePos;
    G4ThreeVector fSourceAxis;
    G4double fSourceRadius;
    
    // Direction-dependent energy distributions
    G4int fNDirBins;
    G4int fNEnergyBins;
    std::vector<G4double> fDirBins;       // direction cosine bin edges
    std::vector<G4double> fDirCDF;        // cumulative distribution for direction
    std::vector<G4double> fEnergyBins;    // energy bin edges (MeV)
    std::vector<std::vector<G4double>> fEnergyCDFs;  // CDF for each direction bin
};

#endif
