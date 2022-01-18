/*
    detach threads 
    no longer joinable...can't wait for it to finish before executing
    they clear their own resources
    do not call pthread_join()

    use pthread_exit(0); in main
    just don't have main thread stop before other threads

    detached thread is good if you have a long running process
        main thread can exit, then someone else can use
    
    pthread_exit() helps to wait for all threads

    create it the right way
        but be sure to kill it smartly before crashing out of program
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define GOOD 69
#define INIT_INT -999
#define THREADZ 4

int ex1();
void* routine1(void* arg);

void* ex2();
void* routine2(void* arg);

int main(int argc, char* argv[], char* envp[])
{
    int status = INIT_INT;
    //status = ex1();    // easy way
    void* statuss;
    statuss = ex2();    // correct way

    printf("\n\n\tstatus:  %d\n", status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

int ex1()
{
    printf("\n%s()  ,  basic detached threads:\n", __func__);
    pthread_t thz[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thz[i], NULL, &routine1, NULL) != 0)
        {
            printf("\n%s()  ,  error creating thread %d\n", __func__, i+1);
            return (i+1);
        }
        pthread_detach(thz[i]);    // not the best way
    }
    //pthread_exit(NULL);
    return GOOD;
}
void* routine1(void* arg)
{
    printf("\n%s()  ,  routine executed\n", __func__);
    return NULL;
}


void* ex2()
{
    printf("\n%s()  ,  create a detached thread the correct way\n", __func__);
    pthread_t thz[THREADZ];
    pthread_attr_t dthz[THREADZ];
    int track[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        track[i] = i+1;
        if (pthread_attr_init(&dthz[i]) != 0)
        {
            printf("\n%s()  ,  error with attr %d\n", __func__, i+1);
        }
        if (pthread_attr_setdetachstate(&dthz[i], PTHREAD_CREATE_DETACHED) != 0)
        {
            printf("\n%s()  ,  error setting attr %d\n", __func__, i+1);
            //return (i+1);
        }
        if (pthread_create(&thz[i], &dthz[i], &routine2, (void*)&track[i]) != 0)
        {
            printf("\n%s()  ,  error creating thread %d\n", __func__, i+1);
            //return i+1;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_attr_destroy(&dthz[i]) != 0)
        {
            printf("\n%s()  ,  error destroying attr  %d\n", __func__, i+1);
            //return (-1*(i+1));
        }
    }
    return NULL;
    //return GOOD;       // does not wait
    //pthread_exit(NULL);  // auto kill, even kills self
}
void* routine2(void* arg)
{
    int* temp = (int*)arg;
        printf("%s()  ,  thread  %d  ...\n", 
            __func__, *temp);
        sleep(2); // may not even get a chance
    return NULL;
}

////////~~~~~~~~END>  ut17.c
