/*
    the race condition is back
    use a mutex to solve it... "lock" that section of code

    manually applying lock is acceptable
    if (lockControl == LOCKED) 
        {
            // wait until unlocked
            // lock var
        }
        lockControl = LOCKED;
        messages++;
        lockControl = UNLOCKED;
    but, POSIX thread API already has solution...  pthread_mutex_t

    pthreads want a void * func()
        you can return NULL
        or do pthread_exit(NULL);
    
    locking and unlocking mutex is the way to protect 
    other threads from executing at the same time
    mutex wrapper around section ensures only one thread is executing

    race conditions can only occur on multi-core processors
    single core processor makes it almost impossible to have a race condition
*/

// external libraries
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// macros
#define THREADZ 7
#define INIT_INT -999
#define ITERATIONS 1000000

// global constants
const int enforceMutex = 333;
const int noMutex = -333;

// global variables
int status = INIT_INT;
int messages = 0;
pthread_mutex_t pMute;

// function declarations
int ex_race();
void* race();
int ex_lock();
void* lock();
int ex_thread_arr(int select);    // for multiple ...the wrong way, see ut5 for right
void* thread_arr(int select);  


int main(int argc, char* argv[], char* envp[])
{
    //status = ex_race();
    //status = ex_lock();
    status = ex_thread_arr(enforceMutex);

    printf("\n\tstatus:  %d\n", status);
    printf("\n\n\t\t~ ~ ~  PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex_race(void)
{
    pthread_t p1;
    pthread_t p2;
    printf("\n<%d> %s()  ,  messages =  %d\n", 
        __LINE__, __func__, messages);

    if (pthread_create(&p1, NULL, &race, NULL) != 0) {return 1;}
    if (pthread_create(&p2, NULL, &race, NULL) != 0) {return 2;}
    if (pthread_join(p1, NULL) != 0) {return 3;}
    if (pthread_join(p2, NULL) != 0) {return 4;}

    printf("\n<%d> %s()  ,  messages =  %d  ,  should be:  %d\n", 
        __LINE__, __func__, messages, ITERATIONS*2);
    return 0;

}
void* race()
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        messages++;
    }
    //return NULL;          // either way, depends if you want return value
    pthread_exit(NULL);
}


int ex_lock()
{
    pthread_t p1;
    pthread_t p2;
    pthread_mutex_init(&pMute, NULL); // set your mutex  ...NULL is good for default
    printf("\n<%d> %s()  ,  messages =  %d\n", 
        __LINE__, __func__, messages);

    if (pthread_create(&p1, NULL, &lock, NULL) != 0) {return 1;}
    if (pthread_create(&p2, NULL, &lock, NULL) != 0) {return 2;}
    if (pthread_join(p1, NULL) != 0) {return 3;}
    if (pthread_join(p2, NULL) != 0) {return 4;}

    pthread_mutex_destroy(&pMute); // must deallocate
    printf("\n<%d> %s()  ,  messages =  %d  ,  should be:  %d\n", 
        __LINE__, __func__, messages, ITERATIONS*2);
    return 1776;

}
void* lock()
{
    for (int i = 0; i < ITERATIONS; i++) 
    {
        pthread_mutex_lock(&pMute); // does all the waiting for you
        messages++;
        pthread_mutex_unlock(&pMute); // even sets unlocked...
    }
    return NULL;         
}


int ex_thread_arr(int select)
{
    pthread_t threadArr[THREADZ];
    printf("\n<%d> %s()  ,  messages =  %d  ,  threads:  %d\n", 
        __LINE__, __func__, messages, THREADZ);
    if (select == enforceMutex)
    {
        pthread_mutex_init(&pMute, NULL);
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&threadArr[i], NULL, &thread_arr, &select) != 0)
        {return i;}
        if (pthread_join(threadArr[i], NULL) != 0) {return (-1*i);}
    }
    
    if (select == enforceMutex)
    {
        pthread_mutex_destroy(&pMute); 
    }
    printf("\n<%d> %s()  ,  messages =  %d  ,  should be:  %d\n", 
        __LINE__, __func__, messages, ITERATIONS*THREADZ);
    return 69;
}
void* thread_arr(int select)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        if (select == enforceMutex)
        {
            pthread_mutex_lock(&pMute);
            messages++;
            pthread_mutex_unlock(&pMute);
        }
        else
        {
            messages++;
        }
    }
    return NULL;
}

////////~~~~~~~~END> ut4.c
