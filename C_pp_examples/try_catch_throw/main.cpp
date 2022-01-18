#include <iostream>
#include <string>

int main() {

    int dividend;
    int divisor = 1;
    int quotient;
    std::string inpStr = "input is in failed state.";

    try {
        std::cout << "\nEnter dividend: ";
        std::cin >> dividend;
        std::cout << "Enter divisor: ";
        std::cin >> divisor;

        if (divisor == 0) throw divisor;
        else if (divisor < 0) throw std::string("Negative divisor"); // I didn't know you could make a string like that
        else if (!std::cin) throw inpStr;

        quotient = dividend / divisor;
        std::cout << "{ " << dividend << " } / { " << divisor << " } = { " << quotient << " }\n";
    }

    catch(int x) {
        std::cout << "{ " << dividend << " } / { " << x << " }   ...fuck no bro\n"; // didn't know it could access other variables
    }

    catch(std::string s) {
        std::cout << s << " not allowed\n";
    }

return 0;
}