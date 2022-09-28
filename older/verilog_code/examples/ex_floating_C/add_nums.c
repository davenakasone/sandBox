/*
    applies the algorithim to add numbers
    take return to global "g_result"
*/

#include "headz.h"


int add_nums(ieee745* numA, ieee745* numB, ieee745* result)
{
    if (numA == NULL ||
        numB == NULL  )
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    g_status = init_nums(result);

    #ifdef D_add
        printf("\n\tadding numbers:\n");
        print_SHEFgrs(numA, true, GET_NAME(numA));
        print_SHEFgrs(numB, false, GET_NAME(numB));
    #endif

    char helper[CHAR_BUFF];
    int idx = INIT_INT;
    int exp_diff = INIT_INT;
    bool A_exp_larger = (numA->dec_exp >= numB->dec_exp) ? true : false;
    bool A_greater_equal_B = (dub_abs(numA) >= dub_abs(numB)) ? true : false;
    
    // handle the sign of the result, based on magnitude
    if (A_greater_equal_B == true)
    {
        result->bin_sign = numA->bin_sign;
    }
    else
    {
        result->bin_sign = numB->bin_sign;
    }

    // normalize the lesser exponent to larger
    if (A_exp_larger == true)
    {
        exp_diff = numA->dec_exp - numB->dec_exp;
        #ifdef D_add
            printf("\n\t%s has smaller exponent, alinging  %d shifts right\n",
                GET_NAME(numB), exp_diff);
            print_SHEFgrs(numB, true, GET_NAME(numB));
        #endif
        for (idx = 0; idx < exp_diff; idx++)
        {
            shift_right_EHFgrs(numB);
            #ifdef D_add
                snprintf(helper, CHAR_BUFF, "%s  ,  %d  shift", 
                    GET_NAME(numB), idx+1);
                print_SHEFgrs(numB, false, helper);
            #endif
        }
    }
    else
    {
        exp_diff = numB->dec_exp - numA->dec_exp;
        #ifdef D_add
            printf("\n\t%s has smaller exponent, alinging  %d shifts right\n",
                GET_NAME(numA), exp_diff);
            print_SHEFgrs(numA, true, GET_NAME(numA));
        #endif
        for (idx = 0; idx < exp_diff; idx++)
        {
            shift_right_EHFgrs(numA);
            #ifdef D_add
                snprintf(helper, CHAR_BUFF, "%s  ,  %d  shift", 
                    GET_NAME(numA), idx+1);
                print_SHEFgrs(numA, false, helper);
            #endif
        }
    }

    #ifdef D_add
        if (compare_bins(numA->bin_exp, numB->bin_exp, EXP_WID) == false)
        {
            printf("\n\tthere was a problem shifting\n");
        }
        printf("\n\tnow the numbers are ready to add(sub):\n");
        print_SHEFgrs(numA, true, GET_NAME(numA));
        print_SHEFgrs(numB, false, GET_NAME(numB));
        printf(" -----------------------------------------------------------\n");
    #endif

    // assign preliminary exponent to result, can assign from either
    for (idx = 0; idx < EXP_WID; idx++)
    {
        result->bin_exp[idx] = numA->bin_exp[idx]; 
    }

    if (numA->bin_sign == numB->bin_sign) // equal signs A+B, cases{00 , 11}
    {
        int temp_cout = 0;
        int temp_cin = 0;
        temp_cout = full_adder(numA->grs, numB->grs, result->grs, 0, GRS_WID-1, 0);
        temp_cin = temp_cout;
        temp_cout = full_adder(numA->bin_flt, numB->bin_flt, result->bin_flt, temp_cin, FLT_WID-1, 0);
        temp_cin = temp_cout;
        result->bin_hid = fa_sum(numA->bin_hid, numB->bin_hid, temp_cin);
        temp_cout = fa_cout(numA->bin_hid, numB->bin_hid, temp_cin);

        g_status = loadNum(result, result->bin_sign, result->bin_exp, result->bin_flt, false);

        if (temp_cout == 1)
        {
            shift_right_EHFgrs(result);
            result->bin_hid = temp_cout;
            g_status = loadNum(result, result->bin_sign, result->bin_exp, result->bin_flt, false);
            #ifdef D_add
                snprintf(helper, CHAR_BUFF, "%s  shifts !!! c_out", 
                        GET_NAME(numA));
                print_SHEFgrs(result, false, helper);
            #endif
        }
    }
    else if (numA->bin_sign == 0 && numB->bin_sign == 1)  // A-B  case{01}
    {
        int temp_bout = 0;
        int temp_bin = 0;
        temp_bout = full_sub(numA->grs, numB->grs, result->grs, 0, GRS_WID-1, 0);
        temp_bin = temp_bout;
        temp_bout = full_sub(numA->bin_flt, numB->bin_flt, result->bin_flt, temp_bin, FLT_WID-1, 0);
        temp_bin = temp_bout;
        result->bin_hid = fs_diff(numA->bin_hid, numB->bin_hid, temp_bin);
        temp_bout = fs_bout(numA->bin_hid, numB->bin_hid, temp_bin);

        g_status = loadNum(result, result->bin_sign, result->bin_exp, result->bin_flt, false);
        #ifdef D_add
            snprintf(helper, CHAR_BUFF, "%s,  ignore b_out", 
                GET_NAME(result));
            print_SHEFgrs(result, false, helper);
        #endif
    }
    else if (numA->bin_sign == 1 && numB->bin_sign == 0)  // B-A  case{10}
    {
        int temp_bout = 0;
        int temp_bin = 0;
        temp_bout = full_sub(numB->grs, numA->grs, result->grs, 0, GRS_WID-1, 0);
        temp_bin = temp_bout;
        temp_bout = full_sub(numB->bin_flt, numA->bin_flt, result->bin_flt, temp_bin, FLT_WID-1, 0);
        temp_bin = temp_bout;
        result->bin_hid = fs_diff(numB->bin_hid, numA->bin_hid, temp_bin);
        temp_bout = fs_bout(numB->bin_hid, numA->bin_hid, temp_bin);

        g_status = loadNum(result, result->bin_sign, result->bin_exp, result->bin_flt, false);
        #ifdef D_add
            //print_SHEFgrs(result, false, GET_NAME(result));
        #endif

        if (temp_bout == 1)
        {
            //shift_left_EHFgrs(result);
            //result->bin_hid = temp_bout;
            result->bin_hid = (result->bin_sign == 1) ? 1 : 0;
            g_status = loadNum(result, result->bin_sign, result->bin_exp, result->bin_flt, false);
            print_SHEFgrs(result, false, helper);
            #ifdef D_add
                snprintf(helper, CHAR_BUFF, "%s  shifts !!! b_out", 
                        GET_NAME(numA));
                //print_SHEFgrs(result, false, helper);
            #endif
        }
    }
    else
    {
        #ifdef D_add
            printf("\n\t%s()  ,  logic error\n", __func__);
        #endif
    }
    
    #ifdef D_add
        printf("\n compare:\n");
        printf("\t%15.15f    +\n", g_numAog.dec_num);
        printf("\t%15.15f\n", g_numBog.dec_num);
        printf("  -------------------------------------------------------\n");
        printf("\t%15.15f    theoretical\n", g_numAog.dec_num + g_numBog.dec_num);
        printf("\t%15.15f    result\n", result->dec_num);
        printNumDetail(&g_numAog);
        printNumDetail(&g_numBog);
        printNumDetail(result);
    #endif

    return GOOD;
}


////////~~~~~~~~END>  add_nums.c
