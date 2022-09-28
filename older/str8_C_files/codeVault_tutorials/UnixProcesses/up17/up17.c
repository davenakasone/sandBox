/*
    put process in background and bring to foreground

    putting a process in background is stoping it  == [ctrl]+[z]
    then do SIGCONT in program or "fg" in terminal

    stop != terminated   ...execution not done, memory not free
    background process are per terminal session... if more, fg<id>  "job"

    fyi VScode uses GDB
    fg can have id specified or "job"
*/

#include <signal.h>      // kill(), signal(), SIGKILL, SIGTERM
#include <stdlib.h>      // NULL
#include <stdio.h>       // printf()
#include <sys/wait.h>    // wait()
#include <unistd.h>      // fork(), read(), write(), exec__ family, sleep(), usleep()


int main(int argc, char *argv[]) 
{
    int x = -999;
    printf("\ninput an integer: ");
    scanf("%d", &x); // program waits here  where to put SIGTSTP, like SIGSTOP
    // program comes back to foreground "SIGCONT", process restarts...fg in terminal
    printf("result %d * 5 = %d\n", x, x*5);
    
    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up17.c
