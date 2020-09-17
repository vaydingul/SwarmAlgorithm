/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 02:28:36
 */

#ifndef OBSERVER2
#define OBSERVER2

#include "_Observer.h"
#include "_Observable.h"

class Observer2 : public _Observer
{
public:
    _Observable *_observable;

    Observer2(_Observable *_observable);
    ~Observer2();
    void update() override;

private:
protected:
};
#include "../source/Observer2.cpp"
#endif