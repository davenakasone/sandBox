/*
    when and why to use a smart pointer
    there are: unique, shared, and weak
    they should handle memory allocation/deallocation for you

    try to use vs <new> <delete> ... especially <malloc> <free>

    unique_ptr is a smart pointer that models unique ownership, 
    at any time in your program there shall be only one (owning) pointer to the pointed object 
    that's why unique_ptr is non-copyable...can't share
    As long as you use smart pointers in a way that does not break the implicit contract they require 
    you to comply with, you will have the guarantee that no memory will be leaked, 
    and the proper ownership policy for your object will be enforced
    Raw pointers do not give you this guarantee
    unique_ptr is guaranteed to destroy the object they manage when they go out of scope

    shared pointer can be "shared" between multiple owners
    you can assign 1 raw pointer to multiple owners
    it keeps a count of all the owners ( any refereces) "<ptr_name>.use_count()"

    a weak pointer does not increase number of owners
    use to observe objects in memory, but won't keep object alive
    if nothing else needs to object, deallocaiton will occur
    a shared pointer will keep object alive
*/

#include <iostream>
#include <memory> // where smart pointers live

#include "demo_class.h"


void ex_unique1 ();
void ex_unique2 ();
void ex_shared1 ();
void ex_weak1 ();

int main (int argc, char* argv[], char* envp[])
{
    //ex_unique1 ();
    //ex_unique2 ();
    //ex_shared1 ();
    ex_weak1 ();

    printf("\n\n\t\t ~ ~  ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


void ex_unique1 ()
{
    printf("\n%s()\n", __func__);
    int varInt = 333;

    std::cout << "\nthe integer variable is  " << 
        varInt << " and at address: " << &varInt << std::endl;
    
    std::unique_ptr<int> unqP1 = std::make_unique<int>(555);

    std::cout << "\nthe unique_ptr1 value is " << *unqP1 <<
        " and at address: " << unqP1 << std::endl;

    *unqP1 = varInt;

    std::cout << "\nthe unique_ptr1 value is " << *unqP1 <<
        " and at address: " << unqP1 << std::endl;
    
    //std::unique_ptr<int> unqP2 = unqP1;  // illegal
    std::unique_ptr<int> unqP2 = std::move(unqP1); // now unqP2 is the owner of address
    *unqP2 = 777; // unqP1 is an exception because it got deallocated and put on NULL
    std::cout << "\nthe unique_ptr2 value is " << *unqP2 <<
        " and at address: " << unqP2 << " and unique_ptr2 is null:  " <<
        unqP1 << std::endl;
}


////~~~~


void ex_unique2 ()
{
    printf("\n\t%s()  ,  using demo_class\n", __func__);
    //demo myDemo;
    std::unique_ptr<demo> classPtr = std::make_unique<demo>(); // gets destroyed at end of scope {}
    std::cout << "\n\t class pointer stays in scope, address:  " << classPtr << std::endl;
}


////~~~~


void ex_shared1 ()
{
    printf("\n%s()\n", __func__);
    std::shared_ptr<demo> sPtr1 = std::make_shared<demo>();
    std::cout << "\nnumber of owners (for memory location) :  " << sPtr1.use_count() <<
        "    address:  " << sPtr1 << std::endl;

    std::shared_ptr<demo> sPtr2 = sPtr1;
    std::cout << "number of owners (for memory location) :  " << sPtr1.use_count() <<
        "    address:  " << sPtr1 << std::endl;
    
    {
        std::shared_ptr<demo> sPtr3 = sPtr2;
        std::cout << "number of owners (for memory location) :  " << sPtr1.use_count() <<
            "    address:  " << sPtr1 << std::endl;
    }
    std::cout << "number of owners (for memory location) :  " << sPtr1.use_count() <<
        "    address:  " << sPtr1 << std::endl;
    // memory address will be deallocated when no more pointers point to it
    // all owners will get destroyed at end of their scope
}


////~~~~


void ex_weak1()
{
    printf("\n%s()\n", __func__);
    std::weak_ptr<int> wPtr1;
    
    {
        std::shared_ptr<int> sPtr1 = std::make_shared<int>(555);
        wPtr1 = sPtr1;
        std::cout << "\nshared pointer:  " << *sPtr1  << "  address:  " << sPtr1 << std::endl;
    }
    printf("\nowners:  %ld\n", wPtr1.use_count());
}


/*
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>

std::vector<std::thread> threadz;


struct message
{
    std::string content;
};

////~~~~


void f_sendEmail (const message msg, const std::string email)
{
    std::cout << "\nsending email to " << email << " ...\n";
    std::this_thread::sleep_for (std::chrono::microseconds(100));
    std::cout << "\t\tsend success\n";
}

////~~~~


void sendEmail (const message& msg, const std::string& email)
{
    threadz.emplace_back(f_sendEmail, msg, email);
}

////~~~~

int main(int argc, char* argv[], char* envp[])
{
    printf("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}
*/

////////~~~~~~~~END>  smartPointer.cpp
