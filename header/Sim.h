#ifndef SIM
#define SIM
#include <vector>
#include "Drone.h"
#include <string>
#include <math.h>
class Sim
{
public:
    Sim(float dt, float startTime, float finalTime, int numberOfDrones, float initialDistBtwDrns);
    ~Sim();
    void Run();
    void checkProximity(Drone *drn1, Drone *drn2);

    

private:
    float dt;
    float startTime;
    float finalTime;
    float initialDistBtwDrns;
    float proximityCaution = 3;
    float forceCoeff = 0.1;
    std::vector<Drone *> drones;
};
#include "../source/Sim.cpp"
#endif