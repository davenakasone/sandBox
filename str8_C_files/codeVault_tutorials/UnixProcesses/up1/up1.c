/*
    forking makes 2 different processes (everytime)
    everyitme fork() is called, the execution line is forked
        a child process is born and starts executing lines as well
        ID = 0 is child
        ID != 0 is main process
    each fork() returns a number as "int id"

    every process has process ID {linux, windows, any OS}
*/

#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <unistd.h>    // fork() {linux only}

void ex1();
void ex2();
void ex3();
void ex4(); // fork() n times, get 2^n processes
void ex5(); // only want 3 processes


int main(int argc, char *argv[]) 
{

    //ex1();
    //ex2();
    //ex3();
    //ex4();
    ex5();

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}


////~~~~ 2 processes execute same code once forked
void ex1()
{
    printf("\n%s() -->\n", __func__);
    fork();
    printf("\nfork() was called\n");
}


////~~~~ notice use of id
void ex2()
{
    printf("\n%s() -->\n", __func__);
    int id = -999;
    id = fork();    // everything after fork is executed once per process
    printf("\nfork() was called, id:  %d\n", id);
}

////~~~~ use ID to segregate
void ex3()
{
    printf("\n%s() -->\n", __func__);
    int id = -999;
    id = fork();    // everything after fork is executed once per process
    if (id == 0)
    {
        printf("\nthis is the child process because id == 0 >>>  id:  %d\n", id);
    }
    else
    {
       printf("\nthis is the parent process because id != 0 >>>  id:  %d\n", id); 
    }
}


////~~~~ 2 processes execute same code once forked ...fork() fork()
void ex4()
{
    printf("\n%s() -->\n", __func__);
    int id = -999;
    id = fork();
    id = fork();
    printf("\nfork() was called, id:  %d\n", id);
}


////~~~~ prevent extra process...3 processes
void ex5()
{
    printf("\n%s() -->\n", __func__);
    int id = -999;
    id = fork();
    if (id != 0)
    {
        id = fork(); // only fork main process, 3 proceeses total
    }
    printf("\nfork() was called, id:  %d\n", id);
}

////////~~~~~~~~END>  up1.c
