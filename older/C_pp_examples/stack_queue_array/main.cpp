
#include "HEADS.h"

const int g_MIN_num = 100;                     // the minimum value an integer or double element can be
const int g_MAX_num = 500;                     // the maximum value an integer or double element can be
const int g_MIN_str = 3;                       // the minimum length a string element can be
const int g_MAX_str = 9;                       // the maximum length a string element can be
const int g_SIZE_elm = 8;                      // the maximum elements that can be held by the data strucutre
std::string g_DISCARD = "";                    // throws away input, not very important
int g_RAN_INT = -99;                           // adjusted by randomInt() when a random integer is needed

// this program tests the integer data type, but templates can take chars, strings, doubles, and more (need to add features)
stk_arrType<int> stk_arr_tester;     // an object to test the stack based on an array, elements as integers 
stk_llType<int> stk_ll_tester;       // an object to test the stack based on a linked list, elements as integers 
q_arrType<int> q_arr_tester;         // an object to test the queue based on an array, elements as integers
q_llType<int> q_ll_tester;           // an object to test the queue based on a linked list, elements as integers

void testStackArray();                       // tests the functions of the stack built from an array
void testStackLL();                          // tests the functions of the stack built from a linked list
void testQueueArray();                       // tests the functions of the queue built from an array
void testQueueLL();                          // tests the functions of the queue built from a linked list
void pause();                                // called to observe results and wait to proceed, ostream
int randomInt();                             // called when a random integer is needed (for an element) ... manupulates 

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
int main() 
{    
    //testStackArray();                      
    //testStackLL();
    //testQueueArray();
    testQueueLL();

    std::cout << "\n ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n";
    return 0; 
}

//----------------------------------------------------------------------------------------------------------------------------
void pause()
{
    std::cout << "\npress any key and hit [enter] to proceed: ";     // option 1 (wait for input)
    std::cin >> g_DISCARD;                                             
    std::cout.flush();
    system("clear");
}

//----------------------------------------------------------------------------------------------------------------------------
int randomInt()
{
    std::random_device rdevice{};                                      // generator, when needed
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<int> randomNum{ g_MIN_num, g_MAX_num };

    g_RAN_INT = randomNum(num);

    return g_RAN_INT;
}

//----------------------------------------------------------------------------------------------------------------------------
void testStackArray()
{
    //stk_arr_1(); // check initialization
    //stk_arr_2(); // check random setup
    //stk_arr_3(); // test quick reset
    //stk_arr_4(); // test = ol
    //stk_arr_5(); // test copy constructor
    //stk_arr_6(); // test adding and deleting
    //stk_arr_7(); // test == ol 
}

//----------------------------------------------------------------------------------------------------------------------------
void testStackLL()
{
    //stk_ll_1(); // check initialization
    //stk_ll_2(); // check random setup
    //stk_ll_3(); // test quick reset
    //stk_ll_4(); // test = ol
    //stk_ll_5(); // test copy constructor
    //stk_ll_6(); // test adding and deleting 
    //stk_ll_7(); // test == ol
}

//----------------------------------------------------------------------------------------------------------------------------
void testQueueArray()
{
    //q_arr_1(); // check initialization
    //q_arr_2(); // check random setup
    //q_arr_3(); // test quick reset
    //q_arr_4(); // test = ol
    //q_arr_5(); // test copy constructor
    //q_arr_6(); // test adding and deleting 
    //stk_ll_7(); // test == ol  
}

//----------------------------------------------------------------------------------------------------------------------------
void testQueueLL()
{
    //q_ll_1(); // check initialization
    //q_ll_2(); // check random setup
    //q_ll_3(); // test quick reset
    //q_ll_4(); // test = ol
    //q_ll_5(); // test copy constructor
    //q_ll_6(); // test adding and deleting 
    q_ll_7(); // test == ol  
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------