#include <math.h>

ProximityCautionModel::ProximityCautionModel(Drone *drn, bool isActive)
{
    this->SetDrone(drn);
    this->SetIsActive(isActive);
    this->SetForce({0.0, 0.0});
}

ProximityCautionModel::~ProximityCautionModel()
{
}

void ProximityCautionModel::calculate()
{
    std::vector<float> proximityForce(2, 0.0);

    for (_Observer *obs : this->GetDrone()->Get_Observers())
    {
        Drone *drn = (Drone *)obs;
        std::vector<float> r = this->GetDrone()->calculateRVector(drn);
        float dist = Drone::calculateDistanceFromRVector(r);
        if (dist < this->GetDrone()->GetProximityCautionDistance())
        {

            for (int k = 0; k < 2; k++)
            {
                r[k] /= dist;
                proximityForce[k] += -r[k] * this->GetDrone()->GetProximityCoeff() * (this->GetDrone()->GetProximityCautionDistance() / dist);
            }
            //            this->GetDrone()->notify(drn, reqForce);
        }
    }
    for (int k = 0; k < 2; k++)
            {
                proximityForce[k] /= this->GetDrone()->GetProximityCount();
            }

    this->SetForce(proximityForce);
}

std::vector<float> ProximityCautionModel::GetForce()
{
    
    return this->force;
}
void ProximityCautionModel::SetIsActive(bool isActive)
{
    this->isActive = isActive;
}
bool ProximityCautionModel::GetIsActive()
{
    return this->isActive;
}
void ProximityCautionModel::SetDrone(Drone *drone)
{
    this->drone = drone;
}
Drone *ProximityCautionModel::GetDrone()
{
    return this->drone;
}
void ProximityCautionModel::SetForce(std::vector<float> force)
{
    this->force = force;
}
