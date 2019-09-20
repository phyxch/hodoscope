// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
// Sep 20, 2019: hexc, James, Nadia, Denzel and Ernesto
// Implement code to get the logical names of the hodoscope layers

#ifndef HDSDetectorConstruction_h
#define HDSDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

class HDSDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    HDSDetectorConstruction();
    virtual ~HDSDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // get methods
    //
    const G4VPhysicalVolume* GetScintLayer0PV() const;   // Top layer in X
    const G4VPhysicalVolume* GetScintLayer1PV() const;   // Top layer in Y
    const G4VPhysicalVolume* GetScintLayer2PV() const;   // Bottom layer in X
    const G4VPhysicalVolume* GetScintLayer3PV() const;   // Bottom layer in Y

    const G4LogicalVolume* GetScintLayer0LV() const;
    const G4LogicalVolume* GetScintLayer1LV() const;
    const G4LogicalVolume* GetScintLayer2LV() const;
    const G4LogicalVolume* GetScintLayer3LV() const;
     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
     
    //    G4VPhysicalVolume*   fAbsorberPV; // the absorber physical volume
    
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
    
    G4double           worldSizeX, worldSizeY, worldSizeZ;
    G4double           dist12, dist23;
    G4double           scintX, scintY, scintZ;
    G4int                 nofLayers;

    G4VPhysicalVolume  *physiScint0, *physiScint1, *physiScint2, *physiScint3;
    G4LogicalVolume  *LVScint0, *LVScint1, *LVScint2, *LVScint3;

};

// inline functions

inline const G4VPhysicalVolume* HDSDetectorConstruction::GetScintLayer0PV() const { 
  return physiScint0; 
}

inline const G4VPhysicalVolume* HDSDetectorConstruction::GetScintLayer1PV() const { 
  return physiScint1; 
}

inline const G4VPhysicalVolume* HDSDetectorConstruction::GetScintLayer2PV() const { 
  return physiScint2; 
}

inline const G4VPhysicalVolume* HDSDetectorConstruction::GetScintLayer3PV() const { 
  return physiScint3; 
}


inline const G4LogicalVolume* HDSDetectorConstruction::GetScintLayer0LV() const { 
  return LVScint0; 
}

inline const G4LogicalVolume* HDSDetectorConstruction::GetScintLayer1LV() const { 
  return LVScint1; 
}

inline const G4LogicalVolume* HDSDetectorConstruction::GetScintLayer2LV() const { 
  return LVScint2; 
}

inline const G4LogicalVolume* HDSDetectorConstruction::GetScintLayer3LV() const { 
  return LVScint3; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

