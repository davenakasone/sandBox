/*
    manage multiple pipes
    you should know what is going on

    [process main]
    [process child]  --> [process main, child]
                         x[process child, child]
    
    3x process, 2 forks()   ...just add 5 to check
    pipes are unidirectional, link between 2 process...need 3

             p1, fd[0][1] ...writes   fd[2][0]...reads
           / _  \
reads, fd[0][0] ;p2     p3   fd[2][1]  writes
           fd[1][1]    fd[1][0] reads
    that means 6 fd's , includes read/write end
    child inherets the 6 fd's, 18 fds...you don't want them to dangle

    you should be able to generalize this
    n processes...n pipes
               ... nodes n forks  n-1

    could also kill sub parent...SIGTERM
*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define PIPES 3
#define ENDS 2


int main( int argc, char* argv[])
{
    printf("\n");
    int fd[PIPES][ENDS];
    for (int i = 0; i < PIPES; i++)    // open pipes on parent
    {
        if (pipe(fd[i]) <0) { printf("pipe %d error\n", i); exit(i); }
    }

    int og;
    int pid[ENDS];
    for (int i = 0; i < ENDS; i++) // make process
    {
        pid[i] = fork();
        if (pid[i] < 0) {printf("fork %d error\n", i); exit(i);}
        if (i == 0 && pid[i] != 0) { og = pid[i];} // get total parent
    }

    if (pid[0] == 0)
    {
        close(fd[0][1]); // won't write here 
        close(fd[1][0]); // won't read here
        close(fd[2][0]); // don't need 3rd pipe
        close(fd[2][1]); // don't need 3rd pipe

        int x = -999;
        if (read(fd[0][0], &x, sizeof(int)) < 0) {printf("read pipe 0  error\n"); exit(-1);}
        printf("\n\tchild1, read, x = %d\n", x);
        x = x + 5;
        if (write(fd[1][1], &x, sizeof(int)) < 0) {printf("write pipe 1 error\n"); exit(-2);}
        printf("\n\tchild1, write, x = %d\n", x);
        close(fd[0][0]);
        close(fd[1][1]);
        return 0; // don't want anymore execution
    }

    if (pid[1] == 0)
    {
        close(fd[0][0]); // don't need
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int x = -999;
        if (read(fd[1][0], &x, sizeof(int)) < 0) {printf("read pipe 1 error\n"); exit(-3);}
        printf("\n\tchild2, read, x = %d\n", x);
        x = x + 5;
        if (write(fd[2][1], &x, sizeof(int)) < 0) {printf("write pipe 3 error\n"); exit(-4);}
        printf("\n\tchild2, write, x = %d\n", x);
        close(fd[1][0]);
        close(fd[2][1]);
        return 0; // must stop execution
    }
    
    if (og) // total parent only ...other parent can die
    {
        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][1]);

        int x = 0;
        printf("\n\tenter an integer:  ");
        scanf("%d", &x);

        printf("\n\tparent, start, x = %d\n", x);
        
        if(write(fd[0][1], &x, sizeof(int)) < 0) {printf("write pipe 0 error\n"); exit(-5);}
        if(read(fd[2][0], &x, sizeof(int)) < 0) {printf("read pipe 3 error\n"); exit(-6);}
        printf("\n\tparent, final, x = %d\n", x);
        
        close(fd[0][1]);
        close(fd[2][0]);
        waitpid(pid[0], NULL, 0);
        waitpid(pid[1], NULL, 0);
        
        kill(pid[1], SIGTERM);
        printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    }
    return 0;
}

////~~~~END>  up23.c
