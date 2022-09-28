/*
    conditional variables let you do a lot
    the pthread API will call: wait-->signal-->broadcast for you

    think about someone waiting inline to fill up gas
    one guy waits to fill car
    other guy fills car
    ...this could only happen in NJ, fyi

    ideally, you can't take fuel when there is none
    ex1() is not good... driver gets there first and fuel goes negative
    ex2() simple if statment to control...waits, but car didn't get fuel
        trying a loop is getting savage -->
    ex3() ...condition variables, part of API, use them

    pthread_cond_t has: wait, signal, broadcast

    pthread_cond_wait()  should have an unlocked mutex and conditional variable
        1> pthread_mutex_unlock(&pMute)    loop indicates unlock
        2> waits for signal on conditional var
        3> pthread_lock(&pMute)     lock for processing
    
    condition variable is an identifier for a certain signal
    you can signal or wait on it
    signaling does not mean wait condition is true
    just signaling that condition's result might have changed
        waiting always calls _unlock()
        
*/

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define GET_NAME(var) #var
#define INIT_INT -999
#define GOOD 69

int gv_status = INIT_INT;
int fueled = 0; // gallons put in car
pthread_mutex_t pMute;
pthread_cond_t conFuel; // the condition varialbe

int ex1(); // not good
void* fuel_filling1(void* arg);
void* car_waits1(void* arg);
int ex2(); // better
void* fuel_filling2(void* arg);
void* car_waits2(void* arg);
int ex3(); // best
void* fuel_filling3(void* arg);
void* car_waits3(void* arg);


int main(int argc, char* argv[], char* envp[])
{
    //gv_status = ex1();
    //gv_status = ex2();
    gv_status = ex3();

    printf("\n\n\tstatus:  %d\n", gv_status);
    printf("\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    printf("\n%s()  ,  begin simulating gas station...\n", __func__);
    pthread_t thz[2];
    pthread_mutex_init(&pMute, NULL);

    for (int i = 0; i < 2; i++)
    {
        if (i == 1) // no one in line
        {
            if (pthread_create(&thz[i], NULL, &fuel_filling1, NULL) != 0)
            {
                printf("\nfailed to create thread %d\n", i+1);
                return (i+1);
            }
        }
        else // waiting car first
        {
            if (pthread_create(&thz[i], NULL, &car_waits1, NULL) != 0)
            {
                printf("\nfailed to create thread %d\n", i);
                return (i+1);
            }
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfaild to join thread %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
    }
    
    pthread_mutex_destroy(&pMute);
    return GOOD;
}
void* fuel_filling1(void* arg)
{
    printf("\n\t%s()...\n", __func__);
    for (int i = 0; i < 5; i++) // guy only needs 5 gallons
    {
        pthread_mutex_lock(&pMute);
        fueled++;
        printf("\n\tfilled  %d  gallons\n", fueled);
        pthread_mutex_unlock(&pMute);
        sleep(1); // time for a gallon to fuel
    }
    return NULL;
}
void* car_waits1(void* arg)
{
    printf("\n\t%s()...\n", __func__);
    printf("\n\tcar got  %d  gallons\n", fueled);
    fueled = fueled - 5;
    printf("\n\t%s =  %d\n", GET_NAME(fueled), fueled);
    return NULL;
}


int ex2()
{
    printf("\n%s()  ,  begin simulating gas station...\n", __func__);
    pthread_t thz[2];
    pthread_mutex_init(&pMute, NULL);

    for (int i = 0; i < 2; i++)
    {
        if (i == 1) // no one in line
        {
            if (pthread_create(&thz[i], NULL, &fuel_filling2, NULL) != 0)
            {
                printf("\nfailed to create thread %d\n", i+1);
                return (i+1);
            }
        }
        else // waiting car first
        {
            if (pthread_create(&thz[i], NULL, &car_waits2, NULL) != 0)
            {
                printf("\nfailed to create thread %d\n", i);
                return (i+1);
            }
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfaild to join thread %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
    }
    
    pthread_mutex_destroy(&pMute);
    return GOOD;
}
void* fuel_filling2(void* arg)
{
    printf("\n\t%s()...\n", __func__);
    for (int i = 0; i < 5; i++) // guy only needs 5 gallons
    {
        pthread_mutex_lock(&pMute);
        fueled++;
        printf("\n\tfilled  %d  gallons\n", fueled);
        pthread_mutex_unlock(&pMute);
        sleep(1); // time for a gallon to fuel
    }
    return NULL;
}
void* car_waits2(void* arg)
{
    printf("\n\t%s()...\n", __func__);
    if (fueled == 5)
    {
        printf("\n\tcar got  %d  gallons\n", fueled);
        fueled = fueled - 5;
        printf("\n\t%s =  %d\n", GET_NAME(fueled), fueled);
    }
    else
    {
        printf("\n\tnot fueled\n");
    }
    return NULL;
}


int ex3()
{
    printf("\n%s()  ,  begin simulating gas station...\n", __func__);
    pthread_t thz[2];
    pthread_mutex_init(&pMute, NULL);
    pthread_cond_init(&conFuel, NULL);

    for (int i = 0; i < 2; i++)
    {
        if (i == 1) // no one in line
        {
            if (pthread_create(&thz[i], NULL, &fuel_filling3, NULL) != 0)
            {
                printf("\nfailed to create thread %d\n", i+1);
                return (i+1);
            }
        }
        else // waiting car first
        {
            if (pthread_create(&thz[i], NULL, &car_waits3, NULL) != 0)
            {
                printf("\nfailed to create thread %d\n", i);
                return (i+1);
            }
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(thz[i], NULL) != 0)
        {
            printf("\nfaild to join thread %d\n", (-1*(i+1)));
            return (-1*(i+1));
        }
    }
    
    pthread_mutex_destroy(&pMute);
    pthread_cond_destroy(&conFuel);
    return GOOD;
}
void* fuel_filling3(void* arg)
{
    printf("\n\t%s()...\n", __func__);
    for (int i = 0; i < 5; i++) // guy only needs 5 gallons
    {
        pthread_mutex_lock(&pMute);
        fueled++;
        printf("\n\tfilled  %d  gallons\n", fueled);
        pthread_mutex_unlock(&pMute);
        sleep(1); // time for a gallon to fuel
    }
    pthread_cond_signal(&conFuel); // tells all waiting threads they can continue
    return NULL;
}
void* car_waits3(void* arg)
{
    printf("\n\t\t%s()...\n", __func__);
    pthread_mutex_lock(&pMute);
    while(fueled != 5) // must contain condition in a while loop
    {
        printf("\n\t\tno fuel, waiting...\n");
        pthread_cond_wait(&conFuel, &pMute); // waits IN A WHILE LOOP, then wakes up thread
    }
    printf("\n\t\tcar got  %d  gallons\n", fueled);
    fueled = fueled - 5;
    printf("\n\t\treset  ,  %s =  %d\n", GET_NAME(fueled), fueled);
    pthread_mutex_unlock(&pMute);
    return NULL;
}

////////~~~~~~~~END>  ut10.c
