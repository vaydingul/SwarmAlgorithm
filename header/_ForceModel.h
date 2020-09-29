#ifndef _FORCEMODEL
#define _FORCEMODEL
#include <vector>
#include "Drone.h"
class _ForceModel
{
public:
    virtual std::vector<float> GetForce() = 0;
    virtual bool GetIsActive() = 0;
    virtual void calculate() = 0;
private:
    bool isActive;
    std::vector<float> force;
protected:
};
#include "../source/_ForceModel.cpp"
#endif