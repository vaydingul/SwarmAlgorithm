/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 13:02:09
 */
#include <iostream>

void MainObservable::addObserver(_Observer *_observer)
{
    this->_observers.push_back(_observer);
}

void MainObservable::removeObserver(_Observer *_observer)
{
    std::vector<_Observer *>::iterator it = std::find(this->_observers.begin(), this->_observers.end(), _observer);
    if (it != this->_observers.end())
    {
        this->_observers.erase(it);
    }
}

void MainObservable::notifyAll()
{
    if (this->isChanged)
    {
        for (auto it = this->_observers.begin(); it != this->_observers.end(); ++it)
        {
            (*it)->update();
        }
        this->isChanged = false;
    }
}

void MainObservable::setChanged()
{
    this->isChanged = true;
}

void MainObservable::check()
{
    while (true)
    {
        int k;
        std::cin >> k;
        if (k % 5 == 0)
        {
            setChanged();
            notifyAll();
        }
    }
}