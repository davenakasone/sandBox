/*
    timer utilities
    processing time != running time
    processing time depends on clock speed and task
    running time is simply elapsed time

    user selects start point,
        returns (current - start) as float, in seconds
    
    use gv_startProcessingTime or gv_startRunningTime
        for absolute time
*/

#include "timers.h"    // declared here

#include "../resources/globalMacros.h"


/*
    processing time required, in seconds
    time required by processor to complete task
*/
float timeProcessing(clock_t start)
{
    clock_t currentTime = clock();    // get the current time
    float processingTime = INIT_FLOAT;

    // cast difference in seconds, current time less specified starting time
    processingTime = ((float)currentTime - (float)start)/CLOCKS_PER_SEC;              

    return processingTime;    // how many processesing seconds were used so far
}


/*
    total elapsed time, in seconds
    as a stop-watch would record
*/
float timeRunning(time_t start)
{
    time_t currentTime = time(NULL);    // get the current time
    float runningTime = INIT_FLOAT;

    runningTime = (float)(currentTime - start);
    return runningTime;
}

////////~~~~~~~~END>  timers.c
