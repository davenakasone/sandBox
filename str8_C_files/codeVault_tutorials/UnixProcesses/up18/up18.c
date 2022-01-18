/*
    prevent process going to background ... ignores [ctrl]+[z]

    you have to be careful when you handle signals in your own way

    sigaction is an important struct and function

    signal is a good one too, but not portable

    SIGCONT is special, some signals you can't handle yourself

    run from terminal, hit [ctrl]+[z]
*/

#include <signal.h>      // kill(), signal(), SIGKILL, SIGTERM
#include <stdlib.h>      // NULL
#include <stdio.h>       // printf()
#include <sys/wait.h>    // wait()
#include <unistd.h>      // fork(), read(), write(), exec__ family, sleep()


void handle_sigtstp(int sig)    // change way to handle
{
    printf("stop denied\n");
}


void handle_sigcont(int sig)    // get prompt back
{
    printf("\ninput an integer: ");
    fflush(stdout); // immidate printing
}


int main(int argc, char *argv[]) 
{
    //   option 1  {portalbe}
    struct sigaction sa; // instantiate

    //sa.sa_handler = &handle_sigtstp;  // this is a function pointer
    sa.sa_handler = &handle_sigcont;    // this is a function pointer

    sa.sa_flags = SA_RESTART;    // for scanf

    // pick method of handling signal
    sigaction(SIGTSTP, &sa, NULL);    // 3rd parameter would be last
    //sigaction(SIGCONT, &sa, NULL);    // 3rd parameter would be last
    
   // option 2 {not gaurunteed, not portable, don't use}
   //signal(SIGTSTP, &handle_sigtstp);

    int x;
    printf("\ninput an integer: ");
    scanf("%d", &x); // program waits here  where to put SIGTSTP 
    printf("result %d * 5 = %d\n", x, x*5);
    
    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up18.c
