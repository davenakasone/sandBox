#include "animalType.h"

void animalType::print() const {
    std::cout << "Name: " << name;
}

animalType::animalType(std::string n) {
    name = n;
}