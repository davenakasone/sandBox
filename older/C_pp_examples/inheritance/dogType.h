
#ifndef H_dogType
#define H_dogType

#include "petType.h"

class dogType: public petType {

    public:
        void print() const;
        void setBreed(std::string b = "") {breed = b;}
        dogType(std::string n = "", std::string b = "");

    
    private:
        std::string breed;
};

#endif