/*
    using these objects has to have a set up like this in main()
    fyi, 1ns = 1s e -9    ...   1 / 1,000,000,000
         1ms = 1s e -3    ...   1 / 1,000    (milli not micro) ...this one is probably easiiest...multiply by 1000
         or whatever unit you want, just change the ratio in obj and main()  and the cast
*/

#include "customClock.h"

// pick a type, change based on OS
//std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<double, std::ratio<1, 1000000000>>> g_START;
//std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<double, std::ratio<1, 1000000000>>> g_STOP;

std::chrono::time_point<std::chrono::system_clock> g_START = std::chrono::system_clock::now(); // get current time
std::chrono::time_point<std::chrono::system_clock> dummy = std::chrono::system_clock::now();  // get current time
std::chrono::duration<double> g_DURATION = dummy - g_START;                      // initialize...should be about 0
double g_CURRENT = 0; // just to initialize, should hold current time based on duration in ns


void UPDATE(std::chrono::duration<double>& g_DURATION, double& g_CURRENT); // use before and after each obj life-cycle
void checkMe();
void objDemo();


//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    std::cout << "\n                                                          ~ BEGIN: { " << g_CURRENT << "  ns } ~\n";
    UPDATE(g_DURATION, g_CURRENT);
    
    // how to calibrate
    //checkMe();
    //UPDATE(g_DURATION, g_CURRENT);
    //checkMe();
    //currentTime(g_DURATION, g_UPDATER, g_CURRENT);

    //objDemo(); // good to check all features, could get a duration in easily if needed

    // check a loop
    long long int burner;
    customClock clock("clock");
    clock.printTimeStamp();
    for (long long int i = 0; i < 999'999'999; i++)
    {
        burner = 3;
    }
    clock.printTimeStamp();


    UPDATE(g_DURATION, g_CURRENT);
    std::cout << "\n                                                            ~ END: { " << g_CURRENT << "  ns } ~\n";
    
    std::cout << "\n ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n";
    return 0; 
}

//--------------------------------------------------------------------------------------------------------------------------
void UPDATE(std::chrono::duration<double>& g_DURATION, double& g_CURRENT)
{
    std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
    g_DURATION =  (current - g_START); // updates to new current time, based on ellapsed
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = std::chrono::duration_cast<std::chrono::nanoseconds>(g_DURATION);
    g_CURRENT = caster.count();
    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    std::cout << "\n ~ check { " << g_CURRENT << "  ns } ~\n";
}

//--------------------------------------------------------------------------------------------------------------------------
void checkMe()
{
    int test = 0;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // calibrate
    for (int i = 0; i < 4000000; i++)
    {
        test = test + 1;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void objDemo()
{
    customClock timer_1("timer_1");
    double timeKeeper;
    int tester;
    std::cout << std::fixed << std::showpoint << std::setprecision(1);

    std::cout << "\n---------------------------------\n";
    std::cout << "use the obj for a running time stamp:";
    timer_1.printTimeStamp();

    std::cout << "\ncheck the internal calibration of the object:";
    timer_1.calibrate();

    std::cout << "\n see how long this loop takes to iterate through 5,000,000 items:\n";
    timeKeeper = timer_1.runningTime();

    std::cout << "\nthe current time is: " << timeKeeper << "  ns";
    for (int i = 0; i < 5000000; i++)
    {
        tester = i;
    }
    timeKeeper = timer_1.runningTime();
    std::cout << "\nthe current time is: " << timeKeeper << "  ns";

    std::cout << "\nanother time stamp:";
    timer_1.printTimeStamp();

    std::cout << " \n---------------------obj test complete, function at end, it will be destroyed now\n";
    
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------