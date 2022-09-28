/*
    SM_2 :    very rigid, 
            will dead lock on clock skew or anything else that goes out of sync
        
        need a very nice cushion to:
            1) engine parses data
            2) engine unlocks mutex
            3) engine waits a good while
            4) read request hopefully locks mutex
            5) engine signals for read request (if it occurs)
            6) engine locks and continues
    
    it is a lot of code, but 
        very good if the timing is right
            redundant....no use waiting for signal 
            condition can already be checked before unlocking in engine
            just don't signal until you have the condition you want
*/

#include "resourcez.h"    // everything
#ifdef SM_2


int initializeEngine2()
{
    printf("\n%s()  ,  wait and signal with some delays...\n", 
        __func__);
    sM.idx = 0;
    sM.readReady = false;
    sM.runFlag = true;
    memset(sM.data, '\0', STR_SIZE);
    
    // initialize threading resources
    gv_status = pthread_cond_init(&sM.engineCond, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error initializing cond  ,  status:  %d\n",
            __func__, gv_status);
    }
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
        &sM.engineAttr, &stateMachine2, NULL);
    if (gv_status != 0)
    {
        printf("\n%s()  ,  error creating thread\n", __func__);
        return gv_status;
    }
    return GOOD;
}


int readEngine2()
{
    printf("\n%s()  ,  attempt read with pthread_cond_wait()\n", 
        __func__);
    char temp[STR_SIZE];
    memset(temp, '\0', STR_SIZE);
    usleep_proper(READ_DELAY_US);    // pause in case of frequent calls

    gv_status = pthread_mutex_lock(&sM.engineMutex);
    printf("\n%s()  ,  mutex locked status:  %d\n", __func__, gv_status);
    while(sM.readReady == false)
    {
        gv_status = pthread_cond_wait(&sM.engineCond, &sM.engineMutex);
        // unlock, wait for signal, lock
    }
    printf("\n%s()  ,  wait status:  %d\n", __func__, gv_status);

    strncpy(temp, sM.data, STR_SIZE);
    printf("\n\t\textracted:   { %s }\n", temp);
    gv_status = pthread_mutex_unlock(&sM.engineMutex);    // very important
    printf("\n%s()  ,  unlock status:  %d\n", 
            __func__, gv_status);

    usleep_proper(READ_DELAY_US);    // pause in case of frequent calls
    return GOOD;
}


void* stateMachine2(void* arg)
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
            usleep_proper(READ_DELAY_US*10);                    // 10x pause for possible read call
            //read call should get the mutex
            gv_status = pthread_cond_signal(&sM.engineCond);    // inform other 
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


int haltEngine2()
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

////////~~~~~~~~END>  ut_2_signal.c
