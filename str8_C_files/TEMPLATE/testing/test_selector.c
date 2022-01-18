/*
    match the testing unit to switch selector
    stores test options as made
    reserve "0" for the test bench

    seeds random number generator and 
    provides entry-->exit for testing

    !!! must have valid selection, no default
*/

#include <stdio.h>     // printf() 
#include <stdlib.h>    // NULL , srand() , system()
#include <time.h>      // time() , clock() , time_t , clock_t

#include "testing.h"    // declared here

#include "../commonFunctions/timers.h"


void test_selector(int selection)
{
    clock_t pt = clock();      // processor starting time
    time_t rt = time(NULL);    // start of running time, physical
    system("clear");
    srand(time(NULL));         // seed pseudo random number generator
    printf("\nTEST^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^TEST\n");

    switch(selection)
    {
        case(0) :
            testBench();
            break;

        case(1) :
            tu_dateTimeStamp();
            break;
        
        case(2) :
            tu_makeNumbers();
            break;
    }

    printf("\nTEST^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^TEST\n");
    printf("\t\t*** testing complete ***\n");
    printf("\tprocessing time:  %0.6f  {seconds}\n",
        timeProcessing(pt));
    printf("\trunning time:     %0.3f     {seconds}",
        timeRunning(rt));
    printf("\nTEST^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^TEST\n");
}

////////~~~~~~~~END>  test_selector.c

