#include "pathfinder.h"
#include <set>

PathFinder::PathFinder(const std::vector<std::string>& inGrid)
    : myInGrid(inGrid)
{
    myLineLength  = (int)myInGrid.at(0).length();
    myTotalLength = (int)myInGrid.size() * myLineLength;
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

std::vector< std::vector<edge> > PathFinder::buildEdgeGraph()
{
    std::vector< std::vector<edge> > outGraph;
    std::vector<edge> edges;

    int curIndx = -1;
    int curLine = -1;
    int neighborIndx = -1;
    foreach (auto str, myInGrid)
    {
        ++curLine;
        foreach (auto c, str)
        {
            ++curIndx;
            edges.clear();

            int len = (c == 'X') ? INT_MAX : 1;    // Set X nodes length to INT_MAX

            // Check all 4 near neighbors, and, if valid,
            // add an edge to the graph for that neighbor.
            edge curEdge;

            // North...
            neighborIndx = curIndx-myLineLength;
            if (neighborIndx >= 0)
            {
                curEdge.to      = neighborIndx;
                curEdge.length  = len;
                edges.emplace_back(curEdge);
            }

            // East...
            neighborIndx = curIndx+1;
            if (neighborIndx < ((curLine+1)*myLineLength))
            {
                curEdge.to      = neighborIndx;
                curEdge.length  = len;
                edges.emplace_back(curEdge);
            }

            // South...
            neighborIndx = curIndx+myLineLength;
            if (neighborIndx < myTotalLength)
            {
                curEdge.to      = neighborIndx;
                curEdge.length  = len;
                edges.emplace_back(curEdge);
            }

            // West...
            neighborIndx = curIndx-1;
            if (neighborIndx >= ((curLine)*myLineLength))
            {
                curEdge.to      = neighborIndx;
                curEdge.length  = len;
                edges.emplace_back(curEdge);
            }

            outGraph.emplace_back(edges);
        }
    }

    return outGraph;
}

int PathFinder::doDijkstra(const std::vector< std::vector<edge> >& graph,
                           int source, int target,
                           std::vector<int>& shortRouteNodes)
{
    std::vector<int> min_distance( graph.size(), INT_MAX );
    min_distance[ source ] = 0;
    std::set< std::pair<int,int> > active_vertices;
    active_vertices.insert( {0,source} );

    while (!active_vertices.empty())
    {
        int where = active_vertices.begin()->second;
        if (where == target)
        {
            return min_distance[where];
        }
        active_vertices.erase( active_vertices.begin() );

        for (auto ed : graph[where])
        {
            if (min_distance[ed.to] > min_distance[where] + ed.length)
            {
                active_vertices.erase( { min_distance[ed.to], ed.to } );
                min_distance[ed.to] = min_distance[where] + ed.length;
                active_vertices.insert( { min_distance[ed.to], ed.to } );
            }
        }
    }
    return INT_MAX;
}
