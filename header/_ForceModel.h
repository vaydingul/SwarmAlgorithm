#ifndef _FORCEMODEL
#define _FORCEMODEL
#include <vector>
#include "Drone.h"
class _ForceModel
{
public:
    virtual std::vector<float> fetchForce();

private:
    bool isActive;

protected:
};
#include "../source/_ForceModel.cpp"
#endif