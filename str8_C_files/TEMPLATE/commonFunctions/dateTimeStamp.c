/*
    provide a statically allocated string 
        of at least size "U5_DTS"
    updates string if <time.h> can be accessed

    these stamps chronologically order files
    "%Z_%Y_%m_%d___%H_%M_%S_%a" , 29 + 1 chars
*/

#include <stdlib.h>    // NULL
#include <string.h>    // memset() 
#include <time.h>      // struct tm , time_t , time() , gmtime() , strftime()

#include "dateTimeStamp.h"    // declared here

#include "../resources/globalMacros.h"

#if defined(DEBUG_ALL) || defined(DEBUG_dateTimeStamp)
    #include <stdio.h>    // printf()
#endif


void dateTimeStamp(char * dts)
{   
    #if defined(DEBUG_ALL) || defined(DEBUG_dateTimeStamp)
        PRINT_DEBUG_START();
        PRINT_DEBUG_ENTER(__FILE__, __func__, __LINE__);
    #endif

    if (dts == NULL) 
    { 
        #if defined(DEBUG_ALL) || defined(DEBUG_dateTimeStamp)
            PRINT_DEBUG_EXIT(__func__, __LINE__, "empty string");
            PRINT_DEBUG_STOP();
        #endif
        return; 
    }

    memset(dts, '\0', U5_DTS);
    #ifdef DEBUG_dateTimeStamp
        printf("\n\t%s()  ,  BP_1  ,  %s = { %s }\n", 
            __func__ , GET_NAME(dts) , dts);
    #endif

    // request current date and time in GMT format
    time_t currentTime;
    struct tm * ptr = NULL;
    currentTime = time(&currentTime);
    ptr = gmtime(&currentTime);          

    if (currentTime != -1 && ptr != NULL)
    {    
        strftime(dts, U5_DTS,
            "%Z_%Y_%m_%d___%H_%M_%S_%a", ptr);
    }
    #ifdef DEBUG_dateTimeStamp
        printf("\n\t%s()  ,  BP_2  ,  %s = { %s }\n", 
            __func__ , GET_NAME(dts) , dts);
    #endif

    #if defined(DEBUG_ALL) || defined(DEBUG_dateTimeStamp)
        PRINT_DEBUG_EXIT(__func__, __LINE__, "complete");
        PRINT_DEBUG_STOP();
    #endif
}

////////~~~~~~~~END>  dateTimeStamp.c
