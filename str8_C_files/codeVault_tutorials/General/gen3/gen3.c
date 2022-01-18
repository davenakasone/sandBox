/*
    you should always check return values on function calls
    errno is usually set

    int fprintf(stream*, char* format,...)  <0 on fail, total chars on success
    stderr : default file descriptor where error messages can be written, usually stdout
    errno : gets set every function call (if POSIX type) by daemon


    let perror() print
    let strerror(errno) translate the code
    print to stderr    fprintf()

    if you want to dup() and close() ...redirection takes smallest availible fd
    or just keep with a DEBUG_PRINT and DEBUG_WRITE

    put everywhere, even /by 0
*/

#include <fcntl.h>     // open() , close() , write() , O_
#include <errno.h>     // errno + MACROS
#include <stdio.h>     // stdout , stderr , fprintf() , printf() , perror()
#include <stdlib.h>    // EXIT_SUCCESS , NULL
#include <string.h>    // strerror() ,
#include <unistd.h>

#define GOOD 69
#define BAD -69
#define INIT_INT -999

int gv_status = INIT_INT;
int gv_errNum = INIT_INT;

int ex1();
int ex2();
int ex3();

extern int errno;    // good idea


int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();
    //gv_status = ex2();
    gv_status = ex3();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  basic use of stderr, strerror, errno...\n", __func__);

    char fake[] = "does_not_exist.txt";
    FILE* fp = NULL;
    fp = fopen(fake, "r");

    if (fp == NULL)
    {
        //gv_status = errno;  // not really needed
        fprintf(stderr, "\n\terrno =  %d\n", gv_status);
        perror("\n\terror code");
        fprintf(stderr, "\n\terror opening \"%s\" :: %s  ,  ", fake, strerror(errno));
        return BAD;
    }
    return GOOD;
}


int ex2()
{
    printf("\n%s()  ,  practical use with some redirect...\n", __func__);

    char fake[] = "does_not_exist.txt";
    FILE* fp = NULL;
    fp = fopen(fake, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "\n\t%s()  ,  errno =  %d  -->  %s\n", 
            __func__, errno, strerror(errno));
        return BAD;
    }
    return GOOD;
}


int ex3()
{
    printf("\n%s()  ,  practical use...\n", __func__);

    //dup2(stdout, debug_fp);   // can use these interchangably now
    //FILE* debug_fp = fopen("debug.txt", "w");
    int debug = dup(STDERR_FILENO);
    debug = open("debug.txt", O_WRONLY | O_CREAT);

    char fake[] = "does_not_exist.txt";
    FILE* fp = NULL;
    fp = fopen(fake, "r");

    if (fp == NULL)
    {
        char temp[256];
        snprintf(temp, 256-1, "\n\t%s()  ,  errno =  %d  -->  %s\n", 
            __func__, errno, strerror(errno));
        write(debug, "fuck you", 10);
        close(debug);
        return BAD;
    }
    return GOOD;
}

////////~~~~~~~~END>  gen3.c
