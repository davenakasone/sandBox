/*
    the full adder takes a bin array A and carry in
        specify the start/stop
        leave bin_b NULL or make it the same as array A

    derive sum bit of full adder
    derive carry-out bit of full adder
*/

#include "headz.h"

int full_adder(int* bin_A, int* bin_B, int* bin_C, int c_in, int start, int stop)
{
    if (start == stop)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int temp_cout = INIT_INT;
    int temp_cin = c_in;
    int temp_sum[TOT_WID];
    int idx = INIT_INT;
    bool reverse_loop = (start > stop) ? true : false;

    if (bin_B == NULL && 
        bin_C == NULL  )    // increment call, changing bin_A
    {
        if (reverse_loop == false)
        {
            for (idx = start; idx <= stop; idx++)
            {
                temp_sum[idx] = fa_sum(bin_A[idx], 0, temp_cin);
                temp_cout = fa_cout(bin_A[idx], 0, temp_cin);
                temp_cin = temp_cout;
            }
            for (idx = start; idx <= stop; idx++)
            {
                bin_A[idx] = temp_sum[idx];
            }
        }
        else
        {
            for (idx = start; idx >= stop; idx--)
            {
                temp_sum[idx] = fa_sum(bin_A[idx], 0, temp_cin);
                temp_cout = fa_cout(bin_A[idx], 0, temp_cin);
                temp_cin = temp_cout;
            }
            for (idx = start; idx >= stop; idx--)
            {
                bin_A[idx] = temp_sum[idx];
            }
        }
    }
    else if (bin_A != NULL && 
             bin_B != NULL &&
             bin_C != NULL  )    // add 2 arrays to bin_C, provide carry-out
    {
        if (reverse_loop == false)
        {
            for (idx = start; idx <= stop; idx++)
            {
                bin_C[idx] = fa_sum(bin_A[idx], bin_B[idx], temp_cin);
                temp_cout = fa_cout(bin_A[idx], bin_B[idx], temp_cin);
                temp_cin = temp_cout;
            }
        }
        else
        {
            for (idx = start; idx >= stop; idx--)
            {
                bin_C[idx] = fa_sum(bin_A[idx], bin_B[idx], temp_cin);
                temp_cout = fa_cout(bin_A[idx], bin_B[idx], temp_cin);
                temp_cin = temp_cout;
            }
        }
    }
    else
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    return temp_cout;
}


////~~~~


int fa_sum(int a_bit, int b_bit, int in_c)
{
    return ( (a_bit ^ b_bit) ^ in_c);
}


////~~~~


int fa_cout(int a_bit, int b_bit, int in_c)
{
    return ( (a_bit & b_bit) || (a_bit & in_c) || (b_bit & in_c) );
}


////////~~~~~~~~END>  full_adder.c
