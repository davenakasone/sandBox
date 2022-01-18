/*
    send an string through a pipe
    ...send sizes first so other process knows what to do

    fgets is interesting
    go char by char if needed

    could do this with pipe, file, ect
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUFF 256


int main(int argc, char* argv[])
{
    int fd[2];
    if (pipe(fd) == -1) {printf("pipe error\n"); exit(1);}
    int pid = fork();
    if (pid == -1) {printf("fork error\n"); exit(2);}

    if (pid == 0) // child
    {
        close(fd[0]);

        char holder[BUFF];
        memset(holder, '\0', BUFF);

        printf("\ninput a string:  ");
        fgets(holder, BUFF-1, stdin);
        int characters = sizeof(char) * (strlen(holder) + 1); // includes terminator '\0'
        holder[characters-2] = '\0'; // get rid of '\n'
        characters = characters - 1;

        if (write(fd[1], &characters, sizeof(int)) == -1) {printf("write error\n"); exit(3);}
        if (write(fd[1], holder, characters) == -1) {printf("write error\n"); exit(4);}
        close(fd[1]);
        printf("child:  \"%s\"  , chars:  %d {includes terminator}\n\n", holder, characters);
    }
    else // parent
    {
        close(fd[1]);

        char holder[BUFF];
        int chars = -999;

        if (read(fd[0], & chars, sizeof(int)) == -1) {printf("read error\n"); exit(5);}
        if (read(fd[0], holder, sizeof(char)*chars) < 0) {printf("read error\n"); exit(6);}
        close(fd[0]);
        printf("parent:  \"%s\"  , chars:  %d {includes terminator}\n\n", holder, chars);
        wait(NULL);
    }
    if (pid != 0) {printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");}
    return 0;
}

////~~~~END>  up21.c
