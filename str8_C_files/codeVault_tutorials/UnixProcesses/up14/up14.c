/*
    scripts != programs
    grep in Linux lets you filter output

    >ping -c 1 google.com | grep "stddev"
    can do same with exec__ but exec does not use bash script
    exec__ is simple execuatable , no BASH interpreter

    | operator is for BASH only
    you are executing execuatable files, not BASH script

    need pipe to simulate | operator
    exec__() is for executable files, not script
*/

#include <stdlib.h>      // NULL
#include <stdio.h>       // printf()
#include <sys/wait.h>    // wait()
#include <unistd.h>      // fork() {linux only}  ...read(), write(), exec__ family


int main(int argc, char *argv[]) 
{
    printf("\n");
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); exit(1);}

    if (pid == 0) // child
    {
        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        //int err = execlp("ping", "ping", "-c", "1", "google.com", "|", "grep", "stddev", NULL); // wrong
        if (err == -1) {printf("exec__ error\n"); exit(2);}
    }
    else // parent
    {
        int waitStatus;
        wait(&waitStatus);
        if (WIFEXITED(waitStatus))
        {
            int statusCode = WEXITSTATUS(waitStatus);
            if (statusCode == 0)
            {
                printf("success:  %d\n", statusCode);
            }
            else
            {
                printf("failure:  %d\n", statusCode);
            }
        }
    }
    
    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up14.c
