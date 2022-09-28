/*
    c++ provides support to handle exceptions via a hierarchy of classes
    class "exception" is base classes
    inside this class is the what() function ... it returns a string with an appropriate message
    any derived class of "exception" overrides what() function
    "logic_error" and "runtime_error" are derived from "exception" use #include<stdexcept>

    to deal with logical errors (string subscript out of range, invalid arguments, ect), you have a few classes derived from 
    "logic_error"  ..."invalid_argument"  for illegal argument used to call functions
                   ..."out_of_range" for string subscript out of range errors
                   ..."length_error" for lengths greater than maximum allowable characters for a string object
    
    if new can't allocate memory space, it throws "bad_alloc"
    "runtime_error" deals with these erros that only show up during program execution
            ..."overflow_error" for arithmetic overflow errors
            ..."underflow_error" for arithmetic underflow errors
    
    here, if exception will be thrown automatically, don't throw it again in your try block
*/
#include <iostream>
#include<stdexcept>
#include<string>

int main() {
    std::string sentence;
    std::string str1, str2, str3;

    try {
        sentence = "testing string exceptions";
        std::cout << "\nsentence = { " << sentence << " }";
        std::cout << "\nsentence.length() = { " << static_cast<int>(sentence.length()) << " }";

        str1 = sentence.substr(8, 20);
        std::cout << "\nstr1 = { " << str1 << " }";

        str2 = sentence.substr(28, 10);
        std::cout << "\nstr2 = { " << str2 << " }";

        str3 = "Exception handling. " + sentence;
        std::cout << "\nstr3 = { " << str3 << " }";
    }

    catch(std::out_of_range re) {
        std::cout << "\nthe out_of_range catch: { " << re.what() << " }\n";
    }
    catch(std::length_error le) {
        std::cout << "\nthe length_error catch: { " << le.what() << "}/n";
    }
  
return 0;
}