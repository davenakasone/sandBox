/*
    you do have to consider 2 pointers, but using a current and trailCurrent is easy
    see how many extras you need to get buy

    there is a better way to return for empty ...You have two options: return something or throw...if you throw, you have to catch
*/

#ifndef H_doublyLinkedList
#define H_doublyLinkedList
#include <iomanip>
#include <iostream> 
#include <cassert>
#include <random>
#include <string>
#include <chrono>
#include <thread>

//----------------------------------------------------------------------------------------------------------------------------------
//==================================================================================================================================
//                                                 Definition of the node                                                         //
//----------------------------------------------------------------------------------------------------------------------------------
//==================================================================================================================================
  
template <class T>
struct nodeType
{  
    T info;
    nodeType<T> *next;
    nodeType<T> *back;  
}; // no member functions, may want to use a class and some getters/setters...keep those private



//----------------------------------------------------------------------------------------------------------------------------------
//==================================================================================================================================
//                                                 Definition of the list                                                        //
//----------------------------------------------------------------------------------------------------------------------------------
//==================================================================================================================================


template <class T>
class doublyLinkedList
{
    public:
        const doublyLinkedList<T>& operator = (const doublyLinkedList<T>& otherList);
         /*
            Overload the assignment operator
         */

        void initializeList();
         /*
            Function to initialize the list to an empty state
            Postcondition: first = nullptr; last = nullptr; count = 0;
         */

        bool isEmptyList() const;
         /*
            Function to determine whether the list is empty
            Postcondition: Returns true if the list is empty, otherwise returns false
         */

        void destroy();
         /*
            Function to delete all the nodes from the list
            Postcondition: first = nullptr; last = nullptr; count = 0;
         */

        void print() const;
         /*
            Function to output the info contained in each node
         */

        void reversePrint() const;
         /*
            Function to output the info contained in each node in reverse order
         */

        int length() const;
         /*
            Function to return the number of nodes in the list
            Postcondition: The value of count is returned
         */

        T front() const;
         /*
            Function to return the first element of the list
            Precondition: The list must exist and must be nonempty.
            Postcondition: If the list is empty, the program terminates; otherwise, the first element of the list is returned 
         */

        T back() const;
         /*
            Function to return the last element of the list
            Precondition: The list must exist and must be nonempty.
            Postcondition: If the list is empty, the program terminates; otherwise, the last element of the list is returned
         */ 

        bool search(const T& searchItem) const;
         /* 
            Function to determine whether searchItem is in the list
            Postcondition: Returns true if searchItem is found in the list, otherwise returns false
         */

        void insert(const T& insertItem);
        /* Function to insert insertItem in the list.
            Precondition: If the list is nonempty, it must be in order
            Postcondition: insertItem is inserted at the proper place in the list, first points to the first node,
            last points to the last node of the new list, and count is incremented by 1
         */

        void deleteNode(const T& deleteItem);
         /*
            Function to delete deleteItem from the list
            Postcondition: If found, the node containing deleteItem is deleted from the list; first points
            to the first node of the new list, last points to the last node of the new list, and count is decremented by 1,
             otherwise, an appropriate message is printed
         */

        doublyLinkedList(); 
         /*
            default constructor, initializes the list to an empty state
            Postcondition: first = nullptr; last = nullptr; count = 0;
         */

        doublyLinkedList(const doublyLinkedList<T>& otherList);
         /*
            copy constructor
         */ 
      
        ~doublyLinkedList(); 
         /*
            destructor
            Postcondition: the list object is destroyed
         */

        // admin...just some extras ---------------------------------------------------------------------
        
        //initialize
        void manualCreate();                                // to manually create a linked list
        void str_randomBuild(int size);                     // have to go individually and use template specific to data type
        void int_randomBuild(int size);                     //
        void char_randomBuild(int size);                    //
        void dub_randomBuild(int size);                     // only has int, double, char, string
        
        // info
        bool ascending = false;                              // this is a variable you can use, call sort() to activate it
        bool descending = false;                             // this is a variable you can use, call sort() to activate it
        bool isAscending() {return ascending;}
        bool isdescending() {return descending;}
        T max();                                             // returns max value found in list
        T min();                                             // returns smallest value found in list
        void sort(const char method);                        // 'a' for ascending, 'd' for descending
        T valueAtIndex(int& index);                          // returns value at index provided (0....n-1) for index of n
        int freqOfValue(T& value);                           // tells you how many times this value shows up in the list (0 to n)
        int firstIndexOfValue(T& value);                      // find the first index the value shows up at
        void spinAround3times();                              // make a circular linked list and print it out 3 times

        // remove
        void deleteNodeHead();                                // deletes first node
        void deleteNodeTail();                                // deletes last node
        void deleteAllOfValue(T& value);                      // deletes all of the occurances of target value (if any)
        void deleteNodeIndex(int& index);                     // give it an index and it will delete the node there

        //insert
        void insertHead(T& value);                            // puts value in new node at front of list
        void insertTail(T& value);                            // puts value in new node at end of list
        void OWinsertNodeIndex(int& index, T& value);         // give it an index and a value to overwrite-insert
        void insertAtIndex(int& index, T& value);             // no over_write, just slides in at index and pushes currents right

    protected: // can put private if you aren't deriving objects on top of this
        int count;                  // how many nodes are in the list
        nodeType<T> *first;         // pointer to the first node
        nodeType<T> *last;          // pointer to the last node

    private:
        void copyList(const doublyLinkedList<T>& otherList); 
         /*
            Function to make a copy of otherList...keep it private
            Postcondition: a copy of otherList is created and assigned to this list
         */
};



//==================================================================================================================================



//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
doublyLinkedList<T>::doublyLinkedList()    // default constructor...or call initialize/delete
{
    first= nullptr;
    last = nullptr;
    count = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
bool doublyLinkedList<T>::isEmptyList() const
{
    return (first == nullptr);
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::destroy()
{ 
    nodeType<T>  *temp; // pointer to delete the node
	
    while (first != nullptr)
    {
        temp = first;
        first = first->next;
        delete temp;
    }

    last = nullptr; // first set to null inside loop
    count = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::initializeList()
{
    destroy(); // one way of getting to an empty state
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
int doublyLinkedList<T>::length() const
{
    return count;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::print() const
{
    nodeType<T> *current; // pointer to traverse the list
    current = first;  // set current to point to the first node

    std::cout << "{  ";
    while (current != nullptr)
    {
        std::cout << std::fixed << std::showpoint << std::setprecision(3); // set presistants
        std::cout << current->info << "  ";  // output info
        current = current->next;
    }
    std::cout << "}";
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::reversePrint() const // easier than recursion, since you already have a path
{
    nodeType<T> *current; //pointer to traverse the list
    current = last;  //set current to point to the last node

    std::cout << "{  ";
    while (current != nullptr)
    {
        std::cout << std::fixed << std::showpoint << std::setprecision(3); // set presistants
        std::cout << current->info << "  ";  
        current = current->back;
    }
    std::cout << "}";
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
bool doublyLinkedList<T>::search(const T& searchItem) const
{
    bool found = false;
    nodeType<T> *current;     // pointer to traverse the list
    current = first;          // put it on the first node and do what you did for the singly linked list

    while (current != nullptr && !found)
    {
        if (current->info == searchItem)
        {
            found = true;
            return true;
        }
        else
        {
            current = current->next;
        }
    }       
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
T doublyLinkedList<T>::front() const
{
    assert(first != nullptr);
    return first->info;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
T doublyLinkedList<T>::back() const
{
    assert(last != nullptr);
    return last->info;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::insert(const T& insertItem) // was designed to keep order, but I changed it
{
    nodeType<T> *current;        // pointer to traverse the list
    nodeType<T> *trailCurrent;   // pointer just before current
    nodeType<T> *newNode;        // pointer to create a node
    bool found = false;          // indicator

    newNode = new nodeType<T>;   // create the node
    newNode->info = insertItem;  // store the new item in the node
    newNode->next = nullptr;     // set the next to null, for safety
    newNode->back = nullptr;     // set the last to null, for safety

    if(first == nullptr)         // if the list is empty, newNode is only node you need
    {
       first = newNode;
       last = newNode;
       count++;
    }
    else                                       // the list is not empty
    { 
        current = first;                       // start at first node 

        while (current != nullptr && !found)   // search the list
        {
            if (current->info == insertItem)   // found it
            {
                found = true;
            }
            else
            {
                trailCurrent = current;         // bring up the span
                current = current->next;
            }
        }
            
        if (current == first)                   // insert newNode before first, it is smaller, seach stopped on first node
        {
            first->back = newNode;              // take first to point back to the newn ode
            newNode->next = first;              // the new node next link points to current first node
            first = newNode;                    // head comes back on first node
            count++;                            // increment
        }
        else
        {
            if (current != nullptr)              // insert newNode between trailCurrent and current...not on end
            {
                trailCurrent->next = newNode;    // low side next to new node
                newNode->back = trailCurrent;    // new node points back to low side of the span
                newNode->next = current;         // new node points next to high side of span, new node is tied in
                current->back = newNode;         // high side back points to new node, new node is inserted
            }
            else                                 // the new node gets inserted at the end
            {
                trailCurrent->next = newNode;
                newNode->back = trailCurrent;
                last = newNode;
            }
            count++; // increment
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::deleteNode(const T& deleteItem)
{
    nodeType<T> *current;            // pointer to traverse the list
    nodeType<T> *trailCurrent;       // pointer just before current
    bool found = false;

    if (first == nullptr)            // the list is empty
    {
         std::cout << " { cannot delete from an empty list }"; 
    }
    else if (first->info == deleteItem) // node to be deleted is first node
    {
        current = first;                // put current on the first node  
        first = first->next;            // get first node to next one...it is about to be deleted

        if (first != nullptr)           // if the list only had 1 node...
        {
            first->back = nullptr;      // its the first node now, so it's back link is nullptr...next already on nullptr
        }
        else                            // list had more than 1 node, node to delete was not first one
        {
            last = nullptr;             // last should stay on nullptr, if it is not already
        }
        count--;                        // decrement
        delete current;                 // delete        ...i would adjust next and back on current before deleting
    }
    else 
    {
        current = first;                     // set up on first node

        while (current != nullptr && !found)  //search the list
        {
            if (current->info == deleteItem)
            {
                found = true; // should stop loop
            }
            else
            {
                current = current->next;
            }
        }
                
        if (current == nullptr) // or !found...got to the end of list without finding anything
        {
            std::cout << "{ item to be deleted is not in the list }";
        }
        else if (current->info == deleteItem)  // or found....
        {
            trailCurrent = current->back;             // put trailer one node behind node to delete
            trailCurrent->next = current->next;       // span the node to delete, could even be nullptr

            if (current->next != nullptr)             // the node to delete is the not the last node 
            {
                current->next->back = trailCurrent;   // point back to trailer and complete span
            }
                
            if (current == last)                      // if you are going to delete the last node, put last on trailer
            {
                last = trailCurrent;
            }
            count--;                                  // decrement and delete
            delete current;
        }
        else
        {
            std::cout << "{ item to be deleted is not in list }"; 
        }       
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::copyList(const doublyLinkedList<T>& otherList)
{
    nodeType<T> *newNode; // pointer to a new node
    nodeType<T> *current; // pointer to iterate

    if (first != nullptr)   // the list is not empty
    {
        destroy();
    }

    if (otherList.first == nullptr) // the other list is empty, just initiialize
    {
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.first;        // take head of other list so you can start copying it
        // and copy the first node
        first = new nodeType<T>;          // make a new node with the head
        first->info = current->info;      // copy data from the node1 of the other list
        first->back = nullptr;            // ground the links
        first->next = nullptr;

        last = first;                      // because only 1 node had been copied so far
        current = current->next;           // advance to 2nd node of list you are trying to copy

        while (current != nullptr)         // if there are still more to copy....
        {
            
            newNode = new nodeType<T>;        // make a new node   
            newNode->info = current->info;    // copy the data
            newNode->next = nullptr;          // ground links
            newNode->back = nullptr;

            last->next = newNode;             // set next of existing node via last
            newNode->back = last;             // and use last again to set the back of the new node
            last = newNode;                   // finally, put last on the newly inserted node

            current = current->next;          // and advance current, repeat until end...
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T>& otherList) // copy constructor
{
	first = nullptr; // has to be set before copying
    copyList(otherList);
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
const doublyLinkedList<T>& doublyLinkedList<T>::operator = (const doublyLinkedList<T> & otherList)
{
	if (this != otherList) // don't self copy
    {
        copyList(otherList);
    }
    return *this;       // you return a dereferenced pointer
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
doublyLinkedList<T>::~doublyLinkedList()
{
	destroy(); // all there is to it
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::insertHead(T& value)
{
    nodeType<T> *newNode;             // a pointer to make new nodes
    newNode = new nodeType<T>;        // create a new node
    newNode->info = value;            // put the value to add in the newly created node
    newNode->next = nullptr;          // ground out links
    newNode->back = nullptr; 

    if (first == nullptr)   // the list is empty
    {
        first = newNode;    // put head on the new node
        last = newNode;     // put tail on the new node 
        newNode = nullptr;  // break it away
        delete newNode;
        count++;            // increment the count
    }
    else            // should work for any other case (first->next == nullptr)  // there is only one node in the list
    {
        newNode->next = first;        // back link is good, already on null, just take first (or last)
        first->back = newNode;        // update backlink off nullptr
        first = newNode;              // update first to sit at head ...don't touch last, it is already good
        newNode = nullptr;            // get it out of the way, the list is set
        delete newNode;
        count++;                      // increment
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <>
void doublyLinkedList<std::string>::str_randomBuild(int size) // quick initialization for strings
{
    destroy();
    std::string *filler; // a string pointer
    filler = new std::string[size]; // a dynamic 1D array of size specified by user is made
    char holder;
    const unsigned int minLength = 3; // minimun size string can be
    const unsigned int maxLength = 9; // maximum size string can be;

    std::random_device rdevice{};
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum1{minLength,maxLength}; // the range of lengths for each string in array

    std::default_random_engine num2{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum2{65,90}; // don't change this one too much, these are ascii

    for (int i = 0; i < size; i++) 
    {
        filler[i] = ""; // initialize
        for (int j = 0; j < randomNum1(num1); j++)
        {
            holder = randomNum2(num2);
            filler[i] = filler[i] + holder;
        }
        insertHead(filler[i]); // add it in anywhere
    }
    filler = nullptr;
    delete [] filler;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <>
void doublyLinkedList<int>::int_randomBuild(int size)
{
    destroy();
    int *filler; // an integer pointer
    filler = new int[size]; // a dynamic 1D array of size specified by user is made
   
    const unsigned int minLength = 0; // minimun size 
    const unsigned int maxLength = 999; // maximum size

    std::random_device rdevice{};
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum1{minLength,maxLength}; // the range of lengths for each number

    for (int i = 0; i < size; i++) 
    {
        filler[i] = randomNum1(num1); // get it
        insertHead(filler[i]); // add it in anywhere
    }
    filler = nullptr;
    delete [] filler;
}
        
//----------------------------------------------------------------------------------------------------------------------------------
template <>
void doublyLinkedList<char>::char_randomBuild(int size)
{
    destroy();
    char *filler; // a char pointer
    filler = new char[size]; // a dynamic 1D array of size specified by user is made
    
    const unsigned int minLength = 65; // minimun size string can be
    const unsigned int maxLength = 90; // maximum size string can be;

    std::random_device rdevice{};
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum1{minLength,maxLength}; // don't change this one too much, these are ascii

    for (int i = 0; i < size; i++) 
    {
        filler[i] = randomNum1(num1); // get it in array
        insertHead(filler[i]); // add it in anywhere
    }
    filler = nullptr;
    delete [] filler;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <>
void doublyLinkedList<double>::dub_randomBuild(int size)
{
    destroy();
    double *filler; // a double pointer
    filler = new double[size]; // a dynamic 1D array of size specified by user is made
   
    const unsigned int minLength = 0; // minimun size 
    const unsigned int maxLength = 999; // maximum size

    std::random_device rdevice{};
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum1{minLength,maxLength}; // the range of lengths for each number

    for (int i = 0; i < size; i++) 
    {
        filler[i] = randomNum1(num1) / 3.1416; // get it
        insertHead(filler[i]); // add it in anywhere
    }
    filler = nullptr;
    delete [] filler;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::sort(const char method) // small to large = a, large to small = d
{
    if (method != 'a' && method != 'd') // invalid seletection
    {
        std::cout << " { parameter = 'a' for ascending sort, or 'd' for 'decending' sort }";
    }
    else
    {
        T *infoArray;                // a pointer to target dataType
        int size = count;            // find out how many elements to get into this dynamic array
        infoArray = new T[size];     // make an array

        nodeType<T> *current;        // a pointer to a node
        current = first;              // put it on the head

        for (int i = 0; i < size; i++)
        {
            infoArray[i] = current->info;        // take the value at the node into the array
            current = current->next;             // advance current to next node
        }
    
        destroy();                               // clear out the linked list, the values are safely stored in the array
        T temp;                                  // need a temporary variable to hold the bubble sort transfer

        for (int iteration = 1; iteration < size; iteration++) // sort the array smallest to largest or largest to smallest
        {
            for (int index = 0; index < (size - iteration); index++)
            {
                if (method == 'a' && infoArray[index] > infoArray[index+1])
                {
                    temp = infoArray[index];
                    infoArray[index] = infoArray[index+1];
                    infoArray[index+1] = temp;
                }
                if (method == 'd' && infoArray[index] < infoArray[index+1])
                {
                    temp = infoArray[index];
                    infoArray[index] = infoArray[index+1];
                    infoArray[index+1] = temp;
                }
            }
        }

        for (int i = 0; i < size; i++) // fill up the linked list
        {
            temp = infoArray[i];
            insertTail(temp);
        }

        current = nullptr; // clean up mess
        delete current;
        infoArray = nullptr;
        delete [] infoArray;
    }
}
        
//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::insertTail(T& value)
{
    if (first == nullptr) // the list is empty
    {
        insertHead(value); // same thing
    }
    else // at least one node
    {
        nodeType<T> *newNode;           // a pointer to a node
        newNode = new nodeType<T>;      // make a new node
        newNode->info = value;          // copy value into new node
        newNode->next = nullptr;        // grounds links
        newNode->back = nullptr; 

        last->next = newNode;           // update next link of current last node
        newNode->back = last;           // update value of new last node back link
        last = newNode;                 // shift last pointer to just added node
        count++;

        newNode = nullptr;
        delete newNode;
    }
    

}
//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::manualCreate()
{
    
    int size = -1;
    int check = 5;
    T value;
    
    std::cout << "\nyour list now: ";
    print();
    std::cout << "\nenter ( 9 ) if you want to clear the list or ( 0 ) to keep it: ";
    std::cin >> check;
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    if (check == 9) destroy();

    while (size < 0 || size > 20)
    {
        badInput:
        std::cout << "\nEnter the number of nodes that you want: ";
        std::cin >> size;
        if ( size < 0 || size > 20 || !std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout << "\nuse a value bettween 0 and 20, or come change me\n";
            std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
            std::cout.flush();
            system("clear");
            goto badInput;
        }
    }

    std::cout << "for this next part, there are no safety check,\n" <<
    "pick chars, doubles, stings, or integers and enter them until told to stop\n";

    for (int i = 0; i < size; i++)
    {
        std::cout << "\nenter the value for index [ " << i << " ]  : ";
        std::cin >> value;
        insertTail(value);
    }

    std::cin.clear();
    std::cin.ignore(1000,'\n');
    std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
    std::cout << "\nhere is your list now: ";
    print();
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
T doublyLinkedList<T>::min()
{
    if (count == 0)
    {
        return 0;
    }
    else
    {
        T min;                  // holds largest
        nodeType<T> *current;   // traverse
        current = first;        // start at head
        min = current->info;    // assume value at first node is smallest

        while (current != nullptr)
        {
            if (current->info < min)
            {
                min = current->info;
            }
            current = current->next;
        }
        return min;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
T doublyLinkedList<T>::max()
{
    if (count == 0)          
    {
        return 0;
    }
    else
    {
        T max;                  // holds largest
        nodeType<T> *current;   // traverse
        current = first;        // start at head
        max = current->info;    // assume value at first node is smallest

        while (current != nullptr)
        {
            if (current->info > max)
            {
                max = current->info;
            }
            current = current->next;
        }
        return max;
    }
    
}
//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::deleteNodeHead()
{
    if (count == 0) // empty list
    {
        std::cout << "{ the list is empty, nothing to delete }";
    }
    else if (count == 1)   // only one item
    {
        destroy();
    }
    else
    {
        nodeType<T> *current;      // a pointer to traverse
        current = first;           // put current on the first node

        first = first->next;        // backs head off node to delete
        current->back = nullptr;   // detach
        current->next = nullptr;
        first->back = nullptr;
        delete current;            // it is detached, delete it and decrement
        count--;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::deleteNodeTail()
{
    if (count == 0) // empty list
    {
        std::cout << "{ the list is empty, nothing to delete }";
    }
    else if (count == 1)   // only one item
    {
        destroy();
    }
    else
    {
        nodeType<T> *current;      // a pointer to traverse
        current = last;            // put current on the last node
        last = last->back;         // bring tail pointer back one node, last node will be deleted

        current->back = nullptr;   // detach
        current->next = nullptr;   // just in case
        last->next = nullptr;

        delete current;            // it is detached, delete it and decrement
        count--;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
T doublyLinkedList<T>::valueAtIndex(int& index)
{
    T value;               // holds value
    nodeType<T> *current;  // pointer to traverse
    current = first;       // start on first node

    if (current == nullptr)
    {
        std::cout << "{ the list is empty } ";
        return 32;
    }
    else
    {
        for (int i = 0; i <= index; i++)
        {
            if (i == index)
            {
                return (current->info);
            }
            current = current->next;
        }
        return 32;
    }
    return 32;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
int doublyLinkedList<T>::freqOfValue(T& value)
{
    if (count == 0)
    {
        std::cout << "{ empty list }";
        return 0;
    }
    else
    {
        int freq = 0;
        nodeType<T> *current;    // traverser
        current = first;         // start at first node

        while (current != nullptr)
        {
            if ((current->info) == value)
            {
                freq++;
            }
            current = current->next;
        }
        current = nullptr;
        return freq;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::OWinsertNodeIndex(int& index, T& value)
{
    if (index < 0 || index > (count - 1))
    {
        std::cout << " { enter a valid index }";
    }
    else if (count == 0)
    {
        insertHead(value); // list was empty...or tail()
    }
    else if ( (count == 1 && index == 0) || ( (count-1) == index) ) // wants to insert at last node (1 node on list, or many)
    {
        deleteNodeTail();
        insertTail(value); // still doesn't matter
    }
    else
    {
        nodeType<T> *current;    // traverser
        current = first;         // start at first node
        for (int i = 0; i <= index; i++)
        {
            if (i == index)
            {
                current->info = value; // put it in
            }
            current = current->next; // advance
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::deleteAllOfValue(T& value)
{
    bool exists = search(value);
    if (!exists)
    {
        std::cout << "{ value is not in the list }";
    }
    else
    {
        int freq = freqOfValue(value);

        for (int i = 0; i < freq; i++)
        {
            deleteNode(value);
        }
    }
    

}
//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::deleteNodeIndex(int& index)
{
    if (index < 0 || index > (count - 1) )
    {
        std::cout << " { invlaid index }";
    }
    else if ( (count == 1) && (index == 0) ) // delete head
    {
        deleteNodeHead();
    }
    else if ((count-1) == index) // delete tail
    {
        deleteNodeTail();
    }
    else // not first or last index to delete
    {
        nodeType<T> *current;
        nodeType<T> *trailer;
        nodeType<T> *deleter;
        current = first->next;   // put on second node
        trailer = first;         // put on first node

        for (int i = 0; i <= index; i++)
        {
            if (i == index)
            {   
                deleter = trailer;  // put a pointer on node to delete
                trailer = trailer->back;    // back off trailer

                deleter->next = nullptr;  // detach node to delete
                deleter->back = nullptr;

                trailer->next = current;   // start span
                current->back = trailer;  // finished span

                delete deleter;           // node is gone
                deleter = nullptr;        // holster
                trailer = nullptr;
                current = nullptr;
                count--;
            }   
            else
            {
                trailer = trailer->next; // advance
                current = current->next;
            } 
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::insertAtIndex(int& index, T& value)  // no over_write, just slides in at index and pushes currents right
{
    if (index < 0 || index > (count -1))
    {
        std::cout << "{ invalid index }";
    }
    else if (index == 0)
    {
        insertHead(value); // this one will work...can't do insertHead for (index = (count -1)) because of shift 
    }
    else 
    {
        nodeType<T> *current;       // prepare the tools to insert
        nodeType<T> *inserter;
        nodeType<T> *trailer;

        inserter = new nodeType<T>; // create the new node that will be inserted
        inserter->info = value;
        inserter->next = nullptr;
        inserter->back = nullptr;

        if (index == (count-1)) // need a special way to insert on last node...to keep value
        {
            trailer = last->back; // set these two to span last gap in the nodes
            current = last;

            inserter->back = trailer;    // tie it in
            inserter->next = current;
            trailer->next = inserter;
            current->back = inserter;

            current = nullptr; // release
            trailer = nullptr;
            inserter = nullptr;

            count++; // increment
        }
        else
        {
            current = first->next; // start on second node
            trailer = first;       // follow behind, start on first node
            for (int i = 0; i <= index; i++)
            {
                if ( i == index )
                {
                    trailer = trailer->back; // shift both back one node
                    current = current->back;

                    trailer->next = inserter; // tie it in
                    current->back = inserter;
                    inserter->back = trailer;
                    inserter->next = current;

                    current = nullptr; // release
                    trailer = nullptr;
                    inserter = nullptr;

                    count++; // increment
                }
                else
                {
                    current = current->next;
                    trailer = trailer->next;
                }
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
int doublyLinkedList<T>::firstIndexOfValue(T& value)                      // find the first index the value shows up at
{
    
    if (isEmptyList())
    {
        std::cout << " { the list is empty }";
        return -1;
    }
    else if (!search(value))
    {
        std::cout << " { the value is not on the list }";
        return -1;
    }
    else
    {
        nodeType<T> *current;
        current = first;
        for (int i = 0; i < count; i++)
        {
            if (current->info == value)
            {
                return i;
            }
            else
            {
                current = current->next;
            }
        }
    }
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------------------
template <class T>
void doublyLinkedList<T>::spinAround3times()
{
    if (first == nullptr)
    {
        std::cout << " { empty }";
    }
    else
    {
        nodeType<T> *current;
        current = first;
        last->next = first; // now it is circular

        for (int i = 0; i < (3*count); i++)
        {
            std::cout << current->info << "  ";
            current = current->next;
            if ( (i+1) % count == 0)
            {
                std::cout << "\n";
            }
        }

    }
    last->next = nullptr; // cut it out
}
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
#endif // end doublyLinkedList.h
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------