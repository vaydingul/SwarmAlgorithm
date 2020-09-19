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
    std::vector<float> calculateExternalForce();
    std::vector<float> saturate(std::vector<float>, float);
    //COMMUNICATION PART
    void addObserver(_Observer *_observer) override;
    void removeObserver(_Observer *_observer) override;
    void notify(_Observer *_observer, std::vector<float>) override;
    void update(std::vector<float>) override;

    //GETTERS AND SETTERS
    std::vector<float> GetXFinal();
    std::vector<float> GetVFinal();
    std::vector<std::vector<float>> GetX();
    std::vector<std::vector<float>> GetV();
    int GetProximityCount();
    void SetProximityCount(int);
    std::vector<float> GetProximityForce();
    void SetProximityForce(std::vector<float>);
    float GetMass();
    void SetMass(float);
    float GetProximityCautionDistance();
    void SetProximityCautionDistance(float);
    float GetProximityCoeff();
    void SetProximityCoeff(float);
    float GetTargetSpringCoeff();
    void SetTargetSpringCoeff(float );
    float GetTargetDampingCoeff();
    void SetTargetDampingCoeff(float );
    float GetC_D();
    void SetC_D(float);
    float GetRho();
    void SetRho(float);
    float GetS();
    void SetS(float);
    std::vector<float> GetTarget();
    void SetTarget(std::vector<float>);
    std::vector<_Observer *> Get_Observers();
    void Set_Observers(std::vector<_Observer *>);
    std::vector<float> calculateRVector(Drone *);
    float calculateDistanceFromRVector(std::vector<float>);
    void SetTargetChaseMode(bool);
    void SetProximityCautionMode(bool);
    void SetAerodynamicsEffectMode(bool);
    void SetExternalForceMode(bool);
    bool GetTargetChaseMode();
    bool GetProximityCautionMode();
    bool GetAerodynamicsEffectMode();
    bool GetExternalForceMode();
    void SetExternalForce(std::vector<float>);
    std::vector<float> GetExternalForce();

private:
    float mass;
    std::vector<std::vector<float>> x;
    std::vector<std::vector<float>> v;
    std::vector<float> proximityForce;
    std::vector<float> externalForce;
    int proximityCount;
    float proximityCautionDistance;
    float proximityCoeff;
    float targetSpringCoeff;
    float targetDampingCoeff;
    float C_D;
    float rho;
    float S;
    std::vector<float> target;
    bool targetChaseMode;
    bool proximityCautionMode;
    bool aerodynamicEffectMode;
    bool externalForceMode;

    

    std::vector<_Observer *> _observers;
};
#include "../source/Drone.cpp"
#endif