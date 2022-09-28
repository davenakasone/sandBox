/*
    macros, libs, no user defined
    if you have a single, make sure EXP_WID = 8, FLT_WID = 23
    if your have a double, make sure EXP_WID = 11, FLT_WID = 52


    not really needed to include
        ...take headz.h and it will take all
*/

#ifndef H_resourcez
#define H_resourcez


#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headz.h"

#define GET_NAME(variable) #variable

#define EXP_WID 8     // single 8, double 11
#define FLT_WID 5     // single 23, double 52 ...or whatever given
#define GRS_WID 3     // should always be 3

#define TOT_WID 32       // single 32, double 64...   EXP + FLT + 1 for sign
#define EXP_MAP 127      // single 127, double 1023
#define CHAR_BUFF 256    // arbitrary helper string

#define GOOD 69             // function success
#define NOT_GOOD -69        // function failure
#define INIT_INT 333        // initialize integer types
#define INIT_DUB 333.333    // initialize double types
#define DEBUG_PRINT -999    // general debugging
 
#define D_add -888     // print and debug "add_nums.c"
#define D_mult -777    // print and debug "mult_nums.c"


#endif


////////~~~~~~~~END>  resourcez.h
