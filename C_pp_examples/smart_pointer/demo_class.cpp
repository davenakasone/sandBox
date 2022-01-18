/*
    defining the class
*/

#include <iostream>

#include "demo_class.h"


demo::demo()
{
    std::cout << "\nconstructor invoked, instance of demo_class created\n";
}


////~~~~


demo::~demo()
{
    std::cout << "\ndestructor invoked, instance of demo_class destroyed\n";
}


////////~~~~~~~~END>  demo_class.cpp
