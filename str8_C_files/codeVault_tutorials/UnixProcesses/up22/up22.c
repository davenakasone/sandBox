/*
    simulate the pipe operator "|"     dup and manage pipe ends
    ...script is not program 
        and exec__ family doesn't run BASH script
    
    >ping -c 3 google.com | grep stddev      not same as if in command line
        you are trying to move output of 1st command and use as input for second
            there are 2 programs being executed, linked by pipe operator
    
    it is basically a pipe with 2 ends, routed in a certain way
    [stdout] of "ping" --> | --> [stdin, set on stdin] 

    you do with in C by implementing processes
    {main process} fork--> {ping}
                           {grep}       need 3
        trick is pipe made by main process, info flows ping->grep

    execlp() is good at lauching linux commands...but it replaces everything
    dup2() will make 2 file descriptors that point to same place
        in this case, 2 fd's point to same pipe
    
    waitpid() because more than 1 process to wait for

    ...grep keeps reading (from pipe...has to know when to stop)
    all the writers to pipe must be closed {any process}
    fd's get inhereted when you call fork()
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int main( int argc, char* argv[])
{
    int fd[2];
    if (pipe(fd) == -1) {printf("pipe error\n"); exit(1);}
    int pid1 = fork();
    if (pid1 < 0) {printf("fork1 error\n"); exit(2);}
    int track;
    if (pid1 != 0) { track = pid1; }

    if (pid1 == 0) // child 1, where all the special activity is
    {
        dup2(fd[1], STDOUT_FILENO); // reroute  write-->STDOUT...creates new fd
        close(fd[0]); // not used, only want to write
        close(fd[1]); // remains open, even though rerouted

        // "ping"  replaced...
        execlp("ping", "ping", "-c", "3", "google.com", NULL); //  no need for else
        //waitpid(pid1, NULL, 0); // just have to wait... all else can only be executed by parent
    }
    
    int pid2 = fork();
    if (pid2 < 0) {printf("fork2 error\n"); exit(3);}
    
    if (pid2 == 0) // child 2
    {
        dup2(fd[0], STDIN_FILENO); // grep waits to read STDOUT...reroute
        close(fd[0]); // no need
        close(fd[1]); // no need
        execlp("grep", "grep", "stddev", NULL); // "grep"
    }

    close(fd[0]); // parent must close ...do both to be safe
    close(fd[1]); // when you close write end, grep can finish execution
    waitpid(pid1, NULL, 0); // 1 of 2
    waitpid(pid2, NULL, 0); // 2 of 2

    if (track != 0) {printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");}
    return 0;
}

////~~~~END>  up22.c
