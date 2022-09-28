/*
    signals are for sending simple information

    an infinite loop...you'd have to go to htop and kill

    use that <signal.h>, call from parent to kill child

    signals are inpedendent of code, process must execute signal when received

    Linux has lots of signals, pick as needed, SIGTERM, SIGKILL, SIGSTOP, SIGCONT are good

    kill() just sends a signal...doesn't really kill stuff
    https://man7.org/linux/man-pages/man7/signal.7.html
    there are a lot of signals, depends what you want to do
*/

#include <signal.h>      // kill(), signal(), SIGKILL, SIGTERM
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
        while(1)
        {
            printf("in a loop...\n");
            sleep(1);
        }
    }
    else    // parent
    {
        sleep(3); // wait 3 seconds before kill
        kill(pid, SIGTERM); // signals don't depend on order
        printf("\n\tkilled:  %d\n", pid);
        wait(NULL);
    }
    
    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up15.c
