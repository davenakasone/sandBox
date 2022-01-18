/*
    passing values to threads is helpful
    may want to do things for order of creation

    here, you will make ~10 threads, each will print a prime
    remember threads run in parallel, so you could have some problems with things changing

    don't go off a loop variable or local variable...
    may want to allocate memory

    notice that there is no guaruntee for what thread finishes first
        still good...only 1 prime for thread
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define THREADZ 10

int gv_status = EXIT_SUCCESS;
int gv_primes[THREADZ] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine_static(void* arg);
void* routine_dynamic(void* arg);
void startSeq();
int ex1();    // wrong way, passing "i" but it changes
int ex2();    // correct handling
int ex3();    //  arg gets free() inside "routine()"


int main(int argc, char* argv[], char* envp[])
{
    startSeq();

    gv_status = ex1();    // don't pass "i" as param
    gv_status = ex2();    // correct
    gv_status = ex3();  // correct, dynamic

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n\t%s()  ,  wrong way:\n", __func__);
    pthread_t thdz[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_create(&thdz[i], NULL, &routine_static, &i) != 0)
        {
            printf("\nfailed to create thread  %d\n", i);
            return i;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thdz[i], NULL) != 0)
        {
            printf("\nfailed to join thread  %d\n", i);
            return (-1*i);
        }
    }
    return 69;
}


int ex2()
{
    printf("\n\t%s()  ,  static correct:\n", __func__);
    pthread_t thdz[THREADZ];
    int reffs[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        reffs[i] = i;
        if (pthread_create(&thdz[i], NULL, &routine_static, &reffs[i]) != 0)
        {
            printf("\nfailed to create thread  %d\n", i);
            return i;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thdz[i], NULL) != 0)
        {
            printf("\nfailed to join thread  %d\n", i);
            return (-1*i);
        }
    }
    return 69;
}


int ex3()
{
    printf("\n\t%s()  ,  dynamic correct:\n", __func__);
    pthread_t thdz[THREADZ];
    for (int i = 0; i < THREADZ; i++)
    {
        int * ref = malloc(sizeof(int));
        *ref = i;
        if (pthread_create(&thdz[i], NULL, &routine_dynamic, ref) != 0)
        {
            printf("\nfailed to create thread  %d\n", i);
            return i;
        }
    }
    for (int i = 0; i < THREADZ; i++)
    {
        if (pthread_join(thdz[i], NULL) != 0)
        {
            printf("\nfailed to join thread  %d\n", i);
            return (-1*i);
        }
    }
    return 69;
}


void* routine_static(void* arg)
{
    usleep(300000);  // value at address can change
    int idx = *(int*)arg; // void* --> int* --> int
    printf("\t\tprime[%d] =  %d\n", 
        idx, gv_primes[idx]);
    return NULL;
}
void* routine_dynamic(void* arg)
{
    usleep(300000); 
    int idx = *(int*)arg;
    printf("\t\tprime[%d] =  %d\n", 
        idx, gv_primes[idx]);
    free(arg);    // allocated and deallocated in different functions !!!
    return NULL;
}


void startSeq()
{
    printf("\nprimes { ");
    for (int i = 0; i < THREADZ - 2; i++)
    {
        printf("%d, ", gv_primes[i]);
    }
    printf("%d }\n", gv_primes[THREADZ-1]);
}

////////~~~~~~~~END>  ut7.c
