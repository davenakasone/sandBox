/*
    a stove with gas being used by chefs
    gas can delplete after cooking

    ex1()  no trylock  ...not really needed
    ex2()  now there are n stoves...  mutex for each stove   but 4 stoves fill faster than 4 chefs
    ex3()  make chefs check again

*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define STOVES 4
#define CHEFS 10            // the threads
#define FUEL_USED_MAX 30    // max fuel to be used per cook
#define GOOD 69
#define FUEL_START 100

pthread_mutex_t muteStove;
pthread_mutex_t muteStoveArr[STOVES];
int gv_stoveFuel = FUEL_START;
int gv_stoveFuelArr[STOVES];
int gv_status = EXIT_SUCCESS;

int ex1();
void* routine1(void* arg);
int ex2();
void* routine2(void* arg);
int ex3();
void* routine3(void* arg);

int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));
    
    //gv_status = ex1();
    //gv_status = ex2();
    gv_status = ex3();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

int ex1()
{
    printf("\n%s()  ,  simulate stove with %d cooks  ,  no trylock...\n", 
        __func__, CHEFS);
    pthread_t thz[CHEFS];
    pthread_mutex_init(&muteStove, NULL);

    for (int i = 0; i < CHEFS; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine1, NULL) != 0)
        {
            printf("\nerror creating thread %d\n", i);
            gv_status = (i+1);
        }
    }

    for (int i = 0; i < CHEFS; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nerror joining thread %d\n", i);
            return (-1*(i+1));
        }
    }

    pthread_mutex_destroy(&muteStove);
    return GOOD;
}
void* routine1(void* arg)
{
    pthread_mutex_lock(&muteStove);
    int fuelNeeded = 1 + (rand() % FUEL_USED_MAX);
    
    if ( (gv_stoveFuel-fuelNeeded) < 0)
    {
        printf("\t\tno more fuel, chef goes home\n");
    }
    else
    {
        gv_stoveFuel = gv_stoveFuel - fuelNeeded;
        usleep(500000); // take time to cook 
        printf("\t\tfuel remaining:  %d\n", gv_stoveFuel);
    }

    pthread_mutex_unlock(&muteStove);
    return NULL;
}


int ex2()
{
    printf("\n%s()  ,  simulate stove with %d cooks  ,  use trylock...\n", 
        __func__, CHEFS);
    pthread_t thz[CHEFS];
    pthread_mutex_init(&muteStove, NULL);
    for (int i = 0; i < STOVES; i++) 
    {
        gv_stoveFuelArr[i] = FUEL_START;
        pthread_mutex_init(&muteStoveArr[i], NULL);
    }

    for (int i = 0; i < CHEFS; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine2, NULL) != 0)
        {
            printf("\nerror creating thread %d\n", i);
            gv_status = (i+1);
        }
    }

    for (int i = 0; i < CHEFS; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nerror joining thread %d\n", i);
            return (-1*(i+1));
        }
    }
    
    for (int i = 0; i < STOVES; i++) 
    {
        pthread_mutex_destroy(&muteStoveArr[i]);
    }
    printf("\n%s()  ,  the %d stoves filled up and blocked everything else\n", 
        __func__, STOVES);
    return GOOD;
}
void* routine2(void* arg)
{
    for (int i = 0; i < STOVES; i++) // lets all chefs check all stoves
    {
        // see if any stove available
        if (pthread_mutex_trylock(&muteStoveArr[i]) == 0)
        {
            int fuelNeeded = 1 + (rand() % FUEL_USED_MAX);
            if ( (gv_stoveFuelArr[i]-fuelNeeded) < 0)
            {
                printf("\t\tno more fuel, chef goes home\n");
            }
            else
            {
                gv_stoveFuelArr[i] = gv_stoveFuelArr[i] - fuelNeeded;
                usleep(500000); // take time to cook 
                printf("\t\tstove:  %d  ,  fuel remaining:  %d\n", 
                    i+1, gv_stoveFuelArr[i]);
            }
            pthread_mutex_unlock(&muteStoveArr[i]);
            break; // only gets 1 pass...the way it should be
        } 
    }
    return NULL;
}


int ex3()
{
    printf("\n%s()  ,  simulate stove with %d cooks  ,  use trylock and stop for all...\n", 
        __func__, CHEFS);
    pthread_t thz[CHEFS];
    pthread_mutex_init(&muteStove, NULL);
    for (int i = 0; i < STOVES; i++) 
    {
        gv_stoveFuelArr[i] = FUEL_START;
        pthread_mutex_init(&muteStoveArr[i], NULL);
    }

    for (int i = 0; i < CHEFS; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine3, NULL) != 0)
        {
            printf("\nerror creating thread %d\n", i);
            gv_status = (i+1);
        }
    }

    for (int i = 0; i < CHEFS; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nerror joining thread %d\n", i);
            return (-1*(i+1));
        }
    }
    
    for (int i = 0; i < STOVES; i++) 
    {
        pthread_mutex_destroy(&muteStoveArr[i]);
    }
    return GOOD;
}
void* routine3(void* arg)
{
    for (int i = 0; i < STOVES; i++) // lets all chefs check all stoves
    {
        // see if any stove available
        if (pthread_mutex_trylock(&muteStoveArr[i]) == 0)
        {
            int fuelNeeded = 1 + (rand() % FUEL_USED_MAX);
            if ( (gv_stoveFuelArr[i]-fuelNeeded) < 0)
            {
                printf("\t\tno more fuel, chef goes home\n");
            }
            else
            {
                gv_stoveFuelArr[i] = gv_stoveFuelArr[i] - fuelNeeded;
                usleep(500000); // take time to cook 
                printf("\t\tstove:  %d  ,  fuel remaining:  %d\n", 
                    i+1, gv_stoveFuelArr[i]);
            }
            pthread_mutex_unlock(&muteStoveArr[i]);
            break; // only gets 1 pass...the way it should be
        } 
        else
        {
            if (i == STOVES-1)
            {
                printf("\tno stove available, waiting...\n");
                usleep(500000);
                i = 0; // makes loop try again
            }
        }
    }
    return NULL;
}

////////~~~~~~~~END>  ut12.c
