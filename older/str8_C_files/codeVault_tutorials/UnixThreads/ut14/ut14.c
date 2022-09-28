/*
    OSX does not have pthread_barrier_t ....use Linux
 
    the pthread_barrier is an object other threads have to wait for

    thd[1] -->    |
    thd[2] -->    | this barrier is set to stop until 3 threads waiting

    once a 3rd thread comes, the barrier will be lifted

    like any pthread obj in the API
        you declare, initialize, and maybe deallocate/destroy

    ex1()  never finished, can't get enough threads in Queue
    ex2()  builds...all pass barrier at same time
    
    good to batch process....

    ex3()  how to actually use a barrier

    good way to control execution...or just make barrier all the active threads
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pthreadBarrierOSX.h" // mac only

#define GOOD 69
#define QUEUE_SIZE 3
#define THREADZ_1 2
#define THREADZ_2 9
#define THREADZ_3 7

pthread_barrier_t barry;
int gv_status = GOOD;


int ex1();
int ex2();
void* routine(void* arg);
int ex3();
void* routinE(void* arg);

int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();
    //gv_status = ex2();
    gv_status = ex3();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  basic barrier  ,  never finishes...\n", __func__);
    pthread_t thz[THREADZ_1];
    pthread_barrier_init(&barry, NULL, QUEUE_SIZE);
    for (int i = 0; i < THREADZ_1; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine, NULL) != 0)
        {
            printf("\nfailed to create thread %d\n", i+1);
            return (i+1);
        }
    }
    for (int i = 0; i < THREADZ_1; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfailed to join thread %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
    }
    pthread_barrier_destroy(&barry);
    return GOOD;
}


int ex2()
{
    printf("\n%s()  ,  passes because multiple of %d...\n", 
        __func__, QUEUE_SIZE);
    pthread_t thz[THREADZ_2];
    pthread_barrier_init(&barry, NULL, QUEUE_SIZE);
    for (int i = 0; i < THREADZ_2; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine, NULL) != 0)
        {
            printf("\nfailed to create thread %d\n", i+1);
            return (i+1);
        }
    }
    for (int i = 0; i < THREADZ_2; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfailed to join thread %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
    }
    pthread_barrier_destroy(&barry);
    return GOOD;
}


void* routine(void* arg)
{
    printf("\twaiting at the barrier...\n");
    pthread_barrier_wait(&barry); // waits until QUEUE_SIZE threads 
    printf("\tpassed barrier\n");
    return NULL;
}


int ex3()
{
    printf("\n%s()  ,  correct use of barrier   ,  QUEUE_SIZE:  %d  ,  THREADZ:  %d...\n", 
        __func__, QUEUE_SIZE, THREADZ_3);
    pthread_t thz[THREADZ_3];
    pthread_barrier_init(&barry, NULL, QUEUE_SIZE);
    for (int i = 0; i < THREADZ_3; i++)
    {
        if (pthread_create(&thz[i], NULL, &routinE, NULL) != 0)
        {
            printf("\nfailed to create thread %d\n", i+1);
            return (i+1);
        }
    }
    for (int i = 0; i < THREADZ_3; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfailed to join thread %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
    }
    pthread_barrier_destroy(&barry);
    return GOOD;
}
void* routinE(void* arg)
{
    while(1)
    {
        printf("\twaiting at the barrier...\n");
        sleep(1);
        pthread_barrier_wait(&barry); 
        printf("\tpassed barrier\n");
        sleep(1);
    }
    
    return NULL;
}

////////~~~~~~~~END>  ut14.c
