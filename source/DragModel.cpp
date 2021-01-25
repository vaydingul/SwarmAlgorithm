DragModel::DragModel(Drone *drn, bool isActive)
{
    this->SetDrone(drn);
    this->SetIsActive(isActive);
    this->SetForce({0.0, 0.0});
}

DragModel::~DragModel()
{
}

void DragModel::calculate()
{
    std::vector<float> dragForce(2, 0.0);
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

std::vector<float> DragModel::GetForce()
{
    return this->force;
}
void DragModel::SetIsActive(bool isActive)
{
    this->isActive = isActive;
}
bool DragModel::GetIsActive()
{
    return this->isActive;
}
void DragModel::SetDrone(Drone *drone)
{
    this->drone = drone;
}
Drone *DragModel::GetDrone()
{
    return this->drone;
}
void DragModel::SetForce(std::vector<float> force)
{
    this->force = force;
}
