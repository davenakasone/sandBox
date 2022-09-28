#include "petType.h"

void petType::print() const {
    std::cout << "Name: " << name;
}

petType::petType(std::string n) {
    name = n;
}