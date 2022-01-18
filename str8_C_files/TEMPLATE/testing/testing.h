/*
    route unit tests
    develop unit tests independently
*/

#ifndef H_test
#define H_test

void test_selector(int selection);
void waitEnterClear();

// test unit "tu"
void testBench();            // selection 0, test bench of program features, temporary use
void tu_dateTimeStamp();     // selection 1, test dateTimeStamp()
void tu_makeNumbers();       // selection 2, test makeNumbers.c 

#endif

////~~~~END>  test.h
