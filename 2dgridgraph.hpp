#include <string>
#include <tuple>
#include <vector>
#include "gtest/gtest.h"


#pragma once

// (0,0) -- 1.coordinate --->
//   |
// 2. coordinate
//   |
//   V

/* two points of a GridGraph are connected iff manhattan distance 1 */
/* TODO: remove testcase of manhattan distance -> cost, eta testcase */ 
class GridGraph 
{
public:  // 
    typedef int nodeid_t;

public: // Client interface
    /* 
     * construct from string 
     * string s: an ascii map of a maze 
     */
    GridGraph(const std::string& s);

    nodeid_t start();
    nodeid_t goal();

public: // A*-interface
    std::vector<nodeid_t> neighbors(nodeid_t p);
    int cost(nodeid_t to, nodeid_t from);
    int eta(nodeid_t target, nodeid_t from);

private:
    std::vector<std::tuple<int, int>> nodes;
    nodeid_t startpoint;
    nodeid_t goalpoint;
    static int manhattan_distance(std::tuple<int, int> p, std::tuple<int, int> q);
    
    FRIEND_TEST(GridGraphImplementation, testcase1);
    FRIEND_TEST(GridGraphImplementation, manhattan_distance);
};
