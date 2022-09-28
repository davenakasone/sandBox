/*
    general template for making C program
    good for embedded
    "testing" should be deleted for final release
*/

#include <stdlib.h>    // NULL , EXIT_SUCCESS
#include <stdio.h>     // printf() , __FILE__ , __func__ , __LINE__
#include <time.h>      // clock() , time()

// declared here

// access to macros
#include "resources/globalMacros.h"
#ifdef MODE_TEST
    #include "testing/testing.h"
#endif

// access to functions
#include "commonFunctions/dateTimeStamp.h"
#include "commonFunctions/checkOut.h"

// access to global variables
extern clock_t gv_startProcessingTime;
extern time_t gv_startRunningTime;
extern char gv_startDTS[U5_DTS];

// access to global constants


int main(void)
//int main(int argc, char * argv[])
{
    // record the starting times
    dateTimeStamp(gv_startDTS);
    gv_startProcessingTime = clock();
    gv_startRunningTime = time(NULL);

    // unit tests, as needed
    #ifdef MODE_TEST
        //test_selector(0);    // test bench
        //test_selector(1);    // dateTimeStamp()
        //test_selector(2);    // makeNumbers.c
    #endif

    // finish
    checkOut();
    printf("\nFILE:  %s  ,  FUNCTION:  %s()  ,  LINE:  %d\n\n",
        __FILE__, __func__, __LINE__);
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  main.c
