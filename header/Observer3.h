/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 03:32:06
 */

#ifndef OBSERVER3
#define OBSERVER3

#include "_Observer.h"
#include "_Observable.h"

class Observer3 : public _Observer
{
public:
    _Observable *_observable;

    Observer3(_Observable *_observable);
    ~Observer3();
    void update() override;

private:
protected:
};
#include "../source/Observer3.cpp"
#endif