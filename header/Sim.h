#ifndef SIM
#define SIM
#include <vector>
#include "_Drone.h"
#include "Drone.h"
#include <string>
class Sim
{
public:
    Sim(int numberOfDrones, float initialDistBtwDrns);
    ~Sim();
    void Run();

private:
    float dt;
    float simTime;
    float initialDistBtwDrns;
    std::vector<Drone *> drones;
};
#include "../source/Sim.cpp"
#endif