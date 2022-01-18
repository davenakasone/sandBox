/*
    of course this would be on here
    all the discs are stacked smallest on top
    you can't put a bigger diameter on a smaller one
    3 towers, only one move at a time   

    could go binary, but will go recursive

    1 disk : A -> C    complete
    2 disks: A -> B, A -> C, B -> C
    3 disks: ...once you can do 3, you can use recursion to do the rest

    pints in order traversal, A to C w/ help of B
    2^n - 1 moves, 2^n+1 - 1 calls   exponential time....

    disc number irrelevent
    __
   ____
  ______
    |          |      |
    A          B      C


    The rythm of binary counting is what makes it iterative
    2^n + 2^n-1 + ... + 2^1 + 2^0     lowers reset a lot      bits in base 2 represent different powers of 2
    do something, rollover, do again...
    count from 00000...
          when you are flipping LSB, move top disc one peg to right   if it was already on right most peg, loop back


     disc number important     determines your binary numbers  000 starts here (3 discs) LSB on 0, LSB + 1 , MSB = 2
    __ 0
   ____ 1
  ______ 2
    |          |      |
    A          B      C

    everytime you get the biggest disc, you make a smaller problem   binary counting and this problem are self-similar
    even relates to svinsky's triangle
    you effectivley reverse engineer the recurrsive algorithm...and save a lot of time/space

    https://www.youtube.com/watch?v=2SUvWfNJSsM
    https://www.youtube.com/watch?v=bdMfjfT0lKk&t=5s     // can't be on top, and can't be adjacent (more complex, use base 3)
                                                                3^n - 1 moves...
                                                                can't hit same configuration twice, and goes through all configs
    each configuration is a vertex, they are connected if you can make a legal move to it
    make the graph and you will see the triangle, then you can use all your DFS, BFS, djikstra, ect
    a hilbert curve is the path, but instead of exp limit it is a fractral
*/

#include <cmath>
#include <iostream>

const int POLES = 3; // game only allows for 3 poles .... use other than binary if these change
int REP = 0; // calls to funciton
int MOV = 0; // actual moves
int DISCS = 4; // discs in your tower       keep in single digits or there will be problems
int *BIN;    // your array to hold the binary....MSB @ index 0
int **MTX; // 2D array showing current arrangement of discs and poles
char *PLS; // array to hold poles A, B, and C

void recur_toh(int n, char A, char B, char C); // the traditional way    way less of an abortion

void bin_toh(int discs); // the binary way ...a lot slopier than recursive way
void bin_initialize(int discs, int bin[]);   // [1] fill up any array to binary 00000 based on size, LSB right most (highest index)
void bin_print_bins(int discs, int bin[]);       // [2] print any array, MSB -> LSB
void bin_dec_to_bin(int discs, int bin[], int dec);   // [3] convert a decimal number and put it in the array   bin returned by ref
void bin_copy(int from[], int to[]); // [4] make a copy 'from' array onto -> to[] array
void bin_set_matrix();
void bin_print_matrix();
void bin_print_poles();
bool bin_mtx_allowed(int col, int disc); // give it the column you want to insert at and the disc...true for legal
int bin_mtx_top(int col); // give it the col you want to insert at, it will give you the index to insert disc at
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    
    std::cout << "\n should take 2 ^ " << DISCS << " - 1  = " << std::pow(2,DISCS) - 1 << " reps ...\n";
    recur_toh(DISCS, 'A', 'B', 'C'); // A = 1, B = 2, C = 3    standard source -> destination
    std::cout << "recur_toh(" << DISCS << ") called  " << REP << " times, moves recorded: " << MOV << std::endl;
    REP = 0;
    MOV = 0;
    

    std::cout << "\n                                               ITERATE w/ BINARY:\n";
    BIN = new int[DISCS]; // set globals
    MTX = new int* [DISCS]; 
    for (int i = 0; i < DISCS; i++)
    {
        MTX[i] = new int[POLES];
    }
    PLS = new char[POLES]; // globals set

    bin_toh(DISCS); // start the abortion
    // no use tracking reps...it is the binary number provided 2^n - 1

    for (int i = 0; i < DISCS; i++) // start clean up
    {
        delete [] MTX[i];
    }
    delete [] MTX;
    delete [] PLS;
    delete [] BIN; 
    BIN = nullptr; 
    REP = 0;
    MOV = 0; // clean up complete

    std::cout << "\n\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0; 
}

//--------------------------------------------------------------------------------------------------------------------------
void recur_toh(int n, char A, char B, char C)     // this is so short and clean
{   
    REP++;
    if (n > 0)
    {
        recur_toh(n-1, A, C, B); // source and destination change
        std::cout << "  > from pole_" << A << " , to pole_" << C << std::endl;
        recur_toh(n-1, B, A, C); // source and destination change
        MOV++;
    }
}




//--------------------------------------------------------------------------------------------------------------------------
void bin_toh(int discs)
{
    bin_set_matrix();
    bin_initialize(DISCS, BIN); // initialze
    bin_print_matrix();
    bin_print_poles();
    bin_print_bins(DISCS, BIN); // print intital
    
    int* binP; // previous state of towers
    binP = new int[DISCS];
    bin_copy(BIN, binP); // let binP lag behind BIN one move
    bool *diff; // true if change, false if not
    diff = new bool[DISCS];
    int tempIrow = -9; // msb to move
    int tempIcol = -9; // 
    int maxD = -9; // disc to move
    int top = -9; // top of pole (index to insert)

    std::cout << "----------------------------------------\n"; //TEST

    for (int i = 1; i < std::pow(2,DISCS); i++) // should be able to complete in 2^n - 1 steps
    {
        bin_dec_to_bin(DISCS, BIN, i); // increment binary sequence to array
        for (int j = 0; j < DISCS; j++)
        {
            if (binP[j] == 0 && BIN[j] == 1)
            {
                diff[j] = true; // record true if index has a change (0 -> 1 flip is moving criteria)
            }
            else
            {
                diff[j] = false; // moving criteria not met
            }
        }

        for (int k = 0; k < DISCS; k++)
        {
            if (diff[k] == true)
            {
                maxD = DISCS-1-k;// have to reverse to match BIN[]    largest index of disk
                goto foundMax; // jump
            }
        }
        foundMax: // jump complete, breaks when first bit matching flipping criteria found, MSB -> LSB

        for (int f = 0; f < DISCS; f++)
        {
            for (int g = 0; g < POLES; g++)
            {
                if (MTX[f][g] == maxD)
                {
                    tempIrow = f; // located disk row
                    tempIcol = g; // located disk col
                }
            }
        }
        if (maxD == 0)
        {
            if (tempIcol == 0)
            {
                MTX[tempIrow][tempIcol] = -1; // moving
                top = bin_mtx_top(1); // going to col 1
                MTX[top][1] = maxD;
            }
            if (tempIcol == 1)
            {
                MTX[tempIrow][tempIcol] = -1; // moving
                top = bin_mtx_top(2); // going to col 2
                MTX[top][2] = maxD;
            }
            if (tempIcol == 2)
            {
                MTX[tempIrow][tempIcol] = -1; // moving
                top = bin_mtx_top(0); // going to col 0
                MTX[top][0] = maxD;
            }
        }
        else
        {
            if (tempIcol == 0) // can't go back to col 0, have to move
            {
                if (bin_mtx_allowed(1, maxD)) // disc allowed in col 1
                {
                    MTX[tempIrow][tempIcol] = -1;
                    top = bin_mtx_top(1);
                    MTX[top][1] = maxD;
                }
                else // assume it must be allowed on col 2
                {
                    MTX[tempIrow][tempIcol] = -1;
                    top = bin_mtx_top(2);
                    MTX[top][2] = maxD;
                }
            }
            if (tempIcol == 1) // can't go back to col 1, have to move
            {
                if (bin_mtx_allowed(2, maxD)) // disc allowed in col 2
                {
                    MTX[tempIrow][tempIcol] = -1;
                    top = bin_mtx_top(2);
                    MTX[top][2] = maxD;
                }
                else // assume it must be allowed on col 0
                {
                    MTX[tempIrow][tempIcol] = -1;
                    top = bin_mtx_top(0);
                    MTX[top][0] = maxD;
                }
            }
            if (tempIcol == 2) // can't go back to col 2, have to move
            {
                if (bin_mtx_allowed(0, maxD)) // disc allowed in col 0
                {
                    MTX[tempIrow][tempIcol] = -1;
                    top = bin_mtx_top(0);
                    MTX[top][0] = maxD;
                }
                else // assume it must be allowed on col 1
                {
                    MTX[tempIrow][tempIcol] = -1;
                    top = bin_mtx_top(1);
                    MTX[top][1] = maxD;
                }
            }
        }
        bin_print_matrix();
        bin_print_poles();
        bin_print_bins(DISCS, BIN); // print binary seqence that caused change
        bin_copy(BIN, binP); // copy old values to increment
        std::cout << "----------------------------------------\n\n"; //TEST
    }
    
}
//--------------------------------------------------------------------------------------------------------------------------
void bin_initialize(int discs, int bin[])      // [1]
{
    for (int i = 0; i < discs; i++)
    {
        bin[i] = 0;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void bin_print_bins(int discs, int bin[]) // [2]
{
    std::cout << "     {  ";
    for (int i = 0; i < discs; i++)
    {
        std::cout << bin[i] << "  ";
    }
    std::cout << "}\n";
}

//--------------------------------------------------------------------------------------------------------------------------
void bin_dec_to_bin(int discs, int bin[], int dec) // [3]
{
    if (std::pow(2,discs) - 1 < dec) // good to check
    {
        std::cout << "\n   there is a problem\n";
        return;
    }
    for (int i = discs - 1; dec > 0; i--) // took LSB -> MSB ...need to reverse
    {
        if (dec % 2 == 0)
        {
            bin[i] = 0;
        }
        else
        {
            bin[i] = 1;
        }
        dec = dec/2;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void bin_copy(int from[], int to[])   // [4]
{
    for (int i = 0; i < DISCS; i++)
    {
        to[i] = from[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void bin_print_poles()
{
    for (int i = 0; i < POLES; i++)
    {
        PLS[i] = i + 65; // ascii
        std::cout << PLS[i] << "  ";
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void bin_set_matrix()
{
    for(int i = 0; i < DISCS; i++)
    {
        for (int j = 0; j < POLES; j++)
        {
            if (j == 0)
            {
                MTX[i][j] = i;
            }
            else
            {
                MTX[i][j] = -1;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void bin_print_matrix()
{
    std::cout << "\n        current tower:\n";
    for (int i = 0; i < DISCS; i++)
    {
        for (int j = 0; j < POLES; j++)
        {
            if (MTX[i][j] < 0)
            {
                std::cout << "   ";
            }
            else 
            {
                std::cout << MTX[i][j] << "  ";
            }
        }
        std::cout << std::endl;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
bool bin_mtx_allowed(int col, int disc)// give it the column you want to insert at and the disc...true for legal
{
    int top;
    int **mtxC; // copy of matrix
    mtxC = new int*[DISCS];
    for (int i = 0; i < DISCS; i++)
    {
        mtxC[i] = new int[POLES];
    }
    for (int i = 0; i < DISCS; i++)
    {
        for (int j = 0; j < POLES; j++)
        {
            mtxC[i][j] = MTX[i][j]; // MTX copied to mtxC
        }
    }
    for (int i = DISCS-1; i >= 0; i--) // from bottom, see if there is room
    {
        if (mtxC[i][col] < 0) // checking at desired col  , no need to check full pole, that is not possible
        {
            top = i;
            goto foundTop;
        }
    }
    foundTop:
    mtxC[top][col] = disc; // update ... no need to adjust, only looking at col
    for(int i = 0; i < DISCS; i++)
    {
        if (i > 0)
        {
            if(mtxC[i][col] < mtxC[i-1][col])
            {
                return false;
            }
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------------------------------
int bin_mtx_top(int col)// give it the col you want to insert at, it will give you the index to insert disc at
{
    int top = -9;
    for (int i = DISCS-1; i >= 0; i--) // from bottom, see if there is room
    {
        if (MTX[i][col] < 0) // checking at desired col  , no need to check full pole, that is not possible
        {
            top = i;
            goto foundTop;
        }
    }
    foundTop:
    return top;
}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================