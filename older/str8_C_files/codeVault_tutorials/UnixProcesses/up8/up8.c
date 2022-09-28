/*
    can only fork in heirarchy
    another feature "FIFO" lets pipes on different heierchy

    this is how you can do inter-process communication
    if you need a "named pipe" use a FIFO

    FIFO is like any other file
    hangs unless another process opens other end {read/write}

    could also open 2 terminals and "cat"
    call mkfifo myFIFO in cmdl if needed
*/

#include <fcntl.h> // open()
#include <errno.h>  // ECHILD
#include <stdlib.h>
#include <stdio.h>     // printf()
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>    // fork() {linux only}  ...read(), write(), 


int main(int argc, char *argv[]) 
{
    printf("\n");
    char myFIFO[] = "myfifo1";
    int status = -999;
    status = mkfifo(myFIFO, 0777); // read, write, anyone
    if (errno != EEXIST){printf("FIFO error\n"); exit(1);}

    //int fd = open(myFile, O_WRONLY); // blocks until other end open
    int fd = open(myFIFO, O_RDWR); // will finish...no waiting
    printf("opening FIFO\n");
    if (fd == -1) {printf("open error\n"); exit(2);}
    // or create fifo yourself

    int x  = 777;
    int y = -999;
    printf("x =  %d\n", x);
    status = write(fd, &x, sizeof(x));
    if (status == -1) {printf("write error\n"); exit(3);}
    status = read(fd, &y, sizeof(int));
    if (status == -1) {printf("read error\n"); exit(4);}
    printf("y =  %d\n", y);
    close(fd);

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up8.c
