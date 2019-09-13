// This is the primary generator messenger class for cosmic ray telescope simulation
// Created on August 8/21/2019: hexc, James and Nadia
//    As a starter, we want to implement an option for selecting different event generator types
//        ev_type = 0     for arbitrary single particle
//        ev_type = 1     cosmic ray muons
//        ev_type = 2     cosmic ray neutrons 
//
// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names

#ifndef HDSPrimaryGeneratorMessenger_h
#define HDSPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HDSPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HDSPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  HDSPrimaryGeneratorMessenger(HDSPrimaryGeneratorAction*);
  ~HDSPrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  HDSPrimaryGeneratorAction* HDSAction;
  G4UIdirectory*               gunDir; 
  G4UIcmdWithAnInteger*        newEventType;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
