/*
    there is a difference between a thread and process
    both execute same code from fork()   ...may cause race
*/

#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <unistd.h>    // fork() {linux only}


void ex1(); // child does some, parent does some
void ex2(); // guaruntee order...wait() , order execution of proceeses

int main(int argc, char *argv[]) 
{
    //ex1();
    ex2();

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}


////~~~~ split work for parent and child
void ex1()
{
    printf("\n");
    int id = fork();
    int n = -999;
    
    if (id == 0)
    {
        n = 6;
    }
    else 
    {
        n = 1;
    }

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout); // so you can print when ready, not by buffer
    }
    printf("\n");
    // it is not predictable...order can be anything
}


////~~~~ split work for parent and child ... and wait()
void ex2()
{
    printf("\n");
    int id = fork();
    int n = -999;
    
    if (id == 0)
    {
        n = 1;
    }
    else 
    {
        n = 6;
    }

    if (id != 0) {wait(&id);} // wait for child to finish

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout); // so you can print when ready, not by buffer
    }
    // now need to wait for parent....join processess
}

////////~~~~~~~~END>  up2.c
