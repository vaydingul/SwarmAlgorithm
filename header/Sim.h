#ifndef SIM
#define SIM
#include <vector>
#include "Drone.h"
#include <string>
#include <math.h>
#include <fstream>
#include <string>


/*

Sim

It is an concrete implementation of the 
Sim class. It basically governs the initial
orientation of the drones and maintains the
propagation of the main simulation.

*/

class Sim
{
public:
    Sim(float dt, float startTime, float finalTime, int numberOfDrones, float initialDistBtwDrns);
    ~Sim();
    void Run();
    void preStep();
    void Step();
    void postStep();
    void saveResults2CSV();
    

private:
    float dt;
    float startTime;
    float finalTime;
    int iter;
    float initialDistBtwDrns;
    int numberOfDrones;
    std::vector<Drone *> drones;
};
#include "../source/Sim.cpp"
#endif