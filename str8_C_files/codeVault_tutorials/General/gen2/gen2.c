/*
    ex1()  rounding, ceiling, floor
    ex2()  type casts, implied behvior
*/

// libraries
#include <math.h>
//#include <locale.h>    // setlocale() , LC_NUMERIC
#include <stdio.h>	
#include <stdlib.h>	


#define TEST_VAL 9.4999         // change here
#define TEST_TIME_SEC 3.9876    // change here
#define NS_PER_SEC 1000000000    
#define NS_PER_MS 1000
#define MS_PER_SEC 1000000
//const unsigned long int gc_ns_per_sec = (unsigned long int)pow(10,9); 

void ex1();
void ex2();

int main(int argc, char* argv[], char* envp[])
{
    //ex1();
    ex2();

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


void ex1()
{
    printf("\n%s()  ,  basic rounding, floors, ceilings...\n",
        __func__);

    int test_int_ceil = (int)ceilf(TEST_VAL);
    int test_int_floor = (int)floorf(TEST_VAL);
    int test_int_roundf = (int)roundf(TEST_VAL);

    printf("\n\t%s()  ,  \"ceilf\" of %f =  %d\n", 
        __func__, TEST_VAL, test_int_ceil);
    printf("\n\t%s()  ,  \"floorf\" of %f =  %d\n", 
        __func__, TEST_VAL, test_int_floor);
    printf("\n\t%s()  ,  \"roundf\" of %f =  %d", 
        __func__, TEST_VAL, test_int_roundf);
}


void ex2()
{
    //setlocale(LC_NUMERIC, "");    // comma formats for large numbers

    printf("\n%s()  ,  rounding and casting with time conversion...\n",
        __func__);
    
    // use a long int or something large enough to hold the values 10^9
    unsigned long int nanoSeconds = NS_PER_SEC * TEST_TIME_SEC; 
    printf("\n\t%s()  ,  %f s  =  %lu ns\n",
        __func__, TEST_TIME_SEC, nanoSeconds);
    
    // "floor" must be whole seconds
    int seconds = (int)floorf(TEST_TIME_SEC);    
    printf("\n\t%s()  ,  there are { %d } whole seconds\n",
        __func__, seconds);
    
    // remainder is nano seconds
    nanoSeconds = nanoSeconds - (((unsigned long int)seconds) * NS_PER_SEC);    
    printf("\n\t%s()  ,  with { %lu } nano seconds\n", 
        __func__, nanoSeconds);
    
    // get micro seconds to sleep properly
    int micro_seconds = (int)(nanoSeconds / NS_PER_MS);
    printf("\n\t%s()  ,  or with { %d } micro seconds\n",
        __func__, micro_seconds);
    
}

////////~~~~~~~~END>  gen2.c
