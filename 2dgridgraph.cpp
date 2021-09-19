#include <cmath>
#include "2dgridgraph.hpp"

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
    // for (auto &p: this->nodes) {
    //     std::cout << std::get<0>(p) << " " << std::get<1>(p) << std::endl;
    // }
    // auto &p = this->nodes[this->startpoint];
    // std::cout << this->startpoint << " " << std::get<0>(p) << " " << std::get<1>(p) << std::endl;
    // auto &q = this->nodes[this->goalpoint];
    // std::cout << this->goalpoint << " " << std::get<0>(q) << " " << std::get<1>(q) << std::endl;
}

int GridGraph::manhattan_distance(nodeid_t to, nodeid_t from) 
{
    auto p = this->nodes[to];
    auto q = this->nodes[from];
    return std::abs(std::get<0>(p) - std::get<0>(q)) + std::abs(std::get<1>(p) - std::get<1>(q));
}

int GridGraph::start() {return startpoint;}
int GridGraph::goal() {return goalpoint;}

TEST(GridGraphClientInterface, testcase1) 
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg(asciimap);
    EXPECT_NE(gg.start(), gg.goal());
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

TEST(GridGraphImplementation, testcase2)
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg(asciimap);
    EXPECT_EQ(gg.manhattan_distance(gg.startpoint, gg.goalpoint), 8);
    EXPECT_EQ(gg.manhattan_distance(gg.goalpoint, gg.startpoint), 8);
    EXPECT_EQ(gg.manhattan_distance(0, 1), 1);
    EXPECT_EQ(gg.manhattan_distance(2, 1), 2);
}