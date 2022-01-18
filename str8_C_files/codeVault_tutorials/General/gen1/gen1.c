/*
    in the old days, you needed to talk to kernel
        find out it's settings
    
    implementation depends on OS

    the properway to use a timer for sleeping
*/

#include <locale.h>      // setlocale() , LC_NUMERIC
#include <math.h>        // floorf()
#include <stdlib.h>      // EXIT_SUCCESS , NULL
#include <stdio.h>       // printf() , 
#include <sys/time.h>    // gettimeofday()
#include <time.h>        // struct timespec
#include <unistd.h>      // sleep() , usleep()

#define TEST_TIME_SEC 3.9876    // change here
#define PAUSE_SEC 2             // change here
#define NS_PER_SEC 1000000000L    // L at end is good practice
#define NS_PER_US 1000
#define US_PER_SEC 1000000
#define GOOD 69
#define INIT_INT -999

int gv_status = INIT_INT;

int ex1();
void usleep_true(float time_sec);
int ex2();
int ex3();


int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();
    //gv_status = ex2();
    gv_status = ex3();

    printf("\n\n%s()  ,  status:  %d\n", __func__, gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  proper sleep for %f seconds\n",
        __func__, TEST_TIME_SEC);
    usleep_true(TEST_TIME_SEC);
    return GOOD;
}

void usleep_true(float time_sec)
{
    // consider guards, MONOTONIC timer increment, combo timespec and timeval
    printf("\n%s()  ,  proper sleep using timer...\n",
        __func__);

    if (time_sec <= 0)    // guard
    {
        printf("\n\t%s()  ,  invalid argument:  %f\n",
            __func__, TEST_TIME_SEC);
        return;
    }    

    setlocale(LC_NUMERIC, "");    // comma formats for large numbers

    // use a long int or something large enough to hold the values 10^9
    unsigned long int nanoSeconds = NS_PER_SEC * TEST_TIME_SEC; 
    printf("\n\t%s()  ,  %f s  =  %lu ns\n",
        __func__, TEST_TIME_SEC, nanoSeconds);

    // may have to step through in a loop
    //struct timespec ts_start;                     // reference start of interval
    //struct timespec ts_stop;                      // mark end of interval
    //ts_stop = ts_start;                           // equate
    //clock_gettime(CLOCK_MONOTONIC, &ts_start);    // use clock with procession only
    
    // "floor" must be whole seconds
    int seconds = (int)floorf(TEST_TIME_SEC);    
    printf("\n\t%s()  ,  there are { %d } whole seconds\n",
        __func__, seconds);
    
    // remainder is nano seconds
    nanoSeconds = nanoSeconds - (((unsigned long int)seconds) * NS_PER_SEC);    
    printf("\n\t%s()  ,  with { %lu } nano seconds\n", 
        __func__, nanoSeconds);
    
    // get micro seconds to sleep properly
    int micro_seconds = (int)(nanoSeconds / NS_PER_US);
    printf("\n\t%s()  ,  or with { %d } micro seconds\n",
        __func__, micro_seconds);
    
    sleep(seconds);
    usleep(micro_seconds);
    printf("\n\t%s()  ,  proper sleeping complete\n", __func__);
}

int ex2()
{
    printf("\n%s()  ,  use struct \"timespec\" as timer  ,  %d sec pause\n",
        __func__, PAUSE_SEC);

    struct timespec stcTS;

    clock_gettime(CLOCK_MONOTONIC, &stcTS);
    printf("\nsec:  %lu", stcTS.tv_sec);
    printf("\t\tns:   %lu\n", stcTS.tv_nsec);

    sleep(PAUSE_SEC);

    clock_gettime(CLOCK_MONOTONIC, &stcTS);
    printf("\nsec:  %lu", stcTS.tv_sec);
    printf("\t\tns:   %lu\n", stcTS.tv_nsec);

    return GOOD;
}


int ex3()
{
    printf("\n%s()  ,  using timer for date-time-stamp...\n",
        __func__);
    // another option:   time_t now = time(NULL); ...
    char dts[64];
    struct tm * stcTM;
    struct timeval stcTV;
    gettimeofday(&stcTV, NULL);
    if (stcTV.tv_usec >= 500000) {stcTV.tv_sec++;}
    stcTM = localtime(&stcTV.tv_sec);
    strftime(dts, 64, "%Y_%m_%d___%H:%M:%S", stcTM);
    printf("\ndate-time-stamp:  %s\n", dts);
    return GOOD;
}

////////~~~~~~~~END>  gen1.c
