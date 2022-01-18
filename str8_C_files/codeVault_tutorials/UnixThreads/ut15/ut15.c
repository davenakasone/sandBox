/*
    practical example of pthread_barrier

    8 threads, each roll dice
    The main thread will see what thread won and what lost
    if multiple 6, then both are winners

    must synchronize
        barrier or mutex it    ... multi threaded envp
    
    if you place the x2 barriers, it is guarunteed to work
    but you have to ensure what follows

    the point is not to do this sequentially...yes it is simple
    this is the fundamental of multi threading...they run in parallel
    try with a loop to see...ex4()
    barrier syncs threads while running ...keeps parallel running
    mutex is more for shared memory access

    +1 for main thread
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "pthreadBarrierOSX.h" // mac only

#define THREADZ 8       // hopefully your CPU has 8 cores
#define GOOD 69

pthread_barrier_t barry;
pthread_barrier_t barryInsured;

int gv_status = GOOD;
int gv_result[THREADZ];      // reflects if thread won or lost
int gv_diceVals[THREADZ];    // store results

void* rollDice1(void* arg);
int ex1();

void* rollDice2(void* arg);
int ex2();

void* rollDice3(void* arg);
int ex3();

void* rollDice4(void* arg);
int ex4();

int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));    // seed
    printf("\n%d threads roll dice...\n\n", THREADZ);

    //gv_status = ex1();   // no barrier...
    //gv_status = ex2();    // barrier, but result not insured
    //gv_status = ex3();    // best way to do it
    gv_status = ex4();    // inf loop

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  no barrier\n", __func__);
    pthread_t thz[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        int* index = (int*)malloc(1*sizeof(int));
        *index = i;
        if (pthread_create(&thz[i], NULL, &rollDice1, index) != 0)
        {
            printf("error creating thread %d\n", i);
            return i+1;
        }
    }
    int max = 0;
    for (int i = 0; i < THREADZ; i++)
    {
        if (gv_diceVals[i] > max)
        {
            max = gv_diceVals[i];
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (gv_diceVals[i] == max)
        {
            gv_result[i] = 1;
        }
        else
        {
            gv_result[i] = 0;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("error joining thread %d\n", i);
            return (-1*(i+1));
        }
    }
    return GOOD;
}


void* rollDice1(void* arg)
{
    int idx = *(int*)arg;
    gv_diceVals[idx] = (rand() % 6) + 1;
    if (gv_result[idx] == 1)
    {
        printf("\n\tWIN>  thread  %d  ,  rolled:  %d\n",
            idx, gv_diceVals[idx]);
    }
    else
    {
        printf("\n\tLOSE>  thread  %d  ,  rolled:  %d\n",
            idx, gv_diceVals[idx]);
    }
    free(arg);
    return NULL;
}


int ex2()
{
    printf("\n%s()  ,  barrier but not insured\n", __func__);
    pthread_t thz[THREADZ];
    pthread_barrier_init(&barry, NULL, (THREADZ+1)); // main thread + other 8
    for (int i = 0; i < THREADZ; i++)
    {
        int* index = (int*)malloc(1*sizeof(int));
        *index = i;
        if (pthread_create(&thz[i], NULL, &rollDice2, index) != 0)
        {
            printf("error creating thread %d\n", i);
            return i+1;
        }
    }
    pthread_barrier_wait(&barry);    // also want to wait here 
    int max = 0;
    for (int i = 0; i < THREADZ; i++)
    {
        if (gv_diceVals[i] > max)
        {
            max = gv_diceVals[i];
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (gv_diceVals[i] == max)
        {
            gv_result[i] = 1;
        }
        else
        {
            gv_result[i] = 0;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("error joining thread %d\n", i);
            return (-1*(i+1));
        }
    }
    pthread_barrier_destroy(&barry);
    return GOOD;
}


void* rollDice2(void* arg)
{
    int idx = *(int*)arg;
    gv_diceVals[idx] = (rand() % 6) + 1;
    pthread_barrier_wait(&barry);
    if (gv_result[idx] == 1)
    {
        printf("\n\tWIN>  thread  %d  ,  rolled:  %d\n",
            idx, gv_diceVals[idx]);
    }
    else
    {
        printf("\n\tLOSE>  thread  %d  ,  rolled:  %d\n",
            idx, gv_diceVals[idx]);
    }
    free(arg);
    return NULL;
}


int ex3()
{
    printf("\n%s()  ,  best way to do it\n", __func__);
    pthread_t thz[THREADZ];
    pthread_barrier_init(&barry, NULL, (THREADZ+1));    // main thread + other 8
    pthread_barrier_init(&barryInsured, NULL, (THREADZ+1));    // ensures calculation of winner calculated
    for (int i = 0; i < THREADZ; i++)
    {
        int* index = (int*)malloc(1*sizeof(int));
        *index = i;
        if (pthread_create(&thz[i], NULL, &rollDice3, index) != 0)
        {
            printf("error creating thread %d\n", i);
            return i+1;
        }
    }
    pthread_barrier_wait(&barry);    // also want to wait here 
    int max = 0;
    for (int i = 0; i < THREADZ; i++)
    {
        if (gv_diceVals[i] > max)
        {
            max = gv_diceVals[i];
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (gv_diceVals[i] == max)
        {
            gv_result[i] = 1;
        }
        else
        {
            gv_result[i] = 0;
        }
    }
    pthread_barrier_wait(&barryInsured); // main thread only gets here after winner calculauted...
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("error joining thread %d\n", i);
            return (-1*(i+1));
        }
    }
    pthread_barrier_destroy(&barry);
    pthread_barrier_destroy(&barryInsured);
    return GOOD;
}


void* rollDice3(void* arg)
{
    int idx = *(int*)arg;
    gv_diceVals[idx] = (rand() % 6) + 1;
    pthread_barrier_wait(&barry);
    pthread_barrier_wait(&barryInsured); // now it will wait for calculation
    if (gv_result[idx] == 1) // won't happen until main thread passes both barriers...
    {
        printf("\n\tWIN>  thread  %d  ,  rolled:  %d\n",
            idx, gv_diceVals[idx]);
    }
    else
    {
        printf("\n\tLOSE>  thread  %d  ,  rolled:  %d\n",
            idx, gv_diceVals[idx]);
    }
    free(arg);
    return NULL;
}


int ex4()
{
    printf("\n%s()  ,  use a loop\n", __func__);
    pthread_t thz[THREADZ];
    pthread_barrier_init(&barry, NULL, (THREADZ+1));    // main thread + other 8
    pthread_barrier_init(&barryInsured, NULL, (THREADZ+1));    // ensures calculation of winner calculated
    for (int i = 0; i < THREADZ; i++)
    {
        int* index = (int*)malloc(1*sizeof(int));
        *index = i;
        if (pthread_create(&thz[i], NULL, &rollDice4, index) != 0)
        {
            printf("error creating thread %d\n", i);
            return i+1;
        }
    }
    while(1)
    {
        pthread_barrier_wait(&barry);    // also want to wait here 
        int max = 0;
        for (int i = 0; i < THREADZ; i++)
        {
            if (gv_diceVals[i] > max)
            {
                max = gv_diceVals[i];
            }
        }
        for (int i = 0; i < THREADZ; i++)
        {
            if (gv_diceVals[i] == max)
            {
                gv_result[i] = 1;
            }
            else
            {
                gv_result[i] = 0;
            }
        }
        printf("\n*********** new round ***********\n");
        sleep(1);
        pthread_barrier_wait(&barryInsured);
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("error joining thread %d\n", i);
            return (-1*(i+1));
        }
    }
    pthread_barrier_destroy(&barry);
    pthread_barrier_destroy(&barryInsured);
    return GOOD;
}


void* rollDice4(void* arg)
{
    int idx = *(int*)arg;
    while(1)
    {
        gv_diceVals[idx] = (rand() % 6) + 1;
        pthread_barrier_wait(&barry);
        pthread_barrier_wait(&barryInsured);
        if (gv_result[idx] == 1)
        {
            printf("\tWIN>  thread  %d  ,  rolled:  %d\n",
                idx, gv_diceVals[idx]);
        }
        else
        {
            printf("\tLOSE>  thread  %d  ,  rolled:  %d\n",
                idx, gv_diceVals[idx]);
        }
    }
    
    free(arg);
    return NULL;
}

////////~~~~~~~~END> ut15.c
