/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 12:58:09
 */

#ifndef _OBSERVER
#define _OBSERVER

/*

_Observer

It is an abstract class to model 
the communation between drones.
It represents the ´slave´ receiver
in the communation.
*/

class _Observer
{
public:
    // Update the internal state
    virtual void update() = 0;
};
#include "../source/_Observer.cpp"
#endif