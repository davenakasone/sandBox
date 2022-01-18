/*
    make wrapper to pass function pointer as an argument

    and/or

    return function pointer as an argument
*/

#include <stdlib.h>
#include <stdio.h>

#define pass_function_pointer_as_arg 221    ////~~~~{on|off}
#define return_function_pointer 222         ////~~~~{on|off}

void fun1(){printf("\n\t%s() called\n", __func__);}
void fun2(){printf("\n\t%s() called\n", __func__);}
void wrapper(void (*func)()) {printf("\n\t%s() called\n", __func__); func();}
void* returnFP() {printf("\n\t%s() called\n", __func__); return fun1;}


int main(int argc, char* argv[], char* envp[])
{
    #ifdef pass_function_pointer_as_arg
        printf("\npass function pointer as argument:\n");
        wrapper(fun1);
        wrapper(fun2);
    #endif

    #ifdef return_function_pointer
        printf("\n************************************************\n");
        printf("\nreturn function pointer from function call:\n");
        void (*fp)();
        fp = returnFP();
        wrapper(fp);
    #endif

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ \n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  fp3.c
