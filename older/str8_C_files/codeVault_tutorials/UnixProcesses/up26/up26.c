/*
    multiple forks have to be managed correctly

    {main process}
        {sub1}
            {sub2}
                ...
                    {subn} 

    fork() and pipe() until you have process you want
    n processes, n+1 pipes ... one process is main()

    make a standard for which process uses which
    each pipe has a read and write end

     0   1   2   3     pipe index
    |r| |r| |r| |r|
    |w| |w| |w| |w|

    main reads from last and writes to first
    each process should close other pipes

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PROCESSES 3

int main(int argc, char * argv[], char * envp[])
{
    int og;
    int pipes[PROCESSES + 1][2];
    for (int i = 0; i < PROCESSES+1; i++)
    {
        if(pipe(pipes[i]) == -1) {printf("error with pipe  %d\n", i); exit(i);}
    }

    int pids[PROCESSES];
    for (int i = 0; i < PROCESSES; i++)
    {
        pids[i] = fork(); // be careful ... 2^n every time
        if (i == 0 && pids[i] != 0) {og = pids[i];}
        if (pids[i] == -1) {printf("error fork %d\n", i); exit(i*-1);}
        if (pids[i] == 0)
        {
            for (int j = 0; j < PROCESSES+1; j++)
            {
                if(i != j)
                {
                    close(pipes[j][0]); // close all other write ends
                }
                if ((i+1) != j)
                {
                    close(pipes[j][1]); // close all other write ends
                }
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) {printf("read error\n"); exit(22);}
            printf("read  ,  process %d  ,  x = %d\n", i, x);
            x++;
            if (write(pipes[i+1][1], &x, sizeof(int)) == -1) {printf("write error\n"); exit(33);}
            printf("write  ,  process %d  ,  x = %d\n", i, x);
            close(pipes[i][0]);
            close(pipes[i+1][1]);
            return 0; // 
            //break; //ok
        }
    }

    if (og)
    {
        for (int i = 0; i < PROCESSES+1; i++)
        {
            if (i != PROCESSES)
            {
                close(pipes[i][0]); // only need to read last pipe
            }
            if (i != 0)
            {
                close(pipes[i][1]); // only need to write pipe index 0
            }
        }
        int y = 5;
        if (write(pipes[0][1], &y, sizeof(int)) == -1) {printf("write error\n"); exit(9);}
        printf("write  ,  main  ,  y = %d\n", y);
        if (read(pipes[PROCESSES][0], &y, sizeof(int)) == -1) {printf("read error\n"); exit(8);}
        printf("read  ,  main  ,  y = %d\n", y);
        close(pipes[0][1]);
        close(pipes[PROCESSES][0]);

        for (int i = 0; i < PROCESSES; i++)
        {
            wait(NULL); // wait it out here, all children finish
        }
        printf("\n\n\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    }

    return EXIT_SUCCESS;
}

////~~~~END>  up26.c
