/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 03:03:29
 */
#include <iostream>

Observer2::Observer2(_Observable *_observable)
{
    this->_observable = _observable;
    this->_observable->addObserver(this);
}

Observer2::~Observer2()
{
}

void Observer2::update()
{
    std::cout << "Observer 2 is being updated by main Observable\n";
}