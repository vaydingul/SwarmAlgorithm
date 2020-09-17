/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 03:16:58
 */

#include <iostream>

Observer3::Observer3(_Observable *_observable)
{
    this->_observable = _observable;
    this->_observable->addObserver(this);
}

Observer3::~Observer3()
{
}

void Observer3::update()
{
    std::cout << "Observer 3 is being updated by main Observable\n";
}