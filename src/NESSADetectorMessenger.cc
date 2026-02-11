#include "NESSADetectorMessenger.hh"
#include "NESSAScoringConfig.hh"
#include "G4UImanager.hh"
#include <sstream>

NESSADetectorMessenger::NESSADetectorMessenger()
{
    fNessaDir = new G4UIdirectory("/nessa/");
    fNessaDir->SetGuidance("NESSA simulation control");
    
    fDetDir = new G4UIdirectory("/nessa/detector/");
    fDetDir->SetGuidance("Scoring detector configuration");
    
    fAddCmd = new G4UIcmdWithAString("/nessa/detector/add", this);
    fAddCmd->SetGuidance("Add detector: name x(cm) y(cm) z(cm) radius(cm)");
    fAddCmd->SetParameterName("params", false);
    
    fRemoveCmd = new G4UIcmdWithAString("/nessa/detector/remove", this);
    fRemoveCmd->SetGuidance("Remove detector by name");
    fRemoveCmd->SetParameterName("name", false);
    
    fEnableCmd = new G4UIcmdWithAString("/nessa/detector/enable", this);
    fEnableCmd->SetGuidance("Enable detector by name");
    fEnableCmd->SetParameterName("name", false);
    
    fDisableCmd = new G4UIcmdWithAString("/nessa/detector/disable", this);
    fDisableCmd->SetGuidance("Disable detector by name");
    fDisableCmd->SetParameterName("name", false);
    
    fListCmd = new G4UIcmdWithoutParameter("/nessa/detector/list", this);
    fListCmd->SetGuidance("List all configured detectors");
}

NESSADetectorMessenger::~NESSADetectorMessenger()
{
    delete fAddCmd; delete fRemoveCmd;
    delete fEnableCmd; delete fDisableCmd;
    delete fListCmd; delete fDetDir; delete fNessaDir;
}

void NESSADetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String val)
{
    auto& config = NESSAScoringConfig::Instance();
    
    if (cmd == fAddCmd) {
        std::istringstream iss(val);
        G4String name;
        G4double x, y, z, r;
        iss >> name >> x >> y >> z >> r;
        config.AddDetector(name, x, y, z, r);
        G4cout << "Added detector: " << name
               << " at (" << x << "," << y << "," << z << ") r=" << r << " cm" << G4endl;
    }
    else if (cmd == fRemoveCmd) {
        config.RemoveDetector(val);
        G4cout << "Removed detector: " << val << G4endl;
    }
    else if (cmd == fEnableCmd) {
        config.SetActive(val, true);
        G4cout << "Enabled: " << val << G4endl;
    }
    else if (cmd == fDisableCmd) {
        config.SetActive(val, false);
        G4cout << "Disabled: " << val << G4endl;
    }
    else if (cmd == fListCmd) {
        const auto& pts = config.GetPoints();
        G4cout << "\n=== NESSA Scoring Detectors ===" << G4endl;
        G4cout << G4String(72, '-') << G4endl;
        for (size_t i = 0; i < pts.size(); i++) {
            const auto& p = pts[i];
            G4cout << "[" << i << "] "
                   << (p.active ? "ON " : "OFF")
                   << "  " << p.name
                   << "  (" << p.x << ", " << p.y << ", " << p.z << ") cm"
                   << "  r=" << p.radius << " cm"
                   << (p.mcnpCell > 0 ? "  [MCNP " + std::to_string(p.mcnpCell) + "]" : "")
                   << G4endl;
        }
        G4cout << "Active: " << config.GetNActive() << "/" << pts.size() << G4endl;
    }
}
