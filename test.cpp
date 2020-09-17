#include <iostream>

void fnc1(int *a, int *b)
{
    std::cout << "a = " << a << std::endl;
    std::cout << "*a = " << *a << std::endl;
    std::cout << "&a = " << &a << std::endl;

    std::cout << " b = " << b << std::endl;
    std::cout << "*b = " << *b << std::endl;
    std::cout << "&b = " << &b << std::endl;
}

void fnc2(int &a, int &b)
{
    std::cout << "a = " << a << std::endl;
    //std::cout << "*a = " << *a << std::endl;
    std::cout << "&a = " << &a << std::endl;

    std::cout << " b = " << b << std::endl;
    //std::cout << "*b = " << *b << std::endl;
    std::cout << "&b = " << &b << std::endl;
}

void fnc3(int a, int b)
{
    std::cout << "a = " << a << std::endl;
    //std::cout << "*a = " << *a << std::endl;
    std::cout << "&a = " << &a << std::endl;

    std::cout << " b = " << b << std::endl;
    //std::cout << "*b = " << *b << std::endl;
    std::cout << "&b = " << &b << std::endl;
}

int main()
{

    int a = 10;
    int b = 20;



    fnc1(&a, &b);
    fnc2(a, b);
    fnc3(a, b);
}