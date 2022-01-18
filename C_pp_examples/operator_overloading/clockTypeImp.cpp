#include "clockType.h"


//--------------------------------------------------------------------------------------------------------------------------
void clockType::setTime(int hours, int minutes, int seconds) {

    if ( 0 <= hours && hours < 24) hr = hours;     // just checks for valid values
    else hr = 0;

    if ( 0 <= minutes && minutes < 60) min = minutes;
    else min = 0;

    if ( 0 <= seconds && seconds < 60) sec = seconds;
    else sec = 0;
} // end clockType::setTime()


//--------------------------------------------------------------------------------------------------------------------------
void clockType::printTime() const { 

    if (hr < 10) std::cout << "0";
    std::cout << hr << ":";

    if (min < 10) std::cout << "0";
    std::cout << min << ":";

    if (sec < 10) std::cout << "0";
    std::cout << sec;
} // end clockType::printTime()


//--------------------------------------------------------------------------------------------------------------------------
bool clockType::operator ==(const clockType& otherClock) const {

    return (hr == otherClock.hr && min == otherClock.min && sec == otherClock.sec);
}



