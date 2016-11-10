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
    std::cout << "Enter input Puzzle File name: ";

    std::cin  >> inFileName;
    std::cout << std::endl;

    std::string curLine;
    std::string cwd ("");   // If you need to adjust your working I/O dir...
    std::ifstream inFile (cwd + inFileName);
    if (!inFile.is_open())
    {
        std::cout << "Unable to open file: " << inFileName << std::endl;
        return -1;
    }

    std::cout << "-----  Input File   -----\n";
    std::vector<std::string> inTextLines;
    while (std::getline (inFile, curLine))
    {
        inTextLines.emplace_back(curLine);
        std::cout << *(inTextLines.end()-1) << "\n";     // Echo...
    }
    inFile.close();
    std::cout << "-------------------------\n";

    // Step 2: Initialize and validate our PathFinder helper object
    PathFinder pf(inTextLines);
    if (!pf.validateInputFile())
    {
        std::cerr << "Error! Invalid Input file!" << std::endl;
        return -1;
    }

    // Step 3: Extract the shortest path from A to B, using the Lee Algorithm.
    std::vector<std::pair<int,int>> outPath = pf.extractPath();
    if (outPath.empty())
    {
        std::cerr << "Error! Unable to extract path!" << std::endl;
        return -1;
    }

    // Step 4: Copy input file to solution file, and add dots at every path node.
    std::vector<std::string> solutionFile = pf.getCopyOfInputFile();
    foreach (auto node, outPath)
    {
        solutionFile.at(node.first).at(node.second) = '.';
    }

    // Step 5: Echo solution file...
    std::cout << "----- Solution File -----\n";
    foreach (auto str, solutionFile)
    {
        std::cout << str << "\n";
    }
    std::cout << "-------------------------\n";

    // Step 6: Output solution as text file...
    std::string solFileName = cwd + "out_" + inFileName;
    std::ofstream oFile (solFileName);
    if (oFile.is_open())
    {
        foreach (auto str, solutionFile)
        {
            oFile << str << "\n";
        }
        oFile.close();
    }
    else
    {
        std::cerr << "Error! Unable to open output file!" << std::endl;
        return -1;
    }

    return 0;
}
