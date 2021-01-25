#include <math.h>

TargetChaseModel::TargetChaseModel(Drone *drn, bool isActive)
{
    /*

    Constructor for the target chase model.

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

TargetChaseModel::~TargetChaseModel()
{
    // Destructor
}

void TargetChaseModel::calculate()
{

    /*

    Calculation of the target chase force, according to the following formula

    target_force = distance_vector * k + veclocity_vector * d

    Input:

        [] 

    */

    // Preallocation of the force vector, and the distance vector
    std::vector<float> targetForce(2), rTarget(2);
    // Get the final velocity of the drone
    std::vector<float> v = this->GetDrone()->GetVFinal();
    // Initialization of the velocity magnitude and the distance
    float vMag = 0;
    float rTargetMag = 0;

    for (int k = 0; k < 2; k++)
    {   
        // Calculation of the distance vector between target and subject drone
        rTarget[k] = this->GetDrone()->GetTarget()[k] - this->GetDrone()->GetXFinal()[k];
        rTargetMag += pow(rTarget[k], 2);
        // Calculation of the velocity magnitude
        vMag += pow(v[k], 2);
    }

    vMag = sqrt(vMag);
    rTargetMag = sqrt(rTargetMag);

    for (int k = 0; k < 2; k++)
    {
        // Calculation of the force based on the ´spring-damper-mass´ system
        rTarget[k] /= rTargetMag;
        targetForce[k] = (rTargetMag * this->GetDrone()->GetTargetSpringCoeff() + vMag * this->GetDrone()->GetTargetDampingCoeff()) * rTarget[k];
    }
    // Finally, set the force!
    this->SetForce(targetForce);
}


// GETTERS AND SETTERSs
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
