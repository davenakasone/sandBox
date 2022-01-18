/*
    SM_3 :    similar to SM_2
            but, a timed wait will help avoid the hang (in theory)
    
    like regular _wait() , pthread_cond_timedwait() blocks calling thread on cond var
    it will unlock the associated mutex (must have a lock before calling)
    when a signal OR time expires,
    caller owns the mutex and it is locked

    remember waiting on a signal or broadcast is a cancelation point
        so: timeout, get signal, or cancelled will stop the blocking
    
    CLOCK_MONOTONIC only advances and won't be changed by system
        don't use default CLOCK_REAL_TIME
    
    also remember not to use recursive mutex with condition vars

    #include <time.h>

    struct timespec
    {
        time_t tv_sec;    // seconds
        long tv_nsec;     // nano seconds
    };

    be careful to advance the timer, then decrement...
        don't want to keep incrementing and overflow
    
    say no to EOK, just use 0
    say no to nanospin(), unless you have a need
    gettimeofday() is ok for
*/

#include "resourcez.h"    // everything
#ifdef SM_3


int initializeEngine3()
{
    printf("\n%s()  ,  wait and signal with some delays...\n", 
        __func__);
    sM.idx = 0;
    sM.readReady = false;
    sM.runFlag = true;
    memset(sM.data, '\0', STR_SIZE);
    timer.tv_sec = 0;
    timer.tv_nsec = 0;
    
    // initialize threading resources
    gv_status = pthread_cond_init(&sM.engineCond, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error initializing cond  ,  status:  %d\n",
            __func__, gv_status); return gv_status;
    }
    gv_status = pthread_mutex_init(&sM.engineMutex, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error initializing mutex  ,  status:  %d\n",
            __func__, gv_status); return gv_status;
    }
    gv_status = pthread_attr_init(&sM.engineAttr);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error initializing attr  ,  status:  %d\n",
            __func__, gv_status); return gv_status;
    }
    gv_status = pthread_attr_setdetachstate(&sM.engineAttr,
        PTHREAD_CREATE_DETACHED);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error setting attr  ,  status:  %d\n",
        __func__, gv_status); return gv_status;
    }

    // start the detached thread
    gv_status = pthread_create(&sM.engineThread, 
        &sM.engineAttr, &stateMachine3, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error creating thread\n", __func__);
        return gv_status;
    }
    return GOOD;
}


int readEngine3()
{
    printf("\n\t%s()  ,  attempt read with pthread_cond_timedwait()\n", 
        __func__);
    char temp[STR_SIZE];
    memset(temp, '\0', STR_SIZE);
    struct timespec stcTS;
    struct timeval stcTV;

    gv_status = pthread_mutex_lock(&sM.engineMutex);
    printf("\n\t%s()  ,  mutex locked status:  %d\n", __func__, gv_status);

    while(1)
    {
        gv_status = gettimeofday(&stcTV, NULL);
        if (gv_status != 0) {printf("\n\t%s()  ,  error getting time\n", __func__);}
        stcTS.tv_sec = stcTV.tv_sec + 1;
        stcTS.tv_nsec = stcTS.tv_nsec + 
                        (stcTV.tv_usec * 1000);// + 
                        //((rand() % US_PER_SEC) * 1000);

        while(sM.readReady == true)
        {
            printf("\n\t%s()  ,  thread blocked...\n", __func__);
            gv_status = pthread_cond_timedwait(&sM.engineCond, &sM.engineMutex, &stcTS);

            if (gv_status == ETIMEDOUT )//||
                //gv_status != 0          )
            {
                printf("\n\t%s()  ,  timed out\n", __func__);
                gv_status = pthread_mutex_unlock(&sM.engineMutex);    // very important
                printf("\n\t%s()  ,  unlock status:  %d\n", 
                        __func__, gv_status);
                usleep_proper(READ_DELAY_US);    // pause in case of frequent calls
                return (-1*GOOD);

            }
            else
            {
                strncpy(temp, sM.data, STR_SIZE);
                printf("\n\t\textracted:   { %s }\n", temp);
                gv_status = pthread_mutex_unlock(&sM.engineMutex);    // very important
                printf("\n\t%s()  ,  unlock status:  %d\n", 
                        __func__, gv_status);
                usleep_proper(READ_DELAY_US);    // pause in case of frequent calls
                return GOOD;
            }
        }
        return (-1*GOOD);
    }
}


void* stateMachine3(void* arg)
{
    printf("\n%s()  ,  engine starts\n\n", __func__);
    bool shouldLock = true;    // important to control

    while (sM.runFlag == true)
    {
        if (shouldLock == true)
        {
            gv_status = pthread_mutex_lock(&sM.engineMutex);
            printf("\t%s()  ,  mutex locked  ,  status:  %d\n", 
                __func__, gv_status);
            shouldLock = false;
        }
        
        if (sM.idx > STR_SIZE-1) {resetStruct(&sM);}

        sM.data[sM.idx] = getChar();

        sM.idx++;

        if (sM.idx == STR_SIZE-1)
        {
            shouldLock = true;
            sM.data[sM.idx] = '\0';
            sM.readReady = true;
            printf("\t\t{ %s }  ,  unlocking mutex  ,", sM.data);
            gv_status = pthread_mutex_unlock(&sM.engineMutex);
            printf("  status:  %d\n", gv_status);
            gv_status = pthread_cond_signal(&sM.engineCond);    // inform other
            usleep( (rand() % US_PER_SEC) ); 
            printf("\t\t\tsignal---*\n");
        }
    }

    if (shouldLock == false)    // safety, the mutex is locked
    {
        pthread_mutex_unlock(&sM.engineMutex);
    }
    printf("\n%s()  ,  loop EXIT engine stops\n", __func__);
    pthread_exit(NULL);    // or return NULL;
}


int haltEngine3()
{
    printf("\n\t%s()  ,  freeing resources...\n", __func__);

    gv_status = pthread_mutex_lock(&sM.engineMutex);
    printf("\n\t%s()  ,  mutex lock status:  %d\n",
        __func__, gv_status);

    sM.runFlag = false;

    gv_status = pthread_mutex_unlock(&sM.engineMutex);
    printf("\n\t%s()  ,  flagged to stop  ,  mutex unlock status:  %d\n", 
        __func__, gv_status);
    usleep_proper(READ_DELAY_US*10);    // give detached thread time to clear loop and free

    // clean up
    gv_status = pthread_attr_destroy(&sM.engineAttr);
    if (gv_status != 0)
    {
        printf("\n\t%s()  ,  error destroying attr ,  status:  %d\n",
            __func__, gv_status);
    }
    gv_status = pthread_cond_destroy(&sM.engineCond);
    if (gv_status != 0)
    {
        printf("\n\t%s()  ,  error destroying cond  ,  status:  %d\n",
            __func__, gv_status);
    }
    gv_status = pthread_mutex_destroy(&sM.engineMutex);
    if (gv_status != 0)
    {
        printf("\n\t%s()  ,  error destroying mutex  ,  status:  %d\n",
            __func__, gv_status);
    }

    printf("\n\t%s()  ,  engine STOPPED\n", __func__);
    return GOOD;
}

#endif

////////~~~~~~~~END>  ut_3_timedwait.c
