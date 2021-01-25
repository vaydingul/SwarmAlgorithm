#ifndef _FORCEMODEL
#define _FORCEMODEL
#include <vector>
#include "Drone.h"
/*

_ForceModel

It is an abstract class to model 
different force model.
Inheritance of this model provides
an abilitity to model different interactions
that might take place during the simulation.

*/
class _ForceModel
{
public:
    virtual std::vector<float> GetForce() = 0;
    virtual bool GetIsActive() = 0;
    // Calculation of the force based on the model
    virtual void calculate() = 0;
private:
    // Specify the model activation
    bool isActive;
    // Specify the force
    std::vector<float> force;
protected:
};
#include "../source/_ForceModel.cpp"
#endif