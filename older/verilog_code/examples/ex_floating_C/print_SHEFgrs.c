/*
    prints the bins, even the hidden
    turn header on/off
    give a custom message or NULL
*/

#include "headz.h"

int print_SHEFgrs(ieee745* stcNum, bool head, char* message)
{
    if (stcNum == NULL)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int idx = 0;

    if (head == true)
    {
        printf("\n sign  exponent             H.float                  g  r  s\n");
        printf(" -----------------------------------------------------------\n");
    }
    
    printf("  %1d    ", stcNum->bin_sign);

    for (idx = 0; idx < EXP_WID; idx ++)
    {
        printf("%1d", stcNum->bin_exp[idx]);
        if (idx == 3) { printf("_");}
    }

    printf("    %1d.", stcNum->bin_hid);
    for (idx = 0; idx < FLT_WID; idx++)
    {
        printf("%1d", stcNum->bin_flt[idx]);
        if (idx == 2 || idx == 6 || idx == 10 || idx == 14 || idx == 18)
        {
            printf("_");
        }
    }
    
    if (message == NULL)
    {
        printf("   %1d  %1d  %1d\n", 
            stcNum->grs[0], stcNum->grs[1], stcNum->grs[2]);
    }
    else
    {
        printf("   %1d  %1d  %1d    %s\n", 
            stcNum->grs[0], stcNum->grs[1], stcNum->grs[2], message);
    }
    
    return GOOD;
}


////////~~~~~~~~END>  print_SHEFgrs.c
