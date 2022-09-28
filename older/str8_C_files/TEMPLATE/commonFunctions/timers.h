/*
    include this header for:
        timeProcessing()
        timeRunning()
*/

#ifndef H_timers
#define H_timers

#include <time.h>    // clock_t , CLOCKS_PER_SEC , clock()

float timeProcessing(clock_t start);
float timeRunning(time_t start);

#endif

////////~~~~~~~~END>  timers.h
