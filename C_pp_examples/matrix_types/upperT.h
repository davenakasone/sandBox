/*
    Mtx[i][j] > 0   if    i <= j
    Mtx[i][j] = 0   if    i > j

    non zero same way    n ( n + 1 ) / 2
    zero elms            n ( n - 1 ) / 2

    also want to avoid space of blanks
    use the 1D array

    row major   use    [ i * n     - ((i-1) * i) / 2]  + (j-i)       adjust for 0/1
    col major  use   [ j*(j-1) / 2] + (i - 1)

*/
#ifndef H_upperT
#define H_upperT

#include "libs.h"

//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================
class upT
{
    public:

        upT(int size, std::string name); // {1} constructor with some defaults
        upT(const upT& other, std::string name); // {2} copy constructor
        void buildRandom(int size); // {3} build a random upper triangualr  matrix to target size
        void printMtx(); // {4} print the matrix    prints all to reval any errors
        void set(int row, int col, int val); // {5}  set ensure matrix stays upper triangular
        int getVal(int row, int col); // {6} getting through linerar 1D array, ensures matrix stays in upper triangle
        ~upT(); // {-1} destructor

    private:

        int mapped_size(int size); // {-7} the 2D array mapped to 1D array has n(n+1)/2 elms
        int mapped_idx(int row, int col); // {-6} helper to give corresponding index in 1D array given desired matrix cell
        void initialize(); // {-5} helper to fill with blanks
        void clear(); // {-4} helper to wipe out all elements and set size to 0
        void copyMtx(const upT& other); // {-3} helper to constructor and assigment ol, copies target obj
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
upT::upT(int size, std::string name) // {1} constructor with some defaults
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
upT::upT(const upT& other, std::string name) // {2} copy constructor
{
    this->copyMtx(other);
    this->Name = name;
}

//--------------------------------------------------------------------------------------------------------------------------
void upT::buildRandom(int size) // {3} build a random upper triangular matrix to target size
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
            if ( i <= j)
            {
                Mtx[i][j] = getRand();
                Map[mapped_idx(i,j)] = Mtx[i][j];
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void upT::printMtx() // {4} print the matrix    prints all to reval any errors
{
    if (Size == 0)
    {
        std::cout << " {4} matrix is empty\n";
        return;
    }
    std::cout << Name << " , " << Size << " x " << Size << " , up-triangle matrix:\n";
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
void upT::set(int row, int col, int val) // {5}  set ensure matrix stays upper triangular
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {5} set not possible, coordinates not in range\n";
        return;
    }
    if (row > col)
    {
        std::cout << " {5} set not possible, must keep triangle , row: " << row << " , col: " << col << " is illegal\n";
        return;
    }
    Map[mapped_idx(row,col)] = val;
    Mtx[row][col] = val;
}

//--------------------------------------------------------------------------------------------------------------------------
int upT::getVal(int row, int col) // {6} getting through linerar 1D array, ensures matrix stays in upper triangle
{
    if (row < 0 || row >= Size || col < 0 || col >= Size)
    {
        std::cout << " {6} get not possible\n";
        return Fill;
    }
    if (row <= col)
    {
        return Map[mapped_idx(row,col)];
    }
    else
    {
        return Fill;
    }   
}

//--------------------------------------------------------------------------------------------------------------------------
int upT::mapped_size(int size) // {-7} the 2D array mapped to 1D array has n(n+1)/2 elms
{
    return (  (Size + 1) * Size) / 2;
}

//--------------------------------------------------------------------------------------------------------------------------
int upT::mapped_idx(int row, int col) // {-6} helper to give corresponding index in 1D array given desired matrix cell
{
    // use row major...col major is savage
    return (  ( (row * Size) - ( (row - 1) * row) / 2 ) + (col - row)  );
}

//--------------------------------------------------------------------------------------------------------------------------
void upT::initialize() // {-5} helper to fill with blanks
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
void upT::clear() // {-4} helper to wipe out all elements and set size to 0
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
void upT::copyMtx(const upT& other) // {-3} helper to constructor and assigment ol, copies target obj
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
int upT::getRand() // {-2} helper, provides random integer
{
    std::random_device rdevice{};                                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{Floor, Cieling}; 
    return randomNum1(num1);    
}

//--------------------------------------------------------------------------------------------------------------------------
upT::~upT() // {-1} destructor
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
#endif // upperT.h