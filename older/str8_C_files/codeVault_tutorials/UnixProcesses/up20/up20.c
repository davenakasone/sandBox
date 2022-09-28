/*
    send an array through a pipe
    ...send sizes first so other process knows what to do
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int fd[2];
    if (pipe(fd) == -1) {printf("pipe error\n"); exit(1);}
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); exit(2);}

    if (pid == 0) // child
    {
        close(fd[0]);

        int n = -999;
        int i = -999;
        int arr[10];
        srand(time(NULL));

        n = (rand() % 10) + 1;    // 1-10

        printf("\n");
        for (i = 0; i < n; i++)
        {
            arr[i] = (rand() % 100) + 101; // 100-200
            printf("child,  arr[%d] =  %d\n", i, arr[i]);
        }

        if (write(fd[1], &n, sizeof(int)) < 0) {printf("write error\n"); exit(3);}
        if (write(fd[1], arr, sizeof(int)*n) < 0) {printf("write error\n"); exit(4);}
        printf("\tchild wrote arry of { %d } elements\n\n", n);

        close(fd[1]);
    }
    else // child
    {
        close(fd[1]);

        int arr[10];
        int n = -999;
        int i = -999;

        if (read(fd[0], &n, sizeof(int)) < 0) {printf("read error\n"); exit(5);}
        if (read(fd[0], arr, sizeof(int)*n) < 0) {printf("read error\n"); exit(6);}
        close(fd[0]);

        for (i = 0; i < n; i++)
        {
            printf("parent,  arr[%d] =  %d\n", i, arr[i]);
        }
        printf("\tparent read arry of { %d } elements\n\n", n);

    }
    if (pid != 0) {printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");}
    return 0;
}

////~~~~END>  up20.c

/*
#define arrSize 10


int main(int argc, char * argv[])
{
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); exit(1);}
    int status = -999;
    int fd[2];
    if (pipe(fd) == -1) {printf("pipe error\n"); exit(2);}

    if (pid == 0) // child
    {
        close(fd[0]);
        int arr[arrSize];
        srand(time(NULL));
        int fills = (rand() % (arrSize-3)) + 1; // fills array with 1 to arrSize

        for (int i = 0; i < fills; i++)
        {
            arr[i] = (rand() % 100) + 101; // 100 to 200
            printf("child arr[%d] = %d\n", i, arr[i]);
        }
        status = write(fd[1], &fills, sizeof(int));
        if ( status == -1) {printf("write error\n"); exit(3);}
        status = write(fd[1], arr, sizeof(int) * fills);
        if (status == -1) {printf("write error\n"); exit(4);}
        close(fd[1]);
    }
    else // parent
    {
        close(fd[1]);
        int ar[arrSize];
        int fill = -999;

        // read number of elments
        status = read(fd[0], &fill, sizeof(int));
        if (status < 0) {printf("read error\n"); exit(5);};
        // then read elements 
        status = read(fd[0], ar, sizeof(int) * fill);
        if (status == -1) {printf("read error\n"); exit(5);}; 

        close(fd[0]); // close child
        for (int i = 0; i < fill; i++)
        {
            printf("parent ar[%d] = %d\n", i, ar[i]);
        }
        wait(NULL); // wait for child to free resources
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}
*/