/*
    .... (3,4) eqv to (4,3)    should see min weight = 71
        and taking diagonals to -1 (infinity) instead of 0 makes it easier and shows loops are not allowed
    this algo is very greedy, so make sure there aren't too many negatives and everything is connected
    made pretty general, should handle unbalanced graph also

    > improved to start from any vertex, just modulate sequence from input...always get same min
*/

#include <cfloat> // DBL_MAX
#include <climits> // INT_MAX
#include <iomanip>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

std::string INPf = "input1.txt";              // adjust for input file
std::string DIS = "";                        // pausing and clearing
const double infinity = DBL_MAX;             // for no link or connection to self (diagonals)
int SIZE = -9;                               // first variable read, 'number of vertecies in graph'
std::vector<std::vector<int>> GRAPH;         // holds vertex list
std::vector<std::vector<double>> WEIGHTS;    // holds costs for each edge pair 

void getInput();
void testPrint();
void next();
void prim(int source);   // should be able to get it from any node
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    getInput();
    testPrint();
    next();
    prim(2); // change parameter to change vertex where tree spans from 'rooted'
    std::cout << "\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0; 
}

//--------------------------------------------------------------------------------------------------------------------------
void getInput()
{
    int temp;
    std::ifstream inFile;
    inFile.open(INPf);
    inFile >> SIZE;
    GRAPH.resize(SIZE);
    WEIGHTS.resize(SIZE);
    for (int i = 0; i < SIZE; i++) // fill up graph's vertex list
    {
        inFile >> temp;
        while (temp != -999)
        {
            GRAPH[i].push_back(temp);
            inFile >> temp;
        }
    }
    inFile >> DIS; // catch 'MATRIX'
    for (int i = 0; i < SIZE; i++) // fill up weight matrix
    {
        WEIGHTS[i].resize(SIZE);
        for (int j = 0; j < SIZE; j++)
        {
            inFile >> WEIGHTS[i][j];
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
void testPrint()
{
    std::cout << "\n------------------------------ Graph:\n";
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << "vertex " << GRAPH[i][0] << " : ";
        for (int j = 1; j < GRAPH[i].size(); j++)
        {
            std::cout << GRAPH[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------ Weights:\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ( i == j)
            {
                std::cout << std::right << std::setw(4) << "-";
            }
            else if (WEIGHTS[i][j] < 0)
            {
                std::cout << std::right << std::setw(4) << "x"; 
            }
            else
            {
                std::cout << std::right << std::setw(4) << WEIGHTS[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------\n";
}

//--------------------------------------------------------------------------------------------------------------------------
void next()
{
    std::cout << "\n                  any key to proceed: ";
    std::cin >> DIS;
    std::cout.flush();
    system("clear");
    std::cout << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------
void prim(int source)
{
    std::vector<std::vector<int>> tree; // to hold node pairs...remember you only need n-1 iterations
    tree.resize(2);
    tree[0].resize(SIZE-1);
    tree[1].resize(SIZE-1); // now a 2 x n-1 array is ready to use

    std::vector<int> visited; // -1 means it was visited
    visited.resize(SIZE);
    int u = -9; // start vertex
    int v = -9; // end vertex
    double minW = infinity; // for comparisons

    for (int i = 0; i < SIZE; i++) // symbolize infinity
    {
        visited[i] = INT_MAX; // initialize > 0 'not yet visited'
        if (i < SIZE - 1) // fill in tree while you are at it
        {
            tree[0][i] = INT_MAX;
            tree[1][i] = INT_MAX;
        }
        for (int j = 0; j < SIZE; j++)
        {
            if (WEIGHTS[i][j] < 0)
            {
                WEIGHTS[i][j] = infinity; // any edges to self or absence of edges is infinity
            }
        }
    }
    // MODULATION
    std::list<int> modulator;
    std::list<int>::iterator modit;
    for (int i = source; i < SIZE; i++) // modulate from desired source vertex
    {
        modulator.push_back(i);
    }
    for(int i = 0; i < source; i++)
    {
        modulator.push_back(i);
    }
    modit = modulator.begin();
    std::vector<int> mod(SIZE);
    
    std::cout << "\nmodulator set {  "; // TEST
    for(int i = 0; i < SIZE; i++)            // put it in the vector
    {
        mod[i] = *modit;
        modit++;
        std::cout << mod[i] << "  "; //TEST
    }
    std::cout << "}\n"; // TEST
    std::vector<std::vector<double>> weightsM; // holds weight matrix in modulation order
    weightsM.resize(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        weightsM[i].resize(SIZE);
        for (int j = 0; j < SIZE; j++)
        {
            weightsM[i][j] = WEIGHTS[mod[i]][mod[j]]; // transfer weights
            //TEST
            if (weightsM[i][j] == infinity)
            {
                std::cout << std::right << std::setw(4) << "x"; 
            }
            else
            {
                std::cout << std::right << std::setw(4) << weightsM[i][j]; 
            }
        }
        std::cout << std::endl; // TEST
    }
    // MODULATION


    for (int i = 0; i < SIZE; i++) // initialize from given root (starting vertex)
    {
                                                    // TEST
                                                    std::cout << "\ni = " << i;
        if (weightsM[0][i] < minW)  // if there is a connection from desired start to another vertex...
        {
            minW = weightsM[0][i];  // udpate
            u = source; // mod[0]
            v = mod[i];
                                                    // TEST
                                                    std::cout << "   min edge update ( " << u << " , " << v << " ) = " << minW;
                                                    // TEST
        }
    }
    tree[0][0] = u; // you have your first min vertex pair (edge)
    tree[1][0] = v;
    visited[u] = -1;
    visited[v] = -1;
                                                    // TEST
                                                    std::cout << "\n      recorded visit:   { ";
                                                    for (int i = 0; i < SIZE; i++)
                                                    {
                                                        std::cout << visited[i] << "  ";
                                                    }
                                                    std::cout << "}" << "  , edge ( " << tree[0][0] << " , " << tree[1][0] << " )\n";
                                                    // TEST

    for (int i = 0; i < SIZE; i++) // just have to fill in matrix for main loop
    {
        if (visited[i] >= 0) // not visited 
        {
            if (WEIGHTS[i][mod[0]] < WEIGHTS[i][mod[i]]) // this lets you handle = weights and default to previous source
            {
                visited[i] = u;
            }
            else
            {
                visited[i] = v;
            } // modulation is now complete and algorithm can begin as usual
        }
    }
                                                            // TEST
                                                            std::cout << "       found nearest:   { ";
                                                            for (int i = 0; i < SIZE; i++)
                                                            {
                                                                std::cout << visited[i] << "  ";
                                                            }
                                                            std::cout << "}\n";
                                                            std::cout << "            tree has : ";
                                                            for (int i = 0; i < SIZE - 1; i++)
                                                            {
                                                                if (tree[0][i] < INT_MAX && tree[1][i] < INT_MAX)
                                                                {
                                                                    std::cout << " ( " << tree[0][i] << " , " << tree [1][i] << " )  ";
                                                                }
                                                            }
                                                            std::cout << "\n\n>>> start main loop...\n"; 
                                                            // TEST
    int setter = -9; // for transfer
    for (int i = 1; i < SIZE-1; i++)  // you already have one edge, now start sequence...only need n-1 edges
    {
                                                            std::cout << "\ni = " << i;    // TEST
        minW = infinity; // assume it is maxed
        for (int j = 0; j < SIZE; j++)
        {
                                                            std::cout << "\n     j = " << j; // TEST
            if (visited[j] >= 0 && WEIGHTS[j][visited[j]] < minW) // not visited and smaller weight found ..finding min edge in current set
            {
                setter = j;
                minW = WEIGHTS[j][visited[j]];
                                                            // TEST
                                                            std::cout << "  ... update   ( " << j << " , " << visited[j] << " ) , min = " << minW;
            }
        }
        tree[0][i] = setter; // input start vertex
        tree[1][i] = visited[setter]; // input end vertex
        visited[setter] = -1; // mark as visited
                                                            // TEST
                                                            std::cout << "\n              *  vertecies now {  ";
                                                            for (int i = 0; i < SIZE; i++)
                                                            {
                                                                std::cout << visited[i] << "  ";
                                                            }
                                                            std::cout << " }\n              *  the tree has recorded: ";
                                                            for (int i = 0; i < SIZE - 1; i++)
                                                            {
                                                                if (tree[0][i] < INT_MAX && tree[1][i] < INT_MAX)
                                                                {
                                                                    std::cout << " ( " << tree[0][i] << " , " << tree [1][i] << " )  ";
                                                                }
                                                            }
        for (int k = 0; k < SIZE; k++)
        {
                                                            std::cout << "\n                       k = " << k; // TEST
            if (visited[k] >= 0 && WEIGHTS[k][setter] < WEIGHTS[k][visited[k]])
            {
                visited[k] = setter;
                                                                                    // TEST
                                                                                    std::cout << "    ... update: {  ";
                                                                                    for (int i = 0; i < SIZE; i++)
                                                                                    {
                                                                                        std::cout << visited[i] << "  ";
                                                                                    }
                                                                                    std::cout << "}  min edge found at ( " << k << " , " << setter << " )";
            }
        }
    }

    // PRINT RESULTS
    double total = 0;
    double temp = 0;
    std::cout << "\n\nthe minimal spanning binary tree from vertex [ " << source << " ]\n";
    for (int i = 0; i < SIZE - 1; i++)
    {
        temp = WEIGHTS[tree[0][i]][tree[1][i]]; // get weight of edge
        std::cout << " ( " << tree[0][i] << " , " << tree[1][i] << " )  , weight : " << temp << std::endl;
        total = total + temp; // keep a running total
    }
    std::cout << "       the minimum wieght/cost is :  " << total << std::endl;

}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================