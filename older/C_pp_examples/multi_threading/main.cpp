/*
    threads are good because it can optimize or let you do 2 things at once (most machines have multiple threads)
    if you abuse threads too much, the performance will suffer...100% utilization
*/

#include <iostream>
#include <thread>
#include <chrono>


bool g_FINISHED = false;

void doWork()
{
    std::cout << "\nthis is thread: " << std::this_thread::get_id();
    while (!g_FINISHED)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "\nenter some data, do it now:";
    }
}


int main() // everything starts on a main thread
{
    std::cout << "this is the main thread: " << std::this_thread::get_id();
    std::thread worker(doWork); // the thread takes a function pointer, then starts the thread
    
    std::cout << "\nEnter some data: ";
    std::cin.get(); // this will wait until data is entered
    g_FINISHED = true; // this will kill the thread

    worker.join(); // if you want to wait for thread to complete, or just let it run paralell for multi thread
    // thread joining is like wait in c#.....block current thread until worker is done

    std::cout << "\nthanks\n";

    std::cout << "\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0; 
}