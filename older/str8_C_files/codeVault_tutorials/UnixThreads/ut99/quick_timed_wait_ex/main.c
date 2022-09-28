/*
    a quick example with pthread_cond_timedwait()
    it is thread safe: multi-threaded application is ensured
    it is not "signal safe" : need to handle multiple calls ...async

    calling thread needs a mutex lock
        pthread_cond_timedwait() blocks until signal/broadcast
            atomic through condition var interface
    
    calling thread automatically gets the mutex if:
        - cancelled
        - times out
        - aquired signal/broadcast
    
    if you try to call with unlocked mutex, EPERM error
    only associate one mutex with one cond var at a time

    waiting through abstime parameter as an absolute system time
    if sys clock passes absolute time before condition signal/broadcase, ETIMEDOUT error
    when the wait time begins, sys clock has no effect
    don't think nano seconds will work if you don't have the hardware for it

    do some lock_spin if you have a lot of coordination

    This one intentionally blocks all the threads so you can see them time out
*/

#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define THREADZ 3
#define WAIT_US 10000
#define NAP_US 500000
#define INIT_INT -999

const int gc_wait_sec = 4;

bool work2do = false;
int gv_status = INIT_INT;
pthread_cond_t conditional;
pthread_mutex_t mutuallyExternal;

void* funThread(void* arg);
void printStatus(const char* msg, const char* func, int stat);

int main(int argc, char*argv[], char* envp[])
{
    printf("\n");
    pthread_t thz[THREADZ];

    gv_status = pthread_mutex_init(&mutuallyExternal, NULL);
    if (gv_status != 0) {printStatus("error initializing mutex", __func__, gv_status);}
    gv_status = pthread_cond_init(&conditional, NULL);
    if (gv_status != 0) {printStatus("error initializing cond", __func__, gv_status);}

    gv_status = pthread_mutex_lock(&mutuallyExternal);
    if (gv_status != 0) {printStatus("error locking mutex", __func__, gv_status);}

    printf("giving 1 work task to 1 thread...\n");
    work2do = true;

    gv_status = pthread_mutex_unlock(&mutuallyExternal);
    if (gv_status != 0) {printStatus("error unlocking mutex", __func__, gv_status);}

    //gv_status = pthread_cond_signal(&conditional);
    //if (gv_status != 0) {printStatus("error sending signal", __func__, gv_status);}
    gv_status = pthread_cond_broadcast(&conditional);

    if (gv_status != 0) {printStatus("error broadcasting signal", __func__, gv_status);}

    for (int i = 0; i < THREADZ; i++)
    {
        gv_status = pthread_create(&thz[i], NULL, &funThread, NULL);
        if (gv_status != 0) {printStatus("error creating thread", __func__, gv_status);}
        printf("thread %d of %d created\n", i+1, THREADZ);
    }

    

    for (int i = 0; i < THREADZ; i++)
    {
        gv_status = pthread_join(thz[i], NULL);
        if (gv_status != 0) {printStatus("error joining thred", __func__, gv_status);}
        printf("thread %d of %d joined\n", i+1, THREADZ);
    }

    pthread_mutex_destroy(&mutuallyExternal);
    if (gv_status != 0) {printStatus("error destroying mutex", __func__, gv_status);}
    pthread_cond_destroy(&conditional);
    if (gv_status != 0) {printStatus("error destroying cond", __func__, gv_status);}

    printf("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


void* funThread(void* arg)
{
    struct timespec stcTS;
    struct timeval stcTV;    // has us ... many other ways to do this

    gv_status = pthread_mutex_lock(&mutuallyExternal);
    if (gv_status != 0) {printStatus("mutex lock error", __func__, gv_status);}
    
    // this is where worker threads get going
    while(1)
    {
        //gv_status = timer_gettime(NULL, &stcTS);
        // go for the conversion
        gv_status = gettimeofday(&stcTV, NULL);
        if (gv_status != 0) {printStatus("error getting time", __func__, gv_status);}
        //stcTS.tv_sec = stcTV.tv_sec;
        //stcTS.tv_nsec = stcTS.tv_nsec + 
        //    ( (stcTV.tv_usec + WAIT_US) * 1000); // increment "us" or "s"
        stcTS.tv_sec = stcTV.tv_sec + gc_wait_sec;    
        stcTS.tv_nsec = stcTS.tv_nsec + (stcTV.tv_usec * 1000);

        while(work2do == false)    // wait for work to do
        {
            printf("\t%s()  ,  thread blocked\n", __func__);
            gv_status = pthread_cond_timedwait(&conditional, &mutuallyExternal, &stcTS);

            // if worked timed out, work is complete and thread ends
            // be sure to verify time out, and don't exit with a locked mutex
            if (gv_status == ETIMEDOUT ||
                gv_status != 0          )
            {
                printf("\t%s()  ,  waiting timed out\n", __func__);
                gv_status = pthread_mutex_unlock(&mutuallyExternal);    // important
                pthread_exit(NULL); // out of loop
            }
            pthread_mutex_unlock(&mutuallyExternal);
            usleep(NAP_US*2);
            pthread_mutex_lock(&mutuallyExternal);
        }
        printf("\t%s()  ,  thread got the job done\n", __func__);
        work2do = false;    // the work just got done
    }

    gv_status = pthread_mutex_unlock(&mutuallyExternal);
    if (gv_status != 0) {printStatus("error unlocking mutex", __func__, gv_status);}
    return NULL;
}


void printStatus(const char* msg, const char* func, int stat)
{
    printf("%s()  ,  %s  ,  status:  %d\n", func, msg, stat);
}

////////~~~~~~~~END>  main.c
