/*
    shift the number format left
*/

#include "headz.h"


int shift_left_EHFgrs(ieee745* numIn)
{
    if (numIn == NULL)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int stick_keep = INIT_INT;
    int from_left = INIT_INT;
    int temp_bout = 0;

    // shift float, taking from grs, adjust hidden if needed
    from_left = shift_left(numIn->grs[0], numIn->bin_flt, FLT_WID);
    numIn->bin_hid = (from_left == 1) ? 1 : 0;

    // shift GRS, enforce active sticky
    stick_keep = numIn->grs[2];
    from_left = shift_left(0, numIn->grs, GRS_WID);
    if (stick_keep == 1) 
    {
        numIn->grs[2] = 1;
    }

    // decrement exponent
    temp_bout = full_sub(numIn->bin_exp, NULL, NULL, 1, EXP_WID - 1, 0);
    if (temp_bout != 0)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  overflow...\n", __func__);
        #endif
    }

    return GOOD;
}


////////~~~~~~~~END>  shift_left_EHFgrs.c