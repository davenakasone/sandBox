/*
    the stack works well, that is the first step

    preorder:   root, left, right            traversing just visiting all the nodes once
    inorder:    left, root, right
    postorder:  left, right, root
*/

#include <chrono>
#include <random>
#include <string>
#include <thread>

#include "binarySearchTree.h"

void checkStack();
void checkSearchTree();
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
int main() 
{
	//checkStack(); // only to be confident in underlying data type
    checkSearchTree(); // only for confidence

    std::cout << "\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
	return 0;
}  

//----------------------------------------------------------------------------------------------------------------------------
void checkStack()
{
    int length = 0;              // randomly set to be max elements allowed in stack
    int min = 20;                // randomly set to be smallest element value in stack
    int max = 99;                // randomly set to be largest element value in stack
    std::string discard = "";    // for clearing screen
    std::random_device rdevice{};                                      // set up generator, only need one
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{min, max};    
    std::default_random_engine num2{ rdevice() };                      // notice the different names 1 vs 2  
    std::uniform_int_distribution<unsigned int> randomNum2{5,9};       // varies size of stack   5 to 10 for now
    // BASIC TEST
    stackType<int> tester(10);      // make a stack with 10 elements
    for (int i = 1; i <= 10; i++)   // 1, 2, ..., 10
    {
        tester.push(i);
    }
    tester.softPrint();
    std::cout << "\n the stack was made and printed, press any key and hit [enter] to proceed: ";     
    std::cin >> discard;  
    std::cout.flush();
    system("clear");    
    // COPY CONSTRUCTOR
    stackType<int>OLcheck(tester);
    OLcheck.softPrint();
    tester.softPrint();
    std::cout << "\n copy constructor was good, press any key and hit [enter] to proceed: ";     
    std::cin >> discard;  
    std::cout.flush();
    system("clear");
    // = OL
    stackType<int> another_tester  = tester; 
    tester.softPrint();
    another_tester.softPrint(); 
    std::cout << "\n = OL was good, press any key and hit [enter] to proceed: ";     
    std::cin >> discard;  
    std::cout.flush();
    system("clear");  
    // DEEP-COPY CHECK
    another_tester.initializeStack();
    another_tester.softPrint();
    tester.softPrint();
    std::cout << "\n deep copy was good, press any key and hit [enter] to proceed: ";     
    std::cin >> discard;  
    std::cout.flush();
    system("clear"); 
    // RESET CHECK
    tester.initializeStack();
    length = randomNum2(num2);
    for(int i = 0; i < length; i++)
    {
        tester.push(randomNum1(num1));
    }
    tester.softPrint();
    std::cout << "\n reset was good, press any key and hit [enter] to proceed: ";     
    std::cin >> discard;  
    std::cout.flush();
    system("clear"); 
    // POP CHECK
    for (int i = 0; i <= length; i++)
    {
        tester.pop();
    }
    // PUSH CHECK
    for(int i = 0; i <= 10; i++)
    {
        tester.push(randomNum1(num1));
    }
    // TOP - POP, ASSERT CHECK...will crash
    std::cout << std::endl;
    for(int i = 0; i <=10; i++)
    {
        std::cout << i <<" top: { " << tester.top() << " }\n";
        tester.pop();
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void checkSearchTree()
{
    bSearchTreeType<int> myTree;
    //int filling[7] = {1, 2, 3, 4, 5, 6, 7}; // should force it to be linear
    //int filling[7] = {5, 4, 7, 3, 6, 8, 2};   // reduces height by following rules of 'binary search tree'
    int filling[7] = {4,3,2,1,5,6,7}; // makes a V
    std::cout << "\ntest seq: {  ";
    for (int i = 0; i < 7; i++)
    {
        int fill = filling[i];
        myTree.insert(fill);
        std::cout << fill << "  ";
    } 
    std::cout << "}\n";
    std::cout << "\ninorder:               ";
    myTree.inorderTraversal();
    std::cout << "\n(non rec) inorder:     ";
    myTree.nonRecursiveInTraversal();

    std::cout << "\npreorder:              ";
    myTree.preorderTraversal();
    std::cout << "\n(non rec) preorder:    ";
    myTree.nonRecursivePreTraversal();

    std::cout << "\npostorder:             ";
    myTree.postorderTraversal();
    std::cout << "\n(non rec) postorder:   ";
    myTree.nonRecursivePostTraversal();

    std::cout << "\nheight:    " << myTree.treeHeight();
    std::cout << "\nleaves:    " << myTree.treeLeavesCount();
    std::cout << "\nnodes:     " << myTree.treeNodeCount();
    //myTree.printTree();
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------

/*


*/