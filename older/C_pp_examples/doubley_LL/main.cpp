/*
    doubly linked lists are linked lists where every node has a next pointer and a back pointer
    every node has the address of the forward node (except last node, it is on nullptr)
    every node has the address of the previous node (except first node, it is on nullptr)

    the benift is that you can traverse it in either direction, but you have to manage a head and a tail
    you'll still want to do the regular operations:
    1) initialize
    2) destroy
    3) determine if empty
    4) search for a specific value
    5) get first element
    6) get last element
    7) insert an item
    8) delete an item
    9) find the length
    10) print
    11) copy 
*/

#include "doublyLinkedList.h"

//globals
char ADVANCE = 'A';
const int SIZE = 13;
doublyLinkedList<std::string> str_ll;
doublyLinkedList<double> dub_ll;
doublyLinkedList<int> int_ll;
doublyLinkedList<char> char_ll;

//prototypes
void setUp();
void testPrintFwd();
void testSort();
void checkManual();
void checkDynamic();
void checkDelete();
void checkInsert();
void checkMisc();
void mostInOne();

//-------------------------------------------------------------------------------------------------------------------------------
int main() 
{
    std::cout << std::fixed << std::showpoint << std::setprecision(3); // set presistants
    
    setUp();
    //testPrintFwd();
    //testSort();
    //checkManual();              // not too user proof...but a little, enter dataTypes you are supposed to
    //checkDynamic();
    //checkDelete();
    //checkInsert();
    //checkMisc();
    mostInOne();


    std::cout << "\n          program complete\n";
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------
void setUp()
{
     str_ll.str_randomBuild(SIZE);
     dub_ll.dub_randomBuild(SIZE);
     int_ll.int_randomBuild(SIZE);
     char_ll.char_randomBuild(SIZE);
}

//-------------------------------------------------------------------------------------------------------------------------------
void testPrintFwd()
{
    std::cout << std::endl;
    str_ll.print();
    std::cout << std::endl;
    dub_ll.print();
    std::cout << std::endl;    
    int_ll.print();
    std::cout << std::endl;    
    char_ll.print();
    std::cout << std::endl;

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
void testSort()
{
    std::cout << "\nthis is the integer LL now: ";
    int_ll.print();
    std::cout << "\nthis is the integer LL asc: ";
    int_ll.sort('a');
    int_ll.print();
    std::cout << "\nthis is the integer LL dsc: ";
    int_ll.sort('d');
    int_ll.print();

    std::cout << "\n\nthis is the double LL now:  ";
    dub_ll.print();
    std::cout << "\nthis is the double LL asc:  ";
    dub_ll.sort('a');
    dub_ll.print();
    std::cout << "\nthis is the double LL dsc:  ";
    dub_ll.sort('d');
    dub_ll.print();

    std::cout << "\n\nthis is the string LL now:  ";
    str_ll.print();
    std::cout << "\nthis is the string LL asc:  ";
    str_ll.sort('a');
    str_ll.print();
    std::cout << "\nthis is the string LL dsc:  ";
    str_ll.sort('d');
    str_ll.print();

    std::cout << "\n\nthis is the char LL now:    ";
    char_ll.print();
    std::cout << "\nthis is the char LL asc:    ";
    char_ll.sort('a');
    char_ll.print();
    std::cout << "\nthis is the char LL dsc:    ";
    char_ll.sort('d');
    char_ll.print();

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
void checkManual ()
{
    char_ll.manualCreate();
    int_ll.manualCreate();
    dub_ll.manualCreate();
    str_ll.manualCreate();

    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
void checkDynamic()
{
    doublyLinkedList<int> *test;
    test = new doublyLinkedList<int>;
    test->int_randomBuild(19);          // change if needed

    std::cout << "\na dynamic doubly LL was made: ";
    test->print();
    std::cout << "\n\nthere are < " << test->length() << " > nodes";
    std::cout << "\nthe largest value is { " << test->max() << " }";
    std::cout << "\nthe smallest value is { " << test->min() << " }";
    std::cout << "\n\nhere it is ascending        : ";
    test->sort('a');
    test->print();


    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
void checkDelete()
{
    char_ll.sort('a');
    std::cout << "\nhere is the sorted LL: ";
    char_ll.print();
    std::cout << "\nthere are < " << char_ll.length() << " > nodes, and the first and last will be deleted\n";
    char_ll.deleteNodeHead();
    char_ll.deleteNodeTail();
    std::cout << "\nhere it is now      :  ";
    char_ll.print();
    std::cout << "\nthere are < " << char_ll.length() << " > nodes";

    setUp();
    std::cout << "\n\npress any key and hit enter, to test the next delete function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    int index = 2;
    int otherIndex = 5;
    double value_at_index = dub_ll.valueAtIndex(index);
    std::cout << "\n               this is a linked list    :   ";
    dub_ll.print();
    std::cout << "\n   you want to see what is at index [ " << index << " ]";
    std::cout << "\n           the class says index [ " << index << " ] has a value of { " << value_at_index << " }";
    std::cout << "\n                   there are < " << dub_ll.length() << " > nodes";
    std::cout << "\n                         and value occurs x " << dub_ll.freqOfValue(value_at_index);  
    std::cout << "\n\nthe value { " << value_at_index << " }  at index [ " << index << " ]   will be put at index [ " << otherIndex << " ]";
    dub_ll.OWinsertNodeIndex(otherIndex, value_at_index);
    std::cout << "\nnow the list is                           : ";
    dub_ll.print();
    std::cout << "\nand { " << value_at_index << " } appears x " << dub_ll.freqOfValue(value_at_index);
    std::cout << "\n\nafter deleting all occurances             : ";
    dub_ll.deleteAllOfValue(value_at_index);
    dub_ll.print();
    std::cout << "\nit appears " << dub_ll.freqOfValue(value_at_index) << " times, and there are < " << dub_ll.length() << " > nodes";
    index = 3;
    value_at_index = dub_ll.valueAtIndex(index);
    std::cout << "\n\nthe value { " << value_at_index << " } , index [ " << index << " ] will be deleted";
    std::cout << "\n                         the list is now:   ";
    dub_ll.deleteNodeIndex(index);
    dub_ll.print();
    std::cout << "\nthere are < " << dub_ll.length() << " > nodes , and the value appears x" << dub_ll.freqOfValue(value_at_index);
    setUp();
    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
void checkInsert()
{

    std::random_device rdevice{};
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum{0,SIZE-1}; // get some indecies to move around

    int index = randomNum(num);
    int nextIndex = randomNum(num);
    int value_at_index = int_ll.valueAtIndex(index);

    std::cout << "\nthe linked list is :   ";
    int_ll.print();
    std::cout << "\nthere are < " << int_ll.length() << " > nodes , and { " << value_at_index << " } , index [ "<< index << " ] will go to [ " << nextIndex << " ]";
    std::cout << "\n\nthe linked list is :   ";
    int_ll.insertAtIndex(nextIndex, value_at_index);
    int_ll.print();
    nextIndex = randomNum(num);
    index = randomNum(num);
    value_at_index = int_ll.valueAtIndex(index);
    std::cout << "\nthere are < " << int_ll.length() << " > nodes , and { " << value_at_index << " } , index [ "<< index << " ] will go to [ " << nextIndex << " ]";
    std::cout << "\n\nthe linked list is :   ";
    int_ll.insertAtIndex(nextIndex, value_at_index);
    int_ll.print();
    std::cout << "\nthere are < " << int_ll.length() << " > nodes\n\nnotice this is a soft insert, no over-write";

    setUp();
    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
void checkMisc()
{
    std::random_device rdevice{};
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum{0,SIZE-1}; // get some indecies to move around
    int index = randomNum(num);
    double value = dub_ll.valueAtIndex(index);

    std::cout << "\nhere is the list     :  ";
    dub_ll.print();
    std::cout << "\nit has < " << dub_ll.length() << " > nodes, first index of value { " << value << " }  is [ " << dub_ll.firstIndexOfValue(value) << " ]\n";

    std::cout << "\nturn it into a circular linked list and print 3 times: \n\n";
    dub_ll.spinAround3times();

    setUp();
    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}
//-------------------------------------------------------------------------------------------------------------------------------
void mostInOne()
{
    std::cout << "\nhere is the list : ";
    int_ll.print();
    std::cout << "\nnodes < " << int_ll.length() << " > , max { " << int_ll.max() << " } , min { " << int_ll.min() << " }\n";
    std::cout << "\ndelete the head: ";
    int_ll.deleteNodeHead();
    int_ll.print();
    std::cout << "\ndelete the tail: ";
    int_ll.deleteNodeTail();
    int_ll.print();
    std::cout << "\nnodes < " << int_ll.length() << " > , max { " << int_ll.max() << " } , min { " << int_ll.min() << " }\n";
    std::cout << "\ndelete the list: ";
    int_ll.destroy();
    int_ll.print();
    std::cout << "\nnodes < " << int_ll.length() << " > , max { " << int_ll.max() << " } , min { " << int_ll.min() << " }\n";
    std::cout << "\nrevive the list: ";
    int_ll.int_randomBuild(SIZE);
    int_ll.print();
    std::cout << "\nnodes < " << int_ll.length() << " > , max { " << int_ll.max() << " } , min { " << int_ll.min() << " }\n";
    std::cout << "\nsort ascenting : ";
    int_ll.sort('a');
    int_ll.print();
    std::cout << "\nsort descending: ";
    int_ll.sort('d');
    int_ll.print();
    std::cout << "\nconvert circular: \n";
    int_ll.spinAround3times();

    setUp();
    std::cout << "\n\npress any key and hit enter, to do more all-in-one tests: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");

    std::random_device rdevice{};
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum{0,SIZE-1}; // get some indecies to move around

    int index = randomNum(num);
    int value = int_ll.valueAtIndex(index);

    std::cout << "\nhere is the list : ";
    int_ll.print();
    std::cout << "\nnodes < " << int_ll.length() << " > , max { " << int_ll.max() << " } , min { " << int_ll.min() << " }\n";
    std::cout << "\nsearch for { " << value << " } , it is: " << int_ll.search(value) << "  , and at index [ " << index << " ]\n";
    index = randomNum(num);
    std::cout << "\noverwrite index [ " << index << " ] , and insert { " << value << " }\n";
    int_ll.print();
    std::cout << std::endl;
    int_ll.OWinsertNodeIndex(index, value);
    int_ll.print();
    std::cout << "\n\nadd { " << value << " } to the head and tail:\n";
    int_ll.insertHead(value);
    int_ll.insertTail(value);
    int_ll.print();
    std::cout << "\nthere are < " << int_ll.length() << " > nodes, and { " << value << " } shows up x" << int_ll.freqOfValue(value) << " , first at index [ " << int_ll.firstIndexOfValue(value) << " ]\n";
    std::cout << "\ndelete all instances of { " << value << " } and the list is:\n";
    int_ll.deleteAllOfValue(value);
    int_ll.print();
    std::cout << "\nthere are < " << int_ll.length() << " > nodes, and { " << value << " } shows up x" << int_ll.freqOfValue(value);
    index = 2;
    value = int_ll.valueAtIndex(index);
    std::cout << "\n\ndo a soft insert (no overwrite) of { " << value << " } , at index [ " << index << " ]\n";
    int_ll.insertAtIndex(index, value);
    int_ll.print();
    std::cout << "\nthere are < " << int_ll.length() << " > nodes, and { " << value << " } shows up x" << int_ll.freqOfValue(value);

    setUp();
    std::cout << "\n\npress any key and hit enter, to test the next linked-list class function: ";
    std::cin >> ADVANCE;
    //std::this_thread::sleep_for(std::chrono::seconds(3)); // do what you want with these to adjust delays
    std::cout.flush();
    system("clear");
}

//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
