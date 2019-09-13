// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
#include "HDSActionInitialization.hh"
#include "HDSPrimaryGeneratorAction.hh"
#include "HDSRunAction.hh"
#include "HDSEventAction.hh"
#include "HDSSteppingAction.hh"
#include "HDSDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSActionInitialization::HDSActionInitialization
                            (HDSDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSActionInitialization::~HDSActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSActionInitialization::BuildForMaster() const
{
  SetUserAction(new HDSRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSActionInitialization::Build() const
{
  SetUserAction(new HDSPrimaryGeneratorAction);
  SetUserAction(new HDSRunAction);
  auto eventAction = new HDSEventAction;
  SetUserAction(eventAction);
  SetUserAction(new HDSSteppingAction(fDetConstruction,eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
