/*
    you can make any recursive function a loop...or any loop to recursive
*/
#include <cmath>
#include <iostream>

const int N = std::pow(2,5);     // make it easy and use power of 2   keep under integer range
int REP = 0;                     // reset to 0 when needed
int RECUR = 95;                   // have to adjust depending on function you want to call

void o_n();                      // O(n) demo
void o_n_2();                    // O(n^2) demo
void o_n_3();                    // O(n^3) demo
void o_logn();                   // O(logn) demo
void recur1(int n);              // basic recusion demo
void print_call(int n);          // print then call self    TAIL   call is last
void call_print(int n);          // call self then print    HEAD   call is first
void recur2(int n);              // ascend and decend   see both phases
int recur_no_static(int n);      // nothing out of the ordinary, no static vars
int recur_with_static(int n);    // static changes output
void tree_recur(int n);          // TREE calls self more than 1 time   can't finish next until predecesor finished
void indirect_A(int n);
void indirect_B(int n);
int recur_nested(int n);          // use RECUR = 95     returns 91 w 13 calls
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    /*
    o_n();
    o_n_2();
    o_n_3();
    o_logn();

    recur1(RECUR);
    std::cout << "\nrecur1() called itself " << REP + 1 << " times\n\n"; // count 1 extra for termination call
    REP = 0;

    print_call(RECUR);          // call has to finish to do anything past that...see the difference
    std::cout << std::endl;
    call_print(RECUR);
    std::cout << std::endl;
    REP = 0;

    recur2(RECUR);
    
    std::cout << "\nrecur_no_static( " << RECUR << " ) = " << recur_no_static(RECUR) << std::endl;
    std::cout << "\nrecur_with_static( " << RECUR << " ) = " << recur_with_static(RECUR) << std::endl;
    
    std::cout << "\nthe tree recursion, tree_recur(" << RECUR << ")  =  ";
    tree_recur(RECUR);
    std::cout << "\n    took " << REP << " calls\n";   //  sum of gpc series 2^0 + 2^1 + ... + 2^n
    REP = 0;

    std::cout << "\nindirect_A(" << RECUR << ")  cycle: ";
    indirect_A(RECUR);
    std::cout << "\n    took " << REP << " calls\n";   //  calls between A & B
    REP = 0;
    */
    int result = -1;
    result = recur_nested(RECUR);
    std::cout << "\nrecur_nested(" << RECUR << ") = " << result << "  , took " << REP << " calls\n";
    REP = 0;

    std::cout << "\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void o_n()
{
    int arr[N]; // technically 1 unit of time here
    for (int i = 0; i < N; i++) // technically 3 units of time here and lots of assembly operations
    {
        arr[i] = 9;
        REP++;               // only rep that matters
    }
    std::cout << "\nsize of  n = [ " << N << " ] , took < " << REP << " > reps , expected O(n) = " << N << std::endl;
    REP = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void o_n_2()
{
    int arr[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = 9;
            REP++;
        }
    }
    std::cout << "\nsize of  n = [ " << N*N << " ] , took < " << REP << " > reps , expected O(n^2) = " << N*N << std::endl;
    REP = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void o_n_3()
{
    int arr[N][N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                arr[i][j][k] = 9;
                REP++;
            }
        }
    }
    std::cout << "\nsize of  n = [ " << N*N*N << " ] , took < " << REP << " > reps , expected O(n^3) = " << N*N*N << std::endl;
    REP = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void o_logn()
{
    int arr[N];
    for (int i = 1; i < N; i = i * 2)     // or (i = N; i > 1; i = i / 2)
    {
        arr[i] = 9;
        REP++;
    }
    std::cout << "\nsize of  n = [ " << N << " ] , took < " << REP << " > reps , expected O(log_2 n ) = " << std::log2(N) << std::endl;
    REP = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void recur1(int n)
{
    if (n > 0)
    {
        REP++;
        recur1(n-1);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void print_call(int n)
{
    if (n > 0)
    {
        std::cout << "TAIL print_call()  call " << n  << std::endl;  
        print_call(n-1); // TAIL  call is last statement
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void call_print(int n)
{
    if (n > 0)
    {
        call_print(n-1); // HEAD   no operations before function call
        std::cout << "HEAD call_print()  call " << n  << std::endl; // printing done at returning time
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void recur2(int n)
{
    if (n > 0)
    {
        std::cout << "recur2() Decending " << n << std::endl;
        recur2(n-1);
        std::cout << "recur2() Ascending " << n << std::endl;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int recur_no_static(int n)
{
    REP++;
    if (n > 0)
    {
        return ( recur_no_static(n - 1) + n );
    }
    return 0;
/*

    fun(5) = ?                           fun(5) = 15 returned
    fun(4) + __          10 + 5 = 15
    fun(3) + __          6 + 4 = 10
    fun(2) + __          3 + 3 = 6
    fun(1) + __          1 + 2 = 3
    fun(0) + __          0 + 1 = 1
       0  xxx

*/
}

//--------------------------------------------------------------------------------------------------------------------------
int recur_with_static(int n)
{
    static int x = 0; // remains same       even globals or outside vars do the same...every call uses same copy
    if (n > 0)
    {
        x++;
        return (recur_with_static(n - 1) + x);
    }
    return 0;
/*
    fun(5) , x = 1      20 + 5 = 25 = fun(5)     how to handle statics...just keep const
    fun(4) , x = 2      15 + 5 = 20
    fun(3) , x = 3      10 + 5 = 15
    fun(4) , x = 4      5 + 5 = 10
    fun(5) , x = 5      0 + 5 = 5
    return 0 ...x = 5
*/
}

//--------------------------------------------------------------------------------------------------------------------------
void tree_recur(int n)
{
    REP++;
    if (n > 0)
    {
        std::cout << n << "  ";
        tree_recur(n-1);
        tree_recur(n-1);
    }
/*

    fun(3) passed   15 calls made and deleted  it's a big tree
    prints n = 3, calls fun(2), will call when first done     << 3
    prints n = 2, calls fun(1), will call when first done     << 2
    prints n = 1, calls fun(0), will call when first done     << 1
    n = 0, first call complete   4 activation records, 4 calls, back to previous call
    fun(0) created again, still stack size of 4, fails and deletes record
    fun(1), n = 1       << 1
    fun(0)  ends
    fun(0) ends
    fun(1) ends
    fun(2) also goes through all << 2
    goes to x2 fun(1)   << 1  << 1           { 3, 2, 1, 1, 2, 1, 1 }
*/
}

//--------------------------------------------------------------------------------------------------------------------------
void indirect_A(int n)
{
    REP++;
    if (n > 0)
    {
        std::cout << "indirect_A, n = " << n << " , ";
        indirect_B(n-1);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void indirect_B(int n)
{
    REP++;
    if (n > 1)
    {
        std::cout << "indirect_B, n = " << n << " , ";
        indirect_A(n/2);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int recur_nested(int n)
{
    REP++;
    if(n > 100)
    {
        return n - 10;
    }
    else
    {
        return recur_nested(recur_nested(n+11));
    }
}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================
