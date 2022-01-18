/*
    methods for the Location struct
*/

#include <pthread.h>
#include <stdio.h>

#include "LocationStruct.h"

extern const int gc_false;
extern const int gc_true;

void metInit(Location* ptr)
{
    if (ptr == NULL) {return;}

    printf("\n%s()  ,  initializing Location struct...\n", __func__);
    ptr->isReady = gc_false;
    for (int i = 0; i < ELEMENTS_LOCATION_STRUCT; i++)
    {
        ptr->data[i] = INIT_FLOAT;
    }
}


void metCopy(const Location* original, Location* duplicate)
{
    if (original == NULL || duplicate == NULL) {return;}

    if (original->isReady == gc_false) {metInit(duplicate); return;}

    duplicate->isReady = original->isReady;

    for (int i = 0; i < ELEMENTS_LOCATION_STRUCT; i++)
    {
        duplicate->data[i] = original->data[i];
    }
}


void metPrint(const Location* ptr)
{
    if (ptr == NULL) {return;}

    if (ptr->isReady != TRUE)
    {
        printf("\n%s()  ,  no data to print\n", __func__);
        return;
    }
    printf("\n%s()  ,  struct data:\n", __func__);
    for (int i = 0; i < ELEMENTS_LOCATION_STRUCT; i++)
    {
        printf("\tdata[%d] =  %f\n", i, ptr->data[i]);
    }
}

////////~~~~~~~~END>  LocationStruct.c
