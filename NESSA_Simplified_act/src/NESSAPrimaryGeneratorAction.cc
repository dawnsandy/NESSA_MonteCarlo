//============================================================================
// NESSAPrimaryGeneratorAction.cc
// GPS-based source: configured entirely via macro file gps_source.mac
// Default fallback: 14 MeV neutron at the D-T generator position
//============================================================================

#include "NESSAPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"

NESSAPrimaryGeneratorAction::NESSAPrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fGPS(new G4GeneralParticleSource())
{
    // GPS is configured via macro commands in gps_source.mac
    // No hard-coded defaults needed here; the macro handles everything.
    // If no macro is loaded, GPS defaults to 1 MeV geantino at origin.
}

NESSAPrimaryGeneratorAction::~NESSAPrimaryGeneratorAction()
{
    delete fGPS;
}

void NESSAPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fGPS->GeneratePrimaryVertex(event);
}
