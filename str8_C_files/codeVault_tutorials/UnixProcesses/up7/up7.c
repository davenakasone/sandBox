/*
    how to use fork() and pipe() in real life
    take advantage of multiple processes on computer
        split the work
*/

#include <errno.h>  // ECHILD
#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <sys/wait.h>  // process ID control
#include <unistd.h>    // fork() {linux only}  ...read(), write(), 


int main(int argc, char *argv[]) 
{
    printf("\nthe array:\n");
    int temp = -999;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    printf("\n");

    int fd[2]; // keys to pipe ... has 2 ends   fd[0] = read, fd[1] = write
    temp = pipe(fd);
    if (temp == -1)
    {
        printf("the pipe was not made correctly\n"); exit(1);
    }

    int id = -999;
    id = fork(); // processes to feed
    if (id == -1)
    {
        printf("the fork was not made correctly\n"); exit(2);
    }

    int start = -999;
    int stop = -999;
    int size = sizeof(arr)/sizeof(int);

    if (id == 0)
    {
        start = 0;
        stop = start + size/2; // floor value
    }
    else
    {
        start = size/2;
        stop = size;
    }

    int sum = 0;
    for (int i = start; i < stop; i++)
    {
        if(i==start) {printf("\n");}
        sum = sum + arr[i];
        if (id == 0)
        {
            printf("child  ,  arr[%d] = %d  ,  sum = %d\n", i, arr[i], sum);
        }
        else
        {
            printf("parent  ,  arr[%d] = %d  ,  sum = %d\n", i, arr[i], sum);
        }
    }

    // they execute in parallel...divided work
    printf("\ncalculated partial sum:  %d  ,  id:  %d\n", sum, id); 
    // send partial sum to other process with pipe()

    if (id == 0)
    {
        close(fd[0]); // close reading end
        temp = write(fd[1], &sum, sizeof(sum)); // child writes to parent
        if (temp == -1) {printf("write error\n"); exit(3);}
        close(fd[1]); // close writting end
    }
    else
    {
        int sumFromChild = -999;
        close(fd[1]); // no writting needed
        temp = read(fd[0], &sumFromChild, sizeof(sumFromChild));
        if (temp == -1) {printf("read error\n"); exit(4);}
        close(fd[0]);

        int totalSum = sum + sumFromChild;
        printf("total sum:  %d\n", totalSum);
        wait(NULL); // wait for child to finish
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up7.c
