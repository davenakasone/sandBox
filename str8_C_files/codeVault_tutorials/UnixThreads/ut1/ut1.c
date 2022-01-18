/*
    basic introduction to threads
    a thread executes a function

    define place where API can store info about thread.. "pthread_t" type

    always check return values...some evnis supress forking, threads, ect...
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void* routine()
{
    printf("\n\ttest from threads\n");
    sleep(1);
    printf("\t\tending thread...\n");
    return NULL;
}


int main(int argc, char * argv[], char * envp[])
{
    pthread_t t1; // for holding info about thread  a struct
    pthread_t t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0) {return 1;}
    if (pthread_create(&t2, NULL, &routine, NULL) != 0) {return 2;}
    /*
        - the thread variable
        - any custom set-up {NULL for default}
        - function to execute
        - args to function {NULL for none}
    */

   if (pthread_join(t1, NULL) != 0) {return 3;}
   if (pthread_join(t2, NULL) != 0) {return 4;}
   /*
        waiting for thread to finish
        - pass the struct to thread 
        - collect what function returns...NULL for nothing
   */

    printf("\n\n\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

////~~~~END ut1.c
