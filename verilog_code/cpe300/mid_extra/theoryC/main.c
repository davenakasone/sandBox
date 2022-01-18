/*
    she is looking for k = log2(N)

    and, we are only doing N = 1 : 128

    round up or down? who the fuck knows    
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROUND_UP    // if you comment this out, you are rounding down
#define START 1
#define STOP 128
#define WIDTH 8

#define DUB_INIT -999.999
#define INT_INIT -999

void bin2dec(int* binIn, int decmal);
void dec2bin(int numIn, int* filler);


int main( int argc, char* argv[], char* envp[])
{
    int track = INT_INIT;
    int round_kk = INT_INIT;
    double kk = DUB_INIT;
    double NN = DUB_INIT;
    int bin_N[WIDTH];
    int bin_N_1[WIDTH];
    int bin_round_k[WIDTH];

    #ifdef ROUND_UP
        printf("\n         N         |        N - 1       |  k = log2(N)  -->  k Round Up\n");
    #else
        printf("\n         N        |  k = log2(N)   -->     k Round Down\n");
    #endif
    printf(" ----------------------------------------------------------------------------\n");

    for (int idx = START; idx <= STOP; idx++)
    {
        track = round_kk;

        NN = (double)idx;
        kk = log2(NN);

        #ifdef ROUND_UP
            round_kk = (int)ceil(kk);
        #else
            round_kk = (int)floor(kk);
        #endif

        if (track != round_kk && idx != START)
        {
            printf(" ----------------------------------------------------------------------------\n");
        }

        dec2bin(idx, bin_N);
        dec2bin(idx-1, bin_N_1);
        dec2bin(round_kk, bin_round_k);

        printf(" {%3d}  ", (int)NN);
        for (int jj = WIDTH-1; jj >= 0; jj--)
        {
            printf("%1d", bin_N[jj]);
            if (jj == 4) printf("_");
        }
        printf("  |  ");
        printf ("{%3d}  ", idx-1);
        for (int jj = WIDTH-1; jj >= 0; jj--)
        {
            printf("%1d", bin_N_1[jj]);
            if (jj == 4) printf("_");
        }
        printf("  |  ");

        printf("%0.5lf      -->  {%3d}  ",
            kk, round_kk);
        for (int jj = WIDTH-1; jj >= 0; jj--)
        {
            printf("%1d", bin_round_k[jj]);
            if (jj == 4) printf("_");
        }
        printf("\n");
    }

    printf("\n\n\t\t ~ ~ ~ PROMGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~ 


void bin2dec(int* binIn, int decmal)
{
    decmal = 0;

    for (int ii = 0; ii < WIDTH; ii++)
    {
        decmal = decmal + (int)pow(2, ii)*binIn[ii];
    }
}


////~~~~ 


void dec2bin(int numIn, int* filler)
{
    for (int ii = 0; ii < WIDTH; ii++)
    {
        filler[ii] = 0;
    }

    for (int ii = 0; numIn > 0; ii++)
    {
        filler[ii] = numIn % 2;
        numIn = numIn / 2; 
    }
}


////////~~~~~~~~END>  main.c
