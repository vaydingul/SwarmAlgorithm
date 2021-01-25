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

/*

_Observable

It is an abstract class to model 
the communation between drones.
It represents the ´master´ emitter
in the communation.
*/



class _Observable
{
public:

    // The method to add observer to the observer list
    virtual void addObserver(_Observer *_observer) = 0;
    // The method to remove observer from the observer list
    virtual void removeObserver(_Observer *_observer) = 0;
    // Notification tool
    virtual void notify(_Observer *_observer, std::vector<float>) = 0;
};

#include "../source/_Observable.cpp"
#endif