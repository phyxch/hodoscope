// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
// Sep 20, 2019: hexc, James, Nadia, Denzel and Ernesto
// Filling analysis ntuple with energy loss, track length, x and y position in each layer.
//

#ifndef HDSEventAction_h
#define HDSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#define nLayer 4          // Number of scintillator layers

/// Event action class
///

class HDSEventAction : public G4UserEventAction
{
  public:
    HDSEventAction();
    virtual ~HDSEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void AddEloss_TrackLength(G4int n, G4double de, G4double dl);
    void hitPositionFilled(G4int n, G4double xPos,  G4double yPos,   G4double zPos); 

  private:
    G4double  fEnergyLayer[nLayer];  
    G4double  fTrackLayer[nLayer], fLayerX[nLayer], fLayerY[nLayer], fLayerZ[nLayer];
};

// inline functions

inline void HDSEventAction::AddEloss_TrackLength(G4int layer, G4double de, G4double dl) {
  fEnergyLayer[layer] += de; 
  fTrackLayer[layer] += dl;  
}

inline void HDSEventAction::hitPositionFilled(G4int layer, G4double xPos,  G4double yPos,   G4double zPos){
    fLayerX[layer] = xPos;
    fLayerY[layer] = yPos;
    fLayerZ[layer] = zPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
