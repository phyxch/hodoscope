// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
// Sep 20, 2019: hexc, James, Nadia, Ernesto and Denzel
// Extract hit position at entry point for filling the analysis ntuple

#include "HDSSteppingAction.hh"
#include "HDSEventAction.hh"
#include "HDSDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSSteppingAction::HDSSteppingAction(
                      const HDSDetectorConstruction* detectorConstruction,
                      HDSEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSSteppingAction::~HDSSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSSteppingAction::UserSteppingAction(const G4Step* step)
{
    // Collect energy and track length step by step
    
    // get volume of the current step
    auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    // energy deposit
    auto edep = step->GetTotalEnergyDeposit();
    
    // step length
    G4double stepLength = 0.;
    if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
	stepLength = step->GetStepLength();
    }

    G4ThreeVector position = step->GetPostStepPoint()->GetPosition();

    if ( volume == fDetConstruction->GetScintLayer0LV() ) {
	fEventAction->AddEloss_TrackLength(0, edep,stepLength);
	fEventAction->hitPositionFilled(0, position.x(), position.y(), position.z());
    } else if (volume == fDetConstruction->GetScintLayer1LV()) {
	fEventAction->AddEloss_TrackLength(1, edep,stepLength);
	fEventAction->hitPositionFilled(1, position.x(), position.y(), position.z());
    } else if (volume == fDetConstruction->GetScintLayer2LV()) {
	fEventAction->AddEloss_TrackLength(2, edep,stepLength);
	fEventAction->hitPositionFilled(2, position.x(), position.y(), position.z());
    } else if (volume == fDetConstruction->GetScintLayer3LV()) {
	fEventAction->AddEloss_TrackLength(3, edep,stepLength);
	fEventAction->hitPositionFilled(3, position.x(), position.y(), position.z());
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
