/*
    processes can talk with signals

    notice child does getppid()

    user defined signals are good choice...no use overriding kernel shit

    signals don't send data...just indicators

    don't do crazy shit with function handles, they are unpredicatable
    they should be atomic operations  ...simple 

    SA_RESTART doesn't appear to restart scanf() on mac's OSX
*/

#include <signal.h>    // SIGUSR1 , kill() , struct sigaction , SA_RESTART...
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>    // getppid()

#define INTinit -999

int result = INTinit; // global option

void handle_sigusr1(int sig)
{
    //printf("\n\tif you can't multiply, end your life...\n");

    // global option
        if (result == INTinit) // didn't actually change
        {
            printf("\n\tif you can't multiply, end your life...\n");
            printf("\ninput the correct answer:  %d\n");
        }
    //
}

int main(int argc, char * argv[])
{
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); exit(1);}

    if (pid == 0) // child
    {
        // waiting occurs in child, sends signal with "kill()"
        sleep(3);
        kill(getppid(), SIGUSR1); // needs handle , see sigaction in parent
    }
    else // parent
    {
        struct sigaction sa = { 0 }; // initialize
        sa.sa_flags = SA_RESTART; // restart scanf
        sa.sa_handler = &handle_sigusr1; // your function handle
        sigaction(SIGUSR1, &sa, NULL); // bind it, don't use old sig...NULL

        srand(time(NULL));
        int p1 = rand() % 10;
        int p2 = rand() % 10;
        //int result = INTinit;

        printf("\nwhat is %d x %d ?   >>> ", p1, p2);
        scanf("%d", &result);
        if (result == (p1*p2))
        {
            printf("your answer:  %d  ,  %d x %d = %d  , correct\n", 
                result, p1, p2, p1*p2);
        }
        else
        {
            printf("your answer:  %d  ,  %d x %d = %d  , wrong\n", 
                result, p1, p2, p1*p2);
        }
        wait(NULL);    // wait for child
    }

    if (pid != 0)
    {
        printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    }
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up19.c
