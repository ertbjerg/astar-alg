#include <tuple>
#include <vector>
#include <map>
#include <queue>

#include "2dgridgraph.hpp"
#include "AStarQueue.hpp"

#pragma once

class AStarAlgorithm
{
public: // Client interface
    AStarAlgorithm(const GridGraph& graph, GridGraph::nodeid_t goal, GridGraph::nodeid_t start);
    void solve();
    std::vector<GridGraph::nodeid_t> path() const;

private:
    const GridGraph& gr;
    GridGraph::nodeid_t goal;
    GridGraph::nodeid_t start;
    AStarQueue frontier;
    std::map<GridGraph::nodeid_t, PathStep> completed;

    void process_neighbors(PathStep ps);
    void initialize();
    void prioritize(PathStep ps);
};