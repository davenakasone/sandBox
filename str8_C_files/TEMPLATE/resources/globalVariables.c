/*
    make all changes to global variables here

    try to avoid using global variables
    
    "extern" to program as needed  
    {gv_} for standard variables
    {gs_} for structs
    ...keep some organization

    when this gets large, you should have an initialization sequence
*/

//#include <stdint.h> for embedded
#include <time.h>    // clock_t , time_t

#include "globalVariables.h"    // declared here

#include "globalMacros.h"  

////~~~~ other
clock_t gv_startProcessingTime;
time_t gv_startRunningTime;

////~~~~ structs


////~~~~ intergers


////~~~~ doubles/floats


////~~~~ chars
char gv_startDTS[U5_DTS];

////~~~~ strings
//char gv_helperString[ARR_BUF_U8]; // general purpose, statically allocated string, char *


////////~~~~~~~~END>  globalVariables.c
