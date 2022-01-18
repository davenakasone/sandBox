/*
    call to load struct inst w/ data
    try to use the global structs
*/

#include "headz.h"


int loadNum(ieee745* inst, int sign, int* exp, int* flt, bool initGRS)
{
    if (inst == NULL ||
        exp == NULL  ||
        flt == NULL   )
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }
    
    int idx = 0;
    double track = 0;

    inst->bin_sign = sign;
    inst->dec_sign = (sign == 0) ? 1 : -1;

    for (idx = 0; idx < EXP_WID; idx++)
    {
        track = track + (pow(2, (double)(EXP_WID - idx - 1)) * exp[idx]);
        inst->bin_exp[idx] = exp[idx];
    }
    inst->dec_exp = track - EXP_MAP;
   
    track = 0;
    for (idx = 0; idx < FLT_WID; idx++)
    {
        track = track + ( pow(2, (double)((-1)*(idx+1))) * flt[idx]);
        inst->bin_flt[idx] = flt[idx];
    }
    inst->dec_flt = track;

    if (initGRS == true)
    {
        inst->bin_hid = 1;
        
        inst->grs[0] = 0;
        inst->grs[1] = 0;
        inst->grs[2] = 0;
    }
    
    inst->dec_num = inst->dec_sign * 
                    pow(2, inst->dec_exp) * 
                    ((double)inst->bin_hid + inst->dec_flt);

    return GOOD;
}

//////////~~~~~~~~END>  loadNum.c
