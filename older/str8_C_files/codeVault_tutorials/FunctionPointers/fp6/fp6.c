/*
    general use of function pointers
*/

#include <stdlib.h>
#include <stdio.h>

#define INIT_INT -999
#define X_INT 3
#define Y_INT 5

int addIntegers(int x, int y) {return (x+y);}
void ex1(); // basic function pointer
void ex2(); // pass pointer to another function
int addInts( int (*funP)(int, int), int x, int y ) {return (*funP)(x, y);}

int main(int argc, char* argv[], char* envp[])
{
    //ex1();
    ex2();

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


void ex1()
{
    printf("\n%s()  ,  function pointer passes args and returns value:\n", __func__);
    int (*funPtr)(int, int); // function pointer, arg: (int, int), returns int
    funPtr = &addIntegers;
    int sum = (*funPtr)(X_INT, Y_INT); // call to add with args
    printf("\n\t%s()  ,  %d  +  %d  =  %d\n", 
        __func__, X_INT, Y_INT, sum);
}


void ex2()
{
    printf("\n%s()  ,  function pointer passed to another function:\n", __func__);
    int (*funPtr)(int, int); // function pointer, arg: (int, int), returns int
    int sum = addInts(funPtr, X_INT, Y_INT);
    printf("\n\t%s()  ,  %d  +  %d  =  %d\n", 
        __func__, X_INT, Y_INT, sum);
}

////////~~~~~~~~END>  fp6.c
