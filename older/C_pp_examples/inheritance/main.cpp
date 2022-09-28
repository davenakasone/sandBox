/*

    as a parameter, a class object can be passed by value OR reference
    normally you match types of actual and formal parameters
    C++ lets you pass an object of a derived class to a formal parameter of the base class type
    this is only allowed because the base class has the derived class as the foundation
    the formal parameter recognizes the base class portion and lets it pass

    consider cases where formal parameter is a reference or a pointer

    in most cases, you want the "dynamic" or late binding that virtual functions provide

*/

#include "dogType.h"
#include "reptileType.h"

void callPrint1(petType& obj); // formal reference parameter is of petType...takes obj of petType or dogType
void callPrint2(animalType& obj); // with virtual function in base class, it is done correct
void callPrint3(animalType *pointer); // also applies to pointers
void callPrint4(animalType obj); // value parameter, going to have same problem, like #1
/*
    if formal parameter of classType is a reference or pointer, and virtual function of base class is used,
    you can effectivley pass a derived class object as an actual parameter (#2 and #3)...#1 makes a mess

    if a formal parameter is a value parameter, value of actual parameter is copied into the formal parameter
    using passing a derived object (#4) will result in behavior like (#1)...member variables of derived class that can't
    be used will not print

    This doesn't work the other way around. You can't pass the object of the base class type to a formal parameter
    that is looking for something of the derived class type...it is missing parts
*/

//--------------------------------------------------------------------------------------------------------------------------
int main() {

    petType petObj("Lucky"); // an object of petType...name is lucky
    dogType dogObj("Tommy", "German Shepherd"); // and object of dogType...name is Tommy, breed is GS

    std::cout << std::endl;
    petObj.print();
    std::cout << std::endl;
    dogObj.print();

    std::cout << "calling function_1 to print...\n";
    callPrint1(petObj);
    std::cout << std::endl; 
    callPrint1(dogObj);
    std::cout << "    ... what happend to 'Breed: German Shepherd' ?" << std::endl;
    //what happened here is "static binding" or "early binding"

    /*
        petObj = dogObj; is legal because derived object has >= member variables than base
        dogObj = petObj; is wrong....compiler can't see 2 member variables because base class only has 1, 
        since it doesn't know what to do, a "slicing problem" occured

        also, petObj.setBreed("Husky"); is wrong

        C++ does have a way to use pointer so you can handle objects from either class without losing derived object properties
            see end of main() #5
    */




    // this is what virtual functions are for

    animalType animalObj("Iggy"); // an object of petType...name is lucky
    reptileType reptileObj("Snap", "Salt-Water Crocidile"); // and object of dogType...name is Tommy, breed is GS

    std::cout << "****************************************************************" << std::endl;
    animalObj.print();
    std::cout << std::endl;
    reptileObj.print();

    std::cout << "\ncalling function_2 to print...\n";
    callPrint2(animalObj);
    std::cout << std::endl; 
    callPrint2(reptileObj);
    std::cout << "       ...with a virtual function in base class, all is preserved for derived class obj";




    // also applies if formal parameter is a pointer to a class
    // pointer of derived class is passed as an actual parameter

    std::cout << "\n****************************************************************" << std::endl;
    animalType *pointerA; // a pointer to an object of class animalType
    reptileType *pointerR; // a pointer to an object of class reptileType

    pointerA = new animalType("slippy"); // the pointer that was pointing at an object for animalType now points to an object
    pointerR = new reptileType("Pepe", "Frog"); // pointer that was pointing at an object for reptileType now points to an obj

    pointerA->print();
    std::cout << std::endl;
    pointerR->print();
    
    std::cout << "\ncalling function_3 to print...\n";
    callPrint3(pointerA);
    std::cout << std::endl; 
    callPrint3(pointerR);
    std::cout << "    ... all preserved with pointer, another use of the virtual function\n";


    // passing to a value function, if base class and derived class have different memember variables, only takes base
    animalType mouse("Mickey"); // an object of animalType created
    reptileType jihadist("Osama", "Snake"); // an object of reptileType created
    std::cout << "****************************************************************" << std::endl;
    mouse.print();
    std::cout << std::endl;
    jihadist.print();

    std::cout << "\ncalling function_4 to print...\n";
    callPrint4(mouse);
    std::cout << std::endl;
    callPrint4(jihadist);
    std::cout << "     ... have the same problem as function_1\n";



    // for handling derived object through base object type, without losing properties of the derived object ...use pointers
    animalType *animalP;
    reptileType *reptileP;
    std::cout << "****************************************************************" << std::endl;
    reptileP = new reptileType("Gieco", "Lizard");
    reptileP->setBreed("Gecco");

    animalP = reptileP; // copies value reptileP into animalP even though class type different...it just points
    // look what happens when you print:

    callPrint3(animalP); // nice work around if needed


return 0;
}



//--------------------------------------------------------------------------------------------------------------------------
void callPrint1(petType& obj) {
    obj.print(); // only executes base class function here
    // base class was bound to callPrint() at compile time
    // since obj is associated with class petType, compiler requires binding to associate function call
}


//--------------------------------------------------------------------------------------------------------------------------
void callPrint2(animalType& obj) {
    obj.print();
}


//--------------------------------------------------------------------------------------------------------------------------
void callPrint3(animalType *pointer) {
    pointer->print();
}


//--------------------------------------------------------------------------------------------------------------------------
void callPrint4(animalType obj) {
    obj.print();
}




//--------------------------------------------------------------------------------------------------------------------------