#include "reptileType.h" 

void reptileType::print() const {
    animalType::print();
    std::cout << " , Breed: " << breed;
}

reptileType::reptileType(std::string n, std::string b) :animalType(n) {
    breed = b;
}


