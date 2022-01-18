/*
    implementing the API
*/

#include <pthread.h>
#include <stdio.h>

#include "javaInterface.h"        // declared here
#include "stateMachine.h"

extern pthread_t gv_engineThread;
extern pthread_cond_t gv_readCond;
extern pthread_mutex_t gv_readMutex;
extern const int gc_false;
extern const int gc_true;
extern Location gs_location; 


int GPS_initializeEngine(const char* serialPath)
{
    if (serialPath == NULL) // make sure it can open
    {
        printf("%s()  ,  error in serial path:  %s\n", 
            __func__, serialPath);
        return INIT_INT;
    }

    printf("\n%s()  ,  initializing engine  ,  fd:  %s\n", 
        __func__, serialPath);
    metInit(&gs_location);

    GPS_runEngine = VALID;
    pthread_mutex_init(&gv_readMutex, NULL);
    pthread_cond_init(&gv_readCond, NULL);
    
    // open the serial path and return an error if it fails

    if (pthread_create(&gv_engineThread, NULL, &runStateMachine, (void*)&gs_location) != 0)
    {
        printf("\n%s()  ,  failed to create thread\n", __func__);
        return INVALID;
    }
    return VALID;
}


int GPS_readLocationStruct(Location * ptr)
{
    if (ptr == NULL) {return INIT_INT;}

    int status = INVALID;
    pthread_mutex_lock(&gv_readMutex);
    if (gs_location.isReady == gc_true)
    {
        metCopy(&gs_location, ptr);
        printf("\n%s()  ,  struct IS ready  ,  deep copy...\n", __func__);
        metInit(&gs_location); // reset struct
        status = VALID;
    }
    else
    {
        printf("\n%s()  ,  struct NOT ready  ,  returning...\n", __func__);
    }
    pthread_mutex_unlock(&gv_readMutex);
    return status;
}


int GPS_haltEngine(void)
{
    pthread_mutex_lock(&gv_readMutex);
    printf("\n%s()...\n", __func__);
    GPS_runEngine = INVALID;
    pthread_mutex_unlock(&gv_readMutex);

    pthread_cond_broadcast(&gv_readCond);
    metInit(&gs_location);
    
    int status = VALID;
    if (pthread_join(gv_engineThread, NULL) != 0)
    {
        printf("\n%s()  ,  error joining thread\n", __func__);
        status = INVALID;
    }

    // close the serial terminal
    
    pthread_cond_destroy(&gv_readCond);
    pthread_mutex_destroy(&gv_readMutex);
    return status;
}

////////~~~~~~~~END>  javaInterface.c
