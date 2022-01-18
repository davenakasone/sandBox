/*     ~ extra methods only apply to integers, still have more to define

    the essential features to make a stack based on an array (dynamic) are inlcuded in this single file
    no need to inherit accross many places, but you could use the stack a a pure ADT and inherit here...only 6 methods

    this might be good if you know your size ahead of time, otherwise, the linked list is better
    if you do know the size ahead of time...just use a static array and stay off the heap...can even cut out other info
    ...it is literally a stack, like a stack of books

    6 essential operations of a stack:

    initialize: puts stack to an empty state
    isEmpty:    determines if the stack is empty
    isFull:     determines if the stack is full
    push:       add new element to top of stack 
    top:        returns top element of stack
    pop:        removes top element from stack

    integer is the main dataType used to test, but need to consider char, string, double....

    [ 0 ] [ 1 ] [ 2 ] ..... [ n - 2 ] [ n - 1 ]   n
                                                  st       stack top sits 1 above last element in this class
                                                                ...st on [ 0 ] means no elements and stack is empty
*/ 

#ifndef H_stk_arr
#define H_stk_arr

#include "../LIBS.h"



//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------



template <class T>
class stk_arrType
{
    public:

        // 6 esential operations
        void initializeStack();                     //# set the stack to an empty state, deletes everything
        bool isEmptyStack() const;                  //# true if no elements are in the stack
        bool isFullStack() const;                   //# true if no elements can be added to the stack
        void push(const T& newItem);                //# adds an element to the top of stack, if there is space
        T top() const;                              //# reveals the value of the top element, if stack is not empty
        void pop();                                 //# removes top element from top of the stack, if it is not empty

        // operator overloads
        const stk_arrType<T>& operator = (const stk_arrType<T>& otherStack);       //# copies provided stack to current object
        bool operator == (const stk_arrType<T>& otherStack);                       //# 2 stacks == if same size and elements ==
        
        
        // admin
        stk_arrType(int stackSize = 10);                                     //# constructor , will work as default
        stk_arrType(const stk_arrType<T>& otherStack);                       //# copy constructor
        ~stk_arrType();                                                      //' destructor

        // extra variables, tracking data structure, or other methods can be used to get more info
        // most of these functions would not be possible in a pure stack or queue

        //information (no mutilation)
        int getCount() const {return stackTop;}                     //# returns the number of elements 
        int getMaxSize() const {return maxSize;};                   //# returns maximum number of elements object can store (no ll)               
        T max();                                                    //# returns value of largest element, if not empty
        T min();                                                    //# returns value of smallest element, if not empty
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

        int maxSize;                    //# how many elements stack can hold
        int stackTop;                   //# sits 1 index ahead of the top element
        T *list;                        //# pointer used to make a dynamic array to hold the elements

        void copy(const stk_arrType<T>& otherStack);         //# only called by = overload and copy constructor...internal use only

        //for testing ... 
        void setBlanks();                //# called to put -99 in all the black spots
        const int blank = -99;           //# if you see it, means index is blank
        int defaultMaxSize = 10;         //# if invlaid or no input is received by constructor, maxSize = 10
        int floor = 100;                 //# for reset, integer testing
        int cieling = 500;               //# for reset, intger testing

};





//----------------------------------------------------------------------------------------------------------------------------
//============================================== important functions =========================================================
//----------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_arrType<T>::initializeStack()
{
    delete [] list;                    // delete the list and all the elements on it
    list = nullptr;                    // set the list pointer to null
    list = new T[maxSize];             // make a new array, still with the same size
    stackTop = 0;                      // set top to show empty
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stk_arrType<T>::isEmptyStack() const
{
    return (stackTop == 0);            // check needed to determine if the stack is empty
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stk_arrType<T>::isFullStack() const
{
    return (stackTop == maxSize);      // only check needed to dermine if the stack is full
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_arrType<T>::push(const T& newItem)
{
    if (!isFullStack())                          // if the stack is not full
    {
        list[stackTop] = newItem;              // put the new item in the stack
        stackTop++;                            // increment the top...top stays one above 
    }
    else
    {
        std::cout << "\n ~ { can't push to a full stack } ~\n";
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T stk_arrType<T>::top() const
{
    if (!isEmptyStack()) // could use !(stackTop == 0), get some cassert in, ect
    {
        return list[stackTop - 1];
    }
    else
    {
        std::cout << "\n ~ { nothing to show, stack is empty} ~\n";
        return blank;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_arrType<T>::pop()
{
    if (!isEmptyStack())
    {
        list[stackTop - 1] = blank;
        stackTop--;
    }
    else
    {
        std::cout << "\n { stack is empty, nothing can be removed } \n";
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stk_arrType<T>::stk_arrType(int stackSize)
{
    if (stackSize <= 0 || stackSize >  2147483646)     // needs to be positive (at least 1 element) and within integer range
    {
        std::cout << "\n ~ { a legal value for the stack size was not received } ~";
        std::cout << "\n ***** the maximum stack size will be set to a default of: " << defaultMaxSize << " elements\n";
        maxSize = defaultMaxSize;
    }
    else
    {
        maxSize = stackSize;
    }

    stackTop = 0;
    list = new T[maxSize];
    setBlanks();
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stk_arrType<T>::~stk_arrType()
{
    delete [] list;               // if the destructor deallocates array and resets top, that is all that is needed
    stackTop = 0;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_arrType<T>::copy(const stk_arrType<T>& otherStack)
{
    delete [] list;                 // need to delete array so you can copy fresh
    list = nullptr;                 // put it on null to make sure that nothing bad happens
    maxSize = otherStack.maxSize;   // get the max so you know how big to make the array
    list = new T[maxSize];          // make the new array, matching size of copy
    stackTop = otherStack.stackTop; // take top
    setBlanks();                    // get blanks filled in

    for (int i = 0; i < stackTop; i++)
    {
        list[i] = otherStack.list[i];
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stk_arrType<T>::stk_arrType(const stk_arrType<T>& otherStack)
{
    list = nullptr;               // nice to do
    copy(otherStack);             // already written to handle
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
const stk_arrType<T>& stk_arrType<T>::operator = (const stk_arrType<T>& otherStack)
{
    if (this != &otherStack) // stops self copy    also have *this != other
    {
        copy(otherStack);
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stk_arrType<T>::operator == (const stk_arrType<T>& otherStack)
{
    if (stackTop != otherStack.stackTop)
    {
        return false;
    }
    else
    {
        bool equality = true;

        for (int i = 0; i < stackTop; i++)
        {
            if (list[i] != otherStack.list[i])
            {
                equality = false;
            }
            return equality;
        }
    }
    return false;
}




//----------------------------------------------------------------------------------------------------------------------------
//================================================  fun functions   ==========================================================
//----------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------
template <>
void stk_arrType<int>::setBlanks()
{
    for (int i = stackTop; i < maxSize; i++)
    {
        list[i] = blank;                    // fill in empty positions with the blank
    }
}
//----------------------------------------------------------------------------------------------------------------------------
template <>
void stk_arrType<int>::int_build_random(const int& size, const int& min, const int& max)
{
    std::random_device rdevice{};                                      // set up generator, only need one
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{min, max};            // by user input, range of values possible

    std::default_random_engine num2{ rdevice() };
    std::uniform_int_distribution<int> randomNum2{1, size-1};            // by user input, determines elements in stack

    maxSize = size;                    // user defined
    stackTop = randomNum2(num2);       // put top at random place, within user's        

    delete [] list;            // start fresh
    list = nullptr;
    list = new int[maxSize];

    setBlanks(); // fill in with blanks

    for (int i = 0; i < stackTop; i++) // get non-blank
    {
        list[i] = randomNum1(num1);
    }
}   

//----------------------------------------------------------------------------------------------------------------------------
template <>
void stk_arrType<int>::int_reset()
{
    int_build_random(defaultMaxSize, floor, cieling);
}
//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stk_arrType<T>::soft_PrintF()
{

    if (stackTop != 0)
    {
        for (int i = (stackTop - 1); i >= 0; i--)
        {
            if (i == (stackTop-1))
            {
                std::cout << "TOP " << " [ " << i + 1 << " ]  = " << list[i] << "\n";
            }
            else if (i == 0)
            {
                std::cout << "BOT " << " [ " << i + 1 << " ]  = " << list[i] << "\n"; 
            }
            else
            {
                std::cout << "    " << " [ " << i + 1 << " ]  = "<< list[i] << "\n";
            } 
        }
    }
    else
    {
        std::cout << "\n ~ { the stack is empty } ~ \n";
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T stk_arrType<T>::max()
{
    T largest = blank;
    if (!isEmptyStack())
    {
        for (int i = 0; i < stackTop; i++)
        {
            if (list[i] > largest)
            {
                largest = list[i];
            }
        }
        return largest;
    }
    else
    {
        return largest;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T stk_arrType<T>::min()
{
    T smallest = 999;
    if (!isEmptyStack())
    {
        for (int i = 0; i < stackTop; i++)
        {
            if (list[i] < smallest)
            {
                smallest = list[i];
            }
        }
        return smallest;
    }
    else
    {
        return smallest;
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
