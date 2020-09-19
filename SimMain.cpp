#include "header/Sim.h"
#include "header/Drone.h"

int main()
{
    std::system("python deleteCsv.py");
    float dt = 1e-1;
    float startTime = 0.0;
    float finalTime = 1000.0;
    int numberOfDrones = 2;
    float initialDistBtwDrns = 2.9;
    Sim *sim = new Sim(dt, startTime, finalTime, numberOfDrones, initialDistBtwDrns);
    sim->Run();
    sim->saveResults2CSV();
    
}   