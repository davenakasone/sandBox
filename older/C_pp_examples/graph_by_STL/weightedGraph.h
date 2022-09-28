/*
    input files also need a wieght matrix ...let base take the vertex list, then start weight matrix on "MATRIX"
    inherit if you need to, but not necessary here
    probably would be better to use vectors instead of lists on the vertex list
    it's very important to:
    - make node going to self = 0   (should have a diagonal of 0's)
    - indicate no neighbor connection with -1  (should reflect accross diagonal)
    - come back and make -1 = DBL_MAX to indicate infinity

    create the obj, nothing happens until createWeightedGraph() is called
    * adjust if you have vertex(s) going back to themselsves with weight
    * does not work with negative weight
    https://www.youtube.com/watch?v=XB4MIexjvY0

*/
 
#ifndef H_weightedGraph
#define H_weightedGraph

#include <cfloat>     // weights could be decimal  and named const 'DBL_MAX' will represent infinity (no edge)
#include <climits>    // has INT_MAX
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>   // for std::advance(iter, n)
#include <list>       // for graph's vertex list
#include <string>     // input file
#include <queue>      // algorithim use
#include <vector>     // for small and weight matrix
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


class weightedGraphType  
{
    public:
        int getSize() const;         // gSize = 0, graph is empty, >0 is number of vertex(s)
        void createWeightedGraph(std::string fileName = "");  // needs vertex list and weight matrix
        void clearGraph();            // memory occupied by each vertex is deallocated
        void printGraph();            // quick print
        void depthFirstTraversal();   // depth first traversal of entire graph ...prints
        void dftAtVertex(int vertex); // depth first traversal of the graph at a node specified 
        void breadthFirstTraversal(); // breadth first traversal of the entire graph ...prints 
        void shortestPath(int vertex); // determines weight of shortest path from source to all other vertecies
        //void printShortestDistance(int vertex); // prints results
        weightedGraphType(); // constructor
        ~weightedGraphType(); // destructor

    protected:
        
        int gSize;                                    // current number of vertices
        std::list<std::list<int>*> graph;             // list of list pointers
        std::list<std::list<int>*>::iterator git;     // iterator for graph
        std::list<int> * sub;                         // pointer to current sub list
        std::list<int>::iterator subit;               // iterator for sub list

    private:
        void dft(int v, bool visited[]); // helper for depthFirstTraversal and dftAtVertex ... prints
        std::list<int> dftSeq;           // just to print
        std::list<int> dftH;             // helper-holder
        std::list<int>::iterator dftHit;              // iterator for helper-holder
        const std::string inputFile = "input6.txt";   // TEST  change input file  here, remove when done
        std::string seperator = "";                   // check vertex list and weight matrix seperation
        std::vector<std::vector<double>> weights;     // holds the weight matrix 
        std::vector<double> smalls;                   // holds min path  
};


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------
int weightedGraphType::getSize() const // GOOD
{
    return (gSize);   // gSize = 0 means empty
}

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::createWeightedGraph(std::string fileName) // GOOD
{
    if (gSize != 0)	// if the graph is not empty, make it empty
    {
        clearGraph();
    }

    std::ifstream inFile;
    fileName = inputFile; // TESTING ONLY
    /*
    if ( fileName != inputFile)      include for final version...avoiding this just speeds up testing
    { 
        std::cout << "\nEnter input file name: ";
        std::cin >> fileName;
        std::cout << std::endl;   
    }
    */
    inFile.open(fileName);
    
    if (!inFile)
    {
        std::cout << "can't open input file\n";
        return;
    }

    int vertex;
    int adjacent;
    git = graph.begin();
    inFile >> gSize;  // get the number of vertices   should be first item

    for (int index = 0; index < gSize; index++)
    {
        inFile >> vertex;
        sub = new std::list<int>;
        subit = sub->begin();
        sub->push_back(vertex);
        inFile >> adjacent; // could be more than 1, but must be at least one

        while (adjacent != -999)
        {
            sub->push_back(adjacent);
            inFile >> adjacent;
        } 
        graph.push_back(sub);
    }
    
    inFile >> seperator; // get weight matrix
    if (seperator != "MATRIX")
    {
        std::cout << "the file is not formated correctly\n";
        return;
    }
    smalls.resize(gSize);
    weights.resize(gSize);
    for (int i = 0; i < gSize; i++)
    {
        weights[i].resize(gSize);
    }
    for (int i = 0; i < gSize; i++)
    {
        for (int j = 0; j < gSize; j++)
        {
            if (!inFile)
            {
                std::cout << "the matrix is incorrect\n";
                return;
            }
            inFile >> weights[i][j];
        }
    }
    inFile.close();
} 

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::clearGraph() // GOOD
{
    git = graph.begin(); // clear vertex list
    for (int i = 0; i < gSize; i++)
    {
        sub = *git;
        delete sub;
        git++;
    }
    graph.clear();

    for (int i = 0; i < gSize; i++)   // clear weight matrix  and smallest weight matrix
    {
        weights[i].clear();
        weights[i].resize(0);
    }
    weights.clear();
    weights.resize(0);
    smalls.clear();
    smalls.resize(0);
    std::cout << "graph was cleared\n";
    gSize = 0; // this reset indicates graph is empty
} 

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::printGraph() // GOOD
{
    if (gSize == 0)
    {
        std::cout << "\n    .... the graph is empty\n";
    }
    else
    {
        git = graph.begin();
        std::cout << "\n-------------------------------- GRAPH\n";
        for (int i = 0; i < gSize; i++)
        {
            sub = *git;
            subit = sub->begin();
            std::cout << *subit << "  ";
            if (sub->size() > 1)
            {
                for (int j = 1; j < sub->size(); j++)
                {
                    subit++;
                    std::cout << *subit << "  ";
                }
            }
        std::cout << std::endl;
        git++;
        }
        std::cout << "-------------------------------- weight matrix\n";

        for (int i = 0; i < gSize; i++)
        {
            for (int j = 0; j < gSize; j++)
            {
                std::cout << std::right << std::setw(4) << weights[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------------------\n";
    } 
} 

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::depthFirstTraversal() // entire graph ... n vertecies  0 to n-1    GOOD
{
    if (gSize == 0)
    {
        std::cout << "\n cant DFS/DFT an empty list..\n";
        return;
    }
    dftSeq.clear(); // start fresh
    bool *visited;              // bool array tracks each visited vertex
    visited = new bool[gSize];  // array for vertex: 0, 1, ... , n-1   of size n

    for (int index = 0; index < gSize; index++) 
    {
        visited[index] = false; // initialize to false
    }
        
    for (int index = 0; index < gSize; index++)	// for each vertex that is not visited, do a depth-first traverssal
    {
        if (!visited[index]) 
        {
            dft(index,visited);
        }      
    }
    std::cout << "\n from vertex 0, DFT/DFS : {  ";
    std::list<int>::iterator tem;
    tem = dftSeq.begin();
    for (int i = 0; i < gSize; i++)
    {
        std::cout << *tem << "  ";
        tem++;
    }
    std::cout << "}\n";
    delete [] visited;
    dftSeq.clear();
} 

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::dft(int v, bool visited[]) // works entire graph from vertex given ...modulus wrap GOOD
{

    if (!visited[v])
    {
        dftSeq.push_back(v); // for printing 
    }
    visited[v] = true;
    git = graph.begin();
    std::advance(git, v); // put on proper index to get proper sub list
    std::list<int> temp;
    temp = *(*git);
    std::list<int>::iterator tempit;
    if (temp.size() > 1)
    {
        tempit = temp.begin();
        for (int j = 0; j < temp.size(); j++)
        {
            int w = *tempit;
            if (!visited[w])
            {
                dft(w, visited);
            }
            tempit++;
        }
    }
} 

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::dftAtVertex(int vertex) // from a node     going to take from vertex, modular wrap GOOD
{
    if (gSize == 0)
    {
        std::cout << "\n cant DFS/DFT an empty list..\n";
        return;
    }
    if (vertex < 0 || vertex > gSize - 1)
    {
        std::cout << "\n vertex not in range\n";
        return;
    }
    
    dftSeq.clear(); // start fresh
    bool *visited;
    visited = new bool[gSize];

    for (int index = 0; index < gSize; index++)
    {
        visited[index] = false; // initialize
    }


    std::list<int> tracker;            // this will hold the modular wrap...ie start at vert = 6, gSize = 10
    std::list<int>::iterator trit;            // tracker is { 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 }
    for(int i = vertex; i < gSize; i++)
    {
        tracker.push_back(i);
    }
    for (int i = 0; i < vertex; i++)
    {
        tracker.push_back(i);
    }
    trit = tracker.begin();
    for (int i = 0; i < gSize; i++)   // instead of starting at index 0, go off the seq in 'tracker'
    {
        int v = *trit;                 // appears to work if modulated
        if (!visited[v])
        {
            dft(v, visited);
        }
        trit++;
    }

    std::cout << "\n from vertex " << vertex << ", DFT/DFS : {  ";
    std::list<int>::iterator tem;
    tem = dftSeq.begin();
    for (int i = 0; i < gSize; i++)
    {
        std::cout << *tem << "  ";
        tem++;
    }
    std::cout << "}\n";
    delete [] visited;
    dftSeq.clear();
} 

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::breadthFirstTraversal() // entire graph, like level by level on binary tree   GOOD  
{
    if (gSize == 0)        // probably can work in a vertex and modulate this also
    {
        std::cout << "\n  the graph is empty...no BFT/BFS possible\n";
        return;
    }

    std::queue<int> vQ; // vertex queue
    std::list<int> *temp; // temporarily hold the sub list
    std::list<int> seq; // holds sequence for printing

    bool *visited;
    visited = new bool[gSize]; // bool array to track visits
    for (int ind = 0; ind < gSize; ind++)
    {
        visited[ind] = false; // initialize false
    }

    for (int index = 0; index < gSize; index++)
    {
        if (!visited[index])
        {
            vQ.push(index);
            visited[index] = true;
            seq.push_back(index);

            while (vQ.size() > 0)
            {
                int u = vQ.front();
                vQ.pop();
                git = graph.begin();
                std::advance(git, u); // put on proper index to get proper sub list
                temp = *git;
                subit = temp->begin();

                for (int j = 0; j < temp->size(); j++)
                {
                    int w = *subit;
                    if (!visited[w])
                    {
                        vQ.push(w);
                        visited[w] = true;
                        seq.push_back(w);
                    }
                    subit++;
                }
            } 
        }
    }	
    std::list<int>::iterator tempit;
    tempit = seq.begin();
    std::cout << "\nBFT/BFS: {  ";
    for (int i = 0; i < gSize; i++)
    {
        std::cout << *tempit << "  ";
        tempit++;
    }
    std::cout << "}\n";
    delete [] visited;
} 

//----------------------------------------------------------------------------------------------------------------------------
weightedGraphType::weightedGraphType() // GOOD
{
    gSize = 0;
}

//----------------------------------------------------------------------------------------------------------------------------
weightedGraphType::~weightedGraphType() // GOOD
{
    clearGraph(); // use helper
}

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphType::shortestPath(int vertex) // any vertex provided, even handles islands
{
    if (gSize == 0)
    {
        std::cout << "this graph is empty\n";
        return;
    }
    if (vertex < 0 || vertex > gSize -1)
    {
        std::cout << "vertex not in range\n";
        return;      
    }

    for (int i = 0; i < gSize; i++)
    {
        for (int j = 0; j < gSize; j++)
        {
            if (weights[i][j] < 0)
            {
                weights[i][j] = DBL_MAX; // put in "infinity" for those -1's
            }
        }
    }

    bool *visited;
    visited = new bool [gSize];
    for (int i = 0; i < gSize; i++) // initialize
    {
        smalls[i] = weights[vertex][i];
        visited[i] = false;
    }
    smalls[vertex] = 0; // from self, weight is 0
    visited[vertex] = true; // start from self
    int v;
    double minW;

    for (int i = 0; i < gSize - 1; i++) // don't have to iterate all, you already did one.. gSize - 1 is good
    {
        minW = DBL_MAX; // assume minimum is infinity
        for (int j = 0; j < gSize; j++) // finds vertex and weight of "closest"  not yet visited and < min
        {
            if (!visited[j])
            {
                if (smalls[j] < minW)
                {
                    v = j;
                    minW = smalls[v]; // update
                }
            }
        }
        visited[v] = true;
        for (int k = 0; k < gSize; k++) // see if any other shorter paths to min vertex
        {
            if (minW + weights[v][k] < smalls[k]) // edge exists and less than current weight
            {
                smalls[k] = minW + weights[v][k];
            }
        }
    }
    std::cout << "\n\nmin weights from vertex " << vertex << " to:\n";
    for (int i = 0; i < gSize; i++)
    {
        std::cout << "     vertex " << i << " :  " << std::left << smalls[i] << std::endl;
    }
    delete [] visited;
}


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif  // end weightedGraph.h
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


