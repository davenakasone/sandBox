/*
    could just execute from command line   path and arguments
    or let the program do it

    whenever you execute a function, your process gets replaced with what you call
    all memory replaced by own line, exec stops all.
    need another process

    use excelp(const char * file, const char * arg,...)
    only on child...don't want zombie process

    make the child process get replaced, then don't touch it...parent wait()
    not proper to exec__() on parent...child will be a zombie, memory leak
*/

#include <stdlib.h>      // NULL
#include <stdio.h>       // printf()
#include <sys/wait.h>    // wait()
#include <unistd.h>      // fork() {linux only}  ...read(), write(), exec__ family


int main(int argc, char *argv[]) 
{
    //execlp("ping", "ping", "-c", "3", "google.com", NULL); // 3x pings to google
    //printf("good ping\n"); // won't print    ...hangs

    printf("\n");
    int pid = fork();
    if (pid == -1) {printf("fork failure\n"); exit(1);}

    if (pid == 0)    // child
    {
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        //execlp("mkfifo", "mkfifo", "myFIFO", NULL); // makes a FIFO...then read/write it
        printf("this won't work, child process replaced by exec__\n");
    }
    else    // parent
    {
        wait(NULL);    // wait for all children to finish
        printf("\ngood ping\n");
    }

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return 0;
}

////////~~~~~~~~END>  up11.c
