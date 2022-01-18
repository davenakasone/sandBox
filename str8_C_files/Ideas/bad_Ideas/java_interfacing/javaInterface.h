/*
    the API for feeding C data to the java code
*/

#ifndef H_javaInterface
#define H_javaInterface

#define VALID 1      // struct is ready to read
#define INVALID 0    // struct not ready to read
#define THREADZ 2    // 1 to run engine, 1 main thread implied

#include "LocationStruct.h"

int GPS_runEngine;

int GPS_initializeEngine(const char* serialPath);
int GPS_readLocationStruct(Location * ptr);
int GPS_haltEngine(void);

#endif

////////~~~~~~~END>  javaInterface.h
