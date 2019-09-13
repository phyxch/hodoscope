// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names

#ifndef HDSEventAction_h
#define HDSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#define nLayer 3          // Number of scintillator layers

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
    void AddEloss_TrackLength_NeutronCell(G4double de, G4double dl);
    
  private:
    G4double  fEnergyLayer[nLayer], fEnergyNeutronCell;  
    G4double  fTrackLayer[nLayer], fTrackNeutronCell; 
};

// inline functions

inline void HDSEventAction::AddEloss_TrackLength(G4int layer, G4double de, G4double dl) {
  fEnergyLayer[layer] += de; 
  fTrackLayer[layer] += dl;  
}

inline void HDSEventAction::AddEloss_TrackLength_NeutronCell(G4double de, G4double dl) {
  fEnergyNeutronCell += de; 
  fTrackNeutronCell += dl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
