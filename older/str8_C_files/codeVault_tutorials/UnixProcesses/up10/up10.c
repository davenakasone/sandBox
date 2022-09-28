/*
    need pipe to communicate between processes
    pipes take 2 file descriptors...4 if forked once, 8, 16, ....

    stop the race condition
    can't have pipe that sends and receives data on same process... use 2
*/

#include <stdlib.h>
#include <stdio.h>       // printf() 
#include <sys/wait.h>    // wait()
#include <time.h>        // time()
#include <unistd.h>      // fork() {linux only}  ...read(), write(),


int main(int argc, char *argv[]) 
{
    int status = -999;
    int pipeA[2]; // read [0] , write [1]   child--> parent  {child writes, parent reads}
    int pipeB[2]; // parent --> child  {parent writes, child reads}
    if (pipe(pipeA) == -1) {printf("error in pipeA\n"); return 1;}
    if (pipe(pipeB) == -1) {printf("error in pipeB\n"); return 1;}
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); return 2;}
    int child = -999;
    int parent  = -999;
    if (pid == 0)
    {
        child = pid;
    }
    if (pid != 0)
    {
        parent = pid;
    }

    if (pid == child)
    {
        close(pipeA[0]);    // never reads on this pipe, only write
        close(pipeB[1]);    // never writes on this pipe, only read

        int x = -999;
        status = read(pipeB[0], &x, sizeof(x));
        printf("2) status:  %d\n", status);
        if(status == -1) {printf("error while reading\n"); exit(3);}
        printf("[pid:  %d]  ,  child received:  %d\n\n", pid, x);

        x = x * 4;

        status = write(pipeA[1], &x, sizeof(x));
        printf("3) status:  %d\n", status);
        if (status == -1) {printf("write error\n"); exit(4);}
        printf("[pid:  %d]  ,  child wrote:  %d\n\n", pid, x);

        close(pipeA[1]);    // all child ends closed
        close(pipeB[0]); 
    }
    
    if (pid == parent)
    {
        close(pipeA[1]);    // never writes, only read
        close(pipeB[0]);    // never reads, only writes

        srand(time(NULL));            // seed
        int y = (rand() % 10) + 1;    // 1,9

        status = write(pipeB[1], &y, sizeof(int));
        printf("\n1) status:  %d\n", status);
        if (status == -1) {printf("write error\n"); exit(5);}
        printf("[pid:  %d]  ,  parent wrote:  %d\n\n", pid, y);
        
        status = read(pipeA[0], &y, sizeof(int));
        printf("4) status:  %d\n", status);
        if (status == -1) {printf("read error\n"); exit(6);}
        printf("[pid:  %d]  ,  parent reads:  %d\n", pid, y);

        wait(NULL);
        close(pipeA[0]); // all parent ends closed
        close(pipeB[1]);
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up10.c
