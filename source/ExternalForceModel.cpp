#include <math.h>

ExternalForceModel::ExternalForceModel(Drone *drn, bool isActive)
{
    this->SetDrone(drn);
    this->SetIsActive(isActive);
    this->SetForce({0.0, 0.0});
}

ExternalForceModel::~ExternalForceModel()
{
}

void ExternalForceModel::calculate()
{
    std::vector<float> externalForce(2, 0.0);

    

    this->SetForce(externalForce);
}

std::vector<float> ExternalForceModel::GetForce()
{
    
    return this->force;
}
void ExternalForceModel::SetIsActive(bool isActive)
{
    this->isActive = isActive;
}
bool ExternalForceModel::GetIsActive()
{
    return this->isActive;
}
void ExternalForceModel::SetDrone(Drone *drone)
{
    this->drone = drone;
}
Drone *ExternalForceModel::GetDrone()
{
    return this->drone;
}
void ExternalForceModel::SetForce(std::vector<float> force)
{
    this->force = force;
}
