#include "dogType.h" 

void dogType::print() const {
    petType::print();
    std::cout << " , Breed: " << breed << std::endl;
}

dogType::dogType(std::string n, std::string b) :petType(n) {
    breed = b;
}


