/*
    give it:
        fill you want on right most bit
        binary array representation
        length of the array
    
    will return MSB....what came off the left

    be carefule with bigEnd or littleEnd
        only good for shifting the 23-bit floating part
        or [0 1 2] grs
    
    should have this format:

        [n, n-1, n-2, ... , 0]   MSB @ idx = 0, LSB @ idx = n
*/

#include "headz.h"


int shift_left(int right_fill, int* bin, int length)
{
    if (bin == NULL ||
        length < 1   )
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }
    
    int from_left = bin[0];
    int temp[TOT_WID];
    int idx = INIT_INT;

    temp[length-1] = right_fill;
    for (idx = length-2; idx >= 0; idx--)
    {
        temp[idx] = bin[idx + 1];
    }
    for (idx = 0; idx < length; idx++)
    {
        bin[idx] = temp[idx];
    }

    return from_left;
}


////////~~~~~~~~END>  shift_left.c
