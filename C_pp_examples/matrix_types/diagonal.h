/*
    diagonal matrix only has values in diagonals                         Mtx[i][j] = blank     if i != j
    n x n is a waste...only need n just keep the diagonal
    only diagonal means both row and col same... idea is to do everything through a single dimension array
*/

#ifndef H_diagonal
#define H_diagonal

#include "libs.h"
//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================
class diagMtx
{
    public:

        diagMtx(int size = 5, std::string name = "OBJ"); // {1} constructor with some defaults
        diagMtx(const diagMtx& other, std::string name = "OBJ COPIED"); // {2} copy constructor 
        void buildRandom(int size); // {3} build a random diagonal matrix to target size
        void printMtx(); // {4} print the matrix
        int getSize() {return Size;} 
        void set(int row, int col, int val); // {5}  set through linear 1D array,  keeps main one diagonal
        int getVal(int row, int col); // {6} getting through linerar 1D array, ensures matrix stays diagonal
        ~diagMtx(); // {-1} destructor

    private:

        void initialize(); // {-5} helper to fill with blanks
        void clear(); // {-4} helper to wipe out all elements and set size to 0
        void copyMtx(const diagMtx& other); // {-3} helper to constructor and assigment ol, copies target obj
        int getRand(); // {-2} helper, provides random integer

        int** Mtx;
        int* Map;
        int Size; // assumed square  dimensions are size x size also size of map
        std::string Name;
        
        int Floor = 11;
        int Cieling = 99;
        const int Fill = -4;

};


//==========================================================================================================================
//                                           ~ ~ ~ IMP ~ ~ ~                                                              //
//==========================================================================================================================



//--------------------------------------------------------------------------------------------------------------------------
diagMtx::diagMtx(int size, std::string name) // {1} constructor with some defaults
{
    if (size <= 0)
    {
        std::cout << " {1} matrix size will be 5\n";
        Size = 5;
    }
    else
    {
        Size = size;
    }
    Name = name;
    initialize();
}

//--------------------------------------------------------------------------------------------------------------------------
diagMtx::diagMtx(const diagMtx& other, std::string name) // {2} copy constructor
{
    this->copyMtx(other);
    this->Name = name;
}

//--------------------------------------------------------------------------------------------------------------------------
void diagMtx::buildRandom(int size) // {3} build a random diagonal matrix to target size
{
    if (size <=0)
    {
        std::cout << " {3} making size = 5\n";
        size = 5;
    }
    clear();
    Size = size;
    initialize();
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if ( i == j)
            {
                Mtx[i][j] = getRand();
                Map[i] = Mtx[i][j];
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void diagMtx::printMtx() // {4} print the matrix    prints all to reval any errors
{
    if (Size == 0)
    {
        std::cout << " {4} matrix is empty\n";
        return;
    }
    std::cout << Name << " , " << Size << " x " << Size << " , diagonal matrix:\n";
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (Mtx[i][j] != Fill)
            {
                std::cout << std::left << std::setfill(' ') << std::setw(4) << Mtx[i][j];
            }
            else
            {
                std::cout << std::left << std::setfill(' ') << std::setw(4) << 'x';
            }
            
        }
        std::cout << std::endl;
    }
    std::cout << "  diagonal [  ";
    for (int i = 0; i < Size; i++)
    {
        if (Map[i] != Fill)
        {
            std::cout << std::left << std::setfill(' ') << std::setw(4) << Map[i];
        }
        else
        {
            std::cout << std::left << std::setfill(' ') << std::setw(4) << 'x';
        } 
    }
    std::cout << "]\n\n";
}

//--------------------------------------------------------------------------------------------------------------------------
void diagMtx::set(int row, int col, int val) // {5}  set through linear 1D array only to keep main one diagonal
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {5} set not possible, coordinates not in range\n";
        return;
    }
    if (row != col)
    {
        std::cout << " {5} set not possible, must be diagonal , row: " << row << " , col: " << col << " is illegal\n";
        return;
    }
    Map[row] = val;
    Mtx[row][col] = val;
}

//--------------------------------------------------------------------------------------------------------------------------
int diagMtx::getVal(int row, int col) // {6} getting through linerar 1D array, ensures matrix stays diagonal
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {6} get not possible\n";
        return Fill;
    }

    if (row == col)
    {
        return Map[row];
    }
    else
    {
        return Fill;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void diagMtx::initialize() // {-5} helper to fill with blanks
{
    Map = new int[Size];
    Mtx = new int*[Size];
    for (int i = 0; i < Size; i++)
    {
        Mtx[i] = new int[Size];
    }
    for (int i = 0; i < Size; i++)
    {
        Map[i] = Fill;
        for (int j = 0; j < Size; j++)
        {
            Mtx[i][j] = Fill;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void diagMtx::clear() // {-4} helper to wipe out all elements and set size to 0
{
    if (Size == 0)
    {
        Mtx = nullptr;
    }
    else
    {
        for (int i = 0; i < Size; i++)
        {
            delete [] Mtx[i];
        }
        delete [] Mtx;
        delete [] Map;
        Size = 0;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void diagMtx::copyMtx(const diagMtx& other) // {-3} helper to constructor and assigment ol, copies target obj
{
    this->clear();
    this->Size = other.Size;
    this->Map = new int[Size];
    this->Mtx = new int*[Size];
   
    for (int i = 0; i < this->Size; i++)
    {
        this->Mtx[i] = new int[Size];
        this->Map[i] = other.Map[i];
        for (int j = 0; j < Size; j++)
        {
            this->Mtx[i][j] = other.Mtx[i][j];
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int diagMtx::getRand() // {-2} helper, provides random integer
{
    std::random_device rdevice{};                                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{Floor, Cieling}; 
    return randomNum1(num1);    
}

//--------------------------------------------------------------------------------------------------------------------------
diagMtx::~diagMtx() // {-1} destructor
{
    Size = 0;
    for (int i = 0; i < Size; i++)
    {
        delete [] Mtx[i];
    }
    delete [] Mtx;
    delete [] Map;
    Map = nullptr;
    Mtx = nullptr;
    std::cout << "\n  {-1}     deallocated: " << Name << std::endl;
}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================
#endif // diagonal.h