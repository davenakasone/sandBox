/*
    control child process by parent
    ...stop and continue process

    a better name the kill() could be used,
        but all it does is send a signal to the process
*/

#include <signal.h>      // kill(), signal(), SIGKILL, SIGTERM, SIGSTOP, SIGCONT
#include <stdlib.h>      // NULL
#include <stdio.h>       // printf()
#include <sys/wait.h>    // wait()
#include <unistd.h>      // fork(), read(), write(), exec__ family, sleep()


int main(int argc, char *argv[]) 
{
    printf("\n");
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); exit(1);}

    if (pid == 0)    // child
    {
        while(1)    // a listener for some request
        {
            printf("in a loop...\n");
            sleep(1);
        }
    }
    else // parent
    {
        //kill(pid, SIGSTOP); // no printing allowed, stopped immidiatley
        //sleep(1);
        //kill(pid, SIGCONT); // start again

        kill(pid, SIGSTOP);    // stop first, so it is not printing
        int tim = -999;

        do    // at least one execution to listen
        {
            printf("enter execution time: ");
            scanf("%d", &tim);
            if (tim > 0)
            {
                kill(pid, SIGCONT);
                sleep((unsigned int)tim);
                kill(pid, SIGSTOP);
            }
        } while (tim > 0);    // so enter negative integer to exit
        
        kill(pid, SIGTERM);       // signals don't depend on order
        printf("\n\tkilled:  %d\n", pid);
        wait(NULL);
    }
    
    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS; // this is a status code ... not 0 = error
}

////////~~~~~~~~END>  up16.c
