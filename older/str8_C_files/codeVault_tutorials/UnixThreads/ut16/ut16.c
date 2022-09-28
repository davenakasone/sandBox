/*
    looking into "pthread_t"
    ...it is a big powerful library, but best thread API there is

    the "unsinged long int" thread ID is what API uses to talk
    pthread_self() is good for getting ID

    don't think that unsigned long int is a number  just for demonstartion
    it is an opaque type...literally could be anything
    don't try to work with values themselves
    you can assign though

    gettid() will get you the thread ID, but it is complex
        specific to Linux
    
    notice the value of pthread_t is not the ID ...
    and it does not work on macOSX
    the hierarchy: your program, ptherad API, OS
    the "tid" is specific to your OS

    

*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>    // gettid()
#include <time.h>
#include <unistd.h>

#define GET_NAME(var) #var
#define THREADZ 4
#define INIT_INT -999
#define GOOD 69

int gv_status = INIT_INT;

int ex1();
void* routine1(void* arg);

int ex2();
void* routine2();

int ex3();
void* routine3();

int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();    // see ID with return value
    //gv_status = ex2();    // see pthread_self()
    gv_status = ex3();    // get thread ID

    printf("\n\nstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  pthread_t is an \"unsigned long\"  :\n", __func__);
    pthread_t thz[THREADZ];
    unsigned long int track [THREADZ][2];

    for (int i = 0; i < THREADZ; i++)
    {
        track[i][0] = i+1;
        if(pthread_create(&thz[i], NULL, &routine1, (void*)(&track[i][0])) != 0)
        {
            printf("\n%s()  ,  error creating thread %d\n", __func__, i+1);
            return (i+1);
        }
        printf("\n%s()  ,  created thread %lu>  thread id:  %lu\n",
            __func__, track[i][0], (unsigned long int)thz[i]);
    }
    unsigned long int* catch = NULL;    // the key to return value...
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], (void**)&catch) != 0)
        {
            printf("\n%s()  ,  error joining thread %d\n", __func__, i+1);
            return (-1*(i+1));
        }
        track[i][1] = *catch;    // boom
        printf("\n%s()  ,  joined thread %lu>  thread id:  %lu\n",
            __func__, track[i][0], (unsigned long int)thz[i]);
    }
    return GOOD;
}
void* routine1(void* arg)
{
    int* temp = (int*)arg;
    printf("\n%s()  ,  thread %d routine\n", __func__, *temp);
    temp = NULL;
    return arg;
}


int ex2()
{
    printf("\n%s()  ,  pthread_self() should give 2 prints:\n", __func__);
    pthread_t thz[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine2, NULL) != 0)
        {
            printf("\n%s()  ,  error creating thread %d\n", __func__, i+1);
            return (i+1);
        }
        printf("\n%s()  ,       thread ID:  %lu\n", 
            __func__, (unsigned long int)thz[i]);
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\n%s()  ,  error joining thread %d\n", __func__, i+1);
            return (-1*(i+1));
        }
    }
    return GOOD;
}
void* routine2()
{
    pthread_t temp = pthread_self();
    printf("\n%s()  ,  thread ID:  %lu\n", 
        __func__, (unsigned long int)temp);
    return NULL;
}


int ex3()
{
    printf("\n%s()  ,  for thread ID use gettid():\n", __func__);
    pthread_t thz[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine3, NULL) != 0)
        {
            printf("\n%s()  ,  error creating thread %d\n", __func__, i+1);
            return (i+1);
        }
        printf("\n%s()  ,       thread ID:  %lu\n", 
            __func__, (unsigned long int)thz[i]);
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\n%s()  ,  error joining thread %d\n", __func__, i+1);
            return (-1*(i+1));
        }
    }
    return GOOD;
}
void* routine3()
{
    printf("\n%s()  ,  thread ID:  %d\n", __func__, (pid_t)syscall(SYS_gettid));
    return NULL;
}

////////~~~~~~~~END>  ut16.c
