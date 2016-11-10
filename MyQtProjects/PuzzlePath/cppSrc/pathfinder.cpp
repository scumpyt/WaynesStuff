#include "pathfinder.h"
#include <set>
#include <map>
#include <iostream>
#include <array>

PathFinder::PathFinder(const std::vector<std::string>& inTextLines)
    : myInFile(inTextLines), myNRows(0), myNCols(0), myTotalLength(0)
    , mySourceNode(std::make_pair(-1,-1))
    , myTargetNode(std::make_pair(-1,-1))
{
    if (!myInFile.empty())
    {
        myNRows       = (int)myInFile.size();
        myNCols       = (int)myInFile.at(0).length();

        myTotalLength = myNRows * myNCols;

        mySourceNode.first=-1, mySourceNode.second=-1;
        findNode('A', mySourceNode.first, mySourceNode.second);

        myTargetNode.first=-1, myTargetNode.second=-1;
        findNode('B', myTargetNode.first, myTargetNode.second);

        myBuildInternalGrid();
    }
}

void PathFinder::myBuildInternalGrid()
{
    // Allocate one vector per row...
    for (int row=0; row<myNRows; ++row)
    {
        std::vector<int> rowVect;
        rowVect.resize(myNCols);
        myGrid.push_back(rowVect);
    }

    // Fill grid with initial values
    for (int row=0; row<myNRows; ++row)
    {
        for (int col=0; col<myNCols; ++col)
        {
            // Obstacles get a -9, all others are 'unmarked' (-1)
            if (getChar(row, col) == 'X')
            {
                myGrid[row][col] = -9;
            }
            else
            {
                myGrid[row][col] = -1;
            }
        }
    }
}

int PathFinder::getNRows() const
{
    return myNRows;
}

int PathFinder::getNCols() const
{
    return myNCols;
}

int PathFinder::getTotalLength() const
{
    return myTotalLength;
}

bool PathFinder::validateInputFile()
{
    if (mySourceNode.first == -1 || mySourceNode.second == -1)
    {
        std::cerr << "Error! Unable to find source node!" << std::endl;
        return false;
    }

    if (myTargetNode.first == -1 || myTargetNode.second == -1)
    {
        std::cerr << "Error! Unable to find target node!" << std::endl;
        return false;
    }

    return true;
}

bool PathFinder::findNode(char inChar, int& row, int& col) const
{
    row = -1;
    foreach (auto str, myInFile)
    {
        ++row;

        col = -1;
        foreach (auto c, str)
        {
            ++col;
            if (c == inChar)
            {
                return true;
            }
        }
    }
    row = col = -1; // Reset back to 'not found'
    return false;
}

void PathFinder::setGridNode(int row, int col, int val)
{
    if (isValidNode(row, col)) myGrid[row][col] = val;
}

char PathFinder::getChar(int row, int col)
{
    if (isValidNode(row, col)) return myInFile.at(row).at(col);
    return 'X';
}

void PathFinder::printInGrid() const
{
    std::cout << "----------------------------\n";
    foreach (auto str, myInFile)
    {
        std::cout << str << "\n";
    }
    std::cout << "----------------------------\n";
}

void PathFinder::printGrid()
{
    for (int row=0; row<myNRows; ++row)
    {
        for (int col=0; col<myNCols; ++col)
        {
            std::cout << myGrid[row][col] << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::pair<int,int> PathFinder::getSourceNode() const
{
    return mySourceNode;
}

std::pair<int,int> PathFinder::getTargetNode() const
{
    return myTargetNode;
}

bool PathFinder::markNeighbors(int curDist)
{
    // For every node that matches our current distance, go to each
    // that node's near neighbors, and, if it's valid and unmarked,
    // update it's value to curDist+1. Once we make it to the target
    // node, break out.

    int nextDist = curDist+1;

    bool ptsMarked   = false;
    bool targetFound = false;
    for (int row=0; row<myNRows; ++row)
    {
        for (int col=0; col<myNCols; ++col)
        {
            if (myGrid[row][col] == curDist)
            {
                if (isValidNode(row-1, col) && isUnMarked(row-1, col))
                {
                    ptsMarked = true;
                    myGrid[row-1][col] = nextDist;
                    if (isTargetNode(row-1, col))
                    {
                        targetFound = true;
                        break;
                    }
                }
                if (isValidNode(row+1, col) && isUnMarked(row+1, col))
                {
                    ptsMarked = true;
                    myGrid[row+1][col] = nextDist;
                    if (isTargetNode(row+1, col))
                    {
                        targetFound = true;
                        break;
                    }
                }
                if (isValidNode(row, col-1) && isUnMarked(row, col-1))
                {
                    ptsMarked = true;
                    myGrid[row][col-1] = nextDist;
                    if (isTargetNode(row, col-1))
                    {
                        targetFound = true;
                        break;
                    }
                }
                if (isValidNode(row, col+1) && isUnMarked(row, col+1))
                {
                    ptsMarked = true;
                    myGrid[row][col+1] = nextDist;
                    if (isTargetNode(row, col+1))
                    {
                        targetFound = true;
                        break;
                    }
                }
            }
        }
        if (targetFound) break;
    }

    if (targetFound || !ptsMarked) return true;
    return false;
}

std::vector<std::pair<int,int>> PathFinder::extractPath()
{
    std::vector<std::pair<int,int>> outPath;

    // validate...
    if (validateInputFile() == false) return outPath;

    // Step 1: Starting with dist=0 at the source node, expand outward
    //         marking each accessible near neighbor with dist+1.
    //         repeat until the target is reached, or, no more neighbors
    //         can be marked.
    int curDist = 0;
    setGridNode(mySourceNode.first, mySourceNode.second, curDist);

    // Now expand outward...
    while (true)
    {
        if (markNeighbors(curDist)) break;
        ++curDist;
    }

    // Step 2: Verify we got to target...
    curDist = myGrid[myTargetNode.first][myTargetNode.second];
    if (curDist == -1)
    {
        std::cerr << "Error! Target node unreachable from source!" << std::endl;
        return outPath;
    }

    // Step 3: Now go back to the target node, and find the near-neighbor that has a
    //         dist of 1 less than the previous, and add that node to the output path.
    //         Repeat until you have reached the source node.
    int curRow = myTargetNode.first;
    int curCol = myTargetNode.second;
    while (true)
    {
        --curDist;
        if (curDist <= 0 ||
           (curRow == mySourceNode.first && curCol == mySourceNode.second)) break;

        if (searchNearNeighbors(curRow, curCol, curDist))
        {
            outPath.push_back(std::make_pair(curRow, curCol));
        }
    }

    return outPath;
}

bool PathFinder::searchNearNeighbors(int& row, int& col, int curDist)
{
    if (searchNode(row-1, col, curDist))
    {
        --row;
        return true;
    }
    if (searchNode(row+1, col, curDist))
    {
        ++row;
        return true;
    }
    if (searchNode(row, col-1, curDist))
    {
        --col;
        return true;
    }
    if (searchNode(row, col+1, curDist))
    {
        ++col;
        return true;
    }

    return false;
}

bool PathFinder::searchNode(int row, int col, int curDist)
{
    if (isValidNode(row, col))
    {
        if (myGrid[row][col] == curDist) return true;
    }
    return false;
}

bool PathFinder::isValidNode(int row, int col) const
{
    if (row >=0 && row < myNRows)
    {
        if (col >= 0 && col < myNCols)
        {
            return true;
        }
    }
    return false;
}

bool PathFinder::isUnMarked  (int row, int col) const
{
    return myGrid[row][col] == -1;
}

bool PathFinder::isTargetNode(int row, int col) const
{
    return (row == myTargetNode.first && col == myTargetNode.second);
}

std::vector<std::string> PathFinder::getCopyOfInputFile() const
{
    return myInFile;
}
