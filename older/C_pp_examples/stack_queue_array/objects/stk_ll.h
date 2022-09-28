/*      ~ extra methods only apply to integers, still have more to define
    
    best to use this one if you don't know how many elements you will have / size keeps changing
    isFullStack() is just there because it is one of the 6 fundamental funcitons
    the essential features to make a stack based on a linked-list (single) are inlcuded in this single file
    no need to inherit accross many places...it is literally a stack, like a stack of books

    6 essential operations of a stack:

    initialize: puts stack to an empty state
    isEmpty:    determines if the stack is empty
    isFull:     determines if the stack is full
    push:       add new element to top of stack 
    top:        returns top element of stack
    pop:        removes top element from stack

    integer is the main dataType used to test, but need to consider char, string, double....

        [ v | * ] -> [ v | * ] -> [ v | * ] -> 0
            st
    aka: head / first   

    notice the similarities...use the linked-list addHead(value);    to push()
                              use the linked-list deleteHead();      to pop()
                              count can tell if it is empty, 
*/

#ifndef H_stk_ll
#define H_stk_ll

#include "../LIBS.h"



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------



template <class T>     // keep the nodes as simple as possible, structs are nice if there are no methods, or you like C
struct s_nodeType
{
    T data;
    s_nodeType<T> *next;
};



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------



template <class T>
class stk_llType
{
    public:

        // 6 esential operations
        void initializeStack();                     //# set the stack to an empty state, deletes everything
        bool isEmptyStack() const;                  //# true if no elements are in the stack
        bool isFullStack() const {return false;}    //# only if you run out of memeory
        void push(const T& newItem);                //# adds an element to the top of stack... there is space
        T top() const;                              //# reveals the value of the top element, if stack is not empty
        void pop();                                 //# removes top element from top of the stack, if it is not empty

        // operator overloads
        const stk_llType<T>& operator = (const stk_llType<T>& otherStack);     //# copies provided stack to current object
        bool operator == (const stk_llType<T>& otherStack);                    //# 2 stacks == if same size and elements ==
        
        
        // admin
        stk_llType();                                                       //# constructor , default
        stk_llType(const stk_arrType<T>& otherStack);                       //# copy constructor
        ~stk_llType();                                                      //' destructor

        // extra variables, tracking data structure, or other methods can be used to get more info
        // most of these functions would not be possible in a pure stack or queue

        //information (no mutilation)
        int getCount() const {return count;}                        //# returns the number of elements 
        //int getMaxSize() const {return maxSize;};                   // returns maximum number of elements object can store (no ll)               
        //T max();                                                    // returns value of largest element, if not empty
        //T min();                                                    // returns value of smallest element, if not empty
        //int max_index();                                            // returns index of largest element, if not empty
        //int min_index();                                            // returns index of smallest element, if not empty
        void soft_PrintF();                                         //# displays current stack from top to bottom
        //void soft_printB();                                         // displays current stack from bottom to top
        //bool val_exists(const T& value);                            // true if provided values is in the stack 
        //int freq_val(const T& value);                               // frequency of provided value returned (if found)
        //int first_index_val(const T& value);                        // first index of provided value returned (if found)
        //T val_at(const int index);                                  // returns the value at desired index, if legal

        //insert & edit
        //void ow_val_to(const int& index, const T& value);           // overwrites provided value to target index (if legal)                                             
        //void add_val_to(const int& index, const T& value);          // value goes to index, other element shift right (if legal)
        //void sort(const char& method);                              // sorts target stack without any changes

        //remove
        //void remove_index(const int& index);                        // deletes element at desired index, if legal
        //void remove_val(const T& value);                            // deletes value (if found)
        //void delete_all(const int& size);                           // deletes all elements, and needs an input for new size 

        //for testing ... 
        void int_build_random(const int& size, const int& min, const int& max);     //# makes stack a random stack of integers
        void int_reset();                                                           //# quick reset to internal variables below
        
        //void dub_build_random(const int& size, const int& min, const int& max);     // makes obj a random stack of doubles
        //void char_build_random(const int& size);                                    // makes obj a random stack of characters
        //void str_build_random(const int& size, const int& minL, const int& maxL);   // makes obj a random stack of strings
        

    private:

        s_nodeType<T> *stackTop;          // sits on first node (if any) ... like 'first' or 'head' in a regular linked list
        int count = 0;                  // how many elements are currently in the stack / ll

        void copy(const stk_llType<T>& otherStack);         //' only called by = overload and copy constructor...internal use only

        //for testing ... 
        int defaultSize = 10;            // if invlaid or no input is received by constructor, maxSize = 10
        int floor = 100;                 // for reset, integer testing
        int cieling = 500;               // for reset, intger testing
        int illegal = -99;                // returned when illegal operation preformed
};






//----------------------------------------------------------------------------------------------------------------------------
//============================================== important functions =========================================================
//----------------------------------------------------------------------------------------------------------------------------






//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stk_llType<T>::stk_llType() // constructor, when obj made, first/head is holstered and count is 0, there are no nodes
{
    stackTop = nullptr;
    count = 0;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stk_llType<T>::isEmptyStack() const
{
    return (stackTop == nullptr);    // or count == 0
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_llType<T>::initializeStack()
{
    s_nodeType<T> *eraser;

    while (stackTop != nullptr)    // starting at head, send eraser down list to delete all the nodes
    {
        eraser = stackTop;
        stackTop = stackTop->next;
        delete eraser;
    } // stackTop will be on nullptr, if it isn't already
    count = 0; // and reset count
    stackTop = nullptr; // just in case
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_llType<T>::push(const T& newItem) // this is what insertHead() would have done
{
    if (stackTop == nullptr) // the stack is empty
    {
        s_nodeType<T> *newNode;
        newNode = new s_nodeType<T>;   // make a new node
        newNode->data = newItem;     // take the value 
        newNode->next = nullptr;     // ground the link

        stackTop = newNode;
        newNode = nullptr;
        count++;
    }
    else // not empty
    {
        s_nodeType<T> *newNode;
        newNode = new s_nodeType<T>;   // make a new node
        newNode->data = newItem;     // take the value 
        newNode->next = stackTop;     // take link to st...insert head

        stackTop = newNode;
        newNode = nullptr;
        count++;
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T stk_llType<T>::top() const
{
    if (stackTop != nullptr) // or count != 0 ... there is at least 1 element in the stack
    {
        return stackTop->data;
    }
    else
    {
        std::cout << "\n ~ { the stack is empty } ~ \n";
        return illegal;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_llType<T>::pop() // deleteHead() equivelent
{
    if (stackTop != nullptr) // or count != 0....the stack is not empty
    {
        s_nodeType<T> *eraser;
        eraser = stackTop;
        
        stackTop = stackTop->next;
        eraser->next = nullptr;
        
        delete eraser;
        eraser = nullptr;
        count--;
    }
    else
    {
        std::cout << "\n ~ { the stack is empty } ~ \n";
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_llType<T>::copy(const stk_llType<T>& otherStack)
{
    if (stackTop != nullptr) // have to start with an empty list...insertTail()
    {
        initializeStack();
    }

    if (otherStack.stackTop == nullptr) // there is nothing to copy... otherStack is empty
    {
        stackTop = nullptr;
        count = 0;
    }
    else
    {
        s_nodeType<T> *current;
        s_nodeType<T> *last;
        s_nodeType<T> *newNode;

        current = otherStack.stackTop;   // current sits on the stack to copy
        this->count = otherStack.count;  // also get the count;  ... could put it in the loop, but should be the same
        
        stackTop = new s_nodeType<T>;      // receiver generates a new node with head pointer
        stackTop->data = current->data;  // receiver copies the data from the first node
        stackTop->next = nullptr;        // receiver grounds the new nodes link

        last = stackTop;                 // first and last are on the newly created node , last is used to input from current
        current = current->next;         // advance current to see if there is more to copy

        while (current != nullptr)
        {
            newNode = new s_nodeType<T>;  // make a new node
            newNode->data = current->data;
            newNode->next = nullptr;

            last->next = newNode;
            last = newNode;
            newNode = nullptr;
            current = current->next;
        }
        last = nullptr;
        newNode = nullptr;
        current = nullptr;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stk_llType<T>::stk_llType(const stk_arrType<T>& otherStack)
{
    stackTop = nullptr; // once made, take care of setting this so it goes through the copy() well
    copy(otherStack);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stk_llType<T>::~stk_llType()
{
    initializeStack(); // ...erases all the nodes, resets count to 0;  and stackTop to nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
const stk_llType<T>& stk_llType<T>::operator = (const stk_llType<T>& otherStack)
{
    if (this != &otherStack)    // if the memory address of this object is not the memory address of the other object 
    {                               // avoids self copy
        copy(otherStack);  // copy it
    }
    return *this; // dereferce to get memory address, then return so same object picks it up
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stk_llType<T>::operator == (const stk_llType<T>& otherStack)
{
    if (count != otherStack.count)
    {
        return false;
    }
    else 
    {
        s_nodeType<T> *current;
        s_nodeType<T> *currentO;
        current = stackTop;
        currentO = otherStack.stackTop;

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
void stk_llType<int>::int_build_random(const int& size, const int& min, const int& max)
{
    initializeStack(); // start fresh

    std::random_device rdevice{};                                      // set up generator
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{min, max};            // by user input, range of values possible

    std::default_random_engine num2{ rdevice() };
    std::uniform_int_distribution<int> randomNum2{1, size};            // by user input, determines elements in stack
    
    int newCount = randomNum2(num2); // pick a size between 1 and whatever the user provides
    int filler; // make an int var to hold some variables

    for (int i = 0; i < newCount; i++)
    {
        filler = randomNum1(num1);
        push(filler);
    }                                  // hopefully this takes care of everything

}  

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_llType<T>::soft_PrintF()
{
    if (stackTop == nullptr)
    {   
        std::cout << "\n ~ { the stack is empty } ~ \n";
    }
    else
    {
        T holder; // will take the node values for printing
        s_nodeType<T> *copier;

        copier = stackTop; // start at the head

        for (int i = 0; i < count; i++)
        {
            holder = copier->data;
            if (i == 0)
            {
                std::cout << "   TOP   " << " [ " << i + 1 << " ]   =   " << holder << "\n";
            }
            else if (i == (count - 1))
            {
                std::cout << "   BOT   " << " [ " << i + 1 << " ]   =   " << holder << "\n";
            }
            else
            {
                std::cout << "         " << " [ " << i + 1 << " ]   =   " << holder << "\n";
            }
            copier = copier->next;
        }
        copier = nullptr; // just in case
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------
template <>
void stk_llType<int>::int_reset()
{
    int_build_random(defaultSize, floor, cieling);
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
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------