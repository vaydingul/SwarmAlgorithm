#include <math.h>

ProximityCautionModel::ProximityCautionModel(Drone *drn, bool isActive)
{

    /*

    Constructor for the proximity caution model.

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

ProximityCautionModel::~ProximityCautionModel()
{
    // Destructor
}

void ProximityCautionModel::calculate()
{

    /*

    Calculation of the proximity caution force, according to the following formula

    proximity_force = unit_distance_vector * proximity_coefficient * threshold_distance / distance_btw_drones

    Input:

        [] 

    */

    // Preallocation of force vector
    std::vector<float> proximityForce(2, 0.0);

    // Check for all other drones
    for (_Observer *obs : this->GetDrone()->Get_Observers())
    {
        // Cast ´drone´ type
        Drone *drn = (Drone *)obs;
        // Calculate the distance vector between drones
        std::vector<float> r = this->GetDrone()->calculateRVector(drn);
        // Calculate the magnitude of the distance vector
        float dist = Drone::calculateDistanceFromRVector(r);

        // If the distance between two drones is less than 
        // threshold value
        if (dist < this->GetDrone()->GetProximityCautionDistance())
        {

            // Then, exert a repulsive force
            for (int k = 0; k < 2; k++)
            {
                r[k] /= dist;
                proximityForce[k] += -r[k] * this->GetDrone()->GetProximityCoeff() * (this->GetDrone()->GetProximityCautionDistance() / dist);
            }
            //            this->GetDrone()->notify(drn, reqForce);
        }
    }       

            // Divide the total repulsive force vector to
            // number of proximity interactions
    for (int k = 0; k < 2; k++)
            {
                proximityForce[k] /= this->GetDrone()->GetProximityCount();
            }

    // Finally, set the force!
    this->SetForce(proximityForce);
}


// GETTERS AND SETTERS
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
