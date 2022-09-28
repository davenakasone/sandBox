/*

    for the constrained case, using base 3, no adjacent moves     still, each bit corresponds to a disc

    * 000 = 0,  3^0
      001 = 1,  1 * 3^0
      002 = 2   2 * 3^0
      010 = 3   3^1
      011 = 4   3^1 + 3^0
      012 = 5   3^1 + 2 * 3^0
      020 = 6   2 * 3^1
      021 = 7   2 * 3^1 + 3^0
      022 = 8   2* 3^1 + 2 * 3^0
      100 = 9   3^2   .........     

    unsigned long long int	8	0 to 18,446,744,073,709,551,615    == ( 2 ^ 63 ) - 1    64 bytes
    if you are going over 39 discs, that is savage and adjustments will be needed
    try to keep it to 9 discs max...3^9 - 1 = 19,682    maybe 3 and below to be reasonable

    come back with template if you want to make it a graph
*/

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

#ifndef H_toh_base3
#define H_toh_base3

//==========================================================================================================================
//                                           ~ ~ ~ CLASS ~ ~ ~                                                            //
//==========================================================================================================================


class toh3
{
    public:

        toh3(int discs = 3); // [1] constructor
        void run_tower(); //@ 2nd from end
        ~toh3(); // destructor @ end

    private:

        void set_base(); // [2]  prepares base
        void print_base();   // [3]  prints "pole_A  pole_B  pole_C "  with formating
        void set_trits();  // [4]   makes array to hold ternary representation
        void print_trits(); // [5] * prints MSB -> LSB in reverse so you can read left to right
        void set_mtx(); // [6]    -1 means empty
        void print_mtx(); // [7] a little string conversion
        long long int trit_to_dec(); // [8]   given trit, updates t_current to the needed value
        void dec_to_trit(long long int update); // [9] give a decimal and it will be put in as trits
        void copy_trits(); // [10] copies so you can keep record of previous before incrementing
        bool isLegal_for_col(int col, int disc); // [11]  true if disc can be moved to column
        int top_index_for_col(int col); // [12]   returns largest available opening for column

        const int poles = 3; // fixed by game rules
        const int cell_width = 9; // up to 6 spots for label, + 2 spaces to pad

        long long int t_reps; // moves made, should correspond to loop, LCV to stop
        int t_discs; // discs in tower
        long long int t_current; // decimal read-out of number in trit array, LCV counter and temp holder
        std::string t_base[3]; // just names the 3 poles

        int *trits; // holds the decimal representation in base 3     LSB to MSB
        int *trits_p; // previous set of trits
        int **mtx;  // holds integer representation of current state
};


//==========================================================================================================================
//                                           ~ ~ ~ IMP ~ ~ ~                                                              //
//==========================================================================================================================


//--------------------------------------------------------------------------------------------------------------------------
toh3::toh3(int discs) // [1]   CONSTRUCTOR w/ default
{
    if (discs > 39)
    {
        std::cout << "\n   can only support 39 discs maximum, you can have 3 discs\n";
        t_discs = 3;
    }
    else
    {
        t_discs = discs;
    }
    
    t_reps = std::pow(3,t_discs) - 1;
    t_current = 0;

    std::cout << "\n********************************************************************************";
    std::cout << "\n   a tower with " << t_discs << " discs was made\n"; 
    std::cout << "           this will take 3^" << t_discs << " - 1 iterations, or " << t_reps << " moves\n\n"; 

    set_base(); // prepare base
    set_trits(); // prepare trinary array
    set_mtx(); // prepar integer representer
    t_current = trit_to_dec(); // for update

    print_mtx();
    print_base();
    print_trits(); 

    std::cout << "\n********************************************************************************\n\n";
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::set_base() // [2]
{
    t_base[0] = "pole_A";
    t_base[1] = "pole_B";
    t_base[2] = "pole_C";
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::print_base()   // [3]
{
    std::cout << "________________________\n";
    for (int i = 0; i < poles; i++)
    {
        std::cout << std::left << std::setw(cell_width) << t_base[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::set_trits() // [4]
{
    trits_p = new int[t_discs];
    trits = new int[t_discs];
    for (int i = 0; i < t_discs; i++)
    {
        trits[i] = 0;
        trits_p[i] = trits[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::print_trits() // [5]
{
    std::cout << "                [  ";
    for (int i = t_discs - 1; i >= 0; i--)
    {
        std::cout << trits[i] << "  ";
    }
    std::cout << "]     decimal: " << t_current; // or call the [8] you barley use
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::set_mtx() // [6]
{
    mtx = new int*[t_discs];
    for (int i = 0; i < t_discs; i++)
    {
        mtx[i] = new int[poles];
        for (int j = 0; j < poles; j++)
        {
            if (j == 0)
            {
                mtx[i][j] = i;
            }
            else
            {
                mtx[i][j] = -1; // the empty value
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::print_mtx() // [7]
{
    for (int i = 0; i < t_discs; i++)
    {
        for (int j = 0; j < poles; j++)
        {
            if (mtx[i][j] >= 0)
            {
                std::cout << std::left << std::setw(cell_width) << "dis_" + std::to_string(mtx[i][j]);
            }
            else 
            {
                std::cout << std::left << std::setw(cell_width) << "      ";
            }
        }
        std::cout << std::endl;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
long long int toh3::trit_to_dec() // [8]
{
    long long int result = 0;
    for (int i = 0; i < t_discs; i++)
    {
        result = result + (trits[i] * std::pow(3,i));
    }
    return result;
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::dec_to_trit(long long int update) // [9]
{
    for (int i = 0; i < t_discs; i++)
    {
        if (update % 3 == 0)
        {
            trits[i] = 0;
        }
        else if (update % 3 == 1)
        {
            trits[i] = 1;
        }
        else
        {
            trits[i] = 2;
        }
        update = update / 3;
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::copy_trits() // [10]
{
    for (int i = 0; i < t_discs; i++)
    {
        trits_p[i] = trits[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
bool toh3::isLegal_for_col(int col, int disc) // [11]  true if disc can be moved to column      lots of patch work
{
    /*bool has0 = false; // patch 0   see if disc_0 is in the target col
    for (int i = 0; i < t_discs; i++)
    {
        if (mtx[i][col] == 0)
        {
            has0 = true; // disc_0 is in the target col, nothing is allowed to move on top of it
        }
    }
    if (has0 == true) // if the target col has disc_0
    {
        return false; // move is illegal
    }// patch 0 complete*/

    bool clear = true; // patch job 1   sees if target column is all clear (filled w/ -1   OR has disc_0)
    for (int i = 0; i < t_discs; i++)
    {
        if (mtx[i][col] >= 0) // if there is anything besides a [ -1 ]   OR [ 0 ]  the target col is not clear
        {
            clear = false;
        }
    }
    if(clear == true) 
    {
        return true;
    } // patch 1 complete

    bool too_big = false; // patch job 2    see if the disc can fit in the col
    for (int i = 0; i < t_discs; i++)
    {
        if (mtx[i][col] != -1 && disc > mtx[i][col])
        {
            too_big = true;
        }
    }
    if (too_big == false) // if the target disc is not too big to move to the target col
    {
        return true; // then it is legal
    } // patch 2 complete

    int** mtxC;
    mtxC = new int*[t_discs];
    for (int i = 0; i < t_discs; i++)
    {
        mtxC[i] = new int[poles];
        for (int j = 0; j < poles; j++)
        {
            mtxC[i][j] = mtx[i][j]; // just making a deep copy
        }
    }

    int rowC = -9; // current row
    int colC = -9; // current col

    for (int i = 0; i < t_discs; i++)
    {
        for (int j = 0; j < poles; j++)
        {
            if (disc == mtxC[i][j]) // found
            {
                rowC = i;
                colC = j;
            }
        }
    }

    if (std::abs(colC - col) != 1) // trying to move disc more than one peg, not allowed   stops full pegs also
    {
        return false;
    }

    mtxC[rowC][colC] = -1; // assume moving
    mtxC[top_index_for_col(col)][col] = disc; // and make the move, just have to check it doesn't violate stack

    for (int i = 0; i < t_discs; i++) // check for violations of larger on top of smaller
    {
        if (i > 0 && mtxC[i][col] < mtxC[i-1][col])
        {
            return false;
        }
    }

    for (int i = 0; i < t_discs; i++) // clean up
    {
        delete [] mtxC[i];
    }
    delete [] mtxC;
    mtxC = nullptr;
    return true;
}

//--------------------------------------------------------------------------------------------------------------------------
int toh3::top_index_for_col(int col) // [12]   returns largest available opening for column
{
    int topi = -9;
    for (int i = 0; i < t_discs; i++) 
    {
        if (mtx[i][col] < 0)
        {
            topi = i;
        }
    }
    return topi; // tells you which row index to insert at     -9 if col full
}

//--------------------------------------------------------------------------------------------------------------------------
void toh3::run_tower()
{
    bool rightWard = true; // A->B->C is true, C->B->A is false  for disc_0  to track its pattern
    int maxD = -9;
    int rowI = -9;
    int colI = -9;
    bool* diff;
    diff = new bool[t_discs];

    for (t_current = 1; t_current <= t_reps; t_current++) // start the BIG LOOP
    {   
        if (t_current % 3 == 0) // this is the key to get the switch for disc_0
        {
            rightWard = !rightWard; // switch direction of travel for disc_0
        }
                                                           //std::cout << "rightward: " << rightWard;//TEST

        dec_to_trit(t_current); // update for current trinary sequence
                                /*//TEST
                                std::cout << "   , trit_p [  ";
                                for (int i = t_discs - 1; i >= 0; i--)
                                {
                                    std::cout << trits_p[i] << "  ";
                                }
                                std::cout << "]    ";
                                //TEST*/
        for (int i = 0; i < t_discs; i++) // find out what changed, this rythm will determine movements
        {
            if (trits[i] != trits_p[i])
            {
                diff[i] = true; // moving criteria met
            }
            else
            {
                diff[i] = false; // trit did not change
            }
        }
                                /*//TEST
                                std::cout << "  ,  diff  [  ";
                                for (int i = 0; i < t_discs; i++)
                                {
                                    std::cout << diff[i] << "  ";
                                }
                                std::cout << "]    ";
                                //TEST*/
        for (int i = 0; i < t_discs; i++) // record largest disc to move
        {
            if (diff[i])
            {
                maxD = i; // takes disc with highest index that has met moving criteria
            }
        }

        for (int i = 0; i < t_discs; i++) // find out coordinates of the target disc
        {
            for (int j = 0; j < poles; j++)
            {
                if (mtx[i][j] == maxD)
                {
                    rowI = i;
                    colI = j;
                }
            }
        }
                                            
                                                   //std::cout << "  maxD: " << maxD << " , rowI: " << rowI << " , colI: " << colI; //TEST
        mtx[rowI][colI] = -1; // clear
        if(maxD == 0) // disc 0 has its own pattern ...0 -> 1 -> 2 -> 1 -> 0 -> 1 -> ... 
        {
            if (colI == 0) // on col 0, must go to col 1
            {
                mtx[top_index_for_col(1)][1] = maxD; 
                                                             //std::cout << "   , disc_0 > col 0 to col 1"; //TEST
            }
            else if (colI == 1) // on col 1, must go to col 2 or col 0 ... what pole on previously
            {
                if (rightWard) // came onto pole_B from pole_A -> pole_C (col2)
                {
                    mtx[top_index_for_col(2)][2] = maxD;
                                                            //std::cout << "  ,  disc_0 > col 1 to col 2"; //TEST
                }
                else // came onto pole_B from pole_C -> pole_A (col0)
                {
                    mtx[top_index_for_col(0)][0] = maxD;
                                                           //std::cout << "  ,  disc_0 > col 1 to col 0"; //TEST
                }
            }
            else // on col 2, must got to col 1
            {
                mtx[top_index_for_col(1)][1] = maxD; 
                                                           //std::cout << "  ,  disc_0 > col 2 to col 1"; //TEST
            }
        }
        else
        {
            if (colI == 0) // on col 0, have to go to col 1
            {
                mtx[top_index_for_col(1)][1] = maxD;
                                                           //std::cout << " , disc_" << maxD << " > col 0 to col " << 1;//TEST
            }
            else if (colI == 1) // on col 1, can go col 0 OR col 2
            {
                if (isLegal_for_col(0, maxD)) // if it can go to col 0, take it
                {
                    mtx[top_index_for_col(0)][0] = maxD; 
                                                           //std::cout << "  , disc_" << maxD << "  > col 1 to col " << 0;//TEST
                }
                else // has to go to col 2
                {
                    mtx[top_index_for_col(2)][2] = maxD;
                                                          //std::cout << " ,  disc_" << maxD << "  > col 1 to col " << 2;//TEST
                }
            }
            else // in col 2, it can onl go to col 1
            {
                mtx[top_index_for_col(1)][1] = maxD;
                                                          //std::cout << "  , disc_" << maxD << " > col 2 to col " << 1;//TEST
            }
        }
        
        std::cout << std::endl;
        print_mtx(); 
        print_base();
        print_trits(); 
        std::cout << "\n--------------------------------------------------------------------------------";
        copy_trits(); // copy to preserve lag
    }
    delete [] diff; // only cleaning needed
    diff = nullptr;
}

//--------------------------------------------------------------------------------------------------------------------------
toh3::~toh3() // destructor to clean up dynamics
{
    delete [] trits;
    delete [] trits_p;
    for (int i = 0; i < t_discs; i++)
    {
        delete [] mtx[i];
    }
    delete [] mtx;
    std::cout << "\n     obj destroyed, see above for time(s)\n";
}

#endif // end toh_base3.h
//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================
