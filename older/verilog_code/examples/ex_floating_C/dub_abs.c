/*
    cmath does't have a function to get the absolute value of a double
    floating arithmetic needs to know magnitudes to determine signs
*/

#include "headz.h"


double dub_abs(ieee745* given)
{
    if (given == NULL)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    if (given->bin_sign == 1)
    {
        return (-1 * given->dec_num);
    }
    else
    {
        return given->dec_num;
    }
}


////////~~~~~~~~END>  dub_abs.c
