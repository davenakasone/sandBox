/*
    struct initializer
*/

#include "headz.h"

int init_nums(ieee745* newNum)
{
    if (newNum == NULL)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  struct not allocated\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int idx;

    newNum->bin_sign = INIT_INT;
    newNum->dec_sign = INIT_DUB;

    for (idx = 0; idx < EXP_WID; idx++)
    {
        newNum->bin_exp[idx] = INIT_INT;
    }

    newNum->dec_exp = INIT_DUB;
    newNum->bin_hid = INIT_INT;

    for (idx = 0; idx < FLT_WID; idx++)
    {
        newNum->bin_flt[idx] = INIT_INT;
    }

    newNum->dec_flt = INIT_DUB;

    newNum->grs[0] = INIT_INT;
    newNum->grs[1] = INIT_INT;
    newNum->grs[2] = INIT_INT;

    newNum->dec_num = INIT_DUB;

    return GOOD;

}

////////~~~~~~~~END> init_nums.c
