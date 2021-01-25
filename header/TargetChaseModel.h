#ifndef TARGETCHASEMODEL
#define TARGETCHASEMODEL
#include "_ForceModel.h"

class TargetChaseModel : public _ForceModel
{
public:
    TargetChaseModel(Drone *, bool);
    ~TargetChaseModel();
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
#include "../source/TargetChaseModel.cpp"
#endif