/*
    BUBBLE SORT can be done in n-1 iterations
    list[i] and list[i+1] are compared, if list[i] > list[i+1], swap
    largest to n-1, n-2, n-3, .....

    search is only concerned with comparisons, sort also cares about movements
    count avg of (n(n-1))/4 movements and (n(n-1))/2 comparisons

    SELECTION SORT 
    find location of smallest element
    move smallest element to beginning of unsorted list
    * can also be used to sort descending, ascending by putting largest to bottom, and many other variations
    works nice with linked lists too
    3(n-1) swaps are needed always O(n)
    (n(n-1))/2 comparisons  always O(n^2) ...not good
    use when data movement is expensive, but comparisons are not

    INSERTION SORT 
    tries to reduce comparisons...not necisarily moves
    divides list into a sorted and unsorted portion and works on it
    (n-1) comps, best case
    n(n-1)/2 comps, worst case
    .25n^2 + n comps, avg    ... also number of moves

    for the comparison-based sorts, use a graph called a comparison tree
    it is binary (only 2 outcomes)
    node is a comparison
    list[i] < list[k]   it is one branch, not is another
    top is root, any route to another node is a path, leaf final ordering
    must have n! leaves....any combo could be the solution
    BUBBLE, SELCTION, and INSERTION sort are O(n^2) , but you could theoretically do it in O(nlog2n) as min comps

    QUICK SORT is one of those lower-bound O(nlog2n) algorithms
    makes a lower and upper sub list, then combines   usually implemented by recursion
    pivot is element in list used to divide list into lower and uppper
    ideally, you want to pivot so both lists are about equal     go with recursion...it is a lot easier

    MERGE SORT always O(nlog2n)....no O(n^2) like quick sort
    also divides into 2 lists, also can be applied to linked list or array
    you do use same algorithim to take care of each sublist, but it keeps dividing the lists, then merges them
    also recursive
    * single element list is automatically sorted
    invented by von-nuemen, so it should be good
    merging is it's own unique operation            the second array is a lot of overhead

    if you are low on memory, use HEAP SORT...just a binary tree, by level
    
*/

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

const int g_FLOOR = 1'000'000;       // the lowest value an element can be in a list
const int g_CEILING = 9'999'999;     // the highest value an element can be in the list
const int g_LENGTH = 1'024;            // the length of test lists keep 2^m for simplicity
const int g_SEARCH_ITEM = 2;         // has to go through entire list...won't be there if not in range
int g_test_list [g_LENGTH];          // where the unsorted list is stored
int g_comps = 0;                     // track number of comparisons made by algorithim
int g_moves = 0;                     // track number of moves made by algorithim
std::string g_algorithims[5];       
double g_times[5];

void get_list(); // and reset comps и moves
void print_first_10();
void conclude(std::ofstream& outFile);

void bubble_sort(std::ofstream& outFile);
void selection_sort(std::ofstream& outFile);
void insertion_sort(std::ofstream& outFile);

void quick_sort(std::ofstream& outFile); // needs serveral functions to go recursivley (or use lambdas)
void quick_sort_main(int first, int last);
int quick_sort_partition(int first, int last);
void quick_sort_swap(int first, int second);

void merge_sort(std::ofstream& outFile); // also needs several funcitons
void merge_sort_main(int low, int high);
void merge(int low, int high, int mid);
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    std::ofstream outFile;
    outFile.open("results.txt");
    outFile << "There are [ " << g_LENGTH << " ] elements in the list, max = [ " << g_CEILING << " ] , min = [ " << g_FLOOR << " ]\n\n";

    bubble_sort(outFile);
    selection_sort(outFile);
    insertion_sort(outFile);
    quick_sort(outFile);
    merge_sort(outFile);
    conclude(outFile);

    outFile.close();
    std::cout << "\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
}

//--------------------------------------------------------------------------------------------------------------------------
void get_list()
{
    g_comps = 0;
    g_moves = 0;
    std::random_device rdevice{};                      
    std::default_random_engine num1{ rdevice() };
    std::uniform_int_distribution<int> randomNum1{g_FLOOR, g_CEILING}; 

    for (int i = 0; i < g_LENGTH; i++)
    {
        g_test_list[i] = randomNum1(num1);
    } // list is ready...taken by global

}

//--------------------------------------------------------------------------------------------------------------------------
void print_first_10()
{
    std::cout << "first 10 elements in list:\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << g_test_list[i] << std::endl;
    }
    std::cout << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------
void bubble_sort(std::ofstream& outFile)
{
    get_list(); // fresh list
    int temp = 0;
    std::string type = "BUBLE SORT";
    std::chrono::time_point<std::chrono::system_clock> start; // time the search
    start = std::chrono::system_clock::now();

    for (int iteration = 1; iteration < g_LENGTH; iteration++)
    {
        for (int index = 0; index < (g_LENGTH - iteration); index++)
        {
            g_comps++; // should be (n(n-1))/2 
            if ( g_test_list[index] > g_test_list[index + 1])
            {
                temp = g_test_list[index];
                g_test_list[index] = g_test_list[index + 1];
                g_test_list[index + 1] = temp;
                g_moves++;
            }
        }
    }

    std::chrono::time_point<std::chrono::system_clock> stop;
    stop = std::chrono::system_clock::now();
    std::chrono::duration<double>internalDuration = stop - start;
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);
    double duration = caster.count();

    outFile << type << ": " << duration << " ns   with [ " << g_comps << " ] comparisons and [ " << g_moves << " ] moves\n";
    outFile << "there should always be: " << (g_LENGTH * (g_LENGTH -1)) / 2 << " comparisons\n";
    outFile << "0 moves if sorted, " << (3 * g_LENGTH * (g_LENGTH - 1)) / 2 << " worst case, " << (g_LENGTH * (g_LENGTH - 1)) / 4 << " on avergage\n";
    std::cout << type << ": " << duration << " ns   with [ " << g_comps << " ] comparisons and [ " << g_moves << " ] moves\n";
    std::cout << "there should always be: " << (g_LENGTH * (g_LENGTH -1)) / 2 << " comparisons\n";
    std::cout << "0 moves if sorted, " << (3 * g_LENGTH * (g_LENGTH - 1)) / 2 << " worst case, " << (g_LENGTH * (g_LENGTH - 1)) / 4 << " on avergage\n";
    print_first_10();
    g_algorithims[0] = type;
    g_times[0] = duration;

}

//--------------------------------------------------------------------------------------------------------------------------
void selection_sort(std::ofstream& outFile)
{
    get_list(); // fresh list
    int smallest_i = 0;
    int iterator_i = 0;
    int temp = 0;

    std::string type = "SELECTION SORT";
    std::chrono::time_point<std::chrono::system_clock> start; // time the search
    start = std::chrono::system_clock::now();

    for (int index = 0; index < g_LENGTH - 1; index++)
    {
        smallest_i = index; // assume element at first index is the smallest in list
        for(iterator_i = index + 1; iterator_i < g_LENGTH; iterator_i++)
        {
            g_comps++;
            if (g_test_list[iterator_i] < g_test_list[smallest_i])
            {
                smallest_i = iterator_i; // update the index of the smallest eleement, if found
            }
        }
        // swap, always (for repeats, not a good idea to bypass)
        temp = g_test_list[smallest_i];
        g_moves++;
        g_test_list[smallest_i] = g_test_list[index];
        g_moves++;
        g_test_list[index] = temp;
        g_moves++;
    }

    std::chrono::time_point<std::chrono::system_clock> stop;
    stop = std::chrono::system_clock::now();
    std::chrono::duration<double>internalDuration = stop - start;
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);
    double duration = caster.count();

    outFile << std::endl << type << ": " << duration << " ns   with [ " << g_comps << " ] comparisons and [ " << g_moves << " ] moves\n";
    outFile << "there should always be: " << (g_LENGTH * (g_LENGTH -1)) / 2 << " comparisons\n";
    outFile << "moves should always be: " << (3 * (g_LENGTH - 1)) << "\n";
    
    std::cout << std::endl << type << ": " << duration << " ns   with [ " << g_comps << " ] comparisons and [ " << g_moves << " ] moves\n";
    std::cout << "there should always be: " << (g_LENGTH * (g_LENGTH -1)) / 2 << " comparisons\n";
    std::cout << "moves should always be: " << (3 * (g_LENGTH - 1)) << "\n";
    print_first_10();
    g_algorithims[1] = type;
    g_times[1] = duration;
}

//--------------------------------------------------------------------------------------------------------------------------
void insertion_sort(std::ofstream& outFile)
{
    get_list(); // fresh list
    int fooo = 0; // 'first out of order'
    int location = 0;
    int temp = 0;
    std::string type = "INSERTION SORT";
    std::chrono::time_point<std::chrono::system_clock> start; // time the search
    start = std::chrono::system_clock::now();

    for (fooo = 1; fooo < g_LENGTH; fooo++)
    {
        if(g_test_list[fooo] < g_test_list[fooo - 1])
        {
            g_comps++;
            temp = g_test_list[fooo];
            location = fooo;
            do
            {
                g_test_list[location] = g_test_list[location - 1];
                location--;
                g_moves++;
                g_comps++;
            }
            while (location > 0 && g_test_list[location - 1] > temp);
            g_test_list[location] = temp;
        }
    }
    std::chrono::time_point<std::chrono::system_clock> stop;
    stop = std::chrono::system_clock::now();
    std::chrono::duration<double>internalDuration = stop - start;
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);
    double duration = caster.count();

    outFile << std::endl << type << ": " << duration << " ns   with [ " << g_comps << " ] comparisons and [ " << g_moves << " ] moves\n";
    outFile << "min comps: " << g_LENGTH - 1 << " , avg comps: " << .25*(g_LENGTH * g_LENGTH) + g_LENGTH << " , max comps: " << .5 * (g_LENGTH * (g_LENGTH - 1)) << "\n";
    outFile << "avg moves: , " << (.25 * (g_LENGTH * g_LENGTH) + g_LENGTH) << "\n";
    
    std::cout << std::endl << type << ": " << duration << " ns   with [ " << g_comps << " ] comparisons and [ " << g_moves << " ] moves\n";
    std::cout << "min comps: " << g_LENGTH - 1 << " , avg comps: " << .25*(g_LENGTH * g_LENGTH) + g_LENGTH << " , max comps: " << .5 * (g_LENGTH * (g_LENGTH - 1)) << "\n";
    std::cout << "avg moves: , " << (.25 * (g_LENGTH * g_LENGTH) + g_LENGTH) << "\n";
    print_first_10();
    g_algorithims[2] = type;
    g_times[2] = duration;
}

//--------------------------------------------------------------------------------------------------------------------------
void quick_sort(std::ofstream& outFile)
{
    get_list(); // fresh list
    std::string type = "QUICK SORT";
    std::chrono::time_point<std::chrono::system_clock> start; // time the search
    start = std::chrono::system_clock::now();

    quick_sort_main(0, g_LENGTH - 1);

    std::chrono::time_point<std::chrono::system_clock> stop;
    stop = std::chrono::system_clock::now();
    std::chrono::duration<double>internalDuration = stop - start;
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);
    double duration = caster.count();

    outFile << std::endl << type << ": " << duration << " ns, [ " << g_comps << " ] comparisons, [ " << g_moves << " ] moves\n";
    outFile << "avg comps: " << 1.39 * g_LENGTH * std::log2(g_LENGTH) + g_LENGTH << "\n";
    outFile << "max comps: " << .5 * (g_LENGTH * (g_LENGTH - 1)) << "\n";
    outFile << "avg moves: " << .69 * g_LENGTH * std::log2(g_LENGTH) + g_LENGTH << "\n";
    outFile << "max moves: " << (g_LENGTH * g_LENGTH) / 2 + 1.5 * g_LENGTH - 2 << "\n";

    std::cout << std::endl << type << ": " << duration << " ns, [ " << g_comps << " ] comparisons, [ " << g_moves << " ] moves\n";
    std::cout << "avg comps: " << 1.39 * g_LENGTH * std::log2(g_LENGTH) + g_LENGTH << "\n";
    std::cout << "max comps: " << .5 * (g_LENGTH * (g_LENGTH - 1)) << "\n";
    std::cout << "avg moves: " << .69 * g_LENGTH * std::log2(g_LENGTH) + g_LENGTH << "\n";
    std::cout << "max swaps: " << (g_LENGTH * g_LENGTH) / 2 + 1.5 * g_LENGTH - 2 << "\n";
    print_first_10();
    g_algorithims[3] = type;
    g_times[3] = duration;
}

//--------------------------------------------------------------------------------------------------------------------------
void quick_sort_main(int first, int last)
{
    if ( first < last)
    {
        int pivot_location = quick_sort_partition(first, last);
        quick_sort_main(first, pivot_location - 1);
        quick_sort_main(pivot_location + 1, last);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
int quick_sort_partition(int first, int last) // if first = 0 and last = length -1 , entire list is partitioned
{
    quick_sort_swap(first, (first + last)/2);

    int pivot = g_test_list[first];
    int index_current = 0;
    int index_small = first;

    for (index_current = first + 1; index_current <= last; index_current++)
    {
        g_comps++;
        if(g_test_list[index_current] < pivot)
        {
            index_small++;
            quick_sort_swap(index_small, index_current);
        }
    }
    quick_sort_swap(first, index_small);
    return index_small;
}

//--------------------------------------------------------------------------------------------------------------------------
void quick_sort_swap(int first, int second)
{
    int temp = g_test_list[first];
    g_test_list[first] = g_test_list[second];
    g_test_list[second] = temp;
    g_moves = g_moves + 3;
}

//--------------------------------------------------------------------------------------------------------------------------
void merge_sort(std::ofstream& outFile)
{
    get_list(); // fresh list
    std::string type = "MERGE SORT";
    std::chrono::time_point<std::chrono::system_clock> start; // time the search
    start = std::chrono::system_clock::now();

    merge_sort_main(0, g_LENGTH - 1);

    std::chrono::time_point<std::chrono::system_clock> stop;
    stop = std::chrono::system_clock::now();
    std::chrono::duration<double>internalDuration = stop - start;
    std::chrono::duration<double, std::ratio<1, 1000000000> > caster = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(internalDuration);
    double duration = caster.count();

    outFile << std::endl << type << ": " << duration << " ns, [ " << g_comps << " ] comparisons, [ " << g_moves << " ] moves\n";
    outFile << "avg and max comps: " << g_LENGTH * std::log2(g_LENGTH) << "\n";
    outFile << "avg and max moves: " << g_LENGTH * std::log2(g_LENGTH) << "\n";

    std::cout << std::endl << type << ": " << duration << " ns, [ " << g_comps << " ] comparisons, [ " << g_moves << " ] moves\n";
    std::cout << "avg and max comps: " << g_LENGTH * std::log2(g_LENGTH) << "\n";
    std::cout << "avg and max moves: " << g_LENGTH * std::log2(g_LENGTH) << "\n";
    print_first_10();
    g_algorithims[4] = type;
    g_times[4] = duration;
}

//--------------------------------------------------------------------------------------------------------------------------
void merge_sort_main(int low, int high)
{ 
    g_comps++;
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort_main(low, mid);
        merge_sort_main(mid + 1, high);
        merge(low, high, mid);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void merge(int low, int high, int mid) // good process to use
{
    int i = low;
    int k = low;
    int j = mid + 1;
    int copy[g_LENGTH];

    while(i <= mid && j <= high) // handle the actual merging with an if statement
    {
        g_comps++;
        if(g_test_list[i] < g_test_list[j])
        {
            copy[k] = g_test_list[i];
            k++;
            i++;
            g_moves++;
        }
        else
        {
            copy[k] = g_test_list[j];
            k++;
            j++;
            g_moves++;
        }
    }

    while(i <= mid) // complete copy for lower list
    {
        copy[k] = g_test_list[i];
        k++;
        i++;
        g_moves++;
    }

    while(j <= high) // complete copy for upper list
    {
        copy[k] = g_test_list[j];
        k++;
        j++;
        g_moves++;
    }
    
    for (i = low; i < k; i++) // assign copy to actual array
    {
        g_test_list[i] = copy[i];
        g_moves++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void conclude(std::ofstream& outFile)
{
    outFile << std::endl << std::endl;

    double temp_d = 0;
    std::string temp_s = "";
    
    for (int iteration = 1; iteration < 5; iteration++)
    {
        for (int index = 0; index < (5 - iteration); index++)
        {
            if ( g_times[index] > g_times[index + 1])
            {
                temp_d = g_times[index];
                g_times[index] = g_times[index + 1];
                g_times[index + 1] = temp_d;

                temp_s = g_algorithims[index];
                g_algorithims[index] = g_algorithims[index + 1];
                g_algorithims[index + 1] = temp_s;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        outFile << std::fixed << std::showpoint << std::setprecision(1);
        outFile << std::left << std::setw(15) << g_algorithims[i] << " :  " << g_times[i] << "  ns\n";
    }
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================ 
//---------------------------------------------------------------------------------------------------------------------------- 