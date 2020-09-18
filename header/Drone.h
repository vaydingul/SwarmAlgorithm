#ifndef DRONE
#define DRONE
#include "_Observable.h"
#include "_Observer.h"
#include <vector>
#include <math.h>
#include <iostream>
class Drone : public _Observable, public _Observer
{
public:
    Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial);
    ~Drone();
    void propagate(float dt);
    void checkProximity();

    //AERODYNAMIC ACTIVITY
    std::vector<float> calculateDrag();
    std::vector<float> calculateTargetForce();
    
    //COMMUNICATION PART
    void addObserver(_Observer *_observer) override;
    void removeObserver(_Observer *_observer) override;
    void notify(_Observer *_observer, std::vector<float>) override;
    void update(std::vector<float>) override;

    //GETTERS AND SETTERS
    std::vector<float> getX();
    std::vector<float> getV();
    std::vector<std::vector<float>> getXHistory();
    std::vector<std::vector<float>> getVHistory();
    std::vector<float> getR(Drone *);
    float getDistance(std::vector<float>);
    std::vector<float> getRequiredForce();
    void increaseProximityCount();
    void addRequiredForce(std::vector<float>);
    void resetProximityCount();
    void resetRequiredForce();

private:
    float mass;
    std::vector<std::vector<float>> x, v;
    std::vector<_Observer *> _observers;
    bool isChanged;
    std::vector<float> requiredForce;
    float proximityCount;
    float proximityCaution = 3;
    float proximityCoeff = 0.1;
    float targetCoeff = 0.1;
    float C_D = 1.5;
    float rho = 1.225;
    float S = 0.5;
    std::vector<float> goToLocation;
    
};
#include "../source/Drone.cpp"
#endif