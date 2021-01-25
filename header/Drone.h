#ifndef DRONE
#define DRONE

#include "_Observable.h"
#include "_Observer.h"
#include "_ForceModel.h"

#include <vector>
#include <math.h>
#include <iostream>

/*

Drone

It is a concrete implementation of
the Drone model. It is a multiple combination 
of different classes to model self-sufficient 
communication model.

*/


class Drone : public _Observable, public _Observer
{
public:
    // Constructor and destructor
    Drone(std::vector<float>, std::vector<float>);
    ~Drone();
    // Propagation of the drone motion
    void propagate(float dt);
    void calculateForceModels();
    static std::vector<float> saturate(std::vector<float>, float);
    //COMMUNICATION PART
    void addObserver(_Observer *_observer) override;
    void removeObserver(_Observer *_observer) override;
    void notify(_Observer *_observer, std::vector<float>) override;
    void update() override;
    std::vector<_Observer *> Get_Observers();
    void Set_Observers(std::vector<_Observer *>);

    //GETTERS AND SETTERS
    std::vector<float> GetXFinal();
    std::vector<float> GetVFinal();
    std::vector<std::vector<float>> GetX();
    std::vector<std::vector<float>> GetV();

    int GetProximityCount();
    void SetProximityCount(int);
    float GetMass();
    void SetMass(float);
    float GetProximityCautionDistance();
    void SetProximityCautionDistance(float);
    float GetProximityCoeff();
    void SetProximityCoeff(float);
    float GetTargetSpringCoeff();
    void SetTargetSpringCoeff(float);
    float GetTargetDampingCoeff();
    void SetTargetDampingCoeff(float);
    float GetC_D();
    void SetC_D(float);
    float GetRho();
    void SetRho(float);
    float GetS();
    void SetS(float);

    std::vector<float> GetTarget();
    void SetTarget(std::vector<float>);

    std::vector<float> calculateRVector(Drone *);
    static float calculateDistanceFromRVector(std::vector<float>);

    std::vector<_ForceModel *> Get_ForceModels();
    void Set_ForceModels(std::vector<_ForceModel *>);
    void add_ForceModel(_ForceModel *);

private:

    // Massi position and velocity of the drone
    float mass;
    std::vector<std::vector<float>> x;
    std::vector<std::vector<float>> v;

    // Force model specific coefficients

    // ProximityCautionModel
    int proximityCount;
    float proximityCautionDistance;
    float proximityCoeff;

    // TargetChaseModel
    float targetSpringCoeff;
    float targetDampingCoeff;

    // DragModel
    float C_D;
    float rho;
    float S;

    
    std::vector<float> target;
    std::vector<_ForceModel *> _ForceModels;
    std::vector<_Observer *> _observers;
};
#include "DragModel.h"
#include "TargetChaseModel.h"
#include "ExternalForceModel.h"
#include "ProximityCautionModel.h"
#include "../source/Drone.cpp"

#endif