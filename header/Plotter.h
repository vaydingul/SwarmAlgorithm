#ifndef PLOTTER
#define PLOTTER
#include "_Observer.h"
#include "_Observable.h"
class Plotter : public _Observer
{
public:
    void update();

private:
    _Observable *observable;
};
#include "../source/Plotter.cpp"
#endif