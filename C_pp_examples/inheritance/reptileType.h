
#ifndef H_reptileType
#define H_reptileType

#include "animalType.h"

class reptileType: public animalType {

    public:
        void print() const;
        void setBreed(std::string b) {breed = b;}
        reptileType(std::string n = "", std::string b = "");
    
    private:
        std::string breed;
};

#endif