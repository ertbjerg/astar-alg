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
class GridGraph 
{
public:  // 
    typedef int nodeid_t;

public: // Client interface
    /* construct from string 
     * string s: an ascii map of a maze 
     */
    GridGraph(const std::string& s);

    nodeid_t start();
    nodeid_t goal();

public: // A*-interface
    std::vector<nodeid_t> neighboors(nodeid_t p);
    int cost(nodeid_t to, nodeid_t from) {return manhattan_distance(to, from);};
    int eta(nodeid_t target, nodeid_t from) {return manhattan_distance(target, from);};

private:
    std::vector<std::tuple<int, int>> nodes;
    nodeid_t startpoint;
    nodeid_t goalpoint;
    int manhattan_distance(nodeid_t to, nodeid_t from);
    
    FRIEND_TEST(GridGraphImplementation, testcase1);
    FRIEND_TEST(GridGraphImplementation, testcase2);
};
