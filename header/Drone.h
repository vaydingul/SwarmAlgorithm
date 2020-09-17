#ifndef DRONE
#define DRONE
#include "_Drone.h"
#include "_Observable.h"
#include "_Observer.h"
#include <vector>
class Drone : public _Observable, public _Observer
{
public:
    Drone(float mass, std::vector<float> x_initial, std::vector<float> v_initial);
    ~Drone();
    void applyForce(std::vector<float> force, float dt);
    void addObserver(_Observer *_observer) override;
    void removeObserver(_Observer *_observer) override;
    void check() override;
    void notifyAll() override;
    void setChanged() override;
    void update() override;
private:
    float mass;
    std::vector<std::vector<float>> x, v;
    std::vector<_Observer *> _observers;
    bool isChanged;
    _Observable *_observable;
};
#include "../source/Drone.cpp"
#endif