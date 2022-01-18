/*
    the essential features to make a queue based on a linked-list (single) are inlcuded in this single file
    no need to inherit accross many places

    queueFront-> [ v | * ] -> [ v | * ] -> [ v | * ] .... [ v | * ] -> null
                                                            qR

    addQueue is insertTail()
    deleteQueue is deleteHead()
*/

#ifndef H_q_ll
#define H_q_ll

#include "../LIBS.h"



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------



template <class T>     // keep the nodes as simple as possible, structs are nice if there are no methods, or you like C
struct q_nodeType
{
    T data;
    q_nodeType<T> *next;
};



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------



template <class T>
class q_llType
{
    public:

        // 7 esential operations
        void initializeQueue();                     //' set the queueto an empty state, deletes everything
        bool isEmptyQueue() const;                  // true if no elements are in the queue
        bool isFullQueue() const;                   // true if no elements can be added to the queue
        T front() const;                            // returns first element, will always be at [0] if not empty
        T back() const;                             // returns last element, will always be at [backIndex] if not empty
        void addQueue(const T& element);            // if the queue exists and is not full ... goes to end
        void deleteQueue();                         // first element is deleted if queue is not empty

        // operator overloads
        const q_llType<T>& operator = (const q_llType<T>& otherQueue);       // copies provided queue to current object
        bool operator == (const q_llType<T>& otherQueue);                    // == ol, for equality
        //!=
        
        // admin
        q_llType();                                          // constructor , will work as default
        q_llType(const q_llType<T>& otherQueue);                         // copy constructor
        ~q_llType();                                                      // destructor

        // extra variables, tracking data structure, or other methods can be used to get more info
        // most of these functions would not be possible in a pure stack or queue

        //information (no mutilation)
        int getCount() const {return count;}                          //' returns the number of elements 
        //int getMaxSize() const {return Qsize;};                     // returns maximum number of elements object can store (no ll)               
        //T max();                                                    // returns value of largest element, if not empty
        //T min();                                                    // returns value of smallest element, if not empty
        //int max_index();                                            // returns index of largest element, if not empty
        //int min_index();                                            // returns index of smallest element, if not empty
        void soft_PrintF();                                         // displays current queue from front to back
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
        void int_build_random(const int& size, const int& min, const int& max);     // makes queue with random of integers
        void int_reset();                                                           // quick reset to internal variables below
        //void dub_build_random(const int& size, const int& min, const int& max);     // makes obj a random queue of doubles
        //void char_build_random(const int& size);                                    // makes obj a random queue of characters
        //void str_build_random(const int& size, const int& minL, const int& maxL);   // makes obj a random queue of strings
        

    private:

        q_nodeType<T> *queueFront; // pointer to the front of the queue
        q_nodeType<T> *queueRear;  // pointer to the rear of the queue
        int count;               // how many element are in the queue

        void copy(const q_llType<T>& otherQueue);         // only called by = overload and copy constructor...internal use only

        //for testing ... 
        //void setBlanks();                  // called to put -99 in all the black spots
        const int illegal = -99;             // if you see it, means illegal operation occured, also used as filling to indicate
        int defaultNodes = 9;    // nodes for random build
        int floor = 100;         // minimum size of element in random build
        int cieling = 500;       // maximum size of element in random build

};





//----------------------------------------------------------------------------------------------------------------------------
//============================================== important functions =========================================================
//----------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------
template <class T>
q_llType<T>::q_llType() // default constructor
{
    queueFront = nullptr; // set front to nullptr
    queueRear = nullptr;  // set rear to nullptr
    count = 0;            // and the count
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool q_llType<T>::isEmptyQueue() const
{
    return (queueFront == nullptr); // only way queue can be empty...count should be 0 also
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool q_llType<T>::isFullQueue() const
{
    return false; // ...unless you run out of memory
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_llType<T>::initializeQueue()
{
    q_nodeType<T> *temp;

    while (queueFront!= nullptr)  // while there are elements left
    {
        temp = queueFront;  // set temp to point to the first node
        queueFront = queueFront->next;  // advance first to the next node
        delete temp;    // deallocate memory occupied by temp
    }
    temp = nullptr; // just in case
    queueFront = nullptr;
    count = 0;
    queueRear = nullptr;  //set rear to nullptr
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_llType<T>::addQueue(const T& newElement) // equivelant to insertTail()
{
    q_nodeType<T> *newNode;

    newNode = new q_nodeType<T>;   // create the node
    newNode->data = newElement;  // store the info
    newNode->next = nullptr;     // initialize the link 

    if (queueFront == nullptr)   // if initially the queue is empty
    {
        queueFront = newNode;
        queueRear = newNode;
    }
    else        // add newNode at the end
    {
        queueRear->next = newNode;
        queueRear = newNode;
    }
    newNode = nullptr; // for safety
    count++;           // and increment
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T q_llType<T>::front() const
{
    assert(queueFront != nullptr); // have to stop if they try to access memory that is illegal
    return queueFront->data; 
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T q_llType<T>::back() const
{
    assert(queueRear!= nullptr); // have to stop if they try to access memory that is illegal
    return queueRear->data;
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_llType<T>::deleteQueue() // should be just like deleteHead()
{
    q_nodeType<T> *temp;
   
    if (!isEmptyQueue())
    {
        temp = queueFront;               // make temp point to the first node
        queueFront = queueFront->next;   // advance queueFront 
        delete temp;                     // delete the first node
        count --;                        // decrement

        if (queueFront == nullptr)       // if after deletion the queue is empty
        {
            queueRear = nullptr;   //set queueRear to nullptr
        }   
    }
    else
    {
        std::cout << "\n ~ { cannot remove from an empty queue } ~ \n";
    }
        
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
q_llType<T>::~q_llType() // destructor
{
    initializeQueue(); // that should do it
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
const q_llType<T>& q_llType<T>::operator = (const q_llType<T>& otherQueue)
{
    if (this != &otherQueue) // no self copy
    {
        copy(otherQueue);
    }
    return *this;
} 

//----------------------------------------------------------------------------------------------------------------------------	
template <class T>
q_llType<T>::q_llType(const q_llType<T>& otherQueue) // copy constructor
{
    queueFront = nullptr; // set front to nullptr
    queueRear = nullptr;  // set rear to nullptr
    count = 0;            // and the count
    copy(otherQueue); // copy it
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_llType<T>::copy(const q_llType<T>& otherQueue)
{
    if (count != 0)
    {
        initializeQueue(); // start fresh
    }

    if (otherQueue.count == 0) // just reset empty if copy is empty
    {
        initializeQueue();
    }
    else
    {
        q_nodeType<T> *temp;           // to trace
        temp = otherQueue.queueFront;  // put on other queue
        
        while (temp != nullptr)
        {
            addQueue(temp->data);
            temp = temp->next;
        }
    } 
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool q_llType<T>::operator == (const q_llType<T>& otherQueue)
{
    if (count != otherQueue.count)
    {
        return false;
    }
    else
    {
        q_nodeType<T> *current;
        q_nodeType<T> *currentO;
        current = queueFront;
        currentO = otherQueue.queueFront;

        for (int i = 0; i < count; i++)
        {
            if ( (current->data) != (currentO->data) )
            {
                current = nullptr;
                currentO = nullptr;
                return false;
            }
        }
        current = nullptr;
        currentO = nullptr;
        return true;
    }
    return false;
}





//----------------------------------------------------------------------------------------------------------------------------
//================================================  fun functions   ==========================================================
//----------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------
template <>
void q_llType<int>::int_build_random(const int& nodes, const int& min, const int& max)
{
    std::random_device rdevice{};                                       // set up generator, only need one
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{min, max};            // by user input, range of values possible

    std::default_random_engine num2{ rdevice() };
    std::uniform_int_distribution<int> randomNum2{0, nodes};           // by user input, determines capacity of queue

    initializeQueue(); // start fresh
    int filler;
    int length;
    length = randomNum2(num2);
    

    for (int i = 0; i < (length + 1); i++)
    {
        filler = randomNum1(num1);
        addQueue(filler);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <>
void q_llType<int>::int_reset()
{
    int_build_random(defaultNodes, floor, cieling);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void q_llType<T>::soft_PrintF()
{
    if (count == 0)
    {
        std::cout << "\n ~ { queue is empty } ~\n";
    }
    else
    {
        q_nodeType<T> *temp;
        temp = queueFront;

        std::cout << std::endl;
        for (int i = 0; i < count; i++)
        {
            if (i == 0 && count != 1) // more than 1 element in the queue
            {
                std::cout << "  front  { " << temp->data << "  ";
            }
            else if (i == 0 && count == 1) // only 1 element
            {
                std::cout << "  front  { " << temp->data << " }  back ";
            }
            else if (i != 0 && (count -1) != i) // in the middle
            {
                std::cout << temp->data << "  ";
            }
            else
            {
                std::cout << temp->data << " } back  ";
            }
            temp = temp->next;
        }
        std::cout << "\nfirst [ " << front() << " ]      ,     last [ " << back() <<
        " ]     ,     elements < " << getCount() << " >  ,  empty? " << isEmptyQueue() << "  ,  full? " << isFullQueue() << "\n";
        temp = nullptr; // just in case
    }
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