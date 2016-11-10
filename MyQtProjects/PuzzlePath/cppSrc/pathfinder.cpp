#include "pathfinder.h"
#include <set>
#include <map>
#include <iostream>

PathFinder::PathFinder(const std::vector<std::string>& inGrid)
    : myInGrid(inGrid)
{
    myLineLength  = (int)myInGrid.at(0).length();
    myTotalLength = (int)myInGrid.size() * myLineLength;

    mySourceNode  = findNode('A');
    myTargetNode  = findNode('B');

    //myNodes =
}

int PathFinder::getNLines() const
{
    return (int)myInGrid.size();
}

int PathFinder::getLineLength() const
{
    return myLineLength;
}

int PathFinder::getTotalLength() const
{
    return myTotalLength;
}

int PathFinder::findNode(char inChar) const
{
    //int curLine = -1;
    int node = -1;
    foreach (auto str, myInGrid)
    {
        //++curLine;
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
        int lineNumber = (int)(indx/myLineLength);
        int charIndx   = indx - (lineNumber * myLineLength);
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
    int nRows = getNLines();
    int nCols = getLineLength();

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
    int nRows = getNLines();
    int nCols = getLineLength();

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

    std::cout << "targetFound = " << targetFound << "\n";
    std::cout << "ptsMarked   = " << ptsMarked << "\n";
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

//    int nRows = getNLines();
//    int nCols = getLineLength();

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
    int nRows = getNLines();
    int nCols = getLineLength();

    if (row >=0 && row < nRows)
    {
        if (col >= 0 && col < nCols)
        {
            return true;
        }
    }
    return false;
}





////////////////////////////////////////////////////////////////////////////////////////////
//#include "pathfinder.h"
//#include <set>
//#include <map>
//#include <iostream>

//PathFinder::PathFinder(const std::vector<std::string>& inGrid)
//    : myInGrid(inGrid)
//{
//    myLineLength  = (int)myInGrid.at(0).length();
//    myTotalLength = (int)myInGrid.size() * myLineLength;

//    mySourceNode  = findNode('A');
//    myTargetNode  = findNode('B');
//}

//void PathFinder::printInGrid() const
//{
//    std::cout << "----------------------------\n";
//    foreach (auto str, myInGrid)
//    {
//        std::cout << str << "\n";
//    }
//    std::cout << "----------------------------\n";
//}

//int PathFinder::getNLines() const
//{
//    return (int)myInGrid.size();
//}

//int PathFinder::getLineLength() const
//{
//    return myLineLength;
//}

//int PathFinder::getTotalLength() const
//{
//    return myTotalLength;
//}

//int PathFinder::findNode(char inChar) const
//{
//    //int curLine = -1;
//    int node = -1;
//    foreach (auto str, myInGrid)
//    {
//        //++curLine;
//        foreach (auto c, str)
//        {
//            ++node;
//            if (c == inChar)
//            {
//                return node;
//            }
//        }
//    }
//    return node;
//}

//std::vector< std::vector<edge> > PathFinder::buildEdgeGraph()
//{
//    std::vector< std::vector<edge> > outGraph;
//    std::vector<edge> edges;

//    int curIndx = -1;
//    int curLine = -1;
//    int neighborIndx = -1;
//    foreach (auto str, myInGrid)
//    {
//        ++curLine;
//        foreach (auto c, str)
//        {
//            ++curIndx;
//            edges.clear();

//            if (c != 'X')   // If current char is X, don't add any edges...
//            {
//                // Check all 4 near neighbors, and, if valid,
//                // add an edge to the graph for that neighbor.
//                edge curEdge;
//                curEdge.length  = 1;

//                // North...
//                neighborIndx = curIndx-myLineLength;
//                if (neighborIndx >= 0 && isValidChar(neighborIndx))
//                {
//                    curEdge.to      = neighborIndx;
//                    edges.emplace_back(curEdge);
//                }

//                // East...
//                neighborIndx = curIndx+1;
//                if (neighborIndx < ((curLine+1)*myLineLength) && isValidChar(neighborIndx))
//                {
//                    curEdge.to      = neighborIndx;
//                    edges.emplace_back(curEdge);
//                }

//                // South...
//                neighborIndx = curIndx+myLineLength;
//                if (neighborIndx < myTotalLength && isValidChar(neighborIndx))
//                {
//                    curEdge.to      = neighborIndx;
//                    edges.emplace_back(curEdge);
//                }

//                // West...
//                neighborIndx = curIndx-1;
//                if (neighborIndx >= ((curLine)*myLineLength) && isValidChar(neighborIndx))
//                {
//                    curEdge.to      = neighborIndx;
//                    edges.emplace_back(curEdge);
//                }
//            }

//            // Add (possibly empty) edge vector for this node...
//            outGraph.emplace_back(edges);
//        }
//    }

//    return outGraph;
//}

//bool PathFinder::isValidChar(int indx) const
//{
//    if (indx >=0 && indx < myTotalLength)
//    {
//        // Convert indx into a char at a specific line/indx...
//        int lineNumber = (int)(indx/myLineLength);
//        int charIndx   = indx - (lineNumber * myLineLength);
//        return (myInGrid.at(lineNumber).at(charIndx) != 'X');
//    }
//    return false;
//}

//int PathFinder::doDijkstra(const std::vector< std::vector<edge> >& graph,
//                           int source, int target,
//                           std::vector<std::vector<int>>& possiblePaths)
//{
//    std::vector<int> min_distance( graph.size(), INT_MAX );
//    min_distance[ source ] = 0;
//    std::set< std::pair<int,int> > active_vertices;
//    active_vertices.insert( {0,source} );

//    possiblePaths.clear();

//    while (!active_vertices.empty())
//    {
//        int where = active_vertices.begin()->second;
//        if (where == target)
//        {
//            return min_distance[where];
//        }
//        active_vertices.erase( active_vertices.begin() );

//        std::vector<int> equalDistNodes;
//        int curDist = -1;

//        for (auto ed : graph[where])
//        {
//            if (min_distance[ed.to] > min_distance[where] + ed.length)
//            {
//                active_vertices.erase( { min_distance[ed.to], ed.to } );
//                min_distance[ed.to] = min_distance[where] + ed.length;
//                active_vertices.insert( { min_distance[ed.to], ed.to } );

//                std::cout << "DIST/To = " << min_distance[ed.to] << " / " << ed.to << std::endl;

//                equalDistNodes.push_back(ed.to);
//                if (curDist != min_distance[ed.to])
//                {
//                    //std::cout << "2\n";
//                    possiblePaths.push_back(equalDistNodes);
//                    equalDistNodes.clear();
//                }
//                curDist = min_distance[ed.to];
//            }
//        }
//    }
//    return INT_MAX;
//}

//std::vector<int> PathFinder::findBestPath(const std::vector<std::vector<int>>& possiblePaths)
//{
//    std::vector<int> outPath;
//    int target = myTargetNode;
//    for (auto itr=possiblePaths.rbegin(); itr!=possiblePaths.rend(); ++itr) // Skip first as that is Target
//    {
//        target = findNeighbor(*itr, target);
//        if (target != -1)
//        {
//            outPath.push_back(target);
//            std::cout << "NODE = " << target << std::endl;
//        }
//    }
//    return outPath;
//}

//int PathFinder::findNeighbor(const std::vector<int>& equalDistNodes, int searchFrom)
//{
//    int neighbor = -1;
//    foreach (auto node, equalDistNodes)
//    {
//        // Look for match, starting at north, working clockwise...
//        if      (node == searchFrom-myLineLength) neighbor = node;
//        else if (node == searchFrom+1)            neighbor = node;
//        else if (node == searchFrom+myLineLength) neighbor = node;
//        else if (node == searchFrom-1)            neighbor = node;
//    }
//    return neighbor;
//}

////std::vector<int> PathFinder::findBestPath(const std::vector<std::vector<int>>& possiblePathsVect)
////{
////    std::vector<int> path;

////    for (auto startItr=possiblePathsVect.at(0).begin(); startItr != possiblePathsVect.at(0).end(); ++startItr)
////    {
////        path.clear();
////        int start = *startItr;
////        path.emplace_back(start);

////        int cur = start;
////        int next;
//////        //for (auto itr=possiblePathsVect.begin()+1; itr != possiblePathsVect.end(); ++itr)
//////        for (int level=1; level<(int)possiblePathsVect.size(); ++level)
//////        {
//////            if (myVisitForShortPath(cur, next, level, possiblePathsVect))
//////            {
//////                return path;
//////            }
//////            cur = next;
//////        }

////        int level = 1;
//////        while (!myVisitForBestPath(cur, next, level, possiblePathsVect))
//////        {
//////            return path;
//////        }
////    }
////}

////bool myVisit (int cur, std::vector<int>& path, int level, const std::vector<std::vector<int>>& possiblePathsVect)
////{
////    for (auto itr=possiblePathsVect.at(level).begin(); itr != possiblePathsVect.at(level).end(); ++itr)
////    {

////    }
////}
