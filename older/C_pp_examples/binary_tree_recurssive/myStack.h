/*
    same as before    ...stack by array     a vector or linked list if needed        
    be careful testing non-integers, turn comment out test code
*/

#ifndef H_StackType
#define H_StackType
  
#include <iostream>
#include <cassert> // for illegal operations ...just put out a message or use try/catch

#include "stackADT.h"
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
template <class T>
class stackType: public stackADT<T>
{
    public:
        const stackType<T>& operator=(const stackType<T>&);     // overload the assignment operator.
        void initializeStack();                                 // initialize the stack to an empty state
        bool isEmptyStack() const;                              // determine whether the stack is empty
        bool isFullStack() const;                               // determine whether the stack is full
        void push(const T& newItem);                            // add newItem to the stack ...if exists and has room
        T top() const;                                          // returns the top element of the stack...if exists and not empty
        void pop();                                             // remove the top element of the stack
     
        stackType(int stackSize = 100);                         // constructor
        stackType(const stackType<T>& otherStack);              // copy constructor
        ~stackType();                                           // destructor
        void softPrint();                                       // just to see what is in the stack

    private:
        int maxStackSize;                                        // variable to store the maximum stack size
        int stackTop;                                            // variable to point to the top of the stack
        T *list;                                                 // pointer to the array that holds the stack elements
                    
        void copyStack(const stackType<T>& otherStack);          // helper for copy constructor and assigment OL
};


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stackType<T>::initializeStack()
{
    //for (int i = 0; i < stackTop; i++)
    //{
      //  list[i] = -999;
    //}
    stackTop = 0; // unwanted will just get overwritten/deleted
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stackType<T>::isEmptyStack() const
{
    return(stackTop == 0);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool stackType<T>::isFullStack() const
{
    return(stackTop == maxStackSize);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stackType<T>::push(const T& newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = newItem;   // add newItem to the top of the stack
        stackTop++;                 // increment stackTop
    }
    else
    {
        std::cout << "\ncan't add to a full stack\n";
    }   
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
T stackType<T>::top() const
{
    assert(stackTop != 0);          // if stack is empty, terminate the program
    return list[stackTop - 1];      // return the element of the stack indicated by stackTop - 1
}
 
//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stackType<T>::pop()
{
    if (!isEmptyStack())
    {
        stackTop--;                 // decrement stackTop 
        //list[stackTop] = -999;
    }
    else
    {
        std::cout << "\ncan't remove from empty stack\n";
    }
        
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stackType<T>::stackType(int stackSize) 
{
    if (stackSize <= 0)
    {
        std::cout << "\nsize of the array to hold the stack must be positive\n";
        std::cout << "\ncreating an array for 100 elements\n";
        maxStackSize = 100;
    }
    else
    {
        maxStackSize = stackSize;   // set the stack size to value of parameter provided
    }
    stackTop = 0;                   // set stackTop to 0
    list = new T[maxStackSize];  // create the array to hold elements
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stackType<T>::~stackType() //destructor
{
    delete [] list; //deallocate the memory occupied by array ... I guess that was better than using a linked list
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stackType<T>::copyStack(const stackType<T>& otherStack)
{ 
    delete [] list;		                    // start fresh		   
    maxStackSize = otherStack.maxStackSize;	// take values	   
    stackTop = otherStack.stackTop;			   
    list = new T[maxStackSize];		        // make an array to hold the values   			   

    for (int j = 0; j < stackTop; j++)      // copy otherStack into this stack
    {
        list[j] = otherStack.list[j];
    }   
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
stackType<T>::stackType(const stackType<T>& otherStack)
{
    list = nullptr;           // good to set just in case
    copyStack(otherStack);    // call helper
}

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
const stackType<T>& stackType<T>::operator = (const stackType<T>& otherStack)
{ 
    if (this != &otherStack) // avoids self-copy
    {
        copyStack(otherStack);
    }
    return *this; 
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class T>
void stackType<T>::softPrint()
{
    std::cout << "\nhere is the array for the stack   {  ";
    for (int i = 0; i < maxStackSize; i++)
    {
        std::cout << list[i] << "  ";
    }
    std::cout << "}";

    std::cout << "\nelements:    < " << stackTop << " >";
    std::cout << "\nmax size:    < " << maxStackSize << " >";
    std::cout << "\n... -999 means empty , the top variable  is 1 above last used index @ :  [ " << stackTop << " ]";
    if (isEmptyStack())
    {
        std::cout << "\nthe stack is EMPTY   (also not full)";
    }
    else if (isFullStack())
    {
        std::cout << "\nthe stack is FULL    (also not empty)";
    }
    else
    {
        std::cout << "\nthe stack is NOT full,  the stack is NOT empty";
    }
    std::cout <<"\n";
    for (int i = (maxStackSize - 1); i >= 0; i--)
    {
        if (i == maxStackSize - 1 && i !=0)
        {
            std::cout << "TOP  [ " << i << " ]  , = " << " { " << list[i] << " }\n";  
        }
        else if (i == 0 && (maxStackSize - 1 != 0) )
        {
            std::cout << "BOTM [ " << i << " ]  , = " << " { " << list[i] << " }\n";
        }
        else if (i == 0 && (maxStackSize - 1 == 0) )
        {
            std::cout << "only [ " << i << " ]  , = " << " { " << list[i] << " }\n";
        }
        else
        {
            std::cout << "elem [ " << i << " ]  , = " << " { " << list[i] << " }\n";
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif // end myStack.h
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
