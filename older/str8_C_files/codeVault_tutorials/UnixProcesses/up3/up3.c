/*
    if parent process finishes before child, new ID issued
    don't make zombies...zombies should have been killed, but are still living
    memory is copied, each process gets own allocation
        control execution by "id"
*/

#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <sys/wait.h>  // process ID control
#include <unistd.h>    // fork() {linux only}

void ex1(); // process with ID == 0 launches all, every process has an ID
void ex2(); // get a zombie...no sig kill, must wait, parent done before child

int main(int argc, char *argv[]) 
{
    //ex1();
    ex2();

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}


////~~~~ prcoccess ID
void ex1()
{
    int id = fork();
    printf("current: %d  ,  parent:  %d\n", getpid(), getppid());
}


////~~~~ should always wait for child before finishing parent
void ex2()
{
    int id = fork();
    if (id == 0)
    {
        sleep(1); // child waits
    }
    printf("current ID:  %d  ,  parent ID:  %d\n", getpid(), getppid());

    int result = -999;
    result = wait(NULL);
    if (result == -1)
    {
        printf("no child process to wait for\n"); // -1 , nothing to wait for
    }
    else
    {
        printf("%d  ,  finished execution\n", result);
    }
}

////////~~~~~~~~END>  up3.c
