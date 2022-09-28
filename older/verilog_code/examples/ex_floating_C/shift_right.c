/*
    give it:
        fill you want on left most bit
        binary array representation
        length of the array
    
    will return LSB....what came off the right

    be carefule with bigEnd or littleEnd
        only good for shifting the 23-bit floating part
        or [0 1 2] grs
    
    should have this format:

        [n, n-1, n-2, ... , 0]   MSB @ idx = 0, LSB @ idx = n
*/

#include "headz.h"


int shift_right(int left_fill, int* bin, int length)
{
    if (bin == NULL ||
        length < 1   )
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }
    
    int from_right = bin[length-1];
    int temp[SHORT_WID];
    int idx = INIT_INT;

    temp[0] = left_fill;
    for (idx = 1; idx < length; idx++)
    {
        temp[idx] = bin[idx - 1];
    }

    for (idx = 0; idx < length; idx++)
    {
        bin[idx] = temp[idx];
    }

    return from_right;
}


////////~~~~~~~~END>  shift_right.c
