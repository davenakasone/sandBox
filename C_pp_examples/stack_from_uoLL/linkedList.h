#ifndef H_LinkedListType
#define H_LinkedListType
   
#include <iostream>
#include <string>
#include <cassert>


//-----------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================
//                                           Definition of the node                                                          //
//=============================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------------


template <class T>
struct nodeType                // make it a struct to be simple, change to class if needed
{
	T info;                    // data in the node       T could be int, double, char, string, or something else
	nodeType<T> *link;         // a pointer to the next node in the list (this is only a single-linked list)
};                             // nice and simple, no functions to define


//-----------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================
//                                           Definition of the linked list iterator                                          //                 //
//=============================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------------

template <class T>             // an iterator is an object that produces each element of a container
class linkedListIterator       // supposed to be helpful in processing each node, an object for linkedListType 
{
    public:
        linkedListIterator();
         /*
            Default constructor
            Postcondition: current = nullptr;
         */

        linkedListIterator(nodeType<T> *ptr);
         /*
            Constructor with a parameter
            Postcondition: current = ptr;
         */

        T operator * ();
         /*
            Function to overload the dereferencing operator *
            Postcondition: returns the info contained in the node
         */

        linkedListIterator<T> operator ++ ();
         /*    
            Overload the pre-increment operator
            Postcondition: the iterator is advanced to the next node
         */

        bool operator == (const linkedListIterator<T>& right) const; 
         /*
            Overload the equality operator
            Postcondition: returns true if this iterator is equal to the iterator specified by right, 
            otherwise it returns the value false
         */

        bool operator != (const linkedListIterator<T>& right) const; 
         /*
            Overload the not equal to operator
            Postcondition: returns true if this iterator is not equal to the iterator specified by right,
            otherwise it returns the value false
         */

    private:
        nodeType<T> *current; //pointer to point to the current node in the linked list
};


//=============================================================================================================================
//=============================================================================================================================


//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListIterator<T>::linkedListIterator()
{
    current = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListIterator<T>::linkedListIterator(nodeType<T> *ptr)
{
    current = ptr;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
T linkedListIterator<T>::operator * ()
{
    return current->info;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListIterator<T> linkedListIterator<T>::operator ++ ()   
{
    current = current->link;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListIterator<T>::operator == (const linkedListIterator<T>& right) const
{
    return (current == right.current);
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListIterator<T>::operator != (const linkedListIterator<T>& right) const
{    
    return (current != right.current);
}


//-----------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================
//                                       Definition of the linkedListType class                                              //         //
//=============================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------------


template <class T>
class linkedListType
{
    public:
        const linkedListType<T>& operator = (const linkedListType<T>& otherList);  
         /*
            Overload the assignment operator
         */

        void initializeList(); 
         /*
            Initialize the list to an empty state
            Postcondition: first = nullptr, last = nullptr, count = 0;
         */

        bool isEmptyList() const;
         /*
            Function to determine whether the list is empty
            Postcondition: returns true if the list is empty, otherwise it returns false
         */

        void print() const;
         /*
            Function to output the data contained in each node
            Postcondition: none
         */

        int length() const;
         /*
            Function to return the number of nodes in the list
            Postcondition: the value of count is returned
         */

        void destroyList();
         /*
            Function to delete all the nodes from the list
            Postcondition: first = nullptr, last = nullptr, count = 0;
         */

        T front() const; 
         /*
            Function to return the first element of the list
            Precondition: the list must exist and must not be empty
            Postcondition: if the list is empty, the program terminates,
            otherwise, the first element of the list is returned
         */

        T back() const; 
         /*
            Function to return the last element of the list
            Precondition: the list must exist and must not be empty
            Postcondition: if the list is empty, the program terminates,
            otherwise, the last element of the list is returned
         */

        virtual bool search(const T& searchItem) const = 0;
         /*
            Function to determine whether searchItem is in the list
            Postcondition: Returns true if searchItem is in the list, 
            otherwise the value false is returned

            improved algo for ordered list, pure virtual function
         */

        virtual void insertFirst(const T& newItem) = 0;
         /*
            Function to insert newItem at the beginning of the list
            Postcondition: first points to the new list, newItem is nserted at the beginning of the list, 
            last points to the last node in the list, and count is incremented by 1

            not applicable to ordered list, pure virtual function
         */

        virtual void insertLast(const T& newItem) = 0;
         /*
            Function to insert newItem at the end of the list
            Postcondition: first points to the new list, newItem is inserted at the end of the list,
            last points to the last node in the list, and count is incremented by 1

            not applicable to ordered list, pure virtual function
         */

        virtual void deleteNode(const T& deleteItem) = 0;
         /*
            Function to delete deleteItem from the list
            Postcondition: if found, the node containing deleteItem is deleted from the list
            first points to the first node, last points to the last node of the updated 
            list, and count is decremented by 1

            applicable to the ordered and unordereed, pure virtual function
         */

        linkedListIterator<T> begin();
         /*
            Function to return an iterator at the begining of the linked list
            Postcondition: returns an iterator such that current is set to first
         */

        linkedListIterator<T> end();
         /*
            Function to return an iterator one element past the last element of the linked list
            Postcondition: returns an iterator such that current is set to nullptr
         */

        linkedListType(); 
         /*
            Default constructor
            Initializes the list to an empty state
            Postcondition: first = nullptr, last = nullptr, count = 0; 
         */
        
        linkedListType(const linkedListType<T>& otherList); 
         /*
            copy constructor   ... you can have two of these, thing about getting one for the pointer
         */
        
        ~linkedListType();   
         /*
            Destructor, eletes all the nodes from the list
            Postcondition: The list object is destroyed ...blank state
         */
         int getCount() {return count;} // had to add

    protected:                      // for easy access of ordered and unordered 
        int count;                  // variable to store the number of elements in the list
        nodeType<T> *first;         // pointer to the first node of the list
        nodeType<T> *last;          // pointer to the last node of the list

    private: 
        void copyList(const linkedListType<T>& otherList); 
         /*
            Function to make a copy of otherList
            Postcondition: a copy of otherList is created and assigned to this list

            only used to implement copy constructor and overload assigment operator, that's why it is private
         */
};


//=============================================================================================================================
//=============================================================================================================================


//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListType<T>::isEmptyList() const
{
    return (first == nullptr);                          // if the list is empty, first will be on nullptr
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListType<T>::linkedListType()                     // default constructor, just a blank list
{
    first = nullptr;
    last = nullptr;
    count = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::destroyList()
{
    nodeType<T> *temp;              // pointer to deallocate the memory occupied by the node

    while (first != nullptr)        // while there are nodes in the list
    {                               
        temp = first;               // set temp to the current node
        first = first->link;        // advance first to the next node
        delete temp;                // deallocate the memory occupied by temp
    }

    last = nullptr;                 // initialize last to nullptr, first has already been set to nullptr by the while loop
    count = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::initializeList()
{
	destroyList();                  // if the list has any nodes, delete them....why not just use destroy?
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::print() const
{
    nodeType<T> *current;           // pointer to traverse the list

    current = first;                // set current so that it points to the first node
    
    std::cout << "{  ";
    while (current != nullptr)      // while more data to print
    {
        std::cout << current->info << "  ";
        current = current->link;
    }
    std::cout << "}";
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
int linkedListType<T>::length() const
{
    return count;
}  

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
T linkedListType<T>::front() const
{   
    assert(first != nullptr);       // check to see if list is empty before calling
    return first->info;             // return the info of the first node	
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
T linkedListType<T>::back() const
{   
    assert(last != nullptr);           // check to see if list is empty before calling
    return last->info;                 // return the info of the last node	
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListIterator<T> linkedListType<T>::begin()
{
    linkedListIterator<T> temp(first); // iterator to head   current = first;
    return temp;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListIterator<T> linkedListType<T>::end()
{
    linkedListIterator<T> temp(nullptr);
    return temp;
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::copyList(const linkedListType<T>& otherList) 
{
    nodeType<T> *newNode;               // pointer to create a node
    nodeType<T> *current;        // pointer to traverse the list     .... I think this is where it picks off the iterator ###

    if (first != nullptr)               // if the list is not empty, make it empty
    {
        destroyList();                  // useful function
    }
       

    if (otherList.first == nullptr)     // otherList is empty, just set copy to an empty list...or call initialize()
    {
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.first;            // current takes head of list to be copied
        count = otherList.count;              // find out how many nodes there are to copy

        first = new nodeType<T>;              // create the node a new node
        first->info = current->info;          // copy the info into the first node
        first->link = nullptr;                // set the link field of the first node to nullptr....it is also last node
    
        last = first;                         // make last point to the also....first node is first and last node
        current = current->link;              // make current point to the next (second node)

        while (current != nullptr)                   // copy remaining list (if any)
        {
            newNode = new nodeType<T>;               // create a node
            newNode->info = current->info;           // copy the info into the node you created
            newNode->link = nullptr;                 // set the link of the new node to nullptr, it is the last node
                    
            last->link = newNode;                    // attach newNode after last
            last = newNode;                          // make last point to new last node (that was just made)
            current = current->link;                 // make current point to the next node to copy (if any)
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListType<T>::~linkedListType() // destructor, you only get one per class
{
   destroyList();    // if you end up getting the dynamic copy in, overload the destroyList()
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListType<T>::linkedListType(const linkedListType<T>& otherList)  // copy constructor
{
    first = nullptr;           // copyList() will check this...set it now to be safe
    copyList(otherList);
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
const linkedListType<T>& linkedListType<T>::operator = (const linkedListType<T>& otherList)  // overload the assignment operator
{ 
    if (this != &otherList) // avoid self-copy, remember every object has a generic pointer to it (this)
    {
        copyList(otherList);
    }
     return *this;            // by returning a dereferenced pointer, you give the address of (return type used)
}

#endif  // end linkedList.h
