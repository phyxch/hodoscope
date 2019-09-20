// Sep 6, 2019: hexc, James, Nadia, Arfa, Ernesto, Denzel
// First modifucation to the event generator for the hodoscope simulation
//
// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
// Sep 20, 2019L hexc, James, Nadia, Denzel and Ernesto
// Shifted filling sequence in the analysis ntuple for the primary particle

#include "HDSPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "HDSAnalysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSPrimaryGeneratorAction::HDSPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
    // set event type
    ev_type = 1;

    G4int nofParticles = 1;
    fParticleGun = new G4ParticleGun(nofParticles);
    
  
    //create a messenger for this class
    gunMessenger = new HDSPrimaryGeneratorMessenger(this);

    // default particle kinematic
    //
    auto particleDefinition 
	= G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particleDefinition);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
    fParticleGun->SetParticleEnergy(50.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HDSPrimaryGeneratorAction::~HDSPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HDSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // This function is called at the begining of event
    G4ParticleDefinition* particle;

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    //particleTable ->DumpTable("ALL");
    
    // In order to avoid dependence of PrimaryGeneratorAction
    // on DetectorConstruction class we get world volume 
    // from G4LogicalVolumeStore
    //
    G4double worldZHalfLength = 0.;
    auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("world_volume");
    
    // Check that the world volume has box shape
    G4Box* worldBox = nullptr;
    if (  worldLV ) {
	G4cout << "We found the world! " << G4endl;
	worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
    }
    
    if ( worldBox ) {
	worldZHalfLength = worldBox->GetZHalfLength();  
	G4cout << " worldZHalfLength = " << worldZHalfLength << G4endl;
    }
    else  {
	G4ExceptionDescription msg;
	msg << "World volume of box shape not found." << G4endl;
	msg << "Perhaps you have changed geometry." << G4endl;
	msg << "The gun will be place in the center.";
	G4Exception("HDSPrimaryGeneratorAction::GeneratePrimaries()",
		    "MyCode0002", JustWarning, msg);
    } 

    G4double xPos, yPos, zPos, xVec, yVec, zVec, sigmaAngle, theta, phi, momentum, sigmaMomentum, mass, pp, Ekin;
    G4int pid;
    
    // Set up cosmic ray events
    if (ev_type == 0) {        // single particle simulation
	pid = 0;   // tmp pID
	//	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	//   fParticleGun->SetParticleEnergy(1.*GeV);
	yPos = (G4UniformRand()-0.5)*30.0*cm;
	zPos = (G4UniformRand()-0.5)*30.0*cm;
	xPos = 25.0*cm;
	fParticleGun->SetParticlePosition(G4ThreeVector(xPos, yPos, zPos)); 
	
	sigmaAngle = 140.*deg;
	theta = (G4UniformRand()-0.5)*sigmaAngle;
	phi = G4UniformRand()*360.*deg;
	yVec = std::sin(phi)*std::sin(theta);
	xVec = -std::cos(theta);
	zVec = std::cos(phi)*std::sin(theta);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xVec, yVec, zVec));
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
	
    }  else if (ev_type == 1) {    // cosmic ray muon flux event
	pid = 1;   // tmp pID
	particle = particleTable->FindParticle("mu-");
	fParticleGun->SetParticleDefinition(particle);
	
	//fParticleGun->SetParticleTime(0.0*ns);
	//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));	

	momentum = 300.*MeV;
	sigmaMomentum = 10000.*MeV;
	
	mass = particle->GetPDGMass();
	
	sigmaAngle = 140.*deg;
	
	G4int npart = 1;
	for (G4int i=1; i<=npart; i++) {
	    pp = momentum + G4UniformRand()*sigmaMomentum;  // 0 GeV < pp << 10.3 GeV    
	    Ekin = std::sqrt(pp*pp+mass*mass) - mass;
	    fParticleGun->SetParticleEnergy(Ekin);
	    yPos = (G4UniformRand()-0.5)*30.0*cm;
	    zPos = (G4UniformRand()-0.5)*30.0*cm;
	    xPos = 25.0*cm;
	    fParticleGun->SetParticlePosition(G4ThreeVector(xPos, yPos, zPos)); 
	    
	    theta = (G4UniformRand()-0.5)*sigmaAngle;
	    phi = G4UniformRand()*360.*deg;
	    yVec = std::sin(phi)*std::sin(theta);
	    xVec = -std::cos(theta);
	    zVec = std::cos(phi)*std::sin(theta);
	    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xVec, yVec, zVec));
	    
	    fParticleGun->GeneratePrimaryVertex(anEvent);
	}
    } else if (ev_type == 2)  // cosmic ray neutron event
	{
	    pid = 2;   // tmp pID
	    particle = particleTable->FindParticle("neutron");
	    fParticleGun->SetParticleDefinition(particle);

	    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	    
	    momentum = 1.*MeV;
	    sigmaMomentum = 100.*MeV;
	    
	    mass = particle->GetPDGMass();
	    
	    sigmaAngle = 140.*deg;
	    
	    G4int npart = 1;
	    for (G4int i=1; i<=npart; i++) {
		pp = momentum + G4UniformRand()*sigmaMomentum;  // 0 GeV < pp << 10.3 GeV    
		Ekin = std::sqrt(pp*pp+mass*mass) - mass;
		fParticleGun->SetParticleEnergy(Ekin);
		yPos = (G4UniformRand()-0.5)*30.0*cm;
		zPos = (G4UniformRand()-0.5)*30.0*cm;
		xPos = 25.0*cm;
		fParticleGun->SetParticlePosition(G4ThreeVector(xPos, yPos, zPos)); 
		
		theta = (G4UniformRand()-0.5)*sigmaAngle;
		phi = G4UniformRand()*360.*deg;
		yVec = std::sin(phi)*std::sin(theta);
		xVec = -std::cos(theta);
		zVec = std::cos(phi)*std::sin(theta);
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xVec, yVec, zVec));
		
		fParticleGun->GeneratePrimaryVertex(anEvent);
	    }
	} else {
	G4cout << "Dummy! you need to pick a proper event type. Choices are: 0, 1 or 2 for now." << G4endl;
    }

    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(20, pid);
    analysisManager->FillNtupleDColumn(21, Ekin);
    analysisManager->FillNtupleDColumn(22, xPos);
    analysisManager->FillNtupleDColumn(23, yPos);
    analysisManager->FillNtupleDColumn(24, zPos);
    analysisManager->FillNtupleDColumn(25, xVec);
    analysisManager->FillNtupleDColumn(26, yVec);
    analysisManager->FillNtupleDColumn(27, zVec);
    
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......	
