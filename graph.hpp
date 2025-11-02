#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <set>
#include <string>
#include <vector>

// Class for undirected graphs with edge weights
class Graph {
public:
  struct Edge { // struct is weught, v1, v2
    double weight{};
    int v1{};
    int v2{};
    auto operator<=>(const Edge &) const = default;
  };

private:
  std::vector<std::set<Edge>> adjList{};

public:
  // default constructor
  Graph();
  // construct graph with n vertices and optionally provide
  // a vector of edges
  explicit Graph(int n, std::vector<Edge> = {});
  // read list of edges in from a file
  explicit Graph(const std::string &inputFile);

  void addEdge(const Edge &);
  int numVertices() const;
  double edgeWeightSum() const;

  // let the user interface with the graph via a const iterator
  // const so they can't change our graph with the iterator
  using iterator = std::vector<std::set<Edge>>::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const { return adjList.cbegin(); }

  iterator end() const { return adjList.cend(); }

  // return iterator to a particular vertex
  iterator neighbours(int a) const { return adjList.cbegin() + a; }
};


// print out a Graph
std::ostream &operator<<(std::ostream &, const Graph &);
// print out an Edge
std::ostream &operator<<(std::ostream &, const Graph::Edge &);

#endif // GRAPH_HPP_
