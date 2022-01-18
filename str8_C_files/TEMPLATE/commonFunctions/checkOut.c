/*
    prints closing remarks to stdout
    - compiler versions present
    - run time (physical)
    - run time (processor)
    - date time stamp
    - completion message
*/

#include <stdio.h>    // printf(), __xx__ ...
#include <time.h>     // time_t , clock_t

#include "checkOut.h"    // declared here

#include "../resources/globalMacros.h"

// access to functions
#include "dateTimeStamp.h"
#include "timers.h"

// access to global variables
extern clock_t gv_startProcessingTime;
extern time_t gv_startRunningTime;
extern char gv_startDTS[U5_DTS];


void checkOut()
{
    printf("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    #ifdef __clang_major__
        printf("\ncompiler:  clang  ,  v %d.%d\n",
            __clang_major__ , __clang_minor__);
    #endif
    #ifdef __GNUC__
        printf("\ncompiler:  gcc  ,  v %d.%d\n",
            __GNUC__ , __GNUC_MINOR__);
    #endif
    
    char holdDTS[U5_DTS];
    dateTimeStamp(holdDTS);
    printf("\nBEGIN date-time-stamp:  %s\n", gv_startDTS);
    printf("\nEND date-time-stamp:    %s\n", holdDTS);
    printf("\nRunning time:           %0.3f  {seconds}\n", 
        timeRunning(gv_startRunningTime));
    printf("\nTotal processing time:  %0.6f  {seconds}\n", 
        timeProcessing(gv_startProcessingTime));
}

////////~~~~~~~~END>  checkOut.c
