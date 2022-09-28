#ifndef H_q_ll_test                // tests for queue (LL-based) ...turn into templates to test anything besides ints
#define H_q_ll_test

#include "../objects/q_ll.h"

// globals from main()
extern const int g_MIN_num;                       // the minimum value an integer or double element can be
extern const int g_MAX_num;                       // the maximum value an integer or double element can be
extern const int g_MIN_str;                       // the minimum length a string element can be
extern const int g_MAX_str;                       // the maximum length a string element can be
extern const int g_SIZE_elm;                      // the maximum elements that can be held by the data strucutre
extern std::string g_DISCARD;                     // throws away input, not very important
extern int g_RAN_INT;                             // adjusted by randomInt() when a random integer is needed
extern q_llType<int> q_ll_tester;                 // an object to test the queue based on LL, elements as integers

// common function from main()
extern void pause();
extern int randomInt();

// functions to test with, see defintions below
void q_ll_1(); // 1    check initialization
void q_ll_2(); // 2    check random integer initializer
void q_ll_3(); // 3    check quick reset
void q_ll_4(); // 4    check = ol
void q_ll_5(); // 5    check copy constructor
void q_ll_6(); // 6    check push, pop, top
void q_ll_7(); // 7    check == ol



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
void q_ll_1()
{
    q_ll_tester.soft_PrintF(); // looks how it should
    std::cout << "\n empty? " << q_ll_tester.isEmptyQueue();
    std::cout << "\n full? " << q_ll_tester.isFullQueue();

    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_ll_2()
{
    q_ll_tester.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    q_ll_tester.soft_PrintF();
    std::cout << "\n empty? " << q_ll_tester.isEmptyQueue();
    std::cout << "\n full? " << q_ll_tester.isFullQueue();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_ll_3()
{
    q_ll_tester.int_reset(); 
    q_ll_tester.soft_PrintF();
    std::cout << "\n empty? " << q_ll_tester.isEmptyQueue();
    std::cout << "\n full? " << q_ll_tester.isFullQueue();
    pause();  
}

//----------------------------------------------------------------------------------------------------------------------------
void q_ll_4()
{
    q_ll_tester.int_reset();
    q_ll_tester.soft_PrintF();
    std::cout << "\n .... by = ol:\n";
    q_llType<int> other;
    other = q_ll_tester;
    other.soft_PrintF();
    pause(); 
}

//----------------------------------------------------------------------------------------------------------------------------
void q_ll_5()
{
    q_ll_tester.int_reset();
    q_ll_tester.soft_PrintF();
    std::cout << "\n .... by copy constructor:\n";
    q_llType<int> another(q_ll_tester);
    another.soft_PrintF();
    pause(); 
}

//----------------------------------------------------------------------------------------------------------------------------
void q_ll_6()
{
    q_ll_tester.int_reset();                  
    g_DISCARD = "";
    int pusher;
    int deleter;

    while (g_DISCARD != "q")
    {
        std::cout << "\n\n (1) add (2) delete (r) reset (q) quit : ";
        std::cin >> g_DISCARD;

        if (q_ll_tester.isEmptyQueue())
        {
            std::cout << "\n ~ { the queue is empty } ~ \n";
        }
        else
        {
            std::cout << std::endl;
            q_ll_tester.soft_PrintF();
        }

        if (g_DISCARD == "1") // push
        {   
            if (q_ll_tester.isFullQueue())
            {
                std::cout << "\n ~ { can't add to a full queue } ~ \n";
            }
            else
            {
                pusher = randomInt();
                q_ll_tester.addQueue(pusher);
                q_ll_tester.soft_PrintF();
                std::cout << "\n                                                    queue after adding { " << pusher << " }\n";
            }
        }
        else if (g_DISCARD == "2") // delete
        {   
            if (!q_ll_tester.isEmptyQueue() && q_ll_tester.getCount() != 1)
            {
                deleter = q_ll_tester.front();
                q_ll_tester.deleteQueue();
                q_ll_tester.soft_PrintF();
                std::cout << "\n                             here is the queue after deleting front { " << deleter << " }\n";
            }
            else if (q_ll_tester.getCount() == 1)
            {
                deleter = q_ll_tester.front();
                q_ll_tester.deleteQueue();
                std::cout << "\n you deleted { " << deleter << " } , the queue is empty\n";
            }
            else
            {
                std::cout << "\n ~ { can't delete from an empty queue } ~ \n";
            }
        }
        else if (g_DISCARD == "r") // reset
        {
            q_ll_tester.int_reset();
            q_ll_tester.soft_PrintF();
            std::cout << "\n          .... after reset \n";
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
void q_ll_7()
{
    q_ll_tester.int_reset();
    q_llType<int> notEqual;
    notEqual.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    q_ll_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (q_ll_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == q_ll_tester);
    
    pause();
    
    notEqual = q_ll_tester;
    q_ll_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (q_ll_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == q_ll_tester);
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