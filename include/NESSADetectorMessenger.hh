#ifndef NESSADetectorMessenger_h
#define NESSADetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIdirectory.hh"

/// Macro commands for detector configuration:
///   /nessa/detector/add name x y z r
///   /nessa/detector/remove name
///   /nessa/detector/enable name
///   /nessa/detector/disable name
///   /nessa/detector/list
class NESSADetectorMessenger : public G4UImessenger
{
public:
    NESSADetectorMessenger();
    ~NESSADetectorMessenger() override;
    void SetNewValue(G4UIcommand*, G4String) override;
    
private:
    G4UIdirectory*          fNessaDir;
    G4UIdirectory*          fDetDir;
    G4UIcmdWithAString*     fAddCmd;
    G4UIcmdWithAString*     fRemoveCmd;
    G4UIcmdWithAString*     fEnableCmd;
    G4UIcmdWithAString*     fDisableCmd;
    G4UIcmdWithoutParameter* fListCmd;
};

#endif
