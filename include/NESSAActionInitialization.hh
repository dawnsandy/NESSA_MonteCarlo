#ifndef NESSAActionInitialization_h
#define NESSAActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class NESSAActionInitialization : public G4VUserActionInitialization
{
public:
    NESSAActionInitialization() = default;
    ~NESSAActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
};

#endif
