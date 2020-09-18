#include "header/Sim.h"
#include "header/Drone.h"

int main()
{

    std::system("python deleteCsv.py");
    float dt = 1e-2;
    float startTime = 0.0;
    float finalTime = 100.0;
    int numberOfDrones = 3;
    float initialDistBtwDrns = 20.0;
    Sim *sim = new Sim(dt, startTime, finalTime, numberOfDrones, initialDistBtwDrns);
    sim->Run();
    sim->saveResults2CSV();
    
}   