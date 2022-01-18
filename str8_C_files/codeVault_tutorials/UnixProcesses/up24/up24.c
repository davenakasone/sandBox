/*
    execute another program in C, using exec__() family
    
    !!! check:   $ which grep    ...  $ which pin  ...

    execl() is for execuatables, in general
    path to program
    path to program
    args
    NULL

    "p" is path ... gets added
    "l" is list of arguments
    "v" is vector
    "e" is environment...give it an environment (set of variables)
        really the "char * envp[]"  
    
    every exec__() is just a combonation or "e,l,p,v"
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

const char ping_path[] = "/sbin/ping";
const char website[] = "google.com";

void ex1();
void ex2();
void ex3();
//void ex4();  // don't try


int main(int argc, char* argv[], char * envp[])
{
    printf("\n");
    ex1(); // execl()
    //ex2(); // execlp()    finds path
    //ex3(); // execvp()  args passed by vector
    //ex4(); // use execvpe() with environment , not C99

    printf("\n\n\t~~~ PROGRAM COMPLETE ~~~\n\n");
    return 0;
}


void ex1()
{
    int pid = fork();
    if (pid < 0) {printf("fork error\n"); exit(1);}

    if (pid == 0)
    {
        int status = execl(ping_path, ping_path, "-c", "3" , website, NULL);
    }
    wait(NULL);
}


void ex2()
{
    int pid = fork();
    if (pid < 0) {printf("fork error\n"); exit(2);}
    
    if (pid == 0)
    {
        execlp("ping", "ping", "-c", "3" , website, NULL);
    }
    wait(NULL);
}


void ex3()
{
    int pid = fork();
    if (pid < 0) {printf("fork error\n"); exit(3);}

    if (pid == 0)
    {
        char * arr[] = {
            "ping",
            "-c",
            "3",
            "google.com",
            NULL };
    
        execvp("ping", arr);
    }
    wait(NULL);
}

/*
void ex4()
{
    int pid = fork();
    if (pid < 0) {printf("fork error\n"); exit(3);}

    if (pid == 0)
    {
        char * env[] = {"TEST=environment variable", NULL};
        char * arr[] = {
            "ping",
            "-c",
            "3",
            "google.com",
            NULL };
    
        execvpe("ping", arr, env);
    }
    wait(NULL);
}
*/

////~~~~END>  up24.c
