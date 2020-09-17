#ifndef SIM
#define SIM
#include <vector>
#include "Drone.h"
#include <string>
class Sim
{
public:
    Sim(float dt, float startTime, float finalTime, int numberOfDrones, float initialDistBtwDrns);
    ~Sim();
    void Run();
    

private:
    float dt;
    float startTime;
    float finalTime;
    float initialDistBtwDrns;
    std::vector<Drone *> drones;
};
#include "../source/Sim.cpp"
#endif