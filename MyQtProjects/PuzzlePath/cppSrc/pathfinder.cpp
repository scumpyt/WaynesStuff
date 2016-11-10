#include "pathfinder.h"
#include <set>
#include <map>
#include <iostream>
#include <array>

PathFinder::PathFinder(const std::vector<std::string>& inGrid)
    : myInGrid(inGrid)
{
    myNRows       = (int)myInGrid.size();
    myNCols       = (int)myInGrid.at(0).length();

    myTotalLength = myNRows * myNCols;

    mySourceNode.first=-1, mySourceNode.second=-1;
    findNode('A', mySourceNode.first, mySourceNode.second);

    myTargetNode.first=-1, myTargetNode.second=-1;
    findNode('B', myTargetNode.first, myTargetNode.second);

    myBuildInternalGrid();
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

bool PathFinder::validateInputGrid()
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

int PathFinder::findNode(char inChar) const
{
    int node = -1;
    foreach (auto str, myInGrid)
    {
        foreach (auto c, str)
        {
            ++node;
            if (c == inChar)
            {
                return node;
            }
        }
    }
    return node;
}

bool PathFinder::findNode(char inChar, int& row, int& col) const
{
    row = -1;
    foreach (auto str, myInGrid)
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
    // Assume valid node checking is done outside...
    myGrid[row][col] = val;
}

char PathFinder::getChar(int row, int col)
{
    return myInGrid.at(row).at(col);
}

bool PathFinder::isValidChar(int indx) const
{
    if (indx >=0 && indx < myTotalLength)
    {
        // Convert indx into a char at a specific line/indx...
        int lineNumber = (int)(indx/myNRows);
        int charIndx   = indx - (lineNumber * myNRows);
        return (myInGrid.at(lineNumber).at(charIndx) != 'X');
    }
    return false;
}

void PathFinder::printInGrid() const
{
    std::cout << "----------------------------\n";
    foreach (auto str, myInGrid)
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

bool PathFinder::markNeighbors(int targetRow, int targetCol, int curDist)
{
    int nextDist = curDist+1;

    bool ptsMarked   = false;
    bool targetFound = false;
    for (int row=0; row<myNRows; ++row)
    {
        for (int col=0; col<myNCols; ++col)
        {
            if (myGrid[row][col] == curDist)
            {
                if (row-1 >= 0)
                {
                    if (myGrid[row-1][col] == -1)
                    {
                        ptsMarked = true;
                        myGrid[row-1][col] = nextDist;
                        if (row-1 == targetRow && col == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
                if (row+1 < myNRows)
                {
                    if (myGrid[row+1][col] == -1)
                    {
                        ptsMarked = true;
                        myGrid[row+1][col] = nextDist;
                        if (row+1 == targetRow && col == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
                if (col-1 >= 0)
                {
                    if (myGrid[row][col-1] == -1)
                    {
                        ptsMarked = true;
                        myGrid[row][col-1] = nextDist;
                        if (row == targetRow && col-1 == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
                if (col+1 < myNCols)
                {
                    if (myGrid[row][col+1] == -1)
                    {
                        ptsMarked = true;
                        myGrid[row][col+1] = nextDist;
                        if (row == targetRow && col+1 == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
            }
        }
        if (targetFound) break;
    }

//    std::cout << "targetFound = " << targetFound << "\n";
//    std::cout << "ptsMarked   = " << ptsMarked << "\n";
    if (targetFound || !ptsMarked) return true;
    return false;
}

std::vector<std::pair<int,int>> PathFinder::extractPath(int targetRow, int targetCol,
                                                        int startRow, int startCol)
{
    std::vector<std::pair<int,int>> outPath;

    // Verify we got to target...
    int curDist = myGrid[targetRow][targetCol];
    if (curDist == -1)
    {
        std::cerr << "Error! Target node unreachable from source!" << std::endl;
        return outPath;
    }

    int curRow = targetRow;
    int curCol = targetCol;
    while (true)
    {
        --curDist;
        if (curDist <= 0 || (curRow == startRow && curCol == startCol)) break;
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

std::vector<std::string> PathFinder::getCopyOfInputGrid() const
{
    return myInGrid;
}
