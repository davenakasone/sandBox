/*
    split array in half, get value, sum
    there is a way to do it static and dynamic
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define INIT_INT -999
#define THREADZ 2
#define ELEMENTS 10
#define GOOD 69

int gv_status = INIT_INT;
int gv_arr[ELEMENTS] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void startMe();
int option1();
void* add_dynamic(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    startMe();
    gv_status = option1();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

int option1()
{
    printf("\n\t%s()  ,  dynamic...\n", __func__);
    pthread_t thz[THREADZ];

    for (int i = 0; i < THREADZ; i++)
    {
        int* thdIdx = (int*) malloc(sizeof(int));
        *thdIdx = i*5; // 0 for [0,4] , 5 for [5,9]  , 5 each
        if (pthread_create(&thz[i], NULL, &add_dynamic, thdIdx) != 0)
        {
            printf("\nerror creating thread %d\n", i);
            return (i+5);
        }
    }
    int totalSum = 0;
    for (int i = 0; i < THREADZ; i++)
    {
        int* result;
        if (pthread_join(thz[i], (void**)&result) != 0)
        {
            printf("\nerror joining thread %d\n", i);
            return (-1*(i+5));
        }
        totalSum = totalSum + (*result);
        printf("\n\t%s()  ,  sum %d :  %4d  ,  address:  %p\n",
            __func__, i, *result, result);
        free(result);
    }
    printf("\n\t%s()  ,  final sum:  %d\n", __func__, totalSum);
    return GOOD;
}


void* add_dynamic(void* arg)
{
    int index = *(int*)arg;
    int sum = 0;
    for (int j = 0; j < (ELEMENTS/2); j++)
    {
        sum = sum + gv_arr[j+index];
        printf("\n\tarr[%d] =  %d  ,  sum:  %d\n",
            j+index, gv_arr[j+index], sum);
    }
    printf("\n***********************************     address:  %p\n", arg);
    *(int*)arg = sum;
    return arg;
}


void startMe()
{
    printf("\nelements:  %d  ,  array-->  { ", ELEMENTS);
    for(int i = 0; i < ELEMENTS; i++)
    {
        if (i == ELEMENTS-1)
        {
            printf("%d }\n", gv_arr[i]);
        }
        else
        {
            printf("%d, ", gv_arr[i]);
        }
    }
}

////////~~~~~~~~END>  ut8.c




/*    figure out the static

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define INIT_INT -999
#define THREADZ 2
#define ELEMENTS 5
#define START 1
#define STOP 9
#define GOOD 69

int gv_status = INIT_INT;
int gv_arr[ELEMENTS];

typedef struct
{
    int marker;
    int beginIdx;
    int endIdx;
    int sumSpan;
}stc_args;

void startMe();
int randomInt(int start, int stop);
int option1();
void* add_static(stc_args* ptr);
void initStruct(stc_args* ptr);


int main(int argc, char* argv[], char* envp[])
{
    startMe();
    gv_status = option1();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

int option1()
{
    printf("\n\t%s()  ,  dynamic...\n", __func__);
    return GOOD;
}




void startMe()
{
    printf("\nelements:  %d  ,  array--> { ", ELEMENTS);
    for(int i = 0; i < ELEMENTS; i++)
    {
        gv_arr[i] = randomInt(START, STOP);
        if (i == ELEMENTS-1)
        {
            printf("%d }\n", gv_arr[i]);
        }
        else
        {
            printf("%d, ", gv_arr[i]);
        }
    }
}


int randomInt(int start, int stop)
{
    if (start >= stop) { return INIT_INT; }

    int16_t diff = (stop - start) + 1;
    int16_t result = ( ( rand() % diff ) + start );
    return result;
}

////////~~~~~~~~END>  ut8.c

*/