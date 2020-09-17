/**
 * @ Author: vaydingul
 * @ Create Time: 2020-09-09 00:43:53
 * @ Modified by: vaydingul 
 * @ Modified time: 2020-09-09 13:45:43
 */
#include "header/_Observable.h"
#include "header/_Observer.h"
#include "header/MainObservable.h"
#include "header/Observer1.h"
#include "header/Observer2.h"
#include "header/Observer3.h"



int main()
{   
    _Observable *mo = new MainObservable;
    _Observer *o1 = new Observer1(mo);
    _Observer *o2 = new Observer2(mo);
    _Observer *o3 = new Observer3(mo);
    mo->check();
}