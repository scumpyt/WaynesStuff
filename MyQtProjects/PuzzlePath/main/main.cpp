#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "pathfinder.h"

int main()
{
    // Get input file name...
    std::string inFileName;
    //    std::cout << "Enter input Puzzle File name: ";

    //    std::cin  >> inFileName;
    //    std::cout << std::endl;

    inFileName = "Puzzle2.txt";

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

    PathFinder pf(inGrid);

    int nRows = pf.getNLines();
    int nCols = pf.getLineLength();

    int** grid = new int* [nRows];
    for (int i=0; i<nRows; ++i)
    {
        grid[i] = new int[nCols];
    }

    for (int row=0; row<nRows; ++row)
    {
        for (int col=0; col<nCols; ++col)
        {
            if (pf.getChar(row, col) == 'X')
            {
                grid[row][col] = -9;
            }
            else
            {
                grid[row][col] = -1;
            }
        }
    }

    //pf.printGrid(grid);


    int startRow, startCol;
    if (!pf.findNode('A', startRow, startCol))
    {
        std::cerr << "Error! Unable to find start node!" << std::endl;
    }

    int targetRow, targetCol;
    if (!pf.findNode('B', targetRow, targetCol))
    {
        std::cerr << "Error! Unable to find target node!" << std::endl;
    }

    std::cout << "Str R/C = " << startRow  << " / " << startCol << std::endl;
    std::cout << "End R/C = " << targetRow << " / " << targetCol << std::endl;

    // Start at 'A'
    int curDist = 0;
    grid[startRow][startCol] = curDist;
    //pf.printGrid(grid);

    // expand grid...
    while (true)
    {
        if (pf.markNeighbors(grid, targetRow, targetCol, curDist)) break;
        ++curDist;

        pf.printGrid(grid);
    }

    pf.printGrid(grid);

    // Now backtrack to extract path, going from target to source...
    std::vector<std::pair<int,int>> outPath = pf.extractPath(grid, targetRow, targetCol,
                                                             startRow, startCol);
    if (outPath.empty())
    {
        std::cerr << "Error! Unable to extract path!" << std::endl;
        return -1;
    }

    foreach (auto node, outPath)
    {
        std::cout << node.first << " / " << node.second << "\n";
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>

//#include "pathfinder.h"

//int main()
//{
//    // Get input file name...
//    std::string inFileName;
////    std::cout << "Enter input Puzzle File name: ";

////    std::cin  >> inFileName;
////    std::cout << std::endl;

//    inFileName = "Puzzle1.txt";

//    // Read, store and echo input file...
//    std::string curLine;
//    std::ifstream inFile ("../../" + inFileName);   // Actual file up 2 levels from exe...
//    if (!inFile.is_open())
//    {
//        std::cout << "Unable to open file: " << inFileName << std::endl;
//        return -1;
//    }

//    std::vector<std::string> inGrid;
//    while (std::getline (inFile, curLine))
//    {
//        inGrid.emplace_back(curLine);
//        std::cout << *(inGrid.end()-1) << "\n";
//    }
//    inFile.close();



//    /////////////////////////////////////////////////////////////////////////////
//    // Set up our PathFinder, and build edge graph...
//    PathFinder pathFinder(inGrid);
//    std::vector< std::vector<edge> > theEdges = pathFinder.buildEdgeGraph();

////    for (auto itr1 = theEdges.begin(); itr1 != theEdges.end(); ++itr1)
////    {
////        for (auto itr2=itr1->begin(); itr2 != itr1->end(); ++itr2)
////        {
////            edge cur = *itr2;
////            std::cout << "(" << cur.to << "," << cur.length << "), ";
////        }
////        std::cout << std::endl;
////    }

////    // Now use a modified Dijkstra's Shortest Path algorithm to find the best path...
//    int sourceNode = pathFinder.findNode('A');
//    int targetNode = pathFinder.findNode('B');
////    //std::vector<int> shortRouteNodes;
////    //int minDistance = pathFinder.doDijkstra(theEdges, sourceNode, targetNode, shortRouteNodes);

//    std::vector<std::vector<int>> possiblePaths;
//    //std::vector<std::pair<int, int>> possiblePaths;
//    int minDistance = pathFinder.doDijkstra(theEdges, sourceNode, targetNode, possiblePaths);
//    std::cout << "MIN DIST = " << minDistance << std::endl;

//    std::cout << "POSS SIZE = " << possiblePaths.size() << "\n";
//    for (auto itr1 = possiblePaths.begin(); itr1 != possiblePaths.end(); ++itr1)
//    {
//        for (auto itr2=itr1->begin(); itr2 != itr1->end(); ++itr2)
//        {
//            std::cout << *itr2 << ", ";
//        }
//        std::cout << std::endl;
//    }


//    std::vector<int> v = pathFinder.findBestPath(possiblePaths);

////    // Next, create the solution file, and mark the shortest path nodes with a dot...
//////    int indx = -1;
//////    //int curLine = -1;
//////    for (int i=0; i<pathFinder.getNLines(); ++i)
//////    {
//////        for (int j=0; j<pathFinder.getLineLength(); ++j)
//////        {
//////            ++indx;
//////            std::cout << shortRouteNodes.at(indx) << "#";
//////        }
//////        std::cout << "\n";
//////    }

//    // Echo, and output solution file...

//    return 0;
//}
