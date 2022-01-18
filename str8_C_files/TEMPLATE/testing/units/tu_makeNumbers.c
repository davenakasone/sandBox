/*
    tests "makeNumbers.c" series
*/

#include <stdlib.h>    // NULL
#include <stdio.h>     // printf()

#include "../testing.h"    // declared here

#include "../../resources/globalMacros.h"

#include "../generators/generators.h"


void tu_makeNumbers()
{
    // adjust
    double ll_double = -33.333333;
    double ul_double = ll_double * -1;
    float ll_float = -33.333;
    float ul_float = ll_float * -1;
    int ll_int = -33;
    int ul_int = ll_int * -1;
    int rep_ll = 4;
    int rep_ul = 9;

    // do not adjust
    int reps = INIT_INT;


    printf("\n%s()  ,  START\n", __func__);


    printf("\n\t%s()  ,  1  ,  get random int:\n", __func__);
    reps = randomInt(rep_ll, rep_ul);
    printf("\n\t%d reps  ,  %d  to  %d\n\n",
        reps, ll_int, ul_int);
    for (int i = 0; i < reps; i++)
    {
        printf("\t%d\n", randomInt(ll_int, ul_int));
    }
    waitEnterClear();


    reps = randomInt(rep_ll, rep_ul);
    ll_int = 0;
    ul_int = 5;
    printf("\n\t%s()  ,  2  ,  positive random int, [0,5]  ,  %d reps:\n\n",
        __func__, reps);
    for (int i = 0; i < reps; i++)
    {
        printf("\t%d\n", randomInt(ll_int, ul_int));
    }
    waitEnterClear();


    printf("\n\t%s()  ,  3  ,  get random float:\n", __func__);
    reps = randomInt(rep_ll, rep_ul);
    printf("\n\t%d reps  ,  %f  to  %f\n\n",
        reps, ll_float, ul_float);
    for (int i = 0; i < reps; i++)
    {
        printf("\t%f\n", randomFloat(ll_float, ul_float));
    }
    waitEnterClear();


    reps = randomInt(rep_ll, rep_ul);
    ll_float = 0.01;
    ul_float = 5.01;
    printf("\n\t%s()  ,  4  ,  positive random float, [0.01,5.01]  ,  %d reps:\n\n",
        __func__, reps);
    for (int i = 0; i < reps; i++)
    {
        printf("\t%f\n", randomFloat(ll_float, ul_float));
    }
    waitEnterClear();


    printf("\n\t%s()  ,  5  ,  get random double:\n", __func__);
    reps = randomInt(rep_ll, rep_ul);
    printf("\n\t%d reps  ,  %lf  to  %lf\n\n",
        reps, ll_double, ul_double);
    for (int i = 0; i < reps; i++)
    {
        printf("\t%f\n", randomDouble(ll_double, ul_double));
    }
    waitEnterClear();


    reps = randomInt(rep_ll, rep_ul);
    ll_double = 0.01;
    ul_double = 5.01;
    printf("\n\t%s()  ,  6  ,  positive random double, [0.01,5.01]  ,  %d reps:\n\n",
        __func__, reps);
    for (int i = 0; i < reps; i++)
    {
        printf("\t%lf\n", randomDouble(ll_double, ul_double));
    }
    

    printf("\n%s()  ,  STOP\n", __func__);
    waitEnterClear();
}

////////~~~~~~~~END>  tu_makeNumbers.c
