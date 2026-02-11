//============================================================================
// NESSANeutronHit.hh
// Hit class for recording neutron interactions in detector volumes
// Stores kinetic energy, position, time, and detector ID for spectral analysis
//============================================================================
#ifndef NESSANeutronHit_h
#define NESSANeutronHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class NESSANeutronHit : public G4VHit
{
public:
    NESSANeutronHit();
    ~NESSANeutronHit() override;
    NESSANeutronHit(const NESSANeutronHit&);

    const NESSANeutronHit& operator=(const NESSANeutronHit&);
    G4bool operator==(const NESSANeutronHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // Setters
    void SetDetectorID(G4int id)              { fDetectorID = id; }
    void SetKineticEnergy(G4double ke)        { fKineticEnergy = ke; }
    void SetPosition(G4ThreeVector pos)       { fPosition = pos; }
    void SetTime(G4double t)                  { fTime = t; }
    void SetTrackLength(G4double len)         { fTrackLength = len; }
    void SetWeight(G4double w)                { fWeight = w; }

    // Getters
    G4int         GetDetectorID()    const { return fDetectorID; }
    G4double      GetKineticEnergy() const { return fKineticEnergy; }
    G4ThreeVector GetPosition()      const { return fPosition; }
    G4double      GetTime()          const { return fTime; }
    G4double      GetTrackLength()   const { return fTrackLength; }
    G4double      GetWeight()        const { return fWeight; }

private:
    G4int         fDetectorID;
    G4double      fKineticEnergy;
    G4ThreeVector fPosition;
    G4double      fTime;
    G4double      fTrackLength;
    G4double      fWeight;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<NESSANeutronHit> NESSANeutronHitsCollection;

extern G4ThreadLocal G4Allocator<NESSANeutronHit>* NESSANeutronHitAllocator;

inline void* NESSANeutronHit::operator new(size_t)
{
    if (!NESSANeutronHitAllocator)
        NESSANeutronHitAllocator = new G4Allocator<NESSANeutronHit>;
    return (void*)NESSANeutronHitAllocator->MallocSingle();
}

inline void NESSANeutronHit::operator delete(void* hit)
{
    NESSANeutronHitAllocator->FreeSingle((NESSANeutronHit*) hit);
}

#endif
