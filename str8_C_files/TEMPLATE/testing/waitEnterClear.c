/*
    waits for user to press [enter]
    clears stdout

    use for section transitions
    use before earasing files (so there is time to check)
*/

#include <stdlib.h>    // system()
#include <stdio.h>     // printf() , getchar()
#include <unistd.h>    // sleep()

#include "testing.h"    // declared here


void waitEnterClear()
{
    char discard;
    printf("\n\t\tpress ENTER to continue:  ");
    discard = getchar();
    
    printf("\t\tclearing stdout...\n\n");
    sleep(1);
    system("clear");
}

////////~~~~~~~~END>  waitEnterClear.c