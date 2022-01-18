/*
    drive from here
*/


#include "headz.h"


int main(int argc, char* argv[], char* envp[])
{
    //
    // begin input
    int A_sign = 1;
    int A_exp[EXP_WID] = {0, 1, 1, 1, 1, 1, 1, 0};
    int A_flt[FLT_WID] = {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int B_sign = 0;
    int B_exp[EXP_WID] = {1, 0, 0, 0, 0, 0, 1, 1};
    int B_flt[FLT_WID] = {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // end input

    g_status = loadNum(&g_numA, A_sign, A_exp, A_flt, true);
    g_status = copy_num(&g_numA, &g_numAog);
    
    g_status = loadNum(&g_numB, B_sign, B_exp, B_flt, true);
    g_status = copy_num(&g_numB, &g_numBog);
    
    g_status = add_nums(&g_numA, &g_numB, &g_result); 
    //
    //proof();
    
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  main.c
