#!/usr/bin/env python3
"""
NESSA Geant4 Post-Processing: Neutron Spectra Analysis
=======================================================
Reads the CSV output from the Geant4 NESSA simulation and produces
neutron energy spectra normalized to match PHITS T-Track unit=3:
    Phi(E) [1/cm^2/MeV/source]

The Geant4 histograms contain sum(weight * trackLength_cm) per energy bin.
To convert to PHITS-equivalent flux:
    Phi(E) = histogram_content / (N_events * V_detector * dE)

where:
    N_events    = total source neutrons simulated
    V_detector  = pi * R^2 * H = pi * 1^2 * 1 = pi cm^3
    dE          = bin width in MeV (variable for log bins)

Author: NESSA Facility Analysis
"""

import numpy as np
import matplotlib.pyplot as plt
import csv
import sys
import os
import glob

# ============================================================================
# Configuration
# ============================================================================

N_DETECTORS = 22
DET_RADIUS = 1.0    # cm
DET_HEIGHT = 1.0    # cm
DET_VOLUME = np.pi * DET_RADIUS**2 * DET_HEIGHT  # cm^3

DETECTOR_NAMES = [
    "Dtctr1",  "Dtctr2",  "Dtctr3",  "Dtctr4",  "Dtctr5",
    "Dtctr6",  "Dtctr7",  "Dtctr8",  "Dtctr9",  "Dtctr10",
    "Dtctr11", "Dtctr12", "Dtctr13", "Dtctr14", "Dtctr15",
    "Dtctr16", "Dtctr17", "Dtctr18", "Dtctr19", "Dtctr20",
    "DtcIn1",  "DtcIn2"
]

# Detector Y-positions (cm) for spatial profile
DET_Y_POSITIONS = [
    -110, -105, -100, -95, -90, -85, -80, -74.5, -70, -65,
    -60, -55, -50, -45, -40, -35, -30, -25, -20, -15,
    -150, -170
]


def read_g4csv_histogram(filename):
    """Read a Geant4 CSV histogram file.
    
    Geant4 CSV histograms have format:
    # comment lines
    binLowEdge, binContent, binError
    """
    edges = []
    contents = []
    errors = []
    
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if line.startswith('#') or line.startswith(',') or not line:
                continue
            parts = line.split(',')
            if len(parts) >= 3:
                try:
                    edges.append(float(parts[0]))
                    contents.append(float(parts[1]))
                    errors.append(float(parts[2]))
                except ValueError:
                    continue
    
    return np.array(edges), np.array(contents), np.array(errors)


def read_ntuple_csv(filename):
    """Read the raw hits ntuple CSV."""
    data = []
    with open(filename, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            data.append({
                'DetID': int(row['DetID']),
                'Energy_MeV': float(row['Energy_MeV']),
                'TrackLength_cm': float(row['TrackLength_cm']),
                'Weight': float(row['Weight']),
            })
    return data


def normalize_spectrum(bin_edges_MeV, bin_contents, n_events):
    """
    Normalize histogram to PHITS T-Track unit=3: 1/cm^2/MeV/source
    
    bin_contents already contain sum(weight * trackLength_cm)
    
    Phi(E) = bin_content / (n_events * V_det * dE)
    """
    n_bins = len(bin_contents)
    bin_widths = np.diff(bin_edges_MeV[:n_bins+1]) if len(bin_edges_MeV) > n_bins else \
                 bin_edges_MeV[1:] - bin_edges_MeV[:-1]
    
    # Avoid division by zero
    bin_widths = np.where(bin_widths > 0, bin_widths, 1e-30)
    
    phi = bin_contents / (n_events * DET_VOLUME * bin_widths[:len(bin_contents)])
    return phi


def plot_spectra(results, n_events, output_dir='.'):
    """Plot neutron spectra for selected detectors."""
    
    fig, axes = plt.subplots(2, 3, figsize=(18, 10))
    fig.suptitle('NESSA Neutron Beamline - Geant4 Simulation\n'
                 f'Neutron Energy Spectra (N = {n_events:.0e} source neutrons)',
                 fontsize=14, fontweight='bold')
    
    # Select key detectors to plot (matching PHITS tallies)
    plot_dets = [
        (0,  "Dtctr1 (post-collimator, y=-110)"),
        (4,  "Dtctr5 (y=-90)"),
        (9,  "Dtctr10 (y=-65)"),
        (14, "Dtctr15 (y=-40)"),
        (20, "DtcIn1 (near source, y=-150)"),
        (21, "DtcIn2 (off-axis, y=-170)"),
    ]
    
    for ax, (det_idx, label) in zip(axes.flatten(), plot_dets):
        if det_idx in results:
            edges, content, phi = results[det_idx]
            bin_centers = 0.5 * (edges[:-1] + edges[1:]) if len(edges) > len(phi) \
                         else edges[:len(phi)]
            
            mask = phi > 0
            if np.any(mask):
                ax.loglog(bin_centers[mask], phi[mask], 'b-', linewidth=0.8)
            
            ax.set_xlabel('Neutron Energy [MeV]')
            ax.set_ylabel('Flux [1/cm²/MeV/source]')
            ax.set_title(label, fontsize=10)
            ax.grid(True, which='both', alpha=0.3)
            ax.set_xlim(1e-10, 20)
        else:
            ax.text(0.5, 0.5, f'No data for {DETECTOR_NAMES[det_idx]}',
                   ha='center', va='center', transform=ax.transAxes)
    
    plt.tight_layout()
    outfile = os.path.join(output_dir, 'NESSA_neutron_spectra.png')
    plt.savefig(outfile, dpi=200)
    plt.close()
    print(f"Spectra plot saved: {outfile}")


def plot_spatial_profile(results, n_events, output_dir='.'):
    """Plot integrated neutron flux vs distance along beamline."""
    
    total_flux = []
    y_pos = []
    
    for i in range(20):  # Only beamline detectors (not DtcIn1, DtcIn2)
        if i in results:
            edges, content, phi = results[i]
            # Integrate flux over all energies
            bin_widths = np.diff(edges[:len(phi)+1]) if len(edges) > len(phi) \
                        else np.ones(len(phi))
            integrated = np.sum(phi * bin_widths[:len(phi)])
            total_flux.append(integrated)
            y_pos.append(DET_Y_POSITIONS[i])
    
    if total_flux:
        fig, ax = plt.subplots(figsize=(10, 6))
        ax.semilogy(y_pos, total_flux, 'ro-', markersize=6)
        ax.set_xlabel('Y position along beamline [cm]')
        ax.set_ylabel('Integrated neutron flux [1/cm²/source]')
        ax.set_title('NESSA: Neutron Flux Profile Along Beamline')
        ax.grid(True, alpha=0.3)
        ax.invert_xaxis()  # Source is at y=-140, collimator exit at y=-75
        
        # Mark key positions
        ax.axvline(x=-115, color='gray', linestyle='--', alpha=0.5, label='Collimator wall')
        ax.axvline(x=-75, color='green', linestyle='--', alpha=0.5, label='Collimator exit')
        ax.legend()
        
        outfile = os.path.join(output_dir, 'NESSA_flux_profile.png')
        plt.savefig(outfile, dpi=200)
        plt.close()
        print(f"Flux profile plot saved: {outfile}")


def main():
    """Main post-processing routine."""
    
    print("=" * 70)
    print("NESSA Geant4 Simulation Post-Processing")
    print("=" * 70)
    
    # Find output files
    # Geant4 CSV analysis creates files like: NESSA_spectra_h1_Dtctr1.csv, etc.
    hist_files = sorted(glob.glob("NESSA_spectra_h1_*.csv"))
    ntuple_file = "NESSA_spectra_nt_Hits.csv"
    
    if not hist_files:
        print("No histogram CSV files found (NESSA_spectra_h1_*.csv)")
        print("Looking for alternative naming...")
        hist_files = sorted(glob.glob("NESSA_spectra*h1*.csv"))
    
    if not hist_files:
        print("\nERROR: No output files found!")
        print("Run the simulation first: ./nessa_sim macros/run.mac")
        print("\nAlternatively, process the ntuple directly...")
        
        if os.path.exists(ntuple_file):
            print(f"Found ntuple: {ntuple_file}")
            process_ntuple(ntuple_file)
        return
    
    # Get number of events (user must provide or read from log)
    n_events = 1000000  # Default; adjust based on your run
    if len(sys.argv) > 1:
        n_events = int(float(sys.argv[1]))
    
    print(f"\nNumber of source events: {n_events:.2e}")
    print(f"Detector volume: {DET_VOLUME:.4f} cm³")
    print(f"Found {len(hist_files)} histogram files\n")
    
    results = {}
    
    for i, det_name in enumerate(DETECTOR_NAMES):
        # Try to find the histogram file for this detector
        matching = [f for f in hist_files if det_name in f]
        if matching:
            fname = matching[0]
            edges, content, errors = read_g4csv_histogram(fname)
            
            if len(content) > 0:
                phi = normalize_spectrum(edges, content, n_events)
                results[i] = (edges, content, phi)
                
                total = np.sum(phi * np.diff(edges[:len(phi)+1])
                              if len(edges) > len(phi)
                              else np.sum(phi))
                print(f"  {det_name}: {len(content)} bins, "
                      f"integrated flux = {total:.3e} 1/cm²/source")
    
    if results:
        plot_spectra(results, n_events)
        plot_spatial_profile(results, n_events)
        
        # Save normalized spectra to text files
        for i, det_name in enumerate(DETECTOR_NAMES):
            if i in results:
                edges, content, phi = results[i]
                n = len(phi)
                outname = f"nspect_{det_name}_normalized.dat"
                with open(outname, 'w') as f:
                    f.write(f"# NESSA Geant4: {det_name}\n")
                    f.write(f"# N_events = {n_events}\n")
                    f.write(f"# Energy_low[MeV]  Energy_high[MeV]  "
                            f"Flux[1/cm2/MeV/source]\n")
                    for j in range(n):
                        elow = edges[j] if j < len(edges) else 0
                        ehigh = edges[j+1] if j+1 < len(edges) else 0
                        f.write(f"{elow:.6e}  {ehigh:.6e}  {phi[j]:.6e}\n")
        
        print("\nNormalized spectra saved as nspect_*_normalized.dat")
    else:
        print("\nNo valid histogram data found.")


def process_ntuple(filename):
    """Process raw ntuple data if histograms aren't available."""
    print(f"\nProcessing ntuple: {filename}")
    
    data = read_ntuple_csv(filename)
    print(f"Total hits: {len(data)}")
    
    # Build spectra from raw hits
    for det_idx in range(N_DETECTORS):
        hits = [d for d in data if d['DetID'] == det_idx]
        if hits:
            energies = [h['Energy_MeV'] for h in hits]
            print(f"  {DETECTOR_NAMES[det_idx]}: {len(hits)} hits, "
                  f"E range: {min(energies):.4e} - {max(energies):.4e} MeV")


if __name__ == '__main__':
    main()
