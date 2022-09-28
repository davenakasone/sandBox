/*
    you can supress printing to the terminal
    bitwise OR to combine flags

    fd's happen everywhere...pipes, FIFO, open
    it is a number unqiue across process...key to I/O resource

    child process {fd, file}
    0 --> STDIN  , by default  ie read(0) == scanf() with no formating
    1 --> STDOUT , by default
    2 --> STDERR , by default
    // usually open by start of program
    3 --> pingResult.txt

    dup() --> dup2() can reroute STDOUT to .txt

    function will always steal process
    operating system always maintains file descriptor...key to a resource
    Linux always opens certain fd's whenever you open a process
*/

#include <fcntl.h>       // open()
#include <stdlib.h>      // NULL
#include <stdio.h>       // printf()
#include <sys/wait.h>    // wait()
#include <unistd.h>      // fork() {linux only}  ...read(), write(), exec__ family

const char newOutPut[] = "pingResults.txt";


int main(int argc, char *argv[]) 
{
    printf("\n");
    int status = -999;
    int pid = fork();
    if (pid == -1) {printf("fork failure\n"); exit(1);}

    if (pid == 0) // child
    {
        int file = open(newOutPut, O_WRONLY | O_CREAT, 0777); // open, make if not there
        if (file == -1) {printf("open error\n"); exit(2);}
        
        printf("original fd:  %d\n", file);
        //int file2 = dup(file); // duplicates with another fd, points to "file"
        //int file2 = dup2(file, 1); // overwrites all, but won't change pid's or open fd's

        // stdout gets closed, then opened to fd   ...no process ID change or pid's already open
        int file2 = dup2(file, STDOUT_FILENO); // best use, fd you want to clone, value to use

        // close .txt, now that not used
        printf("duplicated fd:  %d  {1 == stdout, now in a .txt}\n\n", file2); // goes to .txt, swap already occured
        close(file); // close original fd, not used, already duplicated

        status = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (status == -1){printf("could not find program to execute\n"); exit(3);}
    }
    else
    {
        //wait(NULL); // just waiting for all children to finish
        wait(&status); // it takes an int pointer...macros for status
        if (WIFEXITED(status)) // if true, it finished execution normally
        {
            int statusCode = WEXITSTATUS(status);
            if (statusCode == 0)
            {
                printf("\ngood ping,  see \"%s\"\n", newOutPut);
            }
            else
            {
                printf("no execution\n");
            }
            printf("status:  %d\n", statusCode);
        }
    }

    // clears file every run
    char discard = '\0';
    printf("\n\t\tpress [enter] to continue: ");
    scanf("%c", &discard);
    FILE * fp = NULL;
    fp = fopen(newOutPut, "w");
    fclose(fp);
    fp = NULL;

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return 0; // this is a status code ... not 0 = error
}

////////~~~~~~~~END>  up13.c
