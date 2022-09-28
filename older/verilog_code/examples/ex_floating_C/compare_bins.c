/*
    use to compare equivelant binary arrays
    false if not an exact match

    don't input different sizes
*/

#include "headz.h"


bool compare_bins(int* bin_A, int* bin_B, int length)
{
    if (bin_A == NULL ||
        bin_B == NULL ||
        length < 1     )
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }
    
    int idx = 0;

    for (idx = 0; idx < length; idx++)
    {
        if (bin_A[idx] != bin_B[idx])
        {
            return false;
        }
    }

    return true;

}


////////~~~~~~~~END>  compare_bins.c
