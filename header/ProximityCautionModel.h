#ifndef PROXIMITYCAUTIONMODEL
#define PROXIMITYCAUTIONMODEL
#include "_ForceModel.h"

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