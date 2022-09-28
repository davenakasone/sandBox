/*
    deep copy a struct... usually to save an original value
*/

#include "headz.h"


int copy_num(ieee745* in_data, ieee745* copy_to)
{
    if (in_data == NULL ||
        copy_to == NULL  )
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int idx;

    copy_to->bin_sign = in_data->bin_sign;
    copy_to->dec_sign = in_data->dec_sign;
    copy_to->dec_exp = in_data->dec_exp;
    copy_to->bin_hid = in_data->bin_hid;
    copy_to->dec_flt = in_data->dec_flt;
    copy_to->grs[0] = in_data->grs[0];
    copy_to->grs[1] = in_data->grs[1];
    copy_to->grs[2] = in_data->grs[2];
    copy_to->dec_num = in_data->dec_num;
    
    for (idx = 0; idx < EXP_WID; idx++)
    {
        copy_to->bin_exp[idx] = in_data->bin_exp[idx];
    }

    for (idx = 0; idx < FLT_WID; idx++)
    {
        copy_to->bin_flt[idx] = in_data->bin_flt[idx];
    }

    return GOOD;
}


////////~~~~~~~~END>  copy_num.c
