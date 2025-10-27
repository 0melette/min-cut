#include "graph.hpp"
#include "karger.hpp"
#include "stoer-wagner.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <vector>

TEST(MinCutAlgorithms, FourVertexCycle) {
    std::vector<Graph::Edge> edges = {
        {1.0, 1, 2},
        {1.0, 2, 3}, 
        {1.0, 3, 4},
        {1.0, 4, 1}
    };
    
    Graph graph(4, edges);
    
    double expectedMinCut = 2.0;

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);
    
    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}