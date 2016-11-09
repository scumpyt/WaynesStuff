#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "pathfinder.h"

int main()
{
    // Get input file name...
    std::string inFileName;
    std::cout << "Enter input Puzzle File name: ";

    std::cin  >> inFileName;
    std::cout << std::endl;

    // Read, store and echo input file...
    std::string curLine;
    std::ifstream inFile ("../../" + inFileName);   // Actual file up 2 levels from exe...
    if (!inFile.is_open())
    {
        std::cout << "Unable to open file: " << inFileName << std::endl;
        return -1;
    }

    std::vector<std::string> inGrid;
    while (std::getline (inFile, curLine))
    {
        inGrid.emplace_back(curLine);
        std::cout << *(inGrid.end()-1) << "\n";
    }
    inFile.close();

    // Set up our PathFinder, and build edge graph...
    PathFinder pathFinder(inGrid);
    std::vector< std::vector<edge> > theEdges = pathFinder.buildEdgeGraph();

    // Now use a modified Dijkstra's Shortest Path algorithm to find the best path...
    int sourceNode = pathFinder.findNode('A');
    int targetNode = pathFinder.findNode('B');
    std::vector<int> shortRouteNodes;
    int minDistance = pathFinder.doDijkstra(theEdges, sourceNode, targetNode, shortRouteNodes);
    std::cout << "MIN DIST = " << minDistance << std::endl;

    // Next, create the solution file, and mark the shortest path nodes with a dot...

    // Echo, and output solution file...

    return 0;
}
