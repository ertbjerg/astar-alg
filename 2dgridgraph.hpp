#include <string>
#include <tuple>
#include <set>

#pragma once

/* two points are connected iff manhattan distance 1 */

struct GridPoint
{
public: 
    int id;
    std::tuple<int, int> p;
};

class GridGraph 
{
public:
    /* construct from string 
     * string s: an ascii map of a maze 
     */
    GridGraph(std::string s);

private:
    std::set<GridPoint> nodes;
};
