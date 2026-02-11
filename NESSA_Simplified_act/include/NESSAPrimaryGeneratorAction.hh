//============================================================================
// NESSAPrimaryGeneratorAction.hh
// Primary generator using G4GeneralParticleSource (GPS)
// All source parameters are configured via gps_source.mac macro
//============================================================================
#ifndef NESSAPrimaryGeneratorAction_h
#define NESSAPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class NESSAPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    NESSAPrimaryGeneratorAction();
    ~NESSAPrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* event) override;

    const G4GeneralParticleSource* GetGPS() const { return fGPS; }

private:
    G4GeneralParticleSource* fGPS;
};

#endif
