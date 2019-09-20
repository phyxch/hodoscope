// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
// Sep 20, 2019: hexc, James, Nadia, Denzel and Ernesto
// Filling analysis ntuple with energy loss, track length, x and y position in each layer.

#include "HDSEventAction.hh"
#include "HDSRunAction.hh"
#include "HDSAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSEventAction::HDSEventAction()
 : G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSEventAction::~HDSEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
    // initialisation per event
    for (int j = 0;  j < 4;  j++) 
	{
	    fEnergyLayer[j] = 0.;
	    fTrackLayer[j] = 0.;
	    fLayerX[j] = -9999.0;
	    fLayerY[j] = -9999.0;
	    fLayerZ[j] = -9999.0;
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSEventAction::EndOfEventAction(const G4Event* event)
{
    // Accumulate statistics
    //
    
    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    
    // fill histograms
    for (int j = 0; j<(G4int)nLayer; j++) 
	{
	    analysisManager->FillH1(0+j, fEnergyLayer[j]);
	    analysisManager->FillH1(4+j, fTrackLayer[j]);
	}
    
    // fill ntuple
    analysisManager->FillNtupleDColumn(0, fEnergyLayer[0]);
    analysisManager->FillNtupleDColumn(1, fEnergyLayer[1]);
    analysisManager->FillNtupleDColumn(2, fEnergyLayer[2]);
    analysisManager->FillNtupleDColumn(3, fEnergyLayer[3]);
    analysisManager->FillNtupleDColumn(4, fTrackLayer[0]);
    analysisManager->FillNtupleDColumn(5, fTrackLayer[1]);
    analysisManager->FillNtupleDColumn(6, fTrackLayer[2]);
    analysisManager->FillNtupleDColumn(7, fTrackLayer[3]);

    analysisManager->FillNtupleDColumn(8,  fLayerX[0]);
    analysisManager->FillNtupleDColumn(9,  fLayerY[0]);
    analysisManager->FillNtupleDColumn(10, fLayerZ[0]);

    analysisManager->FillNtupleDColumn(11,  fLayerX[1]);
    analysisManager->FillNtupleDColumn(12,  fLayerY[1]);
    analysisManager->FillNtupleDColumn(13,  fLayerZ[1]);

    analysisManager->FillNtupleDColumn(14,  fLayerX[2]);
    analysisManager->FillNtupleDColumn(15,  fLayerY[2]);
    analysisManager->FillNtupleDColumn(16,  fLayerZ[2]);

    analysisManager->FillNtupleDColumn(17,  fLayerX[3]);
    analysisManager->FillNtupleDColumn(18,  fLayerY[3]);
    analysisManager->FillNtupleDColumn(19,  fLayerZ[3]);

    analysisManager->AddNtupleRow();  
    
    // Print per event (modulo n)
    //
    auto eventID = event->GetEventID();
    auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
	G4cout << "---> End of event: " << eventID << G4endl;     
	
	// From muon panels
	for (int j = 0; j<(G4int)nLayer; j++) 
	    {
		G4cout
		    << "   ELossLayer: total energy: " << std::setw(7)
		    << G4BestUnit(fEnergyLayer[j],"Energy")
		    << "       total track length: " << std::setw(7)
		    << G4BestUnit(fTrackLayer[j],"Length")
		    << G4endl;
	    }
    }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
