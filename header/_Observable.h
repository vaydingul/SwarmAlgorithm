/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 13:05:37
 */

#ifndef _OBSERVABLE
#define _OBSERVABLE

#include "_Observer.h"
#include <vector>
#include <algorithm>

class _Observable
{
public:

    virtual void addObserver(_Observer *_observer) = 0;
    virtual void removeObserver(_Observer *_observer) = 0;
    virtual void check() = 0;
    virtual void notifyAll() = 0;
    virtual void setChanged() = 0;
};

#include "../source/_Observable.cpp"
#endif