/*
    be comfortable implementing any function in the class, lets you get a lot of power out of ODD
    making a linked list has not been going to well, but this one acutally works. I think the book was outdated.
    besides using the generaric linked list in STL, it is good to make your own to have an idea of what is happening
    I won't use an iterator, and I won't distinguish between ordered and unordered...but I will use a template

    main() here is more less a test bench to see if that linkedListType class will make decent objects
    It gets a little quesitionable with UDF dataTypes and strings
    ...string overloads should be defined explicty (use str functions)
    this class should not be used to program things going to space or things with other safety-critical needs
*/

#include <iomanip>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include "myLinkedList.h"

// globals don't hurt anything, it is easier than building another class and stimulating it
// or do this void forwardPrint(linkedListType<int> intLL, linkedListType<double> dubLL, linkedListType<char> chLL, linkedListType<std::string> strLL);
const int SIZE = 7; // change size as you test
char ADVANCE = 'y'; 

// only going to test integers, doubles, characters, and strings 
//...add more if you want, you'll need two of each type to test some class abilities, and this is a good place to put objects 
// just remember to change the testing functions when you add or remove objects...may not need to add any if obj pointers are used

int s_int_arr[SIZE];                          // an array to initialize the static linked list object of integers                  
linkedListType<int> s_int_ll;                 // static linked list object of integers
int d_int_arr[SIZE];                          // an array to initialize the dynamic linked list object of integers 
linkedListType<int> *d_int_ll;                // dynamic ...pointer to a linked list object of integers

double s_dub_arr[SIZE];                       // an array to initialize the static linked list object of doubles                  
linkedListType<double> s_dub_ll;              // static linked list object of doubles   
double d_dub_arr[SIZE];                       // an array to initialize the dynamic linked list object of doubles    
linkedListType<double> *d_dub_ll;             // dynamic ...pointer to a linked list object of doubles   

char s_char_arr[SIZE];                        // an array to initialize the static linked list object of characters                  
linkedListType<char> s_char_ll;               // static linked list object of characters
char d_char_arr[SIZE];                        // an array to initialize the dynamic linked list object of characters 
linkedListType<char> *d_char_ll;              // dynamic ...pointer to a linked list object of characters

std::string s_str_arr[SIZE];                          // an array to initialize the static linked list object of strings                 
linkedListType<std::string> s_str_ll;         // static linked list object of strings
std::string d_str_arr[SIZE];                  // an array to initialize the dynamic linked list object of strings
linkedListType<std::string> *d_str_ll;        // dynamic ...pointer to a linked list object of strings


// prototypes
void setUp();
void viewSetUp();
void objectsPrintFwd();
void objectsPrintBwd();
void deleteObjects();
void checkDefaultConstructor();
void checkEquality();
void checkCopy();
void checkInsertHead();
void checkIterator();
void checkBadThings();
void checkRemoval();
void checkMaxMin();
void checkSearchDelete();
void checkInserts();
void checkInsertsMore();
void checkSortAsc();
void checkSortDes();
void checkOperatorOLs();


template <class Tp>                                // smallest to largest
void sortInputArrayAsc(Tp someArray[], int size); // sort the array and compare to linked list sorting algorithm

template <class Tp>                                // largest to smalles
void sortInputArrayDsc(Tp someArray[], int size); // sort the array and compare to linked list sorting algorithm

template <class Ty>
void testPrintInput(Ty someArray[], int size); // this will just show you are starting off with valid input
//


//--------------------------------------------------------------------------------------------------------------------------
int main() 
{
    std::cout << std::fixed << std::showpoint << std::setprecision(3); // set presistants
    d_int_ll = new linkedListType<int>;             // allocate memory for dynamics
    d_dub_ll = new linkedListType<double>;
    d_char_ll = new linkedListType<char>;
    d_str_ll = new linkedListType<std::string>;
    
    setUp();                       // this will get some random variable values and show you
    //viewSetUp();                 // make sure set up was good, if needed
    //objectsPrintFwd();           // objects will print as is, compare to original input, should match
    //objectsPrintBwd();           // objects will print tail to head....should be reverse of original input
    //deleteObjects();             // we will see if the list can delete itself
    //checkDefaultConstructor();   // checks a static object creation and a dynamic object creation
    //checkEquality();             // has some good dyanmic obj checks also, goes over == overload, some builds implied
    //checkCopy();                 // goes over assigment = copying a list, copy list(), and copy constructor implied
    //checkInsertHead();           // looks at insert node head
    //checkIterator();             // moves *current around the object so several iteration operations can be performed
    //checkBadThings();            // this class gives away private members and you can alter them easily
    //checkRemoval();              // removes first, last, max, min, at index, a value, ect
    //checkMaxMin();               // brief max and min demo
    //checkSearchDelete();         // shows searching for a term, then deleting it
    //checkInserts();              // insert overwrite (at index i), insert above, insert below...already seen the insert first/last
    //checkSortAsc();              // see if list can sort smallest to largest
    //checkSortDes();              // see if list can sort largest to smallest
    //checkOperatorOLs();            // treat linked list as an array, << to print entire list ...not sure about warnings
    //std::cout << s_int_ll;
    //checkInsertsMore();          // up insert no overwrite, down insert no overwrite
    linkedListType<int> tester;
    tester.initializeRandomIntObj(20);
    tester.printListFwd();

    std::cout << "\nprogram complete\n";
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------
void setUp()
{
    //std::ifstream inFile;
    //inFile.open("stringInput.txt"); // change strings as needed....fill in .txt and turn this on if you want your own strings

    std::random_device rdevice{};
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum1{100,600};

    std::default_random_engine num2{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum2{65,90}; // don't change this one too much, these are ascii

    std::default_random_engine num3{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum3{1,9}; // don't change this one too much, string length

    char setterS; // for setting string arrays if you aren't using inFile
    char setterD;

    for (int i = 0; i < SIZE; i++)
    {
        s_int_arr[i] = randomNum1(num1);
        d_int_arr[i] = randomNum1(num1);
        ///d_int_arr[i] = s_int_arr[i];               // if you want static and dynamic to have some values

        s_dub_arr[i] = randomNum1(num1) / 9.87;
        d_dub_arr[i] = randomNum1(num1) / 6.54;
        ///d_dub_arr[i] = s_dub_arr[i];               // if you want static and dynamic to have some values

        s_char_arr[i] = randomNum2(num2);
        d_char_arr[i] = randomNum2(num2);
        ///d_char_arr[i] = s_char_arr[i];             // if you want static and dynamic to have some values
        
        //inFile >> strArray[i];                      // to take strings from the .txt file, instead of random strings
        for (int j = 0; j < randomNum3(num3); j++)
        {
            setterS = randomNum2(num2);
            s_str_arr[i] = s_str_arr[i] + setterS;
            setterD = randomNum2(num2);
            d_str_arr[i] = d_str_arr[i] + setterD;
        }
    
    }

    //inFile.close();

    // use the random data to make linked lists of the respective data dataTypes
    s_int_ll.makeListfromArray(s_int_arr, SIZE);
    s_dub_ll.makeListfromArray(s_dub_arr, SIZE);
    s_char_ll.makeListfromArray(s_char_arr, SIZE);
    s_str_ll.makeListfromArray(s_str_arr, SIZE);

    d_int_ll->makeListfromArray(d_int_arr, SIZE);
    d_dub_ll->makeListfromArray(d_dub_arr, SIZE);
    d_char_ll->makeListfromArray(d_char_arr, SIZE);
    d_str_ll->makeListfromArray(d_str_arr, SIZE);
}

//--------------------------------------------------------------------------------------------------------------------------
void viewSetUp()
{
    // shows intial values of arrays, using integer, double and character to test
    std::cout << "\n(STATIC) integer dataType array of [ " << SIZE << " ] elements will be fed to the linked list:    ";
    testPrintInput(s_int_arr, SIZE);
    std::cout << "\n(STATIC) double dataType array of [ " << SIZE << " ] elements will be fed to the linked list:     ";
    testPrintInput(s_dub_arr, SIZE);
    std::cout << "\n(STATIC) character dataType array of [ " << SIZE << " ] elements will be fed to the linked list:  ";
    testPrintInput(s_char_arr, SIZE);
    std::cout << "\n(STATIC) string dataType array of [ " << SIZE << " ] elements will be fed to the linked list:     ";
    testPrintInput(s_str_arr, SIZE);

    std::cout << "\n\n(DYNAMIC) integer dataType array of [ " << SIZE << " ] elements will be fed to the linked list:   ";
    testPrintInput(d_int_arr, SIZE);
    std::cout << "\n(DYNAMIC) double dataType array of [ " << SIZE << " ] elements will be fed to the linked list:    ";
    testPrintInput(d_dub_arr, SIZE);
    std::cout << "\n(DYNAMIC) character dataType array of [ " << SIZE << " ] elements will be fed to the linked list: ";
    testPrintInput(d_char_arr, SIZE);
    std::cout << "\n(DYNAMIC) string dataType array of [ " << SIZE << " ] elements will be fed to the linked list:    ";
    testPrintInput(d_str_arr, SIZE);

    std::cout << "\n\nThese items will be used to populate the linked list, representing 4 diffrent dataTypes\n";
    std::cout << "\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

}

//--------------------------------------------------------------------------------------------------------------------------
void objectsPrintFwd() // they will display thier nodes head to tail
{
    std::cout << "\nThis shows how the head-tail print function in the linkedListType class works (STATIC)\n";

    std::cout << "\nhere is the original array of integers:  ";
    testPrintInput(s_int_arr, SIZE);
    std::cout << "\nand here is the linked list of integers: ";
    s_int_ll.printListFwd();
    std::cout << "\n";

    std::cout << "\nhere is the original array of doubles : ";
    testPrintInput(s_dub_arr, SIZE);
    std::cout << "\nand here is the linked list of doubles: ";
    s_dub_ll.printListFwd();
    std::cout << "\n";

    std::cout << "\nhere is the original array of characters:  ";
    testPrintInput(s_char_arr, SIZE);
    std::cout << "\nand here is the linked list of characters: ";
    s_char_ll.printListFwd();
    std::cout << "\n";

    std::cout << "\nhere is the original array of strings:  ";
    testPrintInput(s_str_arr, SIZE);
    std::cout << "\nand here is the linked list of strings: ";
    s_str_ll.printListFwd();
    std::cout << "\n";

    std::cout << "\n\npress any key and hit enter, to see dynamic class objects print forwards: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    std::cout << "\nThis shows how the head-tail print function in the linkedListType class works (DYNAMIC)\n";

    std::cout << "\nhere is the original array of integers:  ";
    testPrintInput(d_int_arr, SIZE);
    std::cout << "\nand here is the linked list of integers: ";
    d_int_ll->printListFwd();
    std::cout << "\n";

    std::cout << "\nhere is the original array of doubles : ";
    testPrintInput(d_dub_arr, SIZE);
    std::cout << "\nand here is the linked list of doubles: ";
    d_dub_ll->printListFwd();
    std::cout << "\n";

    std::cout << "\nhere is the original array of characters:  ";
    testPrintInput(d_char_arr, SIZE);
    std::cout << "\nand here is the linked list of characters: ";
    d_char_ll->printListFwd();
    std::cout << "\n";

    std::cout << "\nhere is the original array of strings:  ";
    testPrintInput(d_str_arr, SIZE);
    std::cout << "\nand here is the linked list of strings: ";
    d_str_ll->printListFwd();
    std::cout << "\n";

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void objectsPrintBwd()
{
    std::cout << "\nThis shows how the tail-head print function in the linkedListType class works (STATIC):\n";

    std::cout << "\nhere is the original array of integers:   ";
    testPrintInput(s_int_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse:   { ";
    s_int_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\nhere is the original array of doubles :   ";
    testPrintInput(s_dub_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse:   { ";
    s_dub_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\nhere is the original array of characters:  ";
    testPrintInput(s_char_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse :   { ";
    s_char_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\nhere is the original array of strings:    ";
    testPrintInput(s_str_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse:   { ";
    s_str_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\n\npress any key and hit enter, to see dynamic class objects print backwards: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    std::cout << "\nThis shows how the tail-head print function in the linkedListType class works (DYNAMIC):\n";

    std::cout << "\nhere is the original array of integers:   ";
    testPrintInput(s_int_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse:   { ";
    s_int_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\nhere is the original array of doubles :   ";
    testPrintInput(s_dub_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse:   { ";
    s_dub_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\nhere is the original array of characters:  ";
    testPrintInput(s_char_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse :   { ";
    s_char_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\nhere is the original array of strings:    ";
    testPrintInput(s_str_arr, SIZE);
    std::cout << "\nand here is the linked list in reverse:   { ";
    s_str_ll.printListBwd();
    std::cout << "}\n";

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void deleteObjects()
{
    std::cout << "\n\nchecks the deleteList() function of the linked list class (STATIC)\n";

    std::cout << "\nthe integer linked list was deleted, the print funciton has nothing to display: \n";
    s_int_ll.deleteList();
    s_int_ll.printListFwd();
    std::cout << "\tintLinkedList.getCount() says there are: " << s_int_ll.getCount() << " nodes";

    std::cout << "\n\nthe double linked list was deleted, the print funciton has nothing to display: \n";
    s_dub_ll.deleteList();
    s_dub_ll.printListBwd();
    std::cout << "\tdubLinkedList.getCount() says there are: " << s_dub_ll.getCount() << " nodes";

    std::cout << "\n\nthe character linked list was deleted, the print funciton has nothing to display: \n";
    s_char_ll.deleteList();
    s_char_ll.printListFwd();
    std::cout << "\tcharLinkedList.getCount() says there are: " << s_char_ll.getCount() << " nodes";
    
    std::cout << "\n\nthe string linked list was deleted, the print funciton has nothing to display: \n";
    s_str_ll.deleteList();
    s_str_ll.printListBwd();
    std::cout << "\tstrLinkedList.getCount() says there are: " << s_str_ll.getCount() << " nodes\n";

    std::cout << "\n\npress any key and hit enter, to see how dynamic objects get deleted: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    std::cout << "\n\nchecks the deleteList() function of the linked list class (DYNAMIC)\n";

    std::cout << "\nthe integer linked list was deleted, the print funciton has nothing to display: \n";
    d_int_ll->deleteList();
    d_int_ll->printListFwd();
    std::cout << "\tintLinkedList.getCount() says there are: " << d_int_ll->getCount() << " nodes";

    std::cout << "\n\nthe double linked list was deleted, the print funciton has nothing to display: \n";
    d_dub_ll->deleteList();
    d_dub_ll->printListBwd();
    std::cout << "\tdubLinkedList.getCount() says there are: " << d_dub_ll->getCount() << " nodes";

    std::cout << "\n\nthe character linked list was deleted, the print funciton has nothing to display: \n";
    d_char_ll->deleteList();
    d_char_ll->printListFwd();
    std::cout << "\tcharLinkedList.getCount() says there are: " << d_char_ll->getCount() << " nodes";
    
    std::cout << "\n\nthe string linked list was deleted, the print funciton has nothing to display: \n";
    d_str_ll->deleteList();
    d_str_ll->printListBwd();
    std::cout << "\tstrLinkedList.getCount() says there are: " << d_str_ll->getCount() << " nodes\n";

    setUp(); // give this a call since you just delted everything

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkDefaultConstructor()
{   
    std::cout << "\na new object will be made to see how the constructor initializes it... \n";
    linkedListType<int> testObj;
    std::cout << "\nafter linkedListType<int> testObj; \n";
    std::cout << "\n  the nodes are: " << testObj.getCount();
    std::cout << "\n  testObj.getHead(); has head pointer on: " << testObj.getHead();
    std::cout << "\n  testObj.getTail(); has tail pointer on: " << testObj.getTail();
    std::cout << "\n  testObj.getCurrent(); has current pointer on: " << testObj.getCurrent();
    std::cout << "\n  testObj.isAscending(); says: " << testObj.isAscending();
    std::cout << "\n  testObj.isDescending(); says: " << testObj.isDescending();
    std::cout << "\n  testObj.isEmpty(); says: " << testObj.isEmpty();

    std::cout << "\n\npress any key and hit enter, to constructor on a dynamic object: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    std::cout << "\na new object will be made to see how the constructor initializes it... \n";
    linkedListType<char> *testOb;
    testOb = new linkedListType<char>;

    std::cout << "\nafter linkedListType<char> *testOb; , testOb = new linkedListType<char>; \n";
    std::cout << "\n  the nodes are: " << testOb->getCount();
    std::cout << "\n  testObj.getHead(); has head pointer on: " << testOb->getHead();
    std::cout << "\n  testObj.getTail(); has tail pointer on: " << testOb->getTail();
    std::cout << "\n  testObj.getCurrent(); has current pointer on: " << testOb->getCurrent();
    std::cout << "\n  testObj.isAscending(); says: " << testOb->isAscending();
    std::cout << "\n  testObj.isDescending(); says: " << testOb->isDescending();
    std::cout << "\n  testObj.isEmpty(); says: " << testOb->isEmpty();

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkEquality()
{
    // need to check = overload, == overload, sizeEqual(), probably the add node also....copy constructor

    std::cout << "\nchecking to see if same nodes s_int_ll.listSizeEqual(s_char_ll.getCount()); : " 
    << s_int_ll.listSizeEqual(s_char_ll.getCount()) << " [ 1 is true, 0 is false ]\n";

    linkedListType<int> otherIntLL;
    for (int i = 0; i < SIZE; i++)
    {
        otherIntLL.insertNodeTail(s_int_arr[i]);
    }

    std::cout << "\nthe intLinkedList is              : ";
    s_int_ll.printListFwd();
    std::cout << "\nanother object was made to compare: ";
    otherIntLL.printListFwd();
    std::cout << "\nthe operator == compares entire list, only true if same nodes and same values...\n";
    std::cout << "(s_int_ll == otherIntLL); " << (s_int_ll == otherIntLL) << " [ 1 is true, 0 is false ] \n";
    std::cout << "...notice that the == is overloaded to take the aggragate...use [ ] overload for node-node comparison\n";

    std::cout << "\nlet's try a dynamic object linkedListType<double> *dubLL; : ";
    linkedListType<double> *dubLL;
    dubLL = new linkedListType<double>;
    dubLL->printListFwd();
    for (int i = 0; i < SIZE; i++)
    {
        if (i == 3)
        {
            dubLL->insertNodeTail(22.222);
        }
        else
        {
            dubLL->insertNodeTail(d_dub_arr[i]);
        }
    }
    std::cout << "\nnow the dynamic object is  : ";
    dubLL->printListFwd();
    std::cout << "\nand the original linkedList: ";
    d_dub_ll->printListFwd();
    std::cout << "\nare these linked lists the same? : " << (*d_dub_ll == *dubLL) << " [ 1 is true, 0 is false ] \n";
    std::cout << "       look at the defrerencing for the overload (*d_dub_ll == *dubLL) because of dynamic objs\n";
    
    setUp(); // have to setUp() again, so values can be restored...

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkCopy() 
{
    linkedListType<int> static_LL_A;    // original static obj LL is created and filled with some data
    static_LL_A.insertNodeTail(1);
    static_LL_A.insertNodeTail(1);
    static_LL_A.insertNodeTail(1);
    static_LL_A.insertNodeTail(1);
    static_LL_A.insertNodeTail(1);
    std::cout << "\n static_LL_A created : ";
    static_LL_A.printListFwd();
    linkedListType<int> keeper_A(static_LL_A);     // make a back up copy
    std::cout << "\n another static LL obj was made using the copy constructor : ";
    keeper_A.printListFwd();
    std::cout << "\n\n if the origianal is deleted, nothing happens to the copy, origianl was deleted: ";
    static_LL_A.deleteList();
    static_LL_A.printListFwd();
    std::cout << "\n the copy is still intact: ";
    keeper_A.printListFwd();
    std::cout << "  , the copy constructor works well for static objects. the copy can repopulate the original by = OL\n";
    static_LL_A = keeper_A;
    std::cout << " here they are, original and copy: ";
    static_LL_A.printListFwd();
    std::cout << "  ";
    keeper_A.printListFwd();
    std::cout << "\n\n now the copy will be deleted and we will see if the original can restore the copy";
    keeper_A.deleteList();
    std::cout << "\n the copy is now empty: ";
    keeper_A.printListFwd();
    keeper_A = static_LL_A;
    std::cout << "\n after reset, here they are, original and copy: ";
    static_LL_A.printListFwd();
    std::cout << "  ";
    keeper_A.printListFwd();


    std::cout << "\n\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");


    linkedListType<int> *dynamic_LL_B = nullptr;        // original dynamic obj LL pointer is made and holstered
    dynamic_LL_B = new linkedListType<int>;             // original dynamic obj LL pointer  points to a new LL obj
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    std::cout << "\n\n dynamic_LL_B created: ";
    dynamic_LL_B->printListFwd();
    linkedListType<int> *keeper_B(dynamic_LL_B);     // make a back up copy ...bad idea, dynamic to dynamic is shallow
    std::cout << "\n another dyanamic LL obj was made using the copy constructor : ";
    keeper_B->printListFwd();
    std::cout << "\n\n if the origianal is deleted, nothing happens to the copy, original is deleted: ";
    dynamic_LL_B->deleteList();
    dynamic_LL_B->printListFwd();
    std::cout << "\n the copy is still intact: ";
    keeper_B->printListFwd();
    std::cout << " the copy constructor works well for dynamic objects. the copy can repopulate the original by = OL\n";
    dynamic_LL_B = keeper_B;
    std::cout << " here they are, original and copy: ";
    dynamic_LL_B->printListFwd();
    std::cout << "  ";
    keeper_B->printListFwd();//
    std::cout << "\n\n now the copy will be deleted and we will see if the original can restore the copy";
    keeper_B->deleteList();
    std::cout << "\n the copy is now empty: ";
    keeper_B->printListFwd();
    keeper_B = dynamic_LL_B;
    std::cout << "\n after reset, here they are, original and copy: ";
    dynamic_LL_B->printListFwd();
    std::cout << "  ";
    keeper_B->printListFwd();
    std::cout << "\n\ndynamic to dynamic makes a shallow copy, be careful";


    std::cout << "\n\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");


    std::cout << "\n static_LL_A created : ";
    static_LL_A.printListFwd();

    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    dynamic_LL_B->insertNodeTail(2);
    std::cout << "\n dynamic_LL_B created: ";
    dynamic_LL_B->printListFwd();

    linkedListType<int> static_LL_C;    // another static obj LL is created and filled with some data
    static_LL_C.insertNodeTail(3);
    static_LL_C.insertNodeTail(3);
    static_LL_C.insertNodeTail(3);
    static_LL_C.insertNodeTail(3);
    static_LL_C.insertNodeTail(3);
    std::cout << "\n static_LL_C created : ";
    static_LL_C.printListFwd();

    linkedListType<int> *dynamic_LL_D = nullptr;        // another dynamic obj LL pointer is made and holstered
    dynamic_LL_D = new linkedListType<int>;             // another dynamic obj LL pointer  points to a new LL obj
    dynamic_LL_D->insertNodeTail(4);
    dynamic_LL_D->insertNodeTail(4);
    dynamic_LL_D->insertNodeTail(4);
    dynamic_LL_D->insertNodeTail(4);
    dynamic_LL_D->insertNodeTail(4);
    std::cout << "\n dynamic_LL_D created: ";
    dynamic_LL_D->printListFwd();

    std::cout << "\n\n assign static by dynamic, A = D static_LL_A = *dynamic_LL_D;   ";
    static_LL_A = *dynamic_LL_D;
    static_LL_A.printListFwd();
    std::cout << "    notice the dereference needed";
    //dynamic_LL_D->deleteList(); check successful
    //static_LL_A.printListFwd();
    std::cout << "\n assign dynamic by static, B = C  dynamic_LL_B = &static_LL_C;  ";
    dynamic_LL_B = &static_LL_C;
    dynamic_LL_B->printListFwd();
    std::cout << "    notice the 'address of' needed";
    //static_LL_C.deleteList();          // bad check...made a shallow copy
    //dynamic_LL_B->printListFwd();
    std::cout << "\n\nthe dynamic class objects don't take the copy constructor or = overload well, they are all shallow\n";

    std::cout << "\n\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkInsertHead()
{
    int insert = 999;
    std::cout << "\nHere is the current linked list: ";
    s_int_ll.printListFwd();
    std::cout << "\nThere are [ " << s_int_ll.getCount() << " ] nodes currently in the list";
    std::cout << "\nyou want to insert { " << insert << " } at the front of this linked list\n";
    s_int_ll.insertNodeHead(insert);
    std::cout << "\nusing the insertNodeHead() method of the class : ";
    s_int_ll.printListFwd();
    std::cout << "\nThere are [ " << s_int_ll.getCount() << " ] nodes currently in the list";

    std::cout << "\n\nnow lets start with a blank linked list: ";
    s_int_ll.deleteList();
    s_int_ll.printListFwd();
    std::cout << "\nThere are [ " << s_int_ll.getCount() << " ] nodes currently in the list";
    s_int_ll.insertNodeHead(insert);
    std::cout << "\n\nand insert: " << insert;
    std::cout << "         the list is now : ";
    s_int_ll.printListFwd();
    std::cout << "\nThere is [ " << s_int_ll.getCount() << " ] node currently in the list";

    setUp();  // you changed somethings, so reset it. 

    std::cout << "\n\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}
//--------------------------------------------------------------------------------------------------------------------------
void checkIterator()
{
    std::cout << "\nhere is what a linked list with characters looks like now: ";
    s_char_ll.printListFwd();
    std::cout << "\nthe linked list has n = [ " << s_char_ll.getCount() << " ]  nodes, indexed 0 to n - 1\n";
    
    std::cout << "\nbuilt in class memebers allow iterative methods on the linked list, an iterator was used to print:\n";
    
    for (int i = 0; i < s_char_ll.getCount(); i++) 
    {
        std::cout << "the value at node " << i + 1 << " ...index [ " << i << " ] is { " << s_char_ll.getDataAtIndex(i) << " }\n";
    }
    
    std::cout << "\n     the iterator is placed on index [3] s_char_ll.currentToIndex(3);   and can be moved around\n";
    s_char_ll.currentToIndex(3);
    std::cout << "     there are many iterator options, ie s_char_ll.getDataAtIndex(3) : " << s_char_ll.getDataAtIndex(3);
    

    std::cout << "\n\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkBadThings()
{
    std::cout << "\nthis class purposfully gives away important private variables\n";
    linkedListType<double> adversary;
    std::cout << "\nsome of the flexibility, like taking the iterator (*current) won't hurt much";
    std::cout << "\nhere is the static linked list of doubles:             ";
    s_dub_ll.printListFwd();
    adversary.setHead(s_dub_ll.getHead());
    adversary.setTail(s_dub_ll.getTail());
    adversary.setCount(s_dub_ll.getCount());
    std::cout << "\nadversary object just took everything from and is now: ";
    adversary.printListFwd();
    adversary.deleteList();
    std::cout << "\nthe adversery just deleted everything, the origical is:";
    s_dub_ll.printListFwd();
    std::cout << "\nwhat is worse, the original object doesn't even know what happened, it still thinks it has 5 nodes\n";
    
    s_dub_ll.initialize(); // if you don't do this, the program will crash
    setUp();

    std::cout << "\n\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkRemoval()
{
    std::cout << "\nthis class has some functions to delete nodes\n";

    std::cout << "\nhere is the linked list of strings           : ";
    s_str_ll.printListFwd();
    std::cout << "\nthere are [ " << s_str_ll.getCount() << " ] nodes";
    std::cout << "\nhere is the same list with first node deleted: ";
    s_str_ll.deleteNodeHead();
    s_str_ll.printListFwd();
    std::cout << "\nthere are [ " << s_str_ll.getCount() << " ] nodes";

    std::cout << "\n\nhere is the linked list of characters     :    ";
    s_char_ll.printListFwd();
    std::cout << "\nthere are [ " << s_char_ll.getCount() << " ] nodes";
    std::cout << "\nhere is the same list with last node deleted:  ";
    s_char_ll.deleteNodeTail();
    s_char_ll.printListFwd();
    std::cout << "\nthere are [ " << s_char_ll.getCount() << " ] nodes";

    std::cout << "\n\n\npress any key and hit enter, to see more delete options: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    int deleteMeValue = s_int_ll.getDataAtIndex(s_int_ll.getCount() - 3 );
    int deleteMeIndex = s_int_ll.getCount() - 3;
    std::cout << "\nhere is a linked list of integers: ";
    s_int_ll.printListFwd();
    std::cout << "\nthere are [ " << s_int_ll.getCount() << " ] nodes";
    std::cout << "\ndelete node index [ " << s_int_ll.getCount() - 3 << " ]" << " = " << deleteMeValue;
    std::cout << "\nnow the linked list is: ";
    s_int_ll.deleteNodeIndex(deleteMeIndex);
    s_int_ll.printListFwd();
    std::cout << "\nthere are [ " << s_int_ll.getCount() << " ] nodes";

    std::cout << "\n\nhere is the linked list of doubles: ";
    s_dub_ll.printListFwd();
    std::cout << "\nthere are [ " << s_dub_ll.getCount() << " ] nodes\n";
    std::cout << "\nthe max is " << s_dub_ll.getLargest() << " at index [ " << s_dub_ll.getLargestIndexF() << " ] ";
    std::cout << "\nthe min is " << s_dub_ll.getSmallest() << " at index [ " << s_dub_ll.getSmallestIndexF() << " ] ";
    std::cout << "\nthe max and min were deleted, here is the list now: ";
    s_dub_ll.deleteNodeMax();
    s_dub_ll.deleteNodeMin();
    s_dub_ll.printListFwd();
    std::cout << "\nthere are [ " << s_dub_ll.getCount() << " ] nodes";
    



    setUp(); 

    std::cout << "\n\n\npress any key and hit enter, to see more class functions: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkMaxMin()
{
    std::cout << "\nhere is a linked list of doubles: ";
    d_dub_ll->printListFwd();
    std::cout << "\nthe largest value in this linked list is : " << d_dub_ll->getLargest();
    std::cout << "\nit was found at index [ " << d_dub_ll->getLargestIndexF() << " ]";
    std::cout << "\nthe smallest value in this linked list is: " << d_dub_ll->getSmallest();
    std::cout << "\nit was found at index [ " << d_dub_ll->getSmallestIndexF() << " ]";


    std::cout << "\n\n\npress any key and hit enter, to see more class features: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}
//--------------------------------------------------------------------------------------------------------------------------
void checkSearchDelete() 
{
    std::random_device rdevice{};
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum{0,SIZE-1};

    std::string searchTerm = "jihad";
    std::cout << "\nhere is the linked list of strings: ";
    s_str_ll.printListFwd();
    std::cout << "\nyou want to see if { " << searchTerm << " } is on the list";
    std::cout << "\nsearch says: " << s_str_ll.valueExists(searchTerm) << "    [ false = 0, true = 1 ]";
    std::cout << "\ncheck the index..." << s_str_ll.firstIndexOfValue(searchTerm);
    searchTerm = s_str_ll.getDataAtIndex(randomNum(num));
    std::cout << "\n\nwe will search for: { " << searchTerm << " }";
    std::cout << "\nsearch says: " << s_str_ll.valueExists(searchTerm) << "    [ false = 0, true = 1 ]\n";
    std::cout << "check the index...   " << s_str_ll.firstIndexOfValue(searchTerm);
    std::cout << "\n" <<searchTerm << "   was deleted, list is now: ";
    s_str_ll.deleteNodeValue(searchTerm);
    s_str_ll.printListFwd();
    std::cout << "\nthere are [ " << s_str_ll.getCount() << " ] nodes , and " << searchTerm << " appears : " <<
    s_str_ll.frequencyOfValue(searchTerm) << "  times\n";

    setUp();

    std::cout << "\n\n\npress any key and hit enter, to see more class features: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}
//--------------------------------------------------------------------------------------------------------------------------
void checkInserts()
{
    std::random_device rdevice{};
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum{0,SIZE-1};
    //int deleteMeValue = d_int_ll->getDataAtIndex(randomNum(num));   // the dynamics do strange things
    //int deleteMeIndex = d_int_ll->firstIndexOfValue(deleteMeValue);
    //int deleteMeIndex = 6;
    //int deleteMeValue = s_int_ll.getDataAtIndex(deleteMeIndex);
    int deleteMeIndex = randomNum(num);
    int deleteMeValue = s_int_ll.getDataAtIndex(deleteMeIndex);

    std::cout << "\nhere is a linked list of integers: ";
    s_int_ll.printListFwd();
    std::cout << "\nwe will look for { " << deleteMeValue << " }\n";
    std::cout << "\nit first appears  at index [ " << deleteMeIndex<< " ]  ,  "
         << s_int_ll.frequencyOfValue(deleteMeValue) << " time(s)\n";
    std::cout << "there are currently  < " << s_int_ll.getCount() << " >  nodes in this list, and the term will be deleted\n";
    s_int_ll.deleteNodeIndex(deleteMeIndex);
    std::cout << "\nthe list with { " << deleteMeValue << " } removed  :   ";
    s_int_ll.printListFwd();
    std::cout << "\nnow it has < " << s_int_ll.getCount() << " >   nodes, and { " << deleteMeValue << " } is in it: " <<
        s_int_ll.frequencyOfValue(deleteMeValue) << " time(s)";
    std::cout << "\ntry another delete operation on same term:  ";
    s_int_ll.deleteNodeValue(deleteMeValue);
    
    std::cout << "\n\n\npress any key and hit enter, to see more delete options: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    std::cout << "\nthe linked list is (from last screen) :  ";
    s_int_ll.printListFwd();
    std::cout << "\nyou want to put { " << deleteMeValue << " } back in the list at the first AND last Node\n\n";
    s_int_ll.insertNodeHead(deleteMeValue);
    s_int_ll.insertNodeTail(deleteMeValue);
    s_int_ll.printListFwd();
    std::cout << "  " <<s_int_ll.getCount() << " nodes, and " << deleteMeValue << " x" << s_int_ll.frequencyOfValue(deleteMeValue);
    std::cout << "\n\nnow { " << deleteMeValue << " } will be deleted, and put back only at index [ " << randomNum(num) << " ]\n";
    s_int_ll.deleteAllValues(deleteMeValue); //  this is how you multiple delete
    std::cout << "\nremoved 2 nodes, and over-wrote 1, there are < " << s_int_ll.getCount() << " > nodes";
    std::cout << "\nthe list is : ";
    s_int_ll.printListFwd();

    std::cout << "\n\n\npress any key and hit enter, to see more delete options: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    linkedListType<std::string> testStringLL;
    std::string testArray[SIZE];
    std::ifstream inFile;
    inFile.open("stringInput.txt");
    for (int i = 0; i < SIZE; i++)
    {
        inFile >> testArray[i];
    }
    testStringLL.makeListfromArray(testArray, SIZE);
    std::string deleteMeString = "COBOL";           // change here as needed
    std::cout << "\nhere is a linked list of strings: ";
    testStringLL.printListFwd();
    std::cout << "\n\nit looks like someone put { " << deleteMeString << " } in there " << 
    testStringLL.frequencyOfValue(deleteMeString) << "   time(s), but want to remove it\n";
    std::cout << "\nthe list has < " << testStringLL.getCount() << " > nodes, and { " << deleteMeString << 
    " } appears at index(s) : ";
    for (int i = 0; i < testStringLL.getCount(); i++)
    {
        if (testStringLL.getDataAtIndex(i) == deleteMeString)
        {
            std::cout << i << " ";
        }
    }
    testStringLL.deleteAllValues(deleteMeString);
    std::cout << "\n\nall instances were deleted      : ";
    testStringLL.printListFwd();
    std::cout << "\n\nthe list now has < " << testStringLL.getCount() << " > nodes  ,   and { " << deleteMeString << 
    " } appears x " << testStringLL.frequencyOfValue(deleteMeString); 


    setUp();
    inFile.close();
    std::cout << "\n\n\npress any key and hit enter, to see more class features: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
    
}
//--------------------------------------------------------------------------------------------------------------------------
void checkInsertsMore()
{

    setUp();
    std::cout << "\n\n\npress any key and hit enter, to see more class features: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkSortAsc()
{
    std::cout << "\nthe linked list is currently: ";
    s_int_ll.printListFwd();
    std::cout << "\nwant to sort small to large : ";
    sortInputArrayAsc(s_int_arr, SIZE);
    testPrintInput(s_int_arr, SIZE);
    std::cout << "\n\nusing the function to sort the linked list smallest largest, the resulting list is:\n                              ";
    s_int_ll.sortAscending();
    s_int_ll.printListFwd();

    setUp();
    std::cout << "\n\n\npress any key and hit enter, to see more class features: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkSortDes()
{

    std::cout << "\nthe linked list is currently: ";
    s_int_ll.printListFwd();
    std::cout << "\nwant to sort large to small : ";
    sortInputArrayDsc(s_int_arr, SIZE);
    testPrintInput(s_int_arr, SIZE);
    std::cout << "\n\nusing the function to sort the linked list largest to smallest, the resulting list is:\n                              ";
    s_int_ll.sortDescending();
    s_int_ll.printListFwd();

    setUp();
    std::cout << "\n\n\npress any key and hit enter, to see more class features: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void checkOperatorOLs ()
{
    std::cout << "\nhere is the current linked list: ";
    s_dub_ll.printListFwd();
    std::cout << " \n\nusing the [ ] overload, the linked list can be treated like an array: \n";
    std::cout << "                                 { ";
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << std::fixed << std::showpoint << std::setprecision(3); // set presistants
        std::cout << s_dub_ll[i] << " ";
    }
    std::cout << " }\n";
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
template <class Tp>                                
void sortInputArrayDsc(Tp someArray[], int size) // bubbles
{
    Tp temp; // don't initialize on template, you don't know what it will be

    for (int iteration = 1; iteration < size; iteration++)
    {
        for (int index = 0; index < size - iteration; index++)
        {
            if (someArray[index] < someArray[index + 1])
            {
                temp = someArray[index];                      // take larger value from lower index
                someArray[index] = someArray[index + 1];      // take smaller value to lower index from higher index
                someArray[index + 1] = temp;                  // put larger value in larger index
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------
template <class Tp>
void sortInputArrayAsc(Tp someArray[], int size) // bubbles
{
    Tp temp; // don't initialize on template, you don't know what it will be

    for (int iteration = 1; iteration < size; iteration++)
    {
        for (int index = 0; index < size - iteration; index++)
        {
            if (someArray[index] > someArray[index + 1])
            {
                temp = someArray[index];                      // take larger value from lower index
                someArray[index] = someArray[index + 1];      // take smaller value to lower index from higher index
                someArray[index + 1] = temp;                  // put larger value in larger index
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
template <class Ty>
void testPrintInput(Ty someArray[], int size)
{
    std::cout << "{ ";
    for (int i = 0; i < size; i++) 
    {
        std::cout << someArray[i] << " ";
    }
    std::cout << "}";

}


