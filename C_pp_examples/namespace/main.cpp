#include <iostream>
using namespace std;

int t;
double u;

namespace expN {
    int x;
    char t = 'A';
    double u;
    void printResult();
}
using namespace expN;

int main() {
    int one;
    double t = 5;
    double three;

    cout << endl;
    cout << "I want to refer to the global variable 't', but other two other variables are named 't'" << endl;
    cout << "I'll have to use '::t' to get it, gloabal 't' is: " << ::t << endl << endl;

    cout << "I want to refer to 't' in expN, but other two other variables are named 't'" << endl;
    cout << "I'll have to use 'expN::t' to get it, 't' in expN is: " << expN::t << endl << endl;

    cout << "I want to refer to 't' for main(), but other two other variables are named 't'" << endl;
    cout << "I'll have to use 't' to get it, 't' in main() is: " << t << endl << endl;

    printResult();

  return 0;
}
 //------------------------------------------------------------------------------------------------------
void expN::printResult() { // definition of a function is a member of the namespace
// usually it is written outside the namespace
// here, it could have been defined as printResult because no other identifiers have the same named
// but, it is safer to use expN::function()  then define it, youll be able to use it if you said "using"

cout << "This function was called, and it seems to be working." << endl;

}