// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names

#ifndef HDSPrimaryGeneratorAction_h
#define HDSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "HDSPrimaryGeneratorMessenger.hh"

#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gum.
///
/// It defines a single particle which hits the calorimeter 
/// perpendicular to the input face. The type of the particle
/// can be changed via the G4 build-in commands of G4ParticleGun class 
/// (see the macros provided with this example).

class HDSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    HDSPrimaryGeneratorAction();    
    virtual ~HDSPrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event* event);
    
    // set methods
    void SetRandomFlag(G4bool value);
    void SetEventType(G4int eventType) { ev_type = eventType; };
    
private:
    G4ParticleGun*  fParticleGun; // G4 particle gun
    HDSPrimaryGeneratorMessenger* gunMessenger;
    G4int ev_type, evtID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
