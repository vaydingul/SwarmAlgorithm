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

    for (_Observer *obs : this->GetDrone()->Get_Observers())
    {
        Drone *drn = (Drone *)obs;
        std::vector<float> reqForce(2, 0.0);
        std::vector<float> r = this->calculateRVector(drn);
        float dist = this->calculateDistanceFromRVector(r);
        if (dist < this->GetProximityCautionDistance())
        {

            for (int k = 0; k < 2; k++)
            {
                r[k] /= dist;
                reqForce[k] = r[k] * this->proximityCoeff * (this->GetProximityCautionDistance() / dist);
            }
            this->GetDrone()->notify(drn, reqForce);
        }
        else
        {
            this->notify(drn, {0.0, 0.0});
        }
    }

    std::vector<float> proximityForce(2, 0.0);
    std::vector<float> v = this->GetDrone()->GetVFinal();
    float vMag = sqrt(pow(v[0], 2) + pow(v[1], 2));

    float dragForceMag = pow(vMag, 2) * 0.5 * this->GetDrone()->GetRho() * this->GetDrone()->GetS() * this->GetDrone()->GetC_D();
    if (vMag != 0.0)
    {
        for (int k = 0; k < 2; k++)
        {
            v[k] /= vMag;
            dragForce[k] = -dragForceMag * v[k];
        }
    }
    else
    {
        dragForce = {0.0, 0.0};
    }
    this->SetForce(dragForce);
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
