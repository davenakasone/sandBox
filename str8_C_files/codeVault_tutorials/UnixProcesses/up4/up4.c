/*
    every process, except id = 0 has a process ID
    main process lanuches everything

    every process has an ID, and it may switch
    call wait() if you fork()
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    printf("\n");
    int id = fork();

    /* zombie  , parent should not finish first
    if (id == 0)
    {
        printf("current ID:  %d  ,  parent ID:  %d\n",
        getpid(), getppid());
        sleep(1);
    }
    */

    printf("current ID:  %d  ,  parent ID:  %d\n",
        getpid(), getppid());
        
    if (id != 0) // parent
    {
        int result;
        result = wait(NULL);
        if ( result == -1)    // still would finish if you did not check if parent
        {
            printf("no children to wait for\n");
        }    
        else
        {
            printf("finished execution\n");
        }
    }
    
    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  up4.c
