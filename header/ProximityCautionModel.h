#ifndef PROXIMITYCAUTIONMODEL
#define PROXIMITYCAUTIONMODEL
#include "_ForceModel.h"



/*

ProximityCautionModel

It is an concrete implementation of the 
proximity caution force model. It basically
prevents the collision between drones.

*/


class ProximityCautionModel : public _ForceModel
{
public:
    ProximityCautionModel(Drone *, bool);
    ~ProximityCautionModel();
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
#include "../source/ProximityCautionModel.cpp"
#endif