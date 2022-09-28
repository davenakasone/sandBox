/*
    tests "dateTimeStamp()"
*/

#include <stdlib.h>    // NULL
#include <stdio.h>     // printf() , fopen() , fclose() , fputs() , snprintf()
#include <string.h>    // strnlen() , memset() , strncpy()
#include <unistd.h>    // sleep()

#include "../testing.h"    // declared here

#include "../../resources/globalMacros.h"

#include "../../commonFunctions/dateTimeStamp.h"

extern const char tc_generalIO[];


void tu_dateTimeStamp()
{
    // do not adjust
    char holder[U5_DTS];
    char temp[ARR_BUF_U6];
    FILE * fp = NULL;


    printf("\n%s()  ,  START\n", __func__);


    printf("\n\t%s()  ,  1  ,  get date-time-stamp:\n", __func__);
    memset(holder, '\0', U5_DTS);
    printf("\n\tnewly allocated, %s = { %s }  ,  strnlen:  %d\n",
        GET_NAME(holder), holder, (int)strnlen(holder, U5_DTS-1));
    dateTimeStamp(holder);
    printf("\n\tupdated, %s = { %s }  ,  strnlen:  %d\n",
        GET_NAME(holder), holder, (int)strnlen(holder, U5_DTS-1));
    waitEnterClear();


    printf("\n\t%s()  ,  2  ,  get after delay:\n", __func__);
    dateTimeStamp(holder);
    printf("\n\tpast stamp, %s =    { %s }  ,  strnlen:  %d\n",
        GET_NAME(holder), holder, (int)strnlen(holder, U5_DTS-1));
    sleep(4);
    dateTimeStamp(holder);
    printf("\n\tpresent stamp, %s = { %s }  ,  strnlen:  %d\n",
        GET_NAME(holder), holder, (int)strnlen(holder, U5_DTS-1));
    waitEnterClear();

    
    printf("\n\t%s()  ,  3  , copy the date-time-stamp:\n", __func__);
    dateTimeStamp(holder);
    strncpy(temp, holder, ARR_BUF_U6-1);
    printf("\n\t%s = { %s }\n", GET_NAME(holder), holder);
    printf("\n\t%s   = { %s }\n", GET_NAME(temp), temp);
    waitEnterClear();

    
    fp = fopen(tc_generalIO, "w");
    fclose(fp);
    fp = NULL;
    printf("\n\t%s()  ,  4  ,  write date-time-stamp to .txt:\n", __func__);
    dateTimeStamp(holder);
    snprintf(temp, ARR_BUF_U6-1, "\n\t%s\n", holder);
    fp = fopen(tc_generalIO, "w");
    fputs(temp, fp);
    printf("\n\tcheck \"%s\"\n", tc_generalIO);
    fclose(fp);
    fp = NULL;


    printf("\n%s()  ,  STOP\n", __func__);
    waitEnterClear();
    fp = fopen(tc_generalIO, "w");
    fclose(fp);
    fp = NULL;
}

////////~~~~~~~~END>  tu_dateTimeStamp.c
