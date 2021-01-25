#include "header/Sim.h"
#include "header/Drone.h"

int main()
{   
    // It deletes the previously created .csv files
    std::system("python deleteCsv.py");
    // Time step
    float dt = 1e-2;
    // Start and final time of the simulation
    float startTime = 0.0;
    float finalTime = 10000.0;

    // Number of drones to be created
    int numberOfDrones = 1;

    // Initial distribution between drones
    float initialDistBtwDrns = 2.0;

    // New Sim entity
    Sim *sim = new Sim(dt, startTime, finalTime, numberOfDrones, initialDistBtwDrns);

    // Execution of the simulation
    sim->Run();

    // Save results to the csv file
    sim->saveResults2CSV();
}
