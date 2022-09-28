/*
    pthread_exit() is another way to get out of thread
    pthread_exit() can replace return

    in main() , pthread_exit() enforces termination
        process owns multiple threads...
        if you return 0; from main()  , then it is main process and will kill all threads

    but, calling pthread_exit() in main() makes it wait for all other threads

    pthread_exit() is good if you want to start long running thread
    it won't matter if you join them
    process has to wait for other threads to finish
    lets process handle it

    pthread_exit() is not nescessary, but may come in use
    just return
    put pthread_exit() in main if you want to kill thread
    program and OS still have to kill the process
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define GOOD 69
#define DIE 2

int gv_status = GOOD;

int ex1();
void* roll_dice1(void* arg);
int ex2();
void* roll_dice2();


int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));

    //gv_status = ex1();
    gv_status = ex2();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  no exit , rolling...\n", __func__);
    pthread_t thz[DIE];
    int diceValue[DIE];

    for (int i = 0; i < DIE; i++)
    {
        diceValue[i] = GOOD;
        if (pthread_create(&thz[i], NULL, &roll_dice1, &diceValue[i]) != 0)
        {
            printf("\nerror creating thread %d\n", i+1);
            return (i+1);
        }
    }
    int sum = 0;
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nerror joining thread  %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
        printf("\ndie %d  =  %d\n", i+1, diceValue[i]);
        sum = sum + diceValue[i];
    }
    printf("\ncombined roll:  %d\n", sum);
    return GOOD;
}
void* roll_dice1(void* arg)
{
    int* temp = (int*)arg;
    *temp = (rand() % 6) + 1;
    temp = NULL;
    return NULL;
}


int ex2()
{
    printf("\n%s()  ,  uses exit , rolling...\n", __func__);
    pthread_t thz[DIE];
    int sum = 0;
    int* result;

    for (int i = 0; i < DIE; i++)
    {
        if (pthread_create(&thz[i], NULL, &roll_dice2, NULL) != 0)
        {
            printf("\nerror creating thread %d\n", i+1);
            return (i+1);
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(thz[i], (void**)&result) != 0)
        {
            printf("\nerror joining thread  %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
        printf("\ndie %d  =  %d\n", i+1, *(int*)result);
        sum = sum + *result;
        if (result != NULL) {free(result); result = NULL;}
    }
    printf("\ncombined roll:  %d\n", sum);
    return GOOD;
}
void* roll_dice2()
{
    int val = (rand() % 6) + 1;
    int* res = (int*)malloc(1*sizeof(int)); 
    *res = val;
    pthread_exit((void*)res); // no return needed
}

////////~~~~~~~~END>  ut13.c
