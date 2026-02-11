# NESSA Neutron Beamline — Geant4 Simulation

**Converted from PHITS 3.35 input with importance biasing**  
Uppsala University · Division of Applied Nuclear Physics  
NESSA (NEutron Source in UppSAla) · FREIA Hall Bunker

---

## Overview

This is a complete Geant4 simulation of the NESSA 14 MeV D-T neutron generator facility, translated from the PHITS Monte Carlo input file. It models:

- **Concrete bunker** with layered walls (left, right, back)
- **Stainless steel-lined collimator** (10 cm radius aperture, 40 cm length)
- **Shielding**: lead, polyethylene, borated polyethylene blocks
- **Aluminum source generator housing**
- **22 detector positions** along the beamline for neutron spectra measurement
- **14 MeV D-T neutron source** (Gaussian energy, isotropic emission)

## File Structure

```
NESSA_Geant4/
├── CMakeLists.txt              # Build system
├── nessa_sim.cc                # Main program
├── build_and_run.sh            # Build/run helper script
├── analyze_spectra.py          # Post-processing (Python)
├── include/
│   ├── NESSADetectorConstruction.hh
│   ├── NESSAPhysicsList.hh
│   ├── NESSAActionInitialization.hh
│   ├── NESSAPrimaryGeneratorAction.hh
│   ├── NESSARunAction.hh
│   ├── NESSAEventAction.hh
│   ├── NESSANeutronHit.hh
│   └── NESSANeutronSD.hh
├── src/
│   ├── NESSADetectorConstruction.cc   # Full bunker geometry
│   ├── NESSAPhysicsList.cc            # QGSP_BIC_HP + thermal
│   ├── NESSAActionInitialization.cc
│   ├── NESSAPrimaryGeneratorAction.cc # GPS-based source
│   ├── NESSARunAction.cc              # Histogram booking
│   ├── NESSAEventAction.cc            # Track-length scoring
│   ├── NESSANeutronHit.cc
│   └── NESSANeutronSD.cc
└── macros/
    ├── run.mac                 # Batch execution
    ├── gps_source.mac          # Source definition (editable)
    ├── vis.mac                 # Visualization settings
    └── init_vis.mac            # Interactive initialization
```

## Prerequisites

1. **Geant4 11.x** compiled with multithreading and visualization
2. **G4NDL** neutron data library (essential for HP physics below 20 MeV)
3. **CMake ≥ 3.16**
4. **Python 3** with numpy and matplotlib (for post-processing)

Ensure your Geant4 environment is sourced:
```bash
source /path/to/geant4-install/bin/geant4.sh
```

## Building

```bash
chmod +x build_and_run.sh
./build_and_run.sh build
```

Or manually:
```bash
mkdir build && cd build
cmake .. -DWITH_GEANT4_UIVIS=ON
make -j$(nproc)
```

## Running

### Batch mode (production)
```bash
cd build
./nessa_sim macros/run.mac
```

### Interactive mode (visualization)
```bash
cd build
./nessa_sim
```

### Quick test
Edit `macros/run.mac` and change `/run/beamOn 1000000` to `/run/beamOn 10000`.

## Source Configuration

The D-T neutron source is defined entirely in `macros/gps_source.mac` using the General Particle Source (GPS). **No recompilation needed to change source parameters.**

### PHITS → Geant4 GPS mapping:

| PHITS Parameter | Value | GPS Command |
|---|---|---|
| `proj = neutron` | neutron | `/gps/particle neutron` |
| `s-type = 1` (cylinder) | flat disk | `/gps/pos/type Plane` + `/gps/pos/shape Circle` |
| `x0,y0,z0 = 60,-140,0` | cm | `/gps/pos/centre 60 -140 0 cm` |
| `r0 = 1.0` | 1 cm radius | `/gps/pos/radius 1.0 cm` |
| `dir = all` | isotropic | `/gps/ang/type iso` |
| `e-type = 2` (Gauss) | E₀=14 MeV | `/gps/ene/type Gauss` + `/gps/ene/mono 14.0 MeV` |
| `eg1 = 0.050` (FWHM) | σ = FWHM/2.355 | `/gps/ene/sigma 0.02123 MeV` |
| `eg2,eg3 = 13.8,14.7` | bounds | `/gps/ene/min 13.8 MeV` + `/gps/ene/max 14.7 MeV` |

### Modifying the source

To change to a monoenergetic 14 MeV pencil beam:
```
/gps/particle neutron
/gps/pos/type Point
/gps/pos/centre 60.0 -140.0 0.0 cm
/gps/ang/type beam1d
/gps/ang/rot1 0 1 0
/gps/ene/type Mono
/gps/ene/mono 14.0 MeV
```

## Scoring / Tallies

### Detector spectra (equivalent to PHITS T-Track)

The simulation uses a **track-length fluence estimator**, identical in principle to the PHITS `T-Track` tally with `unit=3`:

- Each neutron step in a detector volume records: energy, track length, weight
- Histograms: 100 logarithmic energy bins per detector
- Normalization: Φ(E) = Σ(w·ℓ) / (N_events · V_det · ΔE) → [1/cm²/MeV/source]

### 2D flux map

A 2D histogram (96×144 bins) records neutron flux in the XY plane at z=0, matching the PHITS xyz mesh tally.

### Output files

- `NESSA_spectra_h1_*.csv` — Histogram data per detector
- `NESSA_spectra_h2_FluxXY.csv` — 2D flux map
- `NESSA_spectra_nt_Hits.csv` — Raw hit ntuple

## Post-Processing

```bash
python3 analyze_spectra.py [n_events]
```

Produces:
- `NESSA_neutron_spectra.png` — Energy spectra at 6 key positions
- `NESSA_flux_profile.png` — Integrated flux vs beamline position
- `nspect_*_normalized.dat` — Text files matching PHITS output format

## Physics

The physics list uses **QGSP_BIC_HP** components:

- **HP (High Precision)**: Evaluated neutron data (G4NDL) for E < 20 MeV — essential for accurate 14 MeV transport through concrete
- **BIC**: Binary Intranuclear Cascade for intermediate energies
- **Thermal neutron scattering**: S(α,β) treatment for hydrogen in concrete and polyethylene — critical for thermalized neutron spectra
- **G4NeutronTrackingCut**: Kills very slow neutrons to save CPU time

### PHITS vs Geant4 physics comparison

| Aspect | PHITS | Geant4 |
|---|---|---|
| Neutron transport | JENDL/ENDF libraries | G4NDL (same evaluated data) |
| Elastic scattering | Library-based | G4NeutronHPElastic |
| Inelastic | Library-based | G4NeutronHPInelastic |
| Thermal scattering | S(α,β) | G4ThermalNeutrons |
| Variance reduction | Importance biasing | Not needed (but available) |

## PHITS → Geant4 Geometry Conversion Notes

### Coordinate system
PHITS and Geant4 use the same Cartesian coordinate system. All PHITS coordinates in cm are preserved. Geant4 internally uses mm, so all dimensions use explicit `*cm` unit multipliers.

### Key differences
1. **PHITS layered cells for importance biasing** → Single concrete volumes in Geant4 (Geant4 has its own biasing framework if needed)
2. **PHITS CSG with surface numbers** → Geant4 solid primitives (G4Box, G4Tubs) placed directly
3. **PHITS T-Track tally** → Sensitive detector with track-length scoring + G4AnalysisManager histograms
4. **PHITS source definition** → G4GeneralParticleSource (GPS) via macro

### Detector positions (all at z=0, oriented along Y-axis)

| Detector | X (cm) | Y (cm) | PHITS Cell | Distance from source |
|---|---|---|---|---|
| Dtctr1 | 60 | -110 | 33 | 30 cm (post-collimator) |
| Dtctr5 | 60 | -90 | 37 | 50 cm |
| Dtctr10 | 60 | -65 | 42 | 75 cm |
| Dtctr15 | 60 | -40 | 47 | 100 cm |
| Dtctr20 | 60 | -15 | 52 | 125 cm |
| DtcIn1 | 60 | -150 | 53 | 10 cm (source side) |
| DtcIn2 | 10 | -170 | 54 | Off-axis |

## Variance Reduction (Optional)

The PHITS input uses importance biasing. If statistics are insufficient in Geant4, you can add geometry importance biasing:

```cpp
// In DetectorConstruction::ConstructSDandField()
#include "G4IStore.hh"
auto istore = G4IStore::GetInstance();
istore->AddImportanceGeometryCell(128, physDetector1);  // etc.
```

Or use the built-in weight window technique via `/run/setCut` commands. For most applications with 1M+ events and multithreading, variance reduction is not critical in Geant4.
