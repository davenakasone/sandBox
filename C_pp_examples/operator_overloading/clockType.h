#ifndef H_clockType
#define H_clockType

#include <iostream>

class clockType { 

    public:
        void setTime(int hours, int minutes, int seconds); 
        void getTime(int& hours, int& minutes, int& seconds) const {hours = hr; minutes = min; seconds = sec;}
        void printTime() const; 

        void incrementSeconds() { sec++; if (sec > 59) {sec = 0; incrementMinutes();} }
        void incrementMinutes() { min++; if (min > 59) { min = 0; incrementHours();} }
        void incrementHours()   {hr++; if (hr > 23) hr = 0;}

        bool equalTime(const clockType& otherClock) const {return (hr == otherClock.hr && min == otherClock.min && sec == otherClock.sec);}
        int getHours() const     {return hr;}                           // inline, saves memory
        int getMinutes() const   {return min;}
        int getSeconds() const   {return hr;}

        bool operator ==(const clockType& otherClock) const; // to overload equality operator

        clockType(int hours = 6, int minutes = 6, int seconds = 6) { setTime(hours, minutes, seconds);} 
        // constructor w parameters

    private:
        int hr;
        int min;
        int sec;
};
#endif