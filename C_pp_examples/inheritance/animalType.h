#ifndef H_animalType
#define H_animalType

#include <string>
#include <iostream>

class animalType {

    public:
        virtual void print() const; // a virtual function...you only need to put it in the base class
        // virtual in base class means base class object can use the derived classe's definition

        //void print() const;
        animalType(std::string n = "");
    
    private:
        std::string name;
};
#endif