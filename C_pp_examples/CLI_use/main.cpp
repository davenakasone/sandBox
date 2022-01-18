// David Nakasone

// 1. this only works in the CLI
// 2. compile the file "clang++ -std=c++14 -Wall main.cpp" 
// 3. run the file (remeber name of target or just use ./a.out)   "./a.out 5278 3149587"

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <bitset>
#include <stack>
#include <sstream>
using namespace std;
// clang++ -std=c++14 -Weverything main.cpp   ./a.out 5278 3149587


//prototypes
void runLoopMethod(long& multiplicand, long& multiplier, long& iterationCount, long& answer);
void runRussianMethod(long& multiplicand, long& multiplier, long& iterationCount, long& answer);
void printResult(long& iterationCount, long& answer);



//--------------------------------------------------------------------------------------------------------------------------
// @ breif: primary function used to control the program
// @ call(s):
// @ param():
// @ return(s): 0 if successful
//--------------------------------------------------------------------------------------------------------------------------
int main (int argc, const char** argv) {   // should this be char*  or char** ?
 long multiplicand = 0; // the first user input, integer to multiply with multiplier
 long multiplier = 0; // the second user input, integer to multiply with multiplicand
 long iterationCountLoop = 0; // counts times through "LoopMethod"
 long iterationCountRussian = 0; // counts times through "RussianMethod"
 long answerLoop = 0; // product of "LoopMethod"
 long answerRussian = 0; // product of "RussianMethod"
 bool proceed = true; // determines if input was good and program can continue, or program needs to stop

 multiplicand = atoi(argv[1]); // use the first CLA as the multiplicand
 multiplier = atoi(argv[2]); // use the second CLA as the multiplier
    
    if (argv[1] == NULL || argv[2] == NULL || argv[3] != NULL) {  // see if arguments are there. argv[0] for program ... argv[3] is the NULL
        cout << "Syntax error! Usage: extra01 int_1 int_2" << endl;
        proceed = false;
    } // end if

    if ( multiplicand <= 0 || multiplier <= 0) { // see if arguments are in range (positive integers)
        cout << "This program requires positive non-zero integers (floats will be truncated)" << endl;
        proceed = false;
    } // end if 

    if (proceed == true) {
        cout << "This program compares two multiplication methods" << endl;
        cout << "without using the multiplication operator..." << endl << endl;     // sample output uses "that doesn't" instrucitons say this

        cout << "For loop method..." << endl;
        runLoopMethod(multiplicand, multiplier, iterationCountLoop, answerLoop); // run loop method
        printResult(iterationCountLoop, answerLoop);

        cout << endl;

        cout << "Russian Multiplication Method..." << endl;
        runRussianMethod(multiplicand, multiplier, iterationCountRussian, answerRussian); // run russian method
        printResult(iterationCountRussian, answerRussian);
    } // end if


return (proceed) ? 0 : 1;  // returns 1 if there was an input problem, 0 if input is good
} // end main()



//--------------------------------------------------------------------------------------------------------------------------
// @ breif: runLoopMethod() has 4 formal reference parameters, it is designed to multiply by adding
// @ call(s): called by main(), does not call other functions
// @ param(multiplicand): number to be added to itself
// @ param(multiplier): set number of times to add
// @ param(iterationCount): keeps track of how many times  "multiplicand" was added to itself, should be multiplier
// @ param(answer): should be the product of the multiplicand and multiplier
// @ return(s): n/a, pass by reference
//--------------------------------------------------------------------------------------------------------------------------
void runLoopMethod(long& multiplicand, long& multiplier, long& iterationCount, long& answer) {
    for (iterationCount = 0; iterationCount < multiplier; iterationCount++) {
        answer = answer + multiplicand;
    } // end for
} // end runLoopMethod()




//--------------------------------------------------------------------------------------------------------------------------
// @ breif: runRussianMethod() has 4 formal reference parameters
// @ call(s): called by main(), does not call other functions
// @ param(multiplicand): 1 of 2 desired inputs to receive a product
// @ param(multiplier): 2 of 2 desired inputs to receive a product
// @ param(iterationCount): keeps track of how many times  the peasent sequence ran
// @ param(answer): should be the product of the multiplicand and multiplier
// @ return(s): n/a, pass by reference
//--------------------------------------------------------------------------------------------------------------------------
void runRussianMethod(long& multiplicand, long& multiplier, long& iterationCount, long& answer) {
long matrix[100][2]; // take 2,147,483,647 / 2, have to leave some extra room
long rowIndex = 1; // LCV for rows
long colIndex = 0; // LCV for cols
int lastEntry = 0; // find last *2 or /2 row index

        //initialize
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 2; j++) {
                    matrix[i][j] = 0;
                } // end for
            } // end for

    matrix [0][0] = multiplicand; // set multiplicand to row 0, col 0
    matrix [0][1] = multiplier; // set multiplier to row 0, col 1

    do { // need to run at least once
        matrix[rowIndex][colIndex] = matrix[rowIndex-1][colIndex] / 2; // divide last entry by 2, integer gets floor
        rowIndex++; // increment
        lastEntry++; // find last entry
    } // end do
    while (rowIndex < 100 && matrix[rowIndex-1][colIndex] != 1); // stops at end or when 1 is obtained
    
    rowIndex = 1; // reset
    colIndex = 1; // position for other column

    do {
        matrix[rowIndex][colIndex] = matrix[rowIndex-1][colIndex] * 2; // double last entry
        rowIndex++;
    } // end do
    while (rowIndex < 100 && matrix[rowIndex][colIndex-1] != 0); // stops when it finds blanks or reaches end

    rowIndex = 0; // reset , going to sweep entire array now
    colIndex = 0;  // reset, going to sweep entire array now

    while (rowIndex < 100) {
        if ((matrix[rowIndex][colIndex] % 2) == 0){
            matrix[rowIndex][colIndex] = 0; // sets even rows to 0
            matrix[rowIndex][colIndex+1] = 0;
        } // end if
        rowIndex++;
    } // end while

    colIndex = 1;  // need second column

    for (rowIndex = 0; rowIndex <= lastEntry; rowIndex++) {
        if (matrix[rowIndex][colIndex] != 0) {
            answer = answer + matrix[rowIndex][colIndex];
        } // end if
        iterationCount++;
        
    } // end for
} // end runRussianMethod



//--------------------------------------------------------------------------------------------------------------------------
// @ breif: printResult() has 2 formal reference parameters, I think they have to be reference for argv/argc
// @ call(s): called by main() x2, does not call other functions, looks like it will need 2 calls
// @ param(iterationCount): keeps track of how many times  each method...gets 2 passes
// @ param(answer): should be the product of the multiplicand and multiplier and the same for each method
// @ return(s): n/a, just prints result
//--------------------------------------------------------------------------------------------------------------------------
void printResult(long& iterationCount, long& answer) {

    cout << "The number of times through the loop: " << iterationCount << endl;
    cout << "Answer: " << answer <<endl;

} // end printResult()
