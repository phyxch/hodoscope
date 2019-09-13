// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names

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
    for (int j = 0;  j < 3; j++) 
	{
	    fEnergyLayer[j] = 0.;
	    fTrackLayer[j] = 0.;
	}
    
    // for neutron cell
    fEnergyNeutronCell = 0.;
    fTrackNeutronCell = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSEventAction::EndOfEventAction(const G4Event* event)
{
    // Accumulate statistics
    //
    
    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    
    // fill histograms
    for (int j = 0; j<3; j++) 
	{
	    analysisManager->FillH1(0+j, fEnergyLayer[j]);
	    analysisManager->FillH1(4+j, fTrackLayer[j]);
	}
    // for Neutron cell
    analysisManager->FillH1(3, fEnergyNeutronCell);
    analysisManager->FillH1(7, fTrackNeutronCell);
    
    // fill ntuple
    analysisManager->FillNtupleDColumn(0, fEnergyLayer[0]);
    analysisManager->FillNtupleDColumn(1, fEnergyLayer[1]);
    analysisManager->FillNtupleDColumn(2, fEnergyLayer[2]);
    analysisManager->FillNtupleDColumn(3, fEnergyNeutronCell);
    analysisManager->FillNtupleDColumn(4, fTrackLayer[0]);
    analysisManager->FillNtupleDColumn(5, fTrackLayer[1]);
    analysisManager->FillNtupleDColumn(6, fTrackLayer[2]);
    analysisManager->FillNtupleDColumn(7, fTrackNeutronCell);
    analysisManager->AddNtupleRow();  
    
    // Print per event (modulo n)
    //
    auto eventID = event->GetEventID();
    auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
	G4cout << "---> End of event: " << eventID << G4endl;     
	
	// From muon panels
	for (int j = 0; j<3; j++) 
	    {
		G4cout
		    << "   ELossLayer: total energy: " << std::setw(7)
		    << G4BestUnit(fEnergyLayer[j],"Energy")
		    << "       total track length: " << std::setw(7)
		    << G4BestUnit(fTrackLayer[j],"Length")
		    << G4endl;
	    }
	
	// For neutron cell
	G4cout
	    << "   ELossNeutronCell: total energy: " << std::setw(7)
	    << G4BestUnit(fEnergyNeutronCell,"Energy")
	    << "       total track length: " << std::setw(7)
	    << G4BestUnit(fTrackNeutronCell,"Length")
	    << G4endl;	
    }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
