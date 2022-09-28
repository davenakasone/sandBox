#ifndef H_stk_arr_test                // tests for stack (array-based) ...turn into templates to test anything besides ints
#define H_stk_arr_test

#include "../objects/stk_arr.h"

// globals from main()
extern const int g_MIN_num;                       // the minimum value an integer or double element can be
extern const int g_MAX_num;                       // the maximum value an integer or double element can be
extern const int g_MIN_str;                       // the minimum length a string element can be
extern const int g_MAX_str;                       // the maximum length a string element can be
extern const int g_SIZE_elm;                      // the maximum elements that can be held by the data strucutre
extern std::string g_DISCARD;                     // throws away input, not very important
extern int g_RAN_INT;                             // adjusted by randomInt() when a random integer is needed
extern stk_arrType<int> stk_arr_tester;           // an object to test the stack based on an array, elements as integers

// common function from main()
extern void pause();
extern int randomInt();

// functions to test with, see defintions below
void stk_arr_1(); // 1    check initialization
void stk_arr_2(); // 2    check random integer initializer
void stk_arr_3(); // 3    check quick reset
void stk_arr_4(); // 4    check = ol
void stk_arr_5(); // 5    check copy constructor
void stk_arr_6(); // 6    check push, pop, top
void stk_arr_7(); // 7    check == ol



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_1()
{
    stk_arr_tester.soft_PrintF();                       //  1      stack was initialized properly, variables are showing
    std::cout << "\nthere are < " << stk_arr_tester.getCount() << " > elements\n";
    std::cout << "\nthe max size is < " << stk_arr_tester.getMaxSize() << " > elements\n";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_2()
{
    std::cout << "\nafter set up....\n\n";              //  2    able randomize, print, and display min/max
    stk_arr_tester.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    stk_arr_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_arr_tester.getCount() << " > elements";
    std::cout << "\nthe max size is < " << stk_arr_tester.getMaxSize() << " > elements";
    std::cout << "\nthe largest element is  { " << stk_arr_tester.max() << " }";
    std::cout << "\nthe smallest element is { " << stk_arr_tester.min() << " }\n";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_3()
{
    std::cout << "\n           original:\n";            //  3      test quick reset feature built into class
    stk_arr_tester.int_reset();
    stk_arr_tester.soft_PrintF();
    stk_arr_tester.int_reset();
    std::cout << "\n            reset:\n";
    stk_arr_tester.soft_PrintF();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_4()
{
    std::cout << "\n    here is the original object: \n";         //  4  testing = overload
    stk_arr_tester.int_reset();
    stk_arr_tester.soft_PrintF();
    stk_arrType<int> other;
    other = stk_arr_tester;
    std::cout << "\n    here is the copied object (by assignment): \n";
    other.soft_PrintF();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_5()
{
    std::cout << "\n      this object will be used to construct another: \n";   //  5 test copy constructor
    stk_arr_tester.int_reset();
    stk_arr_tester.soft_PrintF();
    stk_arrType<int> another(stk_arr_tester);
    std::cout << "\n here is the result: \n";
    another.soft_PrintF();
    pause();
    stk_arr_tester.initializeStack();
    stk_arr_tester.soft_PrintF();
    std::cout << "\n even though the original was deleted...deep copy stays \n";
    another.soft_PrintF();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_6()
{
    stk_arr_tester.int_reset();                                           // 6  tests pushing, poping, toping
    g_DISCARD = "";
    int pusher;
    int top;
    while (g_DISCARD != "q")
    {
        
        std::cout << "\n (1) push (2) pop  (3) top  (r) reset (q) quit : ";
        std::cin >> g_DISCARD;

        if (g_DISCARD == "q")
        {
            break;
        }
        else if (stk_arr_tester.isEmptyStack())
        {
            std::cout << "\n ~ { the stack is empty } ~\n";
        }
        else
        {
            std::cout << "\n here is the stack now...\n";
            stk_arr_tester.soft_PrintF();
            std::cout << "\nstack capacity  < " << stk_arr_tester.getMaxSize() << " >  ,  " <<
            "elements  < " << stk_arr_tester.getCount() << " >  ,  " <<
            "empty?  " << stk_arr_tester.isEmptyStack() <<
            "  ,  full? " << stk_arr_tester.isFullStack() << std::endl;
        }

        if (g_DISCARD == "1") // push
        {   
            if (stk_arr_tester.isFullStack())
            {
                std::cout << " ~ { push not possible, stack is full } ~\n";
            }
            else
            {
                pusher = randomInt();
                stk_arr_tester.push(pusher);
                std::cout << "\nstack capacity  < " << stk_arr_tester.getMaxSize() << " >  ,  " <<
                "elements  < " << stk_arr_tester.getCount() << " >  ,  " <<
                "empty?  " << stk_arr_tester.isEmptyStack() <<
                "  ,  full? " << stk_arr_tester.isFullStack() << std::endl;
                stk_arr_tester.soft_PrintF();
                std::cout << "\n             ..... after pushing { " << pusher << " }\n";
            } 
        }
        else if (g_DISCARD == "2") // pop
        {
            if (stk_arr_tester.isEmptyStack())
            {
                std::cout << " ~ { pop not possible, stack is empty } ~\n";
            }
            else
            {
                top = stk_arr_tester.top();
                stk_arr_tester.pop();
                std::cout << "\nstack capacity  < " << stk_arr_tester.getMaxSize() << " >  ,  " <<
                "elements  < " << stk_arr_tester.getCount() << " >  ,  " <<
                "empty?  " << stk_arr_tester.isEmptyStack() <<
                "  ,  full? " << stk_arr_tester.isFullStack() << std::endl;
                stk_arr_tester.soft_PrintF();
                std::cout << "\n ........ after poping { " << top << " }\n";
            }
        }
        else if (g_DISCARD == "3") // top
        {
            if (stk_arr_tester.isEmptyStack())
            {
                std::cout << " ~ { top not possible, stack is empty } ~\n";  
            }
            else
            {
                std::cout << "\nstack capacity  < " << stk_arr_tester.getMaxSize() << " >  ,  " <<
                "elements  < " << stk_arr_tester.getCount() << " >  ,  " <<
                "empty?  " << stk_arr_tester.isEmptyStack() <<
                "  ,  full? " << stk_arr_tester.isFullStack() << std::endl;
                std::cout << "\n here is the top element of the stack { " << stk_arr_tester.top() << " }\n";
            } 
        }
        else if (g_DISCARD == "r")
        {
            stk_arr_tester.int_reset();
            std::cout << "\nstack capacity  < " << stk_arr_tester.getMaxSize() << " >  ,  " <<
            "elements  < " << stk_arr_tester.getCount() << " >  ,  " <<
            "empty?  " << stk_arr_tester.isEmptyStack() <<
            "  ,  full? " << stk_arr_tester.isFullStack() << std::endl;
            stk_arr_tester.soft_PrintF();
            std::cout << "\n ....... after reset: \n";
        }
        else
        {
            std::cout << "\ninvalid entry\n";
            g_DISCARD = "z";
            std::this_thread::sleep_for(std::chrono::seconds(5));           
            std::cout.flush();
            system("clear");
        }
        std::cout << "\n    enter (p) to proceed: ";
        std::cin >> g_DISCARD;
        std::cout.flush();
        system("clear");
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_arr_7()
{
    stk_arr_tester.int_reset();
    stk_arrType<int> notEqual;
    notEqual.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    stk_arr_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (stk_arr_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == stk_arr_tester);
    pause();
    notEqual = stk_arr_tester;
    stk_arr_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (stk_arr_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == stk_arr_tester);
    pause();
}
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------