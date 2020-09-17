/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 03:40:05
 */

#ifndef OBSERVER1
#define OBSERVER1

#include "_Observer.h"
#include "_Observable.h"

class Observer1 : public _Observer
{
public:
    _Observable *_observable;

    Observer1(_Observable *_observable);
    ~Observer1();
    void update() override;
};
#include "../source/Observer1.cpp"
#endif