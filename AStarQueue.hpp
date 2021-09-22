#include <vector>
#include <tuple>

#include "2dgridgraph.hpp"
#pragma once

/* Helper data structures for the A*-algortihm */

struct PathStep 
{
    GridGraph::nodeid_t parent;
    GridGraph::nodeid_t child; 
    int accCostToChild;
};

class AStarQueue 
{
public: 
    AStarQueue();

    /* insert if not present, update if cost lower, do nothing if present and cheaper */ 
    void merge(double prio, PathStep ps);

    PathStep pop_lowest_prio();

private:
    std::vector< std::tuple<double, PathStep> > queue;
};