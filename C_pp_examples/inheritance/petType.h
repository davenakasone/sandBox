#ifndef H_petType
#define H_petType

#include <string>
#include <iostream>

class petType {

    public:
        void print() const;
        petType(std::string n = "");
    
    private:
        std::string name;
};
#endif