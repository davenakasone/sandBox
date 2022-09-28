/*
    SM_88 : no threads
        with just one worker thread and small work-load,
        it is easier and more robust to just not use threads
    
    this is the simplest and most robust
        but it is purley SEQUENTIAl ... can only go parallel with threads (or fork)
            not good for a large work load
*/

#include "resourcez.h"    // everything
#ifdef SM_88


int initializeEngine88()
{
    printf("\n%s()  ,  no threads used...\n", 
        __func__);
    
    return GOOD;
}


int readEngine88()
{
    printf("\n%s()  ,  attempt read\n", 
        __func__);
    char temp[STR_SIZE];
    memset(temp, '\0', STR_SIZE);

    stateMachine88();    // just make it complete a cycle

    if (sM.readReady == true)
    {
        strncpy(temp, sM.data, STR_SIZE);
        printf("\n\t%s()  ,  extracted:   { %s }\n", 
            __func__, temp);
        gv_status = GOOD;
    }
    else
    {
        printf("\n%s()  ,  no extraction possible\n",
            __func__);
        gv_status = INIT_INT;
    }

    usleep_proper(READ_DELAY_US);    // always helps stop rapid reading
    return gv_status;
}


void stateMachine88()
{
    printf("\n%s()  ,  engine starts\n\n", 
        __func__);

    resetStruct(&sM);
    sM.runFlag = true;

    while (sM.runFlag == true)
    {
        if (sM.idx > STR_SIZE-1) {resetStruct(&sM);}
        sM.data[sM.idx] = getChar();
        sM.idx++;

        if (sM.idx == STR_SIZE-1)
        {
            sM.data[sM.idx] = '\0';
            sM.readReady = true;
            sM.runFlag = false;
            printf("\t%s()  ,  parsed:  { %s }\n", 
                __func__, sM.data);
            return;
        }
    }

    // should never occur, but just in case
    printf("\n%s()  ,  loop EXIT engine stops\n", 
        __func__);
}


int haltEngine88()
{
    printf("\n\t%s()  ,  engine STOPPED\n", 
        __func__);

    return GOOD;
}

#endif

////////~~~~~~~~END>  ut_88_no_thread.c
