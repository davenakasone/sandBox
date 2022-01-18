/*
    same, but 3 non-recursive functions added
    look at those nested templates in the non-recursive....and the   $ *   ref / deref
    still has lots of recursion

    be careful with the templates in stack...some of the test items are only good with integers...
    comment out if objects and other data types will be put on the stack
*/

#ifndef H_binaryTree
#define H_binaryTree

#include <iostream> 

#include "myStack.h"
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


template <class elemType>
struct nodeType 
{
    elemType info;
    nodeType<elemType> *lLink;
    nodeType<elemType> *rLink;
};


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


template <class elemType>
class binaryTreeType
{
    public:
        
        const binaryTreeType<elemType>& operator = (const binaryTreeType<elemType>&); 
        bool isEmpty() const;                                // determine whether the binary tree is empty
        
        void inorderTraversal() const;                       // inorder traversal of the binary tree ... prints
        void preorderTraversal() const;                      // preorder traversal of the binary tree ... prints
        void postorderTraversal() const;                     // postorder traversal of the binary tree ... prints

        void nonRecursiveInTraversal() const;                // same as above 3, but no recursion 
        void nonRecursivePreTraversal() const;                   // all print
        void nonRecursivePostTraversal() const;                      // all use stack

        int treeHeight() const;                              // determine the height of a binary tree
        int treeNodeCount() const;                           // determine number of nodes in tree
        int treeLeavesCount() const;                         // determine the number of leaves in tree
        void destroyTree();                                  // deallocates everything in the tree   root to nullptr
      
        virtual bool search(const elemType& searchItem) const = 0;    // determine if searchItem is in tree 
        virtual void insert(const elemType& insertItem) = 0;          // insert an item into the tree
        virtual void deleteNode(const elemType& deleteItem) = 0;      // delete a specified item form tree

        binaryTreeType(const binaryTreeType<elemType>& otherTree);    // copy constructor
        binaryTreeType();                                             // default constructor
        ~binaryTreeType();                                            // destructor
    
    protected:
        
        nodeType<elemType>  *root;                                    // only node you have to track

    private:
        
        void copyTree(nodeType<elemType>* &copiedTreeRoot, nodeType<elemType>* otherTreeRoot); // helper
        void destroy(nodeType<elemType>* &p);          // helper to deallocate entire tree
        
        void inorder(nodeType<elemType> *p) const;     // inorder traversal of the binary of where 'p' points, prints, helper
        void preorder(nodeType<elemType> *p) const;    // preorder traversal of the binary of where 'p' points, prints, helper
        void postorder(nodeType<elemType> *p) const;   // postorder traversal of the binary of where 'p' points, prints, helper

        int height(nodeType<elemType> *p) const;       // determines the height of tree 'p' is pointing to
        int max(int x, int y) const;                   // determines the larger of x and y, returns largest
        int nodeCount(nodeType<elemType> *p) const;    // determines the number of nodes in tree where 'p' points 
        int leavesCount(nodeType<elemType> *p) const;  // determines the number of leaves in tree where 'p' points
};


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
    root = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
    return (root == nullptr);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
    inorder(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const
{
    preorder(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const
{
    postorder(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
    return height(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const
{
    return nodeCount(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const
{
    return leavesCount(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void  binaryTreeType<elemType>::copyTree (nodeType<elemType>* &copiedTreeRoot, nodeType<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
    {
        copiedTreeRoot = nullptr;
    }
    else
    {
        copiedTreeRoot = new nodeType<elemType>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType> *p) const
{
    if (p != nullptr)
    {
        inorder(p->lLink); // 1 of 2 function stacks load up....2^n as levels needed
        std::cout << p->info << "  ";
        inorder(p->rLink); // 2 of 2 function stacks load up....2^n as levels needed
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType> *p) const
{
    if (p != nullptr)
    {
        std::cout << p->info << "  ";
        preorder(p->lLink);
        preorder(p->rLink);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType> *p) const
{
    if (p != nullptr)
    {
        postorder(p->lLink);
        postorder(p->rLink);
        std::cout << p->info << "  ";
    }		
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator = (const binaryTreeType<elemType>& otherTree)
{ 
    if (this != &otherTree) // avoid self-copy
    {
        if (root != nullptr)   // destroy if not empty...starting fresh
        {
            destroy(root);
        }

        if (otherTree.root == nullptr) // otherTree is empty
        {
            root = nullptr; // just put copy in an empty state also
        }  
        else
        {
            copyTree(root, otherTree.root);
        }    
    }
    return *this; 
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void  binaryTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
    if (p != nullptr)
    {
        destroy(p->lLink);
        destroy(p->rLink);
        delete p;
        p = nullptr;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void  binaryTreeType<elemType>::destroyTree()
{
    destroy(root);
}
//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType>& otherTree)
{
    if (otherTree.root == nullptr) // empty tree given to copy constructor
    {
        root = nullptr; // just initialize an empty tree
    }
    else
    {
        copyTree(root, otherTree.root);
    }     
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
    destroy(root);
}

//----------------------------------------------------------------------------------------------------------------------------
template<class elemType>
int binaryTreeType<elemType>::height(nodeType<elemType> *p) const
{
    if (p == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(p->lLink), height(p->rLink)); 
    }
        
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
    if (x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }     
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType> *p) const
{
    if (p == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + nodeCount(p->lLink) + nodeCount(p->rLink);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
int binaryTreeType<elemType>::leavesCount(nodeType<elemType> *p) const
{
    if (p == nullptr) // empty
    {
        return 0;
    }
    else
    {
        if (p->lLink == nullptr && p->rLink == nullptr) // only root node exists
        {
            return 1;
        }
        else
        {
            return leavesCount(p->lLink) + leavesCount(p->rLink);
        }
    }
}





//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::nonRecursiveInTraversal() const     // far left, parent, right    ...can use to split tree
{
    stackType<nodeType<elemType>*> stack; // the stack uses elements of type for tree node...tree nodes will go into the stack
    nodeType<elemType> *current;          // to traverse
    current = root;                       // start at root

    while ( (current != nullptr) || (!stack.isEmptyStack()) )
    {
        if (current != nullptr)
        {
            stack.push(current); // keeps going until left link is null ... you are saving parent's link in the stack
            current = current->lLink; // left child
        }
        else
        {
            current = stack.top();
            stack.pop();
            std::cout << current->info << "  ";
            current = current->rLink; // right child
        }
    }
    std::cout << std::endl;
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::nonRecursivePreTraversal() const // parent, left, right
{
    stackType<nodeType<elemType>*> stack; // also making a stack to hold nodes in tree
    nodeType<elemType> *current;
    current = root;

    while ( (current != nullptr) || (!stack.isEmptyStack()) )
    {
        if (current != nullptr)
        {
            std::cout << current->info << "  ";
            stack.push(current);
            current = current->lLink; // left child
        }
        else
        {
            current = stack.top();
            stack.pop();
            current = current->rLink; // right child
        }
    }
    std::cout << std::endl;
} 

//----------------------------------------------------------------------------------------------------------------------------
template <class elemType>
void binaryTreeType<elemType>::nonRecursivePostTraversal() const // left, right, parent
{
    stackType<nodeType<elemType>*> stack; // also making a stack to hold nodes in tree
    stackType<int> dStack;             // will be 2 parallel stacks    1 before left visited, 2 before right visited
    nodeType<elemType> *current;
    current = root;
    int v = 0; // direction   1 = left visited, 2 = right visited

    if (current == nullptr)
    {
        std::cout << "the tree is empty\n";
    }
    else if ( current != nullptr)
    {
        stack.push(current);
        dStack.push(1);
        current = current->lLink;
        while ( !stack.isEmptyStack() )
        {
            if (current != nullptr && v == 0)
            {
                stack.push(current);
                dStack.push(1);
                current = current->lLink;
            }
            else
            {
                current = stack.top(); // assign top element of node stack to current
                stack.pop();
                v = dStack.top(); // assign top element of direction stack to v
                dStack.pop();
                if (v == 1)
                {
                    stack.push(current);
                    dStack.push(2);
                    v = 0;
                    current = current->rLink;
                }
                else // visit current
                {
                    std::cout << current->info << "  ";
                }
            }
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "there has been an error\n";
    }
} 

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif // end binaryTree.h
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
