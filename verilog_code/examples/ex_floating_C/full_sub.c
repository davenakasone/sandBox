/*
    the full subtractor
    X - Y - borrow_in ==>  diff, borrow_out
*/

#include "headz.h"



int full_sub(int* inX, int* inY, int* outA, int b_in, int start, int stop)
{
    if (start == stop)
    {
        #ifdef DEBUG_PRINT
            printf("\n\t%s()  ,  bad inputs\n", __func__);
        #endif
        return NOT_GOOD;
    }

    int temp_bout = INIT_INT;
    int temp_bin = b_in;
    int temp_diff[TOT_WID];
    int idx = INIT_INT;
    bool reverse_loop = (start > stop) ? true : false;

    if (inY == NULL && 
        outA == NULL  )    // decrement call, changing inX
    {
        if (reverse_loop == false)
        {
            for (idx = start; idx <= stop; idx++)
            {
                temp_diff[idx] = fs_diff(inX[idx], 0, temp_bin);
                temp_bout = fs_bout(inX[idx], 0, temp_bin);
                temp_bin = temp_bout;
            }
            for (idx = start; idx <= stop; idx++)
            {
                inX[idx] = temp_diff[idx];
            }
        }
        else
        {
            for (idx = start; idx >= stop; idx--)
            {
                temp_diff[idx] = fs_diff(inX[idx], 0, temp_bin);
                temp_bout = fs_bout(inX[idx], 0, temp_bin);
                temp_bin = temp_bout;
            }
            for (idx = start; idx >= stop; idx--)
            {
                inX[idx] = temp_diff[idx];
            }
        }
    }
    else if (inX != NULL && 
             inY != NULL &&
             outA != NULL  )    // sub 2 arrays to outA, provides borrow_out
    {
        if (reverse_loop == false)
        {
            for (idx = start; idx <= stop; idx++)
            {
                outA[idx] = fs_diff(inX[idx], inY[idx], temp_bin);
                temp_bout = fs_bout(inX[idx], inY[idx], temp_bin);
                temp_bin = temp_bout;
            }
        }
        else
        {
            for (idx = start; idx >= stop; idx--)
            {
                outA[idx] = fs_diff(inX[idx], inY[idx], temp_bin);
                temp_bout = fs_bout(inX[idx], inY[idx], temp_bin);
                temp_bin = temp_bout;
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

    return temp_bout;
}


////~~~~


int fs_diff(int x_bit, int y_bit, int in_bor)
{
    return ( (x_bit ^ y_bit) ^ in_bor);
}


////~~~~


int fs_bout(int x_bit, int y_bit, int in_bor)
{
    return ( ((!x_bit) & in_bor) | ((!x_bit) & y_bit) | (y_bit & in_bor));
}


////////~~~~~~~~END full_sub.c
