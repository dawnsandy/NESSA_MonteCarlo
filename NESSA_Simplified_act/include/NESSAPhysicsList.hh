//============================================================================
// NESSAPhysicsList.hh
// Physics list for NESSA neutron beamline simulation
// Optimized for 14 MeV D-T neutron transport through shielding
//============================================================================
#ifndef NESSAPhysicsList_h
#define NESSAPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class NESSAPhysicsList : public G4VModularPhysicsList
{
public:
    NESSAPhysicsList();
    ~NESSAPhysicsList() override;

    void SetCuts() override;
};

#endif
