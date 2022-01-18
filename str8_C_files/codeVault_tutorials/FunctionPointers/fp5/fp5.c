/*
    common application of function pointers:

    searching

    void* are nice because you can pass any type, but be careful

    the idea is to stop redundancy
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GET_NAME(var) #var
#define START 11
#define STOP 15
#define ARR_SIZE 9
#define INIT_INT -999

int randomInt(int start, int stop);
bool compare(const void* a, const void* b) {return ( *(int*)a == *(int*)b ); }
int search(void* arr, int arrSize, int elmSize, void* searchTerm,
            bool compare(const void*, const void*));

int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));    // seed
    int arrInt[ARR_SIZE];
    int searchNum = randomInt(START, STOP); // what to search for

    printf("\ninital array:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        arrInt[i] = randomInt(START, STOP);
        printf("%s[%d] =  %d\n", 
            GET_NAME(arrInt), i, arrInt[i]);
    }
    
    printf("\n***************************\n");
    int result = search(arrInt, ARR_SIZE, sizeof(int), &searchNum, compare);
    if (result < 0) {printf("\nsearch term %d not found\n", searchNum);}
    else{printf("\nsearch term %d  ,  found @ index %d\n", searchNum, result);}

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


int search(void* arr, int arrSize, int elmSize, void* searchTerm,
            bool compare(const void*, const void*))
{
    char* ptr = (char*)arr; // know char == 1 byte
    for(int i = 0; i < arrSize; i++)
    {
        if(compare((ptr + i*elmSize), searchTerm))
        {
            return i;
        }
    }
    return INIT_INT;
}


////////~~~~~~~~END>  fp5.c
