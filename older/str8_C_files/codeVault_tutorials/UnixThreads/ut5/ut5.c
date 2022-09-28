/*
    make pthreads in a loop

    wrong() shows you don't get multiple threads running
    ...you wanted it to run in parallel
    don't put create && join with the same loop ==> sequential exec

    if you have 8 cores...  make 8 threads

    fyi, printf's don't mean thread[2] finished 3rd...
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define THREADZ 7
#define ITERATIONS 1000000

int messages = 0;
int status = -999;
pthread_mutex_t pMute;

int ex_wrong();
void* wrong();
int ex_correct();
void* correct();


int main(int argc, char* argv[], char* envp[])
{
    //status = ex_wrong();
    status = ex_correct();

    printf("\n\nstatus:  %d\n", status);
    printf("\t ~ ~ ~ PROGRAM COMPELTE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex_wrong()
{
    pthread_t th[THREADZ];
    pthread_mutex_init(&pMute, NULL);
    printf("\n%s()  ,  threads:  %d  ,  iterations:  %d\n",
        __func__, THREADZ, ITERATIONS);

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&th[i], NULL, &wrong, NULL) != 0)
        {
            printf("\n\t%s()  ,  failed to create thread %d\n",
                __func__, i);
            return -111;
        }
        printf("\nthread[%d] started...\n", i);
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("\n\t%s()  ,  failed to join pthread  %d\n",
                __func__, i);
            return 111;
        }
        printf("\tthread[%d] finished\n", i);
    }

    pthread_mutex_destroy(&pMute);
    printf("\n\t!!! no multi threading, execution sequential !!!\n");
    printf("\n%s()  ,  messages:  %d  ,  expected:  %d\n",
        __func__, messages, ITERATIONS*THREADZ);
    return 69;
}
void* wrong()
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        pthread_mutex_lock(&pMute);
        messages++;
        pthread_mutex_unlock(&pMute);
    }
    return NULL;
}


int ex_correct()
{
    pthread_t th[THREADZ];
    pthread_mutex_init(&pMute, NULL);
    printf("\n%s()  ,  threads:  %d  ,  iterations:  %d\n",
        __func__, THREADZ, ITERATIONS);

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&th[i], NULL, &wrong, NULL) != 0)
        {
            printf("\n\t%s()  ,  failed to create thread %d\n",
                __func__, i);
            return -111;
        }
        printf("\nthread[%d] started...\n", i);
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("\n\t%s()  ,  failed to join pthread  %d\n",
                __func__, i);
            return 111;
        }
        printf("\tthread[%d] finished\n", i);
    }

    pthread_mutex_destroy(&pMute);
    printf("\n\t!!! multi threading worked, execution in parallel!!!\n");
    printf("\n%s()  ,  messages:  %d  ,  expected:  %d\n",
        __func__, messages, ITERATIONS*THREADZ);
    return 69;
}
void* correct()
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        pthread_mutex_lock(&pMute);
        messages++;
        pthread_mutex_unlock(&pMute);
    }
    return NULL;
}

////////~~~~~~~~END>  ut5.c
