/*
    common application of function pointers:

    qsort()

    just write a good compare function

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GET_NAME(var) #var
#define START 10
#define STOP 20
#define ARR_SIZE 6
#define INIT_INT -999

int randomInt(int start, int stop);
int compare(const void* a, const void* b) {return ( *(int*)a - *(int*)b ); }

int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));    // seed
    int arrInt[ARR_SIZE];
    printf("\ninital array:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        arrInt[i] = randomInt(START, STOP);
        printf("%s[%d] =  %d\n", 
            GET_NAME(arrInt), i, arrInt[i]);
    }

    qsort(arrInt, ARR_SIZE, sizeof(int), compare);
    
    printf("\n***************************\n");
    printf("\nsorted array:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%s[%d] =  %d\n", 
            GET_NAME(arrInt), i, arrInt[i]);
    }

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ \n\n");
    return EXIT_SUCCESS;
}


int randomInt(int start, int stop)
{
    if (start >= stop) { return INIT_INT; }

    int16_t diff = (stop - start) + 1;
    int16_t result = ( ( rand() % diff ) + start );
    return result;
}

////////~~~~~~~~END>  fp4.c
