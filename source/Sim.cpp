#include <math.h>
Sim::Sim(int numberOfDrones, float initialDistBtwDrns)
{
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
                drones[i].
            }
        }
    }
}

Sim::~Sim()
{
}

void Sim::Run()
{
    while (true)
    {
    }
}
