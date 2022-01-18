/*
    also square, has all non-blank elements
    all elements in diagonals are the same

    [0][0] = [1][1] = [2][2] ....    

    Mtx[i][j] = Mtx[i-1][j-1]   there is a pattern
    store first row and first col and you have it 

    non-blank  2 * Size - 1

    1 2 3 4
    5 1 2 3           ->  row0 , col0 stating col0 @ [1]      { 1, 2, 3, 4     ,    5, 6, 7} mapped
    6 5 1 2
    7 6 5 1            the upper triangle is i <= j   case 1   take from row, idx = j - i
                       lower triange i > j  case 2             idx = Size +  i - j - 1                       
*/

#ifndef H_toeplitz
#define H_toeplitz

#include "libs.h"

//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================
class toep
{
    public:

        toep(int size, std::string name); // {1} constructor with some defaults
        toep(const toep& other, std::string name); // {2} copy constructor
        void buildRandom(int size); // {3} build a random toeplitz  matrix to target size
        void printMtx(); // {4} print the matrix    prints all to reval any errors
        void set(int row, int col, int val); // {5}  set ensure matrix toeplitz
        int getVal(int row, int col); // {6} getting through linerar 1D array, ensures matrix stays in toeplitz
        ~toep(); // {-1} destructor

    private:

        int mapped_size(int size); // {-7} the 2D array mapped to 1D array has 3n - 2 elms
        int mapped_idx(int row, int col); // {-6} helper to give corresponding index in 1D array given desired matrix cell
        void initialize(); // {-5} helper to fill with blanks
        void clear(); // {-4} helper to wipe out all elements and set size to 0
        void copyMtx(const toep& other); // {-3} helper to constructor and assigment ol, copies target obj
        int getRand(); // {-2} helper, provides random integer

        int Size; // still has to be a square matrix
        int SizeMap; // by formula
        int** Mtx;
        int* Map; // in row major
        std::string Name;

        int Floor = 11;
        int Cieling = 99;
        const int Fill = -4;
};
//==========================================================================================================================
//                                           ~ ~ ~ IMP ~ ~ ~                                                              //
//==========================================================================================================================


//--------------------------------------------------------------------------------------------------------------------------
toep::toep(int size, std::string name) // {1} constructor with some defaults
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
    SizeMap = mapped_size(Size);
    Name = name;
    initialize();
}
//--------------------------------------------------------------------------------------------------------------------------
toep::toep(const toep& other, std::string name) // {2} copy constructor
{
    this->copyMtx(other);
    this->Name = name;
}

//--------------------------------------------------------------------------------------------------------------------------
void toep::buildRandom(int size) // {3} build a random toeplitz matrix to target size
{
    if (size <=0)
    {
        std::cout << " {3} making size = 5\n";
        size = 5;
    }
    clear();
    Size = size;
    SizeMap = mapped_size(Size);
    initialize();
    for (int i = 0; i < SizeMap; i++)
    {
        Map[i] = getRand();
    }
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            Mtx[i][j] = Map[mapped_idx(i,j)];
        }
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------
void toep::printMtx() // {4} print the matrix    prints all to reval any errors
{
    if (Size == 0)
    {
        std::cout << " {4} matrix is empty\n";
        return;
    }
    std::cout << Name << " , " << Size << " x " << Size << " , toep matrix:\n";
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
    std::cout << "  as 1D [  ";
    for (int i = 0; i < SizeMap; i++)
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
void toep::set(int row, int col, int val) // {5}  set ensure matrix stays toep
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {5} set not possible, coordinates not in range\n";
        return;
    }
    Map[mapped_idx(row,col)] = val;
    
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            Mtx[i][j] = Map[mapped_idx(i,j)];
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int toep::getVal(int row, int col) // {6} getting through linerar 1D array, ensures matrix stays toep
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {6} get not possible\n";
        return Fill;
    }
    return Map[mapped_idx(row,col)];
}

//--------------------------------------------------------------------------------------------------------------------------
int toep::mapped_size(int size) // {-7} the 2D array mapped to 1D array has n(n+1)/2 elms
{
    return 2 * Size - 1;
}

//--------------------------------------------------------------------------------------------------------------------------
int toep::mapped_idx(int row, int col) // {-6} helper to give corresponding index in 1D array given desired matrix cell
{
    // use row major...col major is savage
    if ( row < 0 || row >= Size || col < 0 || col >= Size)
    {
        return -9; // something is wrong
    }
    else if (row <= col) // upper triangle
    {
        return col - row; 
    }
    else  // lower triangle row > col
    {
        return Size + row - col - 1;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void toep::initialize() // {-5} helper to fill with blanks
{
    Map = new int[SizeMap];
    Mtx = new int*[Size];
    for (int i = 0; i < Size; i++)
    {
        Mtx[i] = new int[Size];
    }
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            Mtx[i][j] = Fill;
        }
    }
    for (int i = 0; i < SizeMap; i++)
    {
        Map[i] = Fill;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void toep::clear() // {-4} helper to wipe out all elements and set size to 0
{
    if (Size != 0)
    {
        for (int i = 0; i < Size; i++)
        {
            delete [] Mtx[i];
        }
        delete [] Mtx;
        delete [] Map;
        Size = 0;
        SizeMap = 0;
    }
    Mtx = nullptr;
    Map = nullptr;
}

//--------------------------------------------------------------------------------------------------------------------------
void toep::copyMtx(const toep& other) // {-3} helper to constructor and assigment ol, copies target obj
{
    this->clear();
    this->Size = other.Size;
    this->SizeMap = other.SizeMap;
    this->Map = new int[SizeMap];
    this->Mtx = new int*[Size];
    
    for (int i = 0; i < this->Size; i++)
    {
        this->Mtx[i] = new int[Size];
        for (int j = 0; j < Size; j++)
        {
            this->Mtx[i][j] = other.Mtx[i][j];
        }
    }
    for (int i = 0; i < this->SizeMap; i++)
    {
        this->Map[i] = other.Map[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int toep::getRand() // {-2} helper, provides random integer
{
    std::random_device rdevice{};                                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{Floor, Cieling}; 
    return randomNum1(num1);    
}

//--------------------------------------------------------------------------------------------------------------------------
toep::~toep() // {-1} destructor
{
    Size = 0;
    SizeMap = 0;
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
#endif // toeplitz.h