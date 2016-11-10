#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <string>

#include "cppsrc_global.h"

class CPPSRCSHARED_EXPORT PathFinder
{
public:
    explicit PathFinder(const std::vector<std::string>& inTextLines);

    int                                 getNRows() const;
    int                                 getNCols() const;
    int                                 getTotalLength() const;
    bool                                findNode(char c, int& row, int& col) const;

    bool                                validateInputFile();

    void                                setGridNode(int row, int col, int val);

    char                                getChar(int row, int col);
    bool                                isValidNode (int row, int col) const;
    bool                                isUnMarked  (int row, int col) const;
    bool                                isTargetNode(int row, int col) const;

    void                                printInGrid() const;
    void                                printGrid();

    std::pair<int,int>                  getSourceNode() const;
    std::pair<int,int>                  getTargetNode() const;

    bool                                markNeighbors(int curDist);
    std::vector<std::pair<int,int>>     extractPath(int targetRow, int targetCol,
                                                    int startRow, int startCol);
    bool                                searchNearNeighbors(int& curRow, int& curCol, int curDist);
    bool                                searchNode(int row, int col, int curDist);

    std::vector<std::string>            getCopyOfInputFile() const;

private:
    void                                myBuildInternalGrid();

private:
    std::vector<std::string>            myInFile;
    int                                 myNRows;
    int                                 myNCols;
    int                                 myTotalLength;

    std::pair<int,int>                  mySourceNode;
    std::pair<int,int>                  myTargetNode;

    std::vector<std::vector<int>>       myGrid;
};

#endif // PATHFINDER_H
