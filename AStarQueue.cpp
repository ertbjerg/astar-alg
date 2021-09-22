#include "gtest/gtest.h"
#include "AStarQueue.hpp"

AStarQueue::AStarQueue() {}

void AStarQueue::merge(double prio, PathStep ps) 
{
    for (auto &v: queue) {
        auto &pathstep = std::get<1>(v); 
        if (pathstep.child == ps.child) {
            if (ps.accCostToChild < pathstep.accCostToChild) {
                pathstep = ps;
                auto &pr = std::get<0>(v);
                pr = prio;                                                
            }
            return;
        }
    }
    queue.push_back(std::tuple<double, PathStep> {prio, ps});
}

PathStep AStarQueue::pop_lowest_prio()
{
    auto cmp = [](const std::tuple<double, PathStep> &left, const std::tuple<double, PathStep> &right) {
        auto left_prio = std::get<0>(left);
        auto right_prio = std::get<0>(right);
        return right_prio < left_prio;
    };
    std::sort(queue.begin(), queue.end(), cmp);
    auto ps = std::get<1>(queue.back());
    queue.pop_back();
    return ps;
}

TEST(AStarQueue, merge) 
{
    AStarQueue q;
    PathStep ps0 {0,0,0};
    PathStep ps1 {0,1,10};
    PathStep ps2 {0,2,20};
    PathStep ps3 {0,3,30};
    PathStep ps4 {0,4,40};
    
    q.merge(1.0, ps4);
    q.merge(1.1, ps1);
    q.merge(2.0, ps0);
    q.merge(3.0, ps3);
    q.merge(5.0, ps2);

    ps2.accCostToChild = 12;
    ps3.accCostToChild = 33;

    q.merge(3.0, ps3);
    q.merge(1.7, ps2);
    q.merge(1.2, ps4); //stays at prio 1.0

    EXPECT_EQ(q.pop_lowest_prio().accCostToChild, 40); 
    EXPECT_EQ(q.pop_lowest_prio().accCostToChild, 10);
    EXPECT_EQ(q.pop_lowest_prio().accCostToChild, 12);
    EXPECT_EQ(q.pop_lowest_prio().accCostToChild, 0);
    EXPECT_EQ(q.pop_lowest_prio().accCostToChild, 30);
}


TEST(AStarQueue, pop_lowest_prio)
{
    AStarQueue q;
    PathStep ps0 {0,0,0};
    PathStep ps1 {0,1,10};
    PathStep ps2 {0,2,20};
    PathStep ps3 {0,3,30};
    PathStep ps4 {0,4,40};
    
    q.merge(5.0, ps2);
    q.merge(1.0, ps4);
    q.merge(3.0, ps3);
    q.merge(1.1, ps1);

    EXPECT_EQ(q.pop_lowest_prio().child, 4);
    EXPECT_EQ(q.pop_lowest_prio().child, 1);
    EXPECT_EQ(q.pop_lowest_prio().child, 3);
    q.merge(2.0, ps0);
    EXPECT_EQ(q.pop_lowest_prio().child, 0);
    EXPECT_EQ(q.pop_lowest_prio().child, 2);
}
