/*
    more on structs
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct point
{
    int xCord;
    int yCord;
} point;


int main(int argc, char* argv[], char* envp[])
{
    point myCord = {
                        myCord.xCord = 3,
                        myCord.yCord = 7
                    };
    printf("\n%s()  ,  your coodinate:  [ %d , %d ]\n",
        __func__, myCord.xCord, myCord.yCord);
    
    point anotherCord = {
                        .xCord = 1,
                        .yCord = 5
                    };
    printf("\n%s()  ,  your coodinate:  [ %d , %d ]\n",
        __func__, anotherCord.xCord, anotherCord.yCord);

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END>  stc2.c
