/*
    get return value from threads

    pthread_join()  has a return to pass back as void**
    takes reference to pointer...pointer to pointer
    sets value inside it
    void* are nice because they are wild cards
    nice to cast (void**)

    be careful allocating and deallocating in different funcitons
        in a large program...you don't want to do it
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define START 1
#define STOP 6
#define INIT_INT -999

int gv_status = INIT_INT;

int randomInt(int start, int stop);
void* roll_dice();
int ex1();
int ex2();


int main(int argc, char* argv[], char* envp[])
{
    srand(time(NULL));    // seed

    //gv_status = ex1();  // single dice roll
    gv_status = ex2();  // double dice roll

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ \n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  single thread rolls the dice:\n", __func__);
    pthread_t thd;
    int *rollResult; // gets set by pthread_join
    if (pthread_create(&thd, NULL, &roll_dice, NULL) != 0) {return 1;}
    if (pthread_join(thd, (void**)&rollResult) != 0) {return 2;} // double pointer to int
    printf("\n%s()  ,  result of roll:  %d  ,   ptr address:  %p\n", 
        __func__, *rollResult, rollResult);
    free(rollResult);    // deallocate that segment of memory
    rollResult = NULL;
    return 69;
}
void* roll_dice()
{
    int rollValue_static = randomInt(START, STOP);     // on the stack, goes out of scope too fast
    int * rollValue_dynamic = malloc(1 * sizeof(int)); // make it dynamic
    printf("\n%s()  ,  dice roll:  %d  ,  ptr address:  %p\n", 
        __func__, rollValue_static, rollValue_dynamic);
    *rollValue_dynamic = rollValue_static;
    //return (void*)&rollValue_static; // turns into a void*   but local to function
    return (void*)rollValue_dynamic;
}


int ex2()
{
    printf("\n%s()  ,  2 threads roll, craps:\n", __func__);
    pthread_t thd[2];
    int *rollResult[2];
    rollResult[0] = NULL;
    rollResult[1] = NULL;

    if (pthread_create(&thd[0], NULL, &roll_dice, NULL) != 0) {return 1;}
    if (pthread_create(&thd[1], NULL, &roll_dice, NULL) != 0) {return 2;}
    if (pthread_join(thd[0], (void**)&rollResult[0]) != 0) {return 3;}
    if (pthread_join(thd[1], (void**)&rollResult[1]) != 0) {return 4;}

    printf("\n%s()  ,  1st roll:  %d  ,   ptr address:  %p\n", 
        __func__, *rollResult[0], rollResult[0]);
    printf("\n%s()  ,  2nd roll:  %d  ,   ptr address:  %p\n", 
        __func__, *rollResult[1], rollResult[1]);

    free(rollResult[0]); 
    rollResult[0] = NULL;
    free(rollResult[1]);   
    rollResult[1] = NULL;
    return 69;
}


int randomInt(int start, int stop)
{
    if (start >= stop) { return INIT_INT; }

    int16_t diff = (stop - start) + 1;
    int16_t result = ( ( rand() % diff ) + start );
    return result;
}

////////~~~~~~~~END>  ut6.c
