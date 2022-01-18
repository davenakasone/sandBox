/*
    FIFO can be used to process data
    you should balance what will read, what will write

    here, we made the FIFO in terminal
    navigate to this directory
    "mkfifo sum"   ...special file that allows processes to get common read/write location
    we called it [sum]

    you can write array all at once...it is contigous memory
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
    int catch = -999;
    printf("\n");

    catch = ex1();
    printf("\n\tcatch:  %d\n", catch);

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}


////~~~~ FIFO already made, just use for work
int ex1()
{   
    srand(time(NULL)); // seed
    int arr[SIZE];
    printf("\nan array with { %d } elements:\n", SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 10; // fill 0,9
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    int fd = open("sum", O_WRONLY);
    if (fd == -1) {printf("error while opening\n"); return 1;}

    if (write(fd, arr, sizeof(int) * 5) == -1) {printf("error while writting\n"); return 2;}
    close(fd);

    int sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum = sum + arr[i];
    }
    printf("\tsum:  %d\n", sum);

    return 0;
}

////////~~~~~~~~END>  up91.c
