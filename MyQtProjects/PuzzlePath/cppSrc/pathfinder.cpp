#include "pathfinder.h"
#include <set>
#include <map>
#include <iostream>

PathFinder::PathFinder(const std::vector<std::string>& inGrid)
    : myInGrid(inGrid)
{
    myNRows       = (int)myInGrid.size();
    myNCols       = (int)myInGrid.at(0).length();

    myTotalLength = myNRows * myNCols;

    mySourceNode  = findNode('A');
    myTargetNode  = findNode('B');
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
    return false;
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

void PathFinder::printGrid(int** grid)
{
    int nRows = getNRows();
    int nCols = getNCols();

    for (int row=0; row<nRows; ++row)
    {
        for (int col=0; col<nCols; ++col)
        {
            std::cout << grid[row][col] << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool PathFinder::markNeighbors(int** grid, int targetRow, int targetCol, int curDist)
{
    int nRows = getNRows();
    int nCols = getNCols();

    int nextDist = curDist+1;

    bool ptsMarked   = false;
    bool targetFound = false;
    for (int row=0; row<nRows; ++row)
    {
        for (int col=0; col<nCols; ++col)
        {
            if (grid[row][col] == curDist)
            {
                if (row-1 >= 0)
                {
                    if (grid[row-1][col] == -1)
                    {
                        ptsMarked = true;
                        grid[row-1][col] = nextDist;
                        if (row-1 == targetRow && col == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
                if (row+1 < nRows)
                {
                    if (grid[row+1][col] == -1)
                    {
                        ptsMarked = true;
                        grid[row+1][col] = nextDist;
                        if (row+1 == targetRow && col == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
                if (col-1 >= 0)
                {
                    if (grid[row][col-1] == -1)
                    {
                        ptsMarked = true;
                        grid[row][col-1] = nextDist;
                        if (row == targetRow && col-1 == targetCol)
                        {
                            targetFound = true;
                            break;
                        }
                    }
                }
                if (col+1 < nCols)
                {
                    if (grid[row][col+1] == -1)
                    {
                        ptsMarked = true;
                        grid[row][col+1] = nextDist;
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

std::vector<std::pair<int,int>> PathFinder::extractPath(int** grid,
                                                        int targetRow, int targetCol,
                                                        int startRow, int startCol)
{
    std::vector<std::pair<int,int>> outPath;

    // Verify we got to target...
    int curDist = grid[targetRow][targetCol];
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
        if (searchNearNeighbors(grid, curRow, curCol, curDist))
        {
            outPath.push_back(std::make_pair(curRow, curCol));
        }
    }

    return outPath;
}

bool PathFinder::searchNearNeighbors(int** grid, int& row, int& col, int curDist)
{
    if (searchNode(grid, row-1, col, curDist))
    {
        --row;
        return true;
    }
    if (searchNode(grid, row+1, col, curDist))
    {
        ++row;
        return true;
    }
    if (searchNode(grid, row, col-1, curDist))
    {
        --col;
        return true;
    }
    if (searchNode(grid, row, col+1, curDist))
    {
        ++col;
        return true;
    }

    return false;
}

bool PathFinder::searchNode(int** grid, int row, int col, int curDist)
{
    if (isValidNode(row, col))
    {
        if (grid[row][col] == curDist) return true;
    }
    return false;
}

bool PathFinder::isValidNode(int row, int col) const
{
    int nRows = getNRows();
    int nCols = getNCols();

    if (row >=0 && row < nRows)
    {
        if (col >= 0 && col < nCols)
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
