/*
    basic pthread_mutex_timedlock()
    mutex takes absolute time
        simple, can be better than ptherad_cond_timedwait()
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SEC_TIME_OUT 4

int gv_val = -999;
pthread_mutex_t mute;

void* funSet(void* arg);
void* funGet(void* arg);


int main(int argc, char* argv[], char*envp[])
{
    srand(time(NULL));
    pthread_t thz[3];

    if (pthread_mutex_init(&mute, NULL) != 0)
    {
        printf("\nerror initializing mutex\n");
        return EXIT_FAILURE;
    }
    if (pthread_create(&thz[0], NULL, &funSet, NULL) != 0)
    {
        printf("\nerror creating thread 1\n");
        return EXIT_FAILURE;
    }
    sleep(1);    // ensure set
    if (pthread_create(&thz[1], NULL, &funGet, NULL) != 0)
    {
        printf("\nerror creating thread 2\n");
        return EXIT_FAILURE;
    }
    if (pthread_create(&thz[2], NULL, &funGet, NULL) != 0)
    {
        printf("\nerror creating thread 3\n");
        return EXIT_FAILURE;
    }

    printf("\n%s()  ,  threads created  ,  1 setter  ,  2 getters\n",
        __func__);

    if (pthread_join(thz[0], NULL) != 0)
    {
        printf("\nerror joining thread 1\n");
        return EXIT_FAILURE;
    }
    if (pthread_join(thz[1], NULL) != 0)
    {
        printf("\nerror joining thread 2\n");
        return EXIT_FAILURE;
    }
    if (pthread_join(thz[2], NULL) != 0)
    {
        printf("\nerror joining thread 3\n");
        return EXIT_FAILURE;
    }
    if (pthread_mutex_destroy(&mute) != 0)
    {
        printf("\nerror destroying mutex\n");
        return EXIT_FAILURE;
    }
    printf("\n%s()  ,  threads joined  ,  mutex destroyed\n", 
        __func__);

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


void* funSet(void* arg)
{
    pthread_mutex_lock(&mute);
    printf("\n\t%s()  ,  locked \"mute\"\n",
        __func__);

    gv_val = (rand() % 100) + 101;    // target value [100-200]

    printf("\n\t%s()  ,  value:  %d\n", 
        __func__, gv_val);
    pthread_mutex_unlock(&mute);
    printf("\n\t%s()  ,  unlocked \"mute\"\n", 
        __func__);
    return NULL;
}


void* funGet(void* arg)
{
    int result = -999;
    struct timespec stcTS;
    stcTS.tv_sec = SEC_TIME_OUT-1;
    stcTS.tv_sec = 0;

    result = pthread_mutex_timedlock(&mute, &stcTS);
    sleep(SEC_TIME_OUT);    // purposley time out other thread
    if (result != 0)
    {
        printf("\n\t\t%s()  ,  waiting for mutex lock has timed out\n",
            __func__);
        return NULL;    // notice there is no unlocking here...never got lock
    }
    printf("\n\t\t%s()  ,  locked mutex, value =  %d\n", 
        __func__, gv_val);
    pthread_mutex_unlock(&mute);    // must unlock
    return NULL;
}


////////~~~~~~~~  main.c
