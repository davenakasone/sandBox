/*
    many considerations when using multi-thread
    all the threads will not just wake up
        pthread_cond_signal()  only signals 1 thread {but maybe more}
    
    don't trust thread priority

    can't do while() loop in multi-threaded fashion

    use pthread_cond_broadcast()   to give signal to all waiting threads

    mutex lock makes code sequtential...can't go parallel
*/

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define THREADZ 6
#define GALS_PER_FILL 40
#define REDUCE_PER_VIX 40

int gv_status = EXIT_SUCCESS;
int gv_fuel = 0;
int gv_carCounter = 0;
pthread_mutex_t muteFuel;
pthread_cond_t condFuel;

void* fuel_filling(void* arg);
void* car_waits(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    printf("\nfuelers:  %d  ,  cars:  %d  ,  total threads:  %d\n",
        1, THREADZ-1, THREADZ);
    printf("\nbegin simulation....\n");
    pthread_t thz[THREADZ];
    pthread_mutex_init(&muteFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        if (i == THREADZ-1)
        {
            if (pthread_create(&thz[i], NULL, &fuel_filling, NULL) != 0)
            {
                gv_status = i;
                printf("failed to create thread %d\n", i);
            }
        }
        else
        {
            if (pthread_create(&thz[i], NULL, &car_waits, NULL) != 0)
            {
                gv_status = i;
                printf("failed to create thread %d\n", i);
            }
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            gv_status = -1*i;
            printf("\nfailed to join thread %d\n", i);
        }
    }

    pthread_mutex_destroy(&muteFuel);
    pthread_cond_destroy(&condFuel);
    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    return gv_status;
}


void* fuel_filling(void* arg)
{
    for (int i = 0; i < (THREADZ-1); i++)
    {
        pthread_mutex_lock(&muteFuel);
        gv_fuel = gv_fuel + GALS_PER_FILL;
        printf("\t\tgallons filled:  %d\n", gv_fuel);
        pthread_mutex_unlock(&muteFuel);
        //pthread_cond_signal(&condFuel); // no, want all to get signal
        pthread_cond_broadcast(&condFuel);
        usleep(500000);
    } 
    return NULL;
}


void* car_waits(void* arg)
{
    pthread_mutex_lock(&muteFuel);
    while (gv_fuel < REDUCE_PER_VIX)
    {
        printf("\tno fuel, waiting...\n");
        pthread_cond_wait(&condFuel, &muteFuel); // unlock, wait, lock
    }
    gv_carCounter++;
    gv_fuel = gv_fuel - REDUCE_PER_VIX;
    printf("\n\tcar{ %d } got fuel, gallons left:  %d\n", 
        gv_carCounter, gv_fuel);
    pthread_mutex_unlock(&muteFuel);
    return NULL;
}

////////~~~~~~~~END>  ut11.c
