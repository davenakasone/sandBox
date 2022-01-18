/*
    be able to execute in parallel
    need at least 2 processes

    exit status tells you if process was successful
    - ping program not found
    - ping not executed successfully
    execlp() only runs function if possible
*/

#include <stdlib.h>
#include <stdio.h>     // printf()
#include <sys/wait.h>
#include <unistd.h>    // fork() {linux only}  ...read(), write(), exec__ family


int main(int argc, char *argv[]) 
{
    printf("\n");
    int status = -999;
    int pid = fork();
    if (pid == -1) {printf("fork failure\n"); exit(1);}

    if (pid == 0) // child
    {
        // change comment to see error
        status = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        //status = execlp("pingg", "ping", "-c", "3", "google.com", NULL); // can't find
        //status = execlp("ping", "ping", "-c", "3", "google.con", NULL); // can't execute
        if (status == -1){printf("could not find program to execute\n"); exit(2);}
    }
    else
    {
        //wait(NULL); // just waiting for all children to finish
        wait(&status); // it takes an int pointer...macros for status
        if (WIFEXITED(status)) // if true, it finished execution normally
        {
            int statusCode = WEXITSTATUS(status);    // value it exited with
            if (statusCode == 0)
            {
                printf("\ngood ping\n");
            }
            else
            {
                printf("no execution\n");
            }
            printf("status:  %d\n", statusCode);
        }
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return 0; // this is a status code ... not 0 = error
}

////////~~~~~~~~END>  up12.c
