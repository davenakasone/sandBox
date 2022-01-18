/*
    figure out best way to wait for a read, then time out
    use "gv_rand" as the extraction of interest ... could be anything, but int for simplicity
    select method "SM_1" , "SM_2" , or "SM_3"

    a thread is detached and begins running until flagged to stop
    the routine is just to fill an array with specified number of random integers
    the "predicate" to be coordinated is all the struct members of the global instance

    SM_1 is ok , simple pthread_mutex_trylock()   ...same with looping

    SM_2 is ok , but relys on the wait and signal

    SM_3 is plausible , stops the skip if it works...watch the timing
    
    SM_88 : consider sequetial executing with no threads if workload is light enough

    note that some operating systems require the use of sleep() and usleep()
    if sleeping over 1 second
    don't expect timing resolution to be better than the input timer tick rate
    clock jitter might happen
    most OS don't like pthread.h anymore and only have pieces
*/

#include "resourcez.h"    // everything
#include <asm/errno.h> 


int main(int argc, char* argv[], char* envp[])
{
    // prepare experiment
    srand(time(NULL));
    #ifdef MAKE_READ_DELAY
        int delay = INIT_INT;
    #endif
    gv_status = INIT_INT;
    printf("\n%s()  ,  reading a detached worker thread  ,  reps:  %d\n",
        __func__, REPS);

    // initialize the resources
    #ifdef SM_1
        gv_status = initializeEngine1();
    #endif
    #ifdef SM_2
        gv_status = initializeEngine2();
    #endif
    #ifdef SM_3
        gv_status = initializeEngine3();
    #endif
    #ifdef SM_88
        gv_status = initializeEngine88();
    #endif
    printf("\n%s()  ,  preparations complete  ,  status:  %d\n", 
        __func__, gv_status);
    
    // execute test reads
    for (int i = 0; i < REPS; i++)
    {
        #ifdef MAKE_READ_DELAY
            delay = (rand() % DELAY_MAX_US);
            #ifndef SM_88
                if (i == 0)
                {
                    printf("\n%s()  ,  before read--> wait %f sec...\n", 
                        __func__, (float)((float)delay/(float)US_PER_SEC));
                }
                else
                {
                    printf("\n%s()  ,  before read--> wait %f sec...\n\n", 
                        __func__, (float)((float)delay/(float)US_PER_SEC));
                }
            #else
                printf("\n%s()  ,  before read--> wait %f sec...\n", 
                    __func__, (float)((float)delay/(float)US_PER_SEC));
            #endif
            usleep_proper(delay);
        #endif
        
        #ifdef SM_1
            printf("\n%s()  ,  readEngine1()  %d of %d ...\n", 
                __func__, i+1, REPS);
            gv_status = readEngine1();
        #endif
        #ifdef SM_2
            printf("\n%s()  ,  readEngine2()  %d of %d ...\n", 
                __func__, i+1, REPS);
            gv_status = readEngine2();
        #endif
        #ifdef SM_3
            printf("\n%s()  ,  readEngine3()  %d of %d ...\n", 
                __func__, i+1, REPS);
            gv_status = readEngine3();
        #endif
        #ifdef SM_88
            printf("\n%s()  ,  readEngine88()  %d of %d ...\n", 
                __func__, i+1, REPS);
            gv_status = readEngine88();
        #endif

        if (gv_status == GOOD)
        {
            printf("\n%s()  ,  read success  ,  status:  %d\n", 
                __func__, gv_status);
        }
        else
        {
            printf("\n%s()  ,  UNABLE to read  ,  status:  %d\n", 
                __func__, gv_status);
        }
    }

    // clean up resources
    #ifdef SM_1
        gv_status = haltEngine1();
    #endif
    #ifdef SM_2
        gv_status = haltEngine2();
    #endif
    #ifdef SM_3
        gv_status = haltEngine3();
    #endif
    #ifdef SM_88
        gv_status = haltEngine88();
    #endif
    printf("\n%s()  ,  halting engine status:  %d\n", 
        __func__, gv_status);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  ut_main.c
