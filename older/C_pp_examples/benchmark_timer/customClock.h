/*

    make the constructor and destructor private if you are going to derive on top of this

    This seemed to all work out, use that hot toggle on stop & duration

    I can't find a way to make a running total of the time_points, or even output a specific time point in mili/nano
    it made everything simple, but doesn't provide a timeline
    I guess you could chain them together and pass durations...not looking good
    
    you will want to run this with at least 2 objects (or use the set up like main)

    put one object at the beginning of main...the start time of the overall program can be kept ... and stop time
    this can be used to make sure the measurements are at least reasonable

    for the functions you want to time, inject the second object, start the time, stop the time, and see difference

    for pure measurement through construction and destruction, use
    https://repl.it/@davenakasone/20200607-timer#myTimer.h            see the myTimer.h and op2() example
*/
#ifndef H_customClock
#define H_customClock

#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <string>
#include <thread>

// extern std::chrono::time_point<std::chrono::system_clock> g_START; // this might be the ticket
// just going to pass this by the constructor

extern std::chrono::time_point<std::chrono::system_clock> g_START; // need to make these 3 globals available
//extern std::chrono::duration<double> g_DURATION;
extern double g_CURRENT;

//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
//--------------------------------------------------------------------------------------------------------------------------

class customClock // adjust for any unit, chose miliseconds here
{
    public:
        double runningTime();        // can receive the time stamp as a double if obj is at point of interest
        void printTimeStamp();       // begin, end, duration
        void calibrate();          // check a 1sec pause and see if it is close, don't forget / by 1,000,000,000 

        customClock(const std::string& name); // defualt construtor (uses externs)
        ~customClock(); // destructor, won't be used much, can be used by life-cycle (adjustment needed)


        //double getStart_ns();      //' should return static running creation time of object
        //double getDuration_ms();   // will not automatically stop, just returns current difference between start and stop
        //void setStart();         //' returns start time that user initialized the object at...no need for manual start
        
        //double getStop_ms(); // don't call unless you stopped the clock ... no use if you can't get as a double
        //void setStop(); // returns time that user stoped the object at

        //void reset();            // can reset to time a different point in the program...do this later, just use new obj now
        
        // also serves as default construtor, must have these 3 parameters to work
        //custmClock(const std::chrono::time_point<std::chrono::system_clock>& g_START,
                   //std::chrono::duration<double>& g_DURATION, std::string& name);           

    private:
        //std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<double, std::ratio<1, 1000000000>>> startTime;
        //std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<double, std::ratio<1, 1000000000>>> stopTime;
        //std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<double, std::ratio<1, 1000000000>>> creationTime;
        //std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<double, std::ratio<1, 1000000000>>> currentTime;
        //std::chrono::time_point<std::chrono::system_clock> stop;           // used when closing, quick toggle, multiple use
        
        std::chrono::time_point<std::chrono::system_clock> start;          // creation of obj > time = 0
        std::chrono::time_point<std::chrono::system_clock> current;        // transfer var (time Stamp, current duration)

        std::chrono::duration<double> internalDuration;                    // used for addition
        
        
        double start_ns;
        double duration_ns;
        std::string objName = "obj";
        
        //bool manualStart; add latter
        //double stop_ns;
};





//==========================================================================================================================
//--------------------------------------------------------------------------------------------------------------------------
//                                                      IMP                                                               //
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================



//--------------------------------------------------------------------------------------------------------------------------
customClock::customClock(const std::string& name) // constructor
{
    start = std::chrono::system_clock::now();     // the obj is tracks time from now
    current = std::chrono::system_clock::now();   // should be close to start time
    internalDuration = current - start;           // should be small, but keeps count imdiatley
    start_ns = g_CURRENT;                         // allows for a running clock
    objName = name;                               // get a name on the instance
}

//--------------------------------------------------------------------------------------------------------------------------
customClock::~customClock()
{
    // nothing to worry about here , no sneaky pointers to handle....could do a quick call to check out
    
    current = std::chrono::system_clock::now();
    internalDuration = current - start;
    
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);

    duration_ns = caster.count();
    
    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    std::cout << "\n ~ " << objName << " destroyed , began:  " << start_ns <<  "  ns  , ended: " <<  start_ns + duration_ns << 
    "  ,  lasted:  " << duration_ns << "  ns\n";
}

//--------------------------------------------------------------------------------------------------------------------------
double customClock::runningTime()
{
    current = std::chrono::system_clock::now();
    internalDuration = current - start;
    
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);

    duration_ns = caster.count();

    return (duration_ns + start_ns);
}

//--------------------------------------------------------------------------------------------------------------------------
void customClock::printTimeStamp()
{
    current = std::chrono::system_clock::now();
    internalDuration = current - start;
    
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);

    duration_ns = caster.count();

    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    std::cout << "\n ~ " << objName << "  , began:  " << start_ns <<  "  ns  , reported: " <<  start_ns + duration_ns << 
    "  ,  running:  " << duration_ns << "  ns\n";
}

//--------------------------------------------------------------------------------------------------------------------------
void customClock::calibrate()
{
    double before;
    double after;
    std::cout << std::fixed << std::showpoint << std::setprecision(1);

    std::cout << std::endl << objName ;
    before = runningTime();
    std::cout << "\n ~ calibrate , time  =  " << before << "  ns       pause 1 sec";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // calibrate
    after = runningTime();
    std::cout << "\n ~ after 1sec, time  =  " << after << "  ns";
    std::cout << "\ndifference:  " << after - before << "  ns\n";
}



//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
//--------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
//--------------------------------------------------------------------------------------------------------------------------





















/*
                    an abortion gone wrong
//--------------------------------------------------------------------------------------------------------------------------
double customClock::getStart_ms()
{
    if (!manualStart) // was not started manually, assumes creation time = start time
    {
        currentTime = std::chrono::high_resolution_clock::now(); // find the current time
        currentTime = currentTime - creationTime;
        
        blankTime = (fillerTime - fillerTime) + fillerTime; // just want the system starting time
        start_ms = blankTime.count() * 1000;
        return start_ms;
    }
    else
    {
        blankTime = (startTime - fillerTime) + fillerTime; // need manually selected start time
        start_ms = blankTime.count() * 1000;
        return start_ms;
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------
void customClock::setStart()
{
    startTime = std::chrono::high_resolution_clock::now(); // start the clock at the current time;
    manualStart = true;
}

//--------------------------------------------------------------------------------------------------------------------------
double customClock::getStop_ms()
{
    blankTime = stopTime - fillerTime;
    stop_ms = blankTime.count() * 1000;
    return stop_ms;
}

//--------------------------------------------------------------------------------------------------------------------------
void customClock::setStop()
{
    stopTime = std::chrono::high_resolution_clock::now();
}

//--------------------------------------------------------------------------------------------------------------------------
double customClock::getDuration_ms()
{
    durationTime = stopTime - startTime;
    duration_ms = durationTime.count() * 1000;
    return duration_ms;
}

//--------------------------------------------------------------------------------------------------------------------------
void customClock::reset()
{
    creationTime = std::chrono::high_resolution_clock::now(); // reset to current time, methods follow

    startTime = creationTime;                // starting point automatically set here, unless manual start used
    stopTime = creationTime;                 // just to hold a value
    currentTime = creationTime;              // just to hold a value

    durationTime = stopTime - startTime;     // just to hold a value
    transferTime = durationTime;             // just to hold a value

    duration_ms = 0;
    start_ms = 0;
    stop_ms = 0;
    manualStart = false;                     // assume no manual start
}

*/