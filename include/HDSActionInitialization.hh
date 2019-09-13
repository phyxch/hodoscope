// Sep 13, 2019: hexc, James, Nadia, Ernesto, Denzel, Arfa
// Update the code with proper file names
//
#ifndef HDSActionInitialization_h
#define HDSActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class HDSDetectorConstruction;

/// Action initialization class.
///

class HDSActionInitialization : public G4VUserActionInitialization
{
  public:
    HDSActionInitialization(HDSDetectorConstruction*);
    virtual ~HDSActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    HDSDetectorConstruction* fDetConstruction;
};

#endif

    
