/*
    where data of interest would be harvested from input stream 
    provided by Coperincus2 and wiringPi/wiringSerial
*/

#ifndef H_LocationStruct
#define H_LocationStruct

#include "programMacros.h"

struct Location
{
    float data[ELEMENTS_LOCATION_STRUCT];
    int isReady;
};
typedef struct Location Location;


void metInit(Location* ptr);
void metCopy(const Location* original, Location* duplicate);
void metPrint(const Location* ptr);

#endif

////////~~~~~~~~END>  LocationStruct.h
