/*
    algorithim development
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define START 1
#define STOP 128
#define RFZ 4
#define BITZ 8

void dec2bin(int numIn, int* filler);
void bin2dec(int* binIn, int decmal);


int main( int argc, char* argv[], char* envp[])
{
    int rf[RFZ][BITZ];
    int input[BITZ];
    int input_dec;
    int output;
    int output_dec;

    for (int idx = START; idx <= STOP; idx++)
    {
        input_dec = idx;
        dec2bin(input_dec, input);

        

        for (int jj = BITZ-1; jj >= 0; jj--)
        {
            printf("%1d", input[jj]);
            if (jj == 4) printf("_");
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}


////~~~~


void dec2bin(int numIn, int* filler)
{
    for (int ii = 0; ii < BITZ; ii++)
    {
        filler[ii] = 0;
    }

    for (int ii = 0; numIn > 0; ii++)
    {
        filler[ii] = numIn % 2;
        numIn = numIn / 2; 
    }
}


////~~~~


void bin2dec(int* binIn, int decmal)
{
    decmal = 0;

    for (int ii = 0; ii < BITZ; ii++)
    {
        decmal = decmal + (int)pow(2, ii)*binIn[ii];
    }
}

////////~~~~~~~END> alg.c
