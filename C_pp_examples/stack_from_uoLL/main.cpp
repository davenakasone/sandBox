#include "derivedLinkedStack.h"
#include <chrono>
#include <thread>

std::string DISCARD = "";
linkedStackType<int> tester;
const int MIN = 10;
const int MAX = 99;
int SIZE = -444; // gets put between 0 and 10 in set up

void setUp();
void display();
void testPopPush();
void testCopy();


//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
int main() 
{
    setUp();
    testPopPush();
    testCopy();

    std::cout << "\n ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n";
    return 0; 
}

//----------------------------------------------------------------------------------------------------------------------------
void setUp()
{
    std::random_device rdevice{};                                // set up generator, only need one
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<int> randomNum{0, 7};     // by user input
    
    SIZE = randomNum(num);

    tester.int_build(SIZE, MIN, MAX);
}

//----------------------------------------------------------------------------------------------------------------------------
void display()
{
    tester.softPrint();

    std::cout << "\npress any key and hit [enter] to proceed: ";     // option 1
    std::cin >> DISCARD;                                             // option 1
    //std::this_thread::sleep_for(std::chrono::seconds(5));          // option 2
    std::cout.flush();
    system("clear");
}

//----------------------------------------------------------------------------------------------------------------------------
void testPopPush()
{
    while (DISCARD != "s")
    {
        if (DISCARD == "1")
        {
            if (tester.getCount() == 0)
            {
                std::cout << "\n           :(    can't pop from a stack with no elements, program crashed\n";
            }

            tester.softPrint();
            std::cout << "\n  -------------  *** AFTER POP ***   { " << tester.top() << " }   removed  ----------------\n";
            tester.pop();
            tester.softPrint();
            DISCARD = "";
            if (tester.getCount() != 0)
                std::cout << "                             top element is { " << tester.top() << " }\n";
        }
        else if (DISCARD == "2")
        {
            std::random_device rdevice{};                                // set up generator, only need one
            std::default_random_engine num{ rdevice() };
            std::uniform_int_distribution<int> randomNum{MIN, MAX};     // by user input
            int pusher = randomNum(num);

            tester.softPrint();
            std::cout << "\n  -------------  *** AFTER PUSH   added { " << pusher << " } ***  ----------------\n";
            tester.push(pusher);
            tester.softPrint();
            DISCARD = "";
            if (tester.getCount() != 0)
                std::cout << "                              top element is { " << tester.top() << " }\n";
        }
        else
        {
            badInput:
            std::cout << "\nenter (s) to stop , (1) to POP , (2) PUSH , or (r) to reset list : ";
            std::cin >> DISCARD;                                             // option 1
            //std::this_thread::sleep_for(std::chrono::seconds(5));          // option 2
            std::cout.flush();
            system("clear");

            if (tester.getCount() == 0 && DISCARD == "1")
            {
                std::cout << "\n      you did something bad\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            if (DISCARD == "s")
            {
                goto done;
            }

            if (DISCARD == "r")
            {
                setUp();
                std::cout << "\n      reset complete\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));          // option 2
                std::cout.flush();
                system("clear");
            }

            if (DISCARD != "s" && DISCARD != "1" && DISCARD != "2" && DISCARD != "r")
            {
                std::cout << "\n      enter a valid input\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));          // option 2
                std::cout.flush();
                system("clear");
                goto badInput;
            }
        }
    }
    done:
    DISCARD = "";
    setUp();
}

//----------------------------------------------------------------------------------------------------------------------------
void testCopy()
{
    linkedStackType<int> other;

    std::cout << "\nthis will test the assignment operator, here is the original:\n";
    tester.softPrint();
    other = tester;
    std::cout << "\n          ** and the copy ** \n";
    other.softPrint();

    std::cout << "\npress any key and hit [enter] to delete original and see if copy remains: ";     // option 1
    std::cin >> DISCARD;                                             // option 1
    //std::this_thread::sleep_for(std::chrono::seconds(5));          // option 2
    std::cout.flush();
    system("clear");

    tester.destroyList();
    tester.softPrint();
    std::cout << "\n          ** and the copy (below) ** \n";
    other.softPrint();

    std::cout << "\npress any key and hit [enter] to test copy constructor: ";     // option 1
    std::cin >> DISCARD;                                             // option 1
    //std::this_thread::sleep_for(std::chrono::seconds(5));          // option 2
    std::cout.flush();
    system("clear");

    std::cout << "\nthis is the result of the copy constructor: \n";
    linkedStackType<int> copyConst(other);
    copyConst.softPrint();
    std::cout << "\nthis is what was copied: \n";
    other.softPrint();

    std::cout << "\npress any key and hit [enter] to test more: ";     // option 1
    std::cin >> DISCARD;                                             // option 1
    //std::this_thread::sleep_for(std::chrono::seconds(5));          // option 2
    std::cout.flush();
    system("clear");
}


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================ 
//---------------------------------------------------------------------------------------------------------------------------- 

