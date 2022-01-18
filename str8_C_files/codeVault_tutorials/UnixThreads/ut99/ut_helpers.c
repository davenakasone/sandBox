/*
    some support functions
*/

#include "resourcez.h"    // everything


void resetStruct()
{ 
    sM.idx = 0;
    sM.readReady = false;
    memset(sM.data, '\0', STR_SIZE);
}


void usleep_proper(int time_us)
{
    if (time_us <= 0) {return;}    // guard

    if (time_us <= US_PER_SEC)
    {
        usleep(time_us);
        return;    // within range
    }
    
    int secs = time_us / US_PER_SEC;
    int secs_us = time_us - secs;
    sleep(secs);
    usleep(secs_us);
}


char getChar()
{
    return (char) ( (rand() % (STOP-START)) + START );
}

////////~~~~~~~~END>  ut_helpers.c
