/*
    only has 3 diagonals...tri-diagonal matrix
    has main diagonal i = j    i-j = 0
    lower diagonal  i-j = 1
    upper diagonal i-j = -1

    abs(i-j) <= 1

    Mtx[i][j] > 0   if abs(i -j) <= 1

    non-blank   =   n + (n-1) + (n-1)       = 3n - 2
    can also put in 1D array

    case1: i - j = 1 , get your index from i striaght      lower i-j = 1
    case2: size of row/col + i - 1       size + i - 1      main diagonal i - j = 0
    case3: 2(size) + i - 1                                  upper i-j = -1
*/

#ifndef H_triDiag
#define H_triDiag

#include "libs.h"

//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================
class triD
{
    public:

        triD(int size, std::string name); // {1} constructor with some defaults
        triD(const triD& other, std::string name); // {2} copy constructor
        void buildRandom(int size); // {3} build a random triDiag  matrix to target size
        void printMtx(); // {4} print the matrix    prints all to reval any errors
        void set(int row, int col, int val); // {5}  set ensure matrix triDiag
        int getVal(int row, int col); // {6} getting through linerar 1D array, ensures matrix stays in triDiag
        ~triD(); // {-1} destructor

    private:

        int mapped_size(int size); // {-7} the 2D array mapped to 1D array has 3n - 2 elms
        int mapped_idx(int row, int col); // {-6} helper to give corresponding index in 1D array given desired matrix cell
        void initialize(); // {-5} helper to fill with blanks
        void clear(); // {-4} helper to wipe out all elements and set size to 0
        void copyMtx(const triD& other); // {-3} helper to constructor and assigment ol, copies target obj
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
triD::triD(int size, std::string name) // {1} constructor with some defaults
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
triD::triD(const triD& other, std::string name) // {2} copy constructor
{
    this->copyMtx(other);
    this->Name = name;
}

//--------------------------------------------------------------------------------------------------------------------------
void triD::buildRandom(int size) // {3} build a random triD matrix to target size
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
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if ( std::abs(i-j) <= 1)
            {
                Mtx[i][j] = getRand();
                Map[mapped_idx(i,j)] = Mtx[i][j];
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void triD::printMtx() // {4} print the matrix    prints all to reval any errors
{
    if (Size == 0)
    {
        std::cout << " {4} matrix is empty\n";
        return;
    }
    std::cout << Name << " , " << Size << " x " << Size << " , triD matrix:\n";
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
void triD::set(int row, int col, int val) // {5}  set ensure matrix stays triD
{
    if (row < 0 || row >= Size || col < 0 || col >= Size || std::abs(row-col) > 1)
    {
        std::cout << " {5} set not possible, coordinates not in range\n";
        return;
    }
    
    Map[mapped_idx(row,col)] = val;
    Mtx[row][col] = val;
}

//--------------------------------------------------------------------------------------------------------------------------
int triD::getVal(int row, int col) // {6} getting through linerar 1D array, ensures matrix stays triD
{
    if (row < 0 || row >= Size || col < 0 || col >= Size || std::abs(row-col) > 1)
    {
        std::cout << " {6} get not possible\n";
        return Fill;
    }
    return Map[mapped_idx(row,col)];
}

//--------------------------------------------------------------------------------------------------------------------------
int triD::mapped_size(int size) // {-7} the 2D array mapped to 1D array has n(n+1)/2 elms
{
    return 3 * Size - 2;
}

//--------------------------------------------------------------------------------------------------------------------------
int triD::mapped_idx(int row, int col) // {-6} helper to give corresponding index in 1D array given desired matrix cell
{
    // use row major...col major is savage
    if ( row < 0 || row >= Size || col < 0 || col >= Size || std::abs(row-col) > 1)
    {
        return -9; // something is wrong
    }
    else if (row - col == 1) // lower diagonal
    {
        return row; 
    }
    else if (row - col == 0) // main diagonal
    {
        return Size + row - 1;
    }
    else // i - j = -1   upper diagonal
    {
        return 2 * Size + row - 1;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void triD::initialize() // {-5} helper to fill with blanks
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
void triD::clear() // {-4} helper to wipe out all elements and set size to 0
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
void triD::copyMtx(const triD& other) // {-3} helper to constructor and assigment ol, copies target obj
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
int triD::getRand() // {-2} helper, provides random integer
{
    std::random_device rdevice{};                                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{Floor, Cieling}; 
    return randomNum1(num1);    
}

//--------------------------------------------------------------------------------------------------------------------------
triD::~triD() // {-1} destructor
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
#endif // triDiag.h