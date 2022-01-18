/*
    most processes need to communicate between them
    ...might not want to just copy memory over
        that is what pipes are for, an in-memory file
            a file that only has a buffer saved in memory, and you can read/write from it
    
    make pipe control flow of process
    always comes with 2 fd's...your keys to each end of the pipe
    fd's are independent of each other in different processes, 
        open and close in each process
*/

#include <errno.h>  // ECHILD
#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <sys/wait.h>  // process ID control
#include <unistd.h>    // fork() {linux only}  ...read(), write(), 

void ex1(); // fork, fork ... control ID


int main(int argc, char *argv[]) 
{
    printf("\n");
    int result = -999;
    int fd[2]; // keys to pipe ... has 2 ends   fd[0] = read, fd[1] = write
    if (pipe(fd) != 0) // takes the file descriptors...where to read and right
    {
        printf("could not open pipe\n");
    }
    int id = fork(); // file descriptors will be inhereted, not just assigned
    if (id == -1) {printf("error with fork\n");}
    if (id == 0)
    {
        close(fd[0]); // also have to manage own pipe ends...never need to read
        int x = -999;
        printf("input a number: ");
        scanf("%d", &x);
        result = write(fd[1], &x, sizeof(int));
        if (result == -1)
        {
            printf("error while writing\n");
        }
        close(fd[1]);
        printf("child has:  %d\n", x);
    }
    else
    {
        close(fd[1]); // don't have to write
        int y = -999;
        result = read(fd[0], &y, sizeof(int));
        if (result == -1)
        {
            printf("error while reading\n");
        }
        close(fd[0]);
        printf("child gave parent:  %d", y);
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up6.c
