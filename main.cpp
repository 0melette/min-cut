#include "graph.hpp"
#include "karger.hpp"
#include "stoer-wagner.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <random>

//  Test 1 - Simple Cycle
TEST(MinCutAlgorithms, SimpleCycle) {
    std::vector<Graph::Edge> edges = {
        {1.0, 0, 1},
        {1.0, 1, 2},
        {1.0, 2, 3},
        {1.0, 3, 4},
        {1.0, 4, 0},
    };

    Graph graph(5, edges);

    double expectedMinCut = 2.0;

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// Test 1A - Large Simple Cycle
TEST(MinCutAlgorithms, LargeSimpleCycle) {
    const int n = 100; // Make the cycle larger
    std::vector<Graph::Edge> edges;
    for (int i = 0; i < n; ++i) {
        edges.push_back({1.0, i, (i + 1) % n});
    }

    Graph graph(n, edges);

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, 2);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, 2);
}

// Test 1B - Weighted Simple Cycle

TEST(MinCutAlgorithms, WeightedSimpleCycle) {
    std::vector<Graph::Edge> edges = {
        {2.0, 0, 1},
        {12.0, 1, 2},
        {3.0, 2, 3},
        {8.0, 3, 4},
        {3.0, 4, 0},

    };

    Graph graph(5, edges);

    double expectedMinCut = 5.0;

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// TEST 2 - Path Graph
TEST(MinCutAlgorithms, PathGraph) {
    std::vector<Graph::Edge> edges = {
        {1.0, 0, 1},
        {1.0, 1, 2},
        {1.0, 2, 3},
        {1.0, 3, 4}
    };

    Graph graph(5, edges);

    double expectedMinCut = 1.0;  // Any cut will split it fine

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// TEST 3 - Weighted Path Graph
TEST(MinCutAlgorithms, WeightedPathGraph) {
    std::vector<Graph::Edge> edges = {
        {3.0, 0, 1},
        {5.0, 1, 2},
        {2.0, 2, 3},
        {4.0, 3, 4}
    };

    Graph graph(5, edges);

    double expectedMinCut = 2.0;  // Split the lightest edge

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}


// TEST 4 -  Star Graph
TEST(MinCutAlgorithms, StarGraph) {
    std::vector<Graph::Edge> edges = {
        {1.0, 0, 1},  // Center is vertex 0
        {1.0, 0, 2},
        {1.0, 0, 3},
        {1.0, 0, 4},
        {1.0, 0, 5},
    };

    Graph graph(6, edges);

    double expectedMinCut = 1.0;  // Cut off any single spoke

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// TEST 5 - Complete Graph K5
TEST(MinCutAlgorithms, CompleteGraphK5) {
    std::vector<Graph::Edge> edges;
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            edges.push_back({1.0, i, j});
        }
    }

    Graph graph(5, edges);

    double expectedMinCut = 4.0;  // To isolate one vertex you must cut off n-1 edges

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// TEST 6 - Dumbbell Graph
TEST(MinCutAlgorithms, DumbbellGraph) {
    std::vector<Graph::Edge> edges = {
        // First triangle
        {1.0, 0, 1},
        {1.0, 1, 2},
        {1.0, 2, 0},
        // Second triangle
        {1.0, 3, 4},
        {1.0, 4, 5},
        {1.0, 5, 3},
        // Bar
        {1.0, 2, 3}
    };

    Graph graph(6, edges);

    double expectedMinCut = 1.0;  // Cut the bar

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// Broken rn
// // Test 6A - Graph from test6a.txt
// TEST(MinCutAlgorithms, GraphFromTest6A) {
//     // Assuming the Graph constructor can read from a file
//     Graph graph("test6a.txt");

//     double expectedMinCut = 99;  // Replace with the actual expected min cut for the graph in test6a.txt

//     Graph kargerGraph = graph;
//     // double kargerResult = karger(kargerGraph);
//     // EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

//     Graph stoerWagnerGraph = graph;
//     double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
//     EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
// }

// TEST 7 - Complete Bipartite Graph K3,3
TEST(MinCutAlgorithms, CompleteBipartiteK33) {
    std::vector<Graph::Edge> edges;
    // Connect every vertex in group A (0,1,2) to every vertex in group B (3,4,5)
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 6; j++) {
            edges.push_back({1.0, i, j});
        }
    }

    Graph graph(6, edges);

    double expectedMinCut = 3.0;  // Separate the two groups

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}

// Edge Case - Self loop
TEST(MinCutAlgorithms, SelfLoop) {
    std::vector<Graph::Edge> edges = {
        {1.0, 0, 0},
        {1.0, 0, 1},
        {1.0, 1, 1},
        {1.0, 1, 2},
        {1.0, 2, 1},
        {1.0, 2, 3},
        {1.0, 3, 4},
        {1.0, 3, 3},
        {1.0, 4, 0},
        {1.0, 4, 4},
    };

    Graph graph(5, edges);

    double expectedMinCut = 2.0;

    Graph kargerGraph = graph;
    double kargerResult = karger(kargerGraph);
    EXPECT_DOUBLE_EQ(kargerResult, expectedMinCut);

    Graph stoerWagnerGraph = graph;
    double stoerWagnerResult = stoerWagner(stoerWagnerGraph);
    EXPECT_DOUBLE_EQ(stoerWagnerResult, expectedMinCut);
}