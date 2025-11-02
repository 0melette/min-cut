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


    // union-find structure to track super-vertices
    // each vertex starts in its own set
    std::vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // find the super-vertex the vertex v belongs to
    // o(n) path compression not implemented  :p
    auto find = [&](int v) {
        while (parent[v] != v) {
            v = parent[v];
        }
        return v;
    };

    // contraction loop
    int active = n;
    while (active > 2) { // keep contracting until 2 super-vertices remain
        // randomly select an edge
       int randomIndex = rand() % edges.size();
        Graph::Edge e = edges[randomIndex];

        // use the find function to get super-vertices
        int u = find(e.v1);
        int v = find(e.v2);
        
        // skip self loop (edge in the same super-vertex)
        if (u == v) {
            continue;
        }

        // contract -  merge v into u and then update parent
        for (int i = 0; i < n; i++) {
            if (parent[i] == v) {
                parent[i] = u;
            }
        }
        
        active--;
    }

    // calculate cut weight - adding weights of edges in between the two super-vertices
    // total - O(En)
    double cutWeight = 0.0;
    for (const auto& e : edges) { // o(e) 
        int u = find(e.v1);  // both find calls are o(n) worst case
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
    int iterations = std::max(50, n * n); // minimum of 50 for small graphs
    double minCut = std::numeric_limits<double>::infinity();

    // take the best cut found over all iterations (the minimum)
    for (int i = 0; i < iterations; i++) {
        minCut = std::min(minCut, kargerSingleRun(graph));
    }

    return minCut;
}