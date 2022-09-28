/*
    macros to off load heavy operations
    macros of known constants [data type not enforced]
*/

#ifndef H_globalMacros
#define H_globalMacros

#include <stdio.h>    // printf() , snprintf() , fputs()


// select 1 operating mode
#define MODE_TEST 1111     //~~{on-off} , text inputs to stimulate
//#define MODE_BARE -1111    //~~{off-on} , serial inputs on embedded device

// select 1 xxx
#define xxx_1 1492    //~~{on-off-off}
#define xxx_2 1776    //~~{off-on-off}
#define xxx_3 1917    //~~{off-off-on}


////~~~~ debug, 7000 series, select any combonation
#define GET_NAME(variable) #variable

#define PRINT_DEBUG_START()\
    printf("\nDEBUG**********************************************************************DEBUG");

#define PRINT_DEBUG_STOP()\
    printf("DEBUG**********************************************************************DEBUG\n");

#define PRINT_DEBUG_ENTER(file, function, line)\
    printf("\n%s  ,  %s()  ,  LINE: %d  --->>>\n", file, function, line);

#define PRINT_DEBUG_EXIT(function, line, status)\
    printf("\nEND>>>  %s() , LINE: %d  ,  %s  <<<END\n", function, line, status);

//#define DEBUG_ALL 7000    //~~{on-off}
//#define DEBUG_dateTimeStamp 7001    //~~{on-off}


////~~~~ known constants
#define INIT_INT -999          // initialization of integers
#define INIT_FLOAT -999.999    // initialization of doubles and floats
#define TRUE 1                 // equivalent bool value, true
#define FALSE 0                // equivalent bool value, false


////~~~~ sizing
#define ARR_BUF_U4 16    // 0000 to 1111 , 4 bits {0,15} , 16 representations, 2^4
#define ARR_BUF_U5 32    // 0 0000 to 1 1111 , 5 bits {0,31} , 32 representations, 2^5
#define ARR_BUF_U6 64    // 00 0000 to 11 1111 , 6 bits {0,63} , 64 representations, 2^6
#define ARR_BUF_U7 128   // 000 0000 to 111 1111 , 7 bits {0,127} , 128 representations, 2^7
#define ARR_BUF_U8 256   // 0000 0000 to 1111 1111 , 8 bits {0,255} , 256 representations, 2^8
#define ARR_BUF_U9 512   // 0 0000 0000 to 1 1111 1111 , 9 bits {0,511} , 512 representations, 2^9
#define ARR_BUF_U10 1024 // 00 0000 0000 to 11 1111 1111 , 10 bits {0,1023} , 1024 representations , 2^10

#define U5_DTS 30    // date-time-stamp format: "%Z_%Y_%m_%d___%H_%M_%S_%a" , 29 + 1 char


////~~~~ printing, make repetitive "format" in "globalConstants.c"
#define PRINT_1ARG(format, arg)\
    printf(format, arg);

#define PRINT_2ARG(format, arg1, arg2)\
    printf(format, arg1, arg2);

#define PRINT_3ARG(format, arg1, arg2, arg3)\
    printf(format, arg1, arg2, arg3);

#define PRINT_4ARG(format, arg1, arg2, arg3, arg4)\
    printf(format, arg1, arg2, arg3, arg4);


////~~~~ writing, make repetitive "format" in "globalConstants.c"
#define WRITE_1ARG(helper, format, arg, fp)\
    snprintf(helper, ARR_BUFF_U8, format, arg);\
    fputs(helper, fp);

#define WRITE_2ARG(helper, format, arg1, arg2, fp)\
    snprintf(helper, ARR_BUFF_U8, format, arg1, arg2);\
    fputs(helper, fp);

#define WRITE_3ARG(helper, format, arg1, arg2, arg3, fp)\
    snprintf(helper, ARR_BUFF_U8, format, arg1, arg2, arg3);\
    fputs(helper, fp);

#define WRITE_4ARG(helper, format, arg1, arg2, arg3, arg4, fp)\
    snprintf(helper, ARR_BUFF_U8, format, arg1, arg2, arg3, arg4);\
    fputs(helper, fp);

#endif

////////~~~~~~~~END>  globalMacros.h
