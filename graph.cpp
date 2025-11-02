#include "graph.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

// taken from Prim's Algorithm lecture slide

// Graph member functions
Graph::Graph() = default;

Graph::Graph(int n, std::vector<Edge> vec)
    : adjList{std::vector<std::set<Edge>>(n)} {
  for (const Edge &e : vec) {
    addEdge(e);
  }
}

Graph::Graph(const std::string &inputFile) {
  std::ifstream infile{inputFile};
  if (!infile) {
    std::cerr << inputFile << " could not be opened\n";
    return;
  }
  // first line has number of vertices N
  int N{};
  infile >> N;
  adjList.resize(N);
  int i{};
  int j{};
  double weight{};
  // assume each remaining line is of form  -  lmao the file format is v1, v2, weight
  // origin dest weight
  while (infile >> i >> j >> weight) {
    addEdge({weight, i, j});
  }
}

void Graph::addEdge(const Edge &e) {
  if (e.v1 >= 0 && e.v2 >= 0 && e.v1 < numVertices() && e.v2 < numVertices()) {
    adjList.at(e.v1).insert(e);
    adjList.at(e.v2).insert(e);
  }
}

int Graph::numVertices() const { return static_cast<int>(adjList.size()); }

double Graph::edgeWeightSum() const {
  double totalWeight{0.0};
  for (int i = 0; i < numVertices(); ++i) {
    for (const Edge &e : *neighbours(i)) {
      totalWeight += e.weight;
    }
  }
  // undirected graph -> we have counted every edge twice
  return totalWeight / 2;
}

// print out adjacency list of a Graph
std::ostream &operator<<(std::ostream &out, const Graph &G) {
  for (Graph::iterator it = G.begin(); it != G.end(); ++it) {
    for (const Graph::Edge &e : *it) {
      std::cout << e << ' ';
    }
    std::cout << '\n';
  }
  return out;
}

// print out an Edge
std::ostream &operator<<(std::ostream &out, const Graph::Edge &e) {
  out << '{' << e.v1 << ", " << e.v2 << "}[" << e.weight << ']';
  return out;
}
