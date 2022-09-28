//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================ 
//---------------------------------------------------------------------------------------------------------------------------- 

 
#ifndef H_derivedLinkedStack
#define H_derivedLinkedStack
  
#include "unorderedLinkedList.h"
#include <random>


template<class T>
class linkedStackType: public unorderedLinkedList<T>             // the 6 basic functions sitting on the uo LL
{                               // takes advantage of insertFirst() and things that can implement a stack
    public:
        void initializeStack();
        bool isEmptyStack() const;
        bool isFullStack() const;
        void push(const T& newItem);
        T top() const;
        void pop();

        void int_build(const int& size, const int& min, const int& max);
        void softPrint(); // won't alter stack
}; // no functions needed, very efficient use of inheritence


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================ 
//---------------------------------------------------------------------------------------------------------------------------- 



//----------------------------------------------------------------------------------------------------------------------------
template<class T>
void linkedStackType<T>::initializeStack()
{
    unorderedLinkedList<T>::initializeList();
}

//----------------------------------------------------------------------------------------------------------------------------
template<class T>
bool linkedStackType<T>::isEmptyStack() const
{
    return unorderedLinkedList<T>::isEmptyList();
}

//----------------------------------------------------------------------------------------------------------------------------
template<class T>
bool linkedStackType<T>::isFullStack() const
{
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------
template<class T>
void linkedStackType<T>::push(const T& newElement)
{
    unorderedLinkedList<T>::insertFirst(newElement);
}

//----------------------------------------------------------------------------------------------------------------------------
template<class T>
T linkedStackType<T>::top() const
{
    return unorderedLinkedList<T>::front();	
}

//----------------------------------------------------------------------------------------------------------------------------
template<class T>
void linkedStackType<T>::pop()
{
    nodeType<T> *temp;

    if (this->count == 1)
    {
        temp = this->first;
        delete temp;
        temp = nullptr;

        this->first = nullptr;
        this->last = nullptr;
        this->count = 0;
    }
    else
    {
        temp = this->first;
        this->first = this->first->link;
        delete temp;
        this->count--;
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------
template<>
void linkedStackType<int>::int_build(const int& size, const int& min, const int& max)
{
    linkedListType<int>::destroyList();
    std::random_device rdevice{};                                // set up generator, only need one
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<int> randomNum{min, max};     // by user input
    int value = -444;

    for (int i = 0; i < size; i++)
    {
        value = randomNum(num);
        push(value);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template<class T>
void linkedStackType<T>::softPrint() // will not effect stack...no pops
{
    nodeType<T> *traverse;
    traverse = this->first;
    int counter = 1;

    std::cout << "\nthere are < " << this->count << " > elements in the stack:\n\n";
    while (traverse != nullptr)
    {
        if (counter == 1)
        {
            std::cout << "   " << counter << "   TOP [ " << traverse->info << " ]\n";
        }
        else if (counter == this->count)
        {
            std::cout << "   " << counter << "  BOTM [ " << traverse->info << " ]\n";
        }
        else
        {
            std::cout << "   " << counter << "       [ " << traverse->info << " ]\n";
        }
        traverse = traverse->link;
        counter++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================ 
//---------------------------------------------------------------------------------------------------------------------------- 
#endif
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================ 
//---------------------------------------------------------------------------------------------------------------------------- 
