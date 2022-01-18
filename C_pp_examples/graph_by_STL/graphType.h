/*
    good for directed, undirected, and inheriting          dont trust dfs from vertex


    this will index vertecies 0, 1, ..., n-1

    assume data comes in from a file:
    5                          // first line is vertecies
    0 2 4 ... -999             // end with -999
    1 3 6 8 ... -999
    ..

    and make graph

    having a gSize x gSize matrix would be a lot easier...put one in
*/
 
#ifndef H_graph
#define H_graph
  
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator> // for std::advance(iter, n)
#include <list>
#include <string>
#include <queue>
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


class graphType  
{
    public:
        bool isEmpty() const;         // determine whether the graph is empty
        void createGraph(std::string fileName = "");  // graph is created using the adjacency list representation
        void clearGraph();            // memory occupied by each vertex is deallocated
        void printGraph();            // quick print
        void depthFirstTraversal();   // depth first traversal of entire graph ...prints
        void dftAtVertex(int vertex); // depth first traversal of the graph at a node specified 
        void breadthFirstTraversal(); // breadth first traversal of the entire graph ...prints
        graphType(int size = 0);      // constructor
        ~graphType();                 // destructor

    protected:
        int maxSize;                      // maximum number of vertices
        int gSize;                        // current number of vertices
        
        std::list<std::list<int>*> graph;             // list of list pointers
        std::list<std::list<int>*>::iterator git;     // iterator for graph
        std::list<int> * sub;                         // pointer to current sub list
        std::list<int>::iterator subit;               // iterator for sub list

    private:
        void dft(int v, bool visited[]); // helper for depthFirstTraversal and dftAtVertex ... prints
        std::list<int> dftSeq;           // just to print
        std::list<int> dftH;             // helper-holder
        std::list<int>::iterator dftHit;          // iterator for helper-holder
        const std::string inputFile = "input4.txt";   // TEST  change input file  here, remove when done
};


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------
bool graphType::isEmpty() const // GOOD
{
    return (gSize == 0);
}

//----------------------------------------------------------------------------------------------------------------------------
void graphType::createGraph(std::string fileName) // GOOD
{
    if (gSize != 0)	// if the graph is not empty, make it empty
    {
        clearGraph();
    }

    std::ifstream inFile;
    fileName = inputFile; // TESTING ONLY
    /*
    if ( fileName != inputFile)
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
    inFile.close();
} 

//----------------------------------------------------------------------------------------------------------------------------
void graphType::clearGraph() // GOOD
{
    git = graph.begin();
    for (int i = 0; i < gSize; i++)
    {
        //sub = new std::list<int>;
        sub = *git;
        delete sub;
        git++;
    }
    graph.clear();
    gSize = 0; // this reset indicates graph is empty
} 

//----------------------------------------------------------------------------------------------------------------------------
void graphType::printGraph() // GOOD
{
    if (gSize == 0)
    {
        std::cout << "\n    .... the graph is empty\n";
    }
    else
    {
        git = graph.begin();
    
        std::cout << "\nGRAPH :\n";
        std::cout << "---------------------\n";
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
        std::cout << "\n---------------------\n";
    } 
} 

//----------------------------------------------------------------------------------------------------------------------------
void graphType::depthFirstTraversal() // entire graph ... n vertecies  0 to n-1   GOOD
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
void graphType::dft(int v, bool visited[]) // works entire graph from vertex given ...modulus wrap
{

    if (!visited[v])
    {
        dftSeq.push_back(v); // for printing 
    }
    visited[v] = true;
    git = graph.begin();
    std::advance(git, v); // put on proper index to get proper sub list
    /*
    dftH = *(*git);
    dftHit = dftH.begin();
    for (int i = 0; i < dftH.size(); i++)
    {
        int w = *dftHit;
        if (!visited[w]) // if the vertex has not been visited
        {
            dft(w, visited);
        }
        dftHit++;
    }
    git++;
    */
    /*
    sub = new std::list<int>;
    sub = *git;
    subit = sub->begin();
    for (int i = 0; i < sub->size(); i++)
    {
        int w = *subit;
        if (!visited[w])
        {
            dft(w, visited);
        }
        subit++;
    }
    sub = nullptr;
    delete sub;
    git++;
    */
    /*
    std::list<int> *temp; // temporarily hold the sub list
    temp = *git;
    std::list<int>::iterator tempit;
    tempit = temp->begin();
    for (int j = 0; j < temp->size(); j++)
    {
        int w = *tempit;
        if (!visited[w])
        {
            dft(w, visited);
        }
        tempit++;
    }*/
    
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
void graphType::dftAtVertex(int vertex) // from a node     going to take from vertex, modular wrap
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
        int v = *trit;
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
void graphType::breadthFirstTraversal() // entire graph, like level by level on binary tree     GOOD
{
    if (gSize == 0)
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
graphType::graphType(int size) // GOOD
{
    maxSize = size;
    gSize = 0;
    //graph = new unorderedLinkedList<int>[size]; // make an array where each element is a linked list, according to size
}

//----------------------------------------------------------------------------------------------------------------------------
graphType::~graphType() // GOOD
{
    clearGraph(); // use helper
}


//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
#endif  // end graphType.h
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------
