/*
    make double, float, or int types
    specify starting and stoping range (inclusive)
    where stop > start
*/

#include <stdlib.h>    // RAND_MAX

#include "generators.h"    // declared here

#include "../../resources/globalMacros.h"


double randomDouble(double start, double stop)
{
    if (start >= stop) { return INIT_FLOAT; }

    double diff = stop - start;
    double randD = ((double)rand()) / ((double)RAND_MAX );
    randD = (diff * randD) + start;
    return randD;
}


float randomFloat(float start, float stop)
{
    if (start >= stop) { return INIT_FLOAT; }

    float diff = stop - start;
    float randF = ((float)rand()) / ((float)RAND_MAX );
    randF = (diff * randF) + start;
    return randF;
}


int randomInt(int start, int stop)
{
    if (start >= stop) { return INIT_INT; }

    int16_t diff = (stop - start) + 1;
    int16_t result = ( ( rand() % diff ) + start );
    return result;
}

////////~~~~~~~~END>  makeNumbers.c
