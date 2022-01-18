/*
    a list is a collection of values of the same type
    an array is a collection of values of the same type that is sequentially stored in memory (good application of a list)
    size is the number of elements
    since the size can change, if you do want to use an array, you will have to know the maximum size

    these are some basic things you might want to do:
    - search list for a specific item
    - sort the list
    - insert an item to the list
    - delete an item from the list
    - print the list

    use your math skills to detremine what the best algorithm should be
    the performance of each algo is different, pay attention to comparisons and assignments needed
    averages, your application, your resources, and other things are important to consider

*/

// administrative information
    #include <iostream>
    #include <random>
    #include <iomanip>
    #include <chrono>
    #include <thread>

    void initialize(int list[], int listLength);                              // a
    void makeCopy(const int copy[], int toCopy[], int size);                  // b
    void printList(const int list[], int listLength);                         // c
    void interact(int original[], int list[], int size);                      // d
    
    void elementMaxMin(const int list[], int size);                           // 1
    void seqentialSearch(const int list[], int listLength, int searchItem);   // 2
    void selectionSort(int list[], int listLength);                           // 3
    void bubbleSort(int list[], int listLength);                              // 4
    void insertionSort(int list[], int listLength);                           // 5
    void binarySearch(const int list[], int size, int searchTerm);            // 6
//                            ... headers, prototypes, ect

//------------------------------------------------------------------------------------------------------------------------------
int main() {

    // just some set-up
    std::random_device rdevice{};
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum1{1,20};

    const int size = 17; // or use randomNum1(num1)
    int list[size];
    int original[size];
    
    initialize(list, size); // fill with random numbers
    makeCopy(list, original, size); // make a copy for comparison
    interact(original, list, size); // start the interaction

    std::cout << "program complete.\n";

return 0;
}

// a ---------------------------------------------------------------------------------------------------------------------------
void initialize(int list[], int listLength) {
    std::random_device rdevice{};
    std::default_random_engine num{ rdevice() };
    std::uniform_int_distribution<unsigned int> randomNum{0,299}; // adjust range here
    for (int i = 0; i < listLength; i++) {
        list[i] = randomNum(num);
    }
}

// b ---------------------------------------------------------------------------------------------------------------------------
void makeCopy(const int copy[], int toCopy[], int size) {
    for (int i = 0; i < size; i++) {
        toCopy[i] = copy[i];
    }
}

// c ---------------------------------------------------------------------------------------------------------------------------
void printList(const int list[], int listLength) {
    std::cout << "{  ";
    for (int i = 0; i < listLength; i++) {
        std::cout << std::left << std::setw(5) << list[i];
    }
    std::cout << "}";
}

// d ---------------------------------------------------------------------------------------------------------------------------
void interact(int original[], int list[], int size) {
    // pick the algo that you want to see
    int selection = 0;
    int searchTerm; // for use in case 3
    char advance;
    
        do {
        std::cout << "\nThere are < " << size << " > elements in this list , ";
        printList(list, size);
        std::cout << "\n(1) min/max , (2) seq search , (3) selectrion sort , (4) bubble sort , (5) insertion sort , (6) bin search\n " <<
         "   (0) to make a new array , (999) to stop: ";
        std::cin >> selection;
        if (std::cin) {
        switch (selection) {
            case 0:
                     initialize(list, size); // fill with random numbers
                     makeCopy(list, original, size);
                     std::cout << "\nnew array made...";
                     std::cout << std::endl << std::endl << std::endl;
                     std::cout << "\n\npress any key and hit enter, to try more: ";
                     std::cin >> advance;
                     std::cout.flush();
                     system("clear"); 
                     break;
            case 1: 
                    elementMaxMin(list, size);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << "\n\npress any key and hit enter, to try more: ";
                    std::cin >> advance;
                    std::cout.flush();
                    system("clear"); 
                    break;
            case 2: 
                    std::cout << "\nEnter the integer you want to search for: ";
                    std::cin >> searchTerm;
                    seqentialSearch(list, size, searchTerm);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << "\n\npress any key and hit enter, to try more: ";
                    std::cin >> advance;
                    std::cout.flush();
                    system("clear"); 
                    break;
            case 3:
                    std::cout << "\noriginal list is :    ";
                    printList(original, size);
                    selectionSort(list, size);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << "\n\npress any key and hit enter, to try more: ";
                    std::cin >> advance;
                    std::cout.flush();
                    system("clear"); 
                    break;
            case 4:
                    std::cout << "\noriginal list is :    ";
                    printList(original, size);
                    bubbleSort(list, size);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << "\n\npress any key and hit enter, to try more: ";
                    std::cin >> advance;
                    std::cout.flush();
                    system("clear"); 
                    break;
            case 5: 
                    std::cout << "\noriginal list is :    ";
                    printList(original, size);
                    insertionSort(list, size);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << "\n\npress any key and hit enter, to try more: ";
                    std::cin >> advance;
                    std::cout.flush();
                    system("clear"); 
                    break;
            case 6:
                    std::cout << "\nThe list needs to be sorted before using this...";
                    bubbleSort(list, size);
                    std::cout << "\nEnter the integer you want to search for: ";
                    std::cin >> searchTerm;
                    binarySearch(list, size, searchTerm);
                    std::cout << std::endl << std::endl << std::endl;
                    std::cout << "\n\npress any key and hit enter, to try more: ";
                    std::cin >> advance;
                    std::cout.flush();
                    system("clear"); 
                    break;
            case 999: break;
            default: 
                    std::cout << "\n           INVALID, enter a number 0, 1, 2, 3, 4, 5, 6, or 7, then press then [enter] button.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(4)); // do what you want with these to adjust delays
                    std::cout.flush();
                    system("clear");
                    break;
        }
        makeCopy(original, list, size);
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\n           INVALID, enter a number 0, 1, 2, 3, 4, 5, 6, or 7, then press then [enter] button.\n";
            std::this_thread::sleep_for(std::chrono::seconds(4)); // do what you want with these to adjust delays
            std::cout.flush();
            system("clear");
        }
    }
    while (selection != 999);
    std::cout << "\nuser wants to end -> ";
}

// 1 ---------------------------------------------------------------------------------------------------------------------------
void elementMaxMin(const int list[], int size) {
    int min = 1000;
    int max = 0;

    for (int i = 0; i < size; i++) {
        if (list[i] < min) min = list[i];
        if (list[i] > max) max = list[i];
    }
    std::cout << "\nThe largest element is: { " << max << " } , the smallest is : { " << min << " }";
}

// 2 ---------------------------------------------------------------------------------------------------------------------------
void seqentialSearch(const int list[], int listLength, int searchItem) {
    
    std::cout << "Sequential search to see if { " << searchItem << " } is in the list...\n";
    
    int location = 0;
    bool found = false;
    int comps = 0;

    while (location < listLength && !found) {
        comps++;
        if (list[location] == searchItem) found = true;
        else location++;
    }
    if (found) {
        std::cout << "{ " << searchItem << " } was found at least one time at index: [ " << location << " ]\n";
        std::cout << "It took < " << comps << " > key comparisons to figure this out.\n";
    } 
    else {
        std::cout << "this list does not have an element with the value of { " << searchItem << " }\n";
        std::cout << "It took < " << comps << " > key comparisons to figure this out (see size of list above).\n";
    } 

    /*            does not assume list is sorted
        if you had a list of 1000 elements, and searchItem was 2nd element (index 1), two "key" or "item" comparisons are made
        if the search item is in the 900th spot, that is a lot more comparisons
        if the item is not on the list, this function has to check every element
        on average, it will take 1/2 the list size comparisons
        this algo does not assume the list is sorted...if it is sorted, you can help yourself out a lot
    */
}

// 3 ---------------------------------------------------------------------------------------------------------------------------
void selectionSort(int list[], int listLength) {
    /*
        for an unsorted list:
            1) find the location of the smallest element
            2) move the smallest element to the beginning of the unsorted list
        
        moves from list[0] ..... list[length -1] 
            then .... list [1] to list[length -1]    and list[2] ... list[length -1]

        for (index = 0; index < length - 1; index++) {
            a. what is location of smallest element in list[index] ... list[length -1] ?
            b. swap smallest elemnt with list[index]
        }

        so first time through loop, you look at list[0] ... to list[length -1]    locate the positon of th smallest element
        swap smallest element with list[0]....do the same until you reach the end, incrementing index along the way
    */
    std::cout << "\nwith 'selection sort' ";

    int index;
    int smallestIndex;
    int location;
    int temp;

    for (index = 0; index < listLength - 1; index++) {

        smallestIndex = index; // assume first element is smallest

        for (location = index + 1; location < listLength; location++) {
            if (list[location] < list[smallestIndex]) smallestIndex = location;  // current element is smaller, update index
        }
        // swaps list[smallestIndex] with list[index]
        temp = list[smallestIndex];          // put smallest value in temp
        list[smallestIndex] = list[index];   // hand value in list[i] to minimum idex
        list[index] = temp;                  // set list[i] value to minimum
    }

    printList(list, listLength);
}

// 4 ---------------------------------------------------------------------------------------------------------------------------
void bubbleSort(int list[], int listLength) {


    /*
        there are a fuck load of sorting algorithims
        selection sort is teribbly inefficent n^2
        assume list[0] ... list [n-1]  is a list of n elements indexed 0 to n-1
        you want to rearrange the elements in increasing order
        
        in a series of n-1 iterations, successive elements list[index] and list[index + 1] are compared
        if list[index] is > list[index + 1] , elements / values are swaped  ... smaller value goes to smaller index in this case

        list[0] .... list [n-1]
        list[0] .... list [n-2]
        ...

        ie { 10, 7, 19, 5, 16 }    there are 5 elements [0] to [4]

        // iteration 1   list[0] to list[5-1]
        10 v 7    {7, 10, 19, 5, 16}    // swap        list[0] was > list[1]
        10 v 19   {7, 10, 19, 5, 16}    // no swap     list[1] was < list[2]
        19 v 5    {7, 10, 5, 19, 16}    // swap        list[2] was > list[3]
        19 v 16   {7, 10, 5, 16, 19}    // swap        list[3] was > list[4]          largest element is in last position

        // iteration 2   list[0] to list[5-2]
        7  v 10   {7, 10, 5, 16, 19}    // no swap     list[0] was < list[1]
        10 v 5    {7, 5, 10, 16, 19}    // swap        list[1] was > list[2]
        10 v 16   {7, 5, 10, 16, 19}    // no swap     list[2] was < list[3]          largest elements in last 2 positions

        // iteration 3   list[0] to list[5-3]
        7  v 5    {5, 7, 10, 16, 19}     // swap       list[0] was > list[1]
        7  v 10   {5, 7, 10, 16, 19}     // no swap    list[1] was < list[2]

        // iteration 4   list[0] to list[5-4]
        5  v 7    {5, 7, 10, 16, 19}     // no swap    list[0] was < list[1]

        now you are at list[0] to list[0]     it is complete
    */

    std::cout << "\nwith 'bubble sort'... ";      // i like this one the best

    int temp;

    for (int iteration = 1; iteration < listLength; iteration++) {
        for (int index = 0; index < listLength - iteration; index++) {
            
            if (list[index] > list[index+1]) {
                temp = list[index];
                list[index] = list[index+1];
                list[index+1] = temp;
            }
        }
    }
    printList(list, listLength);
}

// 5 ---------------------------------------------------------------------------------------------------------------------------
void insertionSort(int list[], int listLength) {
 /*
    this should reduce the key comparisons
    it just moves each element into its proper place

    { 10 18 25 30 | 23 17 45 35 }     here are 8 elements, list[0] ... list[3] look sorted
    { 10 18 25 30 | 23 17 45 35 }   temp = 23          since list[4] < list [3], you have to move  list[4] to list[2]
    list[4] was copied into temp

    now you have to take list[3] to list[4]   and list[2] to list[3]
    { 10 18 xx xx | xx 17 45 35 }
    { 10 18 25 25 | 30 17 45 35 }    and just use temp to update list[2]
    { 10 18 23 25 30 | 17 45 35 }   list[0] ... list[4] is sorted, just have to do list[5] to list[7]
    repeat by moving first element in unsorted portion into the correct place of the sorted portion

    consider your "first out of order" index of the unsorted portion as 1....so list[0] is the only sorted portion 
    ...it is a list with 1 element and sorted by basic logic

    (n^2 + 3n - 4) / 4   key comparisons made
    [ n ( n - 1) ] / 2   item assigments       about half as much as bubble
 */
    std::cout << "\nwith 'insertion sort' ";

    int firstOutOfOrder;
    int location;
    int temp;

    for (firstOutOfOrder = 1; firstOutOfOrder < listLength; firstOutOfOrder++) {
        if (list[firstOutOfOrder] < list[firstOutOfOrder-1]) {
            temp = list[firstOutOfOrder];
            location = firstOutOfOrder;
            do {
                list[location] = list[location-1];
                location--;
            }
            while (location > 0 && list[location-1] > temp);
            list[location] = temp;
        }
    }
    printList(list, listLength);
}

// 6 ---------------------------------------------------------------------------------------------------------------------------
void binarySearch(const int list[], int size, int searchTerm) {
    /*
        you need to have a sorted list
        that way it will be faster
        it divides the list 
        first, the search item is compared with the middle element of the list

        if the search item is < middle element, focus on bottom half, but start at the middle
        if the search item is > middle eleemnt, focus on top half, but start at the middle

        don't worry about the middle being odd or even, the formaula will get you there eventually

        it's so much better than the sequential search if you can sort the list
        this technique just keeps cutting the list in half
        2 log2(n) +2  is all that is needed
    */

    std::cout << "Binary search to see if { " << searchTerm << " } is in the list...\n";

    int first = 0;
    int last = size-1;
    int mid;
    bool found = false;
    int location = 0;
    int comps = 0;

    while (first <= last && !found) {
        comps++;
        mid = (first + last) / 2;
        
        if (list[mid] == searchTerm) {
            location = mid;
            found = true;
        } 

        else if (list[mid] > searchTerm) last = mid - 1;
        else first = mid + 1;
    }

    if (found) {
        std::cout << "{ " << searchTerm << " } was found at least one time at index: [ " << location << " ]\n";
        std::cout << "It took < " << comps << " > key comparisons to figure this out.\n";
    } 
    else {
        std::cout << "this list does not have an element with the value of { " << searchTerm << " }\n";
        std::cout << "It took < " << comps << " > key comparisons to figure this out (see size of list above).\n";
    } 
}



//---------------------------------------------------------------------------------------------------------------------------