/*
    basic function pointer
*/

#include <stdlib.h>
#include <stdio.h>

#define GET_NAME(var) #var

void ex_A();
void ex_B(); // removed '&' ...functions name gives address also
void fun( int A);


int main(int argc, char* argv[], char* envp[])
{
    //ex_A();
    ex_B();

    printf("\n\n\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


void ex_A()
{
    void (*fun_ptr)(int); // a function pointer to a function with int arg
    fun_ptr = &fun;      // fun_ptr is pointer to function "funA()"
    (*fun_ptr)(10);       // invoke it
}


void ex_B()
{
    void (*fun_ptr)(int); // a function pointer to a function with int arg
    fun_ptr = fun;        // name of function gives address...
    (*fun_ptr)(10);       // invoke it
}


void fun(int A)
{
    printf("\n\t%s()  ,  value of %s :  %d",
        __func__, GET_NAME(A), A);
}

////////~~~~~~~~END>  fp1.c
