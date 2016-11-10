#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "pathfinder.h"

int main()
{
    // Step 1: Read, store and echo input file...
    std::string inFileName;
    //    std::cout << "Enter input Puzzle File name: ";

    //    std::cin  >> inFileName;
    //    std::cout << std::endl;

    inFileName = "Puzzle1.txt";

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
        std::cout << *(inGrid.end()-1) << "\n";     // Echo...
    }
    inFile.close();

    // Step 2: Initialize and validate our PathFinder helper object
    PathFinder pf(inGrid);

    if (!pf.validateInputGrid())
    {
        std::cerr << "Error! Invalid Input file!" << std::endl;
        return -1;
    }

    std::pair<int,int> sourceNode = pf.getSourceNode();
    std::pair<int,int> targetNode = pf.getTargetNode();

    // Step 3: Starting with dist=0 at the source node, expand outward
    //         marking each accessible, near neighbor with dist+1.
    //         repeat until the target is reached, or, no more neighbors
    //         can be marked.
    int curDist = 0;
    pf.setGridNode(sourceNode.first, sourceNode.second, curDist);

    // Now expand outward...
    while (true)
    {
        if (pf.markNeighbors(curDist)) break;
        ++curDist;
    }

    // Step 4: Go to the target node, and find the neighbor that has a dist
    //         of 1 less than the previous, and add that node to the output
    //         path. Repeat until you have reached the source node.
    std::vector<std::pair<int,int>> outPath = pf.extractPath(targetNode.first, targetNode.second,
                                                             sourceNode.first, sourceNode.second);
    if (outPath.empty())
    {
        std::cerr << "Error! Unable to extract path!" << std::endl;
        return -1;
    }

    // Step 5: Copy input file to solution file, and add dots at every path node.
    std::vector<std::string> solutionFile = pf.getCopyOfInputGrid();
    foreach (auto node, outPath)
    {
        solutionFile.at(node.first).at(node.second) = '.';
    }

    // Step 6: Echo solution file...
    std::cout << "----- Solution File -----\n";
    foreach (auto str, solutionFile)
    {
        std::cout << str << "\n";
    }
    std::cout << "-------------------------\n";

    return 0;
}
