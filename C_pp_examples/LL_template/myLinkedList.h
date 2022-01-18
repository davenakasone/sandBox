/*
    don't be trying to use class methods that have not been defined

    need the same fucntions, but with the ability to take in pointer references
    if you are testing static with linkeListType<int> myIntLL; 
    it is fed to the function differently that testing a dynamic     linkedListType<int> *intLL;
    you can make a static class and a dynamic class, but should be careful combining both
    the dynamic class will use 'this' a lot, here is tested static
    going to need a lot of overloads to keep both, but taking param by reference & can solve a lot of that

    the template does restrict the class in some ways, but you just have to be careful to ensure
    that the valid dataTypes are always used in operations/methods

    have to work in some operator over loads
    I don't want to overload ++ and * (dereference)....just overload [] and turn it into an array
    
    it would be nice to have == be able to handle node wise comparison and entire list comparison, but with node-wise,
    the entire loop can be checked

    could do the << and >> for a prints and inputs

    definatley need the assigment operator = so the copy constructor can be used
*/

#ifndef H_myLinkedList
#define H_myLinkedList

#include <iostream>
#include <string>
#include <random> // to scramble, not sure why you would want to, but you can 

//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================
// Definition of the node

template <class T>
class nodeType 
{
    public:
        T data;                   // the information stored in the node
        nodeType<T> *next;        // the link to the next node in the list...nullptr if last node

}; // no member functions to define, keep this one simple





//==========================================================================================================================
//==========================================================================================================================
//==========================================================================================================================
// Definition of the linkedListType          going to let current do the job of the iterator

template <class T>
class linkedListType 
{
    friend std::ostream& operator << (std::ostream& osObj, const linkedListType<T>& nsObj);  // has to be this way

    public:
        // variable access & variable adjustment (for private members that can be safely modified) "getters and setters"
        int getCount() const {return count;}                              //' returns the nodes in the list
        bool isEmpty() const {return (count == 0 && head == nullptr);}    //' returns true if list has no nodes, has redundancy
        bool isAscending() const {return ascending;}                      //' true if sortAscending()) was called
        bool isDescending() const {return descending;}                    //' true if sortDescending() was called
        bool listSizeEqual(int otherList_count);                          //' true if both lists have same number of nodes
        nodeType<T>* getHead() const {return head;}                       //' normally would not want to do this, 
        nodeType<T>* getTail() const {return tail;}                            // ... make sure user doesn't abuse these
        void setHead(nodeType<T> *newHead) {head = newHead;}
        void setTail(nodeType<T> *newTail) {tail = newTail;}
        void setCount(int newCount) {count = newCount;}
       
        // for iterating
        nodeType<T>* getCurrent() const {return current;}
        void currentToTail() {current = tail;}                            //' put current on the last node "iterate" if desired
        void currentToHead() {current = head;}                            //' put current on the first node "iterate" if desired
        void currentToIndex(const int& index);                            //' helps iterate form outside
        T valueAtCurrent() {return current->data;} 
        
        // build & insert 
        void makeListfromArray(T inputArray[], int elements);             //' makes a list from an array and sets first to head
        void insertNodeTail(const T& newItem);                            //' puts new node as last node
        void insertNodeHead(const T& newItem);                            //' puts new node as first node
        void insertNodeKeepOrder(const T& newItem);                       // puts new node in list, ensuring order (if any)
        void overWrite_insertNodeAt(int index, T& newItem);               // puts value in new node at  a legal index of list
        void copyList(const linkedListType<T>& otherList);                //' copies the other list provided
        void initialize();                                                //' sets all member variables to blank list ready
        //void split(linkedListType<T>& list1, linkedListType<T>& list2, int list1_start, int list1_stop, int list2_start, int list2_stop);
        //void copySegment(linkedListType<T>& otherList, int start, int stop);
        //void shiftNodesUp();
        //void shiftNodesDown();
        //void insertUp_no_overwrite(int index, T& newItem); // makes a new index above yours and shifts everything
        //void insertDown_no_overwrite(int index, T& newItem); // makes new index below yours and shifts everything
        //void scramble();

        // removal
        void deleteNodeValue(T& deleteItem);                        //' deletes first node with value to delete, if found
        void deleteAllValues(T& deleteItem);                         //' deletes all nodes with target value...not just 1 node
        void deleteNodeIndex(int& index);                            //' deletes node at index specified
        void deleteNodeHead();                                            //' deletes first node (if any)
        void deleteNodeTail();                                            //' deletes last node (if any)
        void deleteNodeMin();                                             //' deletes node with first instance of smallest value
        void deleteNodeMax();                                             //' deletes node with first instance of largest value
        void deleteList();                                                //' all nodes are deleted, list is blank
        void deleteSegment(int startIndex, int stopIndex);                // pick a segment to delete

        // search and display
        void printListFwd();                                              //' prints the list head to tail
        void printListBwd();                                              //' prints the list tail to head
        T getDataAtIndex(int index);                                      //' returns data at node 'index'
        void sortAscending();                                             //' sorts list smallest to largest
        void sortDescending();                                            //' sorts list largest to smallest
        T getLargest();                                                   //' returns largest value in nodes (if any)
        T getSmallest();                                                  //' returns smallest value in nodes (if any)
        int getLargestIndexF();                                           //' returns first index of largest value in nodes (if any)
        int getSmallestIndexF();                                          //' returns first index of smallest value in nodes (if any)
        bool valueExists(const T& searchItem);                            //' true if item found
        int firstIndexOfValue(const T& searchItem);                       //' gives index of first find for target value, if any
        int frequencyOfValue(const T& searchItem);                        //' gives number of times value appears, if any 
          


        // operator overloads
        bool operator == (linkedListType<T>& otherList);      //' if otherList = current list, true  for static
        const linkedListType<T>& operator = (const linkedListType<T>& otherList);    // should set =
        T& operator [] (int index); // turn it into an array
        const T& operator [] (int index) const; 
        //bool operator == (linkedListType<T> *otherList);      // if otherList = current list, true  for dynamic...only 1 OL ?
        // [], ++, =,
        
        // admin
        void holsterPointers() {generator = nullptr; current = nullptr; trailer = nullptr;}  //' reset them when done
        linkedListType();                                                 //' default constructor, zeros everything out
        linkedListType(const linkedListType<T>& otherList);               //' doubles as copy constructor if pointer to first node
        ~linkedListType();                                                //' just going to make the call to delete the list
        void initializeRandomIntObj(int size); // makes a random integer ll to test w

    private:
        int count;                                           //' represents the nodes on the list, 0 if no nodes
        bool ascending;                                      //' true if ordered smallest to largest
        bool descending;                                     //' true if ordered largest to smallest
        nodeType<T> *head;                                   //' points to first node on the list
        nodeType<T> *tail;                                   //' points to last node in the list
        nodeType<T> *generator;                              //' used to make new node objects
        mutable nodeType<T> *current;                        //' mutable for user to use as an iterator
        nodeType<T> *trailer;                                //' usually lags one node behind current, when needed 

        void reverseRecursion(nodeType<T> *first);           //' only let printBwd() call this funciton.
};



//==========================================================================================================================
//                                      functions not defined inline                                                      //
//==========================================================================================================================



//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::makeListfromArray(T inputArray[], int elements)
{
    if (elements == 0)
    {
        std::cout << "/nat least one element is needed to make a linked list/n";
    }
    else if (elements < 0) 
    {
       std::cout << "/na list of negative elements can't be interpreted here/n"; 
    }
    else
    {
        deleteList(); // have to remove the current list, if there is any. Everything will be reset and ready to build
        
        for (int i = 0; i < elements; i++)
        {
            generator = new nodeType<T>;
            generator->data = inputArray[i];
            generator->next = nullptr;
            if (i == 0)                  // if taking the first element from the array, set the head
            {
                head = generator;
                tail = generator;
            }
            else
            {
                tail->next = generator;
                tail = generator;
            }
            count++;
        }
        holsterPointers();
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::insertNodeTail(const T& newItem) // not complete, improve isAscending and isDescending with a call
{
    if (head == nullptr) // the list is empty
    {
        generator = new nodeType<T>;   // make a new node
        generator->next = nullptr;     // put new node's link on nullptr because it will be inserted at the end
        generator->data = newItem;     // put the data in the new node

        head = generator;              // since list was empty, the head and tail should point to the new node
        tail = generator;

        holsterPointers();
        
        count++;
    }
    else                               // the list is not empty
    {
        generator = new nodeType<T>;   // make a new node
        generator->next = nullptr;     // put new node's link on nullptr because it will be inserted at the end
        generator->data = newItem;     // put the data in the new node

        tail->next = generator;        // take former last node next-link off nullptr and put it on the new node
        tail = generator;              // put the tail pointer on the acutal last node;

        holsterPointers();
        ascending = false; // improve this with calling a function
        descending = false; // improve this with calling a function
        count++;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::insertNodeHead(const T& newItem)
{
    generator = new nodeType<T>;     // create a new node
    generator->data = newItem;       // input the  information into the new node
    generator->next = nullptr;       // set the link of the newNode to nullptr...it will be the last node

    if (head == nullptr)             // if the list is empty, the head is on nullptr
    {
        head = generator;            // put the new node in the list
        tail = generator;  
        count++;          
        holsterPointers();
    }
    else                             // the list is not empty
    {
        current = head->next;        // send current to the second node, first node is now isolated
        generator->next = head;      // new node ready to insert
        head = generator;            // head points to new first node in LL
        count++;
        holsterPointers();
    }

}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::insertNodeKeepOrder(const T& newItem)
{

}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::overWrite_insertNodeAt(int index, T& newItem)    // this is the insert to overwrite
{
    if ( (index < 0) || (index > (count -1) ) )
    {
        std::cout << "{ enter a valid index value }";
    }
    else if (index == 0 )
    {
        deleteNodeHead();          // you can go this way if you don't want to use the iterator
        insertNodeHead(newItem);
        
    }
    else if (index == (count - 1))
    {
        deleteNodeTail();
        insertNodeTail(newItem);
    }
    else
    {
        currentToIndex(index); // don't make it any harder than it has to be ... this is the best way
        current->data = newItem;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::copyList(const linkedListType<T>& otherList)
{
    if (head != nullptr)    // need to make list empty if it is not
    {
        deleteList();
    }

    if (otherList.head == nullptr) // the other list is empty
    {
        initialize();    // just set copy to a black list
    }
    else
    {
        current = otherList.head;    // put a pointer at head of otherList
        count = otherList.count;     // find out how many elements need to be copied
        head = new nodeType<T>;      // make a new node, put head on it
        head->data = current->data;  // copy data in first node
        head->next = nullptr;        // ground out last node's link
        tail = head;                 // make the last point to the first....only one node in list now

        current = current->next;     // advance current (which is on otherList) to see if there are more nodes

        while (current != nullptr)
        {
            generator = new nodeType<T>;       // make a new node
            generator->data = current->data;   // copy the info into the new node
            generator->next = nullptr;         // ground out new node, it is getting put as last node

            tail->next = generator;            // update link on previously last node
            tail = generator;                  // advance tail to mark last node
            current = current->next;           // advance current to next node on otherList (if any)
        }
        holsterPointers(); // stop any nonsense
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::initialize()
{
    count = 0;
    ascending = false;
    descending = false;
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    generator = nullptr;
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteNodeValue(T& deleteItem) 
{
    if (count == 0) // empty list
    {
        std::cout << "{ the list is empty, nothing can be deleted }";
    }
    else if (!valueExists(deleteItem)) // the value to delete is not in the list
    {
        std::cout << "{ the value to delete is not on the list }";
    }
    else
    {
        int index = firstIndexOfValue(deleteItem);
        deleteNodeIndex(index);

    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteNodeIndex(int& index)
{
        if (head == nullptr)
    {
        std::cout << "{ the list is empty, can't delete anything }";
    }
    else if (index < 0 || index > (count - 1))
    {
        std::cout << "{ the index to delete is not valid }";
    }
    else // list is not empty and the index is valid
    {
        if (index == 0)              // index to delete is on first node
        {
            deleteNodeHead();
        }
        else if (index == (count-1)) // index to delete is on last node
        {
            deleteNodeTail();
        }
        else
        {
            currentToIndex(index-1); // put current right before node to delete
            trailer = current;       // current and trailer on the same node, right before node to be deleted
            generator = current;     // get the generator involved, now all 3 pointer are before node to delete
            generator = generator->next; // generator is on node to delete
            current = generator->next;   // current is ahead of node to delete, it is spanned
            generator->next = nullptr;   // node to delete is broken off list
            trailer->next = current;
            delete generator;             // node at index to delete is deallocated
            count--;
            holsterPointers();
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteList()
{
    if (head == nullptr) // the list is already empty, just going to reset to make sure
    {
        initialize();
    }
    else // the list has at least one item
    {
        current = head;
        while(current!= nullptr)  // not worried about losing head, 
        {
            current = current->next;
            delete head;
            head = current;
        }
        initialize();
    } 
}   

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::printListFwd()
{
    current = head;          // current starts at the head ... can even do it off size if you really want
    
    if (current == nullptr)  // list is empty
    {
        std::cout << " { the list is empty } ";
    }
    else
    {
        std::cout << "{ ";
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "}";
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::printListBwd() // you don't really have to use recursion since you already have the length
{
    if (head == nullptr)
    {
        std::cout << " { the list is empty } ";
    }
    else
    {
        current = head; // set current to head and send it away
        reverseRecursion(current);
        holsterPointers(); // in case any bad changes were made
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::reverseRecursion(nodeType<T> *first) // this is a private function so no one messes with it
{
    if (first != nullptr)
    {
        reverseRecursion(first->next);      // recursion gets to the end, then stack unwinds to print
        std::cout << first->data << " ";    
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
T linkedListType<T>::getDataAtIndex(int index)
{
    if (index < 0 || index > count-1)   // the index is valid
    {
        std::cout << "\nyou did not enter a valid index";
        return 0;
    }
    else
    {
        currentToIndex(index);
        return (current->data);
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::sortAscending()
{
    T *holder;               // prepare a pointer to creat a dynamic array of T (dataType)
    int size = getCount();   // find out how many nodes are on the list => elements in array
    holder = new T[size];    // create the array
    T temp;                  // holds the value

    // transfer values to array
    for (int i = 0; i < size; i++)
    {
        holder[i] = getDataAtIndex(i);
    }
    deleteList();   // delete the current linked list so it can be repopulated with the sorted array

    //sort the array smallest to largest
    for (int iteration = 1; iteration < size; iteration++)
    {
        for (int index = 0; index < (size - iteration); index++)
        {
            if (holder[index] > holder[index+1])
            {
                temp = holder[index];
                holder[index] = holder[index+1];
                holder[index+1] = temp;
            }
        }
    }

    //repopulat the list
    makeListfromArray(holder, size);

    holder = nullptr; // shift off
    delete holder; // dealocate
    ascending = true;
    descending = false;
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::sortDescending()
{
    T *holder;               // prepare a pointer to creat a dynamic array of T (dataType)
    int size = getCount();   // find out how many nodes are on the list => elements in array
    holder = new T[size];    // create the array
    T temp;                  // holds the value

    // transfer values to array
    for (int i = 0; i < size; i++)
    {
        holder[i] = getDataAtIndex(i);
    }
    deleteList();   // delete the current linked list so it can be repopulated with the sorted array

    //sort the array smallest to largest
    for (int iteration = 1; iteration < size; iteration++)
    {
        for (int index = 0; index < (size - iteration); index++)
        {
            if (holder[index] < holder[index+1])
            {
                temp = holder[index];
                holder[index] = holder[index+1];
                holder[index+1] = temp;
            }
        }
    }

    //repopulat the list
    makeListfromArray(holder, size);

    holder = nullptr; // shift off
    delete holder; // dealocate
    ascending = false;
    descending = true;
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListType<T>::valueExists(const T& searchItem) // you can add some enhancements to improve speed by sorting
{
    if (head == nullptr)
    {
        std::cout << " { the list is empty and can't be searched }";
        return false;
    }
    else if (count == 1 && ((head->data) == searchItem)) // length of 1 node, just see if it matches
    {
        return true;
    }
    else
    {
        current = head; // start at first node
        while (current != nullptr)
        {
            if ((current->data) == searchItem)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListType<T>::linkedListType() // default constructor just makes object ready with a blank list
{
    initialize();
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListType<T>::linkedListType(const linkedListType<T>& otherList) // declaring off another obj activates copy constructor
{
    //deleteList();        // make sure you start with a blank list...you should if constructors are working correctly
    head = nullptr;
    //this = new linkedListType<T>;
    copyList(otherList); // then get a copy
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
linkedListType<T>::~linkedListType() // destructor
{
    deleteList(); // that is all it has to do if things get out of scope    ...ensures all memory is deallocated
}                              

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListType<T>::operator == (linkedListType<T>& otherList)
{
    if (otherList.count == 0 && count == 0)
    {
        std::cout << "both lists are empty";
        return true;
    }
    else if (otherList.count != count)
    {
        std::cout << "lists have a different number of nodes, comparison can't be made";
        return false;
    }
    else
    {
        current = head;
        otherList.current = otherList.head;
        bool isSame = true;
        for (int i = 0; i < count; i++)
        {
            if (current->data != otherList.current->data) // order matters...
            {
                isSame = false;
            }
            current = current->next;
            otherList.current = otherList.current->next;
            
        }
        return isSame;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
const linkedListType<T>& linkedListType<T>::operator = (const linkedListType<T>& otherList)
{
    // an obj LLa was put into a statement LLa = LLb      where LLb is the 'otherList' parameter
    // LLb is returned to LLa after the assigment. LLa becomes LLb (value returned), but with deep copy (not same head)
    if (this != &otherList) // avoid self copy
    {
        copyList(otherList); // copies other list if assigned to something besides itself
    }
    return *this; // change this to this for statics or take it off reference
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListType<T>::listSizeEqual(int otherList_count)
{
    return (count == otherList_count);
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::currentToIndex(const int& index) // for user iteration....by index, the user should know it starts at 0 and goes to n - 1
{
    if ( (index < 0) || (index > (count - 1)) )         // can't do, not a valid index in the list
    {
        std::cout << " { the index you provided does not correspond to a node on the list }";
    }
    else                                 // the index is within a valid range
    {
        if (index == 0)                  // the user wants to put pointer on the first node
        {
            currentToHead();
        }
        else if (index == (count -1))    // the user wants to put pointer on the last node
        {
            currentToTail();
        }
        else
        {
            for (int i = 0; i <= index; i++)
            {
                if (i == 0)
                {
                    current = head;              // start the pointer on the first node in the linked list
                }
                else 
                {
                    current = current->next;     // keep advancing the pointer until you get to the right index
                }
                
            }
        }
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
T linkedListType<T>::getLargest()
{
    T max;
    if (head == nullptr)
    {
        std::cout << " { the list is empty, nothing can be done }";
        return 0;
    }
    else if ((head->next) == nullptr) // only one node
    {
        return head->data;
    }
    else
    {
        current = head; // put current at first node
        max = current->data; // set max to first node
        current = current->next; // searched first one
        while (current != nullptr) // now search the rest
        {
            if (current->data > max) // a node with a larger value than previous max was found
            {
                max = current->data;
            }
            current = current->next;
        }
        holsterPointers();
        return max;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
T linkedListType<T>::getSmallest()
{
    T min;
    if (head == nullptr)
    {
        std::cout << " { the list is empty, nothing can be done }";
        return 0;
    }
    else if ((head->next) == nullptr) // only one node
    {
        return head->data;
    }
     else
    {
        current = head; // put current at first node
        min = current->data; // set max to first node
        current = current->next; // searched first one
        while (current != nullptr) // now search the rest
        {
            if (current->data < min) // a node with a smaller value than previous min was found
            {
                min = current->data;
            }
            current = current->next;
        }
        holsterPointers();
        return min;
    }
}       

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
int linkedListType<T>::getLargestIndexF()
{
    int index = 0;
    T max = getLargest();
    if (head == nullptr)
    {
        std::cout << " { the list is empty, nothing can be done }";
        return index;
    }
    else if ((head->next) == nullptr)
    {
        return index; // only one node, it is the max and the min
    }
    else 
    {
        current = head; // set current to first node ... index 0
        while(current != nullptr)
        {
            if ((current->data) == max)
            {
                holsterPointers();
                return index; // notice it returns the first find
            }
            index++;                   // track index
            current = current->next;   // advance
        }
        holsterPointers();
        return index;
    }

}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
int linkedListType<T>::getSmallestIndexF()
{
    int index = 0;
    T min = getSmallest();
    if (head == nullptr)
    {
        std::cout << " {the list is empty, nothing can be done }";
        return index;
    }
    else if ((head->next) == nullptr)
    {
        return index; // only one node, it is the max and the min 
    }
    else 
    {
        current = head; // set current to first node ... index 0
        while(current != nullptr)
        {  
            if ((current->data) == min)
            {
                holsterPointers();
                return index; // notice it returns the first find
            }
            index++;                   // track index
            current = current->next;   // advance
        }
        holsterPointers();
        return index;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
std::ostream& operator << (std::ostream& osObj, const linkedListType<T>& nsObj)
{
    if (nsObj.head == nullptr)
    {
        //T tempy = nsObj.getDataAtIndex(0);
        //std::cout << "{ empty }";
        osObj << 0;
        return osObj;
    }
    else
    {
        std::string outputSeq;
        for (int i = 0; i < nsObj.count; i++)
        {
            outputSeq = outputSeq + nsObj.getDataAtIndex(i);
            outputSeq = outputSeq + " ";
        }
    
        osObj << outputSeq;
        return osObj;
    }

}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteNodeHead()
{
    if (count == 0)
    {
        std::cout << "{ there is nothing to delete, the list is empty }";
    }
    else
    {
        if (count == 1)
        {
            deleteList();       // only one node, reset everything to a blank list
        }
        else
        {
            current = head;    // current takes first node
            head = head->next; // head advances to the second node
            delete current;    // delete first node
            holsterPointers();
            count--;
        }
    }
}


//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteNodeTail()
{
    if (count == 0)
    {
        std::cout << "{ there is nothing to delete, the list is empty }";
    }
    else
    {
        if (count == 1)
        {
            deleteList();       // only one node, reset everything to a blank list
        }
        else
        {
            currentToIndex(count-2);               // set current to node before last
            tail = current;                        // move tail one node back, so node can be deleted
            current = current->next;               // advance current to last node
            tail->next = nullptr;               // it is now the last node, so put it on nullptr
            delete current;                        // delete the last node
            holsterPointers();
            count--;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteNodeMin()
{
    if (count == 0) // no nodes
    {
        std::cout << "\n { the list is empty, there is nothing to delete }";
    }
    else if (count == 1) // only one node
    {
        deleteNodeHead();
    }
    else
    {
        int toDelete = getSmallestIndexF();
        deleteNodeIndex(toDelete);
    }
    
}
//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteNodeMax()
{
    if (count == 0) // no nodes ... add   && head == nullptr    for redundancy if you want
    {
        std::cout << "\n { the list is empty, there is nothing to delete }";
    }
    else if (count == 1) // only one node
    {
        deleteNodeHead();
    }
    else
    {
        int toDelete = getLargestIndexF();
        deleteNodeIndex(toDelete);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
int linkedListType<T>::firstIndexOfValue(const T& searchItem)
{
    int index = 0;
    if (head == nullptr)
    {
        std::cout << " { the list is empty }";
        return -1;
    }
    else if ( (count == 1) && ( (head->data) == searchItem ) )    // list had one node and it matched the search item
    {
        return index;
    }
    else if (!valueExists(searchItem))
    {
        std::cout << " { search item is not in the list }";
        return -1;
    }
    else
    {
        current = head; // start at first node
        while (current != nullptr)
        {
            if ((current->data) == searchItem)
            {
                holsterPointers();
                return index;
            }
            index++;
            current = current->next; // advance to next node
        }
        return -1;
    }

}

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
int linkedListType<T>::frequencyOfValue(const T& searchItem)
{
    int freq = 0;
    current = head; // start at first node
    while (current != nullptr)
    {
        if ((current->data) == searchItem)
        {
            freq++;
        }
        current = current->next;
    }
    return freq;
}
//--------------------------------------------------------------------------------------------------------------------------
template <class T>
void linkedListType<T>::deleteAllValues(T& deleteItem)
{   
    if (frequencyOfValue(deleteItem) == 0) // not on list or list is empty
    {
        std::cout << "{ the value is already gone from the list }";
    }
    else
    {
        //int counter = 0;
        nodeType<T> *special;
        special = head;

        // the easy way...lowest LCV requirement, minimal need for pointers, by this point, built in functions used to help
        int freq = frequencyOfValue(deleteItem); // number of times values shows up, acts as LCV
        int position;                            // to show index value to delete occurs
        for (int i = 0; i < freq; i++)
        {
            if (valueExists(deleteItem))         // still have some items to delete
            {
                position = firstIndexOfValue(deleteItem);   // find the first index of the value to delete
                deleteNodeIndex(position);             // get rid of it
            }
        }


        /*                          the hard way
        bool allGone = false;
        while (!allGone)
        {
            if ((special->data) == deleteItem)
            {
                deleteNodeValue(deleteItem);
            }

            if (!valueExists(deleteItem))
            {
                allGone = true;
            }

            if ((special->next) != nullptr)
            {
                special = special->next;
            }
            else
            {
                allGone = true; // just in case
            }
            
        }
        */

        special = nullptr; // clean up the mess
    }
}
//--------------------------------------------------------------------------------------------------------------------------
template <class T>
T& linkedListType<T>::operator [] (int index)
{
    if (index < 0 || index > (count - 1))
    {
        std::cout << "{ out of range }";
        T tempy = getDataAtIndex(0);
        return tempy;
    }
    else
    {
        T temp;
        temp = getDataAtIndex(index);
        return temp;
    }
}
        
//--------------------------------------------------------------------------------------------------------------------------
template <class T>
const T& linkedListType<T>::operator [] (int index) const // the constant version
{
    if (index < 0 || index > (count - 1))
    {
        std::cout << "{ out of range }";
        T tempy = getDataAtIndex(0);
        return tempy;
    }
    else
    {
        T temp;
        temp = getDataAtIndex(index);
        return temp;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template<> // template specialization
void linkedListType<int>::initializeRandomIntObj(int size)
{
    std::random_device rdevice{};
    std::default_random_engine integer{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomInteger{100,600};

    int *filler;
    filler = new int[size];

    for (int i = 0; i < size; i++)
    {
        filler[i] = randomInteger(integer);
    }

    int temp;

    for (int i = 0; i < size; i++)
    {
        temp = filler[i];
        insertNodeTail(temp);
    }

    filler = nullptr;
    delete filler;
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------

#endif // H_myLinkedList.h
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------





//==========================================================================================================================
//                                                    failures                                                            //
//==========================================================================================================================
/*

//--------------------------------------------------------------------------------------------------------------------------
template <class T>
bool linkedListType<T>::operator == (linkedListType<T>& otherList)             can't take a dynamic
{
    if (otherList.count == 0 && count == 0)
    {
        std::cout << "both lists are empty";
        return true;
    }
    else if (otherList.count != count)
    {
        std::cout << "lists have a different number of nodes, comparison can't be made";
        return false;
    }
    else
    {
        current = head;
        otherList.current = otherList.head;
        bool isSame = true;
        for (int i = 0; i < count; i++)
        {
            if (current->data != otherList.current->data) // order matters...
            {
                isSame = false;
            }
            current = current->next;
            otherList.current = otherList.current->next;
            
        }
        return isSame;
    }
}

can't have 2 things going different ways


        for (int i = 0; i <= count; i++)
        {
            if ( (special->data) == deleteItem)
            {
                deleteNodeValue(deleteItem);
            }
            special = special->next;
        }
    
        while (special != nullptr) // not sure why this does not work
        {
            if ((special->data) == deleteItem)
            {
                deleteNodeIndex(counter);
            }
            counter++;
            special = special->next;
        }
        





*/