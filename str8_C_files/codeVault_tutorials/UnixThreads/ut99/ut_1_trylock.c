/*
    SM_1 : basic pthread_mutex_trylock(), minimal control
                engine must wait after unlocking, gives chance to read
                ensuring read assisted if long wait after unlock
                reading should pause in case multiple reads are called
            very good for skipping, won't hang if state machine fails
        
        but fails if called before the delay (reads same data)
            this methods is all about timing
        
        ie, disable MAKE_READ_DELAY and it fails

    fyi, putting this in a loop would result in similar dead lock / race
        while(status != 0)
        {
            status = pthread_mutex_trylock(&sM.engineMutex);
        }
    
    ...could just do a complete block with _lock() instead of _trylock()
*/

#include "resourcez.h"    // everything
#ifdef SM_1


int initializeEngine1()
{
    printf("\n%s()  ,  a simple pthread_mutex_trylock() with some delays...\n", 
        __func__);
    sM.idx = 0;
    sM.readReady = false;
    sM.runFlag = true;
    memset(sM.data, '\0', STR_SIZE);
    
    // initialize threading resources
    gv_status = pthread_mutex_init(&sM.engineMutex, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error initializing mutex  ,  status:  %d\n",
            __func__, gv_status);
    }
    gv_status = pthread_attr_init(&sM.engineAttr);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error initializing attr  ,  status:  %d\n",
            __func__, gv_status);
        return gv_status;
    }
    gv_status = pthread_attr_setdetachstate(&sM.engineAttr,
        PTHREAD_CREATE_DETACHED);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error setting attr  ,  status:  %d\n",
        __func__, gv_status);
        return gv_status;
    }

    // start the detached thread
    gv_status = pthread_create(&sM.engineThread, 
        &sM.engineAttr, &stateMachine1, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error creating thread\n", __func__);
        return gv_status;
    }
    
    return GOOD;
}


int readEngine1()
{
    printf("\n%s()  ,  attempt read with pthread_mutex_trylock()\n", 
        __func__);
    char temp[STR_SIZE];
    memset(temp, '\0', STR_SIZE);
    usleep_proper(READ_DELAY_US);    // pause in case of frequent calls

    gv_status = pthread_mutex_trylock(&sM.engineMutex);
    if (gv_status == 0)
    {
        printf("\n%s()  ,  lock status:  %d  ,  read status:  %d\n",
            __func__, gv_status, (int)sM.readReady);
        if (sM.readReady == true)
        {
            strncpy(temp, sM.data, STR_SIZE);
            printf("\n\t\textracted:   { %s }\n", temp);
            gv_status = pthread_mutex_unlock(&sM.engineMutex);  // very important
            printf("\n%s()  ,  unlock status:  %d\n", __func__, gv_status);
            return GOOD;
        }
        gv_status = pthread_mutex_unlock(&sM.engineMutex);  // very important
        printf("\n%s()  ,  unlock status:  %d\n", __func__, gv_status);
        return INIT_INT;
    }
    
    if (gv_status == EBUSY)
    {
        printf("\n%s()  ,  EBUSY  ,  no extraction possible\n", 
            __func__);
    }
    else
    {
        printf("\n%s()  ,  lock status:  %d  ,  no extraction possible\n", 
            __func__, gv_status);
    }

    usleep_proper(READ_DELAY_US);    // pause in case of frequent calls
    return gv_status;
}


void* stateMachine1(void* arg)
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
            usleep_proper(READ_DELAY_US*10);    // 10x pause for possible read call
        }
    }

    if (shouldLock == false)    // safety, the mutex is locked
    {
        pthread_mutex_unlock(&sM.engineMutex);
    }
    printf("\n%s()  ,  loop EXIT engine stops\n", __func__);
    pthread_exit(NULL);    // or return NULL;
}


int haltEngine1()
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
        printf("\n\t%s()  ,  error destroying attr  ,  status:  %d\n",
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

////////~~~~~~~~END>  ut_1_trylock.c
