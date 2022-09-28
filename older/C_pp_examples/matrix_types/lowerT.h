/*
    i < j elment must be 0
    Mtx[i][j] > 0    if i >= j
    
    has n(n+1)/2 elements vs n*n

    blank elements are n * n -   n(n+1)/2        or   n(n-1)/2 blank elements

    store row by row or col/col    row major best

    row(0) has 1 elm
    row(1) has 2 elm
    ....there is a formula to map the matrix onto the 1D array

    index for Mtx[i][j]  maps to     i(i-1) / 2   + j - 1         or  (i+1)i / 2  +  j   depending on index start 

    on col major, do  n(j-1)  -    (j-2)(j-1) / 2        + (i-j)   ...but it is garbage
*/
#ifndef H_lowerT
#define H_lowerT

#include "libs.h"

//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================
class lowT
{
    public:

        lowT(int size, std::string name); // {1} constructor with some defaults
        lowT(const lowT& other, std::string name); // {2} copy constructor
        void buildRandom(int size); // {3} build a random lower triangualr  matrix to target size
        void printMtx(); // {4} print the matrix    prints all to reval any errors
        void set(int row, int col, int val); // {5}  set ensure matrix stays lower triangular
        int getVal(int row, int col); // {6} getting through linerar 1D array, ensures matrix stays in lower triangle
        ~lowT(); // {-1} destructor

    private:

        int mapped_size(int size); // {-7} the 2D array mapped to 1D array has n(n+1)/2 elms
        int mapped_idx(int row, int col); // {-6} helper to give corresponding index in 1D array given desired matrix cell
        void initialize(); // {-5} helper to fill with blanks
        void clear(); // {-4} helper to wipe out all elements and set size to 0
        void copyMtx(const lowT& other); // {-3} helper to constructor and assigment ol, copies target obj
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
lowT::lowT(int size, std::string name) // {1} constructor with some defaults
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
lowT::lowT(const lowT& other, std::string name) // {2} copy constructor
{
    this->copyMtx(other);
    this->Name = name;
}

//--------------------------------------------------------------------------------------------------------------------------
void lowT::buildRandom(int size) // {3} build a random lower triangular matrix to target size
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
            if ( i >= j)
            {
                Mtx[i][j] = getRand();
                Map[mapped_idx(i,j)] = Mtx[i][j];
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void lowT::printMtx() // {4} print the matrix    prints all to reval any errors
{
    if (Size == 0)
    {
        std::cout << " {4} matrix is empty\n";
        return;
    }
    std::cout << Name << " , " << Size << " x " << Size << " , low-triangle matrix:\n";
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
void lowT::set(int row, int col, int val) // {5}  set ensure matrix stays lower triangular
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {5} set not possible, coordinates not in range\n";
        return;
    }
    if (row < col)
    {
        std::cout << " {5} set not possible, must keep triangle , row: " << row << " , col: " << col << " is illegal\n";
        return;
    }
    Map[mapped_idx(row,col)] = val;
    Mtx[row][col] = val;
}

//--------------------------------------------------------------------------------------------------------------------------
int lowT::getVal(int row, int col) // {6} getting through linerar 1D array, ensures matrix stays in lower triangle
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {6} get not possible\n";
        return Fill;
    }
    if (row >= col)
    {
        return Map[mapped_idx(row,col)];
    }
    else
    {
        return Fill;
    }   
}

//--------------------------------------------------------------------------------------------------------------------------
int lowT::mapped_size(int size) // {-7} the 2D array mapped to 1D array has n(n+1)/2 elms
{
    return (  (Size + 1) * Size) / 2;
}

//--------------------------------------------------------------------------------------------------------------------------
int lowT::mapped_idx(int row, int col) // {-6} helper to give corresponding index in 1D array given desired matrix cell
{
    return ( ( ( (row + 1) * row ) / 2 ) + col ); // use row major...col major is savage
}

//--------------------------------------------------------------------------------------------------------------------------
void lowT::initialize() // {-5} helper to fill with blanks
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
void lowT::clear() // {-4} helper to wipe out all elements and set size to 0
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
void lowT::copyMtx(const lowT& other) // {-3} helper to constructor and assigment ol, copies target obj
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
int lowT::getRand() // {-2} helper, provides random integer
{
    std::random_device rdevice{};                                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{Floor, Cieling}; 
    return randomNum1(num1);    
}

//--------------------------------------------------------------------------------------------------------------------------
lowT::~lowT() // {-1} destructor
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
#endif // lowerT.h