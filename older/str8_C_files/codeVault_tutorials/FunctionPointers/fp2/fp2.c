/*
    array of function pointers
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int gc_x = 7;
const int gc_y = 4;

void add(int x, int y) {printf("\n\t\taddition  ,  %d  +  %d  =  %d\n", x, y, x+y);}
void sub(int x, int y) {printf("\n\t\tsubtraction  ,  %d  -  %d  =  %d\n", x, y, x-y);}
void mul(int x, int y) {printf("\n\t\tmultiply  ,  %d  *  %d  =  %d\n", x, y, x*y);}


int main(int argc, char* argv[], char* envp[])
{
    // array of function pointers for function with arg: int, int
    void (*fun_ptr_arr[])(int, int) = {add, sub, mul};

    int choice = 0;
    while (choice == 0 ||
           choice == 1 ||
           choice == 2  )
    {
        choice = -999;
        printf("\n\tselect < 0, 1, or 2 >  :  ");
        scanf("%d", &choice);
        if (choice == 0 ||
            choice == 1 ||
            choice == 2  )  
        {
            (*fun_ptr_arr[choice])(gc_x, gc_y);
        }
    }

    printf("\n\n\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

////////~~~~~~~~END> fp2.c
