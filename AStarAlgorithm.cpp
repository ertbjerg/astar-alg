#include "AStarAlgorithm.hpp"

AStarAlgorithm::AStarAlgorithm(const GridGraph& gg, GridGraph::nodeid_t goal, GridGraph::nodeid_t start) : gr(gg), goal(goal), start(start)
{

}

void AStarAlgorithm::solve()
{
    return;
}

std::vector<GridGraph::nodeid_t> AStarAlgorithm::path() const
{
    return std::vector<GridGraph::nodeid_t> {};
}

#include "2dgridgraph.hpp"

TEST(AStarAlgorithm, testcase1)
{
    std::string asciimap = 
        "S.#...\n"
        "..#.#.\n"
        "..#.#.\n"
        "....#G\n";
    GridGraph gg = GridGraph::from_ascii_map(asciimap);
    AStarAlgorithm astar {gg, gg.goal(), gg.start()};
    astar.solve();
    EXPECT_EQ(astar.path().size(), 14);
}
