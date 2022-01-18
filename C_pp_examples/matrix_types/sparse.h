/*
    does not have to be square, has more blanks than elements with values
    just want to store non blank

    -compressed sparse row (3-column rep)  like coordinates
    -coordinate list  (row, col, val)

     0 0 0 0 3
     8 0 1 0 0
     0 4 0 0 7
     0 9 0 0 0

    4 rows, 5 cols            

    ROW COL VAL     // coordinate list
     4   5   6      store matrix dimensions and number of non-blank elements
     0   4   3      Mtx[0][4] = 3
     1   0   8      Mtx[1][0] = 8
     1   2   1      Mtx[1][2] = 1
     2   1   4      Mtx[2][1] = 4
     2   4   7      Mtx[2][4] = 7
     3   1   9      Mtx[3][1] = 9

    // the compressed sparse row uses 3 arrays
    Vals [ 3, 8, 1, 4, 7, 9 ]    take the non-blank elements as they appear, don't change order
    Rows [ 1, 3, 5, 6 ]         cummulative number of elements in row   subtraction implies elements in each row
    Cols [ 4, 0, 2, 1, 4, 1 ]   col element appears in

    m x n elements, either option reduces foot print a lot

    to add 2 matricies, dimensions must be SAME
    every element must be added to other @ same index
    with coord list, use helper functions or make a new coord list big enough to hold all posibilities

*/

#ifndef H_sparse
#define H_sparse

#include "libs.h"

//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================


class spr
{
    public:

        spr(int rows = 3, int cols = 4, int sparses = 5, std::string name = "OBJ"); // {1} defualt constructor with parameters
        spr(const spr& other, std::string name = "OBJ"); // {2} copy constructor
        void buildRandom(int rows, int cols, int sparses); // {3} clear current obj and build it to provided dimensions
        void print(); // {4} prints matix and coordinate list
        int getVal(int row, int col); // {5} returns value at index (if legal), using Coord list to maintain
        void set(int row, int col, int val); // {6} sets value , adjusts obj if needed
        void addOther(const spr& other); // {7} give it another matrix, and it will add to update this obj
        void copyOther(const spr& other); // {8} overwrite other obj onto this obj, except Name
        void wipe(); // {9} make all elements blank
        ~spr(); // {-1} destructor

    private:

        void initialize(); // {-5} helper to fill with blanks and get Coord list set
        void clear(); // {-4} helper to deallocate 
        void copy(const spr& other); // {-3} helper to make deep copy of other obj into this obj
        int getRand(int min, int max); // {-2} helper to provide a random integer, given a min and max

        int SizeRows = 0;          // row dimension of target matrix
        int SizeCols = 0;          // col dimension of target matrix
        int ElmsTotal = 0;         // SizeRows * SizeCols
        int ElmsSparse = 0;        // number of elements that are not blank
        int** Mtx;                 // not really here, just to show results
        int** Coord;               // the coordinate list implementation is best for programmers
        int CoordRows = 0;         // first row for   SizeRows, SizeCols, number of non-blanks    next (row, col, val)
        const int CoordCols = 3;   // should remain at 3 for all 2D matrix
        std::string Name;

        const int ValMin = 11;      // minimum value element can be
        const int ValMax = 99;     // max value element can be
        const int Blank = INT_MIN;       // blank element
};


//==========================================================================================================================
//                                           ~ ~ ~ IMP ~ ~ ~                                                              //
//==========================================================================================================================


//--------------------------------------------------------------------------------------------------------------------------
spr::spr(int rows, int cols, int sparses, std::string name) // {1} defualt constructor with parameters
{
    if (rows <= 0 || cols <= 0 || sparses < 1)
    {
        std::cout << " {1} using 3 rows, 4 cols, 5 sparse elements so matrix at least has some size\n";
        SizeRows = 3;
        SizeCols = 4;
        ElmsSparse = 5;
    }
    else
    {
        SizeRows = rows;
        SizeCols = cols;
        ElmsSparse = sparses;
    }
    Name = name;
    initialize();
    buildRandom(rows, cols, sparses);
}

//--------------------------------------------------------------------------------------------------------------------------
spr::spr(const spr& other, std::string name) // {2} copy constructor
{
    this->Name = name;
    this->SizeRows = other.SizeRows;
    this->SizeCols = other.SizeCols;
    this->ElmsSparse = other.ElmsSparse;
    initialize();
    this->copy(other);
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::buildRandom(int rows, int cols, int sparses) // {3} clear current obj and build it to provided dimensions
{
    if (rows <= 0 || cols <= 0 || sparses <= 0)
    {
        std::cout << " {3} using 3 rows, 4 cols, and 5 sparses\n";
        rows = 3;
        cols = 4;
        sparses = 5;
    }
    clear();
    SizeRows = rows;
    SizeCols = cols;
    ElmsSparse = sparses;
    initialize();
    for (int i = 1; i < CoordRows; i++)
    {
        Coord[i][2] = getRand(ValMin, ValMax);
    }

    bool** used;
    used = new bool*[SizeRows];
    for (int i = 0; i < SizeRows; i++)
    {
        used[i] = new bool[SizeCols];
        for (int j = 0; j < SizeCols; j++)
        {
            used[i][j] = false;
        }
    }

    int filled = 1;
    int row = -9;
    int col = -9;
    while (filled < CoordRows)
    {
        row = getRand(0, SizeRows-1);
        col = getRand(0, SizeCols-1);
        if (!used[row][col])
        {
            Coord[filled][0] = row;
            Coord[filled][1] = col;
            Mtx[row][col] = Coord[filled][2];
            filled++;
            used[row][col] = true;
        }
    }

    for (int i = 0; i < SizeRows; i++)
    {
        delete [] used[i];
    }
    delete [] used;
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::print() // {4} prints matix and coordinate list
{
    if (SizeRows <= 0 || SizeCols <= 0 || ElmsSparse <= 0)
    {
        std::cout << " {4} matrix is empty\n";
        return;
    }
    std::cout << Name << "  , elements: " << ElmsTotal << " , rows: " << Coord[0][0] << " , cols: " 
        << Coord[0][1] << " , sparse matrix:\n";
    for (int i = 0; i < SizeRows; i++)
    {
        for (int j = 0; j < SizeCols; j++)
        {
            if (Mtx[i][j] != Blank)
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
    
    std::cout << "------------------COORD LIST\n";
    std::cout << "Row  Col  Value         for " << Coord[0][2] << " elements\n";
    for (int i = 1; i < CoordRows; i++)
    {
        std::cout << std::right << std::setfill(' ') << std::setw(2) << Coord[i][0];
        std::cout << std::right << std::setfill(' ') << std::setw(5) << Coord[i][1];
        std::cout << std::right << std::setfill(' ') << std::setw(6) << Coord[i][2];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------
int spr::getVal(int row, int col) // {5} returns value at index (if legal), using Coord list to maintain
{
    if (row >= SizeRows || row < 0 || col >= SizeCols || col < 0)
    {
        std::cout << " {5}  invlaid index\n";
        return -9;
    }
    else if (ElmsSparse > 0)
    {
        for (int i = 1; i < CoordRows; i++)
        {
            if (Coord[i][0] == row && Coord[i][1] == col)
            {
                return Coord[i][2];        // found matching row-col, look up value and return it
            }
        }
        return Blank; // element not on list, but in limits of matrix, so it must be blank
    }
    else // ElmsSparse == 0
    {
        return Blank;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::set(int row, int col, int val) // {6} sets value , adjusts obj if needed
{
    if (row >= SizeRows || row < 0 || col >= SizeCols || col < 0)
    {
        std::cout << " {6}  invlaid index\n";
    }
    else if (ElmsSparse == 0 && val > Blank) // matrix is empty, came from clear
    {
        CoordRows++;  // = 2
        ElmsSparse++; // = 1
        Coord = new int*[CoordRows];
        Coord[0] = new int[CoordCols];
        Coord[1] = new int [CoordCols];
        Coord[0][0] = SizeRows;
        Coord[0][1] = SizeCols;
        Coord[0][2] = ElmsSparse;
        Coord[1][0] = row;
        Coord[1][1] = col;
        Coord[1][2] = val;
        Mtx[row][col] = val;
    }
    else if (getVal(row, col) > Blank && val > Blank && ElmsSparse > 0) // already in coordinate list
    {
        for (int i = 1; i < CoordRows; i++)
        {
            if (Coord[i][0] == row && Coord[i][1] == col)
            {
                Coord[i][2] = val;        // update
            }
        }
        Mtx[row][col] = val;
    }
    else if (getVal(row, col) > Blank && val == Blank && ElmsSparse > 0) // want to delete an existing value
    {
        for (int i = 0; i < CoordRows; i++)
        {
            if (Coord[i][0] == row && Coord[i][1] == col)
            {
                Coord[i][2] = Blank; // mark for removal
            }
        }

        CoordRows--;
        ElmsSparse--;
        Mtx[row][col] = Blank;

        int **holder;
        holder = new int*[CoordRows];
        for (int i = 0; i < CoordRows; i++)
        {
            holder[i] = new int[CoordCols];
        }
        holder[0][0] = Coord[0][0];
        holder[0][1] = Coord[0][1];
        holder[0][2] = Coord[0][2] - 1;
        

        int count = 1;
        int rep = 1;
        while (rep < CoordRows + 1) // less than old CoordRows 
        {
            if (Coord[rep][2] > 0)
            {
                holder[count][0] = Coord[rep][0];
                holder[count][1] = Coord[rep][1];
                holder[count][2] = Coord[rep][2];
                count++;
                rep++;
            }
            else
            {
                rep++;
            }
        }

        for (int i = 0; i < CoordRows + 1; i++) // copy complete, deallocate and build to new size
        {
            delete [] Coord[i];
        }
        delete [] Coord;
        Coord = new int*[CoordRows];
        for (int i = 0; i < CoordRows; i++)
        {
            Coord[i] = new int[CoordCols];
            for (int j = 0; j < CoordCols; j++)
            {
                Coord[i][j] = holder[i][j]; // copy complete, everything is updated
            }
        }

        for (int i = 0; i < CoordRows; i++)
        {
            delete [] holder[i];
        }
        delete [] holder;
    }
    else if (val == Blank) // don't have to do much, they want to add a blank
    {
        std::cout << " {6}  element at row:" << row << " , col: " << col << " already blank\n";
    } 
    else // getVal(row, col) < 0 && val > Blank  want to add new non-blank element , not already in coord list
    {
        ElmsSparse++;
        CoordRows++;
        Mtx[row][col] = val;

        int **holder;
        holder = new int*[CoordRows];
        for (int i = 0; i < CoordRows; i++)
        {
            holder[i] = new int[CoordCols];
        }

        for (int i = 0; i < CoordRows - 1; i++)
        {
            for (int j = 0; j < CoordCols; j++)
            {
                holder[i][j] = Coord[i][j]; // copied all but last row
            }
        }
        holder[0][2] = ElmsSparse; // only top-row element needed to update, rows and cols stay same
        holder[CoordRows-1][0] = row;
        holder[CoordRows-1][1] = col;
        holder[CoordRows-1][2] = val;

        for (int i = 0; i < CoordRows - 1; i++)
        {
            delete [] Coord[i];
        }
        delete [] Coord;
        Coord = new int*[CoordRows];
        for (int i = 0; i < CoordRows; i++)
        {
            Coord[i] = new int[CoordCols];
            for (int j = 0; j < CoordCols; j++)
            {
                Coord[i][j] = holder[i][j]; // copy complete
            }
        }

        for (int i = 0; i < CoordRows; i++)
        {
            delete [] holder[i];
        }
        delete [] holder;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::addOther(const spr& other) // {7} give it another matrix, and it will add to update this obj
{
    if (this->SizeRows != other.SizeRows || this->SizeCols != other.SizeCols)
    {
        std::cout << " {7} addition not possible, dimensions must be same\n";
        return;
    }
    if (other.ElmsSparse == 0)
    {
        return; // addition complete...nothing to add
    }

    int sum = -9;
    bool added = false;
    for (int i = 1; i < other.CoordRows; i++) // only scan non-blank elements by scanning coord list
    {
        for (int x = 1; x < this->CoordRows; x++)
        {
            if (this->Coord[x][0] == other.Coord[i][0] && this->Coord[x][1] == other.Coord[i][1]) // same coords
            {
                sum = this->Coord[x][2] + other.Coord[i][2];
                set(this->Coord[x][0], other.Coord[i][1], sum); // rows and cols same, just set to update
                added = true;
            }
        }
        if (!added) // if match was not found, other element getting added to a blank
        {
            set(other.Coord[i][0], other.Coord[i][1], other.Coord[i][2]);
        }
        added = false;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::copyOther(const spr& other) // {8} overwrite other obj onto this obj, except Name
{
    this->copy(other);
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::wipe() // {9} make all elements blank     must come through set() or randBuild() after use
{
    if (ElmsSparse != 0) // no use wiping if it is already wiped
    {
        Mtx = new int*[SizeRows];
        for (int i = 0; i < SizeRows; i++)
        {
            Mtx[i] = new int[SizeCols];
            for (int j = 0; j < SizeCols; j++)
            {
                Mtx[i][j] = Blank;
            }
        }
        ElmsSparse = 0;
        for (int i = 0; i < CoordRows; i++)
        {
            delete [] Coord[i];
        }
        delete Coord;
        Coord = nullptr;
        CoordRows = 1;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::initialize() // {-5} helper to fill with blanks and get Coord list set  , assumes already deallocated 
{
    if (SizeRows == 0 || SizeCols == 0)
    {
        std::cout << "  {-5} matrix has no dimensions\n";
        return;
    }

    ElmsTotal = SizeCols * SizeRows;

    if (ElmsSparse > ElmsTotal)
    {
        std::cout << " {-5} can't have more sparse elements than total possible elements\n";
        return;
    }

    Mtx = new int*[SizeRows];
    for (int i = 0; i < SizeRows; i++)
    {
        Mtx[i] = new int[SizeCols];
        for (int j = 0; j < SizeCols; j++)
        {
            Mtx[i][j] = Blank;
        }
    }

    CoordRows = ElmsSparse + 1; // first row for # rows, # cols, and # ElmsSparse  need extra
    Coord = new int*[CoordRows];
    for (int i = 0; i < CoordRows; i++)
    {
        Coord[i] = new int[CoordCols];
        if (i == 0)
        {
            Coord[i][0] = SizeRows;
            Coord[i][1] = SizeCols;
            Coord[i][2] = ElmsSparse;
        }
        for (int j = 0; j < CoordCols; j++)
        {
            if (i != 0)
            {
                Coord[i][j] = Blank;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::clear() // {-4} helper to deallocate    the major possibilities are cover, could be more if more functions added
{
    if (ElmsSparse == 0) // don't have to deallocate Coord[][]
    {
        for (int i = 0; i < SizeRows; i++)
        {
            delete [] Mtx[i];
        }
        delete [] Mtx;
    
        Mtx = nullptr;
        Coord = nullptr; // should already be there
    }
    else
    {
        for (int i = 0; i < SizeRows; i++)
        {
            delete [] Mtx[i];
        }
        delete [] Mtx;
        Mtx = nullptr;

        for (int i = 0; i < CoordRows; i++)
        {
            delete [] this->Coord[i];
        }
        delete Coord;
        Coord = nullptr;
    }
    SizeRows = 0;
    SizeCols = 0; 
    ElmsTotal = 0;
    ElmsSparse = 0;
    CoordRows = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void spr::copy(const spr& other) // {-3} helper to make deep copy of other obj into this obj
{
    this->clear();
    this->SizeRows = other.SizeRows;
    this->SizeCols = other.SizeCols;
    this->ElmsTotal = other.ElmsTotal;
    this->ElmsSparse = other.ElmsSparse;
    this->CoordRows = other.CoordRows;
    
    this->Mtx = new int*[this->SizeRows];
    for (int i = 0; i < this->SizeRows; i++)
    {
        this->Mtx[i] = new int[this->SizeCols];
        for (int j = 0; j < this->SizeCols; j++)
        {
            this->Mtx[i][j] = other.Mtx[i][j];
        }
    }

    if (this->ElmsSparse > 0) // only need if non-blank elements present
    {
        this->Coord = new int*[this->CoordRows];
        for (int i = 0; i < this->CoordRows; i++)
        {
            this->Coord[i] = new int[this->CoordCols];
            for (int j = 0; j < this->CoordCols; j++)
            {
                this->Coord[i][j] = other.Coord[i][j];
            }
        }
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------
int spr::getRand(int min, int max) // {-2} helper to provide a random integer, given a min and max
{
    std::random_device rdevice{};                                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{min, max}; 
    return randomNum1(num1);
}

//--------------------------------------------------------------------------------------------------------------------------
spr::~spr() // {-1} destructor
{
    clear();
    std::cout << "\n  {-1}     deallocated: " << Name << std::endl;
}


//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================
#endif // sparse.h