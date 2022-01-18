/*
    static initializers

    ex1()  the standard way
    ex2()  use the built in macros to initialize

    many good MACROS
        you probably want to use traditional way when it counts
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define THREADZ 2
#define GOOD 69

int gv_status;

int ex1();
int ex2();
void* routine(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();
    gv_status = ex2();

    printf("\n\nstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  no static initializer\n", __func__);
    pthread_mutex_t mute;
    pthread_t thz[THREADZ];
    pthread_mutex_init(&mute, NULL);
    gv_status = GOOD;

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine, NULL) != 0)
        {
            printf("error creating thread %d\n", i);
            gv_status = i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("error joining thread %d\n", i);
            gv_status = i;
        }
    }

    pthread_mutex_destroy(&mute);
    return gv_status;
}


int ex2()
{
    printf("\n%s()  ,  no static initializer\n", __func__);
    pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;  // creates mutex nicely
        //loop through standard pthread_mutex_init() in an array

    pthread_t thz[THREADZ];
    //pthread_mutex_init(&mute, NULL);  no need to call
    gv_status = GOOD;

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine, NULL) != 0)
        {
            printf("error creating thread %d\n", i);
            gv_status = i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("error joining thread %d\n", i);
            gv_status = i;
        }
    }

    pthread_mutex_destroy(&mute);  // a good thing, but not mandatory
    return gv_status;
}


void* routine(void* arg)
{
    printf("\n\t%s()  ,  a thread completed the routine\n",__func__);
    return NULL;
}

////////~~~~~~~~END>  ut18.c
