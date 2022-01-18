/*
    the semaphore

    in a thread, use the semaphore to:
        1) wait {like a mutex lock}
        2) post {like a mutex unlock}
    
    ex1()  operation without semaphore
    ex2()  semaphore to control execution (almost like a mutex)

    sem_wait() checks value, if == 0, can't be decremented, it waits
                             > 0 , it will decrement and not wait
    
    sem_post()  does the reverse ... increments

    all the threads will also be working
    the initial value is very important, the counter controls what the threads can do
    between a sem_wait() and sem_post() is critical point

    a mutex with a counter, that lets you lock and control flow
    multiple locks with multiple threads
    ...mutex only lets one thread get the lock
    they are very useful
*/

//#include "apple_sem.h"    // apple fix
#include <pthread.h>
#include <semaphore.h>    // they live here
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define GOOD 69
#define THREADZ 5
#define INIT_INT -999

sem_t mySem;
int gv_status = INIT_INT;

int ex1();
void* routine1(void* arg);
int ex2();
void* routine2(void* arg);
int ex3();
void* routine3(void* arg);
int ex4();
void* routine4(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));

    //gv_status = ex1();
    //gv_status = ex2();
    gv_status = ex3();
    //gv_status = ex4();

    printf("\n\nstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
}


////~~~~ 1


int ex1()
{
    printf("\n%s()  ,  no semaphore\n", __func__);
    int t_id[THREADZ];
    pthread_t thz[THREADZ];
    sem_init(&mySem, 0, 1);    // ref, number processes, initial val

    for (int i = 0; i < THREADZ; i++)
    {
        t_id[i] = i;
        if (pthread_create(&thz[i], NULL, &routine1, &t_id[i]) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    sem_destroy(&mySem);
    return GOOD;
}


void* routine1(void* arg)
{
    printf("\tthread %d\n", *(int*)arg);
    return NULL;
}


////~~~~ 2


int ex2()
{
    printf("\n%s()  ,  a semaphore\n", __func__);
    int t_id[THREADZ];
    pthread_t thz[THREADZ];
    sem_init(&mySem, 0, 1);    // ref, number processes, initial val

    for (int i = 0; i < THREADZ; i++)
    {
        t_id[i] = i;
        if (pthread_create(&thz[i], NULL, &routine2, &t_id[i]) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    sem_destroy(&mySem);
    return GOOD;
}


void* routine2(void* arg)
{
    sem_wait(&mySem);    // only 1 thread at a time can get in here
    sleep(1);
    printf("\tthread %d\n", *(int*)arg);
    sem_post(&mySem);
    return NULL;
}


////~~~~ 3


int ex3()
{
    printf("\n%s()  ,  a semaphore, multiple threads allowed to run\n", __func__);
    int t_id[THREADZ];
    pthread_t thz[THREADZ];
    sem_init(&mySem, 0, 1);    // ref, number processes, initial val

    for (int i = 0; i < THREADZ; i++)
    {
        t_id[i] = i;
        if (pthread_create(&thz[i], NULL, &routine3, &t_id[i]) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("%s()  ,  error creating thread %d\n", 
                __func__, i);
            return i;
        }
    }

    sem_destroy(&mySem);
    return GOOD;
}


void* routine3(void* arg)
{
    sem_wait(&mySem);    // 2 threads at a time can get in here
    sleep(1);
    printf("\tthread %d\n", *(int*)arg);
    sem_post(&mySem);
    return NULL;
}

////////~~~~~~~~END>  ut21.c
