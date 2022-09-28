#include "clockType.h"

int main() {

    clockType myClock(8, 23, 34); // object made
    clockType yourClock(4, 5, 30); // object made

    myClock.printTime(); // print just to check
    myClock.incrementSeconds(); // increment one second
    if (myClock.equalTime(yourClock)) std::cout << "\nthey are equal\n";
    // these statements do their jobs

    /*
        if you can use insertion <<, increment ++, and relationals to compare, the class will be a lot more flexible
        cout << myClock;
        myClock++;
        if (myClock ==  yourClock)      would have done same thing as above

        you can only use the built-in operations on class objects (assigment and member selection)
        to apply the other operators directly, C++ lets you operator overload

        ie / works by having both operands of integer, double, float, ect
                clearly this operator has one definition when both operands are integers and other definitions for different cases
                    the data types (in operands) determine the definition of the operator
        
        or << >> being stream insertion, stream extraction or left shift and right shift
                all examples of overloading the operator
        
        even + and - will make a different result based on data types of operands

        C++ wants you to overload operators so you can get them to work with predicatble behavior
        the only thing is, you can't create new operators
        most of the operators can be overloaded to manipulate class objects

        you need to write functions (header and body) to overload operators...indicate what should be performed
        the name of the function starts operator

            returnType operator operatorSymbol(formal parameter list) {}       ...has to be value returning

        this is how you explicitly overload operator to work with class objects
        you get the same consice expressions applied to your objects (or any other data type...just don't conflict)
        try to keep it user defined data. don't be trying to rewrite definitions for integers, doubles, ect
        to overload operator for a class:
            1) include statement to declare the function prototype to overload the operator in definition of the class
            2) write the definition of the operator function
        follow rules when including operator function in class definition....in a few more examples

        when overloading an operator:
        1) can't change precedence of an operator
        2) associativity can't be changed (left to right > right to left won't work)
        3) default parameters can't be used with an overloaded operator
        4) you can't change the number of parameters an operator is supposed to take
        5) can't create new operators, only existing operators can be overloaded
        6) .   .*   ::  ?:   sizeof       can't be overloaded
        7) can't change meaning of how operator interacts with built in data types
        8) operators can be overloaded for objects of the user-defined types OR for a combonation of objects of the user defined 
        types and objets of the built-in type
    */

    // == is overloaded to take a clockType object

    clockType anotherClock(8, 23, 35);

    if (myClock == anotherClock) std::cout << "\nboth clocks are equal\n"; // a lot more compact

return 0;
}