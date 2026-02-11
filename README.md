# NESSA Geant4 Simulation v3

Converted from MCNP5 model of the FREIA/NESSA neutron beamline facility
at Uppsala University. Simulates 14 MeV D-T neutrons from an Adelphi DT-110
generator propagating through magnetite concrete shielding.

## Build

```bash
tar xzf nessa_v3.tar.gz && cd nessa_v3
mkdir build && cd build
cmake .. -DGeant4_DIR=/path/to/geant4/lib/cmake/Geant4
make -j$(nproc)
```

## Run

### Interactive (visualization)
```bash
./nessa_sim
```
Then: `/run/beamOn 50` to see neutron tracks.

### Batch (production)
```bash
./nessa_sim macros/run.mac
```

## Output

`nessa_output.root` (or `.csv` if Geant4 was built without ROOT):
- **80 histograms**: neutron/photon spectra + dose at 20 detector positions
- **scoring ntuple**: step-level data (detID, energy, edep, trackLength, particle)
- **ar41 ntuple**: Ar-41 production events (x, y, z, neutronE, weight, volume)

## Detector Configuration

Edit `macros/detectors.mac` to add/remove/move scoring detectors:

```
/nessa/detector/add MyNewDet 200 500 150 3.0
/nessa/detector/disable Lab_exit
/nessa/detector/list
```

## Analysis

```bash
root -l 'macros/plot_results.C("nessa_output.root")'
```

## File Structure

```
include/
  NESSADetectorConstruction.hh  - Geometry
  NESSAPrimaryGeneratorAction.hh - Adelphi DT source
  NESSAActionInitialization.hh   - Action wiring
  NESSARunAction.hh              - Run control + ROOT output
  NESSASteppingAction.hh         - Ar-41 tracking
  NESSAScoringSD.hh              - Point detector sensitive detector
  NESSAScoringConfig.hh          - Detector positions (singleton)
  NESSADetectorMessenger.hh      - Macro commands for detectors
src/
  (corresponding .cc files)
macros/
  run.mac          - Batch production run
  vis.mac          - Visualization with labels and cutaways
  init_vis.mac     - Interactive init
  detectors.mac    - Detector configuration (user-editable)
  scorers.mac      - Optional mesh tallies
  plot_results.C   - ROOT analysis macro
data/
  adelphi_source.dat - Direction-dependent DT energy spectra
```

## Ar-41 Activity

The simulation tracks Ar-40(n,γ)Ar-41 production in all air volumes.
At run end, it reports:
- Total Ar-41 atoms produced per source neutron
- Saturation activity in Bq for a given source strength
- Breakdown by volume (which air regions contribute most)

## Visualization Tips

- **See inside**: wireframe mode + cutaway plane (default)
- **Solid view**: `/vis/viewer/set/style surface`
- **New cutaway**: `/vis/viewer/addCutawayPlane 0 0 1.50 m 0 0 -1`
- **Remove cutaway**: `/vis/viewer/clearCutawayPlanes`
- **Track 50 neutrons**: `/run/beamOn 50`
- Labels show: DT-Source, Collimator-In/Out, HVS, FissionChamber, Labyrinth-Out
