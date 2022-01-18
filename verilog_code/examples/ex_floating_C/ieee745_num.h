/*
    stores format of IEEE 745
    32 bit floating point number
        adjust for long or short in "headz.h"
*/

#ifndef H_ieee745
#define H_ieee745


#include "resourcez.h"


typedef struct ieee745
{
    int bin_sign;            // sign indicator {0,1} , 0 pos, 1 neg
    double dec_sign;         // -1 or 1

    int bin_exp[EXP_WID];    // exponent place, multiple of 2^exp
    double dec_exp;          // decimal of exponent

    int bin_hid;             // the hidden bit

    int bin_flt[FLT_WID];    // binary representation of floating number
    double dec_flt;          // decimal representation of floating number

    int grs[GRS_WID];        // gaurd, reserve, sticky

    double dec_num;          // complete representation of the number

} ieee745;


#endif


////////~~~~~~~~END>  ieee745_num.c
