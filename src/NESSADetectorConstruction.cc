// ============================================================
// NESSADetectorConstruction - Auto-generated from MCNP5
// FREIA/NESSA bunker, Uppsala University
// 218 cells, 227 surfaces, 10 materials
// ============================================================

#include "NESSADetectorConstruction.hh"
#include "NESSAScoringSD.hh"
#include "NESSAScoringConfig.hh"
#include "NESSADetectorMessenger.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"

static NESSADetectorMessenger* gMessenger = nullptr;

NESSADetectorConstruction::NESSADetectorConstruction()
{
    if (!gMessenger) gMessenger = new NESSADetectorMessenger();
}

NESSADetectorConstruction::~NESSADetectorConstruction()
{
    delete gMessenger; gMessenger = nullptr;
}

void NESSADetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();
    
    // --- Material 2: Air (0.0013 g/cm3) ---
    {
        auto* mat = new G4Material("Air", 0.0013*g/cm3, 6);
        mat->AddElement(nist->FindOrBuildElement("H"),  0.001357);
        mat->AddElement(nist->FindOrBuildElement("C"),  0.000329);
        mat->AddElement(nist->FindOrBuildElement("N"),  0.735784);
        mat->AddElement(nist->FindOrBuildElement("O"),  0.237154);
        mat->AddElement(nist->FindOrBuildElement("Ne"), 0.000025);
        mat->AddElement(nist->FindOrBuildElement("Ar"), 0.025351);
        fMaterials[2] = mat;
    }
    // --- Material 3: Ordinary Concrete (2.30 g/cm3) ---
    {
        auto* mat = new G4Material("OrdinaryConcrete", 2.30*g/cm3, 10);
        mat->AddElement(nist->FindOrBuildElement("H"),  0.02210);
        mat->AddElement(nist->FindOrBuildElement("C"),  0.00248);
        mat->AddElement(nist->FindOrBuildElement("O"),  0.57469);
        mat->AddElement(nist->FindOrBuildElement("Na"), 0.01521);
        mat->AddElement(nist->FindOrBuildElement("Mg"), 0.00127);
        mat->AddElement(nist->FindOrBuildElement("Al"), 0.01995);
        mat->AddElement(nist->FindOrBuildElement("Si"), 0.30477);
        mat->AddElement(nist->FindOrBuildElement("K"),  0.01004);
        mat->AddElement(nist->FindOrBuildElement("Ca"), 0.04310);
        mat->AddElement(nist->FindOrBuildElement("Fe"), 0.00639);
        fMaterials[3] = mat;
    }
    // --- Material 5: Polyethylene (0.96 g/cm3) ---
    {
        auto* mat = new G4Material("Polyethylene", 0.96*g/cm3, 2);
        mat->AddElement(nist->FindOrBuildElement("H"), 0.143926);
        mat->AddElement(nist->FindOrBuildElement("C"), 0.856074);
        fMaterials[5] = mat;
    }
    // --- Material 7: Magnetite Concrete (3.9 g/cm3) ---
    {
        auto* mat = new G4Material("MagnetiteConcrete", 3.9*g/cm3, 11);
        mat->AddElement(nist->FindOrBuildElement("H"),  0.003289);
        mat->AddElement(nist->FindOrBuildElement("O"),  0.349121);
        mat->AddElement(nist->FindOrBuildElement("Mg"), 0.010502);
        mat->AddElement(nist->FindOrBuildElement("Al"), 0.024820);
        mat->AddElement(nist->FindOrBuildElement("Si"), 0.027400);
        mat->AddElement(nist->FindOrBuildElement("S"),  0.001495);
        mat->AddElement(nist->FindOrBuildElement("Ca"), 0.074924);
        mat->AddElement(nist->FindOrBuildElement("V"),  0.003290);
        mat->AddElement(nist->FindOrBuildElement("Cr"), 0.001820);
        mat->AddElement(nist->FindOrBuildElement("Mn"), 0.002093);
        mat->AddElement(nist->FindOrBuildElement("Fe"), 0.501246);
        fMaterials[7] = mat;
    }
    // --- Material 11: Iron (7.874 g/cm3) ---
    {
        auto* mat = new G4Material("Iron", 7.874*g/cm3, 1);
        mat->AddElement(nist->FindOrBuildElement("Fe"), 1.0);
        fMaterials[11] = mat;
    }
    // --- Material 12: Lead (11.34 g/cm3) ---
    {
        auto* mat = new G4Material("Lead", 11.34*g/cm3, 1);
        mat->AddElement(nist->FindOrBuildElement("Pb"), 1.0);
        fMaterials[12] = mat;
    }
    // --- Material 13: Soil (1.52 g/cm3) ---
    {
        auto* mat = new G4Material("Soil", 1.52*g/cm3, 10);
        mat->AddElement(nist->FindOrBuildElement("O"),  0.51363);
        mat->AddElement(nist->FindOrBuildElement("Na"), 0.00614);
        mat->AddElement(nist->FindOrBuildElement("Mg"), 0.01307);
        mat->AddElement(nist->FindOrBuildElement("Al"), 0.06858);
        mat->AddElement(nist->FindOrBuildElement("Si"), 0.27126);
        mat->AddElement(nist->FindOrBuildElement("K"),  0.01433);
        mat->AddElement(nist->FindOrBuildElement("Ca"), 0.05116);
        mat->AddElement(nist->FindOrBuildElement("Ti"), 0.00461);
        mat->AddElement(nist->FindOrBuildElement("Mn"), 0.00072);
        mat->AddElement(nist->FindOrBuildElement("Fe"), 0.05650);
        fMaterials[13] = mat;
    }
    // --- Material 53: Borated Paraffin (1.05 g/cm3) ---
    {
        auto* mat = new G4Material("BoratedParaffin", 1.05*g/cm3, 4);
        mat->AddElement(nist->FindOrBuildElement("C"),  0.72);
        mat->AddElement(nist->FindOrBuildElement("H"),  0.12);
        mat->AddElement(nist->FindOrBuildElement("O"),  0.11);
        mat->AddElement(nist->FindOrBuildElement("B"),  0.05);
        fMaterials[53] = mat;
    }
    // --- Material 54: Stainless Steel 304 (8.00 g/cm3) ---
    {
        auto* mat = new G4Material("SS304", 8.00*g/cm3, 8);
        mat->AddElement(nist->FindOrBuildElement("C"),  0.0004);
        mat->AddElement(nist->FindOrBuildElement("Si"), 0.0050);
        mat->AddElement(nist->FindOrBuildElement("P"),  0.00023);
        mat->AddElement(nist->FindOrBuildElement("S"),  0.00015);
        mat->AddElement(nist->FindOrBuildElement("Cr"), 0.19000);
        mat->AddElement(nist->FindOrBuildElement("Mn"), 0.01);
        mat->AddElement(nist->FindOrBuildElement("Fe"), 0.70173);
        mat->AddElement(nist->FindOrBuildElement("Ni"), 0.09249);
        fMaterials[54] = mat;
    }
    // Galactic vacuum (unused but safe)
    fMaterials[0] = nist->FindOrBuildMaterial("G4_Galactic");
}

G4VPhysicalVolume* NESSADetectorConstruction::Construct()
{
    DefineMaterials();
    
    // World volume (96m x 96m x 96m)
    G4double worldHalf = 4800.0*cm;
    auto* worldSolid = new G4Box("World", worldHalf, worldHalf, worldHalf);
    auto* worldLogical = new G4LogicalVolume(worldSolid, fMaterials[2], "World");
    worldLogical->SetVisAttributes(G4VisAttributes::GetInvisible());
    fWorldLogical = worldLogical;
    
    auto* worldPhysical = new G4PVPlacement(0, G4ThreeVector(),
        worldLogical, "World", 0, false, 0);
    
    ConstructBunkerGeometry(worldLogical);
    ApplyVisAttributes();
    
    G4cout << "*** NESSA geometry construction complete ***" << G4endl;
    return worldPhysical;
}


void NESSADetectorConstruction::ConstructBunkerGeometry(G4LogicalVolume* worldLogical)
{
    // ---- Cell 1001: The air (left) (Mat 2: Air) ----
    auto* solid_c1001_box = new G4Box("solid_c1001_box",
        2380.0000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* solid_c1001_rpp0 = new G4Box("solid_c1001_rpp0",
        50.0000*cm, 50.0000*cm, 50.0000*cm);
    auto* solid_c1001_b0 = new G4SubtractionSolid("solid_c1001_b0",
        solid_c1001_box, solid_c1001_rpp0,
        0, G4ThreeVector(2090.0000*cm, 290.0000*cm, -2350.0000*cm));
    auto* solid_c1001 = solid_c1001_b0;
    auto* logic_c1001 = new G4LogicalVolume(solid_c1001, fMaterials[2], "logic_c1001");
    new G4PVPlacement(0, G4ThreeVector(-2420.0000*cm, 0.0000*cm, 2400.0000*cm),
        logic_c1001, "phys_c1001", worldLogical, false, 1001, fCheckOverlaps);

    // ---- Cell 1002: Air Right side of bunker (Mat 2: Air) ----
    auto* solid_c1002 = new G4Box("solid_c1002",
        2210.0000*cm, 2280.0000*cm, 2400.0000*cm);
    auto* logic_c1002 = new G4LogicalVolume(solid_c1002, fMaterials[2], "logic_c1002");
    new G4PVPlacement(0, G4ThreeVector(2590.0000*cm, 2520.0000*cm, 2400.0000*cm),
        logic_c1002, "phys_c1002", worldLogical, false, 1002, fCheckOverlaps);

    // ---- Cell 1003: The air (below) (Mat 2: Air) ----
    auto* solid_c1003 = new G4Box("solid_c1003",
        2220.0000*cm, 2480.0000*cm, 120.0000*cm);
    auto* logic_c1003 = new G4LogicalVolume(solid_c1003, fMaterials[2], "logic_c1003");
    new G4PVPlacement(0, G4ThreeVector(2580.0000*cm, -2320.0000*cm, 120.0000*cm),
        logic_c1003, "phys_c1003", worldLogical, false, 1003, fCheckOverlaps);

    // ---- Cell 1004: Easter part of ESS bunker (Mat 2: Air) ----
    auto* solid_c1004_box = new G4Box("solid_c1004_box",
        200.0000*cm, 480.0000*cm, 250.0000*cm);
    auto* solid_c1004_sph0 = new G4Orb("solid_c1004_sph0", 10.0000*cm);
    auto* solid_c1004_b0 = new G4SubtractionSolid("solid_c1004_b0",
        solid_c1004_box, solid_c1004_sph0,
        0, G4ThreeVector(170.0000*cm, 200.0000*cm, -100.0000*cm));
    auto* solid_c1004_rpp1 = new G4Box("solid_c1004_rpp1",
        50.0000*cm, 50.0000*cm, 50.0000*cm);
    auto* solid_c1004_b1 = new G4SubtractionSolid("solid_c1004_b1",
        solid_c1004_b0, solid_c1004_rpp1,
        0, G4ThreeVector(-10.0000*cm, 50.0000*cm, -200.0000*cm));
    auto* solid_c1004 = solid_c1004_b1;
    auto* logic_c1004 = new G4LogicalVolume(solid_c1004, fMaterials[2], "logic_c1004");
    new G4PVPlacement(0, G4ThreeVector(-320.0000*cm, 240.0000*cm, 250.0000*cm),
        logic_c1004, "phys_c1004", worldLogical, false, 1004, fCheckOverlaps);

    // ---- Cell 10041: Stainless steel cube (Mat 54: SS304) ----
    // RPP surface 3093: xmin=-380 xmax=-280 ymin=240 ymax=340 zmin=0 zmax=100
    auto* solid_c10041 = new G4Box("solid_c10041", 50.0000*cm, 50.0000*cm, 50.0000*cm);
    auto* logic_c10041 = new G4LogicalVolume(solid_c10041, fMaterials[54], "logic_c10041");
    new G4PVPlacement(0, G4ThreeVector(-330.0000*cm, 290.0000*cm, 50.0000*cm),
        logic_c10041, "phys_c10041", worldLogical, false, 10041, fCheckOverlaps);

    // ---- Cell 1005: Easter part of ESS bunker (Mat 2: Air) ----
    auto* solid_c1005 = new G4Box("solid_c1005",
        160.0000*cm, 40.0000*cm, 250.0000*cm);
    auto* logic_c1005 = new G4LogicalVolume(solid_c1005, fMaterials[2], "logic_c1005");
    new G4PVPlacement(0, G4ThreeVector(-360.0000*cm, 760.0000*cm, 250.0000*cm),
        logic_c1005, "phys_c1005", worldLogical, false, 1005, fCheckOverlaps);

    // ---- Cell 1007: The air (below) (Mat 2: Air) ----
    auto* solid_c1007 = new G4Box("solid_c1007",
        200.0000*cm, 2390.0000*cm, 2240.0000*cm);
    auto* logic_c1007 = new G4LogicalVolume(solid_c1007, fMaterials[2], "logic_c1007");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, -2410.0000*cm, 2560.0000*cm),
        logic_c1007, "phys_c1007", worldLogical, false, 1007, fCheckOverlaps);

    // ---- Cell 1008: The air (below) (Mat 2: Air) ----
    auto* solid_c1008 = new G4Box("solid_c1008",
        140.0000*cm, 2470.0000*cm, 120.0000*cm);
    auto* logic_c1008 = new G4LogicalVolume(solid_c1008, fMaterials[2], "logic_c1008");
    new G4PVPlacement(0, G4ThreeVector(140.0000*cm, -2330.0000*cm, 120.0000*cm),
        logic_c1008, "phys_c1008", worldLogical, false, 1008, fCheckOverlaps);

    // ---- Cell 10080:  (Mat 5: Polyethylene) ----
    auto* solid_c10080 = new G4Box("solid_c10080",
        140.0000*cm, 10.0000*cm, 120.0000*cm);
    auto* logic_c10080 = new G4LogicalVolume(solid_c10080, fMaterials[5], "logic_c10080");
    new G4PVPlacement(0, G4ThreeVector(140.0000*cm, 150.0000*cm, 120.0000*cm),
        logic_c10080, "phys_c10080", worldLogical, false, 10080, fCheckOverlaps);

    // ---- Cell 1009:  (Mat 2: Air) ----
    auto* solid_c1009 = new G4Box("solid_c1009",
        40.0000*cm, 2160.0000*cm, 120.0000*cm);
    auto* logic_c1009 = new G4LogicalVolume(solid_c1009, fMaterials[2], "logic_c1009");
    new G4PVPlacement(0, G4ThreeVector(320.0000*cm, -2640.0000*cm, 120.0000*cm),
        logic_c1009, "phys_c1009", worldLogical, false, 1009, fCheckOverlaps);

    // ---- Cell 1010:  (Mat 2: Air) ----
    auto* solid_c1010 = new G4Box("solid_c1010",
        2420.0000*cm, 2160.0000*cm, 40.0000*cm);
    auto* logic_c1010 = new G4LogicalVolume(solid_c1010, fMaterials[2], "logic_c1010");
    new G4PVPlacement(0, G4ThreeVector(2380.0000*cm, -2640.0000*cm, 280.0000*cm),
        logic_c1010, "phys_c1010", worldLogical, false, 1010, fCheckOverlaps);

    // ---- Cell 1011:  (Mat 2: Air) ----
    auto* solid_c1011 = new G4Box("solid_c1011",
        2220.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* logic_c1011 = new G4LogicalVolume(solid_c1011, fMaterials[2], "logic_c1011");
    new G4PVPlacement(0, G4ThreeVector(2580.0000*cm, -160.0000*cm, 2520.0000*cm),
        logic_c1011, "phys_c1011", worldLogical, false, 1011, fCheckOverlaps);

    // ---- Cell 1013:  (Mat 2: Air) ----
    auto* solid_c1013 = new G4Box("solid_c1013",
        10.0000*cm, 2160.0000*cm, 120.0000*cm);
    auto* logic_c1013 = new G4LogicalVolume(solid_c1013, fMaterials[2], "logic_c1013");
    new G4PVPlacement(0, G4ThreeVector(370.0000*cm, 2640.0000*cm, 120.0000*cm),
        logic_c1013, "phys_c1013", worldLogical, false, 1013, fCheckOverlaps);

    // ---- Cell 1014:  (Mat 2: Air) ----
    auto* solid_c1014 = new G4Box("solid_c1014",
        2220.0000*cm, 40.0000*cm, 120.0000*cm);
    auto* logic_c1014 = new G4LogicalVolume(solid_c1014, fMaterials[2], "logic_c1014");
    new G4PVPlacement(0, G4ThreeVector(2580.0000*cm, 200.0000*cm, 120.0000*cm),
        logic_c1014, "phys_c1014", worldLogical, false, 1014, fCheckOverlaps);

    // ---- Cell 1018:  (Mat 2: Air) ----
    auto* solid_c1018 = new G4Box("solid_c1018",
        10.0000*cm, 1975.0000*cm, 2280.0000*cm);
    auto* logic_c1018 = new G4LogicalVolume(solid_c1018, fMaterials[2], "logic_c1018");
    new G4PVPlacement(0, G4ThreeVector(370.0000*cm, 2825.0000*cm, 2520.0000*cm),
        logic_c1018, "phys_c1018", worldLogical, false, 1018, fCheckOverlaps);

    // ---- Cell 1020:  (Mat 2: Air) ----
    auto* solid_c1020 = new G4Box("solid_c1020",
        2220.0000*cm, 2160.0000*cm, 2240.0000*cm);
    auto* logic_c1020 = new G4LogicalVolume(solid_c1020, fMaterials[2], "logic_c1020");
    new G4PVPlacement(0, G4ThreeVector(2580.0000*cm, -2640.0000*cm, 2560.0000*cm),
        logic_c1020, "phys_c1020", worldLogical, false, 1020, fCheckOverlaps);

    // ---- Cell 1023:  (Mat 2: Air) ----
    auto* solid_c1023 = new G4Box("solid_c1023",
        20.0000*cm, 2160.0000*cm, 120.0000*cm);
    auto* logic_c1023 = new G4LogicalVolume(solid_c1023, fMaterials[2], "logic_c1023");
    new G4PVPlacement(0, G4ThreeVector(-20.0000*cm, -2640.0000*cm, 120.0000*cm),
        logic_c1023, "phys_c1023", worldLogical, false, 1023, fCheckOverlaps);

    // ---- Cell 10230:  (Mat 2: Air) ----
    auto* solid_c10230 = new G4Box("solid_c10230",
        10.0000*cm, 40.0000*cm, 2280.0000*cm);
    auto* logic_c10230 = new G4LogicalVolume(solid_c10230, fMaterials[2], "logic_c10230");
    new G4PVPlacement(0, G4ThreeVector(370.0000*cm, 200.0000*cm, 2520.0000*cm),
        logic_c10230, "phys_c10230", worldLogical, false, 10230, fCheckOverlaps);

    // ---- Cell 10231:  (Mat 2: Air) ----
    auto* solid_c10231 = new G4Box("solid_c10231",
        10.0000*cm, 305.0000*cm, 2280.0000*cm);
    auto* logic_c10231 = new G4LogicalVolume(solid_c10231, fMaterials[2], "logic_c10231");
    new G4PVPlacement(0, G4ThreeVector(370.0000*cm, 545.0000*cm, 2520.0000*cm),
        logic_c10231, "phys_c10231", worldLogical, false, 10231, fCheckOverlaps);

    // ---- Cell 1024:  (Mat 2: Air) ----
    auto* solid_c1024 = new G4Box("solid_c1024",
        2210.0000*cm, 40.0000*cm, 2280.0000*cm);
    auto* logic_c1024 = new G4LogicalVolume(solid_c1024, fMaterials[2], "logic_c1024");
    new G4PVPlacement(0, G4ThreeVector(2590.0000*cm, 200.0000*cm, 2520.0000*cm),
        logic_c1024, "phys_c1024", worldLogical, false, 1024, fCheckOverlaps);

    // ---- Cell 1200: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c1200 = new G4Box("solid_c1200",
        2540.0000*cm, 2480.0000*cm, 2400.0000*cm);
    auto* logic_c1200 = new G4LogicalVolume(solid_c1200, fMaterials[3], "logic_c1200");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, -2320.0000*cm, -2400.0000*cm),
        logic_c1200, "phys_c1200", worldLogical, false, 1200, fCheckOverlaps);

    // ---- Cell 1201: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c1201 = new G4Box("solid_c1201",
        2540.0000*cm, 2280.0000*cm, 2400.0000*cm);
    auto* logic_c1201 = new G4LogicalVolume(solid_c1201, fMaterials[3], "logic_c1201");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 2520.0000*cm, -2400.0000*cm),
        logic_c1201, "phys_c1201", worldLogical, false, 1201, fCheckOverlaps);

    // ---- Cell 12205: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12205 = new G4Box("solid_c12205",
        2540.0000*cm, 10.0000*cm, 2400.0000*cm);
    auto* logic_c12205 = new G4LogicalVolume(solid_c12205, fMaterials[3], "logic_c12205");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 230.0000*cm, -2400.0000*cm),
        logic_c12205, "phys_c12205", worldLogical, false, 12205, fCheckOverlaps);

    // ---- Cell 12211: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12211 = new G4Box("solid_c12211",
        2540.0000*cm, 5.0000*cm, 2400.0000*cm);
    auto* logic_c12211 = new G4LogicalVolume(solid_c12211, fMaterials[3], "logic_c12211");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 215.0000*cm, -2400.0000*cm),
        logic_c12211, "phys_c12211", worldLogical, false, 12211, fCheckOverlaps);

    // ---- Cell 12215: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12215 = new G4Box("solid_c12215",
        2540.0000*cm, 5.0000*cm, 2400.0000*cm);
    auto* logic_c12215 = new G4LogicalVolume(solid_c12215, fMaterials[3], "logic_c12215");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 205.0000*cm, -2400.0000*cm),
        logic_c12215, "phys_c12215", worldLogical, false, 12215, fCheckOverlaps);

    // ---- Cell 12212: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12212 = new G4Box("solid_c12212",
        2540.0000*cm, 5.0000*cm, 2400.0000*cm);
    auto* logic_c12212 = new G4LogicalVolume(solid_c12212, fMaterials[3], "logic_c12212");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 195.0000*cm, -2400.0000*cm),
        logic_c12212, "phys_c12212", worldLogical, false, 12212, fCheckOverlaps);

    // ---- Cell 12225: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12225 = new G4Box("solid_c12225",
        2540.0000*cm, 5.0000*cm, 2400.0000*cm);
    auto* logic_c12225 = new G4LogicalVolume(solid_c12225, fMaterials[3], "logic_c12225");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 185.0000*cm, -2400.0000*cm),
        logic_c12225, "phys_c12225", worldLogical, false, 12225, fCheckOverlaps);

    // ---- Cell 12213: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12213 = new G4Box("solid_c12213",
        2540.0000*cm, 5.0000*cm, 2400.0000*cm);
    auto* logic_c12213 = new G4LogicalVolume(solid_c12213, fMaterials[3], "logic_c12213");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 175.0000*cm, -2400.0000*cm),
        logic_c12213, "phys_c12213", worldLogical, false, 12213, fCheckOverlaps);

    // ---- Cell 12235: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c12235 = new G4Box("solid_c12235",
        2540.0000*cm, 5.0000*cm, 2400.0000*cm);
    auto* logic_c12235 = new G4LogicalVolume(solid_c12235, fMaterials[3], "logic_c12235");
    new G4PVPlacement(0, G4ThreeVector(-2260.0000*cm, 165.0000*cm, -2400.0000*cm),
        logic_c12235, "phys_c12235", worldLogical, false, 12235, fCheckOverlaps);

    // ---- Cell 1205: Floor (Mat 3: OrdinaryConcrete) ----
    auto* solid_c1205 = new G4Box("solid_c1205",
        60.0000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c1205 = new G4LogicalVolume(solid_c1205, fMaterials[3], "logic_c1205");
    new G4PVPlacement(0, G4ThreeVector(420.0000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c1205, "phys_c1205", worldLogical, false, 1205, fCheckOverlaps);

    // ---- Cell 1300: Left wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1300 = new G4Box("solid_c1300",
        5.0000*cm, 640.0000*cm, 120.0000*cm);
    auto* logic_c1300 = new G4LogicalVolume(solid_c1300, fMaterials[7], "logic_c1300");
    new G4PVPlacement(0, G4ThreeVector(-25.0000*cm, 160.0000*cm, 120.0000*cm),
        logic_c1300, "phys_c1300", worldLogical, false, 1300, fCheckOverlaps);

    // ---- Cell 1301: Left wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1301 = new G4Box("solid_c1301",
        5.0000*cm, 640.0000*cm, 120.0000*cm);
    auto* logic_c1301 = new G4LogicalVolume(solid_c1301, fMaterials[7], "logic_c1301");
    new G4PVPlacement(0, G4ThreeVector(-35.0000*cm, 160.0000*cm, 120.0000*cm),
        logic_c1301, "phys_c1301", worldLogical, false, 1301, fCheckOverlaps);

    // ---- Cell 1305: Left wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1305 = new G4Box("solid_c1305",
        10.0000*cm, 640.0000*cm, 120.0000*cm);
    auto* logic_c1305 = new G4LogicalVolume(solid_c1305, fMaterials[7], "logic_c1305");
    new G4PVPlacement(0, G4ThreeVector(-10.0000*cm, 160.0000*cm, 120.0000*cm),
        logic_c1305, "phys_c1305", worldLogical, false, 1305, fCheckOverlaps);

    // ---- Cell 1310: Plastic wall in inner bunker (Mat 5: Polyethylene) ----
    auto* solid_c1310 = new G4Box("solid_c1310",
        115.0000*cm, 10.0000*cm, 120.0000*cm);
    auto* logic_c1310 = new G4LogicalVolume(solid_c1310, fMaterials[5], "logic_c1310");
    new G4PVPlacement(0, G4ThreeVector(115.0000*cm, 250.0000*cm, 120.0000*cm),
        logic_c1310, "phys_c1310", worldLogical, false, 1310, fCheckOverlaps);

    // ---- Cell 13105: Back wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13105 = new G4Box("solid_c13105",
        180.0000*cm, 10.0000*cm, 160.0000*cm);
    auto* logic_c13105 = new G4LogicalVolume(solid_c13105, fMaterials[7], "logic_c13105");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 230.0000*cm, 160.0000*cm),
        logic_c13105, "phys_c13105", worldLogical, false, 13105, fCheckOverlaps);

    // ---- Cell 1311: Back wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1311 = new G4Box("solid_c1311",
        180.0000*cm, 5.0000*cm, 160.0000*cm);
    auto* logic_c1311 = new G4LogicalVolume(solid_c1311, fMaterials[7], "logic_c1311");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 215.0000*cm, 160.0000*cm),
        logic_c1311, "phys_c1311", worldLogical, false, 1311, fCheckOverlaps);

    // ---- Cell 13115: Back wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13115 = new G4Box("solid_c13115",
        180.0000*cm, 5.0000*cm, 160.0000*cm);
    auto* logic_c13115 = new G4LogicalVolume(solid_c13115, fMaterials[7], "logic_c13115");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 205.0000*cm, 160.0000*cm),
        logic_c13115, "phys_c13115", worldLogical, false, 13115, fCheckOverlaps);

    // ---- Cell 1312: Back wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1312 = new G4Box("solid_c1312",
        180.0000*cm, 5.0000*cm, 160.0000*cm);
    auto* logic_c1312 = new G4LogicalVolume(solid_c1312, fMaterials[7], "logic_c1312");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 195.0000*cm, 160.0000*cm),
        logic_c1312, "phys_c1312", worldLogical, false, 1312, fCheckOverlaps);

    // ---- Cell 13125: Back wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13125 = new G4Box("solid_c13125",
        180.0000*cm, 5.0000*cm, 160.0000*cm);
    auto* logic_c13125 = new G4LogicalVolume(solid_c13125, fMaterials[7], "logic_c13125");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 185.0000*cm, 160.0000*cm),
        logic_c13125, "phys_c13125", worldLogical, false, 13125, fCheckOverlaps);

    // ---- Cell 1313: Back wall SET TO ZERO IN Step 2 steg 78Vg (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1313 = new G4Box("solid_c1313",
        180.0000*cm, 5.0000*cm, 160.0000*cm);
    auto* logic_c1313 = new G4LogicalVolume(solid_c1313, fMaterials[7], "logic_c1313");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 175.0000*cm, 160.0000*cm),
        logic_c1313, "phys_c1313", worldLogical, false, 1313, fCheckOverlaps);

    // ---- Cell 13135: Back wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13135 = new G4Box("solid_c13135",
        180.0000*cm, 5.0000*cm, 160.0000*cm);
    auto* logic_c13135 = new G4LogicalVolume(solid_c13135, fMaterials[7], "logic_c13135");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 165.0000*cm, 160.0000*cm),
        logic_c13135, "phys_c13135", worldLogical, false, 13135, fCheckOverlaps);

    // ---- Cell 1340: Labyrinth wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1340 = new G4Box("solid_c1340",
        100.0000*cm, 40.0000*cm, 120.0000*cm);
    auto* logic_c1340 = new G4LogicalVolume(solid_c1340, fMaterials[7], "logic_c1340");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 680.0000*cm, 120.0000*cm),
        logic_c1340, "phys_c1340", worldLogical, false, 1340, fCheckOverlaps);

    // ---- Cell 1350: Front wall (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1350 = new G4Box("solid_c1350",
        120.0000*cm, 40.0000*cm, 120.0000*cm);
    auto* logic_c1350 = new G4LogicalVolume(solid_c1350, fMaterials[7], "logic_c1350");
    new G4PVPlacement(0, G4ThreeVector(80.0000*cm, 840.0000*cm, 120.0000*cm),
        logic_c1350, "phys_c1350", worldLogical, false, 1350, fCheckOverlaps);

    // ---- Cell 1370: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1370 = new G4Box("solid_c1370",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c1370 = new G4LogicalVolume(solid_c1370, fMaterials[7], "logic_c1370");
    new G4PVPlacement(0, G4ThreeVector(-115.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c1370, "phys_c1370", worldLogical, false, 1370, fCheckOverlaps);

    // ---- Cell 13701: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13701 = new G4Box("solid_c13701",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13701 = new G4LogicalVolume(solid_c13701, fMaterials[7], "logic_c13701");
    new G4PVPlacement(0, G4ThreeVector(-105.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13701, "phys_c13701", worldLogical, false, 13701, fCheckOverlaps);

    // ---- Cell 13702: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13702 = new G4Box("solid_c13702",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13702 = new G4LogicalVolume(solid_c13702, fMaterials[7], "logic_c13702");
    new G4PVPlacement(0, G4ThreeVector(-95.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13702, "phys_c13702", worldLogical, false, 13702, fCheckOverlaps);

    // ---- Cell 13703: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13703 = new G4Box("solid_c13703",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13703 = new G4LogicalVolume(solid_c13703, fMaterials[7], "logic_c13703");
    new G4PVPlacement(0, G4ThreeVector(-85.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13703, "phys_c13703", worldLogical, false, 13703, fCheckOverlaps);

    // ---- Cell 13704: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13704 = new G4Box("solid_c13704",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13704 = new G4LogicalVolume(solid_c13704, fMaterials[7], "logic_c13704");
    new G4PVPlacement(0, G4ThreeVector(-75.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13704, "phys_c13704", worldLogical, false, 13704, fCheckOverlaps);

    // ---- Cell 13706: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13706 = new G4Box("solid_c13706",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13706 = new G4LogicalVolume(solid_c13706, fMaterials[7], "logic_c13706");
    new G4PVPlacement(0, G4ThreeVector(-65.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13706, "phys_c13706", worldLogical, false, 13706, fCheckOverlaps);

    // ---- Cell 13707: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13707 = new G4Box("solid_c13707",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13707 = new G4LogicalVolume(solid_c13707, fMaterials[7], "logic_c13707");
    new G4PVPlacement(0, G4ThreeVector(-55.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13707, "phys_c13707", worldLogical, false, 13707, fCheckOverlaps);

    // ---- Cell 13708: Left side wall (right) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13708 = new G4Box("solid_c13708",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13708 = new G4LogicalVolume(solid_c13708, fMaterials[7], "logic_c13708");
    new G4PVPlacement(0, G4ThreeVector(-45.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13708, "phys_c13708", worldLogical, false, 13708, fCheckOverlaps);

    // ---- Cell 1371: Left side wall (upper) (Mat 2: Air) ----
    auto* solid_c1371 = new G4Box("solid_c1371",
        40.0000*cm, 40.0000*cm, 250.0000*cm);
    auto* logic_c1371 = new G4LogicalVolume(solid_c1371, fMaterials[2], "logic_c1371");
    new G4PVPlacement(0, G4ThreeVector(-160.0000*cm, 760.0000*cm, 250.0000*cm),
        logic_c1371, "phys_c1371", worldLogical, false, 1371, fCheckOverlaps);

    // ---- Cell 1372: Left side wall (lower) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1372 = new G4Box("solid_c1372",
        160.0000*cm, 40.0000*cm, 250.0000*cm);
    auto* logic_c1372 = new G4LogicalVolume(solid_c1372, fMaterials[7], "logic_c1372");
    new G4PVPlacement(0, G4ThreeVector(-280.0000*cm, -440.0000*cm, 250.0000*cm),
        logic_c1372, "phys_c1372", worldLogical, false, 1372, fCheckOverlaps);

    // ---- Cell 13731: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13731 = new G4Box("solid_c13731",
        5.0000*cm, 680.0000*cm, 250.0000*cm);
    auto* logic_c13731 = new G4LogicalVolume(solid_c13731, fMaterials[7], "logic_c13731");
    new G4PVPlacement(0, G4ThreeVector(-525.0000*cm, 200.0000*cm, 250.0000*cm),
        logic_c13731, "phys_c13731", worldLogical, false, 13731, fCheckOverlaps);

    // ---- Cell 13732: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13732 = new G4Box("solid_c13732",
        5.0000*cm, 680.0000*cm, 255.0000*cm);
    auto* logic_c13732 = new G4LogicalVolume(solid_c13732, fMaterials[7], "logic_c13732");
    new G4PVPlacement(0, G4ThreeVector(-535.0000*cm, 200.0000*cm, 255.0000*cm),
        logic_c13732, "phys_c13732", worldLogical, false, 13732, fCheckOverlaps);

    // ---- Cell 13733: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13733 = new G4Box("solid_c13733",
        5.0000*cm, 680.0000*cm, 260.0000*cm);
    auto* logic_c13733 = new G4LogicalVolume(solid_c13733, fMaterials[7], "logic_c13733");
    new G4PVPlacement(0, G4ThreeVector(-545.0000*cm, 200.0000*cm, 260.0000*cm),
        logic_c13733, "phys_c13733", worldLogical, false, 13733, fCheckOverlaps);

    // ---- Cell 13734: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13734 = new G4Box("solid_c13734",
        5.0000*cm, 680.0000*cm, 265.0000*cm);
    auto* logic_c13734 = new G4LogicalVolume(solid_c13734, fMaterials[7], "logic_c13734");
    new G4PVPlacement(0, G4ThreeVector(-555.0000*cm, 200.0000*cm, 265.0000*cm),
        logic_c13734, "phys_c13734", worldLogical, false, 13734, fCheckOverlaps);

    // ---- Cell 13735: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13735 = new G4Box("solid_c13735",
        5.0000*cm, 680.0000*cm, 270.0000*cm);
    auto* logic_c13735 = new G4LogicalVolume(solid_c13735, fMaterials[7], "logic_c13735");
    new G4PVPlacement(0, G4ThreeVector(-565.0000*cm, 200.0000*cm, 270.0000*cm),
        logic_c13735, "phys_c13735", worldLogical, false, 13735, fCheckOverlaps);

    // ---- Cell 13736: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13736 = new G4Box("solid_c13736",
        5.0000*cm, 680.0000*cm, 275.0000*cm);
    auto* logic_c13736 = new G4LogicalVolume(solid_c13736, fMaterials[7], "logic_c13736");
    new G4PVPlacement(0, G4ThreeVector(-575.0000*cm, 200.0000*cm, 275.0000*cm),
        logic_c13736, "phys_c13736", worldLogical, false, 13736, fCheckOverlaps);

    // ---- Cell 13737: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13737 = new G4Box("solid_c13737",
        5.0000*cm, 680.0000*cm, 280.0000*cm);
    auto* logic_c13737 = new G4LogicalVolume(solid_c13737, fMaterials[7], "logic_c13737");
    new G4PVPlacement(0, G4ThreeVector(-585.0000*cm, 200.0000*cm, 280.0000*cm),
        logic_c13737, "phys_c13737", worldLogical, false, 13737, fCheckOverlaps);

    // ---- Cell 13738: Left side wall (outer) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13738 = new G4Box("solid_c13738",
        5.0000*cm, 680.0000*cm, 285.0000*cm);
    auto* logic_c13738 = new G4LogicalVolume(solid_c13738, fMaterials[7], "logic_c13738");
    new G4PVPlacement(0, G4ThreeVector(-595.0000*cm, 200.0000*cm, 285.0000*cm),
        logic_c13738, "phys_c13738", worldLogical, false, 13738, fCheckOverlaps);

    // ---- Cell 1374: Left side wall (upper 2) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1374 = new G4Box("solid_c1374",
        80.0000*cm, 40.0000*cm, 250.0000*cm);
    auto* logic_c1374 = new G4LogicalVolume(solid_c1374, fMaterials[7], "logic_c1374");
    new G4PVPlacement(0, G4ThreeVector(-440.0000*cm, 840.0000*cm, 250.0000*cm),
        logic_c1374, "phys_c1374", worldLogical, false, 1374, fCheckOverlaps);

    // ---- Cell 1375: Left side wall (labyrinth (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1375 = new G4Box("solid_c1375",
        160.0000*cm, 40.0000*cm, 250.0000*cm);
    auto* logic_c1375 = new G4LogicalVolume(solid_c1375, fMaterials[7], "logic_c1375");
    new G4PVPlacement(0, G4ThreeVector(-360.0000*cm, -280.0000*cm, 250.0000*cm),
        logic_c1375, "phys_c1375", worldLogical, false, 1375, fCheckOverlaps);

    // ---- Cell 1376: Left side wall (cover) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1376 = new G4Box("solid_c1376",
        120.0000*cm, 40.0000*cm, 290.0000*cm);
    auto* logic_c1376 = new G4LogicalVolume(solid_c1376, fMaterials[7], "logic_c1376");
    new G4PVPlacement(0, G4ThreeVector(-240.0000*cm, 840.0000*cm, 290.0000*cm),
        logic_c1376, "phys_c1376", worldLogical, false, 1376, fCheckOverlaps);

    // ---- Cell 13770: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13770 = new G4Box("solid_c13770",
        245.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13770 = new G4LogicalVolume(solid_c13770, fMaterials[7], "logic_c13770");
    new G4PVPlacement(0, G4ThreeVector(-285.0000*cm, 160.0000*cm, 505.0000*cm),
        logic_c13770, "phys_c13770", worldLogical, false, 13770, fCheckOverlaps);

    // ---- Cell 13771: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13771 = new G4Box("solid_c13771",
        250.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13771 = new G4LogicalVolume(solid_c13771, fMaterials[7], "logic_c13771");
    new G4PVPlacement(0, G4ThreeVector(-290.0000*cm, 160.0000*cm, 515.0000*cm),
        logic_c13771, "phys_c13771", worldLogical, false, 13771, fCheckOverlaps);

    // ---- Cell 13772: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13772 = new G4Box("solid_c13772",
        255.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13772 = new G4LogicalVolume(solid_c13772, fMaterials[7], "logic_c13772");
    new G4PVPlacement(0, G4ThreeVector(-295.0000*cm, 160.0000*cm, 525.0000*cm),
        logic_c13772, "phys_c13772", worldLogical, false, 13772, fCheckOverlaps);

    // ---- Cell 13773: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13773 = new G4Box("solid_c13773",
        260.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13773 = new G4LogicalVolume(solid_c13773, fMaterials[7], "logic_c13773");
    new G4PVPlacement(0, G4ThreeVector(-300.0000*cm, 160.0000*cm, 535.0000*cm),
        logic_c13773, "phys_c13773", worldLogical, false, 13773, fCheckOverlaps);

    // ---- Cell 13774: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13774 = new G4Box("solid_c13774",
        265.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13774 = new G4LogicalVolume(solid_c13774, fMaterials[7], "logic_c13774");
    new G4PVPlacement(0, G4ThreeVector(-305.0000*cm, 160.0000*cm, 545.0000*cm),
        logic_c13774, "phys_c13774", worldLogical, false, 13774, fCheckOverlaps);

    // ---- Cell 13775: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13775 = new G4Box("solid_c13775",
        270.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13775 = new G4LogicalVolume(solid_c13775, fMaterials[7], "logic_c13775");
    new G4PVPlacement(0, G4ThreeVector(-310.0000*cm, 160.0000*cm, 555.0000*cm),
        logic_c13775, "phys_c13775", worldLogical, false, 13775, fCheckOverlaps);

    // ---- Cell 13776: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13776 = new G4Box("solid_c13776",
        275.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13776 = new G4LogicalVolume(solid_c13776, fMaterials[7], "logic_c13776");
    new G4PVPlacement(0, G4ThreeVector(-315.0000*cm, 160.0000*cm, 565.0000*cm),
        logic_c13776, "phys_c13776", worldLogical, false, 13776, fCheckOverlaps);

    // ---- Cell 13777: Left side roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c13777 = new G4Box("solid_c13777",
        280.0000*cm, 640.0000*cm, 5.0000*cm);
    auto* logic_c13777 = new G4LogicalVolume(solid_c13777, fMaterials[7], "logic_c13777");
    new G4PVPlacement(0, G4ThreeVector(-320.0000*cm, 160.0000*cm, 575.0000*cm),
        logic_c13777, "phys_c13777", worldLogical, false, 13777, fCheckOverlaps);

    // ---- Cell 1402: Behind (front wall) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1402 = new G4Box("solid_c1402",
        100.0000*cm, 40.0000*cm, 120.0000*cm);
    auto* logic_c1402 = new G4LogicalVolume(solid_c1402, fMaterials[7], "logic_c1402");
    new G4PVPlacement(0, G4ThreeVector(100.0000*cm, -440.0000*cm, 120.0000*cm),
        logic_c1402, "phys_c1402", worldLogical, false, 1402, fCheckOverlaps);

    // ---- Cell 1403: Behind (Labyrinth wall) (Mat 7: MagnetiteConcrete) ----
    auto* solid_c1403 = new G4Box("solid_c1403",
        100.0000*cm, 40.0000*cm, 120.0000*cm);
    auto* logic_c1403 = new G4LogicalVolume(solid_c1403, fMaterials[7], "logic_c1403");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, -280.0000*cm, 120.0000*cm),
        logic_c1403, "phys_c1403", worldLogical, false, 1403, fCheckOverlaps);

    // ---- Cell 1602: Outside left wall (Mat 2: Air) ----
    auto* solid_c1602 = new G4Orb("solid_c1602", 10.0000*cm);
    auto* logic_c1602 = new G4LogicalVolume(solid_c1602, fMaterials[2], "logic_c1602");
    new G4PVPlacement(0, G4ThreeVector(220.0000*cm, 930.0000*cm, 150.0000*cm),
        logic_c1602, "phys_c1602", worldLogical, false, 1602, fCheckOverlaps);

    // ---- Cell 1603: Outside door (Mat 2: Air) ----
    auto* solid_c1603 = new G4Orb("solid_c1603", 10.0000*cm);
    auto* logic_c1603 = new G4LogicalVolume(solid_c1603, fMaterials[2], "logic_c1603");
    new G4PVPlacement(0, G4ThreeVector(-150.0000*cm, 440.0000*cm, 150.0000*cm),
        logic_c1603, "phys_c1603", worldLogical, false, 1603, fCheckOverlaps);

    // ---- Cell 1604: Detector in CLIC bunker below (Mat 2: Air) ----
    auto* solid_c1604 = new G4Orb("solid_c1604", 10.0000*cm);
    auto* logic_c1604 = new G4LogicalVolume(solid_c1604, fMaterials[2], "logic_c1604");
    new G4PVPlacement(0, G4ThreeVector(135.0000*cm, 130.0000*cm, 150.0000*cm),
        logic_c1604, "phys_c1604", worldLogical, false, 1604, fCheckOverlaps);

    // ---- Cell 1110: North of bunker (Air) (Mat 2: Air) ----
    auto* solid_c1110_box = new G4Box("solid_c1110_box",
        200.0000*cm, 1944.7500*cm, 160.0000*cm);
    auto* solid_c1110_sph0 = new G4Orb("solid_c1110_sph0", 10.0000*cm);
    auto* solid_c1110_b0 = new G4SubtractionSolid("solid_c1110_b0",
        solid_c1110_box, solid_c1110_sph0,
        0, G4ThreeVector(60.0000*cm, -1925.2500*cm, -10.0000*cm));
    auto* solid_c1110 = solid_c1110_b0;
    auto* logic_c1110 = new G4LogicalVolume(solid_c1110, fMaterials[2], "logic_c1110");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 2855.2500*cm, 160.0000*cm),
        logic_c1110, "phys_c1110", worldLogical, false, 1110, fCheckOverlaps);

    // ---- Cell 1111: North of bunker (Air) (Mat 2: Air) ----
    auto* solid_c1111_box = new G4Box("solid_c1111_box",
        200.0000*cm, 0.2500*cm, 160.0000*cm);
    auto* solid_c1111_sph0 = new G4Orb("solid_c1111_sph0", 10.0000*cm);
    auto* solid_c1111_b0 = new G4SubtractionSolid("solid_c1111_b0",
        solid_c1111_box, solid_c1111_sph0,
        0, G4ThreeVector(60.0000*cm, 49.7500*cm, -10.0000*cm));
    auto* solid_c1111 = solid_c1111_b0;
    auto* logic_c1111 = new G4LogicalVolume(solid_c1111, fMaterials[2], "logic_c1111");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 880.2500*cm, 160.0000*cm),
        logic_c1111, "phys_c1111", worldLogical, false, 1111, fCheckOverlaps);

    // ---- Cell 2010: Inside bunker inner most part of labyrinth (Mat 2: Air) ----
    auto* solid_c2010 = new G4Box("solid_c2010",
        40.0000*cm, 36.2500*cm, 120.0000*cm);
    auto* logic_c2010 = new G4LogicalVolume(solid_c2010, fMaterials[2], "logic_c2010");
    new G4PVPlacement(0, G4ThreeVector(40.0000*cm, 683.7500*cm, 120.0000*cm),
        logic_c2010, "phys_c2010", worldLogical, false, 2010, fCheckOverlaps);

    // ---- Cell 2015: Inside bunker inner most part of labyrinth (Mat 2: Air) ----
    auto* solid_c2015 = new G4Box("solid_c2015",
        40.0000*cm, 3.7500*cm, 100.0000*cm);
    auto* logic_c2015 = new G4LogicalVolume(solid_c2015, fMaterials[2], "logic_c2015");
    new G4PVPlacement(0, G4ThreeVector(40.0000*cm, 643.7500*cm, 100.0000*cm),
        logic_c2015, "phys_c2015", worldLogical, false, 2015, fCheckOverlaps);

    // ---- Cell 2016:  (Mat 53: BoratedParaffin) ----
    auto* solid_c2016_box = new G4Box("solid_c2016_box",
        40.0000*cm, 3.7500*cm, 20.0000*cm);
    auto* solid_c2016_cyl0 = new G4Tubs("solid_c2016_cyl0",
        0., 8.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2016_0 = new G4RotationMatrix();
    rot_c2016_0->rotateX(90.*deg);
    auto* solid_c2016_b0 = new G4SubtractionSolid("solid_c2016_b0",
        solid_c2016_box, solid_c2016_cyl0,
        rot_c2016_0, G4ThreeVector(30.5000*cm, 0.0000*cm, 6.5000*cm));
    auto* solid_c2016_cyl1 = new G4Tubs("solid_c2016_cyl1",
        0., 10.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2016_1 = new G4RotationMatrix();
    rot_c2016_1->rotateX(90.*deg);
    auto* solid_c2016_b1 = new G4SubtractionSolid("solid_c2016_b1",
        solid_c2016_b0, solid_c2016_cyl1,
        rot_c2016_1, G4ThreeVector(9.5000*cm, 0.0000*cm, 8.5000*cm));
    auto* solid_c2016_cyl2 = new G4Tubs("solid_c2016_cyl2",
        0., 8.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2016_2 = new G4RotationMatrix();
    rot_c2016_2->rotateX(90.*deg);
    auto* solid_c2016_b2 = new G4SubtractionSolid("solid_c2016_b2",
        solid_c2016_b1, solid_c2016_cyl2,
        rot_c2016_2, G4ThreeVector(-20.0000*cm, 0.0000*cm, 7.5000*cm));
    auto* solid_c2016 = solid_c2016_b2;
    auto* logic_c2016 = new G4LogicalVolume(solid_c2016, fMaterials[53], "logic_c2016");
    new G4PVPlacement(0, G4ThreeVector(40.0000*cm, 643.7500*cm, 220.0000*cm),
        logic_c2016, "phys_c2016", worldLogical, false, 2016, fCheckOverlaps);

    // ---- Cell 2017:  (Mat 2: Air) ----
    auto* solid_c2017_box = new G4Box("solid_c2017_box",
        4800.0000*cm, 3.7500*cm, 4800.0000*cm);
    auto* solid_c2017_cyl0 = new G4Tubs("solid_c2017_cyl0",
        0., 8.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2017_0 = new G4RotationMatrix();
    rot_c2017_0->rotateX(90.*deg);
    auto* solid_c2017_b0 = new G4IntersectionSolid("solid_c2017_b0",
        solid_c2017_box, solid_c2017_cyl0,
        rot_c2017_0, G4ThreeVector(70.5000*cm, 0.0000*cm, 226.5000*cm));
    auto* solid_c2017 = solid_c2017_b0;
    auto* logic_c2017 = new G4LogicalVolume(solid_c2017, fMaterials[2], "logic_c2017");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 643.7500*cm, 0.0000*cm),
        logic_c2017, "phys_c2017", worldLogical, false, 2017, fCheckOverlaps);

    // ---- Cell 2018:  (Mat 2: Air) ----
    auto* solid_c2018_box = new G4Box("solid_c2018_box",
        4800.0000*cm, 3.7500*cm, 4800.0000*cm);
    auto* solid_c2018_cyl0 = new G4Tubs("solid_c2018_cyl0",
        0., 10.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2018_0 = new G4RotationMatrix();
    rot_c2018_0->rotateX(90.*deg);
    auto* solid_c2018_b0 = new G4IntersectionSolid("solid_c2018_b0",
        solid_c2018_box, solid_c2018_cyl0,
        rot_c2018_0, G4ThreeVector(49.5000*cm, 0.0000*cm, 228.5000*cm));
    auto* solid_c2018 = solid_c2018_b0;
    auto* logic_c2018 = new G4LogicalVolume(solid_c2018, fMaterials[2], "logic_c2018");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 643.7500*cm, 0.0000*cm),
        logic_c2018, "phys_c2018", worldLogical, false, 2018, fCheckOverlaps);

    // ---- Cell 2019:  (Mat 2: Air) ----
    auto* solid_c2019_box = new G4Box("solid_c2019_box",
        4800.0000*cm, 3.7500*cm, 4800.0000*cm);
    auto* solid_c2019_cyl0 = new G4Tubs("solid_c2019_cyl0",
        0., 8.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2019_0 = new G4RotationMatrix();
    rot_c2019_0->rotateX(90.*deg);
    auto* solid_c2019_b0 = new G4IntersectionSolid("solid_c2019_b0",
        solid_c2019_box, solid_c2019_cyl0,
        rot_c2019_0, G4ThreeVector(20.0000*cm, 0.0000*cm, 227.5000*cm));
    auto* solid_c2019 = solid_c2019_b0;
    auto* logic_c2019 = new G4LogicalVolume(solid_c2019, fMaterials[2], "logic_c2019");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 643.7500*cm, 0.0000*cm),
        logic_c2019, "phys_c2019", worldLogical, false, 2019, fCheckOverlaps);

    // ---- Cell 2020: Inside bunker intermediate part of labyrinth (Mat 2: Air) ----
    auto* solid_c2020 = new G4Box("solid_c2020",
        140.0000*cm, 40.0000*cm, 120.0000*cm);
    auto* logic_c2020 = new G4LogicalVolume(solid_c2020, fMaterials[2], "logic_c2020");
    new G4PVPlacement(0, G4ThreeVector(140.0000*cm, 760.0000*cm, 120.0000*cm),
        logic_c2020, "phys_c2020", worldLogical, false, 2020, fCheckOverlaps);

    // ---- Cell 2030: Inside bunker outer most part of labyrint (Mat 2: Air) ----
    auto* solid_c2030 = new G4Box("solid_c2030",
        40.0000*cm, 25.0000*cm, 120.0000*cm);
    auto* logic_c2030 = new G4LogicalVolume(solid_c2030, fMaterials[2], "logic_c2030");
    new G4PVPlacement(0, G4ThreeVector(240.0000*cm, 825.0000*cm, 120.0000*cm),
        logic_c2030, "phys_c2030", worldLogical, false, 2030, fCheckOverlaps);

    // ---- Cell 2040:  (Mat 5: Polyethylene) ----
    auto* solid_c2040_box = new G4Box("solid_c2040_box",
        40.0000*cm, 15.0000*cm, 20.0000*cm);
    auto* solid_c2040_cyl0 = new G4Tubs("solid_c2040_cyl0",
        0., 8.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2040_0 = new G4RotationMatrix();
    rot_c2040_0->rotateX(90.*deg);
    auto* solid_c2040_b0 = new G4SubtractionSolid("solid_c2040_b0",
        solid_c2040_box, solid_c2040_cyl0,
        rot_c2040_0, G4ThreeVector(30.5000*cm, 0.0000*cm, 6.5000*cm));
    auto* solid_c2040_cyl1 = new G4Tubs("solid_c2040_cyl1",
        0., 10.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2040_1 = new G4RotationMatrix();
    rot_c2040_1->rotateX(90.*deg);
    auto* solid_c2040_b1 = new G4SubtractionSolid("solid_c2040_b1",
        solid_c2040_b0, solid_c2040_cyl1,
        rot_c2040_1, G4ThreeVector(10.5000*cm, 0.0000*cm, 8.5000*cm));
    auto* solid_c2040_cyl2 = new G4Tubs("solid_c2040_cyl2",
        0., 8.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2040_2 = new G4RotationMatrix();
    rot_c2040_2->rotateX(90.*deg);
    auto* solid_c2040_b2 = new G4SubtractionSolid("solid_c2040_b2",
        solid_c2040_b1, solid_c2040_cyl2,
        rot_c2040_2, G4ThreeVector(-20.0000*cm, 0.0000*cm, 7.5000*cm));
    auto* solid_c2040 = solid_c2040_b2;
    auto* logic_c2040 = new G4LogicalVolume(solid_c2040, fMaterials[5], "logic_c2040");
    new G4PVPlacement(0, G4ThreeVector(240.0000*cm, 865.0000*cm, 220.0000*cm),
        logic_c2040, "phys_c2040", worldLogical, false, 2040, fCheckOverlaps);

    // ---- Cell 2041:  (Mat 2: Air) ----
    auto* solid_c2041 = new G4Box("solid_c2041",
        40.0000*cm, 15.0000*cm, 100.0000*cm);
    auto* logic_c2041 = new G4LogicalVolume(solid_c2041, fMaterials[2], "logic_c2041");
    new G4PVPlacement(0, G4ThreeVector(240.0000*cm, 865.0000*cm, 100.0000*cm),
        logic_c2041, "phys_c2041", worldLogical, false, 2041, fCheckOverlaps);

    // ---- Cell 2042:  (Mat 2: Air) ----
    auto* solid_c2042_box = new G4Box("solid_c2042_box",
        4800.0000*cm, 15.0000*cm, 4800.0000*cm);
    auto* solid_c2042_cyl0 = new G4Tubs("solid_c2042_cyl0",
        0., 8.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2042_0 = new G4RotationMatrix();
    rot_c2042_0->rotateX(90.*deg);
    auto* solid_c2042_b0 = new G4IntersectionSolid("solid_c2042_b0",
        solid_c2042_box, solid_c2042_cyl0,
        rot_c2042_0, G4ThreeVector(270.5000*cm, 0.0000*cm, 226.5000*cm));
    auto* solid_c2042 = solid_c2042_b0;
    auto* logic_c2042 = new G4LogicalVolume(solid_c2042, fMaterials[2], "logic_c2042");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 865.0000*cm, 0.0000*cm),
        logic_c2042, "phys_c2042", worldLogical, false, 2042, fCheckOverlaps);

    // ---- Cell 2043:  (Mat 2: Air) ----
    auto* solid_c2043_box = new G4Box("solid_c2043_box",
        4800.0000*cm, 15.0000*cm, 4800.0000*cm);
    auto* solid_c2043_cyl0 = new G4Tubs("solid_c2043_cyl0",
        0., 10.5000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2043_0 = new G4RotationMatrix();
    rot_c2043_0->rotateX(90.*deg);
    auto* solid_c2043_b0 = new G4IntersectionSolid("solid_c2043_b0",
        solid_c2043_box, solid_c2043_cyl0,
        rot_c2043_0, G4ThreeVector(250.5000*cm, 0.0000*cm, 228.5000*cm));
    auto* solid_c2043 = solid_c2043_b0;
    auto* logic_c2043 = new G4LogicalVolume(solid_c2043, fMaterials[2], "logic_c2043");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 865.0000*cm, 0.0000*cm),
        logic_c2043, "phys_c2043", worldLogical, false, 2043, fCheckOverlaps);

    // ---- Cell 2044:  (Mat 2: Air) ----
    auto* solid_c2044_box = new G4Box("solid_c2044_box",
        4800.0000*cm, 15.0000*cm, 4800.0000*cm);
    auto* solid_c2044_cyl0 = new G4Tubs("solid_c2044_cyl0",
        0., 8.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2044_0 = new G4RotationMatrix();
    rot_c2044_0->rotateX(90.*deg);
    auto* solid_c2044_b0 = new G4IntersectionSolid("solid_c2044_b0",
        solid_c2044_box, solid_c2044_cyl0,
        rot_c2044_0, G4ThreeVector(220.0000*cm, 0.0000*cm, 227.5000*cm));
    auto* solid_c2044 = solid_c2044_b0;
    auto* logic_c2044 = new G4LogicalVolume(solid_c2044, fMaterials[2], "logic_c2044");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 865.0000*cm, 0.0000*cm),
        logic_c2044, "phys_c2044", worldLogical, false, 2044, fCheckOverlaps);

    // ---- Cell 2050:  (Mat 5: Polyethylene) ----
    auto* solid_c2050 = new G4Box("solid_c2050",
        45.0000*cm, 15.0000*cm, 102.2500*cm);
    auto* logic_c2050 = new G4LogicalVolume(solid_c2050, fMaterials[5], "logic_c2050");
    new G4PVPlacement(0, G4ThreeVector(240.0000*cm, 895.5000*cm, 102.7500*cm),
        logic_c2050, "phys_c2050", worldLogical, false, 2050, fCheckOverlaps);

    // ---- Cell 2051:  (Mat 2: Air) ----
    auto* solid_c2051 = new G4Box("solid_c2051",
        45.0000*cm, 15.0000*cm, 0.2500*cm);
    auto* logic_c2051 = new G4LogicalVolume(solid_c2051, fMaterials[2], "logic_c2051");
    new G4PVPlacement(0, G4ThreeVector(240.0000*cm, 895.5000*cm, 0.2500*cm),
        logic_c2051, "phys_c2051", worldLogical, false, 2051, fCheckOverlaps);

    // ---- Cell 2052:  (Mat 2: Air) ----
    auto* solid_c2052 = new G4Box("solid_c2052",
        37.5000*cm, 15.0000*cm, 102.5000*cm);
    auto* logic_c2052 = new G4LogicalVolume(solid_c2052, fMaterials[2], "logic_c2052");
    new G4PVPlacement(0, G4ThreeVector(322.5000*cm, 895.5000*cm, 102.5000*cm),
        logic_c2052, "phys_c2052", worldLogical, false, 2052, fCheckOverlaps);

    // ---- Cell 2053:  (Mat 2: Air) ----
    auto* solid_c2053 = new G4Box("solid_c2053",
        117.5000*cm, 15.0000*cm, 102.5000*cm);
    auto* logic_c2053 = new G4LogicalVolume(solid_c2053, fMaterials[2], "logic_c2053");
    new G4PVPlacement(0, G4ThreeVector(77.5000*cm, 895.5000*cm, 102.5000*cm),
        logic_c2053, "phys_c2053", worldLogical, false, 2053, fCheckOverlaps);

    // ---- Cell 2054:  (Mat 2: Air) ----
    auto* solid_c2054 = new G4Box("solid_c2054",
        200.0000*cm, 15.0000*cm, 57.5000*cm);
    auto* logic_c2054 = new G4LogicalVolume(solid_c2054, fMaterials[2], "logic_c2054");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 895.5000*cm, 262.5000*cm),
        logic_c2054, "phys_c2054", worldLogical, false, 2054, fCheckOverlaps);

    // ---- Cell 3000:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3000 = new G4Box("solid_c3000",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3000 = new G4LogicalVolume(solid_c3000, fMaterials[7], "logic_c3000");
    new G4PVPlacement(0, G4ThreeVector(282.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3000, "phys_c3000", worldLogical, false, 3000, fCheckOverlaps);

    // ---- Cell 3020:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3020 = new G4Box("solid_c3020",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3020 = new G4LogicalVolume(solid_c3020, fMaterials[7], "logic_c3020");
    new G4PVPlacement(0, G4ThreeVector(287.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3020, "phys_c3020", worldLogical, false, 3020, fCheckOverlaps);

    // ---- Cell 3030:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3030 = new G4Box("solid_c3030",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3030 = new G4LogicalVolume(solid_c3030, fMaterials[7], "logic_c3030");
    new G4PVPlacement(0, G4ThreeVector(292.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3030, "phys_c3030", worldLogical, false, 3030, fCheckOverlaps);

    // ---- Cell 3040:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3040 = new G4Box("solid_c3040",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3040 = new G4LogicalVolume(solid_c3040, fMaterials[7], "logic_c3040");
    new G4PVPlacement(0, G4ThreeVector(297.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3040, "phys_c3040", worldLogical, false, 3040, fCheckOverlaps);

    // ---- Cell 3050:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3050 = new G4Box("solid_c3050",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3050 = new G4LogicalVolume(solid_c3050, fMaterials[7], "logic_c3050");
    new G4PVPlacement(0, G4ThreeVector(302.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3050, "phys_c3050", worldLogical, false, 3050, fCheckOverlaps);

    // ---- Cell 3060:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3060 = new G4Box("solid_c3060",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3060 = new G4LogicalVolume(solid_c3060, fMaterials[7], "logic_c3060");
    new G4PVPlacement(0, G4ThreeVector(307.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3060, "phys_c3060", worldLogical, false, 3060, fCheckOverlaps);

    // ---- Cell 3070:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3070 = new G4Box("solid_c3070",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3070 = new G4LogicalVolume(solid_c3070, fMaterials[7], "logic_c3070");
    new G4PVPlacement(0, G4ThreeVector(312.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3070, "phys_c3070", worldLogical, false, 3070, fCheckOverlaps);

    // ---- Cell 3080:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3080 = new G4Box("solid_c3080",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3080 = new G4LogicalVolume(solid_c3080, fMaterials[7], "logic_c3080");
    new G4PVPlacement(0, G4ThreeVector(317.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3080, "phys_c3080", worldLogical, false, 3080, fCheckOverlaps);

    // ---- Cell 3090:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3090 = new G4Box("solid_c3090",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3090 = new G4LogicalVolume(solid_c3090, fMaterials[7], "logic_c3090");
    new G4PVPlacement(0, G4ThreeVector(322.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3090, "phys_c3090", worldLogical, false, 3090, fCheckOverlaps);

    // ---- Cell 3100:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3100 = new G4Box("solid_c3100",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3100 = new G4LogicalVolume(solid_c3100, fMaterials[7], "logic_c3100");
    new G4PVPlacement(0, G4ThreeVector(327.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3100, "phys_c3100", worldLogical, false, 3100, fCheckOverlaps);

    // ---- Cell 3110:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3110 = new G4Box("solid_c3110",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3110 = new G4LogicalVolume(solid_c3110, fMaterials[7], "logic_c3110");
    new G4PVPlacement(0, G4ThreeVector(332.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3110, "phys_c3110", worldLogical, false, 3110, fCheckOverlaps);

    // ---- Cell 3120:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3120 = new G4Box("solid_c3120",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3120 = new G4LogicalVolume(solid_c3120, fMaterials[7], "logic_c3120");
    new G4PVPlacement(0, G4ThreeVector(337.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3120, "phys_c3120", worldLogical, false, 3120, fCheckOverlaps);

    // ---- Cell 3130:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3130 = new G4Box("solid_c3130",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3130 = new G4LogicalVolume(solid_c3130, fMaterials[7], "logic_c3130");
    new G4PVPlacement(0, G4ThreeVector(342.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3130, "phys_c3130", worldLogical, false, 3130, fCheckOverlaps);

    // ---- Cell 3140:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3140 = new G4Box("solid_c3140",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3140 = new G4LogicalVolume(solid_c3140, fMaterials[7], "logic_c3140");
    new G4PVPlacement(0, G4ThreeVector(347.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3140, "phys_c3140", worldLogical, false, 3140, fCheckOverlaps);

    // ---- Cell 3150:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3150 = new G4Box("solid_c3150",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3150 = new G4LogicalVolume(solid_c3150, fMaterials[7], "logic_c3150");
    new G4PVPlacement(0, G4ThreeVector(352.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3150, "phys_c3150", worldLogical, false, 3150, fCheckOverlaps);

    // ---- Cell 3160:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3160 = new G4Box("solid_c3160",
        2.5000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3160 = new G4LogicalVolume(solid_c3160, fMaterials[7], "logic_c3160");
    new G4PVPlacement(0, G4ThreeVector(357.5000*cm, 560.0000*cm, 120.0000*cm),
        logic_c3160, "phys_c3160", worldLogical, false, 3160, fCheckOverlaps);

    // ---- Cell 3170:  (Mat 5: Polyethylene) ----
    auto* solid_c3170 = new G4Box("solid_c3170",
        10.0000*cm, 120.0000*cm, 120.0000*cm);
    auto* logic_c3170 = new G4LogicalVolume(solid_c3170, fMaterials[5], "logic_c3170");
    new G4PVPlacement(0, G4ThreeVector(370.0000*cm, 360.0000*cm, 120.0000*cm),
        logic_c3170, "phys_c3170", worldLogical, false, 3170, fCheckOverlaps);

    // ---- Cell 3180:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3180 = new G4Box("solid_c3180",
        40.0000*cm, 320.0000*cm, 120.0000*cm);
    auto* logic_c3180 = new G4LogicalVolume(solid_c3180, fMaterials[7], "logic_c3180");
    new G4PVPlacement(0, G4ThreeVector(320.0000*cm, -160.0000*cm, 120.0000*cm),
        logic_c3180, "phys_c3180", worldLogical, false, 3180, fCheckOverlaps);

    // ---- Cell 3001:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3001_box = new G4Box("solid_c3001_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3001_cyl0 = new G4Tubs("solid_c3001_cyl0",
        0., 5.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3001_0 = new G4RotationMatrix();
    rot_c3001_0->rotateX(90.*deg);
    auto* solid_c3001_b0 = new G4IntersectionSolid("solid_c3001_b0",
        solid_c3001_box, solid_c3001_cyl0,
        rot_c3001_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3001 = solid_c3001_b0;
    auto* logic_c3001 = new G4LogicalVolume(solid_c3001, fMaterials[7], "logic_c3001");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3001, "phys_c3001", worldLogical, false, 3001, fCheckOverlaps);

    // ---- Cell 3021:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3021_box = new G4Box("solid_c3021_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3021_cyl0 = new G4Tubs("solid_c3021_cyl0",
        0., 5.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3021_0 = new G4RotationMatrix();
    rot_c3021_0->rotateX(90.*deg);
    auto* solid_c3021_b0 = new G4SubtractionSolid("solid_c3021_b0",
        solid_c3021_box, solid_c3021_cyl0,
        rot_c3021_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3021_cyl1 = new G4Tubs("solid_c3021_cyl1",
        0., 10.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3021_1 = new G4RotationMatrix();
    rot_c3021_1->rotateX(90.*deg);
    auto* solid_c3021_b1 = new G4IntersectionSolid("solid_c3021_b1",
        solid_c3021_b0, solid_c3021_cyl1,
        rot_c3021_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3021 = solid_c3021_b1;
    auto* logic_c3021 = new G4LogicalVolume(solid_c3021, fMaterials[7], "logic_c3021");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3021, "phys_c3021", worldLogical, false, 3021, fCheckOverlaps);

    // ---- Cell 3031:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3031_box = new G4Box("solid_c3031_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3031_cyl0 = new G4Tubs("solid_c3031_cyl0",
        0., 10.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3031_0 = new G4RotationMatrix();
    rot_c3031_0->rotateX(90.*deg);
    auto* solid_c3031_b0 = new G4SubtractionSolid("solid_c3031_b0",
        solid_c3031_box, solid_c3031_cyl0,
        rot_c3031_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3031_cyl1 = new G4Tubs("solid_c3031_cyl1",
        0., 15.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3031_1 = new G4RotationMatrix();
    rot_c3031_1->rotateX(90.*deg);
    auto* solid_c3031_b1 = new G4IntersectionSolid("solid_c3031_b1",
        solid_c3031_b0, solid_c3031_cyl1,
        rot_c3031_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3031 = solid_c3031_b1;
    auto* logic_c3031 = new G4LogicalVolume(solid_c3031, fMaterials[7], "logic_c3031");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3031, "phys_c3031", worldLogical, false, 3031, fCheckOverlaps);

    // ---- Cell 3041:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3041_box = new G4Box("solid_c3041_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3041_cyl0 = new G4Tubs("solid_c3041_cyl0",
        0., 15.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3041_0 = new G4RotationMatrix();
    rot_c3041_0->rotateX(90.*deg);
    auto* solid_c3041_b0 = new G4SubtractionSolid("solid_c3041_b0",
        solid_c3041_box, solid_c3041_cyl0,
        rot_c3041_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3041_cyl1 = new G4Tubs("solid_c3041_cyl1",
        0., 20.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3041_1 = new G4RotationMatrix();
    rot_c3041_1->rotateX(90.*deg);
    auto* solid_c3041_b1 = new G4IntersectionSolid("solid_c3041_b1",
        solid_c3041_b0, solid_c3041_cyl1,
        rot_c3041_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3041 = solid_c3041_b1;
    auto* logic_c3041 = new G4LogicalVolume(solid_c3041, fMaterials[7], "logic_c3041");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3041, "phys_c3041", worldLogical, false, 3041, fCheckOverlaps);

    // ---- Cell 3051:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3051_box = new G4Box("solid_c3051_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3051_cyl0 = new G4Tubs("solid_c3051_cyl0",
        0., 20.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3051_0 = new G4RotationMatrix();
    rot_c3051_0->rotateX(90.*deg);
    auto* solid_c3051_b0 = new G4SubtractionSolid("solid_c3051_b0",
        solid_c3051_box, solid_c3051_cyl0,
        rot_c3051_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3051_cyl1 = new G4Tubs("solid_c3051_cyl1",
        0., 25.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3051_1 = new G4RotationMatrix();
    rot_c3051_1->rotateX(90.*deg);
    auto* solid_c3051_b1 = new G4IntersectionSolid("solid_c3051_b1",
        solid_c3051_b0, solid_c3051_cyl1,
        rot_c3051_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3051 = solid_c3051_b1;
    auto* logic_c3051 = new G4LogicalVolume(solid_c3051, fMaterials[7], "logic_c3051");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3051, "phys_c3051", worldLogical, false, 3051, fCheckOverlaps);

    // ---- Cell 3061:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3061_box = new G4Box("solid_c3061_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3061_cyl0 = new G4Tubs("solid_c3061_cyl0",
        0., 25.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3061_0 = new G4RotationMatrix();
    rot_c3061_0->rotateX(90.*deg);
    auto* solid_c3061_b0 = new G4SubtractionSolid("solid_c3061_b0",
        solid_c3061_box, solid_c3061_cyl0,
        rot_c3061_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3061_cyl1 = new G4Tubs("solid_c3061_cyl1",
        0., 30.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3061_1 = new G4RotationMatrix();
    rot_c3061_1->rotateX(90.*deg);
    auto* solid_c3061_b1 = new G4IntersectionSolid("solid_c3061_b1",
        solid_c3061_b0, solid_c3061_cyl1,
        rot_c3061_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3061 = solid_c3061_b1;
    auto* logic_c3061 = new G4LogicalVolume(solid_c3061, fMaterials[7], "logic_c3061");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3061, "phys_c3061", worldLogical, false, 3061, fCheckOverlaps);

    // ---- Cell 3071:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3071_box = new G4Box("solid_c3071_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3071_cyl0 = new G4Tubs("solid_c3071_cyl0",
        0., 30.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3071_0 = new G4RotationMatrix();
    rot_c3071_0->rotateX(90.*deg);
    auto* solid_c3071_b0 = new G4SubtractionSolid("solid_c3071_b0",
        solid_c3071_box, solid_c3071_cyl0,
        rot_c3071_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3071_cyl1 = new G4Tubs("solid_c3071_cyl1",
        0., 35.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3071_1 = new G4RotationMatrix();
    rot_c3071_1->rotateX(90.*deg);
    auto* solid_c3071_b1 = new G4IntersectionSolid("solid_c3071_b1",
        solid_c3071_b0, solid_c3071_cyl1,
        rot_c3071_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3071 = solid_c3071_b1;
    auto* logic_c3071 = new G4LogicalVolume(solid_c3071, fMaterials[7], "logic_c3071");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3071, "phys_c3071", worldLogical, false, 3071, fCheckOverlaps);

    // ---- Cell 3081:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3081_box = new G4Box("solid_c3081_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3081_cyl0 = new G4Tubs("solid_c3081_cyl0",
        0., 35.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3081_0 = new G4RotationMatrix();
    rot_c3081_0->rotateX(90.*deg);
    auto* solid_c3081_b0 = new G4SubtractionSolid("solid_c3081_b0",
        solid_c3081_box, solid_c3081_cyl0,
        rot_c3081_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3081_cyl1 = new G4Tubs("solid_c3081_cyl1",
        0., 40.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3081_1 = new G4RotationMatrix();
    rot_c3081_1->rotateX(90.*deg);
    auto* solid_c3081_b1 = new G4IntersectionSolid("solid_c3081_b1",
        solid_c3081_b0, solid_c3081_cyl1,
        rot_c3081_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3081 = solid_c3081_b1;
    auto* logic_c3081 = new G4LogicalVolume(solid_c3081, fMaterials[7], "logic_c3081");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3081, "phys_c3081", worldLogical, false, 3081, fCheckOverlaps);

    // ---- Cell 3091:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3091_box = new G4Box("solid_c3091_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3091_cyl0 = new G4Tubs("solid_c3091_cyl0",
        0., 40.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3091_0 = new G4RotationMatrix();
    rot_c3091_0->rotateX(90.*deg);
    auto* solid_c3091_b0 = new G4SubtractionSolid("solid_c3091_b0",
        solid_c3091_box, solid_c3091_cyl0,
        rot_c3091_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3091_cyl1 = new G4Tubs("solid_c3091_cyl1",
        0., 45.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3091_1 = new G4RotationMatrix();
    rot_c3091_1->rotateX(90.*deg);
    auto* solid_c3091_b1 = new G4IntersectionSolid("solid_c3091_b1",
        solid_c3091_b0, solid_c3091_cyl1,
        rot_c3091_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3091 = solid_c3091_b1;
    auto* logic_c3091 = new G4LogicalVolume(solid_c3091, fMaterials[7], "logic_c3091");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3091, "phys_c3091", worldLogical, false, 3091, fCheckOverlaps);

    // ---- Cell 3101:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3101_box = new G4Box("solid_c3101_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3101_cyl0 = new G4Tubs("solid_c3101_cyl0",
        0., 45.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3101_0 = new G4RotationMatrix();
    rot_c3101_0->rotateX(90.*deg);
    auto* solid_c3101_b0 = new G4SubtractionSolid("solid_c3101_b0",
        solid_c3101_box, solid_c3101_cyl0,
        rot_c3101_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3101_cyl1 = new G4Tubs("solid_c3101_cyl1",
        0., 50.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3101_1 = new G4RotationMatrix();
    rot_c3101_1->rotateX(90.*deg);
    auto* solid_c3101_b1 = new G4IntersectionSolid("solid_c3101_b1",
        solid_c3101_b0, solid_c3101_cyl1,
        rot_c3101_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3101 = solid_c3101_b1;
    auto* logic_c3101 = new G4LogicalVolume(solid_c3101, fMaterials[7], "logic_c3101");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3101, "phys_c3101", worldLogical, false, 3101, fCheckOverlaps);

    // ---- Cell 3111:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3111_box = new G4Box("solid_c3111_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3111_cyl0 = new G4Tubs("solid_c3111_cyl0",
        0., 50.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3111_0 = new G4RotationMatrix();
    rot_c3111_0->rotateX(90.*deg);
    auto* solid_c3111_b0 = new G4SubtractionSolid("solid_c3111_b0",
        solid_c3111_box, solid_c3111_cyl0,
        rot_c3111_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3111_cyl1 = new G4Tubs("solid_c3111_cyl1",
        0., 55.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3111_1 = new G4RotationMatrix();
    rot_c3111_1->rotateX(90.*deg);
    auto* solid_c3111_b1 = new G4IntersectionSolid("solid_c3111_b1",
        solid_c3111_b0, solid_c3111_cyl1,
        rot_c3111_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3111 = solid_c3111_b1;
    auto* logic_c3111 = new G4LogicalVolume(solid_c3111, fMaterials[7], "logic_c3111");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3111, "phys_c3111", worldLogical, false, 3111, fCheckOverlaps);

    // ---- Cell 3121:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3121_box = new G4Box("solid_c3121_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3121_cyl0 = new G4Tubs("solid_c3121_cyl0",
        0., 55.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3121_0 = new G4RotationMatrix();
    rot_c3121_0->rotateX(90.*deg);
    auto* solid_c3121_b0 = new G4SubtractionSolid("solid_c3121_b0",
        solid_c3121_box, solid_c3121_cyl0,
        rot_c3121_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3121_cyl1 = new G4Tubs("solid_c3121_cyl1",
        0., 60.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3121_1 = new G4RotationMatrix();
    rot_c3121_1->rotateX(90.*deg);
    auto* solid_c3121_b1 = new G4IntersectionSolid("solid_c3121_b1",
        solid_c3121_b0, solid_c3121_cyl1,
        rot_c3121_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3121 = solid_c3121_b1;
    auto* logic_c3121 = new G4LogicalVolume(solid_c3121, fMaterials[7], "logic_c3121");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3121, "phys_c3121", worldLogical, false, 3121, fCheckOverlaps);

    // ---- Cell 3131:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3131_box = new G4Box("solid_c3131_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3131_cyl0 = new G4Tubs("solid_c3131_cyl0",
        0., 60.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3131_0 = new G4RotationMatrix();
    rot_c3131_0->rotateX(90.*deg);
    auto* solid_c3131_b0 = new G4SubtractionSolid("solid_c3131_b0",
        solid_c3131_box, solid_c3131_cyl0,
        rot_c3131_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3131_cyl1 = new G4Tubs("solid_c3131_cyl1",
        0., 65.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3131_1 = new G4RotationMatrix();
    rot_c3131_1->rotateX(90.*deg);
    auto* solid_c3131_b1 = new G4IntersectionSolid("solid_c3131_b1",
        solid_c3131_b0, solid_c3131_cyl1,
        rot_c3131_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3131 = solid_c3131_b1;
    auto* logic_c3131 = new G4LogicalVolume(solid_c3131, fMaterials[7], "logic_c3131");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3131, "phys_c3131", worldLogical, false, 3131, fCheckOverlaps);

    // ---- Cell 3141:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3141_box = new G4Box("solid_c3141_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3141_cyl0 = new G4Tubs("solid_c3141_cyl0",
        0., 65.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3141_0 = new G4RotationMatrix();
    rot_c3141_0->rotateX(90.*deg);
    auto* solid_c3141_b0 = new G4SubtractionSolid("solid_c3141_b0",
        solid_c3141_box, solid_c3141_cyl0,
        rot_c3141_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3141_cyl1 = new G4Tubs("solid_c3141_cyl1",
        0., 70.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3141_1 = new G4RotationMatrix();
    rot_c3141_1->rotateX(90.*deg);
    auto* solid_c3141_b1 = new G4IntersectionSolid("solid_c3141_b1",
        solid_c3141_b0, solid_c3141_cyl1,
        rot_c3141_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3141 = solid_c3141_b1;
    auto* logic_c3141 = new G4LogicalVolume(solid_c3141, fMaterials[7], "logic_c3141");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3141, "phys_c3141", worldLogical, false, 3141, fCheckOverlaps);

    // ---- Cell 3151:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3151_box = new G4Box("solid_c3151_box",
        2260.0000*cm, 320.0000*cm, 2280.0000*cm);
    auto* solid_c3151_cyl0 = new G4Tubs("solid_c3151_cyl0",
        0., 70.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3151_0 = new G4RotationMatrix();
    rot_c3151_0->rotateX(90.*deg);
    auto* solid_c3151_b0 = new G4SubtractionSolid("solid_c3151_b0",
        solid_c3151_box, solid_c3151_cyl0,
        rot_c3151_0, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3151_cyl1 = new G4Tubs("solid_c3151_cyl1",
        0., 75.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3151_1 = new G4RotationMatrix();
    rot_c3151_1->rotateX(90.*deg);
    auto* solid_c3151_b1 = new G4IntersectionSolid("solid_c3151_b1",
        solid_c3151_b0, solid_c3151_cyl1,
        rot_c3151_1, G4ThreeVector(-2260.0000*cm, 0.0000*cm, -2280.0000*cm));
    auto* solid_c3151 = solid_c3151_b1;
    auto* logic_c3151 = new G4LogicalVolume(solid_c3151, fMaterials[7], "logic_c3151");
    new G4PVPlacement(0, G4ThreeVector(2540.0000*cm, 560.0000*cm, 2520.0000*cm),
        logic_c3151, "phys_c3151", worldLogical, false, 3151, fCheckOverlaps);

    // ---- Cell 3161:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3161_box = new G4Box("solid_c3161_box",
        40.0000*cm, 320.0000*cm, 40.0000*cm);
    auto* solid_c3161_cyl0 = new G4Tubs("solid_c3161_cyl0",
        0., 75.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c3161_0 = new G4RotationMatrix();
    rot_c3161_0->rotateX(90.*deg);
    auto* solid_c3161_b0 = new G4SubtractionSolid("solid_c3161_b0",
        solid_c3161_box, solid_c3161_cyl0,
        rot_c3161_0, G4ThreeVector(-40.0000*cm, 0.0000*cm, -40.0000*cm));
    auto* solid_c3161 = solid_c3161_b0;
    auto* logic_c3161 = new G4LogicalVolume(solid_c3161, fMaterials[7], "logic_c3161");
    new G4PVPlacement(0, G4ThreeVector(320.0000*cm, 560.0000*cm, 280.0000*cm),
        logic_c3161, "phys_c3161", worldLogical, false, 3161, fCheckOverlaps);

    // ---- Cell 3171:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3171 = new G4Box("solid_c3171",
        40.0000*cm, 320.0000*cm, 40.0000*cm);
    auto* logic_c3171 = new G4LogicalVolume(solid_c3171, fMaterials[7], "logic_c3171");
    new G4PVPlacement(0, G4ThreeVector(320.0000*cm, -160.0000*cm, 280.0000*cm),
        logic_c3171, "phys_c3171", worldLogical, false, 3171, fCheckOverlaps);

    // ---- Cell 3002: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3002 = new G4Box("solid_c3002",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3002 = new G4LogicalVolume(solid_c3002, fMaterials[7], "logic_c3002");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 242.5000*cm),
        logic_c3002, "phys_c3002", worldLogical, false, 3002, fCheckOverlaps);

    // ---- Cell 3022: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3022 = new G4Box("solid_c3022",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3022 = new G4LogicalVolume(solid_c3022, fMaterials[7], "logic_c3022");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 247.5000*cm),
        logic_c3022, "phys_c3022", worldLogical, false, 3022, fCheckOverlaps);

    // ---- Cell 3032: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3032 = new G4Box("solid_c3032",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3032 = new G4LogicalVolume(solid_c3032, fMaterials[7], "logic_c3032");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 252.5000*cm),
        logic_c3032, "phys_c3032", worldLogical, false, 3032, fCheckOverlaps);

    // ---- Cell 3042: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3042 = new G4Box("solid_c3042",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3042 = new G4LogicalVolume(solid_c3042, fMaterials[7], "logic_c3042");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 257.5000*cm),
        logic_c3042, "phys_c3042", worldLogical, false, 3042, fCheckOverlaps);

    // ---- Cell 3052: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3052 = new G4Box("solid_c3052",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3052 = new G4LogicalVolume(solid_c3052, fMaterials[7], "logic_c3052");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 262.5000*cm),
        logic_c3052, "phys_c3052", worldLogical, false, 3052, fCheckOverlaps);

    // ---- Cell 3062: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3062 = new G4Box("solid_c3062",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3062 = new G4LogicalVolume(solid_c3062, fMaterials[7], "logic_c3062");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 267.5000*cm),
        logic_c3062, "phys_c3062", worldLogical, false, 3062, fCheckOverlaps);

    // ---- Cell 3072: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3072 = new G4Box("solid_c3072",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3072 = new G4LogicalVolume(solid_c3072, fMaterials[7], "logic_c3072");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 272.5000*cm),
        logic_c3072, "phys_c3072", worldLogical, false, 3072, fCheckOverlaps);

    // ---- Cell 3082: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3082 = new G4Box("solid_c3082",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3082 = new G4LogicalVolume(solid_c3082, fMaterials[7], "logic_c3082");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 277.5000*cm),
        logic_c3082, "phys_c3082", worldLogical, false, 3082, fCheckOverlaps);

    // ---- Cell 3092: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3092 = new G4Box("solid_c3092",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3092 = new G4LogicalVolume(solid_c3092, fMaterials[7], "logic_c3092");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 282.5000*cm),
        logic_c3092, "phys_c3092", worldLogical, false, 3092, fCheckOverlaps);

    // ---- Cell 3102: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3102 = new G4Box("solid_c3102",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3102 = new G4LogicalVolume(solid_c3102, fMaterials[7], "logic_c3102");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 287.5000*cm),
        logic_c3102, "phys_c3102", worldLogical, false, 3102, fCheckOverlaps);

    // ---- Cell 3112: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3112 = new G4Box("solid_c3112",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3112 = new G4LogicalVolume(solid_c3112, fMaterials[7], "logic_c3112");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 292.5000*cm),
        logic_c3112, "phys_c3112", worldLogical, false, 3112, fCheckOverlaps);

    // ---- Cell 3122: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3122 = new G4Box("solid_c3122",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3122 = new G4LogicalVolume(solid_c3122, fMaterials[7], "logic_c3122");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 297.5000*cm),
        logic_c3122, "phys_c3122", worldLogical, false, 3122, fCheckOverlaps);

    // ---- Cell 3132: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3132 = new G4Box("solid_c3132",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3132 = new G4LogicalVolume(solid_c3132, fMaterials[7], "logic_c3132");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 302.5000*cm),
        logic_c3132, "phys_c3132", worldLogical, false, 3132, fCheckOverlaps);

    // ---- Cell 3142: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3142 = new G4Box("solid_c3142",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3142 = new G4LogicalVolume(solid_c3142, fMaterials[7], "logic_c3142");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 307.5000*cm),
        logic_c3142, "phys_c3142", worldLogical, false, 3142, fCheckOverlaps);

    // ---- Cell 3152: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3152 = new G4Box("solid_c3152",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3152 = new G4LogicalVolume(solid_c3152, fMaterials[7], "logic_c3152");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 312.5000*cm),
        logic_c3152, "phys_c3152", worldLogical, false, 3152, fCheckOverlaps);

    // ---- Cell 3162: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3162 = new G4Box("solid_c3162",
        160.0000*cm, 320.0000*cm, 2.5000*cm);
    auto* logic_c3162 = new G4LogicalVolume(solid_c3162, fMaterials[7], "logic_c3162");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, 560.0000*cm, 317.5000*cm),
        logic_c3162, "phys_c3162", worldLogical, false, 3162, fCheckOverlaps);

    // ---- Cell 3172: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3172 = new G4Box("solid_c3172",
        160.0000*cm, 320.0000*cm, 40.0000*cm);
    auto* logic_c3172 = new G4LogicalVolume(solid_c3172, fMaterials[7], "logic_c3172");
    new G4PVPlacement(0, G4ThreeVector(120.0000*cm, -160.0000*cm, 280.0000*cm),
        logic_c3172, "phys_c3172", worldLogical, false, 3172, fCheckOverlaps);

    // ---- Cell 3182: Roof (Mat 7: MagnetiteConcrete) ----
    auto* solid_c3182 = new G4Box("solid_c3182",
        20.0000*cm, 40.0000*cm, 40.0000*cm);
    auto* logic_c3182 = new G4LogicalVolume(solid_c3182, fMaterials[7], "logic_c3182");
    new G4PVPlacement(0, G4ThreeVector(-20.0000*cm, 200.0000*cm, 280.0000*cm),
        logic_c3182, "phys_c3182", worldLogical, false, 3182, fCheckOverlaps);

    // ---- Cell 3005:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3005 = new G4Box("solid_c3005",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3005 = new G4LogicalVolume(solid_c3005, fMaterials[3], "logic_c3005");
    new G4PVPlacement(0, G4ThreeVector(282.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3005, "phys_c3005", worldLogical, false, 3005, fCheckOverlaps);

    // ---- Cell 3025:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3025 = new G4Box("solid_c3025",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3025 = new G4LogicalVolume(solid_c3025, fMaterials[3], "logic_c3025");
    new G4PVPlacement(0, G4ThreeVector(287.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3025, "phys_c3025", worldLogical, false, 3025, fCheckOverlaps);

    // ---- Cell 3035:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3035 = new G4Box("solid_c3035",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3035 = new G4LogicalVolume(solid_c3035, fMaterials[3], "logic_c3035");
    new G4PVPlacement(0, G4ThreeVector(292.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3035, "phys_c3035", worldLogical, false, 3035, fCheckOverlaps);

    // ---- Cell 3045:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3045 = new G4Box("solid_c3045",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3045 = new G4LogicalVolume(solid_c3045, fMaterials[3], "logic_c3045");
    new G4PVPlacement(0, G4ThreeVector(297.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3045, "phys_c3045", worldLogical, false, 3045, fCheckOverlaps);

    // ---- Cell 3055:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3055 = new G4Box("solid_c3055",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3055 = new G4LogicalVolume(solid_c3055, fMaterials[3], "logic_c3055");
    new G4PVPlacement(0, G4ThreeVector(302.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3055, "phys_c3055", worldLogical, false, 3055, fCheckOverlaps);

    // ---- Cell 3065:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3065 = new G4Box("solid_c3065",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3065 = new G4LogicalVolume(solid_c3065, fMaterials[3], "logic_c3065");
    new G4PVPlacement(0, G4ThreeVector(307.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3065, "phys_c3065", worldLogical, false, 3065, fCheckOverlaps);

    // ---- Cell 3075:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3075 = new G4Box("solid_c3075",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3075 = new G4LogicalVolume(solid_c3075, fMaterials[3], "logic_c3075");
    new G4PVPlacement(0, G4ThreeVector(312.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3075, "phys_c3075", worldLogical, false, 3075, fCheckOverlaps);

    // ---- Cell 3085:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3085 = new G4Box("solid_c3085",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3085 = new G4LogicalVolume(solid_c3085, fMaterials[3], "logic_c3085");
    new G4PVPlacement(0, G4ThreeVector(317.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3085, "phys_c3085", worldLogical, false, 3085, fCheckOverlaps);

    // ---- Cell 3095:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3095 = new G4Box("solid_c3095",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3095 = new G4LogicalVolume(solid_c3095, fMaterials[3], "logic_c3095");
    new G4PVPlacement(0, G4ThreeVector(322.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3095, "phys_c3095", worldLogical, false, 3095, fCheckOverlaps);

    // ---- Cell 3105:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3105 = new G4Box("solid_c3105",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3105 = new G4LogicalVolume(solid_c3105, fMaterials[3], "logic_c3105");
    new G4PVPlacement(0, G4ThreeVector(327.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3105, "phys_c3105", worldLogical, false, 3105, fCheckOverlaps);

    // ---- Cell 3115:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3115 = new G4Box("solid_c3115",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3115 = new G4LogicalVolume(solid_c3115, fMaterials[3], "logic_c3115");
    new G4PVPlacement(0, G4ThreeVector(332.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3115, "phys_c3115", worldLogical, false, 3115, fCheckOverlaps);

    // ---- Cell 3125:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3125 = new G4Box("solid_c3125",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3125 = new G4LogicalVolume(solid_c3125, fMaterials[3], "logic_c3125");
    new G4PVPlacement(0, G4ThreeVector(337.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3125, "phys_c3125", worldLogical, false, 3125, fCheckOverlaps);

    // ---- Cell 3135:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3135 = new G4Box("solid_c3135",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3135 = new G4LogicalVolume(solid_c3135, fMaterials[3], "logic_c3135");
    new G4PVPlacement(0, G4ThreeVector(342.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3135, "phys_c3135", worldLogical, false, 3135, fCheckOverlaps);

    // ---- Cell 3145:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3145 = new G4Box("solid_c3145",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3145 = new G4LogicalVolume(solid_c3145, fMaterials[3], "logic_c3145");
    new G4PVPlacement(0, G4ThreeVector(347.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3145, "phys_c3145", worldLogical, false, 3145, fCheckOverlaps);

    // ---- Cell 3155:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3155 = new G4Box("solid_c3155",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3155 = new G4LogicalVolume(solid_c3155, fMaterials[3], "logic_c3155");
    new G4PVPlacement(0, G4ThreeVector(352.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3155, "phys_c3155", worldLogical, false, 3155, fCheckOverlaps);

    // ---- Cell 3165:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3165 = new G4Box("solid_c3165",
        2.5000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c3165 = new G4LogicalVolume(solid_c3165, fMaterials[3], "logic_c3165");
    new G4PVPlacement(0, G4ThreeVector(357.5000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c3165, "phys_c3165", worldLogical, false, 3165, fCheckOverlaps);

    // ---- Cell 3200:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3200 = new G4Box("solid_c3200",
        200.0000*cm, 101.2500*cm, 15.0000*cm);
    auto* logic_c3200 = new G4LogicalVolume(solid_c3200, fMaterials[3], "logic_c3200");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 341.2500*cm, 335.0000*cm),
        logic_c3200, "phys_c3200", worldLogical, false, 3200, fCheckOverlaps);

    // ---- Cell 3201:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c3201 = new G4Box("solid_c3201",
        200.0000*cm, 18.7500*cm, 15.0000*cm);
    auto* logic_c3201 = new G4LogicalVolume(solid_c3201, fMaterials[3], "logic_c3201");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 221.2500*cm, 335.0000*cm),
        logic_c3201, "phys_c3201", worldLogical, false, 3201, fCheckOverlaps);

    // ---- Cell 32500:  (Mat 2: Air) ----
    auto* solid_c32500 = new G4Box("solid_c32500",
        200.0000*cm, 18.7500*cm, 2225.0000*cm);
    auto* logic_c32500 = new G4LogicalVolume(solid_c32500, fMaterials[2], "logic_c32500");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 221.2500*cm, 2575.0000*cm),
        logic_c32500, "phys_c32500", worldLogical, false, 32500, fCheckOverlaps);

    // ---- Cell 32501:  (Mat 2: Air) ----
    auto* solid_c32501 = new G4Box("solid_c32501",
        200.0000*cm, 101.2500*cm, 2225.0000*cm);
    auto* logic_c32501 = new G4LogicalVolume(solid_c32501, fMaterials[2], "logic_c32501");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 341.2500*cm, 2575.0000*cm),
        logic_c32501, "phys_c32501", worldLogical, false, 32501, fCheckOverlaps);

    // ---- Cell 3251:  (Mat 2: Air) ----
    auto* solid_c3251 = new G4Box("solid_c3251",
        200.0000*cm, 90.0000*cm, 2240.0000*cm);
    auto* logic_c3251 = new G4LogicalVolume(solid_c3251, fMaterials[2], "logic_c3251");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 70.0000*cm, 2560.0000*cm),
        logic_c3251, "phys_c3251", worldLogical, false, 3251, fCheckOverlaps);

    // ---- Cell 3252:  (Mat 2: Air) ----
    auto* solid_c3252 = new G4Box("solid_c3252",
        200.0000*cm, 2178.7500*cm, 2240.0000*cm);
    auto* logic_c3252 = new G4LogicalVolume(solid_c3252, fMaterials[2], "logic_c3252");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 2621.2500*cm, 2560.0000*cm),
        logic_c3252, "phys_c3252", worldLogical, false, 3252, fCheckOverlaps);

    // ---- Cell 3253:  (Mat 2: Air) ----
    auto* solid_c3253 = new G4Box("solid_c3253",
        200.0000*cm, 21.2500*cm, 2240.0000*cm);
    auto* logic_c3253 = new G4LogicalVolume(solid_c3253, fMaterials[2], "logic_c3253");
    new G4PVPlacement(0, G4ThreeVector(160.0000*cm, 181.2500*cm, 2560.0000*cm),
        logic_c3253, "phys_c3253", worldLogical, false, 3253, fCheckOverlaps);

    // ---- Cell 2000: Inner bunker (Mat 2: Air) ----
    auto* solid_c2000_box = new G4Box("solid_c2000_box",
        115.0000*cm, 62.5000*cm, 120.0000*cm);
    auto* solid_c2000_sph0 = new G4Orb("solid_c2000_sph0", 0.1000*cm);
    auto* solid_c2000_b0 = new G4SubtractionSolid("solid_c2000_b0",
        solid_c2000_box, solid_c2000_sph0,
        0, G4ThreeVector(80.0000*cm, 48.5000*cm, 30.7000*cm));
    auto* solid_c2000_sph1 = new G4Orb("solid_c2000_sph1", 0.1900*cm);
    auto* solid_c2000_b1 = new G4SubtractionSolid("solid_c2000_b1",
        solid_c2000_b0, solid_c2000_sph1,
        0, G4ThreeVector(80.0000*cm, 48.5000*cm, 31.0000*cm));
    auto* solid_c2000_sph2 = new G4Orb("solid_c2000_sph2", 0.2500*cm);
    auto* solid_c2000_b2 = new G4SubtractionSolid("solid_c2000_b2",
        solid_c2000_b1, solid_c2000_sph2,
        0, G4ThreeVector(80.0000*cm, 48.5000*cm, 31.7000*cm));
    auto* solid_c2000_sph3 = new G4Orb("solid_c2000_sph3", 0.2500*cm);
    auto* solid_c2000_b3 = new G4SubtractionSolid("solid_c2000_b3",
        solid_c2000_b2, solid_c2000_sph3,
        0, G4ThreeVector(80.0000*cm, 48.5000*cm, 35.0000*cm));
    auto* solid_c2000_sph4 = new G4Orb("solid_c2000_sph4", 0.2500*cm);
    auto* solid_c2000_b4 = new G4SubtractionSolid("solid_c2000_b4",
        solid_c2000_b3, solid_c2000_sph4,
        0, G4ThreeVector(80.0000*cm, 48.5000*cm, 40.0000*cm));
    auto* solid_c2000_sph5 = new G4Orb("solid_c2000_sph5", 5.0000*cm);
    auto* solid_c2000_b5 = new G4SubtractionSolid("solid_c2000_b5",
        solid_c2000_b4, solid_c2000_sph5,
        0, G4ThreeVector(-30.0000*cm, 57.5000*cm, 90.0000*cm));
    auto* solid_c2000 = solid_c2000_b5;
    auto* logic_c2000 = new G4LogicalVolume(solid_c2000, fMaterials[2], "logic_c2000");
    new G4PVPlacement(0, G4ThreeVector(115.0000*cm, 322.5000*cm, 120.0000*cm),
        logic_c2000, "phys_c2000", worldLogical, false, 2000, fCheckOverlaps);

    // ---- Cell 2060:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c2060_box = new G4Box("solid_c2060_box",
        20.0000*cm, 72.5000*cm, 120.0000*cm);
    auto* solid_c2060_sph0 = new G4Orb("solid_c2060_sph0", 4.9000*cm);
    auto* solid_c2060_b0 = new G4SubtractionSolid("solid_c2060_b0",
        solid_c2060_box, solid_c2060_sph0,
        0, G4ThreeVector(-15.0000*cm, 58.5000*cm, 30.0000*cm));
    auto* solid_c2060_sph1 = new G4Orb("solid_c2060_sph1", 4.9000*cm);
    auto* solid_c2060_b1 = new G4SubtractionSolid("solid_c2060_b1",
        solid_c2060_b0, solid_c2060_sph1,
        0, G4ThreeVector(-5.0000*cm, 58.5000*cm, 30.0000*cm));
    auto* solid_c2060_sph2 = new G4Orb("solid_c2060_sph2", 4.9000*cm);
    auto* solid_c2060_b2 = new G4SubtractionSolid("solid_c2060_b2",
        solid_c2060_b1, solid_c2060_sph2,
        0, G4ThreeVector(5.0000*cm, 58.5000*cm, 30.0000*cm));
    auto* solid_c2060_sph3 = new G4Orb("solid_c2060_sph3", 4.9000*cm);
    auto* solid_c2060_b3 = new G4SubtractionSolid("solid_c2060_b3",
        solid_c2060_b2, solid_c2060_sph3,
        0, G4ThreeVector(15.0000*cm, 58.5000*cm, 30.0000*cm));
    auto* solid_c2060 = solid_c2060_b3;
    auto* logic_c2060 = new G4LogicalVolume(solid_c2060, fMaterials[7], "logic_c2060");
    new G4PVPlacement(0, G4ThreeVector(250.0000*cm, 312.5000*cm, 120.0000*cm),
        logic_c2060, "phys_c2060", worldLogical, false, 2060, fCheckOverlaps);

    // ---- Cell 2061: Concrete plug 1 (Mat 7: MagnetiteConcrete) ----
    auto* solid_c2061 = new G4Orb("solid_c2061", 4.9000*cm);
    auto* logic_c2061 = new G4LogicalVolume(solid_c2061, fMaterials[7], "logic_c2061");
    new G4PVPlacement(0, G4ThreeVector(235.0000*cm, 371.0000*cm, 150.0000*cm),
        logic_c2061, "phys_c2061", worldLogical, false, 2061, fCheckOverlaps);

    // ---- Cell 2062: Concrete plug 2 (Mat 7: MagnetiteConcrete) ----
    auto* solid_c2062 = new G4Orb("solid_c2062", 4.9000*cm);
    auto* logic_c2062 = new G4LogicalVolume(solid_c2062, fMaterials[7], "logic_c2062");
    new G4PVPlacement(0, G4ThreeVector(245.0000*cm, 371.0000*cm, 150.0000*cm),
        logic_c2062, "phys_c2062", worldLogical, false, 2062, fCheckOverlaps);

    // ---- Cell 2063: Concrete plug 3 (Mat 7: MagnetiteConcrete) ----
    auto* solid_c2063 = new G4Orb("solid_c2063", 4.9000*cm);
    auto* logic_c2063 = new G4LogicalVolume(solid_c2063, fMaterials[7], "logic_c2063");
    new G4PVPlacement(0, G4ThreeVector(255.0000*cm, 371.0000*cm, 150.0000*cm),
        logic_c2063, "phys_c2063", worldLogical, false, 2063, fCheckOverlaps);

    // ---- Cell 2064: Concrete plug 4 (Mat 7: MagnetiteConcrete) ----
    auto* solid_c2064 = new G4Orb("solid_c2064", 4.9000*cm);
    auto* logic_c2064 = new G4LogicalVolume(solid_c2064, fMaterials[7], "logic_c2064");
    new G4PVPlacement(0, G4ThreeVector(265.0000*cm, 371.0000*cm, 150.0000*cm),
        logic_c2064, "phys_c2064", worldLogical, false, 2064, fCheckOverlaps);

    // ---- Cell 2100: Experimetn area (second next to wall) (Mat 2: Air) ----
    auto* solid_c2100 = new G4Box("solid_c2100",
        100.0000*cm, 10.0000*cm, 120.0000*cm);
    auto* logic_c2100 = new G4LogicalVolume(solid_c2100, fMaterials[2], "logic_c2100");
    new G4PVPlacement(0, G4ThreeVector(180.0000*cm, 435.0000*cm, 120.0000*cm),
        logic_c2100, "phys_c2100", worldLogical, false, 2100, fCheckOverlaps);

    // ---- Cell 2200: Western experimental area (Mat 2: Air) ----
    auto* solid_c2200_box = new G4Box("solid_c2200_box",
        140.0000*cm, 57.5000*cm, 120.0000*cm);
    auto* solid_c2200_sph0 = new G4Orb("solid_c2200_sph0", 5.0000*cm);
    auto* solid_c2200_b0 = new G4SubtractionSolid("solid_c2200_b0",
        solid_c2200_box, solid_c2200_sph0,
        0, G4ThreeVector(-55.0000*cm, -122.5000*cm, 90.0000*cm));
    auto* solid_c2200_sph1 = new G4Orb("solid_c2200_sph1", 1.5000*cm);
    auto* solid_c2200_b1 = new G4SubtractionSolid("solid_c2200_b1",
        solid_c2200_b0, solid_c2200_sph1,
        0, G4ThreeVector(55.0000*cm, 30.5000*cm, 30.0000*cm));
    auto* solid_c2200_sph2 = new G4Orb("solid_c2200_sph2", 1.5000*cm);
    auto* solid_c2200_b2 = new G4SubtractionSolid("solid_c2200_b2",
        solid_c2200_b1, solid_c2200_sph2,
        0, G4ThreeVector(5.0000*cm, 30.5000*cm, 30.0000*cm));
    auto* solid_c2200 = solid_c2200_b2;
    auto* logic_c2200 = new G4LogicalVolume(solid_c2200, fMaterials[2], "logic_c2200");
    new G4PVPlacement(0, G4ThreeVector(140.0000*cm, 502.5000*cm, 120.0000*cm),
        logic_c2200, "phys_c2200", worldLogical, false, 2200, fCheckOverlaps);

    // ---- Cell 2205: Eastern experimental area (SET TO ZERO AFTER 1 STEP IN EASTERN VARIANCE REDUCTION) (Mat 2: Air) ----
    auto* solid_c2205 = new G4Box("solid_c2205",
        140.0000*cm, 30.2500*cm, 120.0000*cm);
    auto* logic_c2205 = new G4LogicalVolume(solid_c2205, fMaterials[2], "logic_c2205");
    new G4PVPlacement(0, G4ThreeVector(140.0000*cm, 594.7500*cm, 120.0000*cm),
        logic_c2205, "phys_c2205", worldLogical, false, 2205, fCheckOverlaps);

    // ---- Cell 2206:  (Mat 2: Air) ----
    auto* solid_c2206_box = new G4Box("solid_c2206_box",
        140.0000*cm, 2.2500*cm, 120.0000*cm);
    auto* solid_c2206_cyl0 = new G4Tubs("solid_c2206_cyl0",
        0., 2.3000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2206_0 = new G4RotationMatrix();
    rot_c2206_0->rotateX(90.*deg);
    auto* solid_c2206_b0 = new G4SubtractionSolid("solid_c2206_b0",
        solid_c2206_box, solid_c2206_cyl0,
        rot_c2206_0, G4ThreeVector(45.0000*cm, 0.0000*cm, 30.0000*cm));
    auto* solid_c2206 = solid_c2206_b0;
    auto* logic_c2206 = new G4LogicalVolume(solid_c2206, fMaterials[2], "logic_c2206");
    new G4PVPlacement(0, G4ThreeVector(140.0000*cm, 562.2500*cm, 120.0000*cm),
        logic_c2206, "phys_c2206", worldLogical, false, 2206, fCheckOverlaps);

    // ---- Cell 2207: D1 detector (Mat 2: Air) ----
    auto* solid_c2207_box = new G4Box("solid_c2207_box",
        4800.0000*cm, 2.2500*cm, 4800.0000*cm);
    auto* solid_c2207_cyl0 = new G4Tubs("solid_c2207_cyl0",
        0., 2.3000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2207_0 = new G4RotationMatrix();
    rot_c2207_0->rotateX(90.*deg);
    auto* solid_c2207_b0 = new G4IntersectionSolid("solid_c2207_b0",
        solid_c2207_box, solid_c2207_cyl0,
        rot_c2207_0, G4ThreeVector(185.0000*cm, 0.0000*cm, 150.0000*cm));
    auto* solid_c2207 = solid_c2207_b0;
    auto* logic_c2207 = new G4LogicalVolume(solid_c2207, fMaterials[2], "logic_c2207");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 562.2500*cm, 0.0000*cm),
        logic_c2207, "phys_c2207", worldLogical, false, 2207, fCheckOverlaps);

    // ---- Cell 2215: Lead shield on labyrinth wall (Mat 2: Air) ----
    auto* solid_c2215 = new G4Box("solid_c2215",
        2.5000*cm, 7.5000*cm, 120.0000*cm);
    auto* logic_c2215 = new G4LogicalVolume(solid_c2215, fMaterials[2], "logic_c2215");
    new G4PVPlacement(0, G4ThreeVector(102.5000*cm, 632.5000*cm, 120.0000*cm),
        logic_c2215, "phys_c2215", worldLogical, false, 2215, fCheckOverlaps);

    // ---- Cell 2216: Experiment area outside inner bunker (Mat 2: Air) ----
    auto* solid_c2216_box = new G4Box("solid_c2216_box",
        87.5000*cm, 7.5000*cm, 120.0000*cm);
    auto* solid_c2216_sph0 = new G4Orb("solid_c2216_sph0", 5.0000*cm);
    auto* solid_c2216_b0 = new G4SubtractionSolid("solid_c2216_b0",
        solid_c2216_box, solid_c2216_sph0,
        0, G4ThreeVector(2.5000*cm, 2.5000*cm, 30.0000*cm));
    auto* solid_c2216 = solid_c2216_b0;
    auto* logic_c2216 = new G4LogicalVolume(solid_c2216, fMaterials[2], "logic_c2216");
    new G4PVPlacement(0, G4ThreeVector(192.5000*cm, 632.5000*cm, 120.0000*cm),
        logic_c2216, "phys_c2216", worldLogical, false, 2216, fCheckOverlaps);

    // ---- Cell 2219: First door next to labyrinth (Mat 2: Air) ----
    auto* solid_c2219 = new G4Box("solid_c2219",
        50.0000*cm, 0.2500*cm, 102.5000*cm);
    auto* logic_c2219 = new G4LogicalVolume(solid_c2219, fMaterials[2], "logic_c2219");
    new G4PVPlacement(0, G4ThreeVector(50.0000*cm, 639.7500*cm, 102.5000*cm),
        logic_c2219, "phys_c2219", worldLogical, false, 2219, fCheckOverlaps);

    // ---- Cell 2220: First door next to labyrinth (Mat 53: BoratedParaffin) ----
    auto* solid_c2220 = new G4Box("solid_c2220",
        49.7500*cm, 4.0000*cm, 102.2500*cm);
    auto* logic_c2220 = new G4LogicalVolume(solid_c2220, fMaterials[53], "logic_c2220");
    new G4PVPlacement(0, G4ThreeVector(50.2500*cm, 635.5000*cm, 102.7500*cm),
        logic_c2220, "phys_c2220", worldLogical, false, 2220, fCheckOverlaps);

    // ---- Cell 2221: First door next to labyrinth (Mat 2: Air) ----
    auto* solid_c2221 = new G4Box("solid_c2221",
        0.2500*cm, 4.0000*cm, 102.5000*cm);
    auto* logic_c2221 = new G4LogicalVolume(solid_c2221, fMaterials[2], "logic_c2221");
    new G4PVPlacement(0, G4ThreeVector(0.2500*cm, 635.5000*cm, 102.5000*cm),
        logic_c2221, "phys_c2221", worldLogical, false, 2221, fCheckOverlaps);

    // ---- Cell 2222: First door next to labyrinth (Mat 2: Air) ----
    auto* solid_c2222 = new G4Box("solid_c2222",
        49.7500*cm, 4.0000*cm, 0.2500*cm);
    auto* logic_c2222 = new G4LogicalVolume(solid_c2222, fMaterials[2], "logic_c2222");
    new G4PVPlacement(0, G4ThreeVector(50.2500*cm, 635.5000*cm, 0.2500*cm),
        logic_c2222, "phys_c2222", worldLogical, false, 2222, fCheckOverlaps);

    // ---- Cell 2225: First door next to labyrinth (Mat 2: Air) ----
    auto* solid_c2225 = new G4Box("solid_c2225",
        50.0000*cm, 3.2500*cm, 102.5000*cm);
    auto* logic_c2225 = new G4LogicalVolume(solid_c2225, fMaterials[2], "logic_c2225");
    new G4PVPlacement(0, G4ThreeVector(50.0000*cm, 628.2500*cm, 102.5000*cm),
        logic_c2225, "phys_c2225", worldLogical, false, 2225, fCheckOverlaps);

    // ---- Cell 2230: Experimetn area (next to c wall, D2 North) (Mat 2: Air) ----
    auto* solid_c2230 = new G4Box("solid_c2230",
        38.0000*cm, 7.5000*cm, 17.5000*cm);
    auto* logic_c2230 = new G4LogicalVolume(solid_c2230, fMaterials[2], "logic_c2230");
    new G4PVPlacement(0, G4ThreeVector(62.0000*cm, 632.5000*cm, 222.5000*cm),
        logic_c2230, "phys_c2230", worldLogical, false, 2230, fCheckOverlaps);

    // ---- Cell 2231: Experimetn area (next to wall, D2 South) (Mat 2: Air) ----
    auto* solid_c2231 = new G4Box("solid_c2231",
        12.0000*cm, 7.5000*cm, 17.5000*cm);
    auto* logic_c2231 = new G4LogicalVolume(solid_c2231, fMaterials[2], "logic_c2231");
    new G4PVPlacement(0, G4ThreeVector(12.0000*cm, 632.5000*cm, 222.5000*cm),
        logic_c2231, "phys_c2231", worldLogical, false, 2231, fCheckOverlaps);

    // ---- Cell 2250: Plastic door next to bunker (Mat 2: Air) ----
    auto* solid_c2250 = new G4Box("solid_c2250",
        40.0000*cm, 10.0000*cm, 114.0000*cm);
    auto* logic_c2250 = new G4LogicalVolume(solid_c2250, fMaterials[2], "logic_c2250");
    new G4PVPlacement(0, G4ThreeVector(40.0000*cm, 435.0000*cm, 114.0000*cm),
        logic_c2250, "phys_c2250", worldLogical, false, 2250, fCheckOverlaps);

    // ---- Cell 2255: Plastic door next to bunker (Mat 5: Polyethylene) ----
    auto* solid_c2255 = new G4Box("solid_c2255",
        28.0000*cm, 10.0000*cm, 6.0000*cm);
    auto* logic_c2255 = new G4LogicalVolume(solid_c2255, fMaterials[5], "logic_c2255");
    new G4PVPlacement(0, G4ThreeVector(52.0000*cm, 435.0000*cm, 234.0000*cm),
        logic_c2255, "phys_c2255", worldLogical, false, 2255, fCheckOverlaps);

    // ---- Cell 2256: Plastic door next to bunker (Mat 2: Air) ----
    auto* solid_c2256 = new G4Box("solid_c2256",
        12.0000*cm, 10.0000*cm, 6.0000*cm);
    auto* logic_c2256 = new G4LogicalVolume(solid_c2256, fMaterials[2], "logic_c2256");
    new G4PVPlacement(0, G4ThreeVector(12.0000*cm, 435.0000*cm, 234.0000*cm),
        logic_c2256, "phys_c2256", worldLogical, false, 2256, fCheckOverlaps);

    // ---- Cell 2260:  (Mat 7: MagnetiteConcrete) ----
    auto* solid_c2260 = new G4Box("solid_c2260",
        50.0000*cm, 20.0000*cm, 40.0000*cm);
    auto* logic_c2260 = new G4LogicalVolume(solid_c2260, fMaterials[7], "logic_c2260");
    new G4PVPlacement(0, G4ThreeVector(130.0000*cm, 405.0000*cm, 190.0000*cm),
        logic_c2260, "phys_c2260", worldLogical, false, 2260, fCheckOverlaps);

    // ---- Cell 2265:  (Mat 11: Iron) ----
    auto* solid_c2265 = new G4Box("solid_c2265",
        50.0000*cm, 20.0000*cm, 75.0000*cm);
    auto* logic_c2265 = new G4LogicalVolume(solid_c2265, fMaterials[11], "logic_c2265");
    new G4PVPlacement(0, G4ThreeVector(130.0000*cm, 405.0000*cm, 75.0000*cm),
        logic_c2265, "phys_c2265", worldLogical, false, 2265, fCheckOverlaps);

    // ---- Cell 2266:  (Mat 3: OrdinaryConcrete) ----
    auto* solid_c2266 = new G4Box("solid_c2266",
        50.0000*cm, 20.0000*cm, 5.0000*cm);
    auto* logic_c2266 = new G4LogicalVolume(solid_c2266, fMaterials[3], "logic_c2266");
    new G4PVPlacement(0, G4ThreeVector(130.0000*cm, 405.0000*cm, 235.0000*cm),
        logic_c2266, "phys_c2266", worldLogical, false, 2266, fCheckOverlaps);

    // ---- Cell 2299: Doorway from inner bunker to outer bunker (Mat 2: Air) ----
    auto* solid_c2299 = new G4Box("solid_c2299",
        40.0000*cm, 20.0000*cm, 120.0000*cm);
    auto* logic_c2299 = new G4LogicalVolume(solid_c2299, fMaterials[2], "logic_c2299");
    new G4PVPlacement(0, G4ThreeVector(40.0000*cm, 405.0000*cm, 120.0000*cm),
        logic_c2299, "phys_c2299", worldLogical, false, 2299, fCheckOverlaps);

    // ---- Cell 2310:  (Mat 11: Iron) ----
    auto* solid_c2310_box = new G4Box("solid_c2310_box",
        50.0000*cm, 20.0000*cm, 120.0000*cm);
    auto* solid_c2310_cyl0 = new G4Tubs("solid_c2310_cyl0",
        0., 10.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2310_0 = new G4RotationMatrix();
    rot_c2310_0->rotateX(90.*deg);
    auto* solid_c2310_b0 = new G4SubtractionSolid("solid_c2310_b0",
        solid_c2310_box, solid_c2310_cyl0,
        rot_c2310_0, G4ThreeVector(-35.0000*cm, 0.0000*cm, 30.0000*cm));
    auto* solid_c2310 = solid_c2310_b0;
    auto* logic_c2310 = new G4LogicalVolume(solid_c2310, fMaterials[11], "logic_c2310");
    new G4PVPlacement(0, G4ThreeVector(230.0000*cm, 405.0000*cm, 120.0000*cm),
        logic_c2310, "phys_c2310", worldLogical, false, 2310, fCheckOverlaps);

    // ---- Cell 2350:  (Mat 2: Air) ----
    auto* solid_c2350_box = new G4Box("solid_c2350_box",
        4800.0000*cm, 20.0000*cm, 4800.0000*cm);
    auto* solid_c2350_sph0 = new G4Orb("solid_c2350_sph0", 5.0000*cm);
    auto* solid_c2350_b0 = new G4SubtractionSolid("solid_c2350_b0",
        solid_c2350_box, solid_c2350_sph0,
        0, G4ThreeVector(195.0000*cm, -15.0000*cm, 150.0000*cm));
    auto* solid_c2350_sph1 = new G4Orb("solid_c2350_sph1", 5.0000*cm);
    auto* solid_c2350_b1 = new G4SubtractionSolid("solid_c2350_b1",
        solid_c2350_b0, solid_c2350_sph1,
        0, G4ThreeVector(195.0000*cm, 15.0000*cm, 150.0000*cm));
    auto* solid_c2350_cyl2 = new G4Tubs("solid_c2350_cyl2",
        0., 10.0000*cm, 10000.0*cm, 0., 360.*deg);
    auto* rot_c2350_2 = new G4RotationMatrix();
    rot_c2350_2->rotateX(90.*deg);
    auto* solid_c2350_b2 = new G4IntersectionSolid("solid_c2350_b2",
        solid_c2350_b1, solid_c2350_cyl2,
        rot_c2350_2, G4ThreeVector(195.0000*cm, 0.0000*cm, 150.0000*cm));
    auto* solid_c2350 = solid_c2350_b2;
    auto* logic_c2350 = new G4LogicalVolume(solid_c2350, fMaterials[2], "logic_c2350");
    new G4PVPlacement(0, G4ThreeVector(0.0000*cm, 405.0000*cm, 0.0000*cm),
        logic_c2350, "phys_c2350", worldLogical, false, 2350, fCheckOverlaps);

    // ---- Cell 2400:  (Mat 2: Air) ----
    auto* solid_c2400 = new G4Box("solid_c2400",
        5.0000*cm, 1.2500*cm, 120.0000*cm);
    auto* logic_c2400 = new G4LogicalVolume(solid_c2400, fMaterials[2], "logic_c2400");
    new G4PVPlacement(0, G4ThreeVector(275.0000*cm, 241.2500*cm, 120.0000*cm),
        logic_c2400, "phys_c2400", worldLogical, false, 2400, fCheckOverlaps);

    // ---- Cell 2410:  (Mat 2: Air) ----
    auto* solid_c2410 = new G4Box("solid_c2410",
        5.0000*cm, 1.2500*cm, 120.0000*cm);
    auto* logic_c2410 = new G4LogicalVolume(solid_c2410, fMaterials[2], "logic_c2410");
    new G4PVPlacement(0, G4ThreeVector(275.0000*cm, 383.7500*cm, 120.0000*cm),
        logic_c2410, "phys_c2410", worldLogical, false, 2410, fCheckOverlaps);

    // ---- Cell 2420:  (Mat 2: Air) ----
    auto* solid_c2420 = new G4Box("solid_c2420",
        5.0000*cm, 70.0000*cm, 1.2500*cm);
    auto* logic_c2420 = new G4LogicalVolume(solid_c2420, fMaterials[2], "logic_c2420");
    new G4PVPlacement(0, G4ThreeVector(275.0000*cm, 312.5000*cm, 238.7500*cm),
        logic_c2420, "phys_c2420", worldLogical, false, 2420, fCheckOverlaps);

    // ---- Cell 2430:  (Mat 12: Lead) ----
    auto* solid_c2430 = new G4Box("solid_c2430",
        5.0000*cm, 70.0000*cm, 118.7500*cm);
    auto* logic_c2430 = new G4LogicalVolume(solid_c2430, fMaterials[12], "logic_c2430");
    new G4PVPlacement(0, G4ThreeVector(275.0000*cm, 312.5000*cm, 118.7500*cm),
        logic_c2430, "phys_c2430", worldLogical, false, 2430, fCheckOverlaps);

    // ---- Cell 6805:  (Mat 13: Soil) ----
    auto* solid_c6805 = new G4Box("solid_c6805",
        2160.0000*cm, 4800.0000*cm, 2400.0000*cm);
    auto* logic_c6805 = new G4LogicalVolume(solid_c6805, fMaterials[13], "logic_c6805");
    new G4PVPlacement(0, G4ThreeVector(2640.0000*cm, 0.0000*cm, -2400.0000*cm),
        logic_c6805, "phys_c6805", worldLogical, false, 6805, fCheckOverlaps);

    // ---- Cell 8000: CUP irradiation position (Mat 2: Air) ----
    auto* solid_c8000 = new G4Orb("solid_c8000", 0.1000*cm);
    auto* logic_c8000 = new G4LogicalVolume(solid_c8000, fMaterials[2], "logic_c8000");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 371.0000*cm, 150.7000*cm),
        logic_c8000, "phys_c8000", worldLogical, false, 8000, fCheckOverlaps);

    // ---- Cell 8001: CUP +0.3cm (Mat 2: Air) ----
    auto* solid_c8001 = new G4Orb("solid_c8001", 0.1900*cm);
    auto* logic_c8001 = new G4LogicalVolume(solid_c8001, fMaterials[2], "logic_c8001");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 371.0000*cm, 151.0000*cm),
        logic_c8001, "phys_c8001", worldLogical, false, 8001, fCheckOverlaps);

    // ---- Cell 8002: CUP +1cm (Mat 2: Air) ----
    auto* solid_c8002 = new G4Orb("solid_c8002", 0.2500*cm);
    auto* logic_c8002 = new G4LogicalVolume(solid_c8002, fMaterials[2], "logic_c8002");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 371.0000*cm, 151.7000*cm),
        logic_c8002, "phys_c8002", worldLogical, false, 8002, fCheckOverlaps);

    // ---- Cell 8003: CUP +4.3cm (Mat 2: Air) ----
    auto* solid_c8003 = new G4Orb("solid_c8003", 0.2500*cm);
    auto* logic_c8003 = new G4LogicalVolume(solid_c8003, fMaterials[2], "logic_c8003");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 371.0000*cm, 155.0000*cm),
        logic_c8003, "phys_c8003", worldLogical, false, 8003, fCheckOverlaps);

    // ---- Cell 8004: CUP +9.3cm (Mat 2: Air) ----
    auto* solid_c8004 = new G4Orb("solid_c8004", 0.2500*cm);
    auto* logic_c8004 = new G4LogicalVolume(solid_c8004, fMaterials[2], "logic_c8004");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 371.0000*cm, 160.0000*cm),
        logic_c8004, "phys_c8004", worldLogical, false, 8004, fCheckOverlaps);

    // ---- Cell 8100: Collimator Entrance (Mat 2: Air) ----
    auto* solid_c8100 = new G4Orb("solid_c8100", 5.0000*cm);
    auto* logic_c8100 = new G4LogicalVolume(solid_c8100, fMaterials[2], "logic_c8100");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 390.0000*cm, 150.0000*cm),
        logic_c8100, "phys_c8100", worldLogical, false, 8100, fCheckOverlaps);

    // ---- Cell 8200: Collimator Exit (Mat 2: Air) ----
    auto* solid_c8200 = new G4Orb("solid_c8200", 5.0000*cm);
    auto* logic_c8200 = new G4LogicalVolume(solid_c8200, fMaterials[2], "logic_c8200");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 420.0000*cm, 150.0000*cm),
        logic_c8200, "phys_c8200", worldLogical, false, 8200, fCheckOverlaps);

    // ---- Cell 8300: Outside labyrinth (Mat 2: Air) ----
    auto* solid_c8300 = new G4Orb("solid_c8300", 5.0000*cm);
    auto* logic_c8300 = new G4LogicalVolume(solid_c8300, fMaterials[2], "logic_c8300");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 635.0000*cm, 150.0000*cm),
        logic_c8300, "phys_c8300", worldLogical, false, 8300, fCheckOverlaps);

    // ---- Cell 8400: Fission chamber (Mat 2: Air) ----
    auto* solid_c8400 = new G4Orb("solid_c8400", 5.0000*cm);
    auto* logic_c8400 = new G4LogicalVolume(solid_c8400, fMaterials[2], "logic_c8400");
    new G4PVPlacement(0, G4ThreeVector(85.0000*cm, 380.0000*cm, 210.0000*cm),
        logic_c8400, "phys_c8400", worldLogical, false, 8400, fCheckOverlaps);

    // ---- Cell 8500: HVS (Mat 2: Air) ----
    auto* solid_c8500 = new G4Orb("solid_c8500", 1.5000*cm);
    auto* logic_c8500 = new G4LogicalVolume(solid_c8500, fMaterials[2], "logic_c8500");
    new G4PVPlacement(0, G4ThreeVector(195.0000*cm, 533.0000*cm, 150.0000*cm),
        logic_c8500, "phys_c8500", worldLogical, false, 8500, fCheckOverlaps);

    // ---- Cell 8600: 20cm outside beam next to HVS (Mat 2: Air) ----
    auto* solid_c8600 = new G4Orb("solid_c8600", 1.5000*cm);
    auto* logic_c8600 = new G4LogicalVolume(solid_c8600, fMaterials[2], "logic_c8600");
    new G4PVPlacement(0, G4ThreeVector(145.0000*cm, 533.0000*cm, 150.0000*cm),
        logic_c8600, "phys_c8600", worldLogical, false, 8600, fCheckOverlaps);

}

void NESSADetectorConstruction::ApplyVisAttributes()
{
    // Color scheme: unique color per geometry REGION (not just material)
    // This lets you distinguish walls, floors, roofs etc.
    
    auto* airVis = new G4VisAttributes(G4VisAttributes::GetInvisible());
    
    // Magnetite concrete regions - different shades
    auto* wallVis    = new G4VisAttributes(G4Colour(0.7, 0.35, 0.1, 0.5));  // brown walls
    auto* roofVis    = new G4VisAttributes(G4Colour(0.55, 0.27, 0.07, 0.4)); // dark brown roof
    auto* backWallVis= new G4VisAttributes(G4Colour(0.8, 0.4, 0.0, 0.5));   // orange back wall
    auto* labWallVis = new G4VisAttributes(G4Colour(0.6, 0.2, 0.0, 0.5));   // red-brown labyrinth
    
    // Ordinary concrete - blue-grey shades
    auto* floorVis   = new G4VisAttributes(G4Colour(0.5, 0.5, 0.6, 0.4));   // blue-grey floor
    auto* ordConcVis = new G4VisAttributes(G4Colour(0.6, 0.6, 0.65, 0.3));  // light grey
    
    // Special materials
    auto* polyVis    = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.6));   // bright yellow
    auto* ironVis    = new G4VisAttributes(G4Colour(0.3, 0.3, 0.35, 0.7));  // dark steel
    auto* leadVis    = new G4VisAttributes(G4Colour(0.1, 0.1, 0.5, 0.7));   // dark blue
    auto* soilVis    = new G4VisAttributes(G4Colour(0.4, 0.25, 0.1, 0.3));  // earth
    auto* borParVis  = new G4VisAttributes(G4Colour(0.0, 0.8, 0.2, 0.6));   // green
    auto* ssVis      = new G4VisAttributes(G4Colour(0.9, 0.9, 0.95, 0.7));  // shiny silver
    
    // Detector spheres
    auto* detVis     = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.9));   // bright red
    detVis->SetForceSolid(true);
    
    auto* lvStore = G4LogicalVolumeStore::GetInstance();
    for (auto* lv : *lvStore) {
        G4String name = lv->GetName();
        G4Material* mat = lv->GetMaterial();
        G4String matName = mat ? mat->GetName() : "";
        
        if (name == "World") {
            lv->SetVisAttributes(G4VisAttributes::GetInvisible());
            continue;
        }
        
        // Detector volumes in red
        if (name.find("logic_c8") != std::string::npos ||
            name.find("score_") != std::string::npos) {
            lv->SetVisAttributes(detVis);
            continue;
        }
        
        // Air → invisible
        if (matName == "Air") {
            lv->SetVisAttributes(airVis);
            continue;
        }
        
        // Region-based coloring by cell number
        // Extract cell number from name "logic_cXXXX"
        G4int cellNum = 0;
        if (name.substr(0, 7) == "logic_c") {
            try { cellNum = std::stoi(name.substr(7)); } catch(...) {}
        }
        
        if (matName == "MagnetiteConcrete") {
            if (cellNum >= 1300 && cellNum < 1400) lv->SetVisAttributes(wallVis);      // walls
            else if (cellNum >= 1500 && cellNum < 1600) lv->SetVisAttributes(roofVis);  // roof
            else if (cellNum >= 1400 && cellNum < 1500) lv->SetVisAttributes(backWallVis); // back
            else if (cellNum >= 2000 && cellNum < 2100) lv->SetVisAttributes(labWallVis);  // labyrinth
            else if (cellNum >= 3000 && cellNum < 4000) lv->SetVisAttributes(wallVis);
            else lv->SetVisAttributes(wallVis);
        }
        else if (matName == "OrdinaryConcrete") {
            if (cellNum >= 1200 && cellNum < 1300) lv->SetVisAttributes(floorVis);
            else lv->SetVisAttributes(ordConcVis);
        }
        else if (matName == "Polyethylene")    lv->SetVisAttributes(polyVis);
        else if (matName == "Iron")            lv->SetVisAttributes(ironVis);
        else if (matName == "Lead")            lv->SetVisAttributes(leadVis);
        else if (matName == "Soil")            lv->SetVisAttributes(soilVis);
        else if (matName == "BoratedParaffin") lv->SetVisAttributes(borParVis);
        else if (matName == "SS304")           lv->SetVisAttributes(ssVis);
    }
}

void NESSADetectorConstruction::ConstructSDandField()
{
    auto* scoringSD = new NESSAScoringSD("ScoringSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(scoringSD);
    
    const auto& pts = NESSAScoringConfig::Instance().GetPoints();
    
    for (G4int i = 0; i < (G4int)pts.size(); i++) {
        const auto& pt = pts[i];
        if (!pt.active) continue;
        
        if (pt.mcnpCell > 0) {
            // Attach to existing MCNP cell volume
            G4String logName = "logic_c" + std::to_string(pt.mcnpCell);
            auto* store = G4LogicalVolumeStore::GetInstance();
            for (auto* lv : *store) {
                if (lv->GetName() == logName) {
                    lv->SetSensitiveDetector(scoringSD);
                    G4cout << "SD: " << pt.name << " -> " << logName << G4endl;
                    break;
                }
            }
        } else {
            // Create new scoring sphere
            auto* solid = new G4Orb("score_" + pt.name, pt.radius*cm);
            auto* lv = new G4LogicalVolume(solid, fMaterials[2], "score_" + pt.name);
            lv->SetSensitiveDetector(scoringSD);
            
            auto* detVis = new G4VisAttributes(G4Colour(1, 0, 0, 0.9));
            detVis->SetForceSolid(true);
            lv->SetVisAttributes(detVis);
            
            new G4PVPlacement(0,
                G4ThreeVector(pt.x*cm, pt.y*cm, pt.z*cm),
                lv, "phys_score_" + pt.name,
                fWorldLogical, false, 90000 + i, false);
            
            G4cout << "SD: Created " << pt.name
                   << " at (" << pt.x << "," << pt.y << "," << pt.z << ") r="
                   << pt.radius << " cm" << G4endl;
        }
    }
}
