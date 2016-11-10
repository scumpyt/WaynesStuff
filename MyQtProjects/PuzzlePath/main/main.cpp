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

    int nRows = pf.getNRows();
    int nCols = pf.getNCols();

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

        //pf.printGrid(grid);
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

    // Copy input file to solution file
    std::vector<std::string> solutionFile = pf.getCopyOfInputGrid();

    // then add '.' (dots) at each path node...
    foreach (auto node, outPath)
    {
        solutionFile.at(node.first).at(node.second) = '.';
    }

    // Echo solution file...
    std::cout << "----------------------------\n";
    foreach (auto str, solutionFile)
    {
        std::cout << str << "\n";
    }
    std::cout << "----------------------------\n";

    return 0;
}
