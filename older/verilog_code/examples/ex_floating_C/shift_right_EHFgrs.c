/*
    increments exponent
    moves hidden bit
    LSB of float to GRS
    ...sticky maintained
*/

#include "headz.h"


int shift_right_EHFgrs(ieee745* numIn)
{
    if (numIn == NULL)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int from_right = INIT_INT;
    int temp_cout = 0;

    // shift float, change hidden if needed, pass to grs
    from_right = shift_right(numIn->bin_hid, numIn->bin_flt, FLT_WID);
    numIn->bin_hid = 0; 

    // shift GRS, enforce active sticky
    from_right = shift_right(from_right, numIn->grs, GRS_WID);
    if (from_right == 1) 
    {
        numIn->grs[2] = 1;
    }

    // increment exponent
    temp_cout = full_adder(numIn->bin_exp, NULL, NULL, 1, EXP_WID - 1, 0);
    if (temp_cout != 0)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  overflow...\n", __func__);
        #endif
    }

    return GOOD;
}

////////~~~~~~~~END>  shift_right_EHFgrs.c
