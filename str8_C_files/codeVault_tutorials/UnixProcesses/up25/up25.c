/*
    waitpid() is like waitppid() , but for child...specific child

    goes with getpid()

    sticking a "return 0;" is a good way to end a process

    waitpid()  0, any child with same group ID, -1 ...same as wait()
    WNOHANG flag is good for finished execution, saves in NULL param
        won't wait for anything
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char * argv[], char * envp[])
{
    int  pid1 = fork();
    if (pid1 == -1) {printf("error in fork 1\n"); exit(1);}
    if (pid1 == 0)    // child on pid1 
    { 
        sleep(3);
        printf("finished execution  ,  pid1:  %d\n", getpid());
        return 0;
    } 

    int pid2 = fork();
    if (pid2 == -1) {printf("error in fork 2\n"); exit(2);}
    if (pid2 == 0)    // child on pid2 
    {
        sleep(1);
        printf("finished execution  ,  pid2:  %d\n", getpid());
        return 0;
    }   
    
    /* just waiting for both...no pid specified
    printf("\n");
    int result1 = wait(NULL);
    printf("waited for pid:  %d\n", result1);
    int result2 = wait(NULL);
    printf("waited for pid:  %d\n", result2);
    */

    // now you can control what to wait for
    printf("\n");
    int result1 = waitpid(pid1, NULL, 0);
    printf("waited for pid:  %d\n", result1);
    int result2 = waitpid(pid2, NULL, 0);
    printf("waited for pid:  %d\n", result2);


    printf("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

////~~~~END>  up25.c
