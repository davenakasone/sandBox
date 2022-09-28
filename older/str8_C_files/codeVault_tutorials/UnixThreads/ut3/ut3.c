/*
    race conditions are not easy to predict
    it is something you do not want to do

    a mail box with listeners...threads
    they increment

    fyi, void* can hold address of can type and be casted to any type
        void pointers can't be dereferenced, but you can cast and dereference
    
    in ex4(), like anything else:    ok with 1 thread
        read variable
        increment
        write back to memory
    
    problem is one thread reads, operates, writes
        then the other thread does the same thing
            if one thread is reading, and so is other, OS will halt a thread
        the thread on pause has no idea what is happening and just keeps executing
        correct results are not gaurunteed {race condition}
    
    look at $ gcc -S for assembly and you can see what the error
    the only reason low iterations worked is because other thread was not created
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int messages = 0;    // mail box is empty
int status = -999;    // just a holder

int ex1();    // memory shared, should get "messages = 2"
void* routine1()
{
    messages++;    // mail box gets incremented...message received
}

int ex2();    // threads with increments in loop
void* routine2()
{
    for (int i = 0; i < 100; i++) // expect 100 + 100 = 200 
    {
        messages++;
    }
}

int ex3();    // threads with increments in big loop
void* routine3()
{
    for (int i = 0; i < 100000; i++) // expect 100k + 100k = 200k 
    {
        messages++;
    }
}

int ex4();    // threads with increments in big loop, failure emminent
void* routine4()
{
    for (int i = 0; i < 1000000; i++) // expect 1M + 1M = 2M ???
    {
        messages++;
    }
}


int main(int argc, char * arvgv[], char * envp[])
{
    //status = ex1(); // seems ok
    //status = ex2(); // works
    //status = ex3(); // getting questionable
    status = ex4(); // race condition --> failure

    printf("\nmessages received:  %d  ,  status:  %d\n",
        messages, status);
    printf("\n\n\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


int ex1()
{
    pthread_t p1;
    pthread_t p2;
    if (pthread_create(&p1, NULL, &routine1, NULL) != 0){return 1;}
    if (pthread_create(&p2, NULL, &routine1, NULL) != 0){return 2;}
    if (pthread_join(p1, NULL) != 0){return 3;}
    if (pthread_join(p2, NULL) != 0){return 4;}
    return 0;
}


int ex2()
{
    pthread_t p1;
    pthread_t p2;
    if (pthread_create(&p1, NULL, &routine2, NULL) != 0){return 1;}
    if (pthread_create(&p2, NULL, &routine2, NULL) != 0){return 2;}
    if (pthread_join(p1, NULL) != 0){return 3;}
    if (pthread_join(p2, NULL) != 0){return 4;}
    return 0;
}


int ex3()
{
    pthread_t p1;
    pthread_t p2;
    if (pthread_create(&p1, NULL, &routine3, NULL) != 0){return 1;}
    if (pthread_create(&p2, NULL, &routine3, NULL) != 0){return 2;}
    if (pthread_join(p1, NULL) != 0){return 3;}
    if (pthread_join(p2, NULL) != 0){return 4;}
    return 0;
}


int ex4()
{
    pthread_t p1;
    pthread_t p2;
    if (pthread_create(&p1, NULL, &routine4, NULL) != 0){return 1;}
    if (pthread_create(&p2, NULL, &routine4, NULL) != 0){return 2;}
    if (pthread_join(p1, NULL) != 0){return 3;}
    if (pthread_join(p2, NULL) != 0){return 4;}
    return 0;
}

////////~~~~~~~~END>
