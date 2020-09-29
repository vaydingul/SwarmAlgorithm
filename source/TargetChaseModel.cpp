#include <math.h>

TargetChaseModel::TargetChaseModel(Drone *drn, bool isActive)
{
    this->SetDrone(drn);
    this->SetIsActive(isActive);
    this->SetForce({0.0, 0.0});
}

TargetChaseModel::~TargetChaseModel()
{
}

void TargetChaseModel::calculate()
{
    std::vector<float> targetForce(2), rTarget(2);
    std::vector<float> v = this->GetDrone()->GetVFinal();
    float vMag = 0;
    float rTargetMag = 0;

    for (int k = 0; k < 2; k++)
    {
        rTarget[k] = this->GetDrone()->GetTarget()[k] - this->GetDrone()->GetXFinal()[k];
        rTargetMag += pow(rTarget[k], 2);
        vMag += pow(v[k], 2);
    }
    vMag = sqrt(vMag);
    rTargetMag = sqrt(rTargetMag);

    for (int k = 0; k < 2; k++)
    {
        rTarget[k] /= rTargetMag;
        targetForce[k] = (rTargetMag * this->GetDrone()->GetTargetSpringCoeff() + vMag * this->GetDrone()->GetTargetDampingCoeff()) * rTarget[k];
    }

    this->SetForce(targetForce);
}

std::vector<float> TargetChaseModel::GetForce()
{
    
    return this->force;
}
void TargetChaseModel::SetIsActive(bool isActive)
{
    this->isActive = isActive;
}
bool TargetChaseModel::GetIsActive()
{
    return this->isActive;
}
void TargetChaseModel::SetDrone(Drone *drone)
{
    this->drone = drone;
}
Drone *TargetChaseModel::GetDrone()
{
    return this->drone;
}
void TargetChaseModel::SetForce(std::vector<float> force)
{
    this->force = force;
}
