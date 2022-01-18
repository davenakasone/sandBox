/*
    control the ID, still a memory copy

    1 fork

    [process , id = x]
    [process , id = 0]

    2 fork , make one parent of all, the rest can inheret

    [process id1 = x, id2 = z]
    {x} [process id1 = 0, id2 = y]  {z} [process id1 = x, id2 = 0]
    {y} [process id1 = 0, id2 = 0]

    ...always 1 parent
    don't be a retard and create forks in loop ; 2^n every fork
    must be able to distinguish each process...use a tree/leaf

    child should terminate before parent [sigkill won't work...it's a zombie, memory leak]
    a new parent will get assinged or something unpredictable 
        wait for child to finish before terminating main process...
*/

#include <errno.h>  // ECHILD
#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <sys/wait.h>  // process ID control    wait()...but use wait(NULL);
#include <unistd.h>    // fork() {linux only}


int main(int argc, char *argv[]) 
{
    printf("\n");
    int id1 = fork();
    int id2 = fork();

    if (id1 != 0 && id2 != 0)
    {
        printf("[x]  parent of all,  id1 = %d  ,  id2 = %d\n", id1, id2);
    }
    if (id1 == 0 && id2 != 0)
    {
        printf("[z]  child of parent --> parent of a child,  id1 = %d  ,  id2 = %d\n", id1, id2);
    }
    if (id1 != 0 && id2 == 0)
    {
        printf("[x]  parent --> child of parent,  id1 = %d  ,  id2 = %d\n", id1, id2);
    }
    if (id1 == 0 && id2 == 0)
    {
        printf("[y]  child of child,  id1 = %d  ,  id2 = %d\n", id1, id2);
    }

    // only waits for 1...put in loop 
    while(wait(NULL) != -1 || errno != ECHILD)
    {
        printf("waited for a child to finish\n"); // should seee 3 prints (3 children to wait)
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up5.c
