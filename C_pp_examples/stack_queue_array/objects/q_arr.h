/*
    the essential features to make a queue based on an array (dynamic) are inlcuded in this single file
    no need to inherit accross many places...array based is good if you know your queue size

    a set of elements of the same type, elements added at back/rear and deleted from the other end (front)
    like the stack, middle elements are inaccessable , it is literally a queue like at a store 
    you can varry this...see none, see only front, see only back, ect

    basic operations:

    1) initialize : to an empty state
    2) isEmpty : see if queue is empty (can't delete from an empty queue)
    3) isFull : see if queue is full (can't add to full queue)
    4) front : returns front element of the queue (queue must exist and must not be empty)
    5) back : returns last element of the queue (queue must exist and must not be empty)
    6) add : puts new element at rear of the queue (queue must exist and must not be full)
    7) delete : removes oldest element from front of queue (queue must exist and must not be empty)

    this is not like the book example, it tries to avoid the modular arithmetic with a transfer array
*/

#ifndef H_q_arr
#define H_q_arr

#include "../LIBS.h"



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------



template <class T>
class q_arrType
{
    public:

        // 7 esential operations
        void initializeQueue();                     //# set the queueto an empty state, deletes everything
        bool isEmptyQueue() const;                  //# true if no elements are in the queue
        bool isFullQueue() const;                   //# true if no elements can be added to the queue
        T front() const;                            //# returns first element, will always be at [0] if not empty
        T back() const;                             //# returns last element, will always be at [backIndex] if not empty
        void addQueue(const T& element);            //' if the queue exists and is not full ... goes to end
        void deleteQueue();                         //' first element is deleted if queue is not empty

        // operator overloads
        const q_arrType<T>& operator = (const q_arrType<T>& otherQueue);       //# copies provided queue to current object
        bool operator == (const q_arrType<T>& otherQueue);                     // equality?
        
        // admin
        q_arrType(int size = 10);                                          //# constructor , will work as default
        q_arrType(const q_arrType<T>& otherQueue);                         //# copy constructor
        ~q_arrType();                                                      //' destructor

        // extra variables, tracking data structure, or other methods can be used to get more info
        // most of these functions would not be possible in a pure stack or queue

        //information (no mutilation)
        int getCount() const {return (backIndex + 1);}                //# returns the number of elements 
        int getMaxSize() const {return Qsize;};                       //# returns maximum number of elements object can store (no ll)               
        //T max();                                                    // returns value of largest element, if not empty
        //T min();                                                    // returns value of smallest element, if not empty
        //int max_index();                                            // returns index of largest element, if not empty
        //int min_index();                                            // returns index of smallest element, if not empty
        void soft_PrintF();                                         //# displays current queue from front to back
        //void soft_printB();                                         // displays current queue from back to front
        //bool val_exists(const T& value);                            // true if provided values is in the queue
        //int freq_val(const T& value);                               // frequency of provided value returned (if found)
        //int first_index_val(const T& value);                        // first index of provided value returned (if found)
        //T val_at(const int index);                                  // returns the value at desired index, if legal

        //insert & edit
        //void ow_val_to(const int& index, const T& value);           // overwrites provided value to target index (if legal)                                             
        //void add_val_to(const int& index, const T& value);          // value goes to index, other element shift right (if legal)
        //void sort(const char& method);                              // sorts target queue without any changes

        //remove
        //void remove_index(const int& index);                        // deletes element at desired index, if legal
        //void remove_val(const T& value);                            // deletes value (if found)
        //void delete_all(const int& size);                           // deletes all elements, and needs an input for new size 

        //for testing ... 
        void int_build_random(const int& size, const int& min, const int& max);     //# makes queue with random of integers
        void int_reset();                                                           //# quick reset to internal variables below
        //void dub_build_random(const int& size, const int& min, const int& max);     // makes obj a random queue of doubles
        //void char_build_random(const int& size);                                    // makes obj a random queue of characters
        //void str_build_random(const int& size, const int& minL, const int& maxL);   // makes obj a random queue of strings
        

    private:

        
        int Qsize;                      //# how many elements queue can hold ...do n - 1 for index
        int backIndex = -1;             //# position of last element in the queue...first is always at [0] ...count = bi + 1  
        T *list;                        //# pointer used to make a dynamic array to hold the elements
        T *transfer;                    //' transfers list elements, when needed

        void copy(const q_arrType<T>& otherQueue);         //# only called by = overload and copy constructor...internal use only

        //for testing ... 
        //void setBlanks();                  // called to put -99 in all the black spots
        const int illegal = -99;           //# if you see it, means illegal operation occured, also used as filling to indicate
        const int defaultQsize = 10;       //# if invlaid or no input is received by constructor, maxSize = 10
        int floor = 100;                   //# for reset, integer testing
        int cieling = 500;                 //# for reset, intger testing

};





//----------------------------------------------------------------------------------------------------------------------------
//============================================== important functions =========================================================
//----------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool q_arrType<T>::isEmptyQueue() const
{
    return (backIndex == -1);         // if the base index is on -1, it means the queue is empty...bi [0] there is 1 element
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool q_arrType<T>::isFullQueue() const
{
    return ( (backIndex + 1) == Qsize); // that means there is an element at index [n-1] so there are n elements
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_arrType<T>::initializeQueue()
{
    for (int i = 0; i < Qsize; i++)
    {
        list[i] = illegal; // fill back in
    }
    backIndex = -1;
    transfer = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T q_arrType<T>::front() const
{
    if (backIndex != -1)
    {
        return list[0];      // return first element if the queue is not empty
    }
    else
    {
        std::cout << "\n ~ { the queue is empty } ~ \n";
        return illegal;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T q_arrType<T>::back() const
{
    if (backIndex != -1)
    {
        return list[backIndex];      // return last element if the queue is not empty
    }
    else
    {
        std::cout << "\n ~ { the queue is empty } ~ \n";
        return illegal;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_arrType<T>::addQueue(const T& element)
{
    if ( (backIndex + 1) < Qsize) // if there is room
    {
        backIndex++;
        list[backIndex] = element;
    }
    else 
    {
        std::cout << "\n ~ { the queue is full } ~ \n";
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_arrType<T>::deleteQueue()
{
    if (backIndex == -1)
    {
        std::cout << "\n ~ { the queue is empty } ~ \n";
    }
    else
    {
        transfer = new T[Qsize];

        for (int i = 0; i < (Qsize - 1); i++)
        {
            transfer[i] = list[i+1];
        }
        backIndex--;

        transfer[Qsize-1] = illegal; // indicate on last element

        delete [] list;
        list = transfer;
        transfer = nullptr;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
q_arrType<T>::q_arrType(int size)
{
    if (size <= 0 || size > 1000000)
    {
        std::cout << "\n ~ { using Qsize = 10 } ~ \n";
        Qsize = defaultQsize;
    }
    else
    {
        Qsize = size;
    }

    list = new T[Qsize];
    backIndex = -1; // just in case
    transfer = nullptr; // make sure it stays somewhere safe

    for (int i = 0; i < Qsize; i++) // fill up with known illegal values, easy to detect illegal access now
    {
        list[i] = illegal;
    }

}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
q_arrType<T>::~q_arrType()
{
    delete [] list;
    list = nullptr;
    transfer = nullptr;
    backIndex = -1;
    Qsize = defaultQsize;

}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
const q_arrType<T>& q_arrType<T>::operator = (const q_arrType<T>& otherQueue) // =
{
    if (this != &otherQueue) // stop self copy
    {
        copy(otherQueue);
    }
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------------
template <class T>
q_arrType<T>::q_arrType(const q_arrType<T>& otherQueue) // cc
{
    list = nullptr;
    copy(otherQueue);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_arrType<T>::copy(const q_arrType<T>& otherQueue)
{
    if (list != nullptr) // not empty, make it empty
    {
        delete [] list;
        list = nullptr;
        Qsize = defaultQsize;
        transfer = nullptr;
        backIndex = -1;
    }

    if (otherQueue.backIndex == -1) // copy empty queue
    {
        Qsize = defaultQsize;
        list = new T[Qsize];
        backIndex = -1;
        transfer = nullptr;

        for (int i = 0; i < Qsize; i++)
        {
            list[i] = illegal;
        }
    }
    else // at least 1 element to copy
    {
        Qsize = otherQueue.Qsize;           // copy size of Q
        backIndex = otherQueue.backIndex;   // copy index of last element in the Q
        list = new T[Qsize];
        transfer = nullptr;

        for (int i = 0; i < Qsize; i++)
        {
            list[i] = otherQueue.list[i];
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool q_arrType<T>::operator == (const q_arrType<T>& otherQueue)
{
    if (backIndex != otherQueue.backIndex)
    {
        return false;
    }
    else 
    {
        for (int i = 0; i <= backIndex; i++)
        {
            if (list[i] != otherQueue.list[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}





//----------------------------------------------------------------------------------------------------------------------------
//================================================  fun functions   ==========================================================
//----------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------
template <>
void q_arrType<int>::int_build_random(const int& size, const int& min, const int& max)
{
    //start fresh
    transfer = nullptr;
    backIndex = -1;
    Qsize = defaultQsize;
    delete [] list;
    list = nullptr;

    std::random_device rdevice{};                                       // set up generator, only need one
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{min, max};            // by user input, range of values possible

    std::default_random_engine num2{ rdevice() };
    std::uniform_int_distribution<int> randomNum2{0, (size - 1)};           // by user input, determines capacity of queue

    Qsize = size;
    int endIndex = randomNum2(num2);
    list = new int[Qsize];
    int stuffer;

    for (int i = 0; i < Qsize; i++)
    {
        list[i] = illegal;
    }

    for (int i = 0; i <= endIndex; i++)
    {
        stuffer = randomNum1(num1);
        addQueue(stuffer);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_arrType<T>::soft_PrintF()
{
    if (backIndex == -1)
    {
        std::cout << "\n ~ { the queue is empty } ~ \n";
    }
    else
    {
        std::cout << std::endl;
        for (int i = 0; i <= backIndex; i++)
        {
            if (i == 0 && backIndex != 0) // more than one element
            {
                std::cout << "   front {  " << list[i] << "  ";
            }
            else if (i == 0 && backIndex == 0) // only one element
            {
                std::cout << "   front {  " << list[i] << "  }  back\n";
            }
            else if (i != 0 && backIndex != i) // not on first element, not on last element
            {
                std::cout << list[i] << "  ";
            }
            else // should be i = backIndex
            {
                std::cout << list[i] << "  } back\n";
            }

        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <>
void q_arrType<int>::int_reset()
{
    int_build_random(defaultQsize, floor, cieling);
}
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
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