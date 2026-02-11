//============================================================================
// NESSADetectorMessenger.hh
// Macro commands for configuring scoring detector positions at runtime:
//   /nessa/detector/add name x y z r
//   /nessa/detector/remove name
//   /nessa/detector/list
//============================================================================
#ifndef NESSADetectorMessenger_h
#define NESSADetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIdirectory.hh"

class NESSADetectorMessenger : public G4UImessenger
{
public:
    NESSADetectorMessenger();
    ~NESSADetectorMessenger() override;
    void SetNewValue(G4UIcommand*, G4String) override;

private:
    G4UIdirectory*           fNessaDir;
    G4UIdirectory*           fDetDir;
    G4UIcmdWithAString*      fAddCmd;
    G4UIcmdWithAString*      fRemoveCmd;
    G4UIcmdWithoutParameter* fListCmd;
};

#endif
