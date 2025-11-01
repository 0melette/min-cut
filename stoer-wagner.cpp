#include "stoer-wagner.hpp"
#include <iostream>

double stoerWagner(Graph& graph) {
    // TODO: Implement Stoer-Wagner algorithm
    // heap?
    // combine nodes with highest weight into one node until 2 remain.
        // combine the weight of all edges going to the supernode into one value in each step, i.e node A -> node B, and node A -> node C gets combined into node A -> node BC, but is separate from node D -> node BC
    // weight of edge between last node and supernode is the min cut for this interation
    // combined last two nodes into one node in the graph, and repeat until all nodes have been combined
    // min cut is the minimum of all interation min cuts

    std::cout << "stoerWagner not yet implemented" << std::endl;
    return 2.0;
}