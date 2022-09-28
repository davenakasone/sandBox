/*
    isolate for extern
        gc_ global constants
        gv_ global variables
        gs_ global structs
*/

#include <pthread.h>

#include "programGlobals.h"       // decleared here
#include "LocationStruct.h"       // "Location" type struct


Location gs_location;

pthread_t gv_engineThread;
pthread_mutex_t gv_readMutex;
pthread_cond_t gv_readCond;

const float gc_start = 10.001;
const float gc_stop = 99.999;

const int gc_false = 0;
const int gc_true = 1;

////////~~~~~~~~END>  programGlobals.c
