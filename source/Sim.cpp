#include <math.h>

Sim::Sim(float dt, float startTime, float finalTime, int numberOfDrones, float initialDistBtwDrns)
{
    this->dt = dt;
    this->startTime = startTime;
    this->finalTime = finalTime;
    this->numberOfDrones = numberOfDrones;
    this->initialDistBtwDrns = initialDistBtwDrns;
    this->iter = (float)(((this->finalTime) - (this->startTime)) / (dt));

    std::vector<float> point = {0, 0};
    float angle = 0.0;
    float angleIncrement = (360.0 / ((float)numberOfDrones)) * (3.14 / 180.0);

    for (int k = 0; k < this->numberOfDrones; k++)
    {
        drones.push_back(new Drone(1, point, {0, 0}));
        point[0] += cos(angle) * this->initialDistBtwDrns;
        point[1] += sin(angle) * this->initialDistBtwDrns;
        angle += angleIncrement;
    }

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
}

void Sim::Run()
{

    for (int k = 0; k < this->iter; k++)
    {
        this->preStep();
        this->Step();
        this->postStep();
    }
}

void Sim::preStep()
{

    for (Drone *drn : this->drones)
    {
        drn->checkProximity();
    }
}

void Sim::Step()
{
    for (Drone *drn : this->drones)
    {
        drn->propagate(this->dt);
    }
}

void Sim::postStep()
{
    for (Drone *drn : this->drones)
    {
        drn->SetProximityForce({0.0, 0.0}); // It allocates the sufficient memory for required force
        drn->SetProximityCount(0);
    }
}

void Sim::saveResults2CSV()
{
    int i = 0;
    for (Drone *drn : drones)
    {
        std::string fname = "drones/" + std::to_string(i) + ".csv";
        std::cout << fname;
        std::ofstream file(fname, std::ofstream::out);
        std::vector<std::vector<float>> x, v;
        x = drn->getX();
        v = drn->getV();

        for (int k = 0; k < this->iter; k++)
        {
            file << x[k][0] << "," << x[k][1] << std::endl;
        }
        file.close();
        i++;
    }
}