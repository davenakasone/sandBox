/*
    main thread implied, need second thread to run the engine
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "javaInterface.h"

Location dummy;


// where java code would interact with C code   ... main() is for testing only
int main(int argc, char* argv[], char* envp[])
{
    printf("\n%s()  ,  simulating java to C API...\n", __func__);
    srand(time(NULL));    // seed
    int catch = INIT_INT;
    int waitTime_us;
    metInit(&dummy);

    // always get the engine running, call once and leave like a daemon
    catch = GPS_initializeEngine("any/serial/path");    
    printf("\n%s()  ,  result of call to GPS_initializeEngine():  %d\n", 
        __func__, catch);

    // read whenever needed
    for (int i = 0; i < READ_ITERATIONS; i++)
    {
        waitTime_us = rand() % US_PER_SEC; // wait 0 to 1 second
        usleep(waitTime_us);
        catch = GPS_readLocationStruct(&dummy);
        printf("\n%s()  ,  read attempt %d of %d  ,  status:  %d\n", 
            __func__, (i+1), READ_ITERATIONS, catch);
        metPrint(&dummy);
        printf("\n***********************************\n");
    }

    catch = GPS_haltEngine();
    printf("\n%s()  ,  ending program  ,  returned:  %d\n", __func__, catch);

    printf("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  main.c
