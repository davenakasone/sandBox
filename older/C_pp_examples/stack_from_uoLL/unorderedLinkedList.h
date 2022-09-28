#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList  

#include "linkedList.h"

//-----------------------------------------------------------------------------------------------------------------------------
//=============================================================================================================================
//                                 Definition of the unorderedlinkedList class                                               //         //
//=============================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------------

template <class T> 
class unorderedLinkedList: public linkedListType<T>    // this is a getting to be a very abstract class
{
    public:
        bool search(const T& searchItem) const;
         /*
            Function to determine whether searchItem is in the list
            Postcondition: returns true if searchItem is in the ;ist, otherwise the value false is returned
         */

        void insertFirst(const T& newItem);
         /*
            Function to insert newItem at the beginning of the list
            Postcondition: first points to the new list, newItem is inserted at the beginning of the list,
            last points to the last node in the list, and count is incremented by 1
         */

        void insertLast(const T& newItem);
         /*
            Function to insert newItem at the end of the list
            Postcondition: first points to the new list, newItem is inserted at the end of the list,
            last points to the last node in the list, and count is incremented by 1
         */

        void deleteNode(const T& deleteItem);
         /*
            Function to delete deleteItem from the list
            Postcondition: if found, the node containing deleteItem is deleted from the list
            first points to the first node, last points to the last node of the updated list, and count is decremented by 1
         */
};


//=============================================================================================================================


//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
bool unorderedLinkedList<T>::search(const T& searchItem) const
{
    nodeType<T> *current;                          // pointer to traverse the list
    bool found = false;                            // indicator
    
    current = this->first;                         // set current to point to the first node in list

    while (current != nullptr && !found)           // search the list
    {
        if (current->info == searchItem)           // searchItem is found
        {
            found = true;
        }
        else
        {
            current = current->link;               // make current point to next node
        }    
    }

    return found; 
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void unorderedLinkedList<T>::insertFirst(const T& newItem)
{
    nodeType<T> *newNode;              // pointer to create the new node
    newNode = new nodeType<T>;         // create the new node

    newNode->info = newItem;           // store the new item in the node
    newNode->link = this->first;       // insert newNode before first
    this->first = newNode;             // make first point to the new first node
                                
    this->count++;                     // increment count

    if (this->last == nullptr)         // if the list was empty, newNode is also  the last node
    {
        this->last = newNode;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void unorderedLinkedList<T>::insertLast(const T& newItem)
{
    nodeType<T> *newNode;                  // pointer to create the new node
    newNode = new nodeType<T>;             // create the new node

    newNode->info = newItem;               // store the new item in the node
    newNode->link = nullptr;               // set the link field of newNode to nullptr

    if (this->first == nullptr)            // if the list is empty, newNode is both the first and last node              
    {
        this->first = newNode;
        this->last = newNode;
        this->count++;                      // and increment count
    }
    else                                    // the list is not empty, insert newNode after last
    {
        this->last->link = newNode;         // insert newNode after last
        this->last = newNode;               // make last point to the actual last node
        this->count++;                      // increment count
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
template <class T>
void unorderedLinkedList<T>::deleteNode(const T& deleteItem)
{
    nodeType<T> *current;          // pointer to traverse the list
    nodeType<T> *trailCurrent;     // pointer just before current
    bool found = false;            // indicator

    if (this->first == nullptr)    // the list is empty. 
    {
        std::cout << "Cannot delete from an empty list\n";
    }
        
    else
    {
        if (this->first->info == deleteItem)           // item to delete is at the first node
        {
            current = this->first;
            this->first = this->first->link;
            this->count--;
            if (this->first == nullptr)                // the list has only one node
            {
                this->last = nullptr;
            }                 
            delete current;
        }
        else                                           // search the list for the node with the given info
        {
            trailCurrent = this->first;                // set trailCurrent to point to first node
            current = this->first->link;               // set current to point to second node

            while (current != nullptr && !found)
            {
                if (current->info != deleteItem) 
                {
                    trailCurrent = current;
                    current = current-> link;
                }
                else
                {
                    found = true;
                }     
            }

            if (found)                                  // item to delete was found
            {
                trailCurrent->link = current->link;     // node to delete is on current, span it
                this->count--;                          // reduce count

                if (this->last == current)              // node to be deleted was the last node
                {
                    this->last = trailCurrent;          // update the value of last node
                }
                                   
                delete current;                         // delete the node from the list
            }
            else
            {
                std::cout << "The item to be deleted is not in the list\n";
            }
        }
    }
}


#endif  // end unorderedLinkedList.h
