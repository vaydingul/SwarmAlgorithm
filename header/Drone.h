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
    std::vector<float> calculateProximityForce();

    //COMMUNICATION PART
    void addObserver(_Observer *_observer) override;
    void removeObserver(_Observer *_observer) override;
    void notify(_Observer *_observer, std::vector<float>) override;
    void update(std::vector<float>) override;

    //GETTERS AND SETTERS
    std::vector<float> getXFinal();
    std::vector<float> getVFinal();
    std::vector<std::vector<float>> getX();
    std::vector<std::vector<float>> getV();
    int getProximityCount();
    void SetProximityCount(int);
    std::vector<float> getProximityForce();
    void SetProximityForce(std::vector<float>);
    float GetMass();
    void SetMass(float);
    float GetProximityCautionDistance();
    void SetProximityCautionDistance(float);
    float GetProximityCoeff();
    void SetProximityCoeff(float);
    float GetTargetCoeff();
    void SetTargetCoeff(float );
    float GetC_D();
    void SetC_D(float);
    float GetRho();
    void SetRho(float);
    float GetS();
    void SetS(float);
    std::vector<float> GetGoToLocation();
    void SetGoToLocation(std::vector<float>);
    std::vector<_Observer *> get_Observers();
    void Set_Observers(std::vector<_Observer *>);
    std::vector<float> calculateRVector(Drone *);
    float calculateDistanceFromRVector(std::vector<float>);

private:
    float mass;
    std::vector<std::vector<float>> x;
    std::vector<std::vector<float>> v;
    std::vector<float> proximityForce;
    int proximityCount;
    float proximityCautionDistance;
    float proximityCoeff;
    float targetCoeff;
    float C_D;
    float rho;
    float S;
    std::vector<float> goToLocation;

    

    std::vector<_Observer *> _observers;
};
#include "../source/Drone.cpp"
#endif