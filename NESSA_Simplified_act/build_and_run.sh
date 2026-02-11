#!/bin/bash
#============================================================================
# build_and_run.sh
# Build and run the NESSA Geant4 simulation
#
# Prerequisites:
#   - Geant4 11.x installed and environment sourced
#   - G4NDL neutron data library installed (for HP physics)
#   - cmake >= 3.16
#
# Usage:
#   ./build_and_run.sh          # Build only
#   ./build_and_run.sh run      # Build and run batch (1M events)
#   ./build_and_run.sh vis      # Build and run interactive
#   ./build_and_run.sh clean    # Clean build directory
#============================================================================

set -e

BUILDDIR="build"
NCORES=$(nproc 2>/dev/null || echo 4)

echo "============================================================"
echo "  NESSA Neutron Beamline - Geant4 Simulation Build System"
echo "  Uppsala University - Division of Applied Nuclear Physics"
echo "============================================================"

# Check Geant4 environment
if [ -z "$G4INSTALL" ] && [ -z "$Geant4_DIR" ]; then
    echo ""
    echo "WARNING: Geant4 environment may not be set."
    echo "Source your Geant4 installation first, e.g.:"
    echo "  source /path/to/geant4-install/bin/geant4.sh"
    echo ""
fi

# Check for neutron data
if [ -z "$G4NEUTRONHPDATA" ]; then
    echo "WARNING: G4NEUTRONHPDATA not set."
    echo "HP neutron models require the G4NDL data library."
    echo ""
fi

case "${1:-build}" in
    clean)
        echo "Cleaning build directory..."
        rm -rf "$BUILDDIR"
        echo "Done."
        ;;
    
    build|run|vis)
        # Create build directory
        mkdir -p "$BUILDDIR"
        cd "$BUILDDIR"
        
        echo ""
        echo "--- Configuring with CMake ---"
        cmake .. -DWITH_GEANT4_UIVIS=ON
        
        echo ""
        echo "--- Building with ${NCORES} cores ---"
        make -j${NCORES}
        
        echo ""
        echo "--- Build successful! ---"
        
        if [ "$1" = "run" ]; then
            echo ""
            echo "--- Running batch simulation (1M events) ---"
            echo "--- Output: NESSA_spectra*.csv ---"
            ./nessa_sim macros/run.mac
            
            echo ""
            echo "--- Post-processing ---"
            cd ..
            python3 analyze_spectra.py 1000000
        fi
        
        if [ "$1" = "vis" ]; then
            echo ""
            echo "--- Starting interactive visualization ---"
            ./nessa_sim
        fi
        ;;
    
    *)
        echo "Usage: $0 [build|run|vis|clean]"
        echo "  build : Build the simulation (default)"
        echo "  run   : Build and run batch mode (1M events)"
        echo "  vis   : Build and run interactive mode"
        echo "  clean : Remove build directory"
        ;;
esac
