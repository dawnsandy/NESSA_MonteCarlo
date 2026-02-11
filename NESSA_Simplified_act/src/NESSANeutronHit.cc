//============================================================================
// NESSANeutronHit.cc
//============================================================================

#include "NESSANeutronHit.hh"

G4ThreadLocal G4Allocator<NESSANeutronHit>* NESSANeutronHitAllocator = nullptr;

NESSANeutronHit::NESSANeutronHit()
    : G4VHit(),
      fDetectorID(-1),
      fKineticEnergy(0.),
      fPosition(G4ThreeVector()),
      fTime(0.),
      fTrackLength(0.),
      fWeight(1.)
{
}

NESSANeutronHit::~NESSANeutronHit()
{
}

NESSANeutronHit::NESSANeutronHit(const NESSANeutronHit& right)
    : G4VHit()
{
    fDetectorID    = right.fDetectorID;
    fKineticEnergy = right.fKineticEnergy;
    fPosition      = right.fPosition;
    fTime          = right.fTime;
    fTrackLength   = right.fTrackLength;
    fWeight        = right.fWeight;
}

const NESSANeutronHit& NESSANeutronHit::operator=(const NESSANeutronHit& right)
{
    fDetectorID    = right.fDetectorID;
    fKineticEnergy = right.fKineticEnergy;
    fPosition      = right.fPosition;
    fTime          = right.fTime;
    fTrackLength   = right.fTrackLength;
    fWeight        = right.fWeight;
    return *this;
}

G4bool NESSANeutronHit::operator==(const NESSANeutronHit& right) const
{
    return (this == &right) ? true : false;
}
