/*
    get this to work right one day
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
void agent_fueler(stcCar * ptr);


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
    pthread_t thz[CARZ];    // one thread per vix
    stcCar cars[CARZ];      // key data for each car

    for (int i = 0; i < CARZ; i++)
    {
        cars[i].gallons = 0;
        cars[i].seqNum = i+1;
        if (pthread_create(&thz[i], NULL, &client_car, (void*)&cars[i]) != 0)
        {
            printf("failed to create thread %d\n", i);
            return i;
        }
    }
    for (int i = 0; i < CARZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfailed to join thread  %d\n", i);
            return (-1*i);
        }
        printf("\ncar %d got %d gallons\n",  
            cars[i-1].seqNum, cars[i-1].gallons);
    }

    pthread_mutex_destroy(&muteFuel);
    pthread_cond_destroy(&condFuel);
    return GOOD;
}


void* client_car(void* arg)
{
    stcCar * temp = (stcCar*)arg;
    for (int i = 1; i <= CARZ; i++)
    {
        if (temp->seqNum == i)
        {
            //pthread_mutex_lock(&muteFuel);
            printf("\t\t%s()  ,  car %d  waiting...\n",
                __func__, temp->seqNum);
            agent_fueler(temp);
            pthread_mutex_lock(&muteFuel);
            gv_fuelSupply = FUEL_INVENTORY;
            printf("\t\t%s()  ,  car %d filled %d gallons, inventory replenished:  %d\n",
                __func__, temp->seqNum, temp->gallons, gv_fuelSupply);
            temp = NULL;
            pthread_mutex_unlock(&muteFuel);
        }
    }
    return arg;
}


void agent_fueler(stcCar * ptr)
{
    for (int i = 0; i < GALLONS_PER_CAR; i++)
    {
        pthread_mutex_lock(&muteFuel);
        gv_fuelSupply--;
        ptr->gallons++;
        printf("\t%s()  ,  car  %d  ,  gallons:  %d  ,  fuel inventory:  %d\n",
            __func__, ptr->seqNum, ptr->gallons, gv_fuelSupply);
        pthread_mutex_unlock(&muteFuel);
        usleep(100000);
        pthread_cond_broadcast(&condFuel);
    }
}

////////~~~~~~~~END>  ut112.c
