//============================================================================
// NESSADetectorConstruction.cc
// Full geometry of the NESSA neutron beamline facility at Uppsala University
// Converted from PHITS input file with importance biasing
//
// Coordinate system (same as PHITS, all in cm converted to mm):
//   PHITS uses cm internally; Geant4 uses mm as default unit.
//   All dimensions below use explicit *cm or *mm units.
//
// Key features:
//   - Concrete bunker walls (layered for biasing in PHITS, single here)
//   - SS-lined concrete collimator with 10 cm radius aperture
//   - 22 detector positions (air-filled cylinders, R=1cm, H=1cm)
//   - Lead + concrete + polyethylene shielding
//   - Aluminum source generator housing
//   - Borated polyethylene blocks
//============================================================================

#include "NESSADetectorConstruction.hh"
#include "NESSANeutronSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4MultiUnion.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NESSADetectorConstruction::NESSADetectorConstruction()
    : fAir(nullptr), fConcrete(nullptr), fStainlessSteel(nullptr),
      fLead(nullptr), fAluminum(nullptr), fPolyethylene(nullptr),
      fBoratedPoly(nullptr), fCheckOverlaps(true)
{
}

NESSADetectorConstruction::~NESSADetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NESSADetectorConstruction::DefineMaterials()
{
    auto nistManager = G4NistManager::Instance();

    //--- Air (PHITS mat[32]) ---
    // Using NIST air; composition matches PHITS (N 75.5%, O 23.2%, Ar 1.3%, C 0.01%)
    fAir = nistManager->FindOrBuildMaterial("G4_AIR");

    //--- Portland Concrete (PHITS mat[27], density 2.3 g/cm3) ---
    fConcrete = new G4Material("PortlandConcrete", 2.3*g/cm3, 10);
    fConcrete->AddElement(nistManager->FindOrBuildElement("H"),  0.01);
    fConcrete->AddElement(nistManager->FindOrBuildElement("C"),  0.001);
    fConcrete->AddElement(nistManager->FindOrBuildElement("O"),  0.529107);
    fConcrete->AddElement(nistManager->FindOrBuildElement("Na"), 0.016);
    fConcrete->AddElement(nistManager->FindOrBuildElement("Mg"), 0.002);
    fConcrete->AddElement(nistManager->FindOrBuildElement("Al"), 0.033872);
    fConcrete->AddElement(nistManager->FindOrBuildElement("Si"), 0.337021);
    fConcrete->AddElement(nistManager->FindOrBuildElement("K"),  0.013);
    fConcrete->AddElement(nistManager->FindOrBuildElement("Ca"), 0.044);
    fConcrete->AddElement(nistManager->FindOrBuildElement("Fe"), 0.014);

    //--- Stainless Steel 304 (PHITS mat[30], density 8.0 g/cm3) ---
    // PHITS uses atom fractions: Cr 18, Fe 74, Ni 8
    fStainlessSteel = new G4Material("StainlessSteel304", 8.0*g/cm3, 3);
    fStainlessSteel->AddElement(nistManager->FindOrBuildElement("Cr"), 18);
    fStainlessSteel->AddElement(nistManager->FindOrBuildElement("Fe"), 74);
    fStainlessSteel->AddElement(nistManager->FindOrBuildElement("Ni"),  8);

    //--- Lead (PHITS mat[17], density 11.35 g/cm3) ---
    fLead = nistManager->FindOrBuildMaterial("G4_Pb");

    //--- Aluminum (PHITS mat[10], density 2.699 g/cm3) ---
    fAluminum = nistManager->FindOrBuildMaterial("G4_Al");

    //--- Polyethylene (PHITS mat[33], density 0.94 g/cm3) ---
    // CH2 composition
    fPolyethylene = new G4Material("Polyethylene", 0.94*g/cm3, 2);
    fPolyethylene->AddElement(nistManager->FindOrBuildElement("H"), 2);
    fPolyethylene->AddElement(nistManager->FindOrBuildElement("C"), 1);

    //--- Borated Polyethylene (PHITS mat[28], density 0.95 g/cm3) ---
    // Mass fractions: H 11.6%, B-10 2%, B-11 8%, C 61.2%, O 17.2%
    fBoratedPoly = new G4Material("BoratedPolyethylene", 0.95*g/cm3, 4);
    fBoratedPoly->AddElement(nistManager->FindOrBuildElement("H"),  0.116);
    fBoratedPoly->AddElement(nistManager->FindOrBuildElement("B"),  0.100);  // 2% B10 + 8% B11
    fBoratedPoly->AddElement(nistManager->FindOrBuildElement("C"),  0.612);
    fBoratedPoly->AddElement(nistManager->FindOrBuildElement("O"),  0.172);

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NESSADetectorConstruction::Construct()
{
    DefineMaterials();
    return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NESSADetectorConstruction::DefineVolumes()
{
    //=========================================================================
    // WORLD VOLUME
    // PHITS surface 4: rpp -280 280 -390 390 -220 220 (cm)
    // We make the world slightly larger
    //=========================================================================
    G4double worldHx = 300.0*cm;
    G4double worldHy = 400.0*cm;
    G4double worldHz = 230.0*cm;

    auto solidWorld = new G4Box("World", worldHx, worldHy, worldHz);
    auto logicWorld = new G4LogicalVolume(solidWorld, fAir, "World");
    auto physWorld  = new G4PVPlacement(nullptr,       // no rotation
                                        G4ThreeVector(), // at (0,0,0)
                                        logicWorld,      // its logical volume
                                        "World",         // name
                                        nullptr,         // mother volume
                                        false,           // no boolean ops
                                        0,               // copy number
                                        fCheckOverlaps);

    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    //=========================================================================
    // BUNKER STRUCTURE
    // PHITS surface 3: rpp -240 240 -360 360 -120 120 (cm)
    // This is the main concrete enclosure. In PHITS it was split into
    // layered cells for importance biasing. In Geant4 we build it as
    // solid concrete walls with the room carved out.
    //=========================================================================

    //--- Outer concrete shell ---
    // Full bunker outer dimensions
    G4double bunkerHx = 240.0*cm;
    G4double bunkerHy = 360.0*cm;
    G4double bunkerHz = 120.0*cm;

    //--- Left wall (x < 0 side): from x=-240 to x=-120 (thickness 120 cm) ---
    // PHITS cells 4-9: layered concrete
    auto solidLeftWall = new G4Box("LeftWall",
                                    60.0*cm,   // half-x = (240-120)/2 = 60
                                    bunkerHy,  // half-y
                                    bunkerHz); // half-z
    auto logicLeftWall = new G4LogicalVolume(solidLeftWall, fConcrete, "LeftWall");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(-180.0*cm, 0, 0),  // center at x=-180
                      logicLeftWall, "LeftWall", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Right wall (x > 0 side): from x=148 to x=240 ---
    // PHITS cells 10-14: x from 148 to 210+ cm
    // Wall from x=148 to x=240, full height
    auto solidRightWall = new G4Box("RightWall",
                                     46.0*cm,   // half-x = (240-148)/2 = 46
                                     bunkerHy,
                                     bunkerHz);
    auto logicRightWall = new G4LogicalVolume(solidRightWall, fConcrete, "RightWall");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(194.0*cm, 0, 0),  // center at x=(148+240)/2=194
                      logicRightWall, "RightWall", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Back wall: y from -360 to -260 (region behind source) ---
    // PHITS cells 15-18: concrete layers from y=-340 to y=-260
    // Plus PHITS cell 19: polyethylene from y=-260 to y=-240 (handled separately)
    // Concrete from y=-360 to -260, x from -120 to 148
    auto solidBackWallConcrete = new G4Box("BackWallConcrete",
                                            134.0*cm,  // half-x = (148-(-120))/2 = 134
                                            50.0*cm,   // half-y = (360-260)/2 = 50
                                            bunkerHz);
    auto logicBackWallConcrete = new G4LogicalVolume(solidBackWallConcrete, fConcrete,
                                                      "BackWallConcrete");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(14.0*cm, -310.0*cm, 0),
                      logicBackWallConcrete, "BackWallConcrete", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Polyethylene wall behind back wall (PHITS cell 19) ---
    // y from -260 to -240 (after concrete layers), x from -120 to 108
    // PHITS: +24 -25 -18 +12: y from -260 to -240, x from -120 to 108
    auto solidPEBackWall = new G4Box("PEBackWall",
                                      114.0*cm,  // half-x = (108-(-120))/2 = 114
                                      10.0*cm,   // half-y = (260-240)/2 = 10
                                      bunkerHz);
    auto logicPEBackWall = new G4LogicalVolume(solidPEBackWall, fPolyethylene, "PEBackWall");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(-6.0*cm, -250.0*cm, 0),
                      logicPEBackWall, "PEBackWall", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Lead shield behind source wall (PHITS cell 26) ---
    // x from 108 to 148, y from -260 to -115
    auto solidLeadShield = new G4Box("LeadShield",
                                      20.0*cm,   // half-x = (148-108)/2 = 20
                                      72.5*cm,   // half-y = (260-115)/2 = 72.5
                                      bunkerHz);
    auto logicLeadShield = new G4LogicalVolume(solidLeadShield, fLead, "LeadShield");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(128.0*cm, -187.5*cm, 0),
                      logicLeadShield, "LeadShield", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Concrete shield behind source (PHITS cell 27) ---
    // x from 108 to 148, y from -240 to -115 (behind polyethylene, in front of lead)
    // Actually: -18 +19 -20 +25: x from 108 to 148, y from -260 to -115
    // This overlaps with lead; from PHITS the concrete is between PE and lead
    // Let's place concrete between the PE and the lead:
    // y from -240 to -115, x from 108 to 148
    auto solidConcreteShield = new G4Box("ConcreteShieldBack",
                                          20.0*cm,
                                          62.5*cm,   // half-y = (240-115)/2 = 62.5
                                          bunkerHz);
    auto logicConcreteShield = new G4LogicalVolume(solidConcreteShield, fConcrete,
                                                    "ConcreteShieldBack");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(128.0*cm, -177.5*cm, 0),
                      logicConcreteShield, "ConcreteShieldBack", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Front wall: y = 360 side ---
    // There's no explicit front wall in PHITS; the bunker has openings
    // The concrete blocks (cells 24, 25) serve as partial walls

    //--- Roof (PHITS cell 31, surface 5): z from 120 to 200 ---
    auto solidRoof = new G4Box("Roof",
                                bunkerHx,
                                bunkerHy,
                                40.0*cm);  // half-z = (200-120)/2 = 40
    auto logicRoof = new G4LogicalVolume(solidRoof, fConcrete, "Roof");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0, 0, 160.0*cm),
                      logicRoof, "Roof", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Floor (PHITS cell 32, surface 6): z from -140 to -120 ---
    auto solidFloor = new G4Box("Floor",
                                 bunkerHx,
                                 bunkerHy,
                                 10.0*cm);  // half-z = (140-120)/2 = 10
    auto logicFloor = new G4LogicalVolume(solidFloor, fConcrete, "Floor");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0, 0, -130.0*cm),
                      logicFloor, "Floor", logicWorld,
                      false, 0, fCheckOverlaps);

    //=========================================================================
    // COLLIMATOR ASSEMBLY
    // The collimator is the critical neutron streaming path
    //=========================================================================

    //--- Concrete collimator block with Fe wall (PHITS cell 22, surface 26) ---
    // rpp 60 160 -115 -75 -120 120 (Fe+Concrete block)
    auto solidCollBlock = new G4Box("CollimatorBlock",
                                     50.0*cm,   // half-x = (160-60)/2 = 50
                                     20.0*cm,   // half-y = (115-75)/2 = 20
                                     bunkerHz);
    auto logicCollBlock = new G4LogicalVolume(solidCollBlock, fConcrete, "CollimatorBlock");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(110.0*cm, -95.0*cm, 0),
                      logicCollBlock, "CollimatorBlock", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Source side concrete collimator (PHITS cell 23, surface 27) ---
    // rpp -40 60 -115 -75 -120 120
    auto solidCollSrc = new G4Box("CollimatorSrc",
                                   50.0*cm,   // half-x = (60-(-40))/2 = 50
                                   20.0*cm,
                                   bunkerHz);
    auto logicCollSrc = new G4LogicalVolume(solidCollSrc, fConcrete, "CollimatorSrc");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(10.0*cm, -95.0*cm, 0),
                      logicCollSrc, "CollimatorSrc", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Stainless Steel collimator liner (PHITS cell 21, surface 29) ---
    // rcc 60 -115 0  0 40 0  R=20 (cylinder along y-axis)
    // This is placed INSIDE the concrete blocks
    auto rotY = new G4RotationMatrix();
    rotY->rotateX(90.0*deg);  // Rotate cylinder from z-axis to y-axis

    auto solidSSLiner = new G4Tubs("SSLiner",
                                    10.0*cm,   // inner radius (aperture)
                                    20.0*cm,   // outer radius
                                    20.0*cm,   // half-length = 40/2 = 20 cm
                                    0, 360.0*deg);
    auto logicSSLiner = new G4LogicalVolume(solidSSLiner, fStainlessSteel, "SSLiner");
    new G4PVPlacement(rotY,
                      G4ThreeVector(60.0*cm, -95.0*cm, 0),
                      logicSSLiner, "SSLiner", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Collimator aperture (air channel, PHITS cell 20, surface 28) ---
    // rcc 60 -115 0  0 40 0  R=10
    auto solidAperture = new G4Tubs("CollimatorAperture",
                                     0,
                                     10.0*cm,   // radius
                                     20.0*cm,   // half-length
                                     0, 360.0*deg);
    auto logicAperture = new G4LogicalVolume(solidAperture, fAir, "CollimatorAperture");
    new G4PVPlacement(rotY,
                      G4ThreeVector(60.0*cm, -95.0*cm, 0),
                      logicAperture, "CollimatorAperture", logicWorld,
                      false, 0, fCheckOverlaps);

    //=========================================================================
    // SHIELDING BLOCKS
    //=========================================================================

    //--- Concrete block at User Area 2 (PHITS cell 25, surface 30) ---
    // rpp -40 160 120 200 -120 120
    auto solidUA2Block = new G4Box("UserArea2Block",
                                    100.0*cm,  // half-x = (160-(-40))/2
                                    40.0*cm,   // half-y = (200-120)/2
                                    bunkerHz);
    auto logicUA2Block = new G4LogicalVolume(solidUA2Block, fConcrete, "UserArea2Block");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(60.0*cm, 160.0*cm, 0),
                      logicUA2Block, "UserArea2Block", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Concrete block near entrance (PHITS cell 24, surface 31) ---
    // rpp -120 80 280 360 -120 120
    auto solidEntrBlock = new G4Box("EntranceBlock",
                                     100.0*cm,  // half-x = (80-(-120))/2
                                     40.0*cm,   // half-y = (360-280)/2
                                     bunkerHz);
    auto logicEntrBlock = new G4LogicalVolume(solidEntrBlock, fConcrete, "EntranceBlock");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(-20.0*cm, 320.0*cm, 0),
                      logicEntrBlock, "EntranceBlock", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Borated Poly block at user area 2 (PHITS cell 28, surface 32) ---
    // rpp -120 -30 113 119.5 -120 110
    auto solidBPolyUA2 = new G4Box("BPolyUA2",
                                    45.0*cm,    // half-x = (120-30)/2
                                    3.25*cm,    // half-y = (119.5-113)/2
                                    115.0*cm);  // half-z = (110-(-120))/2
    auto logicBPolyUA2 = new G4LogicalVolume(solidBPolyUA2, fBoratedPoly, "BPolyUA2");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(-75.0*cm, 116.25*cm, -5.0*cm),
                      logicBPolyUA2, "BPolyUA2", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Borated Poly block at entrance (PHITS cell 29, surface 33) ---
    // rpp 70 170 360 370 -120 120
    auto solidBPolyEntr = new G4Box("BPolyEntrance",
                                     50.0*cm,   // half-x = (170-70)/2
                                     5.0*cm,    // half-y = (370-360)/2
                                     bunkerHz);
    auto logicBPolyEntr = new G4LogicalVolume(solidBPolyEntr, fBoratedPoly, "BPolyEntrance");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(120.0*cm, 365.0*cm, 0),
                      logicBPolyEntr, "BPolyEntrance", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Polyethylene outside right wall (PHITS cell 30, surface 34) ---
    // rpp 240 260 -360 -75 -120 120
    auto solidPEOutside = new G4Box("PEOutsideWall",
                                     10.0*cm,    // half-x = (260-240)/2
                                     142.5*cm,   // half-y = (360-75)/2
                                     bunkerHz);
    auto logicPEOutside = new G4LogicalVolume(solidPEOutside, fPolyethylene, "PEOutsideWall");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(250.0*cm, -217.5*cm, 0),
                      logicPEOutside, "PEOutsideWall", logicWorld,
                      false, 0, fCheckOverlaps);

    //=========================================================================
    // SOURCE GENERATOR ASSEMBLY
    //=========================================================================

    //--- Aluminum source housing (PHITS cell 56, surface 58) ---
    // rcc 60 -140 0  -30 0 0  R=5 (cylinder along -x direction)
    auto rotMinusX = new G4RotationMatrix();
    rotMinusX->rotateY(90.0*deg);

    auto solidGenHousing = new G4Tubs("GeneratorHousing",
                                       3.0*cm,    // inner R (holds inner air)
                                       5.0*cm,    // outer R
                                       15.0*cm,   // half-length = 30/2
                                       0, 360.0*deg);
    auto logicGenHousing = new G4LogicalVolume(solidGenHousing, fAluminum, "GeneratorHousing");
    new G4PVPlacement(rotMinusX,
                      G4ThreeVector(45.0*cm, -140.0*cm, 0),  // center at x=60-15=45
                      logicGenHousing, "GeneratorHousing", logicWorld,
                      false, 0, fCheckOverlaps);

    //--- Inner air of source generator (PHITS cell 55, surface 57) ---
    // rcc 60 -140 0  -20 0 0  R=3
    auto solidGenInner = new G4Tubs("GeneratorInner",
                                     0,
                                     3.0*cm,
                                     10.0*cm,    // half-length = 20/2
                                     0, 360.0*deg);
    auto logicGenInner = new G4LogicalVolume(solidGenInner, fAir, "GeneratorInner");
    new G4PVPlacement(rotMinusX,
                      G4ThreeVector(50.0*cm, -140.0*cm, 0),  // center at x=60-10=50
                      logicGenInner, "GeneratorInner", logicWorld,
                      false, 0, fCheckOverlaps);

    //=========================================================================
    // DETECTOR ARRAY - 22 positions along the beamline
    // All detectors are air-filled cylinders: R=1cm, H=1cm
    // Oriented along Y-axis (beam direction through collimator)
    //
    // PHITS surfaces 35-56: rcc x0 y0 0  0 1 0  1.0
    //
    // CRITICAL PLACEMENT LOGIC:
    // In PHITS, detector cells are explicitly excluded from surrounding
    // cells using surface exclusion (#). In Geant4, we must avoid volume
    // overlaps by placing detectors as daughters of the correct mother:
    //
    //   Dtctr1-7 (y=-110 to -80): Inside collimator aperture (R=10cm)
    //     -> Place as daughters of logicAperture with LOCAL coordinates
    //     Aperture center is at (60, -95, 0) in world, half-length=20cm
    //     Local y_local = world_y - (-95) = world_y + 95
    //     Local x_local = 0 (on axis), local z_local = 0
    //
    //   Dtctr8-20 (y=-74.5 to -15): In the open room (world)
    //     -> Place directly in logicWorld
    //
    //   DtcIn1 (60, -150): In the source room (world, behind collimator)
    //   DtcIn2 (10, -170): Off-axis in source room (world)
    //=========================================================================

    auto solidDetector = new G4Tubs("Detector",
                                     0,
                                     1.0*cm,    // radius
                                     0.5*cm,    // half-height = 1/2
                                     0, 360.0*deg);

    struct DetPos {
        G4double x; G4double y; const char* name;
        G4bool inAperture;  // true if inside collimator aperture
    };

    // Aperture spans y = -115 to -75 in world coords, centered at y = -95
    // Detectors at y=-110 to -80 (center at y+0.5) are inside
    // Dtctr8 at y=-74.5 (center -74.0) is OUTSIDE (aperture ends at -75)
    std::vector<DetPos> detPositions = {
        { 60.0, -110.0, "Dtctr1",  true  },  // y_center=-109.5, inside aperture
        { 60.0, -105.0, "Dtctr2",  true  },
        { 60.0, -100.0, "Dtctr3",  true  },
        { 60.0,  -95.0, "Dtctr4",  true  },
        { 60.0,  -90.0, "Dtctr5",  true  },
        { 60.0,  -85.0, "Dtctr6",  true  },
        { 60.0,  -80.0, "Dtctr7",  true  },
        { 60.0,  -74.5, "Dtctr8",  false },  // y_center=-74.0, outside aperture
        { 60.0,  -70.0, "Dtctr9",  false },
        { 60.0,  -65.0, "Dtctr10", false },
        { 60.0,  -60.0, "Dtctr11", false },
        { 60.0,  -55.0, "Dtctr12", false },
        { 60.0,  -50.0, "Dtctr13", false },
        { 60.0,  -45.0, "Dtctr14", false },
        { 60.0,  -40.0, "Dtctr15", false },
        { 60.0,  -35.0, "Dtctr16", false },
        { 60.0,  -30.0, "Dtctr17", false },
        { 60.0,  -25.0, "Dtctr18", false },
        { 60.0,  -20.0, "Dtctr19", false },
        { 60.0,  -15.0, "Dtctr20", false },
        { 60.0, -150.0, "DtcIn1",  false },  // Source room
        { 10.0, -170.0, "DtcIn2",  false },  // Source room, off-axis
    };

    // Rotation for detectors: cylinder axis along Y
    auto rotDet = new G4RotationMatrix();
    rotDet->rotateX(90.0*deg);

    // Aperture center in world coordinates
    const G4double apertureWorldX = 60.0*cm;
    const G4double apertureWorldY = -95.0*cm;

    fDetectorLogVols.clear();

    for (size_t i = 0; i < detPositions.size(); ++i) {
        const auto& dp = detPositions[i];

        G4String logName = G4String(dp.name) + "_log";
        auto logicDet = new G4LogicalVolume(solidDetector, fAir, logName);
        fDetectorLogVols.push_back(logicDet);

        G4double yCenterWorld = (dp.y + 0.5)*cm;  // rcc starts at y0, extends 1cm

        if (dp.inAperture) {
            // Place inside the aperture logical volume
            // Convert world coords to local aperture coords
            // Aperture is a Tubs rotated 90deg about X: its local z-axis = world y-axis
            // Local coords: local_x = world_x - apertureX, local_y = world_z,
            //               local_z = world_y - apertureY (along tube axis)
            // Detector also rotated 90deg about X, so in aperture frame it's unrotated
            G4double localZ = yCenterWorld - apertureWorldY;  // along tube axis
            // x offset = 0 (detector at x=60, aperture at x=60)
            // Note: no rotation needed for detector inside aperture since both
            // have the same orientation (cylinder along aperture axis)
            new G4PVPlacement(nullptr,  // no additional rotation (aligned with mother)
                              G4ThreeVector(0, 0, localZ),
                              logicDet,
                              G4String(dp.name),
                              logicAperture,  // daughter of aperture
                              false,
                              static_cast<G4int>(i),
                              fCheckOverlaps);
        } else {
            // Place in world volume (open room or source room)
            new G4PVPlacement(rotDet,
                              G4ThreeVector(dp.x*cm, yCenterWorld, 0),
                              logicDet,
                              G4String(dp.name),
                              logicWorld,
                              false,
                              static_cast<G4int>(i),
                              fCheckOverlaps);
        }
    }

    //=========================================================================
    // VISUALIZATION ATTRIBUTES
    //=========================================================================
    auto concreteVis = new G4VisAttributes(G4Colour(0.6, 0.6, 0.6, 0.4));
    concreteVis->SetForceSolid(true);
    logicLeftWall->SetVisAttributes(concreteVis);
    logicRightWall->SetVisAttributes(concreteVis);
    logicBackWallConcrete->SetVisAttributes(concreteVis);
    logicCollBlock->SetVisAttributes(concreteVis);
    logicCollSrc->SetVisAttributes(concreteVis);
    logicUA2Block->SetVisAttributes(concreteVis);
    logicEntrBlock->SetVisAttributes(concreteVis);
    logicConcreteShield->SetVisAttributes(concreteVis);
    logicRoof->SetVisAttributes(concreteVis);
    logicFloor->SetVisAttributes(concreteVis);

    auto ssVis = new G4VisAttributes(G4Colour(0.3, 0.3, 0.8, 0.6));
    ssVis->SetForceSolid(true);
    logicSSLiner->SetVisAttributes(ssVis);

    auto leadVis = new G4VisAttributes(G4Colour(0.3, 0.3, 0.3, 0.7));
    leadVis->SetForceSolid(true);
    logicLeadShield->SetVisAttributes(leadVis);

    auto alVis = new G4VisAttributes(G4Colour(0.9, 0.9, 0.0, 0.5));
    alVis->SetForceSolid(true);
    logicGenHousing->SetVisAttributes(alVis);

    auto peVis = new G4VisAttributes(G4Colour(0.0, 0.8, 0.8, 0.4));
    peVis->SetForceSolid(true);
    logicPEBackWall->SetVisAttributes(peVis);
    logicPEOutside->SetVisAttributes(peVis);

    auto bpolyVis = new G4VisAttributes(G4Colour(0.0, 0.8, 0.0, 0.5));
    bpolyVis->SetForceSolid(true);
    logicBPolyUA2->SetVisAttributes(bpolyVis);
    logicBPolyEntr->SetVisAttributes(bpolyVis);

    auto detVis = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.8));
    detVis->SetForceSolid(true);
    for (auto lv : fDetectorLogVols) {
        lv->SetVisAttributes(detVis);
    }

    auto airVis = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.1));
    logicAperture->SetVisAttributes(airVis);
    logicGenInner->SetVisAttributes(airVis);

    return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NESSADetectorConstruction::ConstructSDandField()
{
    auto sdManager = G4SDManager::GetSDMpointer();

    // Create one sensitive detector for all detector volumes
    auto neutronSD = new NESSANeutronSD("NESSANeutronSD", "NeutronHitsCollection",
                                         static_cast<G4int>(fDetectorLogVols.size()));
    sdManager->AddNewDetector(neutronSD);

    // Assign to all detector logical volumes
    for (size_t i = 0; i < fDetectorLogVols.size(); ++i) {
        fDetectorLogVols[i]->SetSensitiveDetector(neutronSD);
    }
}
