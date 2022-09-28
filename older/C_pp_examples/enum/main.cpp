#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cctype>
using namespace std;

int main() {
    enum courses {ALGEBRA, BASIC, PYTHON, CPP, PHILOSOPHY, ANALYSIS, CHEMISTRY, HISTORY};
    courses registered;
    char ch1, ch2;
    cout << "Enter two characters to match class: ";
    cin >> ch1 >> ch2;
    cout << endl;

    switch (ch1) {
        case 'a':
                if (ch2 == 'l') registered = ALGEBRA;
                else registered = ANALYSIS;
                cout << registered << endl;
                break;
        case 'b':
                registered = BASIC;
                cout << registered << endl;
                break;
        case 'c':
                if (ch2 == 'h') registered = CHEMISTRY;
                else registered = CPP;
                cout << registered << endl;
                break;
        case 'h':
                registered = HISTORY;
                cout << registered << endl;
                break;
        case 'p':
                if (ch2 == 'y') registered = PYTHON;
                else registered = PHILOSOPHY;
                cout << registered << endl;
                break;
        default: cout << "don't have this class..." << endl;
    } // end switch
  return 0;
}