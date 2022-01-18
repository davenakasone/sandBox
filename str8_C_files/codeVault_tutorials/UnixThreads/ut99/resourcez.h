/*
    contains the:
        macros
        global variables
        specific function declarations
    
    just include this header to take everything needed for program
*/

#ifndef H_resourcez
#define H_resourcez


#include <errno.h>       // EBUSY , ETIMEDOUT
#include <pthread.h>     // threading structs and methods
#include <stdbool.h>     // bool , true , false
#include <stdlib.h>      // rand() , srand()  ,  NULL , EXIT_SUCCESS
#include <stdio.h>       // __func__ , printf()
#include <string.h>      // memset() , strnlen()
#include <sys/time.h>    // gettimeofday()
#include <time.h>        // time()  ,  struct timespec , struct timeval
#include <unistd.h>      // usleep() ,

// experiment here, only turn ONE on at a time
//#define SM_1 -1111     ////~~~~{on|off}
//#define SM_2 -2222     ////~~~~{on|off}
#define SM_3 -3333     ////~~~~{on|off}
//#define SM_88 -8888    ////~~~~{on|off}

// turn on create time between read calls
#define MAKE_READ_DELAY 12345    ////~~~~{on|off}

#define INIT_INT -999          
#define GOOD 69                
#define US_PER_SEC 1000000      // do not adjust 
#define NS_PER_US 1000          // do not adjust        
#define DELAY_MAX_US 2000000    
#define READ_DELAY_US 9999      
#define WAITING_US 1000         
#define START 65               
#define STOP 90             
#define REPS 3                 
#define STR_SIZE 4              

#ifdef SM_88

    typedef struct stateMachine_t
    {
        int idx;
        bool readReady;
        bool runFlag;
        char data[STR_SIZE];
    } stcSM;

#else

    typedef struct stateMachine_t
    {
        int idx;
        bool readReady;
        bool runFlag;
        char data[STR_SIZE];

        pthread_t engineThread;
        pthread_attr_t engineAttr;
        pthread_cond_t engineCond;
        pthread_condattr_t engineCondAttr;
        pthread_mutex_t engineMutex;
    } stcSM;

#endif


stcSM sM;                 // global instance of struct
int gv_status;            // global variable
struct timespec timer;    // global struct "timespec" type

// make an attempt with _trylock()
#ifdef SM_1
    int initializeEngine1();
    int readEngine1();                 
    void* stateMachine1(); 
    int haltEngine1();
#endif

// wait and signal
#ifdef SM_2
    int initializeEngine2();
    int readEngine2();                 
    void* stateMachine2(); 
    int haltEngine2();
#endif

// wait and signal
#ifdef SM_3
    int initializeEngine3();
    int readEngine3();                 
    void* stateMachine3(); 
    int haltEngine3();
#endif

// don't even use threads if task is small
#ifdef SM_88
    int initializeEngine88();
    int readEngine88();                 
    void stateMachine88(); 
    int haltEngine88();
#endif

// support
void resetStruct();
void usleep_proper(int time_us);
char getChar();


#endif

////////~~~~~~~~END>  resourcez.h
