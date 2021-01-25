#ifndef EXTERNALFORCEMODEL
#define EXTERNALFORCEMODEL
#include "_ForceModel.h"



/*

ExternalForceModel

It is an concrete implementation of the 
external force model.

*/
class ExternalForceModel : public _ForceModel
{
public:
    ExternalForceModel(Drone *, bool);
    ~ExternalForceModel();
    std::vector<float> GetForce() override;
    void calculate() override;

    void SetIsActive(bool);
    bool GetIsActive() override;
    void SetDrone(Drone *);
    Drone *GetDrone();
    void SetForce(std::vector<float>);

private:
    bool isActive;
    std::vector<float> force;
    Drone *drone;
};
#include "../source/ExternalForceModel.cpp"
#endif