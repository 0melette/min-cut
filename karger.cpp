#include "karger.hpp"
#include "graph.hpp"
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <limits>

double kargerSingleRun(const Graph& originalGraph) {
    
    Graph graph = originalGraph;
    int n = graph.numVertices();
    

    // edge case - graph has 2 or fewer vertices
    if (n <= 2) {
        return graph.edgeWeightSum();
    }

    //  collect edges into set to avoid duplicates
    std::set<Graph::Edge> uniqueEdges;
    for (int v = 0; v < n; v++) {
        for (const auto& edge : *graph.neighbours(v)) {
            uniqueEdges.insert(edge);
        }
    }
    // convert set  to vector for random access O(1)
    std::vector<Graph::Edge> edges(uniqueEdges.begin(), uniqueEdges.end());

    // random number generator - using mersenne twister
    std::random_device rd;
    std::mt19937 gen(rd());

    // union-find structure to track super-vertices
    // each vertex starts in its own set
    std::vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // find the super-vertex the vertex v belongs to
    auto find = [&](int v) {
        while (parent[v] != v) {
            v = parent[v];
        }
        return v;
    };

    // contraction loop
    int active = n;
    while (active > 2) {
        // randomly select an edge
       int randomIndex = rand() % edges.size();
        Graph::Edge e = edges[randomIndex];

        int u = find(e.v1);
        int v = find(e.v2);
        
        // skip self loop
        if (u == v) {
            continue;
        }

        // contract -  merge v into u
        for (int i = 0; i < n; i++) {
            if (parent[i] == v) {
                parent[i] = u;
            }
        }
        
        active--;
    }

    // calculate cut weight
    double cutWeight = 0.0;
    for (const auto& e : edges) {
        int u = find(e.v1);
        int v = find(e.v2);
        if (u != v) {
            cutWeight += e.weight;
        }
    }
    
    return cutWeight;
}

double karger(Graph& graph) {
    int n = graph.numVertices();
    
    if (n <= 2) {
        return graph.edgeWeightSum();
    }

    // number of iterations to increase probability of finding min cut
    // each run is 1/n^2 chance of finding min cut
    int iterations = std::max(50, n * n);
    double minCut = std::numeric_limits<double>::infinity();

    // take the best cut found over all iterations
    for (int i = 0; i < iterations; i++) {
        minCut = std::min(minCut, kargerSingleRun(graph));
    }

    return minCut;
}