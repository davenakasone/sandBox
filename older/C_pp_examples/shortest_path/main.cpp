/*
    common implementation of shortest path...be careful for negative weights
    input a vertex list and a weight matrix
    no modulation needed

    just have to figure out how to trace the predecessor
*/

#include <climits> // has INT_MAX
#include <cfloat>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

const std::string INP = "input4.txt"; // adjust for input file used
const double infinity = DBL_MAX;
std::string DIS = ""; // for pause->clear
std::vector<std::vector<int>> graph; // vertex list
std::vector<std::vector<double>> weights; // weight matrix
std::vector<double> smalls; // holds smallest weights (row in weights initially)
std::vector<bool> visited; // if the node was visited, = true
int SIZE; // vertecies in the graph

void next();
void getInput(); // takes input from input.txt for vertex list and weight matrix ...also initializes globals
void testPrint(); // prints vertex list and weight matrix
void dijkstra(int startV);
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
int main() 
{
    getInput();
    testPrint();
    next();
    dijkstra(0);
    next();
    dijkstra(9);


    std::cout << "\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0; 
}

//----------------------------------------------------------------------------------------------------------------------------
void next()
{
    std::cout << "\n          any key to continue: ";
    std::cin >> DIS;
    std::cout.flush();
    system("clear");
}

//----------------------------------------------------------------------------------------------------------------------------
void getInput() // takes input from input.txt for vertex list and weight matrix
{
    std::fstream inFile;
    inFile.open(INP); // change as needed
    inFile >> SIZE;
    int holder;

    graph.resize(SIZE); // initialize globals based on SIZE (first integer in input file is number or vertecies)
    weights.resize(SIZE);
    smalls.resize(SIZE);
    visited.resize(SIZE);
    
    for (int i = 0; i < SIZE; i++) // fill vertex list
    {
        inFile >> holder;
        while(holder != -999)
        {
            graph[i].push_back(holder);
            inFile >> holder;
        }
    }

    for (int i = 0; i < SIZE; i++) // fill weight matrix, initialize visited (bool)
    {
        visited[i] = false;
        weights[i].resize(SIZE);
        for (int j = 0; j < SIZE; j++)
        {
            inFile >> weights[i][j];
        }
    }
    inFile.close();
}

//----------------------------------------------------------------------------------------------------------------------------
void testPrint()
{
    std::cout << "\n-------------------------------- Graph / Vertex List:\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            std::cout << graph[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------------- Weight Matrix:\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << std::right << std::setw(4) << weights[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------\n";

}

//----------------------------------------------------------------------------------------------------------------------------
void dijkstra(int startV)
{
    if (startV < 0 || startV > SIZE - 1) // see if vertex provided is valid
    {
        std::cout << "vertex not in range\n";
        return;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (weights[i][j] < 0)
            {
                weights[i][j] = infinity; // insert max for infinity
            }
        }
    }
    std::vector<std::vector<int>> seqD(SIZE); // holds the sequence from source -> other node   'predecessor'
    for (int i = 0; i < SIZE; i++) // load min weight and visited matrix
    {
        smalls[i] = weights[startV][i];
        visited[i] = false;
        seqD[i].resize(SIZE); // all predocessors should come from source vertex
        for (int j = 0; j < SIZE; j++)
        {
            seqD[i][j] = startV;
        }
    }
    smalls[startV] = 0; // initialize for starting vertex
    visited[startV] = true; // initialize for starting vertex
    double minW = infinity; // assumes infinity is smallest
    int v = 0;
    int seq;
    for (int i = 0; i < SIZE - 1; i++) //  SIZE - 1 ...because it is forward iterated
    {
        seq = 0;
        seqD[i][seq] = i;
        minW = infinity; // assumes infinity is smallest
                                                                // TEST
                                                                if (minW == infinity)
                                                                {
                                                                    std::cout << "\ni = " << i << " , v = " << v << " , minW = x   , ";
                                                                }
                                                                else
                                                                {
                                                                    std::cout << "\ni = " << i << " , v = " << v << " , minW = " << minW << "  ,  ";
                                                                }
                                                                
                                                                std::cout << "visited : {  ";
                                                                for (int x = 0; x < SIZE; x++)
                                                                {
                                                                    if (visited[x] == true)
                                                                    {
                                                                        std::cout <<  "T  ";
                                                                    }
                                                                    else
                                                                    {
                                                                        std::cout << "F  ";
                                                                    }
                                                                    
                                                                }
                                                                std::cout << "}     ";
                                                                std::cout << "smalls : {  ";
                                                                for (int x = 0; x < SIZE; x++)
                                                                {
                                                                    if (smalls[x] == infinity)
                                                                    {
                                                                        std::cout << "x  ";
                                                                    }
                                                                    else
                                                                    {
                                                                        std::cout << smalls[x] << "  ";
                                                                    }
                                                                }
                                                                std::cout << "}";
                                                                // TEST
        for (int j = 0; j < SIZE; j++) // find vertex index of smallest node not yet visited
        {
                                                                // TEST
                                                                std::cout << "\n      j = " << j << ",  ";
            if (!visited[j])
            {
                if (smalls[j] < minW)
                {
                    v = j; // take vertex index
                    minW = smalls[v]; // update new min
                                                                // TEST
                                                                std::cout << "   UPDATE, v = " << v << "  , minW = " << minW;
                }
            }
        }
        visited[v] = true; // mark min vertex as visited
                                                                // TEST
                                                                std::cout << "\n          update visited: {  ";
                                                                for (int x = 0; x < SIZE; x++)
                                                                {
                                                                    if (visited[x] == true)
                                                                    {
                                                                        std::cout <<  "T  ";
                                                                    }
                                                                    else
                                                                    {
                                                                        std::cout << "F  ";
                                                                    }
                                                                }
                                                                std::cout << "}";
                                                                //TEST
        for (int k = 0; k < SIZE; k++) // check
        {
                                                                //TEST 
                                                                std::cout << "\n            k = " << k;
            if (!visited[k]) // not visited
            {
                if (minW + weights[v][k] < smalls[k]) // edge exists ....and is less than current weight
                {
                    smalls[k] = minW + weights[v][k];
                                                                //TEST
                                                                std::cout << "  !visit, minW + weights[v][k] < smalls[k] , UPDATE smalls:  {  ";
                                                                for (int x = 0; x < SIZE; x++)
                                                                {
                                                                    if (smalls[x] == infinity)
                                                                    {
                                                                        std::cout << "x  ";
                                                                    }
                                                                    else
                                                                    {
                                                                        std::cout << smalls[x] << "  ";
                                                                    }
                                                                }
                                                                std::cout << "}";
                    seqD[i][seq] = k;
                    seq++;
                }
            }
        }
        std::cout << std::endl << std::endl;//TEST
    }// print results
    std::cout << "\n   from node " << startV << " , min distances/weights/costs are:\n";
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << startV << "  to  " << std::left << std::setw(3) << i << "  :  " << std::left << std::setw(5) << smalls[i] << " ";
        for (int j = 0; j < SIZE; j++)
        {
            if (seqD[i][j] != startV)
            {
                std::cout  << "-> " << std::left << std::setw(5) << seqD[i][j];
            }
        }
        std::cout << std::endl;
    }
}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================