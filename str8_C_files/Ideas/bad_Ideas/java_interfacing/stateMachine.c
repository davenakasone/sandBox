/*
    it will run through as usual, but go to directly populating "Location" struct
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "stateMachine.h"    // declared here
#include "programMacros.h"
#include "LocationStruct.h"
#include "javaInterface.h"

extern pthread_cond_t gv_readCond;
extern pthread_mutex_t gv_readMutex;
extern const float gc_start;
extern const float gc_stop;
extern const int gc_false;
extern const int gc_true;
extern int gv_waitTime_us;

static float randomFloat(float start, float stop);


void* runStateMachine(void* arg)
{
    Location* temp = NULL;
    temp = (Location*)arg;

    while(GPS_runEngine == VALID)
    {
        pthread_mutex_lock(&gv_readMutex);
        temp->isReady = gc_false;
        for (int i = 0; i < ELEMENTS_LOCATION_STRUCT; i++)
        {
            temp->data[i] = randomFloat(gc_start, gc_stop);
        }
        temp->isReady = gc_true;
        pthread_mutex_unlock(&gv_readMutex);
        pthread_cond_broadcast(&gv_readCond);
        usleep(DWELL_TIME);
    }

    temp = NULL;
    return NULL;
}


static float randomFloat(float start, float stop)
{
    if (start >= stop) { return INIT_FLOAT; }

    float diff = stop - start;
    float randF = ((float)rand()) / ((float)RAND_MAX );
    randF = (diff * randF) + start;
    return randF;
}


////////~~~~~~~~END>  stateMachine.c
