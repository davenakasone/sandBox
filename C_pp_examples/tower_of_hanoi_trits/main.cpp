/*
    20200911 use cmake, orgainize directories         make files is alright, but ancient
    oxygen is good for c++, spyth in python (no IDE)
    C line is IDE on Linux

    header file per class
    .cpp for implementation
    twitch for default constructor
    default parameter 

    use std::map, for those strings
    use the STL and other libs that are optimized

    publication->suscriber-> functional
    oop is not necaisallry better than funcitonal, just have to pick the place to implement
    co routine, functional, all same thing

    vector, auto ranging for loop...it will optimize great
    val grind is built into cline....memory audit
    every container from allocater....know what allocator is
    stateful lambdas ..use it for recursion. its great
    state machine library ....useful
    union is shared memory space
    a shared pointer of a certain data type, uses union to handle data type
    compiler exploer has profile tool
    threading is big now, lamda functions

    not only is recursion not allowed, but you can only move 1 space at a time (base 3)

      _ 0
     ___ 1
    _____ 2
      |       |       |
    peg_A   peg_B   peg_C   
*/

#include "toh_base3.h"
#include <chrono>

std::chrono::time_point<std::chrono::system_clock> g_START = std::chrono::system_clock::now(); // get current time
std::chrono::time_point<std::chrono::system_clock> dummy = std::chrono::system_clock::now();  // get current time
std::chrono::duration<double> g_DURATION = dummy - g_START;                      // initialize...should be about 0
double g_CURRENT = 0; // just to initialize, should hold current time based on duration in ns

const int DISCS = 4; // how many discs you want on your 3 towers   remeber there are 3^n - 1 moves...keep it below 20

void UPDATE(std::chrono::duration<double>& g_DURATION, double& g_CURRENT);
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    toh3 my_tower(DISCS); // object made, represents a tower with specified number of discs
    my_tower.run_tower();
    UPDATE(g_DURATION, g_CURRENT);
   
    return 0; 
}

//--------------------------------------------------------------------------------------------------------------------------
void UPDATE(std::chrono::duration<double>& g_DURATION, double& g_CURRENT)
{
    std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
    g_DURATION =  (current - g_START); // updates to new current time, based on ellapsed
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = std::chrono::duration_cast<std::chrono::nanoseconds>(g_DURATION);
    g_CURRENT = caster.count();
    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    std::cout << "\n           duration ~  { " << g_CURRENT << "  ns } ... ms = " << g_CURRENT * std::pow(10, -6);
}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================