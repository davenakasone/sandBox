/*
    doesn't appear much changed here
*/

#ifndef H_binarySearchTree
#define H_binarySearchTree

#include <iostream>
#include <cmath> 

#include "binaryTree.h"
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
class bSearchTreeType: public binaryTreeType<elemType> 
{
    public:
        bool search(const elemType& searchItem) const;       // determine if searchItem is in tree 
        void insert(const elemType& insertItem);             // place insertItem in tree (may create new node, rejects doubles)
        void deleteNode(const elemType& deleteItem);         // remove deleteItem from the tree 
      
        void printTree();                                    // crude print of tree

    private:
        
        void deleteFromTree(nodeType<elemType>* &p); // delete the node where 'p' points 
};


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType& searchItem) const
{
    nodeType<elemType> *current;
    bool found = false;

    if (this->root == nullptr)
    {
        std::cout << "can't search empty tree\n";
    } 
    else // uses rules of 'binary search tree'
    { 
       current = this->root;

       while (current != nullptr && !found)
        {
            if (current->info == searchItem)
            {
                found = true;
            }
            else if (current->info > searchItem)
            {
                current = current->lLink;
            } 
            else
            {
                current = current->rLink;
            }    
        }
    }
    return found;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType& insertItem)
{
    nodeType<elemType> *current;        // leader
    nodeType<elemType> *trailCurrent;   // follower
    nodeType<elemType> *newNode;        // node generator

    newNode = new nodeType<elemType>;   // make node
    newNode->info = insertItem;         // copy info
    newNode->lLink = nullptr;           // control end links
    newNode->rLink = nullptr;

    if (this->root == nullptr) // empty
    {
        this->root = newNode;
    } 
    else
    {
        current = this->root;
 
        while (current != nullptr)
        {
            trailCurrent = current;

            if (current->info == insertItem)
            {
                std::cout << "item is already in tree\n";
                return; // complete break
            }
            else if (current->info > insertItem)
            {
                current = current->lLink; // only left children are less than parents
            }
            else
            {
                current = current->rLink; // only right children are greater than parents
            }       
        }

        if (trailCurrent->info > insertItem)
        {
            trailCurrent->lLink = newNode;
        }  
        else
        {
            trailCurrent->rLink = newNode;
        }
            
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
    nodeType<elemType> *current;       // leads
    nodeType<elemType> *trailCurrent;  // follows
    bool found = false;                // flag

    if (this->root == nullptr)
    {
        std::cout << "can't delete from an empty tree\n"; 
    }
    else
    {
        current = this->root;
        trailCurrent = this->root; // starts both on route node

        while (current != nullptr && !found)
        {
            if (current->info == deleteItem)
            {
                found = true;
            }  
            else
            {
                trailCurrent = current; // advance
                if (current->info > deleteItem)
                {
                    current = current->lLink;
                }  
                else
                {
                    current = current->rLink;
                }      
            }
        }

        if (current == nullptr)
        {
            std::cout << "item to be deleted is not in tree\n"; 
        }
        else if (found)
        {
            if (current == this->root)
            {
                deleteFromTree(this->root);
            }
            else if (trailCurrent->info > deleteItem)
            {
                deleteFromTree(trailCurrent->lLink);
            } 
            else
            {
                deleteFromTree(trailCurrent->rLink);
            }   
        }
        else
        {
            std::cout << "item to be deleted is not in the tree\n"; // catch all
        }
    }
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree (nodeType<elemType>* &p)
{
    nodeType<elemType> *current;         // leader
    nodeType<elemType> *trailCurrent;    // follower
    nodeType<elemType> *temp;            // holds to delete node

    if (p == nullptr)
    {
        std::cout << "node to be deleted does not exist\n"; // empty
    }
    else if (p->lLink == nullptr && p->rLink == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }
    else if (p->lLink == nullptr)
    {
        temp = p;
        p = temp->rLink;
        delete temp;
    }
    else if (p->rLink == nullptr)
    {
        temp = p;
        p = temp->lLink;
        delete temp;
    }
    else
    {
        current = p->lLink;
        trailCurrent = nullptr;

        while (current->rLink != nullptr)
        {
            trailCurrent = current;
            current = current->rLink;
        }

        p->info = current->info;

        if (trailCurrent == nullptr)
        {
            p->lLink = current->lLink;
        }                      
        else
        {
            trailCurrent->rLink = current->lLink;
        }  
        delete current;
    }
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void bSearchTreeType<elemType>::printTree()
{
    if (this->root == nullptr)
    {
        std::cout << "the tree is empty\n";
    }
    else
    {
        int sums = 0;               // sum of all possibilities (max number of nodes given tree could have)
        int h = this->treeHeight(); // height of tree, from object     determines rows in array
        for (int i = 0; i < h;  i++)
        {
            sums = sums + std::pow(2,i); // find every possibilitiy, given size, even empty options
        }
        std::cout << "\n" << sums << "\n";//TEST
        
        int bottom = pow(2,h-1);     // max number of possibilties on last level, determines columns in array
        int **vals;                  // holds tree values rows(height) x columns(bottom 'level')
        vals = new int*[h];          // arry pointer for rows
        for (int row = 0; row < h; row++)
        {
            vals[row] = new int [bottom];  // each arry pointer gets an array to make columns
        }

        for (int i = 0; i < h; i++) // TEST
        {
            for (int j = 0; j < bottom; j++)
            {
                vals[i][j] = 2;
                std::cout << vals[i][j] << " ";//TEST
            }
            std::cout << std::endl; //TEST
        }
        
        
        
        // clean up
        for (int i = 0; i < h; i++)
        {
            delete [] vals[i];
        }
        delete [] vals;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
