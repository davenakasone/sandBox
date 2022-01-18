#ifndef H_stk_ll_test                // tests for stack (LL-based) ...turn into templates to test anything besides ints
#define H_stk_ll_test

#include "../objects/stk_ll.h"

// globals from main()
extern const int g_MIN_num;                       // the minimum value an integer or double element can be
extern const int g_MAX_num;                       // the maximum value an integer or double element can be
extern const int g_MIN_str;                       // the minimum length a string element can be
extern const int g_MAX_str;                       // the maximum length a string element can be
extern const int g_SIZE_elm;                      // the maximum elements that can be held by the data strucutre
extern std::string g_DISCARD;                     // throws away input, not very important
extern int g_RAN_INT;                             // adjusted by randomInt() when a random integer is needed
extern stk_llType<int> stk_ll_tester;             // an object to test the stack based on LL, elements as integers

// common function from main()
extern void pause();
extern int randomInt();

// functions to test with, see defintions below
void stk_ll_1(); // 1    check initialization
void stk_ll_2(); // 2    check random integer initializer
void stk_ll_3(); // 3    check quick reset
void stk_ll_4(); // 4    check = ol
void stk_ll_5(); // 5    check copy constructor
void stk_ll_6(); // 6    check push, pop, top
void stk_ll_7(); // 7    check == ol



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
void stk_ll_1()
{
    stk_ll_tester.soft_PrintF();             //  1      stack was initialized properly, variables are showing                       
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack";
    std::cout << "\nis it empty? : " << stk_ll_tester.isEmptyStack();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_ll_2()
{
    stk_ll_tester.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);    //  2           can random build
    stk_ll_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack";
    std::cout << "\nis it empty? : " << stk_ll_tester.isEmptyStack();
    std::cout << "\nis it full? : " << stk_ll_tester.isFullStack() << "  ...trick question";
    std::cout << "\nthe top is: { " << stk_ll_tester.top() << " }\n";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_ll_3()
{
    stk_ll_tester.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);  
    std::cout << "\n        here is the stack:\n";               //  3 can reset
    stk_ll_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack\n";
    std::cout << "\n        here is the stack after the reset:\n";
    stk_ll_tester.int_reset();
    stk_ll_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_ll_4()
{
    stk_ll_tester.int_reset();
    std::cout << "\n    here is the original object: \n";         //  4  testing = overload
    stk_ll_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack\n";
    stk_llType<int> other;
    other = stk_ll_tester;
    std::cout << "\n    here is the copied object (by assignment): \n";
    other.soft_PrintF();
    std::cout << "\nthere are < " << other.getCount() << " > elements in this stack\n";
    pause();
    std::cout << "\n to make sure the deep copy is good, the original will be cleared\n";
    std::cout << "\n    here is the original object: \n";
    stk_ll_tester.initializeStack();
    stk_ll_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack\n";
    std::cout << "\n    here is the copied object (by assignment): \n";
    other.soft_PrintF();
    std::cout << "\nthere are < " << other.getCount() << " > elements in this stack\n";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_ll_5()
{
    std::cout << "\n      this object will be used to construct another: \n";   //  5 test copy constructor
    stk_ll_tester.int_reset();
    stk_ll_tester.soft_PrintF();
    std::cout << "\nthere are < " << stk_ll_tester.getCount() << " > elements in this stack\n";
    stk_llType<int> another(stk_ll_tester);
    std::cout << "\n here is the result: \n";
    another.soft_PrintF();
    std::cout << "\nthere are < " << another.getCount() << " > elements in this stack\n";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void stk_ll_6()
{
    stk_ll_tester.int_reset();                                           // 6  tests pushing, poping, toping
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
        else if (stk_ll_tester.isEmptyStack())
        {
            std::cout << "\n ~ { the stack is empty } ~\n";
        }
        else
        {
            std::cout << "\n here is the stack now...\n";
            stk_ll_tester.soft_PrintF();
            std::cout << "\nelements  < " << stk_ll_tester.getCount() << " >  ,  " <<
            "empty?  " << stk_ll_tester.isEmptyStack() <<
            "  ,  full? " << stk_ll_tester.isFullStack() << std::endl;
        }

        if (g_DISCARD == "1") // push
        {   
            if (stk_ll_tester.isFullStack())
            {
                std::cout << " ~ { push not possible, stack is full } ~\n";
            }
            else
            {
                pusher = randomInt();
                stk_ll_tester.push(pusher);
                std::cout << "\nelements  < " << stk_ll_tester.getCount() << " >  ,  " <<
                "empty?  " << stk_ll_tester.isEmptyStack() <<
                "  ,  full? " << stk_ll_tester.isFullStack() << std::endl;
                stk_ll_tester.soft_PrintF();
                std::cout << "\n             ..... after pushing { " << pusher << " }\n";
            } 
        }
        else if (g_DISCARD == "2") // pop
        {
            if (stk_ll_tester.isEmptyStack())
            {
                std::cout << " ~ { pop not possible, stack is empty } ~\n";
            }
            else
            {
                top = stk_ll_tester.top();
                stk_ll_tester.pop();
                std::cout << "\nelements  < " << stk_ll_tester.getCount() << " >  ,  " <<
                "empty?  " << stk_ll_tester.isEmptyStack() <<
                "  ,  full? " << stk_ll_tester.isFullStack() << std::endl;
                stk_ll_tester.soft_PrintF();
                std::cout << "\n ........ after poping { " << top << " }\n";
            }
        }
        else if (g_DISCARD == "3") // top
        {
            if (stk_ll_tester.isEmptyStack())
            {
                std::cout << " ~ { top not possible, stack is empty } ~\n";  
            }
            else
            {
                std::cout << "\nelements  < " << stk_ll_tester.getCount() << " >  ,  " <<
                "empty?  " << stk_ll_tester.isEmptyStack() <<
                "  ,  full? " << stk_ll_tester.isFullStack() << std::endl;
                std::cout << "\n here is the top element of the stack { " << stk_ll_tester.top() << " }\n";
            } 
        }
        else if (g_DISCARD == "r")
        {
            stk_ll_tester.int_reset();
            std::cout << "\nelements  < " << stk_ll_tester.getCount() << " >  ,  " <<
            "empty?  " << stk_ll_tester.isEmptyStack() <<
            "  ,  full? " << stk_ll_tester.isFullStack() << std::endl;
            stk_ll_tester.soft_PrintF();
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
void stk_ll_7()
{
    stk_ll_tester.int_reset();
    stk_llType<int> notEqual;
    notEqual.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    stk_ll_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (stk_ll_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == stk_ll_tester);
    pause();
    notEqual = stk_ll_tester;
    stk_ll_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (stk_ll_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == stk_ll_tester);
    pause();
}
//----------------------------------------------------------------------------------------------------------------------------
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