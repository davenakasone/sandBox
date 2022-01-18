#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int main() {
    const int size = 25;
    double list[size];
    double selector;
    double arraySum;
    double maxElement;

    cout << fixed << setprecision(0) << endl;

    srand((unsigned)time(NULL));
    selector = rand();
    
    for (int i = 0; i < size; i++) list[i] = rand() / 10000000;
    cout << "The array is: [ ";
    for (int i = 0; i < size; i++) cout << list[i] << " ";
    cout << " ]" << endl;

    for( double num: list) arraySum = arraySum + num; // this loop is very useful
    // for each "num" in list[], variable "num is initialized to list[0] then goes until list[size]"
    // "num" is assigned contents of each element...not the index value
    // loops starts at index 0 and goes until index of last element....traverses entire array
    cout << "The sum of the elements is: " << arraySum << endl;

    //compare to:
    arraySum = 0;
    for (int i; i < size; i++) arraySum = arraySum + list[i];
    cout << "The sum of the elements is: " << arraySum << endl;

// can also use auto decleration in range-based for loop
    for (auto num : list) maxElement = (maxElement < num) ? num : maxElement;
    cout << "The largest element is: " << maxElement << endl;
 
 return 0;
}

// for (dataType identifier : arrayName) { statements.... }

// not auto range for loop if array is a formal parameter... not really an array, just memory address


