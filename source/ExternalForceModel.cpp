#include <math.h>

ExternalForceModel::ExternalForceModel(Drone *drn, bool isActive)
{
    
    /*

    Constructor for the external force model.

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

ExternalForceModel::~ExternalForceModel()
{
    // Destructor
}

void ExternalForceModel::calculate()
{

    /*

    Calculation of the external force.

    Input:

        [] 

    */

    // Preallocation of the force vector
    std::vector<float> externalForce(2, 0.0);
    // Fibally, set the force!
    this->SetForce(externalForce);
}


// GETTERS AND SETTERS
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
