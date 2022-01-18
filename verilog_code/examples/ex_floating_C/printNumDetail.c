/*
    prints number, should be called after loading
    prints details
*/

#include "headz.h"

int printNumDetail(ieee745* stcNum)
{
    if (stcNum == NULL)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int idx = 0;

    printf("\n sign  exponent          float/significant         g  r  s\n");
    printf(" -----------------------------------------------------------\n");

    printf("  %1d    ", stcNum->bin_sign);

    for (idx = 0; idx < EXP_WID; idx ++)
    {
        printf("%1d", stcNum->bin_exp[idx]);
        if (idx == 3) { printf("_");}
    }

    printf("    ");
    for (idx = 0; idx < FLT_WID; idx++)
    {
        printf("%1d", stcNum->bin_flt[idx]);
        if (idx == 2 || idx == 6 || idx == 10 || idx == 14 || idx == 18)
        {
            printf("_");
        }
    }

    printf("   %1d  %1d  %1d\n\n", 
        stcNum->grs[0], stcNum->grs[1], stcNum->grs[2]);
    printf("sign:  %2.0f\n", stcNum->dec_sign);
    printf("exponent:  %4.0f\n", stcNum->dec_exp);
    printf("fraction: %1d + %.15f\n", stcNum->bin_hid, stcNum->dec_flt);
    printf("complete float:  %0.15f\n\n", stcNum->dec_num);

    return GOOD;
}


////////~~~~~~~~END>  printNumDetail.c
