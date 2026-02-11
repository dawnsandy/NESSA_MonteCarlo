//============================================================================
// NESSADoseCalculator.hh
// Neutron fluence-to-dose conversion using ICRP 74 H*(10) coefficients
//
// Provides: h_star_10(E) in pSv·cm² per neutron
// Reference: ICRP Publication 74, Table A.42
//            "Conversion Coefficients for use in Radiological Protection"
//
// The conversion factor h(E) converts neutron fluence Φ [n/cm²] to
// ambient dose equivalent H*(10) [Sv]:
//     H*(10) = Σ h(Ei) × Φ(Ei) × ΔEi
//
// To get dose RATE in μSv/hr from a source emitting S [n/s]:
//     dH/dt [μSv/hr] = S × Σ h(Ei) × φ(Ei) × ΔEi × 3600 × 1e-6
// where φ(Ei) is fluence per source neutron [1/cm²/MeV]
//============================================================================
#ifndef NESSADoseCalculator_h
#define NESSADoseCalculator_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include <vector>
#include <cmath>

class NESSADoseCalculator
{
public:
    static NESSADoseCalculator& Instance() {
        static NESSADoseCalculator instance;
        return instance;
    }

    // Returns H*(10) conversion coefficient in pSv·cm² for given neutron energy
    // Input: neutron kinetic energy in Geant4 internal units (MeV)
    // Output: h*(10) in pSv·cm²
    G4double GetH10(G4double energy_MeV) const;

    // Returns dose contribution for a single track-length step
    // Input: energy [MeV], trackLength [cm], weight
    // Output: dose contribution in pSv (to be accumulated and normalized)
    G4double GetDoseContribution(G4double energy_MeV, G4double trackLen_cm,
                                  G4double weight) const;

private:
    NESSADoseCalculator();

    // ICRP 74 Table A.42: H*(10)/Φ for neutrons
    // Energy in MeV, h*(10) in pSv·cm²
    struct DataPoint { G4double energy; G4double h10; };
    std::vector<DataPoint> fTable;

    // Log-log interpolation
    G4double Interpolate(G4double energy_MeV) const;
};

//============================================================================
// INLINE IMPLEMENTATION
//============================================================================

inline NESSADoseCalculator::NESSADoseCalculator()
{
    // ICRP 74 Table A.42: H*(10)/Φ for monoenergetic neutrons
    // Energy [MeV], H*(10)/Φ [pSv·cm²]
    //
    // These are the standard values used worldwide for neutron dosimetry
    // at facilities like NESSA, reactor halls, and accelerator shielding
    fTable = {
        { 1.0e-09,  6.60 },   // thermal
        { 1.0e-08,  9.00 },
        { 2.5e-08, 10.60 },   // 0.0253 eV thermal peak
        { 1.0e-07,  8.76 },
        { 2.0e-07,  7.80 },
        { 5.0e-07,  6.00 },
        { 1.0e-06,  4.68 },
        { 2.0e-06,  3.72 },
        { 5.0e-06,  3.12 },
        { 1.0e-05,  2.88 },
        { 2.0e-05,  2.76 },
        { 5.0e-05,  2.64 },
        { 1.0e-04,  2.64 },
        { 2.0e-04,  2.88 },
        { 5.0e-04,  3.24 },
        { 1.0e-03,  3.60 },
        { 2.0e-03,  4.08 },
        { 5.0e-03,  5.04 },
        { 1.0e-02,  6.12 },
        { 2.0e-02,  8.16 },
        { 3.0e-02, 10.08 },
        { 5.0e-02, 13.56 },
        { 7.0e-02, 17.16 },
        { 1.0e-01, 23.40 },
        { 1.5e-01, 33.60 },
        { 2.0e-01, 44.40 },
        { 3.0e-01, 67.20 },
        { 5.0e-01, 108.0 },
        { 7.0e-01, 141.6 },
        { 9.0e-01, 168.0 },
        { 1.0e+00, 180.0 },
        { 1.2e+00, 199.2 },
        { 1.5e+00, 216.0 },   // ~1.5 MeV fission spectrum peak
        { 2.0e+00, 240.0 },
        { 3.0e+00, 271.2 },
        { 4.0e+00, 290.4 },
        { 5.0e+00, 300.0 },
        { 6.0e+00, 309.6 },
        { 7.0e+00, 321.6 },
        { 8.0e+00, 336.0 },
        { 9.0e+00, 348.0 },
        { 1.0e+01, 360.0 },
        { 1.2e+01, 378.0 },
        { 1.4e+01, 396.0 },   // *** 14 MeV D-T peak ***
        { 1.5e+01, 405.6 },
        { 1.6e+01, 412.8 },
        { 1.8e+01, 421.2 },
        { 2.0e+01, 420.0 },
    };
}

inline G4double NESSADoseCalculator::Interpolate(G4double energy_MeV) const
{
    if (energy_MeV <= fTable.front().energy)
        return fTable.front().h10;
    if (energy_MeV >= fTable.back().energy)
        return fTable.back().h10;

    // Find bracketing entries
    size_t i = 0;
    for (i = 0; i < fTable.size() - 1; ++i) {
        if (fTable[i+1].energy >= energy_MeV) break;
    }

    // Log-log interpolation (standard for cross-section-like data)
    G4double logE  = std::log(energy_MeV);
    G4double logE0 = std::log(fTable[i].energy);
    G4double logE1 = std::log(fTable[i+1].energy);
    G4double logH0 = std::log(fTable[i].h10);
    G4double logH1 = std::log(fTable[i+1].h10);

    G4double frac = (logE - logE0) / (logE1 - logE0);
    return std::exp(logH0 + frac * (logH1 - logH0));
}

inline G4double NESSADoseCalculator::GetH10(G4double energy_MeV) const
{
    return Interpolate(energy_MeV);
}

inline G4double NESSADoseCalculator::GetDoseContribution(
    G4double energy_MeV, G4double trackLen_cm, G4double weight) const
{
    // h*(10) [pSv·cm²] × trackLength [cm] / Volume [cm³] → pSv per source
    // We accumulate (h * weight * trackLength) and normalize by (N * V) later
    G4double h = Interpolate(energy_MeV);
    return h * weight * trackLen_cm;  // pSv·cm² × cm / (to be divided by V later)
}

#endif
