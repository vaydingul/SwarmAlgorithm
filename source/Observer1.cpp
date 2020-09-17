/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 03:41:33
 */
#include <iostream>

Observer1::Observer1(_Observable *_observable)
{
    this->_observable = _observable;
    this->_observable->addObserver(this);
}

Observer1::~Observer1()
{
}

void Observer1::update()
{
    std::cout << "Observer 1 is being updated by main Observable\n";
}
