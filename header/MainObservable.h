/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-08 23:17:24
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 12:59:49
 */

#ifndef MAINOBSERVABLE
#define MAINOBSERVABLE

#include "_Observable.h"
#include "_Observer.h"

class MainObservable : public _Observable
{
public:
    void addObserver(_Observer *_observer) override;
    void removeObserver(_Observer *_observer) override;
    void notifyAll() override;
    void setChanged() override;
    void check() override;

private:
    std::vector<_Observer *> _observers;
    bool isChanged;
};
#include "../source/MainObservable.cpp"
#endif