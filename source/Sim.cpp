#include <math.h>

Sim::Sim(float dt, float startTime, float finalTime, int numberOfDrones, float initialDistBtwDrns)
{
    this->dt = dt;
    this->startTime = startTime;
    this->finalTime = finalTime;

    std::vector<float> point = {0, 0};
    float angle = 0.0;
    float angleIncrement = (360.0 / ((float)numberOfDrones)) * (3.14 / 180.0);

    for (int k = 0; k < numberOfDrones; k++)
    {
        drones.push_back(new Drone(1, point, {0, 0}));
        point[0] *= cos(angle);
        point[1] *= sin(angle);
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
    int iter = (((int)this->finalTime) - ((int)this->startTime)) / ((int)dt);
    for (int k = 0; k < iter; k++)
    {
        for (Drone *drn1 : drones)
        {
            for (Drone *drn2 : drones)
            {
                if (drn1 != drn2)

                {
                    checkProximity(drn1, drn2);
                }
            }
        }
    }
}

void Sim::checkProximity(Drone *drn1, Drone *drn2)
{
    std::vector<float> r;
    float dist = 0.0;
    for (int k = 0; k < 2; k++)
    {
        r[k] = drn1->getX()[k] - drn2->getX()[k];
        dist += pow(r[k], 2);
    }

    if (dist < this->proximityCaution)
    {
        std::vector<float> reqForce;
        for (int k = 0; k < 2; k++)
        {
            reqForce[k] = r[k] * dist * this->forceCoeff;
        }
        // TODO: Simulationın kendisinin bir timestep atlatmasına izin ver.
        // TODO: Bide Observable/Observer altyapısını kullanmaya çalış boşa gidecek yoksa ;(
    }
}