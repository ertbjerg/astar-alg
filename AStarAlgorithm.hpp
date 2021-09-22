#include <tuple>
#include <vector>
#include <queue>

#include "2dgridgraph.hpp"

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
};