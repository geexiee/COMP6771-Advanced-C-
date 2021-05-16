#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {
  gdwg::Graph<std::string, int> g;
  g.InsertNode("hello");
  g.InsertNode("how");
  g.InsertNode("are");
  g.InsertNode("you?");

  g.InsertEdge("hello", "how", 5);
  g.InsertEdge("hello", "are", 8);
  g.InsertEdge("hello", "are", 2);

  g.InsertEdge("how", "you?", 1);
  g.InsertEdge("how", "hello", 4);

  g.InsertEdge("are", "you?", 3);

  gdwg::Graph<int, double> g1;
  g1.InsertNode(1);
  g1.InsertNode(2);
  g1.InsertNode(3);
  g1.InsertEdge(1, 2, 6.9);
  g1.InsertEdge(1, 2, 4.2);
  g1.InsertEdge(2, 3, 1.1);
  g1.InsertEdge(3, 2, 1.2);
  g1.InsertEdge(3, 2, 1.4);
  std::cout << g1;
  //std::cout << g << '\n';
/*
  gdwg::Graph<std::string, int> g2{g};

  std::cout << g2 << "\n";

  // This is a structured binding.
  // https://en.cppreference.com/w/cpp/language/structured_binding
  // It allows you to unpack your tuple.
  for (const auto& [from, to, weight] : g) {
    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
  }*/
}
