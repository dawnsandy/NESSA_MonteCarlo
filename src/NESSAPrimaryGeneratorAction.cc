// ============================================================
// NESSAPrimaryGeneratorAction
// Implements Adelphi DT generator with direction-dependent
// energy spectrum (MCNP FDIR source definition)
// ============================================================

#include "NESSAPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"

#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>

NESSAPrimaryGeneratorAction::NESSAPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
    
    // Set particle type to neutron
    auto particleTable = G4ParticleTable::GetParticleTable();
    auto neutron = particleTable->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(neutron);
    
    // Source geometry from MCNP SDEF card:
    // POS = 195 371 150, VEC = 0 0 1, AXS = 0 0 1
    // ext d2: si2 0 0.00001 (essentially zero extension along axis)
    // rad d3: si3 0 0.9, sp3 -21 1 (uniform disk, R=0.9 cm)
    fSourcePos = G4ThreeVector(195.0*cm, 371.0*cm, 150.0*cm);
    fSourceAxis = G4ThreeVector(0., 0., 1.);
    fSourceRadius = 0.9*cm;
    
    // Load the direction-dependent energy distributions
    LoadSourceData("data/adelphi_source.dat");
}

NESSAPrimaryGeneratorAction::~NESSAPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void NESSAPrimaryGeneratorAction::LoadSourceData(const G4String& filename)
{
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        G4cerr << "ERROR: Cannot open source data file: " << filename << G4endl;
        G4cerr << "Trying alternate path..." << G4endl;
        infile.open("../data/adelphi_source.dat");
        if (!infile.is_open()) {
            G4Exception("NESSAPrimaryGeneratorAction::LoadSourceData",
                "Source001", FatalException,
                "Cannot find adelphi_source.dat");
            return;
        }
    }
    
    G4cout << "Loading Adelphi source distribution data..." << G4endl;
    
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;
        
        if (keyword == "N_DIR_BINS") {
            iss >> fNDirBins;
        }
        else if (keyword == "N_ENERGY_BINS") {
            iss >> fNEnergyBins;
        }
        else if (keyword == "DIR_BINS") {
            fDirBins.resize(fNDirBins);
            for (int i = 0; i < fNDirBins; i++) {
                iss >> fDirBins[i];
            }
        }
        else if (keyword == "DIR_PROBS") {
            std::vector<G4double> dirProbs(fNDirBins);
            for (int i = 0; i < fNDirBins; i++) {
                iss >> dirProbs[i];
            }
            // Build CDF for direction sampling
            fDirCDF.resize(fNDirBins);
            fDirCDF[0] = dirProbs[0];
            for (int i = 1; i < fNDirBins; i++) {
                fDirCDF[i] = fDirCDF[i-1] + dirProbs[i];
            }
            // Normalize
            G4double total = fDirCDF.back();
            for (auto& v : fDirCDF) v /= total;
        }
        else if (keyword == "ENERGY_BINS") {
            fEnergyBins.resize(fNEnergyBins);
            for (int i = 0; i < fNEnergyBins; i++) {
                iss >> fEnergyBins[i];
            }
        }
        else if (keyword.substr(0, 13) == "ENERGY_PROBS_") {
            int idx = std::stoi(keyword.substr(13));
            std::vector<G4double> probs(fNEnergyBins);
            for (int i = 0; i < fNEnergyBins; i++) {
                iss >> probs[i];
            }
            // Build CDF
            if (idx >= (int)fEnergyCDFs.size()) {
                fEnergyCDFs.resize(idx + 1);
            }
            fEnergyCDFs[idx].resize(fNEnergyBins);
            fEnergyCDFs[idx][0] = probs[0];
            for (int i = 1; i < fNEnergyBins; i++) {
                fEnergyCDFs[idx][i] = fEnergyCDFs[idx][i-1] + probs[i];
            }
            G4double total = fEnergyCDFs[idx].back();
            if (total > 0) {
                for (auto& v : fEnergyCDFs[idx]) v /= total;
            }
        }
    }
    
    infile.close();
    G4cout << "Loaded " << fNDirBins << " direction bins, "
           << fNEnergyBins << " energy bins, "
           << fEnergyCDFs.size() << " energy distributions" << G4endl;
}

G4int NESSAPrimaryGeneratorAction::SampleDirectionBin()
{
    G4double r = G4UniformRand();
    auto it = std::lower_bound(fDirCDF.begin(), fDirCDF.end(), r);
    return std::distance(fDirCDF.begin(), it);
}

G4double NESSAPrimaryGeneratorAction::SampleEnergy(G4int dirBin)
{
    if (dirBin < 0 || dirBin >= (G4int)fEnergyCDFs.size()) {
        return 14.1*MeV;  // Fallback: monoenergetic DT
    }
    
    const auto& cdf = fEnergyCDFs[dirBin];
    if (cdf.empty() || cdf.back() <= 0) {
        return 14.1*MeV;
    }
    
    G4double r = G4UniformRand();
    auto it = std::lower_bound(cdf.begin(), cdf.end(), r);
    G4int idx = std::distance(cdf.begin(), it);
    
    if (idx <= 0) idx = 1;
    if (idx >= fNEnergyBins) idx = fNEnergyBins - 1;
    
    // Linear interpolation within the bin
    G4double elow = fEnergyBins[idx-1];
    G4double ehigh = fEnergyBins[idx];
    G4double frac = G4UniformRand();
    
    return (elow + frac * (ehigh - elow)) * MeV;
}

void NESSAPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // 1. Sample position on uniform disk (sp3 -21 1 = power law r^1)
    G4double r = fSourceRadius * std::sqrt(G4UniformRand());
    G4double phi = twopi * G4UniformRand();
    
    // Disk is perpendicular to the source axis (Z)
    G4ThreeVector pos = fSourcePos;
    pos += G4ThreeVector(r * std::cos(phi), r * std::sin(phi), 0.);
    
    // 2. Sample direction bin (determines both direction and energy)
    G4int dirBin = SampleDirectionBin();
    
    // Get the direction cosine (cos theta relative to source axis)
    G4double cosTheta;
    if (dirBin > 0 && dirBin < fNDirBins) {
        // Sample uniformly within the bin
        G4double binLow = fDirBins[dirBin - 1];
        G4double binHigh = fDirBins[dirBin];
        cosTheta = binLow + G4UniformRand() * (binHigh - binLow);
    } else if (dirBin == 0) {
        cosTheta = fDirBins[0];
    } else {
        cosTheta = fDirBins.back();
    }
    
    // Convert to direction vector
    // cosTheta is relative to the source axis (0,0,1)
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double phiDir = twopi * G4UniformRand();
    
    G4ThreeVector direction(
        sinTheta * std::cos(phiDir),
        sinTheta * std::sin(phiDir),
        cosTheta
    );
    
    // 3. Sample energy from the direction-dependent distribution
    G4double energy = SampleEnergy(dirBin);
    
    // 4. Set the particle gun
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(direction);
    fParticleGun->SetParticleEnergy(energy);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
