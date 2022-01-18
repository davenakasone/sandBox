/*
    waiting is ok if there are just 2 threads...server and client

    trying to wait won't wake the other threads

*/

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define INIT_INT -999
#define CARZ 3
#define FUEL_INVENTORY 100
#define GOOD 69
#define GALLONS_PER_CAR 5

int gv_status = INIT_INT;
int gv_fuelSupply = FUEL_INVENTORY;
pthread_mutex_t muteFuel;
pthread_cond_t condFuel;

typedef struct
{
    int seqNum;
    int gallons;
}stcCar;


int simulate();
void* client_car(void* arg);
void* agent_fueler(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    printf("\nfuelers:  %d  ,  cars:  %d\n", 1, CARZ);
    gv_status = simulate();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int simulate()
{
    printf("\n%s()  ,  begin simulation...\n", __func__);
    pthread_mutex_init(&muteFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    pthread_t thz[(CARZ+1)];    // thz[0] is the fueling guy, rest are for cars being fueled
    stcCar cars[CARZ];        // key data for cars

    for (int i = 0; i <= CARZ; i++)
    {

        if (i==0)
        {
            if(pthread_create(&thz[i], NULL, &agent_fueler, NULL) != 0)
            {
                printf("\nfailed to create thread  %d\n", i);
                return i;
            }
        }
        else
        {
            cars[i-1].seqNum = i;
            cars[i-1].gallons = 0;
printf("%s()  ,  car:  %d  ,  gallons:  %d\n", __func__, cars[i-1].seqNum, cars[i-1].gallons);
            if (pthread_create(&thz[i], NULL, &client_car, &cars[i-1]) != 0)
            {
                printf("\nfailed to create thread  %d\n", i);
                return i;
            }
        }
    }
    for (int i = 0; i <= CARZ; i++)
    {
        if (i == 0)
        {
            if (pthread_join(thz[i], NULL) != 0)
            {
                printf("\nfailed to join thread  %d\n", i);
            }
        }
        else
        {
            //if (pthread_join(thz[i], (void*)&cars[i-1]) != 0)
            if (pthread_join(thz[i], NULL) != 0)
            {
                printf("\nfailed to join thread  %d\n", i);
            }
//printf("\naddress:  %p\n", &cars[i-1]);
            printf("\ncar %d got %d gallons\n",  cars[i-1].seqNum, cars[i-1].gallons);
            //printf("\ncar  %d  got  %d  gallons\n", *(stcCar*)&cars[i-1], *(stcCar*)&cars[i-1]);
        }
    }

    pthread_mutex_destroy(&muteFuel);
    pthread_cond_destroy(&condFuel);
    return GOOD;
}


void* client_car(void* arg)
{
    pthread_mutex_lock(&muteFuel);
    stcCar * temp = (stcCar*)arg;
    while (gv_fuelSupply < FUEL_INVENTORY  && 
           temp->gallons != GALLONS_PER_CAR )
    {
        printf("\t\t%s()  ,  car %d  waiting...\n",
            __func__, temp->seqNum);
        pthread_cond_wait(&condFuel, &muteFuel);
        if (gv_fuelSupply == FUEL_INVENTORY-5)
        {
            gv_fuelSupply = FUEL_INVENTORY;
        }
    }
    temp->gallons = GALLONS_PER_CAR;
    printf("\t\t%s()  ,  car %d filled %d gallons, inventory replenished:  %d\n",
        __func__, temp->seqNum, temp->gallons, gv_fuelSupply);
//printf("address:  %p\n", temp);
    temp = NULL;
    pthread_cond_broadcast(&condFuel);
    pthread_mutex_unlock(&muteFuel);
    return arg;
}


void* agent_fueler(void* arg)
{
    while (gv_fuelSupply == FUEL_INVENTORY)
    {
        for (int i = 0; i < GALLONS_PER_CAR; i++)
        {
            pthread_mutex_lock(&muteFuel);
            gv_fuelSupply--;
            printf("\t%s()  ,  gallons filled:  %d  ,  fuel inventory:  %d\n", 
                __func__, (i+1), gv_fuelSupply);
            //pthread_cond_signal(&condFuel);
            pthread_cond_broadcast(&condFuel);
            pthread_mutex_unlock(&muteFuel);
            usleep(500000);
        }   
    }
    return NULL;
}

////////~~~~~~~~END>  ut111.c
