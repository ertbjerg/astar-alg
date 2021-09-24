#include "AStarAlgorithm.hpp"

AStarAlgorithm::AStarAlgorithm(const GridGraph& gg, GridGraph::nodeid_t goal, GridGraph::nodeid_t start) 
    : gr(gg)
    , goal(goal)
    , start(start)
    , frontier()
    , completed()
{
    
}

void AStarAlgorithm::solve()
{
    // initialize prio-que with start-point
    // for each node in que:
    //      Check if goal reached - then done 
    //      merge node to completed 
    //      for each neighbor:
    //          if in completed
    //              with not lower cost: Discard and continue
    //              with lower cost: remove from completed
    //          merge to frontier
    initialize();
    while (frontier.is_empty() == false) {
        auto ps = frontier.pop_lowest_prio();
        completed[ps.child] = ps;
        if (ps.child == goal) {
            break;   // success!
        }
        process_neighbors(ps);
    }
}

void AStarAlgorithm::process_neighbors(PathStep ps) 
{
    for (auto n: gr.neighbors(ps.child)) {
        PathStep nps {ps.child, n, ps.accCostToChild + gr.cost(n, ps.child)};
        const auto &it = completed.find(n);
        if (it != completed.end()) {
            if (nps.accCostToChild < ps.accCostToChild) {
                completed.erase(it);
            } else {
                // neighbor is already in completed: dont add to frontier
                continue;
            }
        }
        prioritize(nps);
    }
}

void AStarAlgorithm::initialize() 
{
    PathStep ps {start, start, 0};
    prioritize(ps);
}

void AStarAlgorithm::prioritize(PathStep ps) 
{
    double prio = (double) ps.accCostToChild + gr.eta(goal, ps.child);
    frontier.merge(prio, ps);
}

std::vector<GridGraph::nodeid_t> AStarAlgorithm::path() const
{
    std::vector<GridGraph::nodeid_t> p {goal};
    while (p.back() != start) {

        const auto &it = completed.find(p.back());
        if (it == completed.end()) {
            // no next step towards start
            p.clear(); 
            return p;
        }
        PathStep ps = it->second;
        p.push_back(ps.parent);
        // std::cout << ps.child << " " << ps.parent << std::endl;
    }
    
    std::reverse(p.begin(), p.end());
    return p;
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
    EXPECT_GE(astar.path().size(), 14);
}
