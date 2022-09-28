/*
    a login queue, can only handle a few logins at same time
    "THREADZ" are all people trying to connect to some server with some "CAPACITY"

    keep in mind a semaphore is just an integer that is incremented and decremented to control threads

    use this anytime there is a resource where you need to control access for users
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "apple_sem.h" 

#define THREADZ 6
#define CAPACITY 3
sem_t g_semaphore;

void ex1();
void* routine1(void* argz);


int main(int argc, char** argv, char** envp)
{
    ex1();

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


void ex1()
{
    printf("\n\t%s()  ,  starting the example\n", __func__);
    pthread_t thz[THREADZ];
    sem_init(&g_semaphore, 0, CAPACITY);
    int* counter;

    counter = (int*)malloc(THREADZ * sizeof(int));
    
    for (int ii = 0; ii < THREADZ; ii++)
    {
        //int* aa = (int*)malloc(sizeof(int));
        counter[ii] = ii;
        if (pthread_create(&thz[ii], NULL, &routine1, &counter[ii]) != 0)
        {
            printf("\n\t%s()  ,  failed to create thread  %d\n", __func__, ii);
        }
        printf("\n\t%s()  ,  created thread  %d\n", __func__, ii);
    }
    for (int ii = 0; ii < THREADZ; ii++)
    {
        if (pthread_join(thz[ii], NULL) != 0)
        {
            printf("%s()  ,  failed to join thread  %d\n", __func__, ii);
        }
        printf("\n\t%s()  ,  ended thread  %d\n", __func__, ii);
    }
    sem_destroy(&g_semaphore);
}


////~~~~


void* routine1(void* argz)
{
    printf("\n\t%s()  ,  [%d] waiting in login queue\n",
        __func__, *(int*)argz);
    sem_wait(&g_semaphore); // if you get past here, the semaphore was decremented, and thread logged in
    printf("\n\t%s()  ,  [%d] login was good\n",
        __func__, *(int*)argz);
    sleep((rand() % 5) + 1); // stay logged in for 1 to 5 seconds
    printf("\n\t%s()  ,  [%d] logout\n",
        __func__, *(int*)argz);
    sem_post(&g_semaphore); // here the semaphore will get incremented again
    //free(argz);
    return NULL;
}


////////~~~~~~~~END> ut22.c
