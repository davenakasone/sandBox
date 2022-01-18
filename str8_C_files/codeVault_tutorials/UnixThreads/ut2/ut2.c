/*
    threads != processes
    the threads have the same process ID
    processes can have multiple threads
    threads only have one process
    process encompasses threads..

    forking duplicates everything into a child process ... own memory space
    threads keep everything in same place...common memory space

    notice "x" starts at 5
        when fork()
            child increments --> 6 , only process to increment
            parent prints --> 5  (no change) , had different memory / duplicate
        with threads
            thread 1 calls routine() , x incremented     --> 6
            thread 2 calls handleX() , x not incremented  --> 6
                shared same memory, so everything shared
    
    threads are sharing memory...
    do something in 1 thread, it gets seen in other
    everything is shared
    so be careful with threads modifying same variable    
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void process_imp();    // use fork()
void thread_imp();

int x = 5;
int pid = 333;
void* routine()
{
    x++;
    sleep(2);
    printf("\n\tthread works  ,  pid:  %d\n",
        getpid());
    printf("\tx = %d\n", x);
}
void* handleX()
{
    printf("\n\thandling x  ,  pid:  %d\n",
        getpid());
    printf("\tx = %d\n", x);
}


int main(int argc, char * argv[], char * envp[])
{
    //process_imp();
    thread_imp();

    if (pid != 0) {printf("\n\n\t\t~ ~ ~ PROGRAM COMPELTE ~ ~ ~\n\n");}
    return 0;
}


void process_imp()
{
    pid = fork();
    if (pid == -1) {return;}
    if (pid == 0)
    {
        printf("\n\tchild process works  ,  pid:  %d\n",
            getpid());
        x++;
        printf("\tx = %d\n", x);
    }
    
    if (pid != 0) 
    {
        printf("\n\tparent process works  ,  pid:  %d\n",
            getpid());
        printf("\tx = %d\n", x);
        wait(NULL);
    }
}


void thread_imp()
{
    pthread_t t1;
    if (pthread_create(&t1, NULL, &routine, NULL)) {return;};
    if (pthread_join(t1, NULL)) {return;}

    pthread_t t2;
    if (pthread_create(&t2, NULL, &handleX, NULL)) {return;};
    if (pthread_join(t2, NULL)) {return;}
}

////~~~~END>  ut2.c
