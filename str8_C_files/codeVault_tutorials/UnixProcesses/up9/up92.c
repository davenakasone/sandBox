/*
    the other part

    run in 2 terminals...they wait for eachother

    there is a buffer in FIFO
*/

#include <fcntl.h> // open()
#include <errno.h>  // ECHILD
#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>    // fork() {linux only}  ...read(), write(), 
#include <time.h> // time()

#define SIZE 5

int ex1(); // handle muti-process with FIFO


int main(int argc, char *argv[]) 
{
    printf("\n");
    int arr[SIZE];
    int fd = open("sum", O_RDONLY);
    if (fd == -1) {printf("error while reading\n"); return 1;}

    if (read(fd, arr, sizeof(int)*5) == -1) {printf("read error\n"); return 2;}
    for (int i = 0; i < SIZE; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    close(fd);

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return 0;
}

////////~~~~~~~~END>  up92.c
