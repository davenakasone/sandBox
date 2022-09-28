/*
    polynomials usually are only uni-var 
    to use in a program, a matrix helps to represent

    p(x) = 3x^5 + 2x^4 + 5x^2 + 2x + 7       no coef...= 1,  no exp, x^0
    each term is coef and power of x
    x is just a variable

    coef  3   2   5   2   7
    exp   5   4   2   1   0         may also want terms (5 here) ...i'll use the max

    exp has to be integer, coef should be doubles
    if you don't want to track terms, just start from highest one

    keep this simple and use index of 1D matrix to be exp, elment val = coeffieicnt
    you can do a lot with this if you know math
*/

#ifndef H_poly
#define H_poly

#include "libs.h"

//==========================================================================================================================
//                                           ~ ~ ~ OBJ ~ ~ ~                                                              //
//==========================================================================================================================


class poly
{
    public:

        poly(int mDeg = 2, int tms = 3, std::string nm = "OBJ"); // {1} default constructor, will buildRand 
        poly(std::string fn, std::string nm = "OBJ");            // {2} constructor, builds from file
        poly(const poly& other, std::string nm = "COPY");        // {3} copy constructor
        void buildRand(int mDeg, int tms);                       // {4} build randomly
        void print();                                            // {5} print the polynomial
        void set(int exp, int coef); // {6} set coef at exp = 0 like deleting, anything else add or overwrite
        int getCoef(int exp); // {7} returns coefficient of term at specified exp
        void copyOther(const poly& other); // {8} give it other obj and it copies to this obj
        void addOther(const poly& other); // {9} give other obj, and it adds polynomials
        long long int calcVal(int x); // {10} knowing what value x is, you can find the answer

        ~poly();                                                 // {-1} destructor

    private:
        void initialize(int mDeg, int tms);   // {-4} allocate matrix and get obj set to parameters
        void clear();                         // {-3} put obj to initial state, deallocate matrix if needed
        int getRand(int min, int max);        // {-2} helper to get a random number

        int MaxDeg;              // highest degree exponent       .... size = MaxDeg + 1
        int Terms;               // how many non-zero terms it has
        int* Mtx = nullptr;     // array of coefficients and exponents ...exp's are the index of array,
        
        std::string Name;        // name obj
        std::string Dis;         // through away for input files
        const int SizeRows = 2;  // row for coeff, row for exp

        const int ValMin = -9;   // implictly exclude 0's if needed
        const int ValMax = 9;
};


//==========================================================================================================================
//                                           ~ ~ ~ IMP ~ ~ ~                                                              //
//==========================================================================================================================


//--------------------------------------------------------------------------------------------------------------------------
poly::poly(int mDeg, int tms, std::string nm) // {1} default constructor, will buildRand  or take input
{
    Name = nm;
    if (mDeg < 0)
    {
        std::cout << " {1} need at least x^0 term, using x^2 as highest term\n";
        mDeg = 2;
        tms = 3;
    }
    if (tms > mDeg + 1 || tms <= 0)
    {
        std::cout << " {1} can't have more terms than highest degree\n";
        std::cout << " {1} you want " << tms << " terms , but highest degree is " << mDeg << std::endl;
        std::cout << " {1} the there will be a max degree x^2, with 3 terms... x^2, x^1, x^0\n";
        mDeg = 2;
        tms = 3; 
    }
    Name = nm;
    buildRand(mDeg, tms);
}

//--------------------------------------------------------------------------------------------------------------------------
poly::poly(std::string fn, std::string nm) // {2} constructor, builds from file
{
    Name = nm;
    std::ifstream inFile;
    inFile.open(fn);
    if (!inFile)
    {
        std::cout << " {2} can't find file\n";
    }

    inFile >> Dis;
    inFile >> MaxDeg;
    inFile >> Dis;
    inFile >> Terms;

    if (Terms > MaxDeg + 1 || MaxDeg < 0 || Terms < 0)
    {
        std::cout << " {2} invlaid parameters\n";
    }  
    initialize(MaxDeg,Terms);
    inFile >> Dis;
    inFile >> Dis;
    for (int i = 0; i < MaxDeg + 1; i++)
    {
        inFile >> Mtx[i];
        inFile >> Dis;
    }
    inFile.close();
}

//--------------------------------------------------------------------------------------------------------------------------
poly::poly(const poly& other, std::string nm) // {3} copy constructor
{
    this->Name = nm;
    this->initialize(other.MaxDeg,other.Terms);
    for (int i = 0; i < this->MaxDeg + 1; i++)
    {
        this->Mtx[i] = other.Mtx[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void poly::buildRand(int mDeg, int tms) // {4} build randomly
{
    if (tms > mDeg + 1 || tms < 0 || mDeg < 0)
    {
        std::cout << " {4} not valid parameters to make a polynomial\n";
        return;
    }

    initialize(mDeg, tms);
    bool* used;
    used = new bool[MaxDeg + 1];
    for (int i = 0; i < MaxDeg + 1; i++)
    {
        used[i] = false;
    }
    int coef = -9;
    int exp = -9;
    again:
    coef = getRand(ValMin, ValMax);
    if (coef == 0)
    {
        goto again;
    }
    Mtx[MaxDeg] = coef;
    used[MaxDeg] = true;
    tms--;


    while (tms > 0)
    {
        coef = getRand(ValMin, ValMax);
        while (coef == 0)
        {
            coef = getRand(ValMin, ValMax); // excluding coefficients of 0
        }
        exp = getRand(0,MaxDeg);
        if (used[exp] == false) // if not already assigned a value
        {
            Mtx[exp] = coef;
            used[exp] = true;
            tms--;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void poly::print()                                           // {5} print the polynomial
{
    if (Terms == 0)
    {
        std::cout << "polynomial is empty\n";
        return;
    }
    bool first = true;
    std::cout << "\t\tpolynomial:  ";
    for (int i = MaxDeg; i >= 0; i--)
    {
        if (Mtx[i] != 0)
        {
            if (Mtx[i] > 0 && !first)
            {
                std::cout << " + " << Mtx[i] << " x^" << i << "  ";
            }
            else if (first && Mtx[i] > 0)
            {
                std::cout << Mtx[i] << " x^" << i << "  ";
                first = false;
            }
            else if (first && Mtx[i] < 0)
            {
                std::cout << Mtx[i] << " x^" << i << "  ";
                first = false;
            }
            else
            {
                std::cout << Mtx[i] << " x^" << i << "  "; 
            }
        }
    }
    std::cout << " highest degree: " << MaxDeg << " , terms: " << Terms << "   " << Name << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------
void poly::set(int exp, int coef) // {6} set coef at exp = 0 like deleting, anything else add or overwrite
{
    if (exp < 0 || exp > MaxDeg)
    {
        std::cout << " {6} term with degree " << exp << " not in range\n";
        return;
    }
    Mtx[exp] = coef;
    if (coef == 0)
    {
        Terms--;
        int maxD = 0;
        for (int i = MaxDeg; i >= 0; i--)
        {
            if (Mtx[i] != 0)
            {
                maxD = i;
                goto foundMax;
            }
        }
        foundMax:
        MaxDeg = maxD;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int poly::getCoef(int exp) // {7} returns coefficient of term at specified exp
{
    if (exp < 0 || exp > MaxDeg)
    {
        return 0; // not in range, but technically zero
    }
    else
    {
        return Mtx[exp];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void poly::copyOther(const poly& other) // {8} give it other obj and it copies to this obj
{
    this->initialize(other.MaxDeg,other.Terms);
    for (int i = 0; i < this->MaxDeg + 1; i++)
    {
        this->Mtx[i] = other.Mtx[i];
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void poly::addOther(const poly& other) // {9} give other obj, and it adds polynomials
{
    int newTerms = 0;
    if (this->MaxDeg >= other.MaxDeg) // no need to resize
    {
        for (int i = 0; i <= this->MaxDeg; i++)
        {
            if (i <= other.MaxDeg && other.Terms != 0)
            {
                if (this->Mtx[i] != 0 || other.Mtx[i] != 0)
                {
                    newTerms++;
                    this->Mtx[i] = this->Mtx[i] + other.Mtx[i];
                }
            }
            else
            {
                if (this->Mtx[i] != 0)
                {
                    newTerms++;
                }
            }
        }
        this->Terms = newTerms; 
    }
    else // other.MaxDeg > this->MaxDeg , must resize this obj
    {
        int* temp;
        temp = new int[other.MaxDeg + 1];
        for (int i = 0; i <= other.MaxDeg; i++)
        {
            temp[i] = 0; // intitialize
        }
        for (int i = 0; i <= this->MaxDeg; i++)
        {
            temp[i] = this->Mtx[i]; // copy what you can
        }
        for (int i = 0; i <= other.MaxDeg; i++)
        {
            if (temp[i] != 0 || other.Mtx[i] != 0)
            {
                newTerms++;
            }
        }
        initialize(other.MaxDeg,newTerms);
        for (int i = 0; i <= this->MaxDeg; i++)
        {
            this->Mtx[i] = temp[i] + other.Mtx[i];
        }
        delete [] temp;
        temp = nullptr;
        std::cout << "\nnewTerms: " << newTerms << "\n";
    }

    if (this->Mtx[MaxDeg] == 0) // in case you got 3x^6 + -3x^6   update MaxDeg
    {
        int newMaxD = 0;
        for (int i = 0; i <= MaxDeg; i++)
        {
            if (Mtx[i] != 0)
            {
                newMaxD = i; // left at highest
            }
        }
        this->MaxDeg = newMaxD;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
long long int poly::calcVal(int x) // {10} knowing what value x is, you can find the answer
{
    if (Terms == 0)
    {
        std::cout << "there is nothing in the equation\n";
        return 0; // empty equation
    }
    long long int answer = 0;
    for (int i = 0; i <= MaxDeg; i++)
    {
        answer = answer +  (Mtx[i] * std::pow(x,i) );
    }
    return answer;
    
}

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
void poly::initialize(int mDeg, int tms) // {-4} allocate matrix and get obj set to parameters   check params before calling
{
    clear();
    MaxDeg = mDeg;
    Terms = tms;
    Mtx = new int[MaxDeg + 1];
    for (int i = 0; i < MaxDeg + 1; i++)
    {
        Mtx[i] = 0;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void poly::clear() // {-3} put obj to initial state, deallocate matrix if needed
{
    if (Mtx != nullptr)
    {
        delete [] Mtx;
        Mtx = nullptr;
    }
    MaxDeg = 0;
    Terms = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
int poly::getRand (int min, int max) // {-2} helper to get a random number
{
    std::random_device rdevice{};
    std::default_random_engine num1{rdevice()};
    std::uniform_int_distribution<int> randomNum1{min, max};
    return randomNum1(num1);
}

//--------------------------------------------------------------------------------------------------------------------------
poly::~poly() // {-1} destructor
{
    clear();
    std::cout << "\n  {-1} deallocated: " << Name << std::endl;
}


//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================
#endif // poly.h