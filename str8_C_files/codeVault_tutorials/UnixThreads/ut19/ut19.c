/*
    deadlocks, a small gap where threads halt system waiting on lock

    ex1()  everything good
    ex2()  locked mutex x2 by same thread... computer does not know, just hangs
        locking mutex twice in same thread will block everything

    ex3() the issue is having multiple locks, locked in different orders

    ex4()  exagerate mixing up locking order  , likely to dead lock
            each thread has the mutex the other one needs, none can advance
    
    make the code robust enough to stop this
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define GOOD 69
#define THREADZ 5
#define FILL_GAL 10
#define INIT_INT -999

pthread_mutex_t fuelLock;
pthread_mutex_t waterLock;
int gv_status = INIT_INT;
int gv_fuel = 100;
int gv_water = 10;
int gv_mixer = INIT_INT;

int ex1();
void* routine1(void* arg);
int ex2();
void* routine2(void* arg);
int ex3();
void* routine3(void* arg);
int ex4();
void* routine4(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));

    //gv_status = ex1();
    //gv_status = ex2();
    //gv_status = ex3();
    gv_status = ex4();

    printf("\n\nstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
}


int ex1()
{
    printf("\n%s()  ,  good design\n", __func__);
    pthread_t thz[THREADZ];

    pthread_mutex_init(&fuelLock, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine1, NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    pthread_mutex_destroy(&fuelLock);

    return GOOD;
}


void* routine1(void* arg)
{
    pthread_mutex_lock(&fuelLock);
    printf("\n\t%s()  ,  current gallons:  %d\n",
        __func__, gv_fuel);
    gv_fuel = gv_fuel + FILL_GAL;
    printf("\t\tfilled %d gallons, current gallons:  %d\n",
        FILL_GAL, gv_fuel);
    pthread_mutex_unlock(&fuelLock);

    return NULL;
}


int ex2()
{
    printf("\n%s()  ,  mutex gets locked x2... bad\n", __func__);
    pthread_t thz[THREADZ];

    pthread_mutex_init(&fuelLock, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine2, NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    pthread_mutex_destroy(&fuelLock);

    return GOOD;
}


void* routine2(void* arg)
{
    pthread_mutex_lock(&fuelLock);
    pthread_mutex_lock(&fuelLock);
    printf("\n\t%s()  ,  current gallons:  %d\n",
        __func__, gv_fuel);
    gv_fuel = gv_fuel + FILL_GAL;
    printf("\t\tfilled %d gallons, current gallons:  %d\n",
        FILL_GAL, gv_fuel);
    pthread_mutex_unlock(&fuelLock);

    return NULL;
}


int ex3()
{
    printf("\n%s()  ,  order may matter\n", __func__);
    pthread_t thz[THREADZ];

    pthread_mutex_init(&fuelLock, NULL);
    pthread_mutex_init(&waterLock, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine3, NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    pthread_mutex_destroy(&waterLock);
    pthread_mutex_destroy(&fuelLock);

    return GOOD;
}


void* routine3(void* arg)
{
    pthread_mutex_lock(&fuelLock);
    pthread_mutex_lock(&waterLock);
    printf("\n\t%s()  ,  current gallons:  %d\n",
        __func__, gv_fuel);
    gv_fuel = gv_fuel + FILL_GAL;
    gv_water = gv_fuel;
    printf("\t\tthread complete]]]  fuel:  %d  <>  water:  %d\n",
        gv_fuel, gv_water);
    pthread_mutex_unlock(&fuelLock);
    pthread_mutex_unlock(&waterLock);

    return NULL;
}


int ex4()
{
    printf("\n%s()  ,  what happens if execution of locks is changed???\n", __func__);
    pthread_t thz[THREADZ];

    pthread_mutex_init(&fuelLock, NULL);
    pthread_mutex_init(&waterLock, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine4, NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    pthread_mutex_destroy(&waterLock);
    pthread_mutex_destroy(&fuelLock);

    return GOOD;
}


void* routine4(void* arg)
{
    gv_mixer = (rand() % 2);    // [0:1]

    if (gv_mixer)
    {
        pthread_mutex_lock(&fuelLock);
        sleep(1);
        pthread_mutex_lock(&waterLock);
    }
    else
    {
        pthread_mutex_lock(&waterLock);
        pthread_mutex_lock(&fuelLock);
    }
    
    printf("\n\t%s()  ,  current gallons:  %d\n",
        __func__, gv_fuel);
    gv_fuel = gv_fuel + FILL_GAL;
    gv_water = gv_fuel;
    printf("\t\tthread complete]]]  fuel:  %d  <>  water:  %d\n",
        gv_fuel, gv_water);
    pthread_mutex_unlock(&fuelLock);
    pthread_mutex_unlock(&waterLock);

    return NULL;
}

////////~~~~~~~~END>  ut19.c
