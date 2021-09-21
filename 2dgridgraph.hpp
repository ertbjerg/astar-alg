#include <string>
#include <tuple>
#include <vector>
#include "gtest/gtest.h"

#pragma once

/** 
 * GridGraph represents a maze as a Graph (with nodes and edges) 
 * Interface for solving the maze with the A*-algorihthm
 * A second Interface for clients for constructing GridGraphs 
 * from an ascii-map of a maze
 * 
 * Nodes are referenced by a key, to hide implementation details
 * from users.
 */

// nodes are 2-tuples in a grid. 
// (0,0) -- 1.coordinate --->
//   |
// 2. coordinate
//   |
//   V
// two points of a GridGraph are connected iff manhattan distance 1 
// that is, two nodes are connected with an edge iff 
// gridpoints are directly next to each other up/down or left/right

class GridGraph 
{
public:  // 
    typedef int nodeid_t;

public: // Client interface
    /* 
     * static factory
     * string s: an ascii map of a maze 
     */
    static GridGraph from_ascii_map(const std::string& s);
    nodeid_t start();
    nodeid_t goal();

public: // A*-interface
    std::vector<nodeid_t> neighbors(nodeid_t p);
    int cost(nodeid_t to, nodeid_t from);
    int eta(nodeid_t target, nodeid_t from);

private:
    GridGraph(const std::string& s);
    std::vector<std::tuple<int, int>> nodes;
    nodeid_t startpoint;
    nodeid_t goalpoint;
    static int manhattan_distance(std::tuple<int, int> p, std::tuple<int, int> q);
    
    FRIEND_TEST(GridGraphImplementation, testcase1);
    FRIEND_TEST(GridGraphImplementation, manhattan_distance);
};
