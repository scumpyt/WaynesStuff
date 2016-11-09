#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <string>

#include "cppsrc_global.h"

struct edge
{
    int to, length;
};

class CPPSRCSHARED_EXPORT PathFinder
{
public:
    explicit PathFinder(const std::vector<std::string>& inGrid);

    std::vector< std::vector<edge> >    buildEdgeGraph();

    int                                 getLineLength() const;
    int                                 getTotalLength() const;
    int                                 findNode(char c) const;

    int                                 doDijkstra(const std::vector< std::vector<edge> >& graph,
                                                   int source, int target,
                                                   std::vector<int>& shortRouteNodes);

private:
    std::vector<std::string>            myInGrid;
    int                                 myLineLength;
    int                                 myTotalLength;
};

#endif // PATHFINDER_H
