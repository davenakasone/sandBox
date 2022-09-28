/*
    the stacks, queues, and lists are starting to fail...will use STL so the work can be focused on the graph
    you could inherit, but I won't, so everything can stay in one file and no virtual calls confound

    the undirected graph would be the same, just change inputs    any object out of 'grahType.h'  
    input 0, 1, 2   are directed graphs   input 3 is undirected

    the weighted graph is input 4, 5, 

*/

#include "graphType.h"
#include "weightedGraph.h"

std::string DIS = ""; // discard

void next();
void graphTypeTest();
void weightedGraphTest();
//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
int main() 
{
    //graphTypeTest();
    weightedGraphTest();

    std::cout << "\n\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0; 
}

//----------------------------------------------------------------------------------------------------------------------------
void next()
{
    std::cout << "\n        test complete, enter any key to continue: ";
    std::cin >> DIS;
    std::cout.flush();
    system("clear");
}

//----------------------------------------------------------------------------------------------------------------------------
void graphTypeTest()
{
    graphType test;

    std::cout << "\n the graph is empty?  " << test.isEmpty();
    test.createGraph();
    test.printGraph();
    std::cout << "\n the graph is empty?  " << test.isEmpty();
    next();

    test.clearGraph();
    test.printGraph();
    std::cout << "\n the graph is empty?  " << test.isEmpty();
    test.createGraph();
    test.printGraph();
    std::cout << "\n the graph is empty?  " << test.isEmpty();
    next();

    test.breadthFirstTraversal();
    test.clearGraph();
    test.breadthFirstTraversal();
    next();
    
    test.depthFirstTraversal();
    test.createGraph();
    test.dftAtVertex(9999);
    test.printGraph();
    test.depthFirstTraversal();
    test.dftAtVertex(2); // pick a vertex to start from
    next();
}

//----------------------------------------------------------------------------------------------------------------------------
void weightedGraphTest()
{
    weightedGraphType wG;
    
    wG.createWeightedGraph();
    wG.printGraph();
    std::cout << "\n  this graph has " << wG.getSize() << " nodes\n";
    next();

    wG.clearGraph();
    wG.printGraph();
    std::cout << "\n  this graph has " << wG.getSize() << " nodes\n";
    next();

    std::cout << std::endl;
    wG.createWeightedGraph();
    wG.breadthFirstTraversal();
    wG.depthFirstTraversal();
    wG.printGraph();
    std::cout << "\n  this graph has " << wG.getSize() << " nodes\n";
    next();
    
    wG.createWeightedGraph();
    wG.shortestPath(0);
}

//----------------------------------------------------------------------------------------------------------------------------
//============================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------