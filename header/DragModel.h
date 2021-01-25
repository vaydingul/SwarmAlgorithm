#ifndef DRAGMODEL
#define DRAGMODEL

#include "_ForceModel.h"


/*

DragModel

It is an concrete implementation of the 
aerodynamic drag force model.

*/
class DragModel : public _ForceModel
{
public:
    // Constructor and destructor
    DragModel(Drone *, bool);
    ~DragModel();
    
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
#include "../source/DragModel.cpp"
#endif