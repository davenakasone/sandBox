apple has a lot of POSIX shortcomings, use the rigged .h files as needed

This directory contains foundational information for 
using the C programing language to leverage operating system
capabilities in programs of interest.

The applications are directly related to embedded 
programming and real-world programming.
Originally made for UNIX, the C programming language 
is the mother/father of all languages (except assembly and stuff like that).
So, Linux applications are just as relevant.

An underated youTube tutor provided the instruction:
https://www.youtube.com/channel/UC6qj_bPq6tQ6hLwOBpBQ42Q/playlists
but
compile all the code in single files with your favorite (gcc or clang) and run ./a.out
 $ clang example.c      ... $ ./a.out
 make and run by .sh if needed   ,  may need extra compile instructions, or multiples


"Unix Processes in C" ...also for windows, don't use <unistd.h>
multiprocess programming can do a lot
{codeVault_tutorials/UnixProcesses/up*}
    1  : the fork() function
    2  : waiting for processes to finish, use wait()
    3  : visualize the fork() call {understand the memory}
    4  : process IDs     getpid() getppid()
    5  : fork multiple times 
    6  : communicating between processes, pipe()
    7  : use pipe() and fork() together
    8  : FIFO as named pipe
    9  : FIFO to communicate between processes
    10 : 2 way pipes, 2 way communication between process (child/parent)...use 2 pipes
    11 : execute another program in your program, exec__() family
    12 : get exit status
    13 : redirect stdout
    14 : program execution vs script execution   { exec__() vs .sh }
    15 : signals in C
    16 : control execution of process, SIGCONT and SIGSTOP
    17 : move process; background <-> foreground
    18 : handle signals, prevent process from getting sent to background
    19 : communicate between processes with signals
    20 : send array through a pipe, child to parent
    21 : send string through pipe, child to parent
    22 : simulate the pipe operator "|"
    23 : working with multiple pipes
    24 : execute other programs in your program, exec__()
    25 : waitpid()
    26 : more with multiple forks


"Unix Threads in C"
also useful...add "-pthread" with your #include <pthread.h>
{codeVault_tutorials/UnixThreads/ut*}
    1  : introduction to threads
    2  : difference between processes and threads
    3  : race conditions
    4  : pthread_mutex
    5  : create threads in a loop
    6  : get return value from pthread_join()
    7  : pass arg to thread, dynamic or static possible
    8  : practical example, sum array with threads
    9  : pthread_trylock vs pthread_lock  ...trylock not guarunteed
    10 : conditional variables, pthread_cond_wait
    11 : conditional variables, pthread_cond_signal + _broadcast
    12 : practical example pthread_trylock()
    13 : pthread_exit vs return
    14 : pthread_barrier     see the .h for macOSX
    15 : practical example of pthread_barrier   see the .h for macOSX
    16 : looking into pthread_t     see ex1() for better return value
    17 : detached thread
    18 : static initializers for obj's
    19 : deadlocks
    20 : recursive mutex
    21 : semaphore basics    {apple fucks you on this, use the .h}
    22 : semaphore example, login queue
    23 :
    24 :
    25 :
    26 :
    27 :
    28 :
    29 :

    99 : an application of the detached thread and timing {best on Linux}


"Basics/General concepts in C"
any basic or good to know procedures
{codeVault_tutorials/General/gen*}
    1  : timers   ...tons in <time.h> , choose wisley
    2  : round, ceil, floor  <math.h> , set comma for large numbers
    3  : <errno.h>   TODO
    


"Structs in C"
structs, making them classes, and data types
{codeVault_tutorials/Structs/stc*}
    1  : typedef
    2  : struct is user defined type to hold variables
    3  : return or pass a struct
    4  : 

