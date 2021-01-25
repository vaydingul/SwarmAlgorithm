

DragModel::DragModel(Drone *drn, bool isActive)
{
    /*

    Constructor for the drag model.

    Input:

        drn = Subject drone
        isActive = Bool option to determine whether the force model will be active or not  

    */

    // Specify the drone
    this->SetDrone(drn);
    // Specify the activeness
    this->SetIsActive(isActive);
    // Specify the initial force
    this->SetForce({0.0, 0.0});
}

DragModel::~DragModel()
{
    // Destructor 
}

void DragModel::calculate()
{
    /*

    Calculation of the aerodynamic drag force, according to the following formula

    drag = 0.5 * air_density * velocity^2 * area * drag_coefficient

    Input:

        [] 

    */

    // Preallocation of the force vector
    std::vector<float> dragForce(2, 0.0);
    // Fetch velocity of the drone
    std::vector<float> v = this->GetDrone()->GetVFinal();
    // Calculate magnitude of the velocity
    float vMag = sqrt(pow(v[0], 2) + pow(v[1], 2));
    // Calculation of the drag force magnitude
    float dragForceMag = pow(vMag, 2) * 0.5 * this->GetDrone()->GetRho() * this->GetDrone()->GetS() * this->GetDrone()->GetC_D();
    // In the case of zero drag, it unstabilize the simulation,
    // therefore, there is a control condition here.
    if (vMag != 0.0)
    {
        for (int k = 0; k < 2; k++)
        {
            // If the drag force magnitude is not zero,
            // then project the magnitude to the axes.
            v[k] /= vMag;
            dragForce[k] = -dragForceMag * v[k];
        }
    }
    else
    {
        // If it is zero, then send zero vector
        dragForce = {0.0, 0.0};
    }

    // Finally, set the force!
    this->SetForce(dragForce);
}


// GETTERS AND SETTERS
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
