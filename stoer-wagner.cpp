#include "stoer-wagner.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <algorithm>

double stoerWagner(Graph& graph) {
    auto startNode = graph.begin();
    auto minCut = std::numeric_limits<double>::max();

    int n = graph.numVertices();
    if (n < 2) return 0.0;

    // Build adjacency matrix for easier merging and weight updates instead of using a heap
    std::vector<std::vector<double>> edgeWeights(n, std::vector<double>(n, 0.0));

    // Populate edge weight matrix from graph adjacency lists
    for (int i = 0; i < n; ++i) {
        for (const auto& edge : *graph.neighbours(i)) {
            edgeWeights[edge.v1][edge.v2] = edge.weight;
            edgeWeights[edge.v2][edge.v1] = edge.weight;
        }
    }

    // Initial vertex list (we’ll merge them gradually into supernodes)
    std::vector<int> activeVertices(n);
    for (int i = 0; i < n; ++i)
        activeVertices[i] = i;

    // while there are more than 1 active vertices (unmerged nodes)
    while (activeVertices.size() > 1) {
        int numActive = activeVertices.size();

        std::vector<double> weightToSupernode(numActive, 0.0);
        std::vector<bool> addedToSupernode(numActive, false);
        int previousNodeIndex = 0;
        int lastAddedIndex = 0;

        // combine nodes with highest weight into one node until 2 remain.
        for (int i = 0; i < numActive; ++i) {
            double maxWeight = -1.0;
            int maxWeightNeighbour = -1;

            // Find the node not yet added with the highest weight to the current set
            for (int j = 0; j < numActive; ++j) {
                if (!addedToSupernode[j] && weightToSupernode[j] > maxWeight) {
                    maxWeight = weightToSupernode[j];
                    maxWeightNeighbour = j;
                }
            }

            if (maxWeightNeighbour == -1) break;
            addedToSupernode[maxWeightNeighbour] = true;

            // combine the weight of all edges going to the supernode into one value in each step,
            // i.e node A -> node B, and node A -> node C gets combined into node A -> node BC,
            // but is separate from node D -> node BC
            if (i == numActive - 1) {
                // weight of edge between last node and supernode is the min cut for this interation
                if (weightToSupernode[maxWeightNeighbour] < minCut)
                    minCut = weightToSupernode[maxWeightNeighbour];

                // combined last two nodes into one node in the graph, and repeat until all nodes have been combined
                int mergedNode = activeVertices[previousNodeIndex];
                int removedNode = activeVertices[maxWeightNeighbour];

                // merge edges: accumulate edge weights from removedNode into mergedNode
                for (int k = 0; k < numActive; ++k) {
                    int otherNode = activeVertices[k];
                    if (otherNode != mergedNode && otherNode != removedNode) {
                        edgeWeights[mergedNode][otherNode] += edgeWeights[removedNode][otherNode];
                        edgeWeights[otherNode][mergedNode] = edgeWeights[mergedNode][otherNode];
                    }
                }

                // remove the merged node from the active list
                activeVertices.erase(activeVertices.begin() + maxWeightNeighbour);
                break;
            }

            previousNodeIndex = maxWeightNeighbour;

            // update connection weights for remaining nodes
            for (int j = 0; j < numActive; ++j) {
                if (!addedToSupernode[j])
                    weightToSupernode[j] += edgeWeights[activeVertices[maxWeightNeighbour]][activeVertices[j]];
            }
        }
    }

    // min cut is the minimum of all interation min cuts
    return minCut;
}
