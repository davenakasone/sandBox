/*
    pthread_trylock()   not same as pthread_lock

    with trylock()  ...you try to lock mutex
    have to check return value, 0 if locked, other if not

    _trylock() is not a guaruntee
        execution continues...no mandatory waiting
*/

#include <errno.h>    // EBUSY
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define INIT_INT -999
#define THREADZ 4
#define GOOD 69

int gv_status = INIT_INT;
pthread_mutex_t pMute;
int reffs[THREADZ];

int ex1();    // regular lock
void* routine_lock(void* arg);
int ex2();    // trylock
void* routine_tryLock(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();    // pthread_lock()
    gv_status = ex2();    // pthread_trylock()

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n\t%s()  ,  regular pthread_lock:\n", __func__);
    pthread_t thz[THREADZ];
    pthread_mutex_init(&pMute, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        reffs[i] = i;
        if (pthread_create(&thz[i], NULL, &routine_lock, (void*)&reffs[i]) != 0)
        {
            printf("\nerror in creating thread %d\n", i);
            return i;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {

        if (pthread_join(thz[i], (void**)&reffs[i]) != 0)
        {
            printf("\nerror in joining thread %d\n", i);
            return (-1*i);
        }
        printf("\n\targ returned:  %d  ,  %p\n", i, &reffs[i]);
    }

    pthread_mutex_destroy(&pMute);
    printf("\n************************************************************\n");
    return GOOD;
}
void* routine_lock(void* arg)
{
    int * idx = (int*)arg;
    pthread_mutex_lock(&pMute);
    printf("\ngot lock:  %d  ,  %p\n", *idx, idx);
    sleep(1); // this will change things...all threads start executing, but onl 1 can lock
    pthread_mutex_unlock(&pMute);
    return arg;
}


int ex2()
{
    printf("\n\t%s()  ,  pthread_trylock:\n", __func__);
    pthread_t thz[THREADZ];
    pthread_mutex_init(&pMute, NULL);

    for (int i = 0; i < THREADZ; i++)
    {
        reffs[i] = i;
        if (pthread_create(&thz[i], NULL, &routine_tryLock, (void*)&reffs[i]) != 0)
        {
            printf("\nerror in creating thread %d\n", i);
            return i;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {

        if (pthread_join(thz[i], (void**)&reffs[i]) != 0)
        {
            printf("\nerror in joining thread %d\n", i);
            return (-1*i);
        }
        printf("\n\targ returned:  %d  ,  %p\n", i, &reffs[i]);
    }

    pthread_mutex_destroy(&pMute);
    printf("\n************************************************************\n");
    return GOOD;
}
void* routine_tryLock(void* arg)
{
    int * idx = (int*)arg;
    int stat = INIT_INT;
    stat = pthread_mutex_trylock(&pMute);
    if ( stat == 0)
    {
        printf("\ngot lock:  %d  ,  %p\n", *idx, idx);
        sleep(1); 
        pthread_mutex_unlock(&pMute); // still applies
    }
    else
    {
        if (stat == EBUSY)
        {
            printf("\nEBUSY:  %d  ,  %p\n", *idx, idx);
        }
        else
        {
            printf("\nno lock:  %d  ,  %p\n", *idx, idx);
        }
    }
    return arg;
}

////////~~~~~~~~END>  ut9.c
