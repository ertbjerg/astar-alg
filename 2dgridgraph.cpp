#include <algorithm>
#include <cmath>
#include "2dgridgraph.hpp"

GridGraph GridGraph::from_ascii_map(const std::string& s) { return GridGraph {s};}

GridGraph::GridGraph(const std::string& s)
{
    int x1=0, y2=0;
    for (auto &c: s) {
        if (c == '#') { //not part of the maze
            x1++; 
            continue;
        } 
        if (c == '\n') {
            x1 = 0;
            y2++;
            continue;
        }

        this->nodes.push_back(std::tuple<int, int> {x1, y2});
        x1++;

        nodeid_t id = this->nodes.size() - 1; // id is index
        if (c == 'S') {
            this->startpoint = id;
        } 
        if (c == 'G') {
            this->goalpoint = id;
        }
    }
}

int GridGraph::manhattan_distance(std::tuple<int, int> p, std::tuple<int, int> q) 
{
    return std::abs(std::get<0>(p) - std::get<0>(q)) + std::abs(std::get<1>(p) - std::get<1>(q));
}

std::vector<GridGraph::nodeid_t> GridGraph::neighbors(nodeid_t to) 
{   
    auto is_neighbor = [to, this](nodeid_t id) {return GridGraph::manhattan_distance(this->nodes[to], this->nodes[id])==1; };
    std::vector<nodeid_t> result;
    for (auto i = 0; i < nodes.size(); i++) {
        if (is_neighbor(i)) {
            result.push_back(i);
        }
    }
    return result;
}

int GridGraph::cost(nodeid_t to, nodeid_t from) {return manhattan_distance(nodes[to], nodes[from]);}
int GridGraph::eta(nodeid_t target, nodeid_t from) {return manhattan_distance(nodes[target], nodes[from]);}

int GridGraph::start() {return startpoint;}
int GridGraph::goal() {return goalpoint;}

TEST(GridGraphClientInterface, testcase1) 
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg = GridGraph::from_ascii_map(asciimap);
    EXPECT_NE(gg.start(), gg.goal());
}

TEST(GridGraphAStarInterface, testcase1) 
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg = GridGraph::from_ascii_map(asciimap);
    auto nb1 = gg.neighbors(gg.start());
    auto nb2 = gg.neighbors(gg.goal());
    ASSERT_EQ(nb1.size(), 2);
    ASSERT_EQ(nb2.size(), 1);
    auto p = nb1.front();
    auto q = nb1.back();
    auto r = nb2.front();
    EXPECT_EQ(gg.cost(p,gg.start()), 1);
    EXPECT_EQ(gg.cost(q,gg.start()), 1);
    EXPECT_EQ(gg.cost(r,gg.goal()), 1);
}

TEST(GridGraphAStarInterface, testcase2) 
{
    std::string asciimap = 
        "..#...\n"
        ".S.##.\n"
        "..#G#.\n"
        "...##.\n";
    GridGraph gg = GridGraph::from_ascii_map(asciimap);
    auto nb1 = gg.neighbors(gg.start());
    auto nb2 = gg.neighbors(gg.goal());
    EXPECT_EQ(nb1.size(), 4);
    EXPECT_EQ(nb2.size(), 0);
}

TEST(GridGraphAStarInterface, testcase_eta)
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg = GridGraph::from_ascii_map(asciimap);
    EXPECT_EQ(gg.eta(gg.start(), gg.goal()), 8);
    EXPECT_EQ(gg.eta(gg.goal(), gg.start()), 8);
}

TEST(GridGraphAstarInterface, cost)
{
    std::string asciimap = 
        "..#...\n"
        "..#S#.\n"
        "..#G#.\n"
        "....#.\n";
    GridGraph gg = GridGraph::from_ascii_map(asciimap);
    EXPECT_EQ(gg.cost(gg.goal(), gg.start()), 1);
}

TEST(GridGraphImplementation, testcase1)
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg(asciimap);
    EXPECT_EQ(gg.nodes.size(), 18);
    EXPECT_EQ(std::get<0>(gg.nodes[gg.startpoint]), 0);
    EXPECT_EQ(std::get<1>(gg.nodes[gg.startpoint]), 0);
    EXPECT_EQ(std::get<0>(gg.nodes[gg.goalpoint]), 5);
    EXPECT_EQ(std::get<1>(gg.nodes[gg.goalpoint]), 3);
}

TEST(GridGraphImplementation, manhattan_distance)
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg(asciimap);
    EXPECT_EQ(GridGraph::manhattan_distance(gg.nodes[gg.startpoint], gg.nodes[gg.goalpoint]), 8);
    EXPECT_EQ(GridGraph::manhattan_distance(gg.nodes[gg.goalpoint], gg.nodes[gg.startpoint]), 8);
    EXPECT_EQ(GridGraph::manhattan_distance(gg.nodes[0], gg.nodes[1]), 1);
    EXPECT_EQ(GridGraph::manhattan_distance(gg.nodes[2], gg.nodes[1]), 2);
    EXPECT_EQ(GridGraph::manhattan_distance(gg.nodes[0], gg.nodes[0]), 0);
}
