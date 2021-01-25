#include <math.h>
#include <chrono>
#include <random>
Sim::Sim(float dt, float startTime, float finalTime, int numberOfDrones, float initialDistBtwDrns)
{
    /*
        Simple constructor for the Sim class.

        Input:

            dt = Time step
            startTime = Start time
            finalTime = Final time
            numberOfDrones = Number of drones to be simulated  
            initialDistBtwDrns = Initial distance between drones



    */

    // Set the input arguments
    this->dt = dt;
    this->startTime = startTime;
    this->finalTime = finalTime;
    this->numberOfDrones = numberOfDrones;
    this->initialDistBtwDrns = initialDistBtwDrns;

    // Calculation of number of iterations based on the
    // - dt
    // - startTime
    // - finalTime
    // It is more healthy to do rather than while loop
    this->iter = (int)(((this->finalTime) - (this->startTime)) / (dt));

    // The following for-loop routine 
    // basically locates the drones
    // on the polygonal vertices.
    // The edge number of the polygon
    // equals to the number of drones.
    // Also, it provieds the construction of 
    // the drones based on the 
    // precalculated points of the vertices
    std::vector<float> point = {0, 0};
    float angle = 0.0;
    float angleIncrement = (360.0 / ((float)numberOfDrones)) * (3.1415 / 180.0);
    for (int k = 0; k < this->numberOfDrones; k++)
    {
        drones.push_back(new Drone(point, {0.0, 0.0}));
        point[0] += cos(angle) * this->initialDistBtwDrns;
        point[1] += sin(angle) * this->initialDistBtwDrns;
        angle += angleIncrement;
    }

    // This for-loop routine add each drones
    // to the other's observer list so as
    // to create communication infrastructre
    for (int i = 0; i < numberOfDrones; i++)
    {
        for (int k = 0; k < numberOfDrones; k++)
        {
            if (i != k)
            {
                drones[i]->addObserver(drones[k]);
            }
        }
    }
}

Sim::~Sim()
{
    //Destructor
}

void Sim::Run()
{
    /*

        Run

        It executes the whole simulation
        based on the three subparts, namely,
        preStep()
        Step()
        postStep()
        as much as number of iterations.
    */
    for (int k = 0; k < this->iter; k++)
    {
        this->preStep();
        this->Step();
        this->postStep();
    }
}

void Sim::preStep()
{
    /*

    preStep

    It calculates the required forces to 
    propagate the drones.


    */
    for (Drone *drn : this->drones)
    {
        drn->calculateForceModels();
    }
}

void Sim::Step()
{   

    /*

    Step

    It propagates one time-step all the drones.


    */
    for (Drone *drn : this->drones)
    {
        drn->propagate(this->dt);
    }
}

void Sim::postStep()
{   

    /*

    postStep

    It resets the proximity count of each drone
    to prevent overflow and underflow.



    */
    for (Drone *drn : this->drones)
    {
        drn->SetProximityCount(1);
    }

    // The drone list is shuffled in each iteration
    // to experience the undeterministic effect of the
    // real-life simulation
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(this->drones.begin(), this->drones.end(), std::default_random_engine(seed));
}

void Sim::saveResults2CSV()
{

    /*

    saveResults2CSV

    It saves the all position and velocity data of the drones
    to the seperate .csv files.

    There will a correspondent .csv file for
    each drone.

    */

    int i = 0;
    for (Drone *drn : this->drones)
    {
        std::string fname = "drones/" + std::to_string(i) + ".csv";
        std::cout << fname;
        std::ofstream file(fname, std::ofstream::out);
        std::vector<std::vector<float>> x, v;
        x = drn->GetX();
        v = drn->GetV();

        for (int k = 0; k < this->iter; k++)
        {
            file << x[k][0] << "," << x[k][1] << std::endl;
        }
        file.close();
        i++;
    }
}