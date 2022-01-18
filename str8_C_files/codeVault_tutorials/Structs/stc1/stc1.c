/*
    typedef is ok
    use it on existing data types or user defined

    get around the need to prefix with data type
        alias
*/

#include <stdlib.h>
#include <stdio.h>

void ex1();
void ex2();
void ex3();

int main (int argc, char* argv[], char* envp[])
{
    //ex1();
    //ex2();
    ex3();

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


void ex1()
{
    printf("\n%s()  ,  typedef...\n", __func__);
    typedef unsigned long long int myUINT64;
    myUINT64 test = 5;
    printf("\n%s()  ,  type def unsinged long long:  %llu\n",
        __func__, test);
}


void ex2()
{
    printf("\n%s()  ,  typedef a struct...\n", __func__);

    typedef struct
    {
        double x;
        double y;
    } exp;
    
    exp myExp;

    double d1 = 1;
    double d2 = 3;

    myExp.x = d1/d2;
    myExp.y = (2*d1)/d2;

    printf("\n%s()  ,  x =  %0.9lf  ,  y =  %0.9lf\n",
        __func__, myExp.x, myExp.y);
    
    // there are a lot of ways to do this
}


void ex3()
{
    typedef struct peep
    {
        int per1;
        int per2;
        int per3;
    } peep;

    peep myPeep;
    myPeep.per1 = 1;
    myPeep.per2 = 2;
    myPeep.per3 = 3;

    printf("\n%s()  ,  %d  ,  %d  ,  %d\n", 
        __func__, myPeep.per1, myPeep.per2, myPeep.per3);
}

////////~~~~~~~~END>  stc1.c
