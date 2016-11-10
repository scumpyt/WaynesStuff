#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <string>

#include "cppsrc_global.h"

class CPPSRCSHARED_EXPORT PathFinder
{
public:
    explicit PathFinder(const std::vector<std::string>& inGrid);

    int                                 getNLines() const;
    int                                 getLineLength() const;
    int                                 getTotalLength() const;
    int                                 findNode(char c) const;
    bool                                findNode(char c, int& row, int& col) const;

    char                                getChar(int row, int col);
    bool                                isValidChar(int indx) const;

    void                                printInGrid() const;
    void                                printGrid(int** grid);

    bool                                markNeighbors(int** grid, int targetRow, int targetCol, int curDist);
    std::vector<std::pair<int,int>>     extractPath(int** grid,
                                                    int targetRow, int targetCol,
                                                    int startRow, int startCol);
    bool                                searchNearNeighbors(int** grid, int& curRow, int& curCol, int curDist);
    bool                                searchNode(int** grid, int row, int col, int curDist);
    bool                                isValidNode(int row, int col) const;

private:
    std::vector<std::string>            myInGrid;
    int                                 myLineLength;
    int                                 myTotalLength;
    int                                 mySourceNode;
    int                                 myTargetNode;
};

#endif // PATHFINDER_H



////////////////////////////////////////////////////////////////////
//#ifndef PATHFINDER_H
//#define PATHFINDER_H

//#include <vector>
//#include <string>

//#include "cppsrc_global.h"

//struct edge
//{
//    int to, length;
//};

////struct neighbor
////{
////    int node;
////    double dist;
////    neighbor(int inNode, double inDist)
////        : node(inNode), weight(inDist)
////    { }
////};

//class CPPSRCSHARED_EXPORT PathFinder
//{
//public:
//    explicit PathFinder(const std::vector<std::string>& inGrid);

//    std::vector< std::vector<edge> >    buildEdgeGraph();
//    //std::vector<std::vector<neighbor> > buildNeighbors();

//    int                                 getNLines() const;
//    int                                 getLineLength() const;
//    int                                 getTotalLength() const;
//    int                                 findNode(char c) const;

//    //char                                getCharAtIndx(int indx);
//    bool                                isValidChar(int indx) const;

//    void                                printInGrid() const;

//    int                                 doDijkstra(const std::vector< std::vector<edge> >& graph,
//                                                   int source, int target,
//                                                   //std::vector<int>& shortRouteNodes);
//                                                   //std::vector<std::pair<int, int>>& possiblePaths);
//                                                   std::vector<std::vector<int>>& possiblePaths);

//    std::vector<int>                    findBestPath(const std::vector<std::vector<int>>& possiblePaths);
//    int                                 findNeighbor(const std::vector<int>& equalDistNodes, int searchFromNode);

//private:
//    std::vector<std::string>            myInGrid;
//    int                                 myLineLength;
//    int                                 myTotalLength;
//    int                                 mySourceNode;
//    int                                 myTargetNode;
//};

//#endif // PATHFINDER_H
