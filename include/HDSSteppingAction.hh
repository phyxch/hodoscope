// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
// Sep 20, 2019: hexc, James, Nadia, Ernesto and Denzel
// Extract hit position at entry point for filling the analysis ntuple
//

#ifndef HDSSteppingAction_h
#define HDSSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class HDSDetectorConstruction;
class HDSEventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in B4aEventAction.

class HDSSteppingAction : public G4UserSteppingAction
{
public:
  HDSSteppingAction(const HDSDetectorConstruction* detectorConstruction,
                    HDSEventAction* eventAction);
  virtual ~HDSSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
    
private:
  const HDSDetectorConstruction* fDetConstruction;
  HDSEventAction*  fEventAction;  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
