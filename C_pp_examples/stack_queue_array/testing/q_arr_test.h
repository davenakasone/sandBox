#ifndef H_q_arr_test                  // tests for queue (array-based) ...turn into templates to test anything besides ints
#define H_q_arr_test

#include "../objects/q_arr.h"

// globals from main()
extern const int g_MIN_num;                       // the minimum value an integer or double element can be
extern const int g_MAX_num;                       // the maximum value an integer or double element can be
extern const int g_MIN_str;                       // the minimum length a string element can be
extern const int g_MAX_str;                       // the maximum length a string element can be
extern const int g_SIZE_elm;                      // the maximum elements that can be held by the data strucutre
extern std::string g_DISCARD;                     // throws away input, not very important
extern int g_RAN_INT;                             // adjusted by randomInt() when a random integer is needed
extern q_arrType<int> q_arr_tester;               // an object to test the queue based on an array, elements as integers

// common function from main()
extern void pause();
extern int randomInt();

// functions to test with, see defintions below
void q_arr_1(); // 1    check initialization
void q_arr_2(); // 2    check random integer initializer
void q_arr_3(); // 3    check quick reset
void q_arr_4(); // 4    check = ol
void q_arr_5(); // 5    check copy constructor
void q_arr_6(); // 6    check adding and deleting elements
void q_arr_7(); // 6    check == ol


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
void q_arr_1()
{
    q_arr_tester.soft_PrintF();                                 //  1      queue was initialized properly, variables are showing                       
    std::cout << "\nthere are < " << q_arr_tester.getCount() << " > elements in this queue";
    std::cout << "\nis it empty? : " << q_arr_tester.isEmptyQueue();
    std::cout << "\nis it full? : " << q_arr_tester.isFullQueue();
    std::cout << "\ncapacity is: " << q_arr_tester.getMaxSize();
    std::cout << "\nelements in queue: " << q_arr_tester.getCount();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_arr_2()
{
    std::cout << "\nafter set up....\n\n";                       //  2    able randomize, print, and display min/max
    q_arr_tester.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    q_arr_tester.soft_PrintF();
    std::cout << "\nthere are < " << q_arr_tester.getCount() << " > elements";
    std::cout << "\nthe max size is < " << q_arr_tester.getMaxSize() << " > elements";
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_arr_3()
{
    std::cout << "\n           original:\n";            //  3      test quick reset feature built into class
    q_arr_tester.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    q_arr_tester.soft_PrintF();
    q_arr_tester.int_reset();
    std::cout << "\n            reset:\n";
    q_arr_tester.soft_PrintF();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_arr_4()
{
    std::cout << "\n    here is the original object: \n";         //  4  testing = overload
    q_arr_tester.int_reset();
    q_arr_tester.soft_PrintF();
    std::cout << "\nthere are < " << q_arr_tester.getCount() << " > elements";
    std::cout << "\nthe max size is < " << q_arr_tester.getMaxSize() << " > elements";
    std::cout << "\nthe front is:  " << q_arr_tester.front();
    std::cout << "\nthe back is:  " << q_arr_tester.back();
    std::cout << "\nis it empty? : " << q_arr_tester.isEmptyQueue();
    std::cout << "\nis it full? : " << q_arr_tester.isFullQueue();
    q_arrType<int> other;
    other = q_arr_tester;
    std::cout << "\n    here is the copied object (by assignment): \n";
    other.soft_PrintF();
    std::cout << "\nthere are < " << other.getCount() << " > elements";
    std::cout << "\nthe max size is < " << other.getMaxSize() << " > elements";
    std::cout << "\nthe front is:  " << other.front();
    std::cout << "\nthe back is:  " << other.back();
    std::cout << "\nis it empty? : " << other.isEmptyQueue();
    std::cout << "\nis it full? : " << other.isFullQueue();
    pause();
    std::cout << "\ncheck the deep copy, original is deleted:\n";
    q_arr_tester.initializeQueue();
    q_arr_tester.soft_PrintF();
    std::cout << "\nthere are < " << q_arr_tester.getCount() << " > elements";
    std::cout << "\nthe max size is < " << q_arr_tester.getMaxSize() << " > elements";
    std::cout << "\nthe front is:  " << q_arr_tester.front();
    std::cout << "\nthe back is:  " << q_arr_tester.back();
    std::cout << "\nis it empty? : " << q_arr_tester.isEmptyQueue();
    std::cout << "\nis it full? : " << q_arr_tester.isFullQueue();
    std::cout << "\n    here is the copied object (by assignment): \n";
    other.soft_PrintF();
    std::cout << "\nthere are < " << other.getCount() << " > elements";
    std::cout << "\nthe max size is < " << other.getMaxSize() << " > elements";
    std::cout << "\nthe front is:  " << other.front();
    std::cout << "\nthe back is:  " << other.back();
    std::cout << "\nis it empty? : " << other.isEmptyQueue();
    std::cout << "\nis it full? : " << other.isFullQueue();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_arr_5()
{
    std::cout << "\n      this object will be used to construct another: \n";   //  5 test copy constructor
    q_arr_tester.int_reset();
    q_arr_tester.soft_PrintF();
    q_arrType<int> another(q_arr_tester);
    std::cout << "\n here is the result: \n";
    another.soft_PrintF();
    pause();
}

//----------------------------------------------------------------------------------------------------------------------------
void q_arr_6()
{
    q_arr_tester.int_reset();                                           // 6  tests adding and deleting
    g_DISCARD = "";
    int pusher;
    int deleter;

    while (g_DISCARD != "q")
    {
        std::cout << "\n\n (1) add (2) delete (r) reset (q) quit : ";
        std::cin >> g_DISCARD;

        if (q_arr_tester.isEmptyQueue())
        {
            std::cout << "\n ~ { the queue is empty } ~ \n";
        }
        else
        {
            std::cout << "\n< " << q_arr_tester.getCount() << " >  elements  ,  " <<
            "capacity  < " << q_arr_tester.getMaxSize() << " >  ,  " <<
            "front { " << q_arr_tester.front() << " }  ,  " <<
            "back { " << q_arr_tester.back() << " }  ,  " <<
            "empty? : " << q_arr_tester.isEmptyQueue() << "  ,  "
            "full? : " << q_arr_tester.isFullQueue() << std::endl;
            std::cout << std::endl;
            q_arr_tester.soft_PrintF();
        }

        if (g_DISCARD == "1") // push
        {   
            if (q_arr_tester.isFullQueue())
            {
                std::cout << "\n ~ { can't add to a full queue } ~ \n";
            }
            else
            {
                pusher = randomInt();
                q_arr_tester.addQueue(pusher);
                q_arr_tester.soft_PrintF();
            
                std::cout << "\n< " << q_arr_tester.getCount() << " >  elements  ,  " <<
                "capacity  < " << q_arr_tester.getMaxSize() << " >  ,  " <<
                "front { " << q_arr_tester.front() << " }  ,  " <<
                "back { " << q_arr_tester.back() << " }  ,  " <<
                "empty? : " << q_arr_tester.isEmptyQueue() << "  ,  "
                "full? : " << q_arr_tester.isFullQueue() << std::endl;
                std::cout << "\n                                                    queue after adding { " << pusher << " }\n";
            }
        }
        else if (g_DISCARD == "2") // delete
        {   
            if (!q_arr_tester.isEmptyQueue() && q_arr_tester.getCount() != 1)
            {
                deleter = q_arr_tester.front();
                q_arr_tester.deleteQueue();
                q_arr_tester.soft_PrintF();

                std::cout << "\n< " << q_arr_tester.getCount() << " >  elements  ,  " <<
                "capacity  < " << q_arr_tester.getMaxSize() << " >  ,  " <<
                "front { " << q_arr_tester.front() << " }  ,  " <<
                "back { " << q_arr_tester.back() << " }  ,  " <<
                "empty? : " << q_arr_tester.isEmptyQueue() << "  ,  "
                "full? : " << q_arr_tester.isFullQueue() << std::endl;
                std::cout << "\n                             here is the queue after deleting front { " << deleter << " }\n";
            }
            else if (q_arr_tester.getCount() == 1)
            {
                deleter = q_arr_tester.front();
                q_arr_tester.deleteQueue();
                std::cout << "\n you deleted { " << deleter << " } , the queue is empty\n";
            }
            else
            {
                std::cout << "\n ~ { can't delete from an empty queue } ~ \n";
            }
        }
        else if (g_DISCARD == "r") // reset
        {
            q_arr_tester.int_reset();
            q_arr_tester.soft_PrintF();
            std::cout << "\n< " << q_arr_tester.getCount() << " >  elements  ,  " <<
            "capacity  < " << q_arr_tester.getMaxSize() << " >  ,  " <<
            "front { " << q_arr_tester.front() << " }  ,  " <<
            "back { " << q_arr_tester.back() << " }  ,  " <<
            "empty? : " << q_arr_tester.isEmptyQueue() << "  ,  "
            "full? : " << q_arr_tester.isFullQueue() << std::endl;
            std::cout << "\n here is the stack after reset \n";
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
void q_arr_7()
{
    q_arr_tester.int_reset();
    q_arrType<int> notEqual;
    notEqual.int_build_random(g_SIZE_elm, g_MIN_num, g_MAX_num);
    q_arr_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (q_arr_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == q_arr_tester);
    pause();
    notEqual = q_arr_tester;
    q_arr_tester.soft_PrintF();
    std::cout << std::endl;
    notEqual.soft_PrintF();
    std::cout << "\n equality check: " << (q_arr_tester == notEqual);
    std::cout << "\n equality check: " << (notEqual == q_arr_tester);
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